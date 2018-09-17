/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <BIAS/BiasFExt.hpp>

REAL BiasPi, BiasTwoPi, BiasPiHalf, BiasPiQuarter;
REAL BiasE, BiasSqrt2, BiasInvSqrt2, BiasLn10;

static BIASINTERVAL BiasPiHalfIncl; /* enclosure of Pi/2  */
static BIASINTERVAL BiasLn10Incl;   /* enclosure of Ln 10 */

static BIASINTERVAL PlusMinusOne;   /* [-1,1] */


static REAL Zero     =  0.0;
static REAL MinusOne = -1.0;
static REAL PlusOne  =  1.0;
static REAL PlusTwo  =  2.0;

static REAL BiasStdFuncOnePlusEps;  /* (1.0 + n * Epsilon)          */
static REAL BiasStdFuncOneMinusEps; /* (1.0 - n * Epsilon)          */


#define RoundUp(x) \
	(((x < 0.0) ? BiasStdFuncOneMinusEps : BiasStdFuncOnePlusEps) * (x) \
	 + BiasEta)
#define RoundDown(x) \
	(((x < 0.0) ? BiasStdFuncOnePlusEps : BiasStdFuncOneMinusEps) * (x) \
	 - BiasEta)

/************************************************************************
 *  Implementation of global functions
 *************************************************************************/
/**********************************************************************
 *  Initialization
 */

VOID EBiasFuncInit (VOID){
    INT InvalidBits = __BIASSTDFUNCINVALIDBITS__;
    BIASINTERVAL tmp;

    BiasInit ();

    BiasPi         = 3.14159265358979323846;
    BiasTwoPi      = 6.28318530717958647693;
    BiasPiHalf     = 1.57079632679489661923;
    BiasPiQuarter  = 0.78539816339744830962;
    BiasE          = 2.7182818284590452354;
    BiasSqrt2      = 1.41421356237309504880;
    BiasInvSqrt2   = 0.70710678118654752440;
    BiasLn10       = 2.30258509299404568402;

    BiasHullR (& tmp, & BiasPiHalf);
    BiasSuccI (& BiasPiHalfIncl, & tmp);

    BiasHullR (& tmp, & BiasLn10);
    BiasSuccI (& BiasLn10Incl, & tmp);

    BiasHullRR (& PlusMinusOne, & MinusOne, & PlusOne);

    BiasRoundNear ();

    BiasStdFuncOnePlusEps  = 1.0 + (1 << (InvalidBits + 1)) * BiasEpsilon;
    BiasStdFuncOneMinusEps = 1.0 - (1 << (InvalidBits + 1)) * BiasEpsilon;
}


/**********************************************************************
   R = { |x| : x in X }
***********************************************************************/
VOID EBiasIAbs (BIASINTERVAL * const pR,const BIASINTERVAL * const pX){
    REAL t;

    if (BiasInf (pX) > 0.0) *pR = *pX;
    else if (BiasSup (pX) < 0.0) BiasNeg (pR, pX);
    else {
            t = BiasAbs (pX);
            BiasHullRR (pR, & Zero, & t);
    }
}
/**********************************************************************
  R = X^2
***********************************************************************/
VOID EBiasSqr (BIASINTERVAL * const pR,const BIASINTERVAL * const pX)
{
    BIASINTERVAL t1;

    EBiasIAbs (& t1, pX);
    BiasMulII (pR, & t1, & t1);
}

VOID EBiasSqrt (BIASINTERVAL * const pR,const BIASINTERVAL * const pX)
/**********************************************************************
  R = Sqrt (X)
***********************************************************************/
{
    REAL y_inf, y_sup;

    if (BiasInf (pX) < 0.0)
            /*_BiasError ("Sqrt argument out of range");*/ BiasHullR (pR, & BiasNaN);
    else {
            y_inf = sqrt (BiasInf (pX));
            y_sup = sqrt (BiasSup (pX));
            y_inf = RoundDown (y_inf);
            y_sup = RoundUp   (y_sup);
            if (y_inf < 0.0) y_inf = 0.0;
            BiasHullRR (pR, & y_inf, & y_sup);
    }
}
