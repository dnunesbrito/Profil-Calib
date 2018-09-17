/************************************************************************
 *
 * Implementation of type INTERVAL
 * -------------------------------
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
 * $Id: Interval.C 478 2006-08-09 13:13:30Z keil $
 *
 ************************************************************************/

static const char rcs_id[] = "$Id: Interval.C 478 2006-08-09 13:13:30Z keil $";

#include <Interval.h>
#include <cmath>

#include "BIAS/BiasFExt.hpp"

ostream & operator << (ostream & os, CONST INTERVAL & x)
{
  return os << '[' << Inf (x) << ',' << Sup(x) << ']';
}

istream & operator >> (istream & is, INTERVAL & x)
{
  REAL a, b;

  is >> a;
  is >> b;
  BiasHullRR (Bias(x), & a, & b);
  return is;
}

// The following code is only used to force Constants.C to be
// always included in the executable code.

extern VOID RegisterConstants ();

VOID RegisterInterval () { RegisterConstants (); }

bool IsNAN(CONST INTERVAL& src){
    if(std::isnan(src.ival.inf) || std::isnan(src.ival.sup))return true;
    return false;
}

INTERVAL operator ^ (CONST INTERVAL & A, INT power){
    INTERVAL r;
    switch(power){
        case 1:
            r = A;
            break;
        case 2:
            BiasSqr(Bias(r),Bias(A));
            break;
        default:
            BiasPowerN(Bias(r), Bias(A),power);
    }
    return r;
}