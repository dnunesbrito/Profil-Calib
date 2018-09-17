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

#ifndef __NLF2__
#define __NLF2__

#include <IntervalMatrix.h>
#include <Matrix.h>
#include <EINTERVAL.hpp>
#include <EINTERVALVECTOR.hpp>
#include <EINTERVAL_MATRIX.hpp>
#include <AutoDiff/IntervalAutoDiff.h>
#include <AutoDiff/AutoDiff.h>
#include <functional>
#include <memory>
#include <Constants.h>

class FUNCTION2 {
private:
  int nArg;
  int nRes;
  bool isnull;
public:
  /* f:R^n -> R */
  std::function<double (CONST VECTOR& ,std::shared_ptr<VOID> )> RealImplementation;
  std::function<INTERVAL (CONST INTERVAL_VECTOR& ,std::shared_ptr<VOID> )> IntervalImplementation;
  std::function<VECTOR (CONST VECTOR& ,std::shared_ptr<VOID> )> RealGradientImplementation;
  std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR& ,std::shared_ptr<VOID> )> IntervalGradientImplementation;
  std::function<MATRIX (CONST VECTOR& ,std::shared_ptr<VOID> )> RealHessianImplementation;
  std::function<INTERVAL_MATRIX (CONST INTERVAL_VECTOR& ,std::shared_ptr<VOID> )> IntervalHessianImplementation;
  std::function<EINTERVAL_MATRIX (CONST INTERVAL f_bar,EINTERVAL_VECTOR& ,INT ,std::shared_ptr<VOID> )> HCEIntervalHessianImplementation;
  std::function<AUTODIFF (CONST AUTODIFF& ,std::shared_ptr<VOID> )> AutoRealImplementation;
  std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& ,std::shared_ptr<VOID> )> AutoIntervalImplementation;
  std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& ,std::shared_ptr<VOID>,CONST MATRIX B )> BAutoIntervalImplementation;
  std::function<EINTERVAL (CONST EINTERVAL_VECTOR& ,std::shared_ptr<VOID> ) > EIntervalImplementation;
  std::function<EINTERVAL (CONST INTERVAL f_bar,EINTERVAL_VECTOR& ,std::shared_ptr<VOID> ) > HCEIntervaImplementation;
  std::function<EINTERVAL (CONST EINTERVAL_VECTOR& ,std::shared_ptr<VOID>,CONST MATRIX B) > BEIntervalImplementation;
  std::function<EINTERVAL (CONST INTERVAL f_bar,EINTERVAL_VECTOR& ,std::shared_ptr<VOID>,CONST MATRIX B) > HCBEIntervalImplementation;
  std::function<EINTERVAL_VECTOR (CONST EINTERVAL_VECTOR& ,std::shared_ptr<VOID>,CONST MATRIX B) > BEIntervalGradientImplementation;
  std::function<EINTERVAL_VECTOR (CONST INTERVAL f_bar,EINTERVAL_VECTOR& ,std::shared_ptr<VOID>,CONST MATRIX B) > HCBEIntervalGradientImplementation;

  /* f:R^n -> R^m */
  std::function<VECTOR (CONST VECTOR& ,std::shared_ptr<VOID> )> RealVectorImplementation;
  std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR& ,std::shared_ptr<VOID> )> IntervalVectorImplementation;
  std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR& ,std::shared_ptr<VOID> ,CONST MATRIX& )> BIntervalVectorImplementation;
  std::function<VECTOR (CONST VECTOR& ,INT i,std::shared_ptr<VOID> )> RealVectorGradientImplementation;
  std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR& ,INT i,std::shared_ptr<VOID> )> IntervalVectorGradientImplementation;
  std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR& ,INT i,std::shared_ptr<VOID> ,CONST MATRIX& )> BIntervalVectorGradientImplementation;
  std::function<MATRIX (CONST VECTOR& ,INT i,std::shared_ptr<VOID> )> RealVectorHessianImplementation;
  std::function<INTERVAL_MATRIX (CONST INTERVAL_VECTOR& ,INT i,std::shared_ptr<VOID> )> IntervalVectorHessianImplementation;
  std::function<AUTODIFF (CONST AUTODIFF& , INT i,std::shared_ptr<VOID> )> AutoRealVectorImplementation;
  std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& ,INT i,std::shared_ptr<VOID> )> AutoIntervalVectorImplementation;
  std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& ,INT i,std::shared_ptr<VOID>,CONST MATRIX& )> BAutoIntervalVectorImplementation;
  std::function<EINTERVAL_VECTOR (CONST EINTERVAL_VECTOR& ,std::shared_ptr<VOID>) > EIntervalVectorImplementation;
  std::function<EINTERVAL_VECTOR (CONST EINTERVAL_VECTOR& ,INT i,std::shared_ptr<VOID> )> EIntervalVectorGradientImplementation;
  std::function<EINTERVAL_VECTOR (CONST INTERVAL f_bar,EINTERVAL_VECTOR& ,INT i,std::shared_ptr<VOID>) > HCEIntervalVectorImplementation;
  std::function<EINTERVAL_VECTOR (CONST EINTERVAL_VECTOR& ,std::shared_ptr<VOID>,CONST MATRIX B) > BEIntervalVectorImplementation;
  std::function<EINTERVAL_VECTOR (CONST INTERVAL f_bar,EINTERVAL_VECTOR& ,INT i,std::shared_ptr<VOID>,CONST MATRIX B) > HCBEIntervalVectorImplementation;
  std::function<EINTERVAL_VECTOR (CONST EINTERVAL_VECTOR& ,INT i,std::shared_ptr<VOID>,CONST MATRIX B) > BEIntervalVectorGrdImplementation;
  std::function<EINTERVAL_VECTOR (CONST INTERVAL f_bar,EINTERVAL_VECTOR& ,INT i,std::shared_ptr<VOID>,CONST MATRIX B) > HCBEIntervalVectorGrdImplementation;

  /* misc. */
public:
  FUNCTION2 (){isnull = true;};
  FUNCTION2 (FUNCTION2& orig){
        RealImplementation = orig.RealImplementation;
        IntervalImplementation = orig.IntervalImplementation;
        RealGradientImplementation = orig.RealGradientImplementation;
        IntervalGradientImplementation = orig.IntervalGradientImplementation;
        RealHessianImplementation = orig.RealHessianImplementation;
        IntervalHessianImplementation = orig.IntervalHessianImplementation;
        HCEIntervalHessianImplementation = orig.HCEIntervalHessianImplementation;
        AutoRealImplementation = orig.AutoRealImplementation;
        AutoIntervalImplementation = orig.AutoIntervalImplementation;
        BAutoIntervalImplementation = orig.BAutoIntervalImplementation;
        EIntervalImplementation = orig.EIntervalImplementation;
        HCEIntervaImplementation = orig.HCEIntervaImplementation;
        BEIntervalImplementation = orig.BEIntervalImplementation;
        HCBEIntervalImplementation = orig.HCBEIntervalImplementation;
        BEIntervalGradientImplementation = orig.BEIntervalGradientImplementation;
        HCBEIntervalGradientImplementation = orig.HCBEIntervalGradientImplementation;
  }
  /* Constructors for f:R^n -> R */
  FUNCTION2 (int n, std::function<EINTERVAL (CONST EINTERVAL_VECTOR& ,std::shared_ptr<VOID> )> f);
  FUNCTION2 (int n, std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& ,std::shared_ptr<VOID> )> f);
  FUNCTION2 (int n,
                    std::function<AUTODIFF (CONST AUTODIFF& ,std::shared_ptr<VOID> )> fReal,
                    std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& ,std::shared_ptr<VOID> )> fInterval);
  FUNCTION2 (int n,
                    std::function<AUTODIFF (CONST AUTODIFF& ,std::shared_ptr<VOID> )> fReal,
                    std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& ,std::shared_ptr<VOID> )> fInterval,
                    std::function<VECTOR (CONST VECTOR& ,std::shared_ptr<VOID> )> fGradient,
                    std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR& ,std::shared_ptr<VOID> )> fIntervalGradient,
                    std::function<MATRIX (CONST VECTOR& ,std::shared_ptr<VOID> )> fHessian,
                    std::function<INTERVAL_MATRIX (CONST INTERVAL_VECTOR& ,std::shared_ptr<VOID> )> fIntervalHessian);
  FUNCTION2 (int n,
                    std::function<AUTODIFF (CONST AUTODIFF& ,std::shared_ptr<VOID> )> fAutoReal,
                    std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& ,std::shared_ptr<VOID> )> fAutoInterval,
                    std::function<double (CONST VECTOR& ,std::shared_ptr<VOID> )> fReal,
                    std::function<INTERVAL (CONST INTERVAL_VECTOR& ,std::shared_ptr<VOID> )> fInterval,
                    std::function<VECTOR (CONST VECTOR& ,std::shared_ptr<VOID> )> fGradient,
                    std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR& ,std::shared_ptr<VOID> )> fIntervalGradient,
                    std::function<MATRIX (CONST VECTOR& ,std::shared_ptr<VOID> )> fHessian,
                    std::function<INTERVAL_MATRIX (CONST INTERVAL_VECTOR& ,std::shared_ptr<VOID> )> fIntervalHessian);
  
  FUNCTION2 (int n,
                    std::function<AUTODIFF (CONST AUTODIFF& ,std::shared_ptr<VOID> )> fAutoReal,
                    std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& ,std::shared_ptr<VOID> )> fAutoInterval,
                    std::function<double (CONST VECTOR& ,std::shared_ptr<VOID> )> fReal,
                    std::function<INTERVAL (CONST INTERVAL_VECTOR& ,std::shared_ptr<VOID> )> fInterval,
                    std::function<VECTOR (CONST VECTOR& ,std::shared_ptr<VOID> )> fGradient,
                    std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR& ,std::shared_ptr<VOID> )> fIntervalGradient,
                    std::function<MATRIX (CONST VECTOR& ,std::shared_ptr<VOID> )> fHessian,
                    std::function<INTERVAL_MATRIX (CONST INTERVAL_VECTOR& ,std::shared_ptr<VOID> )> fIntervalHessian,
                    std::function<EINTERVAL (CONST EINTERVAL_VECTOR& ,std::shared_ptr<VOID> ) > fEIntervalImplementation);
  FUNCTION2 (int n,
                    std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& ,std::shared_ptr<VOID> )> fAutoInterval,
                    std::function<double (CONST VECTOR& ,std::shared_ptr<VOID> )> fReal,
                    std::function<INTERVAL (CONST INTERVAL_VECTOR& ,std::shared_ptr<VOID> )> fInterval,
                    std::function<VECTOR (CONST VECTOR& ,std::shared_ptr<VOID> )> fGradient,
                    std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR& ,std::shared_ptr<VOID> )> fIntervalGradient,
                    std::function<MATRIX (CONST VECTOR& ,std::shared_ptr<VOID> )> fHessian,
                    std::function<INTERVAL_MATRIX (CONST INTERVAL_VECTOR& ,std::shared_ptr<VOID> )> fIntervalHessian,
                    std::function<EINTERVAL (CONST EINTERVAL_VECTOR& ,std::shared_ptr<VOID> ) > fEIntervalImplementation);
  FUNCTION2 (int n,
                    std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& ,std::shared_ptr<VOID> )> fAutoInterval,
                    std::function<EINTERVAL (CONST EINTERVAL_VECTOR& ,std::shared_ptr<VOID> ) > fEIntervalImplementation);

  FUNCTION2 (int n,
                    std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& ,std::shared_ptr<VOID> )> fAutoInterval,
                    std::function<EINTERVAL (CONST EINTERVAL_VECTOR& ,std::shared_ptr<VOID> ) > fEIntervalImplementation,
                    std::function<EINTERVAL (CONST EINTERVAL_VECTOR& ,std::shared_ptr<VOID> ) > HCEIntervaImplementation,
                    std::function<EINTERVAL (CONST EINTERVAL_VECTOR& ,std::shared_ptr<VOID>,MATRIX B) > BEIntervalImplementation,
                    std::function<EINTERVAL (CONST EINTERVAL_VECTOR& ,std::shared_ptr<VOID>,MATRIX B) > HCBEIntervalImplementation);
  
  /* Constructors for f:R^n -> R^m */
  FUNCTION2 (int n, int m);
  FUNCTION2 (int n, int m,
                    std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& ,INT i,std::shared_ptr<VOID> )> f);
  FUNCTION2 (int n, int m,
                    std::function<AUTODIFF (CONST AUTODIFF& , INT i,std::shared_ptr<VOID> )> fReal,
                    std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF& ,INT i,std::shared_ptr<VOID> )> fInterval);
  FUNCTION2 (int n, int m,
                    std::function<VECTOR (CONST VECTOR& ,std::shared_ptr<VOID> )> fReal,
                    std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR& ,std::shared_ptr<VOID> )> fInterval,
                    std::function<VECTOR (CONST VECTOR& ,INT n,std::shared_ptr<VOID> )> fGradient,
                    std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR& ,INT i,std::shared_ptr<VOID> )> fIntervalGradient,
                    std::function<MATRIX (CONST VECTOR &, INT i,std::shared_ptr<VOID> )> fHessian,
                    std::function<INTERVAL_MATRIX (CONST INTERVAL_VECTOR &, INT i,std::shared_ptr<VOID> ) > fIntervalHessian);
  FUNCTION2 (int n, int m,
                    std::function<AUTODIFF (CONST AUTODIFF &, int i,std::shared_ptr<VOID> )> fAutoReal,
                    std::function<INTERVAL_AUTODIFF (CONST INTERVAL_AUTODIFF &, int i,std::shared_ptr<VOID> )> fAutoInterval ,
                    std::function<VECTOR (CONST VECTOR &,std::shared_ptr<VOID> )> fReal,
                    std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR &,std::shared_ptr<VOID> )> fInterval,
                    std::function<VECTOR (CONST VECTOR &, int n,std::shared_ptr<VOID> )> fGradient,
                    std::function<INTERVAL_VECTOR (CONST INTERVAL_VECTOR &, int i,std::shared_ptr<VOID> )> fIntervalGradient,
                    std::function<MATRIX (CONST VECTOR &, int i,std::shared_ptr<VOID> )> fHessian,
                    std::function<INTERVAL_MATRIX (CONST INTERVAL_VECTOR &, int i,std::shared_ptr<VOID> )> fIntervalHessian);
  FUNCTION2 (int n, int m,
                    std::function<INTERVAL_AUTODIFF(CONST INTERVAL_AUTODIFF&,INT i,std::shared_ptr<VOID> )> fAutoInterval,
                    std::function<EINTERVAL_VECTOR (CONST EINTERVAL_VECTOR &,std::shared_ptr<VOID>) > EIntervalVector,
                    std::function<EINTERVAL_VECTOR (CONST INTERVAL f_bar,EINTERVAL_VECTOR &,INT i,std::shared_ptr<VOID>) > HCEIntervalVector,
                    std::function<EINTERVAL_VECTOR (CONST EINTERVAL_VECTOR &,std::shared_ptr<VOID>,CONST MATRIX B) > BEIntervalVector,
                    std::function<EINTERVAL_VECTOR (CONST INTERVAL f_bar,EINTERVAL_VECTOR &,INT i,std::shared_ptr<VOID>,CONST MATRIX B) > HCBEIntervalVector,
                    std::function<EINTERVAL_VECTOR (CONST EINTERVAL_VECTOR& ,INT i,std::shared_ptr<VOID>,CONST MATRIX B) > BEIntervalVectorGrd,
                    std::function<EINTERVAL_VECTOR (CONST INTERVAL f_bar,EINTERVAL_VECTOR& ,INT i,std::shared_ptr<VOID>,CONST MATRIX B) > HCBEIntervalVectorGrd);

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
  friend REAL Function (FUNCTION2 & f, CONST VECTOR & x,  std::shared_ptr<VOID>  userdata);
  friend INTERVAL Function (FUNCTION2 & f, CONST INTERVAL_VECTOR & x,  std::shared_ptr<VOID>  userdata);
  friend EINTERVAL Function (FUNCTION2 & f, CONST EINTERVAL_VECTOR & X,std::shared_ptr<VOID> userdata);
  friend VECTOR VectorFunction (FUNCTION2 & f, CONST VECTOR & x,std::shared_ptr<VOID> userdata);
  friend EINTERVAL_VECTOR VectorFunction (FUNCTION2 & f, CONST EINTERVAL_VECTOR & x,  std::shared_ptr<VOID> userdata);
  friend INTERVAL_VECTOR VectorFunction (FUNCTION2 & f, CONST INTERVAL_VECTOR & x,std::shared_ptr<VOID> userdata);
  friend VECTOR Gradient (FUNCTION2 & f, CONST VECTOR & x,std::shared_ptr<VOID> userdata);
  friend INTERVAL_VECTOR Gradient (FUNCTION2 & f, CONST INTERVAL_VECTOR & x,std::shared_ptr<VOID> userdata);
  friend EINTERVAL_MATRIX Jacobian (FUNCTION2 & f, CONST EINTERVAL_VECTOR & x,  std::shared_ptr<VOID> userdata);
  friend VECTOR Gradient (FUNCTION2 & f, CONST VECTOR & x, int n,std::shared_ptr<VOID> userdata);
  friend INTERVAL_VECTOR Gradient (FUNCTION2 & f, CONST INTERVAL_VECTOR & x, int n,std::shared_ptr<VOID> userdata);
  friend MATRIX Jacobian (FUNCTION2 & f, CONST VECTOR & x,std::shared_ptr<VOID> userdata);
  friend INTERVAL_MATRIX Jacobian (FUNCTION2 & f, CONST INTERVAL_VECTOR & x,std::shared_ptr<VOID> userdata);
  friend MATRIX Hessian (FUNCTION2 & f, CONST VECTOR & x,std::shared_ptr<VOID>  userdata);
  friend INTERVAL_MATRIX Hessian (FUNCTION2 & f, CONST INTERVAL_VECTOR & x,std::shared_ptr<VOID>  userdata);
  friend MATRIX Hessian (FUNCTION2 & f, CONST VECTOR & x, int n,std::shared_ptr<VOID>  userdata);
  friend INTERVAL_MATRIX Hessian (FUNCTION2 & f, CONST INTERVAL_VECTOR & x, int n,std::shared_ptr<VOID> userdata);
  friend EINTERVAL_VECTOR Function_HC(FUNCTION2 & f, CONST INTERVAL f_bar,EINTERVAL_VECTOR & x,INT i,std::shared_ptr<VOID> userdata);
    friend EINTERVAL Function_HC(FUNCTION2 & f, CONST INTERVAL f_bar,EINTERVAL_VECTOR & x,std::shared_ptr<VOID> userdata);
    friend EINTERVAL_VECTOR BFunction_HC(FUNCTION2 & f, 
        CONST INTERVAL f_bar,
        EINTERVAL_VECTOR & x,
        INT i,
        std::shared_ptr<VOID> userdata,
        MATRIX B);
    friend INTERVAL_VECTOR VectorFunction (FUNCTION2 & f, 
                                            CONST INTERVAL_VECTOR & x,  
                                            std::shared_ptr<VOID> userdata, 
                                            CONST MATRIX& B);
    friend INTERVAL_VECTOR Gradient (FUNCTION2 & f, CONST INTERVAL_VECTOR & x, int n,  std::shared_ptr<VOID> userdata,CONST MATRIX B);
    friend EINTERVAL_MATRIX Hessian_HC(FUNCTION2 & f, CONST INTERVAL f_bar,EINTERVAL_VECTOR & x,INT i,std::shared_ptr<VOID> userdata);
    friend EINTERVAL_VECTOR Gradient_HC(FUNCTION2 & f, CONST INTERVAL f_bar,EINTERVAL_VECTOR & x,INT i,std::shared_ptr<VOID> userdata);
};
#undef NIL

#endif /* __NLF__ */
