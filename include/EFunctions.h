/************************************************************************
 *
 * Definition of standard functions (REAL and EINTERVAL)
 * ----------------------------------------------------
 *
 * Copyright (C) 1993, 1997 Olaf Knueppel
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
 * $Id: Functions.h 478 2006-08-09 13:13:30Z keil $
 *
 ************************************************************************/

#ifndef __EFUNCTIONS__
#define __EFUNCTIONS__

#ifndef __EINTERVAL__
    #include <EINTERVAL.hpp>
#endif
#ifndef __INTERVAL__
    #include <INTERVAL.hpp>
#endif
#include <Functions.h>
#include <BIAS/BiasF.h>
#include <Constants.h>
#include <math.h>

       EINTERVAL Sin    (CONST EINTERVAL & x);
       EINTERVAL Cos    (CONST EINTERVAL & x);
       EINTERVAL Tan    (CONST EINTERVAL & x);
       EINTERVAL Cot    (CONST EINTERVAL & x);
       EINTERVAL ArcSin (CONST EINTERVAL & x);
       EINTERVAL ArcCos (CONST EINTERVAL & x);
       EINTERVAL ArcTan (CONST EINTERVAL & x);
       EINTERVAL EArcTan2(CONST EINTERVAL & x,CONST EINTERVAL & y);
       EINTERVAL ArcCot (CONST EINTERVAL & x);

       EINTERVAL Sinh   (CONST EINTERVAL & x);
       EINTERVAL Cosh   (CONST EINTERVAL & x);
       EINTERVAL Tanh   (CONST EINTERVAL & x);
       EINTERVAL Coth   (CONST EINTERVAL & x);
       EINTERVAL ArSinh (CONST EINTERVAL & x);
       EINTERVAL ArCosh (CONST EINTERVAL & x);
       EINTERVAL ArTanh (CONST EINTERVAL & x);
       EINTERVAL ArCoth (CONST EINTERVAL & x);

       EINTERVAL Exp    (CONST EINTERVAL & x);
       EINTERVAL Log    (CONST EINTERVAL & x);
       EINTERVAL Log10  (CONST EINTERVAL & x);

       EINTERVAL IAbs   (CONST EINTERVAL & x);
       EINTERVAL Sqr    (CONST EINTERVAL & x);
       EINTERVAL Sqrt   (CONST EINTERVAL & x);
       EINTERVAL Root   (CONST EINTERVAL & x, INT n);

       EINTERVAL Power  (CONST EINTERVAL & x, INT n);
       EINTERVAL Power  (CONST EINTERVAL & x, CONST EINTERVAL & y);

#endif /* __EFUNCTIONS__ */
