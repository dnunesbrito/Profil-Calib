/************************************************************************
 *
 * Definition of type VECTOR
 * -------------------------
 *
 * Copyright (C) 1993, 1994, 1997 Olaf Knueppel
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
 * $Id: Vector.h 478 2006-08-09 13:13:30Z keil $
 *
 ************************************************************************/


#ifndef __VECTOR__
#define __VECTOR__

#include <Configuration.h>
#include <Error.h>
#include <iostream>
#include <initializer_list>

#include "IntegerVector.h"

using namespace std;

enum Iformat{MATLAB,OCTAVE};

class VECTOR {
  INT nElements;
#ifdef __DONTCOPY__
  INT IsTemporary;
#endif
public:
  REAL *theElements;
  VECTOR ()
    {
#ifdef __DONTCOPY__
      IsTemporary = 0;
#endif
      nElements = 0; theElements = NULL; }
  VECTOR (INT n)
    {
#ifdef __DONTCOPY__
      IsTemporary = 0;
#endif
      CheckVectorRange (n);
      nElements = n;
      theElements = new REAL[n];
      CheckMemory (theElements);
    }
  ~VECTOR ()
    { if (theElements != NULL) delete [] theElements; }
  VECTOR (CONST VECTOR &);
  REAL & operator () (INT i) CONST
    { CheckVectorIndex (i, *this); return theElements[i-1]; }
  VECTOR (INT nElements,std::initializer_list<REAL> IN);
  VECTOR & operator =  (CONST VECTOR &);
  VECTOR & operator += (CONST VECTOR &);
  VECTOR & operator -= (CONST VECTOR &);
  VECTOR & operator *= (REAL);
  VECTOR & operator /= (REAL);
  REAL Min();
  INT maxID();
  REAL max();
  VECTOR Box(INT iniRow, INT endRow);
  VOID print(CONST string& name,CONST Iformat& format = Iformat::MATLAB);
  VOID clear(){if (theElements != NULL) delete [] theElements; theElements = NULL; nElements = 0;}
  INT rows( ) CONST {return nElements;}
  /* Faz todos os valores do vetor igual a val
   o vetor deve ser prealocado anteriormente.*/
  VOID set(REAL val);
  /*Make all vector elements as zero.*/
  VOID setzeros();
  /*Faz o ordenamento em ordem crescente
   ou decrescente dos componentes do vetor.
   Se order igual a c a ordem e crescente.
   Se order igual a d a ordem e decrescente.*/
  INTEGER_VECTOR sort(char order);
  friend INT Dimension (CONST VECTOR &);
  friend VOID Resize (VECTOR &, INT);
  friend VOID MakeTemporary (VECTOR &);
  friend VOID MakePermanent (VECTOR &);
  friend VOID Clear (VECTOR &);
  friend VOID Initialize (VECTOR &, REAL);
  friend VECTOR operator + (CONST VECTOR &);
  friend VECTOR operator - (CONST VECTOR &);
  friend VECTOR operator + (CONST VECTOR &, CONST VECTOR &);
  friend VECTOR operator - (CONST VECTOR &, CONST VECTOR &);
  friend VECTOR operator * (REAL, CONST VECTOR &);
  friend VECTOR operator / (CONST VECTOR &, REAL);
  friend REAL   operator * (CONST VECTOR &, CONST VECTOR &);
  friend INT    operator <  (CONST VECTOR &, CONST VECTOR &);
  friend INT    operator <= (CONST VECTOR &, CONST VECTOR &);
  friend INT    operator >  (CONST VECTOR &, CONST VECTOR &);
  friend INT    operator >= (CONST VECTOR &, CONST VECTOR &);
  friend bool   operator != (CONST VECTOR &, CONST VECTOR &);
  friend VECTOR Abs  (CONST VECTOR &);
  friend REAL   Sqr  (CONST VECTOR &);
  friend REAL   Norm (CONST VECTOR &);
  friend REAL   Max  (CONST VECTOR &);
  friend REAL   Min  (CONST VECTOR &);
  friend VOID Mean(REAL& dst,CONST VECTOR& src);
  friend VOID Sum(REAL& dst,CONST VECTOR& src);
  friend ostream & operator << (ostream &, CONST VECTOR &);
  friend istream & operator >> (istream &, VECTOR &);
  friend VOID GetNonHomogeneous(VECTOR& dst,CONST VECTOR& src);
  friend VOID GetHomogeneous(VECTOR& dst,CONST VECTOR& src);
};

inline INT Dimension (CONST VECTOR & x) {
  return x.nElements; 
}

VOID Resize (VECTOR &, INT);

#ifdef __DONTCOPY__
inline VOID MakeTemporary (VECTOR & x) { 
  x.IsTemporary = 1; 
}

inline VOID MakePermanent (VECTOR & x) { 
  x.IsTemporary = 0; 
}
#else
inline VOID MakeTemporary (VECTOR & x) { }

inline VOID MakePermanent (VECTOR & x) { }
#endif

VOID Clear (VECTOR &);
VOID Initialize (VECTOR &, REAL);

inline VECTOR operator + (CONST VECTOR & a) {
  return (VECTOR &) a; 
}

VECTOR operator - (CONST VECTOR &);
VECTOR operator + (CONST VECTOR &, CONST VECTOR &);
VECTOR operator - (CONST VECTOR &, CONST VECTOR &);
VECTOR operator * (REAL    , CONST VECTOR &);
VECTOR operator / (CONST VECTOR &, REAL    );
REAL   operator * (CONST VECTOR &, CONST VECTOR &);
INT    operator <  (CONST VECTOR &, CONST VECTOR &);
INT    operator <= (CONST VECTOR &, CONST VECTOR &);
INT    operator >  (CONST VECTOR &, CONST VECTOR &);
INT    operator >= (CONST VECTOR &, CONST VECTOR &);
bool   operator != (CONST VECTOR &, CONST VECTOR &);
VECTOR Abs  (CONST VECTOR &);
REAL   Sqr  (CONST VECTOR &);
REAL   Norm (CONST VECTOR &);
REAL   Max  (CONST VECTOR &);
REAL   Min  (CONST VECTOR &);
VOID Mean(REAL& dst,CONST VECTOR& src);
VOID Sum(REAL& dst,CONST VECTOR& src);
ostream & operator << (ostream &, CONST VECTOR &);
istream & operator >> (istream &, VECTOR &);
VOID GetNonHomogeneous(VECTOR& dst,CONST VECTOR& src);
VOID GetHomogeneous(VECTOR& dst,CONST VECTOR& src);

#endif /* __VECTOR__ */
