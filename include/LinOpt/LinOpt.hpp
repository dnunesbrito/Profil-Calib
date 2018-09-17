/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LocalOpt.hpp
 * Author: darlan
 *
 * Created on 27 de Setembro de 2016, 12:29
 */

#ifndef LINOPT_HPP
#define LINOPT_HPP
#include <Utilities.h>
#include <AutoDiff/IntervalAutoDiff.h>
#include <functional>
#include "EINTERVAL.hpp"
#include "EINTERVALVECTOR.hpp"
#include "EINTERVAL_MATRIX.hpp"
#include <Vector.h>
#include <IntervalVector.h>
#include <Matrix.h>
#include <ctime>
#include <random>
#include <NLF/NLF.hpp>
#include <omp.h>
#include <Constants.h>
#include <Functions.h>
#include <GlobalOpt/UnconstrainedOpt.h>

#define IL_STD
#include <ilcplex/ilocplex.h>

ILOSTLBEGIN
enum STATUS {SINGULAR, REGULAR, UNDEFINED, STRONGSOLUTION, WEAKSOLUTION, SOLUTIONFOUNDED, SOLUTIONNOTFOUNDED, NOOPTIMAL, EMPTY,
            STRICTILYNEGATIVE, INFERIOR_EXPANSION, SUPERIOR_EXPANSION, HALF_DIVIDE, ACCEPT_X,
                    NOTEXPANDED, ALLXDELETED, EXPANDED, REDUCED, DEFAULTOPT, NLUNDEFINED,
                    UNLIMITED, OK, NOTREDUCED, IRREGULAR, ALLXCONTAINED, HASNOSOLUTION, R1R2TXTYNOTFOUND, FTZNOTFOUND};
using namespace std;
class LinOpt {
public:
    INTERVAL_MATRIX A;
    MATRIX Ac;
    INTERVAL_VECTOR B;
    VECTOR bc;
    INTERVAL_VECTOR X;
    INTERVAL_VECTOR WeakX;
    FUNCTION fcn;
    OPTMISET optmiset;
    STATUS status;
    LinOpt();
    LinOpt(CONST INTERVAL_MATRIX Ain,CONST INTERVAL_VECTOR Bin){
        A = Ain;
        B = Bin;
        rdim = Ain.rows();
        cdim = Ain.cols();
        Resize(X,cdim);
        Initialize(X,SymHull(Machine::PosInfinity));
    }
    LinOpt(CONST INTERVAL_MATRIX Ain,CONST INTERVAL_VECTOR Bin,CONST INTERVAL_VECTOR Xin){
        A = Ain;
        B = Bin;
        X = Xin;
        rdim = Ain.rows();
        cdim = Ain.cols();        
    }
    LinOpt(const LinOpt& orig);
    virtual ~LinOpt();
    INT RohnOverLinSys(INTERVAL_VECTOR& Xout);
    INT RohnOptimalLinSys( );
    INT NonSquarePrecondMatrix(MATRIX& M);
    INT HansenWalsterOverLinSys( );
    INT Oettli_Prager_Solvability(CONST MATRIX& Amais,CONST MATRIX& Amenos,INTERVAL_VECTOR& IVx);
    INT GaussElimination(INTERVAL_MATRIX& A_out,
        INTERVAL_VECTOR& B_out,
        INTERVAL_MATRIX& M);
    STATUS intervalhull(MATRIX& S);
    STATUS qzmatrix(CONST VECTOR& z,MATRIX& S,MATRIX& Qz);
    STATUS absvaleqn(CONST MATRIX& Al, CONST MATRIX Bl, CONST VECTOR& b,VECTOR& x,MATRIX& S);
private:
    INT rdim;
    INT cdim;
};
#endif /* LOCALOPT_HPP */

