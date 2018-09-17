/************************************************************************
 *
 * Definition of Unconstrained Minimization Algorithm
 * --------------------------------------------------
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
 * $Id: UnconstrainedOpt.h 478 2006-08-09 13:13:30Z keil $
 *
 ************************************************************************/

#ifndef __UNCONSTOPT__
#define __UNCONSTOPT__

#include <Boolean.h>
#include <NLF/NLF.hpp>
#include <GlobalOpt/AppList.h>
#include <GlobalOpt/VecList.h>
#include <list>
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <fstream>
#include <Constants.h>

struct OPTMISET{
    INT Iterations;
    INT BranchLevels;
    INT MaxBranches;
    REAL Eps;
    REAL RaiseFactor;
    REAL HeuristicExpandFactor;
    REAL LowerBound;
    REAL UpperBound;
    BOOL UseDerivatives;
    BOOL expansion;
    INT MaxIter;
    INT MaxRecursive;
    INTERVAL_VECTOR TheDomain;
    INT popsize;
    INT ngen;
    float pmut;
    float pcross;
    INT showfx;
    REAL fRohn;
    INT MaxIterNonlin;
    INT MaxIterInnerLoop;
    REAL alpha_exp_factor;
    OPTMISET(){
        Iterations = 2;
        BranchLevels = 2;
        MaxBranches = 100;
        Eps = 0.01;
        RaiseFactor = 0.2;
        HeuristicExpandFactor = 5.0;
        UseDerivatives = true;
        MaxIter = 5000;
        MaxRecursive = 1000000;
        popsize = 70;
        ngen = 10000;
        pmut = 0.02;
        pcross = 0.6;
        UpperBound = Machine::PosInfinity;
        expansion = true;
        showfx = false;
        fRohn = 0.01;
        MaxIterNonlin = 100;
        MaxIterInnerLoop = 100;
        alpha_exp_factor = 1e-8;
    }
    OPTMISET& operator = (const OPTMISET& A){
        Iterations = A.Iterations;
        BranchLevels = A.BranchLevels;
        MaxBranches = A.MaxBranches;
        Eps = A.Eps;
        RaiseFactor = A.RaiseFactor;
        HeuristicExpandFactor = A.HeuristicExpandFactor;
        LowerBound = A.LowerBound;
        UpperBound = A.UpperBound;
        UseDerivatives = A.UseDerivatives;
        expansion = A.expansion;
        MaxIter = A.MaxIter;
        MaxRecursive = A.MaxRecursive;
        TheDomain = A.TheDomain;
        popsize = A.popsize;
        ngen = A.ngen;
        pmut = A.pmut;
        pcross = A.pcross;
        showfx = A.showfx;
        fRohn = A.fRohn;
        MaxIterNonlin = A.MaxIterNonlin;
        MaxIterInnerLoop = A.MaxIterInnerLoop;
        alpha_exp_factor = A.alpha_exp_factor;
    }
};


VOID UnconstrainedOptimization (std::list<SOLUTIONLIST_ELEMENT> & SolutionList,
				std::list<APPROX_ELEMENT> & ApproximationList,
				OPTMISET& optmiset);

VOID UnconstrainedOptimization (std::string baseFileName,
				APPROXIMATIONLIST & ApproximationList,
				OPTMISET& optmiset);
VOID StartUnconstrainedOptimization (std::list<SOLUTIONLIST_ELEMENT> & SolutionList,
				     std::list<APPROX_ELEMENT> & ApproximationList,
                                     std::unique_ptr<FUNCTION> & f,
                                     OPTMISET& optmiset);
VOID StartUnconstrainedOptimization (std::string ConfigFileName,
				     std::list<APPROX_ELEMENT> & ApproximationList,
                                     std::unique_ptr<FUNCTION> & f,
                                     OPTMISET& optmiset);

VOID CleanUpLists (SOLUTIONLIST & SolutionList,
		   APPROXIMATIONLIST & ApproximationList,
		   REAL Eps, REAL LowerBound, REAL UpperBound);
VOID CleanUpLists (std::list<SOLUTIONLIST_ELEMENT> & SolutionList,
		   std::list<APPROX_ELEMENT> & ApproximationList,
		   REAL Eps, REAL LowerBound, REAL UpperBound);
VOID CleanUpLists (std::string ConfigFileName,
		   APPROXIMATIONLIST & ApproximationList,
		   REAL Eps, REAL LowerBound, REAL UpperBound);


VOID UpdateLowerBound (SOLUTIONLIST & SolutionList, REAL & LowerBound);
VOID UpdateLowerBound (std::list<SOLUTIONLIST_ELEMENT> & SolutionList, REAL & LowerBound);

#endif /* __UNCONSTOPT__ */

