/************************************************************************
 *
 * Implementation of Solution List
 * -------------------------------
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
 * $Id: VecList.C 478 2006-08-09 13:13:30Z keil $
 *
 ************************************************************************/

static const char rcs_id[] = "$Id: VecList.C 478 2006-08-09 13:13:30Z keil $";

#include <GlobalOpt/VecList.h>
#include <Constants.h>
#include <Lists/LinearList.Cgen>
#include <IntervalVector.h>
#include <yaml-cpp/yaml.h>
#include "yaml-cpp/emitter.h"
#include "yaml-cpp/node/emit.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/impl.h"
#include "yaml-cpp/node/convert.h"
#include "yaml-cpp/node/iterator.h"
#include "yaml-cpp/node/detail/impl.h"
#include "GlobalOpt/AppList.h"
#include <list>

#undef LISTOBJECT
#undef LIST
#undef LIST_ELEMENT
#undef LISTCMPFUNC

SOLUTIONLIST_ELEMENT::SOLUTIONLIST_ELEMENT (CONST INTERVAL & va, CONST INTERVAL_VECTOR & ve)
{
  FunctionValue = va;
  Box = ve;
}

SOLUTIONLIST_ELEMENT & SOLUTIONLIST_ELEMENT::operator = (CONST SOLUTIONLIST_ELEMENT & v)
{
  FunctionValue = v.FunctionValue;
  Box = v.Box;
  return *this;
}

ostream & operator << (ostream & o, CONST SOLUTIONLIST_ELEMENT & v)
{
  return o << v.Box << "->" << v.FunctionValue;
}

BOOL SOLUTIONLIST_ELEMENT::operator < (const SOLUTIONLIST_ELEMENT& obj){
    if(Inf (FunctionValue) != Inf (obj.FunctionValue))
        return (Inf (FunctionValue) <= Inf (obj.FunctionValue));
    else
        return (Sup (FunctionValue) <= Sup (obj.FunctionValue));
}

BOOL SolutionCmp (CONST SOLUTIONLIST_ELEMENT & obj1,
                  CONST SOLUTIONLIST_ELEMENT & obj2)
// Compare subroutine for sorting the list by increasing lower bounds of FunctionValue
{
  return (Inf (obj1.FunctionValue) <= Inf (obj2.FunctionValue));
}
REAL thrshld;
bool smallerthanthrshld (CONST SOLUTIONLIST_ELEMENT& el){return Inf(el.FunctionValue) > thrshld;}
VOID Cleanuplis (list<SOLUTIONLIST_ELEMENT> & List, REAL threshold)
// Delete all list entries with Inf(F(y)) > threshold.
{
    thrshld = threshold;
    List.remove_if(smallerthanthrshld);
}

VOID Cleanup (SOLUTIONLIST & list, REAL threshold)
// Delete all list entries with Inf(F(y)) > threshold.
{
  if (IsEmpty (list)) return;
  First (list);
  while (!Finished (list))
    {
      if (Inf (Current (list).FunctionValue) > threshold) RemoveCurrent (list);
      else Next (list);
    }
}

VOID Cleanup (std::list<SOLUTIONLIST_ELEMENT> & list, REAL threshold)
// Delete all list entries with Inf(F(y)) > threshold.
{
    if (list.empty()) return;
    for(std::list<SOLUTIONLIST_ELEMENT>::iterator it = list.begin();it != list.end();)
        if(Inf((*it).FunctionValue) > threshold)
            it = list.erase(it);
        else
            ++it;
}

REAL LowestList(list<SOLUTIONLIST_ELEMENT>& List)
// return Min{Inf(F(y))}
{
  REAL cur_min = Machine::PosInfinity;
  REAL inf;
  for(list<SOLUTIONLIST_ELEMENT>::iterator it = List.begin();it != List.end();++it){
      inf = Inf((*it).FunctionValue);
      if(inf < cur_min)
          cur_min = inf;
  }
  return cur_min;
}

REAL Lowest(SOLUTIONLIST& list)
// return Min{Inf(F(y))}
{
  REAL cur_min = Machine::PosInfinity;
  REAL inf;

  First (list);
  while (!Finished (list))
    {
      inf = Inf (Current (list).FunctionValue);
      if (inf < cur_min) cur_min = inf;
      Next (list);
    }
  return cur_min;
}

VOID Append (SOLUTIONLIST & list,
             CONST INTERVAL_VECTOR & vec, CONST INTERVAL & value)
{
  SOLUTIONLIST_ELEMENT iv(value, vec);
  list += iv;
}

VOID Insert (SOLUTIONLIST & list,
             CONST INTERVAL_VECTOR & vec, CONST INTERVAL & value)
{
  SOLUTIONLIST_ELEMENT iv(value, vec);
  list <<= iv;
}

VOID Append_First (SOLUTIONLIST & list,
                   CONST INTERVAL_VECTOR & vec, CONST INTERVAL & value)
{
  SOLUTIONLIST_ELEMENT iv(value, vec);
  list *= iv;
}

VOID Append (SOLUTIONLIST & dest, SOLUTIONLIST & source)
{
  while (!IsEmpty (source)) {
    dest += First (source);
    --source;
  }
}
void SaveSolList(std::string FileName,SOLUTIONLIST& IN){
    SOLUTIONLIST_ELEMENT Solutionlist_element;
    FileOp SaveList(FileName);
    Solutionlist_element = First(IN);
    SaveList.node.reset();
    SaveList.node["SOLLIST"].push_back(Length(IN));
    
    for(INT ListLen = Length(IN);ListLen > 0;ListLen--){
        Solutionlist_element = First(IN);
        --IN;
        YAML::Node elementnode;
        WriteNode(elementnode,Solutionlist_element.Box);
        WriteNode(elementnode,Solutionlist_element.FunctionValue);
        SaveList.node["SOLLIST"].push_back(elementnode);
    }
}
void SaveSolList(std::string FileName,std::list<SOLUTIONLIST_ELEMENT>& IN){
    FileOp SaveList(FileName,ios::out);
    if(!SaveList.IsOpen()){
        cerr << "Can't open file to save list" << endl;
        return;
    }
    SaveList.node.reset();
    SaveList.node["SOLLIST"].push_back(IN.size());
    
    for(std::list<SOLUTIONLIST_ELEMENT>::iterator it = IN.begin();it != IN.end();
            ++it){
        YAML::Node elementnode;
        WriteNode(elementnode,(*it).Box);
        WriteNode(elementnode,(*it).FunctionValue);
        SaveList.node["SOLLIST"].push_back(elementnode);
    }
    IN.clear();
}

void LoadSolList(std::string FileName,SOLUTIONLIST& IN){
    SOLUTIONLIST_ELEMENT Solutionlist_element;
    YAML::Node Listnode;
    FileOp SaveList(FileName);
    Listnode = SaveList.node["SOLLIST"];
    if(Listnode.IsNull()){
        cerr << "The list isn't Solution list" << endl;
        return;
    }
    for(int contEl = 1;contEl < Listnode.size();contEl++){
        ReadNode(Listnode[contEl],0,Solutionlist_element.Box);
        ReadNode(Listnode[contEl],1,Solutionlist_element.FunctionValue);
        if(contEl == 1)
            IN *= Solutionlist_element;
        else
            IN += Solutionlist_element;
    }
}
void LoadSolList(std::string FileName,std::list<SOLUTIONLIST_ELEMENT>& IN){
    SOLUTIONLIST_ELEMENT Solutionlist_element;
    YAML::Node Listnode;
    FileOp SaveList(FileName);
    Listnode = SaveList.node["SOLLIST"];
    if(Listnode.IsNull()){
        cerr << "The list isn't Solution list" << endl;
        return;
    }
    for(int contEl = 1;contEl < Listnode.size();contEl++){
        ReadNode(Listnode[contEl],0,Solutionlist_element.Box);
        ReadNode(Listnode[contEl],1,Solutionlist_element.FunctionValue);
        if(Dimension(Solutionlist_element.Box) == 0)
            continue;
        IN.push_back(Solutionlist_element);
    }
}
