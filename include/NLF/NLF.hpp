/************************************************************************
 *
 * Definition of Non-Linear Function Type
 * --------------------------------------
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
 * $Id: NLF.h 478 2006-08-09 13:13:30Z keil $
 *
 ************************************************************************/

#ifndef __NLF__
#define __NLF__

#include <IntervalMatrix.h>
#include <EINTERVAL.hpp>
#include <EINTERVALVECTOR.hpp>
#include <EINTERVAL_MATRIX.hpp>
#include <AutoDiff/IntervalAutoDiff.h>
#include <AutoDiff/AutoDiff.h>
#include <functional>

class FUNCTION {
private:
  int nArg;
  int nRes;
  bool isnull;
  /* f:R^n -> R */
  std::function<REAL (CONST VECTOR& )> RealImplementation;
  std::function<INTERVAL (CONST INTERVAL_VECTOR& )> IntervalImplementation;
  std::function<VECTOR (CONST VECTOR& )> RealGradientImplementation;
  std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR& )> IntervalGradientImplementation;
  std::function<MATRIX (CONST VECTOR& )> RealHessianImplementation;
  std::function<INTERVAL_MATRIX (CONST INTERVAL_VECTOR& )> IntervalHessianImplementation;
  std::function<AUTODIFF (CONST AUTODIFF& )> AutoRealImplementation;
  std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& )> AutoIntervalImplementation;
  std::function<EINTERVAL (CONST EINTERVAL_VECTOR& ) > EIntervalImplementation;

  /* f:R^n -> R^m */
  std::function<VECTOR (CONST VECTOR& )> RealVectorImplementation;
  std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR& )> IntervalVectorImplementation;
  std::function<VECTOR (CONST VECTOR& ,INT i)> RealVectorGradientImplementation;
  std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR& ,INT i)> IntervalVectorGradientImplementation;
  std::function<MATRIX (CONST VECTOR& ,INT i)> RealVectorHessianImplementation;
  std::function<INTERVAL_MATRIX (CONST INTERVAL_VECTOR& ,INT i)> IntervalVectorHessianImplementation;
  std::function<AUTODIFF (CONST AUTODIFF& , INT i)> AutoRealVectorImplementation;
  std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& ,INT i)> AutoIntervalVectorImplementation;

  /* misc. */
public:
  FUNCTION (){isnull = true;};
  /* Constructors for f:R^n -> R */
  FUNCTION (int n, std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& )> f);
  FUNCTION (int n,
                    std::function<AUTODIFF (CONST AUTODIFF& )> fReal,
                    std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& )> fInterval);
  FUNCTION (int n,
                    std::function<AUTODIFF (CONST AUTODIFF& )> fReal,
                    std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& )> fInterval,
                    std::function<VECTOR (CONST VECTOR& )> fGradient,
                    std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR& )> fIntervalGradient,
                    std::function<MATRIX (CONST VECTOR& )> fHessian,
                    std::function<INTERVAL_MATRIX (CONST INTERVAL_VECTOR& )> fIntervalHessian);
  FUNCTION (int n,
                    std::function<AUTODIFF (CONST AUTODIFF& )> fAutoReal,
                    std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& )> fAutoInterval,
                    std::function<REAL (CONST VECTOR& )> fReal,
                    std::function<INTERVAL (CONST INTERVAL_VECTOR& )> fInterval,
                    std::function<VECTOR (CONST VECTOR& )> fGradient,
                    std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR& )> fIntervalGradient,
                    std::function<MATRIX (CONST VECTOR& )> fHessian,
                    std::function<INTERVAL_MATRIX (CONST INTERVAL_VECTOR& )> fIntervalHessian);
  
  FUNCTION (int n,
                    std::function<AUTODIFF (CONST AUTODIFF& )> fAutoReal,
                    std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& )> fAutoInterval,
                    std::function<REAL (CONST VECTOR& )> fReal,
                    std::function<INTERVAL (CONST INTERVAL_VECTOR& )> fInterval,
                    std::function<VECTOR (CONST VECTOR& )> fGradient,
                    std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR& )> fIntervalGradient,
                    std::function<MATRIX (CONST VECTOR& )> fHessian,
                    std::function<INTERVAL_MATRIX (CONST INTERVAL_VECTOR& )> fIntervalHessian,
                    std::function<EINTERVAL (CONST EINTERVAL_VECTOR& ) > fEIntervalImplementation);
  /* Constructors for f:R^n -> R^m */
  FUNCTION (int n, int m,
                    std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& ,INT i)> f);
  FUNCTION (int n, int m,
                    std::function<AUTODIFF (CONST AUTODIFF& , INT i)> fReal,
                    std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& ,INT i)> fInterval);
  FUNCTION (int n, int m,
                    std::function<VECTOR (CONST VECTOR& )> fReal,
                    std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR& )> fInterval,
                    std::function<VECTOR (CONST VECTOR& ,INT n)> fGradient,
                    std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR& ,INT i)> fIntervalGradient,
                    std::function<MATRIX (CONST VECTOR &, INT i)> fHessian,
                    std::function<INTERVAL_MATRIX (CONST INTERVAL_VECTOR &, INT i) > fIntervalHessian);
  FUNCTION (int n, int m,
                    std::function<AUTODIFF (CONST AUTODIFF &, int i)> fAutoReal,
                    std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF &, int i)> fAutoInterval ,
                    std::function<VECTOR (CONST VECTOR &)> fReal,
                    std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR &)> fInterval,
                    std::function<VECTOR (CONST VECTOR &, int n)> fGradient,
                    std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR &, int i)> fIntervalGradient,
                    std::function<MATRIX (CONST VECTOR &, int i)> fHessian,
                    std::function<INTERVAL_MATRIX (CONST INTERVAL_VECTOR &, int i)> fIntervalHessian);
  /* Call Counters */
  int RealFunctionCalls, IntervalFunctionCalls;
  int RealGradientCalls, IntervalGradientCalls;
  int RealHessianCalls,  IntervalHessianCalls;

  /* misc. functions */
  int ArgumentDimension () { return nArg; }
  int ResultDimension () { return nRes; }
  bool isNULL(){
      return isnull;
  }
  friend REAL Function (FUNCTION & f, CONST VECTOR & x);
  friend INTERVAL Function (FUNCTION & f, CONST INTERVAL_VECTOR & x);
  friend EINTERVAL Function (FUNCTION & f, CONST EINTERVAL_VECTOR & X);
  friend VECTOR VectorFunction (FUNCTION & f, CONST VECTOR & x);
  friend INTERVAL_VECTOR VectorFunction (FUNCTION & f, CONST INTERVAL_VECTOR & x);
  friend VECTOR Gradient (FUNCTION & f, CONST VECTOR & x);
  friend INTERVAL_VECTOR Gradient (FUNCTION & f, CONST INTERVAL_VECTOR & x);
  friend VECTOR Gradient (FUNCTION & f, CONST VECTOR & x, int n);
  friend INTERVAL_VECTOR Gradient (FUNCTION & f, CONST INTERVAL_VECTOR & x, int n);
  friend MATRIX Jacobian (FUNCTION & f, CONST VECTOR & x);
  friend INTERVAL_MATRIX Jacobian (FUNCTION & f, CONST INTERVAL_VECTOR & x);
  friend MATRIX Hessian (FUNCTION & f, CONST VECTOR & x);
  friend INTERVAL_MATRIX Hessian (FUNCTION & f, CONST INTERVAL_VECTOR & x);
  friend MATRIX Hessian (FUNCTION & f, CONST VECTOR & x, int n);
  friend INTERVAL_MATRIX Hessian (FUNCTION & f, CONST INTERVAL_VECTOR & x, int n);
};
#undef NIL

#endif /* __NLF__ */
