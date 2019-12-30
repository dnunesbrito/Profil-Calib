/************************************************************************
 *
 * Implementation of standard functions (REAL and EINTERVAL)
 * --------------------------------------------------------
 *
 * Copyright (C) 1993, 1997 Olaf Knueppel
 *               2005 Christian Keil
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
 * $Id: Functions.C 478 2006-08-09 13:13:30Z keil $
 *
 ************************************************************************/

static char rcs_id[] = "$Id: Functions.C 478 2006-08-09 13:13:30Z keil $";

#include <EFunctions.h>
#include <complex>



EINTERVAL Sin (CONST EINTERVAL & x)
{
  EINTERVAL r(x.size());
  for(int i = 1;i <= x.size();i++){
    BiasSin(Bias(r,i), Bias(x,i));
  }
  return r;
}

EINTERVAL Cos (CONST EINTERVAL & x)
{
  EINTERVAL r(x.size());
  for(int i = 1;i <= x.size();i++){
    BiasCos(Bias(r,i), Bias(x,i));
  }
  return r;
}

EINTERVAL Tan (CONST EINTERVAL & x)
{
  EINTERVAL r(x.size());
  for(int i = 1;i <= x.size();i++){
    BiasTan(Bias(r,i), Bias(x,i));
  }
  return r;
}

EINTERVAL Cot (CONST EINTERVAL & x)
{
  EINTERVAL r(x.size());
  for(int i = 1;i <= x.size();i++){
    BiasCot(Bias(r,i), Bias(x,i));
  }
  return r;
}

EINTERVAL ArcSin (CONST EINTERVAL & x)
{
  EINTERVAL r(x.size());
  for(int i = 1;i <= x.size();i++){
    BiasArcSin(Bias(r,i), Bias(x,i));
  }
  return r;
}

EINTERVAL ArcCos (CONST EINTERVAL & x)
{
  EINTERVAL r(x.size());
  for(int i = 1;i <= x.size();i++){
    BiasArcCos(Bias(r,i), Bias(x,i));
  }
  return r;
}

EINTERVAL ArcTan (CONST EINTERVAL & x)
{
  EINTERVAL r(x.size());
  for(int i = 1;i <= x.size();i++){
    BiasArcTan(Bias(r,i), Bias(x,i));
  }
  return r;
}
//EINTERVAL EArcTan2 (CONST EINTERVAL & y,CONST EINTERVAL & x){
//  EINTERVAL r(x.size());
//  for(int i = 1;i <= x.size();i++){
//      for(int j = 1;j <= y.size();j++){
//        r(i)=(INTERVAL)ArcTan2(y(j), x(i));
//      }
//  }
//  return r;
//}
EINTERVAL ArcCot (CONST EINTERVAL & x)
{
  EINTERVAL r(x.size());
  for(int i = 1;i <= x.size();i++){
    BiasArcCot(Bias(r,i), Bias(x,i));
  }
  return r;
}

EINTERVAL Sinh (CONST EINTERVAL & x)
{
  EINTERVAL r(x.size());
  for(int i = 1;i <= x.size();i++){
    BiasSinh(Bias(r,i), Bias(x,i));
  }
  return r;
}

EINTERVAL Cosh (CONST EINTERVAL & x)
{
  EINTERVAL r(x.size());
  for(int i = 1;i <= x.size();i++){
    BiasCosh(Bias(r,i), Bias(x,i));
  }
  return r;
}

EINTERVAL Tanh (CONST EINTERVAL & x)
{
  EINTERVAL r(x.size());
  for(int i = 1;i <= x.size();i++){
    BiasTanh(Bias(r,i), Bias(x,i));
  }
  return r;

}

EINTERVAL Coth (CONST EINTERVAL & x)
{
  EINTERVAL r(x.size());
  for(int i = 1;i <= x.size();i++){
    BiasCoth(Bias(r,i), Bias(x,i));
  }
  return r;

}

EINTERVAL ArSinh (CONST EINTERVAL & x)
{
  EINTERVAL r(x.size());
  for(int i = 1;i <= x.size();i++){
    BiasArSinh(Bias(r,i), Bias(x,i));
  }
  return r;

}

EINTERVAL ArCosh (CONST EINTERVAL & x)
{
  EINTERVAL r(x.size());
  for(int i = 1;i <= x.size();i++){
    BiasArCosh(Bias(r,i), Bias(x,i));
  }
  return r;

}

EINTERVAL ArTanh (CONST EINTERVAL & x)
{
  EINTERVAL r(x.size());
  for(int i = 1;i <= x.size();i++){
    BiasArTanh(Bias(r,i), Bias(x,i));
  }
  return r;

}

EINTERVAL ArCoth (CONST EINTERVAL & x)
{
  EINTERVAL r(x.size());
  for(int i = 1;i <= x.size();i++){
    BiasArCoth(Bias(r,i), Bias(x,i));
  }
  return r;

}

EINTERVAL Exp (CONST EINTERVAL & x)
{
  EINTERVAL r(x.size());
  for(int i = 1;i <= x.size();i++){
    BiasExp(Bias(r,i), Bias(x,i));
  }
  return r;

}

EINTERVAL Log (CONST EINTERVAL & x)
{
  EINTERVAL r(x.size());
  for(int i = 1;i <= x.size();i++){
    BiasLog(Bias(r,i), Bias(x,i));
  }
  return r;

}

EINTERVAL Log10 (CONST EINTERVAL & x)
{
  EINTERVAL r(x.size());
  for(int i = 1;i <= x.size();i++){
    BiasLog10(Bias(r,i), Bias(x,i));
  }
  return r;

}

EINTERVAL IAbs (CONST EINTERVAL & x)
{
  EINTERVAL r(x.size());
  for(int i = 1;i <= x.size();i++){
    BiasIAbs(Bias(r,i), Bias(x,i));
  }
  return r;

}

EINTERVAL Sqr (CONST EINTERVAL & x)
{
  EINTERVAL r(x.size());
  for(int i = 1;i <= x.size();i++){
    BiasSqr(Bias(r,i), Bias(x,i));
  }
  return r;

}

EINTERVAL Sqrt (CONST EINTERVAL & x)
{
  EINTERVAL r(x.size());
  for(int i = 1;i <= x.size();i++){
    if(EBiasHasInfinity(Bias(x,i))){
        if(EBiasPosInfinity(Bias(x,i)) || EBiasNegInfinity(Bias(x,i)))
            r(i) =  x(i);
        else{
            if(x(i).inf() == BiasNegInf)
                r(i).ival.inf = BiasNegInf;
            else
                r(i).ival.inf = sqrt(x(i).ival.inf);
            if(x(i).sup() == BiasPosInf)
                r(i).ival.sup = BiasPosInf;
            else
                r(i).ival.sup = sqrt(x(i).ival.sup);
        }
        return x;
    }
    BiasSqrt(Bias(r,i), Bias(x,i));
  }
  return r;

}

EINTERVAL Root (CONST EINTERVAL & x, INT n)
{
  EINTERVAL r(x.size());
  for(int i = 1;i <= x.size();i++){
    BiasRoot(Bias(r,i), Bias(x,i),n);
  }
  return r;

}

EINTERVAL Power (CONST EINTERVAL & x, INT n)
{
  EINTERVAL r(x.size());
  for(int i = 1;i <= x.size();i++){
    BiasPowerN(Bias(r,i), Bias(x,i),n);
  }
  return r;
}

EINTERVAL Power (CONST EINTERVAL & x, CONST EINTERVAL & y)
{
  EINTERVAL r(x.size());
  for(int i = 1;i <= x.size();i++){
      for(int j = 1;j <= y.size();j++){
        BiasPowerI(Bias(r,i), Bias(x,i),Bias(y,j));
      }
  }
  return r;
}
