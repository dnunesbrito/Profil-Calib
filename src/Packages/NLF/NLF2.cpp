/************************************************************************
 *
 * Implementation of Non-Linear Function Type
 * ------------------------------------------
 *
 * Copyright (C) 1997 Olaf Knueppel
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
 * $Id: NLF.C 478 2006-08-09 13:13:30Z keil $
 *
 ************************************************************************/

#include <NLF/NLF2.hpp>

//
// f:R^n -> R
//
FUNCTION2::FUNCTION2 (int n, std::function<EINTERVAL (CONST EINTERVAL_VECTOR& ,std::shared_ptr<VOID> )> f)
{
  nArg = n;
  nRes = 1;
  isnull = false;
  EIntervalImplementation = f;
}
FUNCTION2::FUNCTION2 (int n, std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& ,std::shared_ptr<VOID> userdata)> f)
{
  nArg = n;
  nRes = 1;
  isnull = false;
  AutoIntervalImplementation = f;
}

FUNCTION2::FUNCTION2 (int n,
                    std::function<AUTODIFF (CONST AUTODIFF& ,std::shared_ptr<VOID> userdata)> fReal,
                    std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& ,std::shared_ptr<VOID> userdata)> fInterval)
{
  nArg = n;
  nRes = 1;
  isnull = false;
  AutoRealImplementation     = fReal;
  AutoIntervalImplementation = fInterval;
}

FUNCTION2::FUNCTION2 (int n,
                    std::function<AUTODIFF (CONST AUTODIFF& ,std::shared_ptr<VOID> userdata)> fReal,
                    std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& ,std::shared_ptr<VOID> userdata)> fInterval,
                    std::function<VECTOR (CONST VECTOR& ,std::shared_ptr<VOID> userdata)> fGradient,
                    std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR& ,std::shared_ptr<VOID> userdata)> fIntervalGradient,
                    std::function<MATRIX (CONST VECTOR& ,std::shared_ptr<VOID> userdata)> fHessian,
                    std::function<INTERVAL_MATRIX (CONST INTERVAL_VECTOR& ,std::shared_ptr<VOID> userdata)> fIntervalHessian)
{
  nArg = n;
  nRes = 1;
  isnull = false;
  RealImplementation             = fReal;
  IntervalImplementation         = fInterval;
  RealGradientImplementation     = fGradient;
  IntervalGradientImplementation = fIntervalGradient;
  RealHessianImplementation      = fHessian;
  IntervalHessianImplementation  = fIntervalHessian;
}

FUNCTION2::FUNCTION2 (int n,
                    std::function<AUTODIFF (CONST AUTODIFF& ,std::shared_ptr<VOID> userdata)> fAutoReal,
                    std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& ,std::shared_ptr<VOID> userdata)> fAutoInterval,
                    std::function<REAL (CONST VECTOR& ,std::shared_ptr<VOID> userdata)> fReal,
                    std::function<INTERVAL (CONST INTERVAL_VECTOR& ,std::shared_ptr<VOID> userdata)> fInterval,
                    std::function<VECTOR (CONST VECTOR& ,std::shared_ptr<VOID> userdata)> fGradient,
                    std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR& ,std::shared_ptr<VOID> userdata)> fIntervalGradient,
                    std::function<MATRIX (CONST VECTOR& ,std::shared_ptr<VOID> userdata)> fHessian,
                    std::function<INTERVAL_MATRIX (CONST INTERVAL_VECTOR& ,std::shared_ptr<VOID> userdata)> fIntervalHessian)
{
  nArg = n;
  nRes = 1;
  isnull = false;
  AutoRealImplementation         = fAutoReal;
  AutoIntervalImplementation     = fAutoInterval;
  RealImplementation             = fReal;
  IntervalImplementation         = fInterval;
  RealGradientImplementation     = fGradient;
  IntervalGradientImplementation = fIntervalGradient;
  RealHessianImplementation      = fHessian;
  IntervalHessianImplementation  = fIntervalHessian;
}
FUNCTION2::FUNCTION2 (int n,
                    std::function<AUTODIFF (CONST AUTODIFF& ,std::shared_ptr<VOID> userdata)> fAutoReal,
                    std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& ,std::shared_ptr<VOID> userdata)> fAutoInterval,
                    std::function<REAL (CONST VECTOR& ,std::shared_ptr<VOID> userdata)> fReal,
                    std::function<INTERVAL (CONST INTERVAL_VECTOR& ,std::shared_ptr<VOID> userdata)> fInterval,
                    std::function<VECTOR (CONST VECTOR& ,std::shared_ptr<VOID> userdata)> fGradient,
                    std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR& ,std::shared_ptr<VOID> userdata)> fIntervalGradient,
                    std::function<MATRIX (CONST VECTOR& ,std::shared_ptr<VOID> userdata)> fHessian,
                    std::function<INTERVAL_MATRIX (CONST INTERVAL_VECTOR& ,std::shared_ptr<VOID> userdata)> fIntervalHessian,
                    std::function<EINTERVAL (CONST EINTERVAL_VECTOR& ,std::shared_ptr<VOID> userdata) > fEIntervalImplementation)
{
  nArg = n;
  nRes = 1;
  isnull = false;
  AutoRealImplementation         = fAutoReal;
  AutoIntervalImplementation     = fAutoInterval;
  RealImplementation             = fReal;
  IntervalImplementation         = fInterval;
  RealGradientImplementation     = fGradient;
  IntervalGradientImplementation = fIntervalGradient;
  RealHessianImplementation      = fHessian;
  IntervalHessianImplementation  = fIntervalHessian;
  EIntervalImplementation        = fEIntervalImplementation;
}

REAL Function (FUNCTION2 & f, CONST VECTOR & x,  std::shared_ptr<VOID> userdata)
{
  f.RealFunctionCalls++;

  if (f.RealImplementation)
    return f.RealImplementation (x,userdata);
  else if (f.IntervalImplementation)
    return Mid (f.IntervalImplementation (Hull (x),userdata));
  else if (f.AutoRealImplementation) {
    AUTODIFF xAuto(x, FALSE);
    return FunctionValue (f.AutoRealImplementation (xAuto,userdata));
  }
  else if (f.AutoIntervalImplementation) {
    INTERVAL_AUTODIFF xAuto(Hull (x), FALSE);
    return Mid (FunctionValue (f.AutoIntervalImplementation (xAuto,userdata)));
  }
  else FatalError ("No Real Function Implementation Available.");
  return 0.0;
}

INTERVAL Function (FUNCTION2 & f, CONST INTERVAL_VECTOR & x,  std::shared_ptr<VOID> userdata)
{
  f.IntervalFunctionCalls++;

  if (f.IntervalImplementation)
    return f.IntervalImplementation (x,userdata);
  else if (f.AutoIntervalImplementation) {
    INTERVAL_AUTODIFF xAuto(x, FALSE);
    return FunctionValue (f.AutoIntervalImplementation (xAuto,userdata));
  }
  else FatalError ("No Interval Function Implementation Available.");
  return INTERVAL (0.0);
}

EINTERVAL Function (FUNCTION2 & f, CONST EINTERVAL_VECTOR & X,  std::shared_ptr<VOID> userdata)
{
    if (f.EIntervalImplementation)
        return f.EIntervalImplementation (X,userdata);
    else FatalError ("No EInterval Function Implementation Available.");
    return INTERVAL (0.0);
}
EINTERVAL BFunction_HC(FUNCTION2 & f, 
        CONST INTERVAL f_bar,
        EINTERVAL_VECTOR & x,
        std::shared_ptr<VOID> userdata,
        MATRIX B){
    f.IntervalFunctionCalls++;
    if(f.HCBEIntervalImplementation )
        return f.HCBEIntervalImplementation(f_bar,x,userdata,B);
    else FatalError ("No Interval function HC Implementation Available.");
    return EINTERVAL(1);
}


VECTOR Gradient (FUNCTION2 & f, CONST VECTOR & x,  std::shared_ptr<VOID> userdata)
{
  f.RealGradientCalls++;

  if (f.RealGradientImplementation)
    return f.RealGradientImplementation (x,userdata);
  else if (f.IntervalGradientImplementation)
    return Mid (f.IntervalGradientImplementation (Hull (x),userdata));
  else if (f.AutoRealImplementation) {
    AUTODIFF xAuto(x, FALSE);
    return GradientValue (f.AutoRealImplementation (xAuto,userdata));
  }
  else if (f.AutoIntervalImplementation) {
    INTERVAL_AUTODIFF xAuto(Hull (x), FALSE);
    return Mid (GradientValue (f.AutoIntervalImplementation (xAuto,userdata)));
  }
  else FatalError ("No Real Gradient Implementation Available.");
  return VECTOR (1);
}

INTERVAL_VECTOR Gradient (FUNCTION2 & f, CONST INTERVAL_VECTOR & x,  std::shared_ptr<VOID> userdata)
{
  f.IntervalGradientCalls++;

  if (f.IntervalGradientImplementation)
    return f.IntervalGradientImplementation (x,userdata);
  else if (f.AutoIntervalImplementation) {
    INTERVAL_AUTODIFF xAuto(x, FALSE);
    return GradientValue (f.AutoIntervalImplementation (xAuto,userdata));
  }
  else FatalError ("No Interval Gradient Implementation Available.");
  return INTERVAL_VECTOR (1);
}

MATRIX Hessian (FUNCTION2 & f, CONST VECTOR & x,  std::shared_ptr<VOID> userdata)
{
  f.RealHessianCalls++;

  if (f.nRes != 1)
    FatalError ("Index for Hessian component needed");

  if (f.RealHessianImplementation)
    return f.RealHessianImplementation (x,userdata);
  else if (f.IntervalHessianImplementation)
    return Mid (f.IntervalHessianImplementation (Hull (x),userdata));
  else if (f.AutoRealImplementation) {
    AUTODIFF xAuto(x, TRUE);
    return HessianValue (f.AutoRealImplementation (xAuto,userdata));
  }
  else if (f.AutoIntervalImplementation) {
    INTERVAL_AUTODIFF xAuto(Hull (x), TRUE);
    return Mid (HessianValue (f.AutoIntervalImplementation (xAuto,userdata)));
  }
  else FatalError ("No Real Hessian Implementation Available.");
  return MATRIX (1, 1);
}

INTERVAL_MATRIX Hessian (FUNCTION2 & f, CONST INTERVAL_VECTOR & x,  std::shared_ptr<VOID> userdata)
{
  f.IntervalHessianCalls++;

  if (f.nRes != 1)
    FatalError ("Index for Hessian component needed");

  if (f.IntervalHessianImplementation)
    return f.IntervalHessianImplementation (x,userdata);
  else if (f.AutoIntervalImplementation) {
    INTERVAL_AUTODIFF xAuto(x, TRUE);
    return HessianValue (f.AutoIntervalImplementation (xAuto,userdata));
  }
  else FatalError ("No Interval Hessian Implementation Available.");
  return INTERVAL_MATRIX (1, 1);
}

//
// f:R^n -> R^m
//
FUNCTION2::FUNCTION2(int n, int m){
    nArg = n;
    nRes = m;
}
FUNCTION2::FUNCTION2 (int n, int m,
                    std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& ,INT i,  std::shared_ptr<VOID> userdata)> f)
{
  nArg = n;
  nRes = m;
  AutoIntervalVectorImplementation = f;
}

FUNCTION2::FUNCTION2 (int n, int m,
                    std::function<AUTODIFF (CONST AUTODIFF& , INT i,  std::shared_ptr<VOID> userdata)> fReal,
                    std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& ,INT i,  std::shared_ptr<VOID> userdata)> fInterval)
{
  nArg = n;
  nRes = m;
  AutoRealVectorImplementation     = fReal;
  AutoIntervalVectorImplementation = fInterval;
}

FUNCTION2::FUNCTION2 (int n, int m,
                    std::function<VECTOR (CONST VECTOR& ,  std::shared_ptr<VOID>)> fReal,
                    std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR& ,  std::shared_ptr<VOID>)> fInterval,
                    std::function<VECTOR (CONST VECTOR& ,INT n,  std::shared_ptr<VOID>)> fGradient,
                    std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR& ,INT i,  std::shared_ptr<VOID>)> fIntervalGradient,
                    std::function<MATRIX (CONST VECTOR &, INT i,  std::shared_ptr<VOID>)> fHessian,
                    std::function<INTERVAL_MATRIX (CONST INTERVAL_VECTOR &, INT i,  std::shared_ptr<VOID>) > fIntervalHessian)
{
  nArg = n;
  nRes = m;
  RealVectorImplementation             = fReal;
  IntervalVectorImplementation         = fInterval;
  RealVectorGradientImplementation     = fGradient;
  IntervalVectorGradientImplementation = fIntervalGradient;
  RealVectorHessianImplementation      = fHessian;
  IntervalVectorHessianImplementation  = fIntervalHessian;
}

FUNCTION2::FUNCTION2 (int n, int m,
                    std::function<AUTODIFF (CONST AUTODIFF &, int i,  std::shared_ptr<VOID>)> fAutoReal,
                    std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF &, int i,  std::shared_ptr<VOID>)> fAutoInterval ,
                    std::function<VECTOR (CONST VECTOR &,  std::shared_ptr<VOID>)> fReal,
                    std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR &,  std::shared_ptr<VOID>)> fInterval,
                    std::function<VECTOR (CONST VECTOR &, int n,  std::shared_ptr<VOID>)> fGradient,
                    std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR &, int i,  std::shared_ptr<VOID>)> fIntervalGradient,
                    std::function<MATRIX (CONST VECTOR &, int i,  std::shared_ptr<VOID>)> fHessian,
                    std::function<INTERVAL_MATRIX (CONST INTERVAL_VECTOR &, int i,  std::shared_ptr<VOID>)> fIntervalHessian)
{
  nArg = n;
  nRes = m;
  AutoRealVectorImplementation         = fAutoReal;
  AutoIntervalVectorImplementation     = fAutoInterval;
  RealVectorImplementation             = fReal;
  IntervalVectorImplementation         = fInterval;
  RealVectorGradientImplementation     = fGradient;
  IntervalVectorGradientImplementation = fIntervalGradient;
  RealVectorHessianImplementation      = fHessian;
  IntervalVectorHessianImplementation  = fIntervalHessian;
}

FUNCTION2::FUNCTION2 (int n, int m,
                    std::function<INTERVAL_AUTODIFF(CONST INTERVAL_AUTODIFF&,INT i,std::shared_ptr<VOID> )> fAutoInterval,
                    std::function<EINTERVAL_VECTOR (CONST EINTERVAL_VECTOR &,std::shared_ptr<VOID>) > EIntervalVector,
                    std::function<EINTERVAL_VECTOR (CONST INTERVAL f_bar,EINTERVAL_VECTOR &,INT i,std::shared_ptr<VOID>) > HCEIntervalVector,
                    std::function<EINTERVAL_VECTOR (CONST EINTERVAL_VECTOR &,std::shared_ptr<VOID>,CONST MATRIX B) > BEIntervalVector,
                    std::function<EINTERVAL_VECTOR (CONST INTERVAL f_bar, EINTERVAL_VECTOR &,INT i,std::shared_ptr<VOID>,CONST MATRIX B) > HCBEIntervalVector,
                    std::function<EINTERVAL_VECTOR (CONST EINTERVAL_VECTOR& ,INT i,std::shared_ptr<VOID>,CONST MATRIX B) > BEIntervalVectorGrd,
                    std::function<EINTERVAL_VECTOR (CONST INTERVAL f_bar, EINTERVAL_VECTOR& ,INT i,std::shared_ptr<VOID>,CONST MATRIX B) > HCBEIntervalVectorGrd){
    nArg = n;
    nRes = m;
    AutoIntervalVectorImplementation    = fAutoInterval;
    EIntervalVectorImplementation       = EIntervalVector;
    HCEIntervalVectorImplementation     = HCEIntervalVector;
    BEIntervalVectorImplementation      = BEIntervalVector;
    HCBEIntervalVectorImplementation    = HCBEIntervalVector;
    BEIntervalVectorGrdImplementation   = BEIntervalVectorGrd;
    HCBEIntervalVectorGrdImplementation = HCBEIntervalVectorGrd;
}


VECTOR VectorFunction (FUNCTION2 & f, CONST VECTOR & x,  std::shared_ptr<VOID> userdata)
{
  f.RealFunctionCalls++;

  if (f.RealVectorImplementation)
    return f.RealVectorImplementation (x,userdata);
  else if (f.IntervalVectorImplementation)
    return Mid (f.IntervalVectorImplementation (Hull (x),userdata));
  else if (f.AutoRealVectorImplementation) {
    AUTODIFF xAuto(x, FALSE);
    VECTOR y(f.nRes);
    for (int i = 1; i <= f.nRes; i++)
      y(i) = FunctionValue (f.AutoRealVectorImplementation (xAuto, i,userdata));
    return y;
  }
  else if (f.AutoIntervalVectorImplementation) {
    INTERVAL_AUTODIFF xAuto(Hull (x), FALSE);
    VECTOR y(f.nRes);
    for (int i = 1; i <= f.nRes; i++)
      y(i) = Mid (FunctionValue (f.AutoIntervalVectorImplementation (xAuto, i,userdata)));
    return y;
  }
  else FatalError ("No Real Vector Function Implementation Available.");
  return VECTOR (1);
}

INTERVAL_VECTOR VectorFunction (FUNCTION2 & f, CONST INTERVAL_VECTOR & x,  std::shared_ptr<VOID> userdata)
{
  f.IntervalFunctionCalls++;

  if (f.IntervalVectorImplementation)
    return f.IntervalVectorImplementation (x,userdata);
  else if (f.AutoIntervalVectorImplementation) {
    INTERVAL_AUTODIFF xAuto(x, FALSE);
    INTERVAL_VECTOR y(f.nRes);
    for (int i = 1; i <= f.nRes; i++)
      y(i) = FunctionValue (f.AutoIntervalVectorImplementation (xAuto, i,userdata));
    return y;
  }
  else FatalError ("No Interval Vector Function Implementation Available.");
  return INTERVAL_VECTOR (1);
}

EINTERVAL_VECTOR VectorFunction (FUNCTION2 & f, CONST EINTERVAL_VECTOR & x,  std::shared_ptr<VOID> userdata)
{
    f.IntervalFunctionCalls++;

    if (f.EIntervalVectorImplementation)
        return f.EIntervalVectorImplementation (x,userdata);
    if (f.IntervalVectorImplementation)
        return f.IntervalVectorImplementation(x.getIV(1),userdata);
    else FatalError ("No Extended Interval Vector Function Implementation Available.");
    return EINTERVAL_VECTOR (1);
}
INTERVAL_VECTOR VectorFunction (FUNCTION2 & f, CONST INTERVAL_VECTOR & x,  std::shared_ptr<VOID> userdata, CONST MATRIX& B)
{
    f.IntervalFunctionCalls++;

    if (f.BIntervalVectorImplementation)
        return f.BIntervalVectorImplementation (x,userdata,B);
    else FatalError ("No Extended Interval Vector Function Implementation Available.");
    return INTERVAL_VECTOR (1);
}

EINTERVAL_VECTOR EVectorFunction (FUNCTION2 & f, CONST EINTERVAL_VECTOR & x,  std::shared_ptr<VOID> userdata, CONST MATRIX B)
{
    f.IntervalFunctionCalls++;

    if (f.BEIntervalVectorImplementation)
        return f.BEIntervalVectorImplementation (x,userdata,B);
    else FatalError ("No Extended Interval Vector Function Implementation Available.");
    return EINTERVAL_VECTOR (1);
}

VECTOR Gradient (FUNCTION2 & f, CONST VECTOR & x, int n,  std::shared_ptr<VOID> userdata)
{
  f.RealGradientCalls++;

  if (f.RealVectorGradientImplementation)
    return f.RealVectorGradientImplementation (x, n,userdata);
  else if (f.IntervalVectorGradientImplementation)
    return Mid (f.IntervalVectorGradientImplementation (Hull (x), n,userdata));
  else if (f.AutoRealVectorImplementation) {
    AUTODIFF xAuto(x, FALSE);
    return GradientValue (f.AutoRealVectorImplementation (xAuto, n,userdata));
  }
  else if (f.AutoIntervalVectorImplementation) {
    INTERVAL_AUTODIFF xAuto(Hull (x), FALSE);
    return Mid (GradientValue (f.AutoIntervalVectorImplementation (xAuto, n,userdata)));
  }
  else FatalError ("No Real Gradient Implementation Available.");
  return VECTOR (1);
}

INTERVAL_VECTOR Gradient (FUNCTION2 & f, CONST INTERVAL_VECTOR & x, int n,  std::shared_ptr<VOID> userdata)
{
  f.IntervalGradientCalls++;

  if (f.IntervalVectorGradientImplementation)
    return f.IntervalVectorGradientImplementation (x, n,userdata);
  else if (f.AutoIntervalVectorImplementation) {
    INTERVAL_AUTODIFF xAuto(x, FALSE);
    return GradientValue (f.AutoIntervalVectorImplementation (xAuto, n,userdata));
  }
  else FatalError ("No Interval Gradient vector Implementation Available.");
  return INTERVAL_VECTOR (1);
}

INTERVAL_VECTOR Gradient (FUNCTION2 & f, CONST INTERVAL_VECTOR & x, int n,  std::shared_ptr<VOID> userdata,CONST MATRIX B)
{
  f.IntervalGradientCalls++;

  if (f.BIntervalVectorGradientImplementation)
    return f.BIntervalVectorGradientImplementation (x, n,userdata,B);
  else FatalError ("No Interval Gradient vector with B Implementation Available.");
  return INTERVAL_VECTOR (1);
}

EINTERVAL_VECTOR Gradient (FUNCTION2 & f, CONST EINTERVAL_VECTOR & x, int n,  std::shared_ptr<VOID> userdata)
{
  f.IntervalGradientCalls++;

  if (f.EIntervalVectorGradientImplementation)
    return f.EIntervalVectorGradientImplementation (x, n,userdata);
  else if (f.AutoIntervalVectorImplementation) {
        vector<INTERVAL_VECTOR> Xl;
        Parse(Xl,x);
        INTERVAL_AUTODIFF X(Xl[0]);
        INTERVAL_AUTODIFF xAuto(X, FALSE);
    return GradientValue (f.AutoIntervalVectorImplementation (xAuto, n,userdata));
  }
  else FatalError ("No EInterval Gradient vector Implementation Available.");
  return EINTERVAL_VECTOR (1);
}

MATRIX Jacobian (FUNCTION2 & f, CONST VECTOR & x,  std::shared_ptr<VOID> userdata)
{
  if (f.nRes != f.nArg)
    FatalError ("Jacobian only defined for f:R^n->R^n.");
  MATRIX y(f.nRes, f.nRes);
  for (int i = 1; i <= f.nArg; i++)
    SetRow (y, i, Gradient (f, x, i,userdata));
  return y;
}

EINTERVAL_MATRIX Jacobian (FUNCTION2 & f, CONST EINTERVAL_VECTOR & x,  std::shared_ptr<VOID> userdata)
{
  if (f.nRes != f.nArg)
    FatalError ("Jacobian only defined for f:R^n->R^n.");
  EINTERVAL_MATRIX y(f.nRes, f.nRes);
  for (int i = 1; i <= f.nArg; i++)
      y.setrow(i,Gradient(f, x, i,userdata));
    //SetRow (y, i, Gradient );
  return y;
}

INTERVAL_MATRIX Jacobian (FUNCTION2 & f, CONST INTERVAL_VECTOR & x,  std::shared_ptr<VOID> userdata)
{
  if (f.nRes != f.nArg)
    FatalError ("Jacobian only defined for f:R^n->R^n.");
  INTERVAL_MATRIX y(f.nRes, f.nRes);
  for (int i = 1; i <= f.nArg; i++)
    SetRow (y, i, Gradient (f, x, i,userdata));
  return y;
}

MATRIX Hessian (FUNCTION2 & f, CONST VECTOR & x, int n,  std::shared_ptr<VOID> userdata)
{
  f.RealHessianCalls++;

  if (f.RealVectorHessianImplementation)
    return f.RealVectorHessianImplementation (x, n,userdata);
  else if (f.IntervalVectorHessianImplementation)
    return Mid (f.IntervalVectorHessianImplementation (Hull (x), n,userdata));
  else if (f.AutoRealVectorImplementation) {
    AUTODIFF xAuto(x, TRUE);
    return HessianValue (f.AutoRealVectorImplementation (xAuto, n,userdata));
  }
  else if (f.AutoIntervalVectorImplementation) {
    INTERVAL_AUTODIFF xAuto(Hull (x), TRUE);
    return Mid (HessianValue (f.AutoIntervalVectorImplementation (xAuto, n,userdata)));
  }
  else FatalError ("No Real Hessian Implementation Available.");
  return MATRIX (1, 1);
}

INTERVAL_MATRIX Hessian (FUNCTION2 & f, CONST INTERVAL_VECTOR & x, int n,  std::shared_ptr<VOID> userdata)
{
  f.IntervalHessianCalls++;

  if (f.IntervalVectorHessianImplementation)
    return f.IntervalVectorHessianImplementation (x, n,userdata);
  else if (f.AutoIntervalVectorImplementation) {
    INTERVAL_AUTODIFF xAuto(x, TRUE);
    return HessianValue (f.AutoIntervalVectorImplementation (xAuto, n,userdata));
  }
  else FatalError ("No Interval Hessian Implementation Available.");
  return INTERVAL_MATRIX (1, 1);
}
EINTERVAL_VECTOR Function_HC(FUNCTION2 & f, CONST INTERVAL f_bar,EINTERVAL_VECTOR & x,INT i,std::shared_ptr<VOID> userdata){
    f.IntervalFunctionCalls++;
    if(f.HCEIntervalVectorImplementation )
        return f.HCEIntervalVectorImplementation(f_bar,x,i,userdata);
    else FatalError ("No Interval function HC Implementation Available.");
    return EINTERVAL_VECTOR(1);
}
EINTERVAL_VECTOR BFunction_HC(FUNCTION2 & f, 
        CONST INTERVAL f_bar,
        EINTERVAL_VECTOR & x,
        INT i,
        std::shared_ptr<VOID> userdata,
        MATRIX B){
    f.IntervalFunctionCalls++;
    if(f.HCBEIntervalVectorImplementation )
        return f.HCBEIntervalVectorImplementation(f_bar,x,i,userdata,B);
    else FatalError ("No Interval vector function HC Implementation Available.");
    return EINTERVAL_VECTOR(1);
}
EINTERVAL Function_HC(FUNCTION2 & f, CONST INTERVAL f_bar,EINTERVAL_VECTOR & x,std::shared_ptr<VOID> userdata){
    f.IntervalFunctionCalls++;
    if(f.HCEIntervaImplementation )
        return f.HCEIntervaImplementation(f_bar,x,userdata);
    else FatalError ("No Interval function HC Implementation Available.");
    return EINTERVAL(1);
}
EINTERVAL_MATRIX Hessian_HC(FUNCTION2 & f, CONST INTERVAL f_bar,EINTERVAL_VECTOR & x,INT i,std::shared_ptr<VOID> userdata){
    f.IntervalFunctionCalls++;
    if(f.HCEIntervalHessianImplementation )
        return f.HCEIntervalHessianImplementation(f_bar,x,i,userdata);
    else FatalError ("No Interval function HC Implementation Available.");
    return EINTERVAL_MATRIX(1,1);
}
EINTERVAL_VECTOR Gradient_HC(FUNCTION2 & f, CONST INTERVAL f_bar,EINTERVAL_VECTOR & x,INT i,std::shared_ptr<VOID> userdata){
    f.IntervalFunctionCalls++;
    if(f.HCEIntervalVectorImplementation )
        return f.HCEIntervalVectorImplementation(f_bar,x,i,userdata);
    else FatalError ("No Interval function HC Implementation Available.");
    return EINTERVAL_VECTOR(1);
}
