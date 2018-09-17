/************************************************************************
 *
 * Implementation of Unconstrained Minimization Algorithm
 * ------------------------------------------------------
 *
 * Copyright (C) 1995, 1997 Olaf Knueppel
 *
 * This file is part of PROFIL/BIAS.
 *
 * PROFIL/BIAS is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 *
 * $Id: UnconstrainedOpt.C 480 2006-10-05 15:34:01Z keil $
 *
 ************************************************************************/

static const char rcs_id[] = "$Id: UnconstrainedOpt.C 480 2006-10-05 15:34:01Z keil $";

#include <Utilities.h>
#include <Functions.h>
#include <Constants.h>
#include <GlobalOpt/VecUtils.h>
#include <GlobalOpt/Expand.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <GlobalOpt/UnconstrainedOpt.h>
#include <LocalOpt/Brent.h>
#include <memory>

using namespace YAML;

#define DOUBLE_SPLIT   // If Inf(y1) == Inf(y2), new split point at 0.49 instead of 0.5
#undef  MONOTON_TEST   // Monotonicity test
#define  SORT_LIST      // Sort solution list
#define FILELEN 10000     // Numbers of elements in List saved files
#define AUTODIFF_COMPUTE_HESSIAN

// Some parameters are kept static in order to avoid large parameter lists:
static INTEGER_VECTOR maxdir;
static REAL CurrentUpperBound;
static REAL LocalExpandFactor2 = 0.1;
static REAL LocalExpandFactor3 = 0.001;
static INT ContBranches;
static INT MaxBranch;
static INTERVAL_VECTOR FunctionDomain;
std::unique_ptr<FUNCTION> TheFunction(new FUNCTION);

static INTERVAL_VECTOR Lower (CONST INTERVAL_VECTOR & x,
                              INT split, REAL ratio)
// Bisect x normal to direction "split" and return the lower half.
{
  INT dim = Dimension (x);
  INTERVAL_VECTOR t (dim);

  CheckVectorIndex (split, x);
  MakeTemporary (t);
  t = x;
  t(split) = Hull (Inf (x(split)),
		   (1.0 - ratio) * Inf (x(split)) + ratio * Sup (x(split)));
  return t;
}

static INTERVAL_VECTOR Upper (CONST INTERVAL_VECTOR & x,
                              INT split, REAL ratio)
// Bisect x normal to direction "split" and return the upper half.
{
  INT dim = Dimension (x);
  INTERVAL_VECTOR t (dim);

  CheckVectorIndex (split, x);
  MakeTemporary (t);
  t = x;
  t(split) = Hull ((1.0 - ratio) * Inf (x(split)) + ratio * Sup (x(split)),
		   Sup (x(split)));
  return t;
}

static REAL RealFunction (CONST VECTOR & x)
{
  return Function (*TheFunction, x);
}

static VOID LocalStrategy (CONST INTERVAL_VECTOR & x,
                           APPROXIMATIONLIST & ApproximationList,
                           CONST OPTMISET& optmiset)
{
  INT dim = Dimension (x);
  INT i;
  VECTOR xs(dim), x_start(dim);
  INTERVAL_VECTOR x_heuristic(dim);
  VECTOR expand_diam(dim);
  REAL fs, f_mid, threshold;
  BOOL do_expand;
  INTERVAL fEnclosure;
  
  x_start = Mid (x);
  fs = Function (*TheFunction, x_start);
  f_mid = fs;
  if (fs > CurrentUpperBound) {
    if (Approximation_In_Range (ApproximationList, x)) return;
    threshold = CurrentUpperBound + ((Abs (CurrentUpperBound) < optmiset.Eps) ?
				     optmiset.RaiseFactor :
				     optmiset.RaiseFactor * Abs (CurrentUpperBound));
    if (fs > threshold) return;
  }
  xs = x_start;
  fs = BrentMinimize (xs, Diam (x),
                      optmiset.Eps, optmiset.Eps,
                      RealFunction,optmiset);
  if (!(xs <= FunctionDomain)) {
    for (i = 1; i <= dim; i++)
      if (xs(i) < Inf (FunctionDomain(i))) xs(i) = Inf (FunctionDomain(i));
      else if (xs(i) > Sup (FunctionDomain(i))) xs(i) = Sup (FunctionDomain(i));
    do_expand = FALSE;
  }
  else do_expand = TRUE;

  fs = Sup (Function (*TheFunction, Hull(xs)));
  if (fs < CurrentUpperBound) CurrentUpperBound = fs;

  // Computation of heuristic box which probably will not contain another minimum
  for (i = 1; i <= dim; i++)
    if (Abs (xs(i) - x_start(i)) > LocalExpandFactor2 * Abs (xs(i)))
      expand_diam(i) = Abs (xs(i) - x_start(i));
    else if (LocalExpandFactor2 * Abs (xs(i)) > LocalExpandFactor3)
      expand_diam(i) = LocalExpandFactor2 * Abs (xs(i));
    else expand_diam(i) = LocalExpandFactor3;
  x_heuristic = xs + SymHull (expand_diam);
  x_heuristic = x_heuristic + SymHull (optmiset.HeuristicExpandFactor * Diam (x_heuristic));
  // expansion step
  if (optmiset.UseDerivatives && do_expand && !Expansion_Exists (ApproximationList, xs)) {
    INTERVAL_VECTOR Enclosure(dim), Expansion(dim);

    if (!ExpansionStep (*TheFunction, FunctionDomain,
                        xs, Enclosure, Expansion)) {
      Resize (Enclosure, 0);
      Resize (Expansion, 0);
      fEnclosure = 0.0;
    }
    else fEnclosure = Function (*TheFunction, Enclosure);
    Append(ApproximationList, xs, fs, x_heuristic, Enclosure, Expansion, fEnclosure);
  }
  else Append(ApproximationList, xs, fs, x_heuristic);
}

static VOID LocalStrategy (CONST INTERVAL_VECTOR & x,
                           std::list<APPROX_ELEMENT> & ApproximationList,
                           CONST OPTMISET& optmiset)
{
  INT dim = Dimension (x);
  INT i;
  VECTOR xs(dim), x_start(dim);
  INTERVAL_VECTOR x_heuristic(dim);
  VECTOR expand_diam(dim);
  REAL fs, f_mid, threshold;
  BOOL do_expand;
  INTERVAL fEnclosure;
  x_start = Mid (x);
  fs = Function (*TheFunction, x_start);
  f_mid = fs;
  if (fs > CurrentUpperBound) {
    if (Approximation_In_Range (ApproximationList, x)) return;
    threshold = CurrentUpperBound + ((Abs (CurrentUpperBound) < optmiset.Eps) ?
				     optmiset.RaiseFactor :
				     optmiset.RaiseFactor * Abs (CurrentUpperBound));
    if (fs > threshold) return;
  }
  xs = x_start;

  fs = BrentMinimize (xs, Diam (x),
                      optmiset.Eps, optmiset.Eps,
                      RealFunction,optmiset);

  if (!(xs <= FunctionDomain)) {
    for (i = 1; i <= dim; i++)
      if (xs(i) < Inf (FunctionDomain(i))) xs(i) = Inf (FunctionDomain(i));
      else if (xs(i) > Sup (FunctionDomain(i))) xs(i) = Sup (FunctionDomain(i));
    do_expand = FALSE;
  }
  else do_expand = TRUE;

  fs = Sup (Function (*TheFunction, Hull(xs)));
  if (fs < CurrentUpperBound) CurrentUpperBound = fs;

  // Computation of heuristic box which probably will not contain another minimum
  for (i = 1; i <= dim; i++)
    if (Abs (xs(i) - x_start(i)) > LocalExpandFactor2 * Abs (xs(i)))
      expand_diam(i) = Abs (xs(i) - x_start(i));
    else if (LocalExpandFactor2 * Abs (xs(i)) > LocalExpandFactor3)
      expand_diam(i) = LocalExpandFactor2 * Abs (xs(i));
    else expand_diam(i) = LocalExpandFactor3;
  x_heuristic = xs + SymHull (expand_diam);
  x_heuristic = x_heuristic + SymHull (optmiset.HeuristicExpandFactor * Diam (x_heuristic));
  // expansion step
  if (optmiset.UseDerivatives && do_expand && !Expansion_Exists (ApproximationList, xs)) {
    INTERVAL_VECTOR Enclosure(dim), Expansion(dim);

    if (!ExpansionStep (*TheFunction, FunctionDomain,
                        xs, Enclosure, Expansion)) {
      Resize (Enclosure, 0);
      Resize (Expansion, 0);
      fEnclosure = 0.0;
    }
    else fEnclosure = Function (*TheFunction, Enclosure);
    ApproximationList.emplace(ApproximationList.end(),fs,x_heuristic,Enclosure,Expansion,fEnclosure,xs);
  }
  else ApproximationList.emplace(ApproximationList.end(), fs,x_heuristic,xs  );
}
static VOID LocalCalib (CONST INTERVAL_VECTOR & x,
                           std::list<APPROX_ELEMENT> & ApproximationList,
                           CONST OPTMISET& optmiset)
{
  INT dim = Dimension (x);
  INT i;
  VECTOR xs(dim), x_start(dim);
  INTERVAL_VECTOR x_heuristic(dim);
  VECTOR expand_diam(dim);
  REAL fs, f_mid, threshold;
  BOOL do_expand;
  INTERVAL fEnclosure;

  x_start = Mid (x);
  fs = Function (*TheFunction, x_start);
  f_mid = fs;
  if (fs > CurrentUpperBound) {
    if (Approximation_In_Range (ApproximationList, x)) return;
    threshold = CurrentUpperBound + ((Abs (CurrentUpperBound) < optmiset.Eps) ?
				     optmiset.RaiseFactor :
				     optmiset.RaiseFactor * Abs (CurrentUpperBound));
    if (fs > threshold) return;
  }
  xs = x_start;

  fs = BrentMinimize (xs, Diam (x),
                      optmiset.Eps, optmiset.Eps,
                      RealFunction,optmiset);

  if (!(xs <= FunctionDomain)) {
    for (i = 1; i <= dim; i++)
      if (xs(i) < Inf (FunctionDomain(i))) xs(i) = Inf (FunctionDomain(i));
      else if (xs(i) > Sup (FunctionDomain(i))) xs(i) = Sup (FunctionDomain(i));
    do_expand = FALSE;
  }
  else do_expand = TRUE;

  fs = Sup (Function (*TheFunction, Hull(xs)));
  if (fs < CurrentUpperBound) CurrentUpperBound = fs;

  // Computation of heuristic box which probably will not contain another minimum
  for (i = 1; i <= dim; i++)
    if (Abs (xs(i) - x_start(i)) > LocalExpandFactor2 * Abs (xs(i)))
      expand_diam(i) = Abs (xs(i) - x_start(i));
    else if (LocalExpandFactor2 * Abs (xs(i)) > LocalExpandFactor3)
      expand_diam(i) = LocalExpandFactor2 * Abs (xs(i));
    else expand_diam(i) = LocalExpandFactor3;
  x_heuristic = xs + SymHull (expand_diam);
  x_heuristic = x_heuristic + SymHull (optmiset.HeuristicExpandFactor * Diam (x_heuristic));
  // expansion step
  if (optmiset.UseDerivatives && do_expand && !Expansion_Exists (ApproximationList, xs)) {
    INTERVAL_VECTOR Enclosure(dim), Expansion(dim);

    if (!ExpansionStep (*TheFunction, FunctionDomain,
                        xs, Enclosure, Expansion)) {
      Resize (Enclosure, 0);
      Resize (Expansion, 0);
      fEnclosure = 0.0;
    }
    else fEnclosure = Function (*TheFunction, Enclosure);
    ApproximationList.emplace(ApproximationList.end(),fs,x_heuristic,Enclosure,Expansion,fEnclosure,xs);
  }
  else ApproximationList.emplace(ApproximationList.end(), fs,x_heuristic,xs  );
}
static VOID RecursiveBranch (SOLUTIONLIST_ELEMENT & y,
                                std::list<APPROX_ELEMENT> & ApproximationList,
                                std::list<SOLUTIONLIST_ELEMENT> & Sollist, 
                                CONST OPTMISET& optmiset,
                                INT Level)
{
    INT dim = Dimension (y.Box);
  INT Split;
  SOLUTIONLIST_ELEMENT y1, y2, temp;
  if (Inf (y.FunctionValue) > CurrentUpperBound) return;
  Split = Level % dim + 1;
  y1.Box = Lower (y.Box, maxdir(Split));
  y2.Box = Upper (y.Box, maxdir(Split));
  if (optmiset.UseDerivatives) {
    if (Expansion_Exists (ApproximationList, y1.Box))
      y1.FunctionValue = Hull (Machine::PosInfinity);
    else y1.FunctionValue = Function (*TheFunction, y1.Box);
    if (Expansion_Exists (ApproximationList, y2.Box))
      y2.FunctionValue = Hull (Machine::PosInfinity);
    else y2.FunctionValue = Function (*TheFunction, y2.Box);
  }
  else {
    y1.FunctionValue = Function (*TheFunction, y1.Box);
    y2.FunctionValue = Function (*TheFunction, y2.Box);
  }
#ifdef MONOTON_TEST
  INTERVAL_VECTOR g(dim);
  INT ii;
  g = Gradient (*TheFunction, y1.Box);
  for (ii = 1; ii <= dim; ii++)
    if (!(0.0 <= g(ii))) y1.FunctionValue = Hull (Machine::PosInfinity);
  g = Gradient (*TheFunction, y2.Box);
  for (ii = 1; ii <= dim; ii++)
    if (!(0.0 <= g(ii))) y2.FunctionValue = Hull (Machine::PosInfinity);
#endif
    if ((Inf (y1.FunctionValue) > CurrentUpperBound)
      && (Inf (y2.FunctionValue) > CurrentUpperBound)) return;
#ifdef DOUBLE_SPLIT
  if (Inf (y1.FunctionValue) == Inf (y2.FunctionValue))
    {
      y1.Box = Lower (y.Box, maxdir(Split), 0.49);
      y2.Box = Upper (y.Box, maxdir(Split), 0.49);
      if (optmiset.UseDerivatives) {
	if (Expansion_Exists (ApproximationList, y1.Box))
	  y1.FunctionValue = Hull (Machine::PosInfinity);
	else y1.FunctionValue = Function (*TheFunction, y1.Box);
	if (Expansion_Exists (ApproximationList, y2.Box))
	  y2.FunctionValue = Hull (Machine::PosInfinity);
	else y2.FunctionValue = Function (*TheFunction, y2.Box);
      }
      else {
	y1.FunctionValue = Function (*TheFunction, y1.Box);
	y2.FunctionValue = Function (*TheFunction, y2.Box);
      }
    }
#endif
  if (Inf (y1.FunctionValue) > Inf (y2.FunctionValue))
    { temp = y1; y1 = y2; y2 = temp; }
  if (++Level == optmiset.BranchLevels)
    {
      if (Sollist.empty()){
	LocalStrategy (y1.Box, ApproximationList,optmiset);
      }
      if (Inf (y1.FunctionValue) <= CurrentUpperBound) Sollist.push_back(y1);
      if (Inf (y2.FunctionValue) <= CurrentUpperBound) Sollist.push_back(y2);
#ifdef SORT_LIST
      Sollist.sort();
      if(Sollist.size() > optmiset.MaxBranches){
        std::list<SOLUTIONLIST_ELEMENT>::iterator it = Sollist.end();
        while(Sollist.size() > optmiset.MaxBranches)
            Sollist.erase(--it);
        CurrentUpperBound = Sup(Sollist.back().FunctionValue);
      }
#endif
    }
  else
    {
      RecursiveBranch (y1, ApproximationList, Sollist, optmiset,Level);
      RecursiveBranch (y2, ApproximationList, Sollist, optmiset,Level);
    }
}

static VOID UnRecursiveBranch (SOLUTIONLIST_ELEMENT & y,
                                std::list<APPROX_ELEMENT> & ApproximationList,
                                std::list<SOLUTIONLIST_ELEMENT> & Sollist, 
                                CONST OPTMISET& optmiset){
    INT Level = 0;
    INT dim = Dimension (y.Box);
    INT Split;
    list<SOLUTIONLIST_ELEMENT> ly2;
    SOLUTIONLIST_ELEMENT y1, y2, temp;
    list<int> veclevel;
    for(int loop = 0;loop < optmiset.MaxRecursive;loop++){
        if (Mid (y.FunctionValue) > CurrentUpperBound){
            if(ly2.empty()){
                break;
            }else{
                y = ly2.front();
                ly2.pop_front();
                Level = veclevel.front();
                veclevel.pop_front();
                continue;
            }
        }
        Split = Level % dim + 1;
        y1.Box = Lower (y.Box, maxdir(Split));
        y2.Box = Upper (y.Box, maxdir(Split));
        if (optmiset.UseDerivatives) {
            if (Expansion_Exists (ApproximationList, y1.Box))
                y1.FunctionValue = Hull (Machine::PosInfinity);
            else y1.FunctionValue = Function (*TheFunction, y1.Box);
            if (Expansion_Exists (ApproximationList, y2.Box))
                y2.FunctionValue = Hull (Machine::PosInfinity);
            else y2.FunctionValue = Function (*TheFunction, y2.Box);
        }
        else {
            y1.FunctionValue = Function (*TheFunction, y1.Box);
            y2.FunctionValue = Function (*TheFunction, y2.Box);
        }
#ifdef MONOTON_TEST
        INTERVAL_VECTOR g(dim);
        INT ii;
        g = Gradient (*TheFunction, y1.Box);
        for (ii = 1; ii <= dim; ii++)
        if (!(0.0 <= g(ii))) y1.FunctionValue = Hull (Machine::PosInfinity);
            g = Gradient (*TheFunction, y2.Box);
        for (ii = 1; ii <= dim; ii++)
            if (!(0.0 <= g(ii))) y2.FunctionValue = Hull (Machine::PosInfinity);
#endif
        if ((Mid (y1.FunctionValue) > CurrentUpperBound)
            && (Mid (y2.FunctionValue) > CurrentUpperBound)){
            if(ly2.empty()){
                break;
            }else{
                y = ly2.front();
                ly2.pop_front();
                if(veclevel.empty())return;
                Level = veclevel.front();
                veclevel.pop_front();
                continue;
            }            
        }
#ifdef DOUBLE_SPLIT
        if (Mid (y1.FunctionValue) == Mid (y2.FunctionValue))
        {
            y1.Box = Lower (y.Box, maxdir(Split), 0.49);
            y2.Box = Upper (y.Box, maxdir(Split), 0.49);
            if (optmiset.UseDerivatives) {
                if (Expansion_Exists (ApproximationList, y1.Box))
                    y1.FunctionValue = Hull (Machine::PosInfinity);
                else y1.FunctionValue = Function (*TheFunction, y1.Box);
                if (Expansion_Exists (ApproximationList, y2.Box))
                    y2.FunctionValue = Hull (Machine::PosInfinity);
                else y2.FunctionValue = Function (*TheFunction, y2.Box);
            }
            else {
                y1.FunctionValue = Function (*TheFunction, y1.Box);
                y2.FunctionValue = Function (*TheFunction, y2.Box);
            }
        }
#endif
        if (Mid (y1.FunctionValue) > Mid (y2.FunctionValue))
        { temp = y1; y1 = y2; y2 = temp; }
        if (++Level == optmiset.BranchLevels)
        {
            if (Sollist.empty()){
                LocalStrategy (y1.Box, ApproximationList,optmiset);
            }
            if (Mid (y1.FunctionValue) <= CurrentUpperBound) Sollist.push_back(y1);
            if (Mid (y2.FunctionValue) <= CurrentUpperBound) Sollist.push_back(y2);
#ifdef SORT_LIST
            Sollist.sort();
            if(Sollist.size() > optmiset.MaxBranches){
                while(Sollist.size() > optmiset.MaxBranches)
                    Sollist.pop_back();
                CurrentUpperBound = Sup(Sollist.back().FunctionValue);
            }
#endif
            if(ly2.empty())break;
            y = ly2.front();
            ly2.pop_front();
            if(!veclevel.empty()){
                Level = veclevel.front();
                veclevel.pop_front();
            }
        }else{
            y = y1;
            ly2.push_back(y2);
            veclevel.push_back(Level);
        }
    }
}

static VOID Branch (SOLUTIONLIST_ELEMENT & y,
                                std::list<APPROX_ELEMENT> & ApproximationList,
                                std::list<SOLUTIONLIST_ELEMENT> & list, 
                                CONST OPTMISET& optmiset)
{
//  RecursiveBranch (y, ApproximationList, list, optmiset,0);
    UnRecursiveBranch (y,ApproximationList,list,optmiset);
}
static VOID RecursiveBranch (SOLUTIONLIST_ELEMENT & y,
                                INT & ContSaveFile,
                                APPROXIMATIONLIST & ApproximationList,
                                SOLUTIONLIST & list, 
                                CONST OPTMISET& optmiset,
                                INT Level)
{
    INT dim = Dimension (y.Box);
  INT Split;
  SOLUTIONLIST_ELEMENT y1, y2, temp;
  if (Inf (y.FunctionValue) > CurrentUpperBound) return;
  Split = Level % dim + 1;
  y1.Box = Lower (y.Box, maxdir(Split));
  y2.Box = Upper (y.Box, maxdir(Split));
  if (optmiset.UseDerivatives) {
    if (Expansion_Exists (ApproximationList, y1.Box))
      y1.FunctionValue = Hull (Machine::PosInfinity);
    else y1.FunctionValue = Function (*TheFunction, y1.Box);
    if (Expansion_Exists (ApproximationList, y2.Box))
      y2.FunctionValue = Hull (Machine::PosInfinity);
    else y2.FunctionValue = Function (*TheFunction, y2.Box);
  }
  else {
    y1.FunctionValue = Function (*TheFunction, y1.Box);
    y2.FunctionValue = Function (*TheFunction, y2.Box);
  }
#ifdef MONOTON_TEST
  INTERVAL_VECTOR g(dim);
  INT ii;
  g = Gradient (*TheFunction, y1.Box);
  for (ii = 1; ii <= dim; ii++)
    if (!(0.0 <= g(ii))) y1.FunctionValue = Hull (Machine::PosInfinity);
  g = Gradient (*TheFunction, y2.Box);
  for (ii = 1; ii <= dim; ii++)
    if (!(0.0 <= g(ii))) y2.FunctionValue = Hull (Machine::PosInfinity);
#endif
  if ((Inf (y1.FunctionValue) > CurrentUpperBound)
      && (Inf (y2.FunctionValue) > CurrentUpperBound)) return;
#ifdef DOUBLE_SPLIT
  if (Inf (y1.FunctionValue) == Inf (y2.FunctionValue))
    {
      y1.Box = Lower (y.Box, maxdir(Split), 0.49);
      y2.Box = Upper (y.Box, maxdir(Split), 0.49);
      if (optmiset.UseDerivatives) {
	if (Expansion_Exists (ApproximationList, y1.Box))
	  y1.FunctionValue = Hull (Machine::PosInfinity);
	else y1.FunctionValue = Function (*TheFunction, y1.Box);
	if (Expansion_Exists (ApproximationList, y2.Box))
	  y2.FunctionValue = Hull (Machine::PosInfinity);
	else y2.FunctionValue = Function (*TheFunction, y2.Box);
      }
      else {
	y1.FunctionValue = Function (*TheFunction, y1.Box);
	y2.FunctionValue = Function (*TheFunction, y2.Box);
      }
    }
#endif
  if (Inf (y1.FunctionValue) > Inf (y2.FunctionValue))
    { temp = y1; y1 = y2; y2 = temp; }
  if (++Level == optmiset.BranchLevels){
      if (IsEmpty (list) && ContSaveFile <= 0)
	LocalStrategy (y1.Box, ApproximationList, optmiset);
#ifdef SORT_LIST
      if (Inf (y1.FunctionValue) <= CurrentUpperBound) list <<= y1;
      if (Length(list) == optmiset.MaxBranches){
          CurrentUpperBound = Sup(Last(list).FunctionValue);
      }else if(Length(list) > optmiset.MaxBranches){
          INT ListLen = Length(list)-1;
          for(First(list);ListLen > 0;Next(list),ListLen--)
              if(ListLen == 1)CurrentUpperBound = Sup(Current(list).FunctionValue);
          RemoveCurrent(list);
          First(list);
      }
      if (Length(list) > FILELEN){
          string LastFileName = "./listfiles/listfile" + to_string(ContSaveFile) + ".yml";
          SaveSolList(LastFileName,list);
          ContSaveFile++;
      }
      if (Inf (y2.FunctionValue) <= CurrentUpperBound) list <<= y2;
      if (Length(list) == optmiset.MaxBranches){
          CurrentUpperBound = Sup(Last(list).FunctionValue);
      }else if(Length(list) > optmiset.MaxBranches){
          INT ListLen = Length(list)-1;
          for(First(list);ListLen > 0;Next(list),ListLen--)
              if(ListLen == 1)CurrentUpperBound = Sup(Current(list).FunctionValue);
          RemoveCurrent(list);
          First(list);
      }
      if (Length(list) > FILELEN){
          string LastFileName = "./listfiles/listfile" + to_string(ContSaveFile) + ".yml";
          SaveSolList(LastFileName,list);
          ContSaveFile++;
      }
#else
      if (Length(list) >= optmiset.MaxBranches)return;
      if (Inf (y1.FunctionValue) <= CurrentUpperBound) list += y1;
      if (Inf (y2.FunctionValue) <= CurrentUpperBound) list += y2;
      if (Length(list) > FILELEN){
          string LastFileName = "./listfiles/listfile" + to_string(ContSaveFile) + ".yml";
          SaveSolList(LastFileName,list);
          ContSaveFile++;
      }
#endif
    }
  else
    {
      RecursiveBranch (y1, ContSaveFile, ApproximationList, list, optmiset,Level);
      RecursiveBranch (y2, ContSaveFile, ApproximationList, list, optmiset,Level);
    }
}

static VOID RecursiveBranch (SOLUTIONLIST_ELEMENT & y,
                                INT & ContSaveFile,
                                std::list<APPROX_ELEMENT> & ApproximationList,
                                std::list<SOLUTIONLIST_ELEMENT> & Sollist, 
                                CONST OPTMISET& optmiset,
                                INT Level)
{
    
    INT dim = Dimension (y.Box);
  INT Split;
  SOLUTIONLIST_ELEMENT y1, y2, temp;
  if (Inf (y.FunctionValue) > CurrentUpperBound) return;
  Split = Level % dim + 1;
  y1.Box = Lower (y.Box, maxdir(Split));
  y2.Box = Upper (y.Box, maxdir(Split));
  if (optmiset.UseDerivatives) {
    if (Expansion_Exists (ApproximationList, y1.Box))
      y1.FunctionValue = Hull (Machine::PosInfinity);
    else y1.FunctionValue = Function (*TheFunction, y1.Box);
    if (Expansion_Exists (ApproximationList, y2.Box))
      y2.FunctionValue = Hull (Machine::PosInfinity);
    else y2.FunctionValue = Function (*TheFunction, y2.Box);
  }
  else {
    y1.FunctionValue = Function (*TheFunction, y1.Box);
    y2.FunctionValue = Function (*TheFunction, y2.Box);
  }
#ifdef MONOTON_TEST
  INTERVAL_VECTOR g(dim);
  INT ii;
  g = Gradient (*TheFunction, y1.Box);
  for (ii = 1; ii <= dim; ii++)
    if (!(0.0 <= g(ii))) y1.FunctionValue = Hull (Machine::PosInfinity);
  g = Gradient (*TheFunction, y2.Box);
  for (ii = 1; ii <= dim; ii++)
    if (!(0.0 <= g(ii))) y2.FunctionValue = Hull (Machine::PosInfinity);
#endif
  if ((Inf (y1.FunctionValue) > CurrentUpperBound)
      && (Inf (y2.FunctionValue) > CurrentUpperBound)) return;
#ifdef DOUBLE_SPLIT
  if (Inf (y1.FunctionValue) == Inf (y2.FunctionValue))
    {
      y1.Box = Lower (y.Box, maxdir(Split), 0.49);
      y2.Box = Upper (y.Box, maxdir(Split), 0.49);
      if (optmiset.UseDerivatives) {
	if (Expansion_Exists (ApproximationList, y1.Box))
	  y1.FunctionValue = Hull (Machine::PosInfinity);
	else y1.FunctionValue = Function (*TheFunction, y1.Box);
	if (Expansion_Exists (ApproximationList, y2.Box))
	  y2.FunctionValue = Hull (Machine::PosInfinity);
	else y2.FunctionValue = Function (*TheFunction, y2.Box);
      }
      else {
	y1.FunctionValue = Function (*TheFunction, y1.Box);
	y2.FunctionValue = Function (*TheFunction, y2.Box);
      }
    }
#endif
  if (Inf (y1.FunctionValue) > Inf (y2.FunctionValue))
    { temp = y1; y1 = y2; y2 = temp; }
  if (++Level == optmiset.BranchLevels){
      if (Sollist.empty() && ContSaveFile <= 0)
	LocalStrategy (y1.Box, ApproximationList, optmiset);
      if (Inf (y1.FunctionValue) <= CurrentUpperBound)
          Sollist.push_back(y1);
      if (Inf (y2.FunctionValue) <= CurrentUpperBound)
          Sollist.push_back(y2);
#ifdef SORT_LIST
      Sollist.sort();
      if(Sollist.size() > optmiset.MaxBranches){
        std::list<SOLUTIONLIST_ELEMENT>::iterator it = Sollist.end();
        while(Sollist.size() > optmiset.MaxBranches)Sollist.erase(--it);
      }
#endif
      if (Sollist.size() > FILELEN){
          string LastFileName = "./listfiles/listfile" + to_string(ContSaveFile) + ".yml";
          SaveSolList(LastFileName,Sollist);
          ContSaveFile++;
      }
    }
  else
    {
      RecursiveBranch (y1, ContSaveFile, ApproximationList, Sollist, optmiset,Level);
      RecursiveBranch (y2, ContSaveFile, ApproximationList, Sollist, optmiset,Level);
    }
}

static VOID Branch (SOLUTIONLIST_ELEMENT & y,
                                INT & ContSaveFile,
                                APPROXIMATIONLIST & ApproximationList,
                                SOLUTIONLIST & list, 
                                CONST OPTMISET& optmiset)
{
    RecursiveBranch (y, ContSaveFile, ApproximationList, list, optmiset,0);
}

static VOID Branch (SOLUTIONLIST_ELEMENT & y,
                                INT & ContSaveFile,
                                std::list<APPROX_ELEMENT> & ApproximationList,
                                std::list<SOLUTIONLIST_ELEMENT> & list, 
                                CONST OPTMISET& optmiset)
{
    RecursiveBranch (y, ContSaveFile, ApproximationList, list, optmiset,0);
}


VOID UnconstrainedOptimization (std::list<SOLUTIONLIST_ELEMENT> & SolutionList,
				std::list<APPROX_ELEMENT> & ApproximationList,
				OPTMISET& optmiset)
{
  INT len;
  SOLUTIONLIST_ELEMENT y;
  
  if (SolutionList.empty()) return;
  CurrentUpperBound = optmiset.UpperBound;
  for (INT i = 0; i < optmiset.Iterations; i++) {
        if (SolutionList.empty()) break;
        len = SolutionList.size();
        std::list<SOLUTIONLIST_ELEMENT> NewSolutionList;
        SOLUTIONLIST_ELEMENT y;
        for (int j = 0; j < len;j++) {
            cout << "   -> Iterations: " << i+1 << " of " << optmiset.Iterations;
            cout  << " -> Loop: " << j+1 << " of " << len << "         " << '\r';
            cout.flush();
            y = SolutionList.front();
            Branch (y, ApproximationList, NewSolutionList, optmiset);
            SolutionList.pop_front();
            SolutionList.merge(NewSolutionList);
            if(SolutionList.size() > optmiset.MaxBranches){
                while(SolutionList.size() > optmiset.MaxBranches)
                    SolutionList.pop_back();                
            }
        }
#ifdef SORT_LIST
        SolutionList.sort();
#endif
//        UpdateLowerBound (SolutionList, optmiset.LowerBound);
    }
    optmiset.UpperBound = CurrentUpperBound;
}

VOID UnconstrainedOptimization (std::string ConfigFileName,
				std::list<APPROX_ELEMENT> & ApproximationList,
				OPTMISET& optmiset)
{
    
    INT i, j, len;
    std::list<SOLUTIONLIST_ELEMENT> SolutionList,SolutionList2;
    SOLUTIONLIST_ELEMENT y;

    if (ConfigFileName.empty()) return;

    CurrentUpperBound = optmiset.UpperBound;
    YAML::Node configfilenode;
    configfilenode = LoadFile(ConfigFileName);
    if(configfilenode.IsNull())configfilenode.push_back("./listfiles/listfile0.yml");
    int ContSaveFile=0,ContLoadFile=0,ContFile=0;
    std::string SolFileName;
    SolFileName = configfilenode[1].as<std::string>();
    LoadSolList(SolFileName,SolutionList);
    int NewLen =SolutionList.size();
    std::string LastFileName;
    for (int i = 0; i < optmiset.Iterations; i++) {
        if (SolutionList.empty()) break;
        std::list<SOLUTIONLIST_ELEMENT> NewSolutionList;
        if(NewLen < optmiset.MaxBranches)
            len = NewLen;
        else
            len = optmiset.MaxBranches;
        NewLen = 0;
        list<SOLUTIONLIST_ELEMENT>::iterator it = SolutionList.begin();
        INT MaxSolList = FILELEN;
        for (j = 0; j < len; j++) {
            cout << "Iterations: " << i+1 << " of " << optmiset.Iterations;
            cout  << " -> Loop: " << j+1 << " of " << len << '\r';
            cout.flush();
            if(j>MaxSolList || SolutionList.empty()){
                if(ContLoadFile <= ContSaveFile){
                    SolFileName = "./listfiles/listfile" + to_string(ContLoadFile) + ".yml";
                    LoadSolList(SolFileName,SolutionList);
                    it = SolutionList.begin();
                    ContLoadFile++;
                    ContFile--;
                    remove(SolFileName.c_str());
                    MaxSolList = j + FILELEN;
                }else{
                    break;
                }
            }
            Branch ((*it),ContSaveFile, ApproximationList, NewSolutionList, optmiset);
            it = SolutionList.erase(SolutionList.begin());
            SolutionList.merge(NewSolutionList);
            NewLen = SolutionList.size() + ContSaveFile*FILELEN;
            NewSolutionList.clear();
        }
#ifdef SORT_LIST
        SolutionList.sort();
#endif
    }
    if(!SolutionList.empty()){
        LastFileName = "./listfiles/listfile" + to_string(ContSaveFile) + ".yml";
        SaveSolList(LastFileName,SolutionList);
    }else{
        cerr << "SolutionList is empty" << endl;
    }
    optmiset.UpperBound = CurrentUpperBound;
}

/*
 * Eps shouldn't be smaller than the square root of the machine precision as it becomes the relative
 * stopping tolerance for the local optimization method.
 */
VOID StartUnconstrainedOptimization (std::list<SOLUTIONLIST_ELEMENT> & SolutionList,
				     std::list<APPROX_ELEMENT> & ApproximationList,
                                     std::unique_ptr<FUNCTION> & f,
                                     OPTMISET& optmiset)
{
    ContBranches = 0;
    MaxBranch = optmiset.MaxBranches;
    FunctionDomain.Delete();
    FunctionDomain = optmiset.TheDomain;
    TheFunction    = std::move(f);
    optmiset.LowerBound = Machine::NegInfinity;
    optmiset.UpperBound = Machine::PosInfinity;
    SortDiam (FunctionDomain, maxdir);
    if(SolutionList.empty())
        SolutionList.emplace(SolutionList.end(),SymHull (Machine::PosInfinity),FunctionDomain);
    optmiset.BranchLevels *= Dimension(optmiset.TheDomain);
    UnconstrainedOptimization (SolutionList, ApproximationList, optmiset);
    optmiset.BranchLevels /= Dimension(optmiset.TheDomain);
    f = std::move(TheFunction);
}


VOID StartUnconstrainedOptimization (std::string ConfigFileName,
				     std::list<APPROX_ELEMENT> & ApproximationList,
                                     std::unique_ptr<FUNCTION> & f,
                                     OPTMISET& optmiset)
{
    FunctionDomain.Delete();
    FunctionDomain = optmiset.TheDomain;
    TheFunction    = std::move(f);
    optmiset.BranchLevels *= Dimension(optmiset.TheDomain);
    optmiset.LowerBound = Machine::NegInfinity;
    optmiset.UpperBound = Machine::PosInfinity;
    SortDiam (FunctionDomain, maxdir);
    std::list<SOLUTIONLIST_ELEMENT> SolutionList;
    SolutionList.push_back(SOLUTIONLIST_ELEMENT(SymHull (Machine::PosInfinity),FunctionDomain));
    YAML::Node configfilenode;
    std::string ListFileName;
    fstream fnode;
    if (ConfigFileName.empty()){
        mkdir("listfile",S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        fnode.open("./listfile/ConfigListFile.yml",ios::out);
        YAML::Node filenamenode;
        ConfigFileName = "./listfile/ConfigListFile.yml";
        filenamenode.push_back("./listfiles/listfile0.yml");
        fnode << "%YAML:1.2" << endl;
        fnode << filenamenode;
        fnode.close();
        ListFileName = "./listfiles/listfile0.yml";
    }
    else{
        std::string dirname;
        int barIdx = ConfigFileName.find_last_of("/");
        dirname = ConfigFileName.substr(0,barIdx);
        mkdir(dirname.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        fnode.open(ConfigFileName,ios::in);
        if(fnode.is_open()){
            configfilenode = LoadFile(ConfigFileName);
            if(configfilenode.IsNull()){
                fnode.close();
                fnode.open(ConfigFileName,ios::out);
                YAML::Node filenamenode;
                filenamenode.push_back(1);
                filenamenode.push_back("./listfiles/listfile0.yml");
                fnode << "%YAML:1.2" << endl;
                fnode << filenamenode;
                filenamenode.reset();
                fnode.close();
                ListFileName = "./listfiles/listfile0.yml";
            }
            else{
                ListFileName = configfilenode[1].as<std::string>();
            }
        }
        else{
            fnode.close();
            fnode.open(ConfigFileName,ios::out);
            YAML::Node filenamenode;
            filenamenode.push_back(1);
            filenamenode.push_back("./listfiles/listfile0.yml");
            fnode << "%YAML:1.2" << endl;
            fnode << filenamenode;
            fnode.close();
            ListFileName = "./listfiles/listfile0.yml";
        }
    }
    fnode.close();
    SaveSolList(ListFileName,SolutionList);
    UnconstrainedOptimization (ConfigFileName, ApproximationList, optmiset);
    optmiset.BranchLevels /= Dimension(optmiset.TheDomain);
    f = std::move(TheFunction);
}

VOID CleanUpLists (SOLUTIONLIST & SolutionList,
		   APPROXIMATIONLIST & ApproximationList,
		   REAL Eps, REAL LowerBound, REAL UpperBound)
{
  REAL CleanApprox = 0.01;

  Cleanup (ApproximationList, UpperBound + ((Abs (UpperBound) < Eps) ?
					    CleanApprox :
					    CleanApprox * Abs (UpperBound)));
  Cleanup (SolutionList, UpperBound);
  UpdateLowerBound (SolutionList, LowerBound);
}

VOID CleanUpLists (std::list<SOLUTIONLIST_ELEMENT> & SolutionList,
		   std::list<APPROX_ELEMENT> & ApproximationList,
		   REAL Eps, REAL LowerBound, REAL UpperBound)
{
  REAL CleanApprox = 0.01;

  Cleanup (ApproximationList, UpperBound + ((Abs (UpperBound) < Eps) ?
					    CleanApprox :
					    CleanApprox * Abs (UpperBound)));
  Cleanup (SolutionList, UpperBound);
  UpdateLowerBound (SolutionList, LowerBound);
}


VOID CleanUpLists (std::string ConfigFileName,
		   APPROXIMATIONLIST & ApproximationList,
		   REAL Eps, REAL LowerBound, REAL UpperBound)
{
    REAL CleanApprox = 0.01;

    Cleanup (ApproximationList, UpperBound + ((Abs (UpperBound) < Eps) ?
                                              CleanApprox :
                                              CleanApprox * Abs (UpperBound)));
    YAML::Node sollistnode;
    fstream filetest;
    filetest.open(ConfigFileName,ios::in);
    if(filetest.is_open())
        sollistnode = LoadFile(ConfigFileName);
    else
        return;
//    SOLUTIONLIST SolutionList;
//    for(int i = 1;i < sollistnode[0].as<int>();i++){
//        cout << "Cleaning: " << i << " of " << sollistnode[0].as<int>() << " files" << endl;
//        LoadSolList(sollistnode[i].as<std::string>(),SolutionList);
//        Cleanup (SolutionList, UpperBound);
//        SaveSolList(sollistnode[i].as<std::string>(),SolutionList);
//        UpdateLowerBound (SolutionList, LowerBound);
//    }
}

VOID CleanUpLists (std::string ConfigFileName,
		   std::list<APPROX_ELEMENT> & ApproximationList,
		   REAL Eps, REAL LowerBound, REAL UpperBound)
{
    REAL CleanApprox = 0.01;

    Cleanup (ApproximationList, UpperBound + ((Abs (UpperBound) < Eps) ?
                                              CleanApprox :
                                              CleanApprox * Abs (UpperBound)));
    YAML::Node sollistnode;
    fstream filetest;
    filetest.open(ConfigFileName,ios::in);
    if(filetest.is_open())
        sollistnode = LoadFile(ConfigFileName);
    else
        return;
//    SOLUTIONLIST SolutionList;
//    for(int i = 1;i < sollistnode[0].as<int>();i++){
//        cout << "Cleaning: " << i << " of " << sollistnode[0].as<int>() << " files" << endl;
//        LoadSolList(sollistnode[i].as<std::string>(),SolutionList);
//        Cleanup (SolutionList, UpperBound);
//        SaveSolList(sollistnode[i].as<std::string>(),SolutionList);
//        UpdateLowerBound (SolutionList, LowerBound);
//    }
}

VOID UpdateLowerBound (SOLUTIONLIST & SolutionList, REAL & LowerBound)
{
  REAL CurrentLow;

  if (!IsEmpty (SolutionList)) {
    CurrentLow = Lowest (SolutionList);
    if (CurrentLow > LowerBound) LowerBound = CurrentLow;
  }
}
VOID UpdateLowerBound (std::list<SOLUTIONLIST_ELEMENT> & SolutionList, REAL & LowerBound)
{
    REAL CurrentLow = Machine::PosInfinity;
    if (!SolutionList.empty()) {
        for(std::list<SOLUTIONLIST_ELEMENT>::iterator it;it != SolutionList.end();++it)
            if(Inf(SolutionList.front().FunctionValue) < CurrentLow)
                CurrentLow = Inf(SolutionList.front().FunctionValue);
        LowerBound = CurrentLow;
  }
}
