/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bias0Ext.hpp
 * Author: darlan
 *
 * Created on 23 de Setembro de 2016, 13:10
 */

#ifndef BIAS0EXT_HPP
#define BIAS0EXT_HPP

#include <BIAS/Bias0.h>
#include <BIAS/BiasRnd.h>
#include <BIAS/BiasInt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/************************************************************************
 *  Definition of Constants, Types, and Variables
 ************************************************************************/

extern REAL     BiasEpsilon;            /* min {x >= 0 : 1 + x > 1}     */
extern REAL     BiasEta;                /* min {x > 0}                  */
extern REAL     BiasNaN;                /* NaN                          */
extern REAL     BiasPosInf;             /* +oo                          */
extern REAL     BiasNegInf;             /* -oo                          */


VOID EBiasAddRR (BIASINTERVAL * const pR,
		const REAL * const pa,
                const REAL * const pb);
VOID EBiasAddRI (BIASINTERVAL * const pR,
		const REAL * const pa,
                const BIASINTERVAL * const pB);
VOID EBiasAddII (BIASINTERVAL * const pR,
		const BIASINTERVAL * const pA, const BIASINTERVAL * const pB);
VOID EBiasSubRR (BIASINTERVAL * const pR,
		const REAL * const pa,
                const REAL * const pb);
VOID EBiasSubRI (BIASINTERVAL * const pR,
		const REAL * const pa,
                const BIASINTERVAL * const pB);
VOID EBiasSubIR (BIASINTERVAL * const pR,
		const BIASINTERVAL * const pA,
                const REAL * const pb);
VOID EBiasSubII (BIASINTERVAL * const pR,
		const BIASINTERVAL * const pA, const BIASINTERVAL * const pB);
VOID EBiasMulRR (BIASINTERVAL * const pR,
		const REAL * const pa, const REAL * const pb);
VOID EBiasMulRI (BIASINTERVAL * const pR,
		const REAL * const pa, const BIASINTERVAL * const pB);
VOID EBiasMulII (BIASINTERVAL * const pR,
		const BIASINTERVAL * const pA,
		const BIASINTERVAL * const pB);
VOID EBiasDivRR (BIASINTERVAL * const pR,
		const REAL * const pa, const REAL * const pb);
VOID EBiasDivRI (BIASINTERVAL * const pR1,BIASINTERVAL * const pR2,
		const REAL * const pa, const BIASINTERVAL * const pB);

VOID EBiasDivIR (BIASINTERVAL * const pR,
		const BIASINTERVAL * const pA, const REAL * const pb);
VOID EBiasDivII (BIASINTERVAL * const pR1,
                BIASINTERVAL * const pR2,
		const BIASINTERVAL * const pA,
		const BIASINTERVAL * const pB);
VOID EBiasMacII (BIASINTERVAL * const pR1,
                BIASINTERVAL * const pR2,
		const BIASINTERVAL * const pA,
		const BIASINTERVAL * const pB);
bool EBiasHasInfinity(BIASINTERVAL * const pR1);
bool EBiasPosInfinity(BIASINTERVAL * const pR1);
bool EBiasNegInfinity(BIASINTERVAL * const pR1);
#define EBiasInf(pA)     ((pA)->inf)
#define EBiasSup(pA)     ((pA)->sup)

#define EBiasAddIR(pR, pA, pb)    EBiasAddRI (pR, pb, pA)
#define EBiasMulIR(pR, pA, pb)    EBiasMulRI (pR, pb, pA)
#define EBiasMacIR(pR, pA, pb)    EBiasMacRI (pR, pb, pA)
#define EBiasDistIR(pA, pb)       EBiasDistRI (pb, pA)
#define EBiasHullIR(pR, pA, pb)   EBiasHullRI (pR, pb, pA)

#endif /* BIAS0EXT_HPP */

