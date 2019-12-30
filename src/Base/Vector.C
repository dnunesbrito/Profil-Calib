/************************************************************************
 *
 * Implementation of type VECTOR
 * -----------------------------
 *
 * Copyright (C) 1993, 1997 Olaf Knueppel
 *               2005, 2009 Christian Keil
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
 * $Id: Vector.C 592 2009-01-28 10:04:19Z christian $
 *
 ************************************************************************/

static const char rcs_id[] = "$Id: Vector.C 592 2009-01-28 10:04:19Z christian $";

#include <RealOp.h>
#include <memory.h>
#include <stdlib.h>
#include <math.h>
#include "Constants.h"
#include "IntegerMatrix.h"
#include <Vector.h>

VECTOR::VECTOR(CONST VECTOR & x)
{
#ifdef __DONTCOPY__
  IsTemporary = 1;
  nElements = x.nElements;
  if (x.IsTemporary) {
    theElements = x.theElements;
    *((REAL **) & x.theElements) = NULL;
    *((INT *) & x.nElements) = 0;
  }
  else {
    theElements = new REAL[nElements];
    CheckMemory (theElements);
    memcpy (theElements, x.theElements, nElements * sizeof (REAL));
  }
#else
  nElements = x.nElements;
  theElements = new REAL[nElements];
  CheckMemory (theElements);
  memcpy (theElements, x.theElements, nElements * sizeof (REAL));
#endif
}

VECTOR::VECTOR (INT nElement,std::initializer_list<REAL> IN)
{
    nElements = nElement;
    theElements = new REAL[nElements];
    if (nElements!=IN.size()) return;
    else
    {
        initializer_list<REAL>::iterator i=IN.begin();
        INT k=0;
        for (i=IN.begin();i!=IN.end();i++) theElements[k++]=(*i);
    }
}
VECTOR & VECTOR::operator = (CONST VECTOR & x)
{
#ifdef __DONTCOPY__
  if (x.IsTemporary) {
    if (theElements != NULL) delete [] theElements;
    theElements = x.theElements;
    nElements = x.nElements;
    ((VECTOR &) x).theElements = NULL;
    ((VECTOR &) x).nElements = 0;
  }
  else {
    if (theElements == NULL) {
      theElements = new REAL[x.nElements];
      CheckMemory (theElements);
      nElements = x.nElements;
    }
    else CheckDimensions (*this, x);
    memcpy (theElements, x.theElements, nElements * sizeof (REAL));
  }
#else
  if (theElements == NULL) {
    theElements = new REAL[x.nElements];
    CheckMemory (theElements);
    nElements = x.nElements;
  }
  else CheckDimensions (*this, x);
  memcpy (theElements, x.theElements, nElements * sizeof (REAL));
#endif
  return *this;
}

VECTOR & VECTOR::operator += (CONST VECTOR & x)
{
  CheckDimensions (*this, x);
  RealOpAddTo (theElements, x.theElements, Dimension (x));
  return *this;
}

VECTOR & VECTOR::operator -= (CONST VECTOR & x)
{
  CheckDimensions (*this, x);
  RealOpSubFrom (theElements, x.theElements, Dimension (x));
  return *this;
}

VECTOR & VECTOR::operator *= (REAL a)
{
  RealOpMulWith (theElements, a, Dimension (*this));
  return *this;
}

VECTOR & VECTOR::operator /= (REAL a)
{
  RealOpDivBy (theElements, a, Dimension (*this));
  return *this;
}
INT VECTOR::maxID(){
  INT i,id=1;
  REAL *px;
  REAL m;
  
  if (nElements == 0) Error ("Illegal Dimension in Max()", 1, ErrorHandler::Warning);
  px = theElements;
  m = *(px++);
  for (i = 1; i < nElements; i++, px++){
    if (*px > m){
        m = *px;
        id = i+1;
    }
  }
  return id;    
}
REAL VECTOR::Min(){
    REAL min = Machine::PosInfinity;
    for(int i = 0;i < nElements;i++)
        if(theElements[1] < min)
            min = theElements[i];
    return min;
}

VOID VECTOR::print(const string& name,CONST Iformat& format){
    if(format == Iformat::MATLAB){
        cout << name << "= [";
        for(int i = 0;i < nElements;i++){
                cout << theElements[i];
                if(i < nElements-1)
                    cout << ";" << endl;
        }
        cout << "];" << endl;
    }
}
VECTOR VECTOR::Box(INT iniRow, INT endRow){
  VECTOR out;
  if (theElements == NULL) return out;
  Resize(out,endRow-iniRow+1);
  memcpy (out.theElements,&theElements[iniRow-1],  (endRow-iniRow+1) * sizeof (REAL));
  return out;    

}
REAL VECTOR::max(){
    REAL MaxVal = -INFINITY;
    for(int i = 0;i < nElements;i++){
        if(theElements[i] > MaxVal){
            MaxVal = theElements[i];
        }
    }
    return MaxVal;
}
VOID VECTOR::setzeros(){
    for(int i = 0;i < nElements;i++)
        theElements[i] = 0;
}
INTEGER_VECTOR VECTOR::sort(char order){
    REAL swap;
    INTEGER_VECTOR Idxs(nElements);
    Clear(Idxs);
    for (INT c = 0 ; c < ( nElements - 1 ); c++){
        for (INT d = 0 ; d < nElements - c - 1; d++){
            if(order == 'd'){
                if (theElements[d] < theElements[d+1]){ /* For decreasing order use < */
                    swap       = theElements[d];
                    theElements[d]   = theElements[d+1];
                    theElements[d+1] = swap;
                    if(Idxs(d+1) == 0){
                        Idxs(d+1) = d + 2;
                        Idxs(d+2) = d + 1;
                    }else{
                        INT tmpIdx = d+2;
                        if(Idxs(d+2) != 0)
                            tmpIdx = Idxs(d+2);
                        Idxs(d+2) = Idxs(d+1);
                        Idxs(d+1) = tmpIdx;
                    }
                }else{
                    if(Idxs(d+1) == 0)
                        Idxs(d+1) = d + 1;
                    if(Idxs(d+2) == 0)
                        Idxs(d+2) = d + 2;
                }
            }
            if(order == 'c'){
                if (theElements[d+1] < theElements[d]){ /* For increasing order use < */
                    swap = theElements[d];
                    theElements[d] = theElements[d+1];
                    theElements[d+1] = swap;
                    if(Idxs(d+1) == 0){
                        Idxs(d+1) = d + 2;
                        Idxs(d+2) = d + 1;
                    }else{
                        INT tmpIdx = d+2;
                        if(Idxs(d+2) != 0)
                            tmpIdx = Idxs(d+2);
                        Idxs(d+2) = Idxs(d+1);
                        Idxs(d+1) = tmpIdx;
                    }
                }else{
                    if(Idxs(d+1) == 0 && Idxs(d+2) == 0){
                        Idxs(d+1) = d + 1;
                        Idxs(d+2) = d + 2;
                    }
                }
            }
        }
    }
    return Idxs;
}
VOID Resize (VECTOR & x, INT n)
{
  CheckVectorRange (n);
  if (n && (x.nElements == n)) return;
  if (x.theElements != NULL) delete [] x.theElements;
  x.nElements = n;
  if (n != 0) {
    x.theElements = new REAL[n];
    CheckMemory (x.theElements);
  }
  else x.theElements = NULL;
}

VECTOR operator - (CONST VECTOR & a)
{
  INT dim = Dimension (a);
  VECTOR t (dim);

  MakeTemporary (t);
  RealOpNeg (t.theElements, a.theElements, dim);
  return t;
}

VECTOR operator + (CONST VECTOR & a, CONST VECTOR & b)
{
  INT dim = Dimension (a);
  VECTOR t (dim);

  CheckDimensions (a, b);
  MakeTemporary (t);
  RealOpAdd (t.theElements, a.theElements, b.theElements, dim);
  return t;
}

VECTOR operator - (CONST VECTOR & a, CONST VECTOR & b)
{
  INT dim = Dimension (a);
  VECTOR t (dim);

  CheckDimensions (a, b);
  MakeTemporary (t);
  RealOpSub (t.theElements, a.theElements, b.theElements, dim);
  return t;
}

VECTOR operator * (REAL a, CONST VECTOR & b)
{
  INT dim = Dimension (b);
  VECTOR t (dim);

  MakeTemporary (t);
  RealOpMul (t.theElements, a, b.theElements, dim);
  return t;
}

VECTOR operator / (CONST VECTOR & a, REAL b)
{
  INT dim = Dimension (a);
  VECTOR t (dim);

  MakeTemporary (t);
  RealOpDiv (t.theElements, a.theElements, b, dim);
  return t;
}

REAL operator * (CONST VECTOR & a, CONST VECTOR & b)
{
  CheckDimensions (a, b);
  return RealOpScalp (a.theElements, b.theElements, Dimension (a));
}

INT operator < (CONST VECTOR & a, CONST VECTOR & b)
{
  CheckDimensions (a, b);
  return RealOpLessThan (a.theElements, b.theElements, Dimension (a));
}

INT operator <= (CONST VECTOR & a, CONST VECTOR & b)
{
  CheckDimensions (a, b);
  return RealOpLessEqual (a.theElements, b.theElements, Dimension (a));
}

INT operator > (CONST VECTOR & a, CONST VECTOR & b)
{
  CheckDimensions (a, b);
  return RealOpGreaterThan (a.theElements, b.theElements, Dimension (a));
}

INT operator >= (CONST VECTOR & a, CONST VECTOR & b)
{
  CheckDimensions (a, b);
  return RealOpGreaterEqual (a.theElements, b.theElements, Dimension (a));
}

bool operator != (CONST VECTOR& src1,CONST VECTOR& src2){
    if(src1.nElements != src2.nElements)return true;
    for(int i = 0;i < src1.nElements;i++)
        if(src1.theElements[i] != src2.theElements[i])return true;
    return false;
}
VECTOR Abs (CONST VECTOR & a)
// Calculates  |x_i|
{
  INT i;
  INT dim = Dimension (a);
  VECTOR t (dim);
  REAL *pa, *pt;

  MakeTemporary (t);
  pa = a.theElements; pt = t.theElements;
  for (i = 0; i < dim; i++) *(pt++) = fabs(*(pa++));
  return t;
}

REAL Sqr (CONST VECTOR & x)
// Calculates  Sum_i (x_i^2)
{
  return RealOpScalp (x.theElements, x.theElements,
		      Dimension (x));
}

REAL Norm (CONST VECTOR & x)
{
  return sqrt (Sqr (x));
}

REAL Max (CONST VECTOR & x)
{
  INT dim = Dimension (x);
  INT i;
  REAL m;
  REAL *px;

  if (dim == 0) Error ("Illegal Dimension in Max()", 1, ErrorHandler::FatalError);
  px = x.theElements;
  m = *(px++);
  for (i = 1; i < dim; i++, px++)
    if (*px > m) m = *px;
  return m;
}

REAL Min (CONST VECTOR & x)
{
  INT dim = Dimension (x);
  INT i;
  REAL m;
  REAL *px;

  if (dim == 0) Error ("Illegal Dimension in Min()", 1, ErrorHandler::FatalError);
  px = x.theElements;
  m = *(px++);
  for (i = 1; i < dim; i++, px++)
    if (*px < m) m = *px;
  return m;
}

VOID Clear (VECTOR & a)
{
  if (a.theElements != NULL)
    memset (a.theElements, 0, Dimension (a) * sizeof (REAL));
}

VOID Initialize (VECTOR & a, REAL b)
{
  INT i;
  REAL *pa = a.theElements;

  for (i = 0; i < Dimension (a); i++) *(pa++) = b;
}
VOID Sum(REAL& dst,CONST VECTOR& src){
    dst = 0;
    for(int i = 1;i <= Dimension(src);i++)dst+=src(i);
}
VOID Mean(REAL& dst,CONST VECTOR& src){
    Sum(dst,src);
    dst = dst/Dimension(src);
}
ostream & operator << (ostream & os, CONST VECTOR & x)
{
  INT i;
  INT dim = Dimension (x);
  REAL *px = x.theElements;

  os << '(';
  for (i = 0; i < dim; i++) {
    os << (*(px++));
    if (i < dim - 1) os << " ; ";
  }
  return os << ')';
}

istream & operator >> (istream & is, VECTOR & x)
{
  INT i;
  INT dim = Dimension (x);
  REAL *px = x.theElements;

  for (i = 0; i < dim; i++)
    is >> (*(px++));
  return is;
}

// The following code is only used to force Constants.C to be
// always included in the executable code.

extern VOID RegisterConstants ();

VOID RegisterVector () { RegisterConstants (); }

VOID GetNonHomogeneous(VECTOR& dst,CONST VECTOR& src){
    Resize(dst,Dimension(src)-1);
    for(int i = 1;i <= Dimension(dst);i++){
        if(src(Dimension(src)) == 0){
            dst(i) = Machine::PosInfinity;
            continue;
        }
        dst(i) = src(i)/src(Dimension(src));
    }
}
VOID GetHomogeneous(VECTOR& dst,CONST VECTOR& src){
    Resize(dst,Dimension(src)+1);
    INT i;
    for(i = 1;i <= Dimension(src);i++)
        dst(i) = src(i);
    dst(i)=1.0;
}
VOID VECTOR::set(REAL val){
    INT i;
    REAL *pa = theElements;

    for (i = 0; i < nElements; i++) *(pa++) = val;
}