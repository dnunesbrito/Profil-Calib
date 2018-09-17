/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <cmath>

#include "BIAS/Bias0Ext.hpp"

/*
 * The macro SECURE has been inserted in those cases where problems may
 * occur due to too much compiler optimization (using previous calculated
 * results after a rounding mode switch).
 */
#if 1 /* let's be pessimistic */
#define SECURE                  volatile
#define SECUREREAL(x)           (*((volatile REAL * const) (x)))
#define SECUREBIASINTERVAL(x)   ((volatile BIASINTERVAL * const) (x))
#else
#define SECURE
#define SECUREREAL(x)           (*(x))
#define SECUREBIASINTERVAL(x)   (x)
#endif

#if defined (__BIASINLINEROUNDING__)
VOID BiasRoundUp (VOID)   { _BiasRoundUp (); }
VOID BiasRoundDown (VOID) { _BiasRoundDown (); }
VOID BiasRoundNear (VOID) { _BiasRoundNear (); }
#endif

VOID EBiasAddRR (BIASINTERVAL * const pR,
		const REAL * const pa,
                const REAL * const pb)
  /**********************************************************************
  *  R = a + b
  */
{
  if(*pa == BiasNegInf){
      if(*pb == BiasNegInf){
          pR->inf = BiasNegInf;
          pR->sup = BiasNegInf;
      }else if(*pb == BiasPosInf){
          pR->inf = BiasNegInf;
          pR->sup = BiasPosInf;
      }else{
          pR->inf = BiasNegInf;
          pR->sup = BiasNegInf;
      }
      return;
  }else if(*pa == BiasPosInf){
      if(*pb == BiasNegInf){
          pR->inf = BiasNegInf;
          pR->sup = BiasPosInf;
      }else if(*pb == BiasPosInf){
          pR->inf = BiasPosInf;
          pR->sup = BiasPosInf;
      }else{
          pR->inf = BiasPosInf;
          pR->sup = BiasPosInf;
      }
      return;
  }
  _BiasRoundDown ();
  pR->inf = SECUREREAL (pa) + SECUREREAL (pb);
  _BiasRoundUp ();
  pR->sup = SECUREREAL (pa) + SECUREREAL (pb);
  _SetRoundToNearest();
} /* BiasAddRR */

VOID EBiasAddRI (BIASINTERVAL * const pR,
		const REAL * const pa,
                const BIASINTERVAL * const pB)
  /**********************************************************************
  *  R = a + B
  */
{
  BIASINTERVAL sum1,sum2;
  EBiasAddRR(&sum1,pa,&pB->inf);
  EBiasAddRR(&sum2,pa,&pB->sup);
  BiasHullII(pR,&sum1,&sum2);
} /* BiasAddRI */

VOID EBiasAddII (BIASINTERVAL * const pR,
		const BIASINTERVAL * const pA, const BIASINTERVAL * const pB)
  /**********************************************************************
  *  R = A + B
  */
{
  BIASINTERVAL sum1,sum2;
  EBiasAddRR(&sum1,&pA->inf,&pB->inf);
  EBiasAddRR(&sum2,&pA->sup,&pB->sup);
  BiasHullII(pR,&sum1,&sum2);
} /* BiasAddII */

VOID EBiasSubRR (BIASINTERVAL * const pR,
		const REAL * const pa,
                const REAL * const pb)
  /**********************************************************************
  *  R = a - b
  */
{
  if(*pa == BiasNegInf){
      if(*pb == BiasNegInf){
          pR->inf = BiasNegInf;
          pR->sup = BiasPosInf;
      }else if(*pb == BiasPosInf){
          pR->inf = BiasNegInf;
          pR->sup = BiasNegInf;
      }else{
          pR->inf = BiasNegInf;
          pR->sup = BiasNegInf;
      }
      return;
  }else if(*pa == BiasPosInf){
      if(*pb == BiasNegInf){
          pR->inf = BiasPosInf;
          pR->sup = BiasPosInf;
      }else if(*pb == BiasPosInf){
          pR->inf = BiasNegInf;
          pR->sup = BiasPosInf;
      }else{
          pR->inf = BiasPosInf;
          pR->sup = BiasPosInf;
      }
      return;
  }
  _BiasRoundDown ();
  pR->inf = SECUREREAL (pa) - SECUREREAL (pb);
  _BiasRoundUp ();
  pR->sup = SECUREREAL (pa) - SECUREREAL (pb);
  _SetRoundToNearest();
} /* BiasSubRR */
VOID EBiasSubRI (BIASINTERVAL * const pR,
		const REAL * const pa,
                const BIASINTERVAL * const pB)
  /**********************************************************************
  *  R = a - B
  *  Assertion: R != B
  */
{
    BIASINTERVAL sub1,sub2;
    EBiasSubRR(&sub1,pa,&pB->sup);
    EBiasSubRR(&sub2,pa,&pB->inf);
    BiasHullII(pR,&sub1,&sub2);
} /* BiasSubRI */

VOID EBiasSubIR (BIASINTERVAL * const pR,
		const BIASINTERVAL * const pA,
                const REAL * const pb)
  /**********************************************************************
  *  R = A - b
  */
{
    BIASINTERVAL sub1,sub2;
    EBiasSubRR(&sub1,&pA->inf,pb);
    EBiasSubRR(&sub2,&pA->sup,pb);
    BiasHullII(pR,&sub1,&sub2);
} /* BiasSubRI */

VOID EBiasSubII (BIASINTERVAL * const pR,
		const BIASINTERVAL * const pA, const BIASINTERVAL * const pB)
  /**********************************************************************
  *  R = A - B
  *  Assertion: R != B
  */
{
    BIASINTERVAL sub1,sub2;
    EBiasSubRR(&sub1,&pA->inf,&pB->sup);
    EBiasSubRR(&sub2,&pA->sup,&pB->inf);
    BiasHullII(pR,&sub1,&sub2);
} /* BiasSubII */

VOID EBiasMulRR (BIASINTERVAL * const pR,
		const REAL * const pa, const REAL * const pb)
  /**********************************************************************
  *  R = a * b
  */
{
  if(*pa == BiasNegInf){
      if(*pb == BiasNegInf){
          pR->inf = BiasPosInf;
          pR->sup = BiasPosInf;
      }else if(*pb == BiasPosInf){
          pR->inf = BiasNegInf;
          pR->sup = BiasNegInf;
      }else if(*pb == 0){
          pR->inf = BiasPosInf;
          pR->sup = BiasNegInf;
      }else if(*pb > 0){
          pR->inf = BiasNegInf;
          pR->sup = BiasNegInf;
      }else if(*pb > 0){
          pR->inf = BiasPosInf;
          pR->sup = BiasPosInf;
      }
      return;
  }else if(*pa == BiasPosInf){
      if(*pb == BiasNegInf){
          pR->inf = BiasPosInf;
          pR->sup = BiasPosInf;
      }else if(*pb == BiasPosInf){
          pR->inf = BiasNegInf;
          pR->sup = BiasPosInf;
      }else if(*pb == 0){
          pR->inf = BiasNegInf;
          pR->sup = BiasPosInf;
      }else if(*pb > 0){
          pR->inf = BiasPosInf;
          pR->sup = BiasPosInf;
      }else if(*pb > 0){
          pR->inf = BiasNegInf;
          pR->sup = BiasNegInf;
      }
      return;
  }else if(*pa == 0 && (*pb == BiasPosInf || *pb == BiasNegInf)){
      pR->inf = BiasNegInf;
      pR->sup = BiasPosInf;
  }
  _BiasRoundDown ();
  pR->inf = SECUREREAL (pa) * SECUREREAL (pb);
  _BiasRoundUp ();
  pR->sup = SECUREREAL (pa) * SECUREREAL (pb);
  _SetRoundToNearest();

} /* BiasMulRR */
VOID EBiasMulRI (BIASINTERVAL * const pR,
		const REAL * const pa, const BIASINTERVAL * const pB)
  /**********************************************************************
  *  R = a * B
  *  Assertion: R != B
  */
{
    BIASINTERVAL mul1,mul2;
  _BiasRoundDown ();
  if (Sign (SECUREREAL (pa)) == 0) {                                /* a >= 0 */
      EBiasMulRR(&mul1,pa,&pB->inf);
      EBiasMulRR(&mul2,pa,&pB->sup);
      BiasHullII(pR,&mul1,&mul2);
  }
  else {                                                /* a < 0  */
      EBiasMulRR(&mul1,pa,&pB->sup);
      EBiasMulRR(&mul2,pa,&pB->inf);
      BiasHullII(pR,&mul1,&mul2);
  }
  _SetRoundToNearest();
} /* BiasMulRI */

VOID EBiasMulII (BIASINTERVAL * const pR,
		const BIASINTERVAL * const pA,
		const BIASINTERVAL * const pB)
  /**********************************************************************
  *  R = A * B
  *  Assertion: R != A and R != B
  */
{
    BIASINTERVAL mul1,mul2;
    if(SECUREBIASINTERVAL (pA)->inf == BiasNegInf){
        if(SECUREBIASINTERVAL (pB)->inf == 0 || SECUREBIASINTERVAL (pB)->sup == 0){
           pR->inf = BiasNegInf;
           pR->sup = BiasPosInf;
           return;
        }else if(Sign(SECUREBIASINTERVAL (pB)->inf) == 0){ /*B >= 0*/
            pR->inf = BiasNegInf;
            if(SECUREBIASINTERVAL (pA)->sup == BiasPosInf){
                pR->sup = BiasPosInf;
                return;
            }else if (Sign(SECUREBIASINTERVAL (pA)->sup) == 0){ /*A.sup >= 0*/
                pR->sup = SECUREBIASINTERVAL (pA)->sup * SECUREBIASINTERVAL (pB)->sup;
                return;
            }else{ /*A.sup < 0 e não é infinito*/
                pR->sup = SECUREBIASINTERVAL (pA)->sup * SECUREBIASINTERVAL (pB)->inf;
            }
        }else if(Sign(SECUREBIASINTERVAL (pB)->sup)){ /*B < 0*/
            pR->sup = BiasPosInf;
            if(SECUREBIASINTERVAL (pA)->sup == BiasPosInf){ 
                pR->inf = BiasNegInf;
                return;
            }else if(Sign(SECUREBIASINTERVAL (pA)->sup) == 0){
                pR->inf = SECUREBIASINTERVAL (pA)->sup * SECUREBIASINTERVAL (pB)->inf;
                return;
            }else{
                pR->inf = SECUREBIASINTERVAL (pA)->sup * SECUREBIASINTERVAL (pB)->sup;
                return;
            }
        }else{
            pR->inf = BiasNegInf;
            pR->sup = BiasPosInf;
            return;
        }
        if(SECUREBIASINTERVAL (pA)->sup == BiasPosInf){
            pR->inf = BiasNegInf;
            pR->sup = BiasPosInf;
            return;
        }
    }
    if(SECUREBIASINTERVAL (pA)->sup == BiasPosInf){
        if(SECUREBIASINTERVAL (pB)->inf == 0 || SECUREBIASINTERVAL (pB)->sup == 0){
           pR->inf = BiasNegInf;
           pR->sup = BiasPosInf;
           return;
        }else if(Sign(SECUREBIASINTERVAL (pB)->inf) == 0){ /*B >= 0*/
            pR->sup = BiasPosInf;
            if(Sign(SECUREBIASINTERVAL (pA)->inf) == 0){ /*A.inf >= 0*/
                pR->inf = SECUREBIASINTERVAL (pA)->inf * SECUREBIASINTERVAL (pB)->inf;
                return;
            }else{
                pR->inf = SECUREBIASINTERVAL (pA)->inf * SECUREBIASINTERVAL (pB)->sup;
                return;
            }
        }else if(Sign(SECUREBIASINTERVAL (pB)->sup)){ /*B < 0*/
            pR->inf = BiasNegInf;
            if(Sign(SECUREBIASINTERVAL (pA)->inf) == 0){ /*A.inf >= 0*/
                pR->sup = SECUREBIASINTERVAL (pA)->inf * SECUREBIASINTERVAL (pB)->sup;
                return;
            }else{
                pR->sup = SECUREBIASINTERVAL (pA)->inf * SECUREBIASINTERVAL (pB)->inf;
                return;
            }
        }else{
            pR->inf = BiasNegInf;
            pR->sup = BiasPosInf;
            return;            
        }
    }
    
    
    
    
    
    if(SECUREBIASINTERVAL (pB)->inf == BiasNegInf){
        if(SECUREBIASINTERVAL (pA)->inf == 0 || SECUREBIASINTERVAL (pA)->sup == 0){
           pR->inf = BiasNegInf;
           pR->sup = BiasPosInf;
           return;
        }else if(Sign(SECUREBIASINTERVAL (pA)->inf) == 0){ /*B >= 0*/
            pR->inf = BiasNegInf;
            if(SECUREBIASINTERVAL (pB)->sup == BiasPosInf){
                pR->sup = BiasPosInf;
                return;
            }else if (Sign(SECUREBIASINTERVAL (pB)->sup) == 0){ /*A.sup >= 0*/
                pR->sup = SECUREBIASINTERVAL (pB)->sup * SECUREBIASINTERVAL (pA)->sup;
                return;
            }else{ /*A.sup < 0 e não é infinito*/
                pR->sup = SECUREBIASINTERVAL (pB)->sup * SECUREBIASINTERVAL (pA)->inf;
            }
        }else if(Sign(SECUREBIASINTERVAL (pA)->sup)){ /*B < 0*/
            pR->sup = BiasPosInf;
            if(SECUREBIASINTERVAL (pB)->sup == BiasPosInf){ 
                pR->inf = BiasNegInf;
                return;
            }else if(Sign(SECUREBIASINTERVAL (pB)->sup) == 0){
                pR->inf = SECUREBIASINTERVAL (pB)->sup * SECUREBIASINTERVAL (pA)->inf;
                return;
            }else{
                pR->inf = SECUREBIASINTERVAL (pB)->sup * SECUREBIASINTERVAL (pA)->sup;
                return;
            }
        }else{
            pR->inf = BiasNegInf;
            pR->sup = BiasPosInf;
            return;
        }
        if(SECUREBIASINTERVAL (pA)->sup == BiasPosInf){
            pR->inf = BiasNegInf;
            pR->sup = BiasPosInf;
            return;
        }
    }
    if(SECUREBIASINTERVAL (pB)->sup == BiasPosInf){
        if(SECUREBIASINTERVAL (pA)->inf == 0 || SECUREBIASINTERVAL (pA)->sup == 0){
           pR->inf = BiasNegInf;
           pR->sup = BiasPosInf;
           return;
        }else if(Sign(SECUREBIASINTERVAL (pA)->inf) == 0){ /*B >= 0*/
            pR->sup = BiasPosInf;
            if(Sign(SECUREBIASINTERVAL (pB)->inf) == 0){ /*A.inf >= 0*/
                pR->inf = SECUREBIASINTERVAL (pB)->inf * SECUREBIASINTERVAL (pA)->inf;
                return;
            }else{
                pR->inf = SECUREBIASINTERVAL (pB)->inf * SECUREBIASINTERVAL (pA)->sup;
                return;
            }
        }else if(Sign(SECUREBIASINTERVAL (pA)->sup)){ /*B < 0*/
            pR->inf = BiasNegInf;
            if(Sign(SECUREBIASINTERVAL (pB)->inf) == 0){ /*A.inf >= 0*/
                pR->sup = SECUREBIASINTERVAL (pB)->inf * SECUREBIASINTERVAL (pA)->sup;
                return;
            }else{
                pR->sup = SECUREBIASINTERVAL (pB)->inf * SECUREBIASINTERVAL (pA)->inf;
                return;
            }
        }else{
            pR->inf = BiasNegInf;
            pR->sup = BiasPosInf;
            return;            
        }
    }
    
    
    
    
    
    
    
  _BiasRoundDown ();
  if (Sign (SECUREBIASINTERVAL (pA)->inf) == 0) {                            /* A >= 0 */
    if (Sign (SECUREBIASINTERVAL (pB)->inf) == 0) {                          /* B >= 0 */
      pR->inf = SECUREBIASINTERVAL (pA)->inf * SECUREBIASINTERVAL (pB)->inf;
      _BiasRoundUp ();
      pR->sup = SECUREBIASINTERVAL (pA)->sup * SECUREBIASINTERVAL (pB)->sup;
    }
    else if (Sign (SECUREBIASINTERVAL (pB)->sup)) {                          /* B <= 0 */
      pR->inf = SECUREBIASINTERVAL (pA)->sup * SECUREBIASINTERVAL (pB)->inf;
      _BiasRoundUp ();
      pR->sup = SECUREBIASINTERVAL (pA)->inf * SECUREBIASINTERVAL (pB)->sup;
    }
    else {                                              /* 0 in B */
      pR->inf = SECUREBIASINTERVAL (pA)->sup * SECUREBIASINTERVAL (pB)->inf;
      _BiasRoundUp ();
      pR->sup = SECUREBIASINTERVAL (pA)->sup * SECUREBIASINTERVAL (pB)->sup;
    }
  }
  else if (Sign (SECUREBIASINTERVAL (pA)->sup)) {                            /* A <= 0 */
    if (Sign (SECUREBIASINTERVAL (pB)->inf) == 0) {                          /* B >= 0 */
      pR->inf = SECUREBIASINTERVAL (pA)->inf * SECUREBIASINTERVAL (pB)->sup;
      _BiasRoundUp ();
      pR->sup = SECUREBIASINTERVAL (pA)->sup * SECUREBIASINTERVAL (pB)->inf;
    }
    else if (Sign (SECUREBIASINTERVAL (pB)->sup)) {                          /* B <= 0 */
      pR->inf = SECUREBIASINTERVAL (pA)->sup * SECUREBIASINTERVAL (pB)->sup;
      _BiasRoundUp ();
      pR->sup = SECUREBIASINTERVAL (pA)->inf * SECUREBIASINTERVAL (pB)->inf;
    }
    else {                                              /* 0 in B */
      pR->inf = SECUREBIASINTERVAL (pA)->inf * SECUREBIASINTERVAL (pB)->sup;
      _BiasRoundUp ();
      pR->sup = SECUREBIASINTERVAL (pA)->inf * SECUREBIASINTERVAL (pB)->inf;
    }
  }
  else {                                                /* 0 in A */
    if (Sign (SECUREBIASINTERVAL (pB)->inf) == 0) {                          /* B >= 0 */
      pR->inf = SECUREBIASINTERVAL (pA)->inf * SECUREBIASINTERVAL (pB)->sup;
      _BiasRoundUp ();
      pR->sup = SECUREBIASINTERVAL (pA)->sup * SECUREBIASINTERVAL (pB)->sup;
    }
    else if (Sign (SECUREBIASINTERVAL (pB)->sup)) {                          /* B <= 0 */
      pR->inf = SECUREBIASINTERVAL (pA)->sup * SECUREBIASINTERVAL (pB)->inf;
      _BiasRoundUp ();
      pR->sup = SECUREBIASINTERVAL (pA)->inf * SECUREBIASINTERVAL (pB)->inf;
    }
    else {                                              /* 0 in B */
      SECURE REAL r1 = SECUREBIASINTERVAL (pA)->inf * SECUREBIASINTERVAL (pB)->sup;
      SECURE REAL r2 = SECUREBIASINTERVAL (pA)->sup * SECUREBIASINTERVAL (pB)->inf;

      pR->inf = r1 < r2 ? r1 : r2;

      _BiasRoundUp ();

      r1 = SECUREBIASINTERVAL (pA)->inf * SECUREBIASINTERVAL (pB)->inf;
      r2 = SECUREBIASINTERVAL (pA)->sup * SECUREBIASINTERVAL (pB)->sup;

      pR->sup = r1 > r2 ? r1 : r2;
    }
  }
  _SetRoundToNearest();
} /* BiasMulII */
VOID EBiasDivRR (BIASINTERVAL * const pR,
		const REAL * const pa, const REAL * const pb)
  /**********************************************************************
  *  R = a / b
  */
{
    if(SECUREREAL (pa) == BiasNegInf){
        if(SECUREREAL (pb) == BiasNegInf){
            pR->inf = 0;
            pR->sup = BiasPosInf;
        }else if(SECUREREAL (pb) < 0){
            pR->inf = BiasPosInf;
            pR->sup = BiasPosInf;
        }else if(SECUREREAL (pb) == 0){
            pR->inf = BiasNegInf;
            pR->sup = BiasPosInf;
        }else if(SECUREREAL (pb) > 0){
            pR->inf = BiasNegInf;
            pR->sup = BiasNegInf;
        }else if(SECUREREAL (pb) == BiasPosInf){
            pR->inf = BiasNegInf;
            pR->sup = 0;
        }
        return;
    }else if(SECUREREAL (pa) > 0){
        if(SECUREREAL (pb) == BiasNegInf){
            pR->inf = 0;
            pR->sup = 0;
            return;
        }else if(SECUREREAL (pb) == 0){
            pR->inf = BiasNegInf;
            pR->sup = BiasPosInf;
            return;
        }else if(SECUREREAL (pb) == BiasPosInf){
            pR->inf = 0;
            pR->sup = 0;
            return;
        }
    }else if(SECUREREAL (pa) == 0){
        if(SECUREREAL (pb) == 0){
            pR->inf = BiasNegInf;
            pR->sup = BiasPosInf;
            return;
        }
    }
    if(SECUREREAL (pa) == BiasPosInf){
        if(SECUREREAL (pb) == BiasNegInf){
            pR->inf = BiasNegInf;
            pR->sup = 0;
        }else if(SECUREREAL (pb) < 0){
            pR->inf = BiasNegInf;
            pR->sup = BiasNegInf;
        }else if(SECUREREAL (pb) == 0){
            pR->inf = BiasNegInf;
            pR->sup = BiasPosInf;
        }else if(SECUREREAL (pb) > 0){
            pR->inf = BiasPosInf;
            pR->sup = BiasPosInf;
        }else if(SECUREREAL (pb) == BiasPosInf){
            pR->inf = 0;
            pR->sup = BiasPosInf;
        }
        return;
    }
  _BiasRoundDown ();
  pR->inf = SECUREREAL (pa) / SECUREREAL (pb);
  _BiasRoundUp ();
  pR->sup = SECUREREAL (pa) / SECUREREAL (pb);
  _SetRoundToNearest();
} /* BiasDivRR */

VOID EBiasDivRI (BIASINTERVAL * const pR1,BIASINTERVAL * const pR2,
		const REAL * const pa, const BIASINTERVAL * const pB)
  /**********************************************************************
  *  R = a / B
  *  Assertion: R != B
  */
{
    BIASINTERVAL div1,div2;
    if(SECUREBIASINTERVAL (pB)->inf == 0){
        if(*pa > 0){
            EBiasDivRR(&div1,pa,&pB->sup);
            pR1->inf = BiasNegInf;
            pR1->sup = BiasNegInf;
            pR2->inf = div1.inf;
            pR2->sup = BiasPosInf;
            return;
        }else if(*pa < 0){
            EBiasDivRR(&div1,pa,&pB->sup);
            pR1->inf = BiasNegInf;
            pR1->sup = div1.inf;
            pR2->inf = BiasPosInf;
            pR2->sup = BiasPosInf;
            return;
        }
    }else if(SECUREBIASINTERVAL (pB)->sup == 0){
        if(*pa > 0){
            EBiasDivRR(&div1,pa,&pB->inf);
            pR1->inf = div1.sup;
            pR1->sup = BiasNegInf;
            pR2->inf = BiasPosInf;
            pR2->sup = BiasPosInf;
            return;
        }else if(*pa < 0){
            EBiasDivRR(&div1,pa,&pB->inf);
            pR1->inf = BiasNegInf;
            pR1->sup = BiasNegInf;
            pR2->inf = div1.inf;
            pR2->sup = BiasPosInf;
            return;
        }
    }else if(SECUREBIASINTERVAL (pB)->inf < 0 && SECUREBIASINTERVAL (pB)->sup > 0){
        if(*pa == BiasNegInf || *pa == BiasPosInf){
            pR1->inf = BiasNegInf;
            pR1->sup = BiasPosInf;
            pR2->inf = NAN;
            pR2->sup = NAN;
            return;
        }
        if(*pa > 0){
            EBiasDivRR(&div1,pa,&pB->inf);
            EBiasDivRR(&div2,pa,&pB->sup);
            pR1->inf = BiasNegInf;
            pR1->sup = div1.inf;
            pR2->inf = div2.inf;
            pR2->sup = BiasPosInf;
            return;
        }else if(*pa < 0){
            EBiasDivRR(&div1,pa,&pB->inf);
            EBiasDivRR(&div2,pa,&pB->sup);
            pR1->inf = BiasNegInf;
            pR1->sup = div2.inf;
            pR2->inf = div1.inf;
            pR2->sup = BiasPosInf;
            return;
        }
    }
    EBiasDivRR(&div1,pa,&pB->inf);
    EBiasDivRR(&div2,pa,&pB->sup);
    BiasHullII(pR1,&div1,&div2);
    pR2->inf = NAN;
    pR2->sup = NAN;
} /* BiasDivRI */

VOID EBiasDivIR (BIASINTERVAL * const pR,
		const BIASINTERVAL * const pA, const REAL * const pb)
  /**********************************************************************
  *  R = A / b
  *  Assertion: R != A
  */
{
    BIASINTERVAL div1,div2;
    EBiasDivRR(&div1,&pA->inf,pb);
    EBiasDivRR(&div2,&pA->sup,pb);
    BiasHullII(pR,&div1,&div2);
} /* BiasDivIR */

VOID EBiasDivII (BIASINTERVAL * const pR1,
                BIASINTERVAL * const pR2,
		const BIASINTERVAL * const pA,
		const BIASINTERVAL * const pB)
  /**********************************************************************
  *  R = A / B
  *  Assertion: R != A and R != B
  */
{
    BIASINTERVAL divinf1,divinf2,divsup1,divsup2;
    EBiasDivRR(&divsup1,&pA->sup,&pB->inf);
    EBiasDivRR(&divsup2,&pA->sup,&pB->sup);
    if(SECUREBIASINTERVAL (pB)->inf == 0){
        if(SECUREBIASINTERVAL (pA)->inf > 0){
            EBiasDivRR(&divinf1,&pA->inf,&pB->sup);
            pR1->inf = BiasNegInf;
            pR1->sup = BiasNegInf;
            pR2->inf = divinf1.inf;
            pR2->sup = BiasPosInf;
            return;
        }else if(SECUREBIASINTERVAL (pA)->sup < 0){
            EBiasDivRR(&divinf1,&pA->inf,&pB->sup);
            pR1->inf = BiasNegInf;
            pR1->sup = divinf1.inf;
            pR2->inf = BiasPosInf;
            pR2->sup = BiasPosInf;
            return;
        }
    }else if(SECUREBIASINTERVAL (pB)->sup == 0){
        if(SECUREBIASINTERVAL (pA)->inf > 0){
            EBiasDivRR(&divinf1,&pA->inf,&pB->inf);
            pR1->inf = divinf1.sup;
            pR1->sup = BiasNegInf;
            pR2->inf = BiasPosInf;
            pR2->sup = BiasPosInf;
            return;
        }else if(SECUREBIASINTERVAL (pA)->sup < 0){
            EBiasDivRR(&divinf1,&pA->inf,&pB->inf);
            pR1->inf = BiasNegInf;
            pR1->sup = BiasNegInf;
            pR2->inf = divinf1.inf;
            pR2->sup = BiasPosInf;
            return;
        }
    }else if(SECUREBIASINTERVAL (pB)->inf < 0 && SECUREBIASINTERVAL (pB)->sup > 0){
        if(SECUREBIASINTERVAL (pA)->inf == BiasNegInf || SECUREBIASINTERVAL (pA)->sup == BiasPosInf){
            pR1->inf = BiasNegInf;
            pR1->sup = BiasPosInf;
            pR2->inf = NAN;
            pR2->sup = NAN;
            return;
        }
        if(SECUREBIASINTERVAL (pA)->inf > 0){
            EBiasDivRR(&divinf1,&pA->inf,&pB->inf);
            EBiasDivRR(&divinf2,&pA->inf,&pB->sup);
            pR1->inf = BiasNegInf;
            pR1->sup = divinf1.inf;
            pR2->inf = divinf2.inf;
            pR2->sup = BiasPosInf;
            return;
        }else if(SECUREBIASINTERVAL (pA)->sup < 0){
            EBiasDivRR(&divinf1,&pA->inf,&pB->inf);
            EBiasDivRR(&divinf2,&pA->inf,&pB->sup);
            pR1->inf = BiasNegInf;
            pR1->sup = divinf2.inf;
            pR2->inf = divinf1.inf;
            pR2->sup = BiasPosInf;
            return;
        }else if(SECUREBIASINTERVAL (pB)->inf < 0 && SECUREBIASINTERVAL (pB)->sup > 0){
            pR1->inf = BiasNegInf;
            pR1->sup = BiasPosInf;
            pR2->inf = NAN;
            pR2->sup = NAN;
            return;
        }
    }
    EBiasDivRR(&divinf1,&pA->inf,&pB->inf);
    EBiasDivRR(&divinf2,&pA->inf,&pB->sup);
    EBiasDivRR(&divsup1,&pA->sup,&pB->inf);
    EBiasDivRR(&divsup2,&pA->sup,&pB->sup);
    BiasHullII(pR1,&divinf1,&divinf2);
    BiasHullII(pR1,pR1,&divsup1);
    BiasHullII(pR1,pR1,&divsup2);
    pR2->inf = NAN;
    pR2->sup = NAN;
}
VOID BiasMacII (BIASINTERVAL * const pR1,
                BIASINTERVAL * const pR2,
		const BIASINTERVAL * const pA,
		const BIASINTERVAL * const pB)
  /**********************************************************************
  *  R += A * B
  *  Assertion: R != A and R != B
  */
{
    BIASINTERVAL divinf1,divinf2,divsup1,divsup2,tmppR1;
    EBiasDivRR(&divsup1,&pA->sup,&pB->inf);
    EBiasDivRR(&divsup2,&pA->sup,&pB->sup);
    if(SECUREBIASINTERVAL (pB)->inf == 0){
        if(SECUREBIASINTERVAL (pA)->inf > 0){
            EBiasDivRR(&divinf1,&pA->inf,&pB->sup);
            pR1->inf = BiasNegInf;
            pR1->sup = BiasNegInf;
            pR2->inf = divinf1.inf;
            pR2->sup = BiasPosInf;
            return;
        }else if(SECUREBIASINTERVAL (pA)->sup < 0){
            EBiasDivRR(&divinf1,&pA->inf,&pB->sup);
            pR1->inf = BiasNegInf;
            pR1->sup = divinf1.inf;
            pR2->inf = BiasPosInf;
            pR2->sup = BiasPosInf;
            return;
        }
    }else if(SECUREBIASINTERVAL (pB)->sup == 0){
        if(SECUREBIASINTERVAL (pA)->inf > 0){
            EBiasDivRR(&divinf1,&pA->inf,&pB->inf);
            pR1->inf = divinf1.sup;
            pR1->sup = BiasNegInf;
            pR2->inf = BiasPosInf;
            pR2->sup = BiasPosInf;
            return;
        }else if(SECUREBIASINTERVAL (pA)->sup < 0){
            EBiasDivRR(&divinf1,&pA->inf,&pB->inf);
            pR1->inf = BiasNegInf;
            pR1->sup = BiasNegInf;
            pR2->inf = divinf1.inf;
            pR2->sup = BiasPosInf;
            return;
        }
    }
    EBiasDivRR(&divinf1,&pA->inf,&pB->inf);
    EBiasDivRR(&divinf2,&pA->inf,&pB->sup);
    EBiasDivRR(&divsup1,&pA->sup,&pB->inf);
    EBiasDivRR(&divsup2,&pA->sup,&pB->sup);
    BiasHullII(&tmppR1,&divinf1,&divinf2);
    BiasHullII(&tmppR1,pR1,&divsup1);
    BiasHullII(&tmppR1,pR1,&divsup2);
    pR2->inf = NAN;
    pR2->sup = NAN;
    BiasAddII(pR1,pR1,&tmppR1);
}
bool EBiasHasInfinity(BIASINTERVAL * const pR1){
    if(EBiasInf(pR1) == BiasPosInf || EBiasSup(pR1) == BiasNegInf)return true;
    if(EBiasInf(pR1) == BiasNegInf || EBiasSup(pR1) == BiasPosInf)return true;
    return false;
}
bool EBiasPosInfinity(BIASINTERVAL * const pR1){
    if(EBiasInf(pR1) == BiasPosInf && EBiasSup(pR1) == BiasPosInf)return true;
    return false;
}
bool EBiasNegInfinity(BIASINTERVAL * const pR1){
    if(EBiasInf(pR1) == BiasNegInf && EBiasSup(pR1) == BiasNegInf)return true;
    return false;
}

