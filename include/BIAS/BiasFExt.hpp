/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BiasFExt.hpp
 * Author: darlan
 *
 * Created on 6 de Outubro de 2016, 12:29
 */

#ifndef BIASFEXT_HPP
#define BIASFEXT_HPP

#include <BIAS/Bias0.h>
#include <BIAS/BiasF.h>
#include <BIAS/BiasRnd.h>
#include <BIAS/Bias0Ext.hpp>
#include <math.h>

/**********************************************************************
  Initialization
***********************************************************************/
VOID EBiasFuncInit (VOID);
/**********************************************************************
   R = { |x| : x in X }
 **********************************************************************/
VOID EBiasIAbs (BIASINTERVAL * const pR,const BIASINTERVAL * const pX);
/**********************************************************************
   R = X^2
***********************************************************************/
VOID BiasSqr (BIASINTERVAL * const pR,const BIASINTERVAL * const pX);
/**********************************************************************
   R = Sqrt (X)
***********************************************************************/
VOID BiasSqrt (BIASINTERVAL * const pR,const BIASINTERVAL * const pX);

#endif /* BIASFEXT_HPP */

