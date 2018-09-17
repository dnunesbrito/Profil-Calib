/************************************************************************
 *
 * Implementation of type INTERVAL_VECTOR
 * --------------------------------------
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
 * $Id: IntervalVector.C 478 2006-08-09 13:13:30Z keil $
 *
 ************************************************************************/

static const char rcs_id[] = "$Id: IntervalVector.C 478 2006-08-09 13:13:30Z keil $";

#include <IntervalVector.h>
#include <Functions.h>
#include <BIAS/BiasF.h>
#include <string.h>
#include <cmath>

#include "Constants.h"
#include "BIAS/BiasFExt.hpp"

INTERVAL_VECTOR::INTERVAL_VECTOR(CONST INTERVAL_VECTOR & x)
{
#ifdef __DONTCOPY__
  IsTemporary = 1;
  nElements = x.nElements;
  if (x.IsTemporary) {
    theElements = x.theElements;
    *((BIASINTERVAL **) & x.theElements) = NULL;
    *((INT *) & x.nElements) = 0;
  }
  else {
    theElements = new BIASINTERVAL[nElements];
    CheckMemory (theElements);
    memcpy (theElements, x.theElements, nElements * sizeof (BIASINTERVAL));
  }
#else
  nElements = x.nElements;
  theElements = new BIASINTERVAL[nElements];
  CheckMemory (theElements);
  memcpy (theElements, x.theElements, nElements * sizeof (BIASINTERVAL));
#endif
}
INTERVAL_VECTOR::INTERVAL_VECTOR (INT nElements,std::initializer_list<INTERVAL> IN)
{
    this->nElements = nElements;
    theElements = new BIASINTERVAL[nElements];
    if (nElements!=IN.size()) return;
    else
    {
        initializer_list<INTERVAL>::iterator i=IN.begin();
        INT k=0;
        for (i=IN.begin();i!=IN.end();i++) memcpy (&theElements[k++], &(*i).ival, sizeof (BIASINTERVAL));
    }    
}
VOID INTERVAL_VECTOR::vcat(const INTERVAL_VECTOR& src) {
    if(theElements == NULL){
        theElements = new BIASINTERVAL[src.nElements];
        CheckMemory(theElements);
        nElements = src.nElements;
        memcpy(theElements,src.theElements,nElements*sizeof(BIASINTERVAL));
    }else{
        BIASINTERVAL *tmpElements;
        tmpElements = new BIASINTERVAL[nElements];
        CheckMemory(tmpElements);
        memcpy(tmpElements,theElements,nElements*sizeof(BIASINTERVAL));
        theElements = new BIASINTERVAL[nElements+src.nElements];
        memcpy(theElements,tmpElements,nElements*sizeof(BIASINTERVAL));
        memcpy((theElements+nElements),src.theElements,src.nElements*sizeof(BIASINTERVAL));
        nElements += src.nElements;
        delete [] tmpElements;
    }
}
INTERVAL_VECTOR & INTERVAL_VECTOR::operator = (CONST INTERVAL_VECTOR & x)
{
#ifdef __DONTCOPY__
  if (x.IsTemporary) {
    if (theElements != NULL) delete [] theElements;
    theElements = x.theElements;
    nElements = x.nElements;
    ((INTERVAL_VECTOR &) x).theElements = NULL;
    ((INTERVAL_VECTOR &) x).nElements = 0;
  }
  else {
    if (theElements == NULL) {
      theElements = new BIASINTERVAL[x.nElements];
      CheckMemory (theElements);
      nElements = x.nElements;
    }
    else CheckDimensions (*this, x);
    memcpy (theElements, x.theElements, nElements * sizeof (BIASINTERVAL));
  }
#else
  if (theElements == NULL) {
    theElements = new BIASINTERVAL[x.nElements];
    CheckMemory (theElements);
    nElements = x.nElements;
  }
  else CheckDimensions (*this, x);
  memcpy (theElements, x.theElements, nElements * sizeof (BIASINTERVAL));
#endif
  return *this;
}


// Because the appropiate routines are missing in Bias, a temporary
// variable is needed for +=, -=, *=, /=.

INTERVAL_VECTOR & INTERVAL_VECTOR::operator += (CONST INTERVAL_VECTOR & x)
{
  INT dim = Dimension (x);
  INTERVAL_VECTOR t(dim);

  CheckDimensions (*this, x);
  MakeTemporary (t);
  BiasAddVIVI (t.theElements, theElements, x.theElements, dim);
  *this = t; return *this;
}

INTERVAL_VECTOR & INTERVAL_VECTOR::operator -= (CONST INTERVAL_VECTOR & x)
{
  INT dim = Dimension (x);
  INTERVAL_VECTOR t(dim);

  CheckDimensions (*this, x);
  MakeTemporary (t);
  BiasSubVIVI (t.theElements, theElements, x.theElements, dim);
  *this = t; return *this;
}

INTERVAL_VECTOR & INTERVAL_VECTOR::operator *= (CONST INTERVAL & x)
{
  INT dim = Dimension (*this);
  INTERVAL_VECTOR t(dim);

  MakeTemporary (t);
  BiasMulIVI (t.theElements, Bias (x), theElements, dim);
  *this = t; return *this;
}

INTERVAL_VECTOR & INTERVAL_VECTOR::operator /= (CONST INTERVAL & x)
{
  INT dim = Dimension (*this);
  INTERVAL_VECTOR t(dim);

  MakeTemporary (t);
  BiasDivVII (t.theElements, theElements, Bias (x), dim);
  *this = t; return *this;
}

INTERVAL_VECTOR & INTERVAL_VECTOR::operator = (CONST VECTOR & x)
{
  INT i;
  REAL *px = x.theElements;
  BIASINTERVAL *pt;

  if (theElements == NULL) {
    theElements = new BIASINTERVAL[Dimension (x)];
    CheckMemory (theElements);
    nElements = Dimension (x);
  }
  else CheckDimensions (*this, x);
  pt = theElements;
  for (i = 0; i < nElements; i++) BiasHullR (pt++, px++);
  return *this;
}

INTERVAL_VECTOR & INTERVAL_VECTOR::operator += (CONST VECTOR & x)
{
  INT dim = Dimension (x);
  INTERVAL_VECTOR t(dim);

  CheckDimensions (*this, x);
  MakeTemporary (t);
  BiasAddVIVR (t.theElements, theElements, x.theElements, dim);
  *this = t; return *this;
}

INTERVAL_VECTOR & INTERVAL_VECTOR::operator -= (CONST VECTOR & x)
{
  INT dim = Dimension (x);
  INTERVAL_VECTOR t(dim);

  CheckDimensions (*this, x);
  MakeTemporary (t);
  BiasSubVIVR (t.theElements, theElements, x.theElements, dim);
  *this = t; return *this;
}

INTERVAL_VECTOR & INTERVAL_VECTOR::operator *= (REAL x)
{
  INT dim = Dimension (*this);
  INTERVAL_VECTOR t(dim);

  MakeTemporary (t);
  BiasMulRVI (t.theElements, & x, theElements, dim);
  *this = t; return *this;
}

INTERVAL_VECTOR & INTERVAL_VECTOR::operator /= (REAL x)
{
  INT dim = Dimension (*this);
  INTERVAL_VECTOR t(dim);

  MakeTemporary (t);
  BiasDivVIR (t.theElements, theElements, & x, dim);
  *this = t; return *this;
}

VOID INTERVAL_VECTOR::Delete(){
    if(theElements != NULL){
        delete [] theElements;
        theElements = NULL;
        nElements = 0;
    }
}
VOID INTERVAL_VECTOR::clear(){
    if(theElements != NULL){
        delete [] theElements;
        theElements = NULL;
        nElements = 0;
    }
}


INTERVAL_VECTOR INTERVAL_VECTOR::Box(INT iniRow, INT endRow) CONST{
  INTERVAL_VECTOR out;
  if (theElements == NULL) return out;
  Resize(out,endRow-iniRow+1);
  memcpy (out.theElements,&theElements[iniRow-1],  (endRow-iniRow+1) * sizeof (BIASINTERVAL));
  return out;    
}

bool INTERVAL_VECTOR::hasNan(){
    for(INT i = 0;i < nElements;i++){
        if(std::isnan(theElements[i].inf))return true;
        if(std::isnan(theElements[i].sup))return true;
    }
    return false;
}
bool INTERVAL_VECTOR::hasInf(){
    for(INT i = 0;i < nElements;i++){
        if(std::isinf(theElements[i].inf))return true;
        if(std::isinf(theElements[i].sup))return true;
    }
    return false;
}

REAL INTERVAL_VECTOR::max(){
    REAL MaxVal = -INFINITY;
    for(int i = 0;i < nElements;i++){
        if(std::abs(theElements[i].sup) > MaxVal){
            MaxVal = std::abs(theElements[i].sup);
        }
        if(std::abs(theElements[i].inf) > MaxVal){
            MaxVal = std::abs(theElements[i].inf);
        }
    }
    return MaxVal;
}

REAL INTERVAL_VECTOR::min(){
    REAL MinVal = Machine::PosInfinity;
    for(int i = 0;i < nElements;i++){
        if(std::abs(theElements[i].inf) < MinVal){
            MinVal = std::abs(theElements[i].inf);
        }
        if(std::abs(theElements[i].sup) < MinVal){
            MinVal = std::abs(theElements[i].sup);
        }
    }
    return MinVal;
}

INT INTERVAL_VECTOR::maxID(){
    REAL MaxVal = -INFINITY;
    INT MaxID;
    for(int i = 0;i < nElements;i++){
        if(std::abs(theElements[i].sup) > MaxVal){
            MaxVal = std::abs(theElements[i].sup);
            MaxID = i;
        }
        if(std::abs(theElements[i].inf) > MaxVal){
            MaxVal = std::abs(theElements[i].inf);
            MaxID = i;
        }
    }
    return MaxVal;
}

REAL INTERVAL_VECTOR::maxdiam(){
    REAL MaxDiam = Machine::NegInfinity;
    for(int i = 0;i < nElements;i++)
        if(Diam(theElements[i]) > MaxDiam)
            MaxDiam = Diam(theElements[i]);
}
std::string INTERVAL_VECTOR::fomatedprinter(const std::string& format){
    INT i;
    BIASINTERVAL *px = theElements;
    INTERVAL iv;
    std::string os;
    if(strcmp(format.c_str(),"BIAS") == 0){
        os = '(';
        for (i = 0; i < nElements; i++, px++) {
          *(Bias(iv)) = *px;
          os += "[" + to_string(iv.inf()) + "," + to_string(iv.sup()) + "]";
          if (i < nElements - 1) os += " ; ";
        }
        os += ')';
    }
    if(strcmp(format.c_str(),"CSV") == 0){
        for (i = 0; i < nElements; i++, px++) {
          *(Bias(iv)) = *px;
          os += to_string(iv.inf()) + "," + to_string(iv.sup());
          if (i < nElements - 1) os += ",";
        }
    }
    if(strcmp(format.c_str(),"MATLAB") == 0){
        os = '(';
        for (i = 0; i < nElements; i++, px++) {
          *(Bias(iv)) = *px;
          os += to_string(iv.inf()) + "," + to_string(iv.sup());
          if (i < nElements - 1) os + " ; ";
        }
        os + ')';
    }
    return os;
}

VOID Resize (INTERVAL_VECTOR & x, INT n)
{
  CheckVectorRange (n);
  if (n && (x.nElements == n)) return;
  if (x.theElements != NULL) delete [] x.theElements;
  x.nElements = n;
  if (n != 0) {
    x.theElements = new BIASINTERVAL[n];
    CheckMemory (x.theElements);
  }
  else x.theElements = NULL;
}

INTERVAL_VECTOR operator - (CONST INTERVAL_VECTOR & a)
{
  INT dim = Dimension (a);
  INTERVAL_VECTOR t (dim);

  MakeTemporary (t);
  BiasNegV (t.theElements, a.theElements, dim);
  return t;
}

INTERVAL_VECTOR Hull (CONST VECTOR & a)
{
  INT dim = Dimension (a);
  INTERVAL_VECTOR t (dim);

  MakeTemporary (t);
  BiasHullVR (t.theElements, a.theElements, dim);
  return t;
}

INTERVAL_VECTOR Hull (CONST VECTOR & a, CONST VECTOR & b)
{
  INT dim = Dimension (a);
  INTERVAL_VECTOR t (dim);

  CheckDimensions (a, b);
  MakeTemporary (t);
  BiasHullVRVR (t.theElements, a.theElements, b.theElements, dim);
  return t;
}

INTERVAL_VECTOR Hull (CONST VECTOR & a, CONST INTERVAL_VECTOR & b)
{
  INT dim = Dimension (a);
  INTERVAL_VECTOR t (dim);

  CheckDimensions (a, b);
  MakeTemporary (t);
  BiasHullVRVI (t.theElements, a.theElements, b.theElements, dim);
  return t;
}

INTERVAL_VECTOR Hull (CONST INTERVAL_VECTOR & a, CONST VECTOR & b)
{
  INT dim = Dimension (a);
  INTERVAL_VECTOR t (dim);

  CheckDimensions (a, b);
  MakeTemporary (t);
  BiasHullVIVR (t.theElements, a.theElements, b.theElements, dim);
  return t;
}

INTERVAL_VECTOR Hull (CONST INTERVAL_VECTOR & a, CONST INTERVAL_VECTOR & b)
{
  INT dim = Dimension (a);
  INTERVAL_VECTOR t (dim);

  CheckDimensions (a, b);
  MakeTemporary (t);
  BiasHullVIVI (t.theElements, a.theElements, b.theElements, dim);
  return t;
}

INTERVAL_VECTOR AddBounds (CONST VECTOR & a, CONST VECTOR & b)
{
  INT dim = Dimension (a);
  INTERVAL_VECTOR t (dim);

  CheckDimensions (a, b);
  MakeTemporary (t);
  BiasAddVRVR (t.theElements, a.theElements, b.theElements, dim);
  return t;
}

INTERVAL_VECTOR operator + (CONST VECTOR & a, CONST INTERVAL_VECTOR & b)
{
  INT dim = Dimension (a);
  INTERVAL_VECTOR t (dim);

  CheckDimensions (a, b);
  MakeTemporary (t);
  BiasAddVRVI (t.theElements, a.theElements, b.theElements, dim);
  return t;
}

INTERVAL_VECTOR operator + (CONST INTERVAL_VECTOR & a, CONST VECTOR & b)
{
  INT dim = Dimension (a);
  INTERVAL_VECTOR t (dim);

  CheckDimensions (a, b);
  MakeTemporary (t);
  BiasAddVIVR (t.theElements, a.theElements, b.theElements, dim);
  return t;
}

INTERVAL_VECTOR operator + (CONST INTERVAL_VECTOR & a, CONST INTERVAL_VECTOR & b)
{
  INT dim = Dimension (a);
  INTERVAL_VECTOR t (dim);

  CheckDimensions (a, b);
  MakeTemporary (t);
  BiasAddVIVI (t.theElements, a.theElements, b.theElements, dim);
  return t;
}

INTERVAL_VECTOR SubBounds (CONST VECTOR & a, CONST VECTOR & b)
{
  INT dim = Dimension (a);
  INTERVAL_VECTOR t (dim);

  CheckDimensions (a, b);
  MakeTemporary (t);
  BiasSubVRVR (t.theElements, a.theElements, b.theElements, dim);
  return t;
}

INTERVAL_VECTOR operator - (CONST VECTOR & a, CONST INTERVAL_VECTOR & b)
{
  INT dim = Dimension (a);
  INTERVAL_VECTOR t (dim);

  CheckDimensions (a, b);
  MakeTemporary (t);
  BiasSubVRVI (t.theElements, a.theElements, b.theElements, dim);
  return t;
}

INTERVAL_VECTOR operator - (CONST INTERVAL_VECTOR & a, CONST VECTOR & b)
{
  INT dim = Dimension (a);
  INTERVAL_VECTOR t (dim);

  CheckDimensions (a, b);
  MakeTemporary (t);
  BiasSubVIVR (t.theElements, a.theElements, b.theElements, dim);
  return t;
}

INTERVAL_VECTOR operator - (CONST INTERVAL_VECTOR & a, CONST INTERVAL_VECTOR & b)
{
  INT dim = Dimension (a);
  INTERVAL_VECTOR t (dim);

  CheckDimensions (a, b);
  MakeTemporary (t);
  BiasSubVIVI (t.theElements, a.theElements, b.theElements, dim);
  return t;
}

INTERVAL_VECTOR MulBounds (REAL a, CONST VECTOR & b)
{
  INT dim = Dimension (b);
  INTERVAL_VECTOR t (dim);

  MakeTemporary (t);
  BiasMulRVR (t.theElements, &a, b.theElements, dim);
  return t;
}

INTERVAL_VECTOR operator * (REAL a, CONST INTERVAL_VECTOR & b)
{
  INT dim = Dimension (b);
  INTERVAL_VECTOR t (dim);

  MakeTemporary (t);
  BiasMulRVI (t.theElements, &a, b.theElements, dim);
  return t;
}

INTERVAL_VECTOR operator * (CONST INTERVAL & a, CONST VECTOR & b)
{
  INT dim = Dimension (b);
  INTERVAL_VECTOR t (dim);

  MakeTemporary (t);
  BiasMulIVR (t.theElements, Bias (a), b.theElements, dim);
  return t;
}

INTERVAL_VECTOR operator * (CONST INTERVAL & a, CONST INTERVAL_VECTOR & b)
{
  INT dim = Dimension (b);
  INTERVAL_VECTOR t (dim);

  MakeTemporary (t);
  BiasMulIVI (t.theElements, Bias (a), b.theElements, dim);
  return t;
}

INTERVAL_VECTOR DivBounds (CONST VECTOR & a, REAL b)
{
  INT dim = Dimension (a);
  INTERVAL_VECTOR t (dim);

  MakeTemporary (t);
  BiasDivVRR (t.theElements, a.theElements, &b, dim);
  return t;
}

INTERVAL_VECTOR operator / (CONST VECTOR & a, CONST INTERVAL & b)
{
  INT dim = Dimension (a);
  INTERVAL_VECTOR t (dim);

  MakeTemporary (t);
  BiasDivVRI (t.theElements, a.theElements, Bias (b), dim);
  return t;
}

INTERVAL_VECTOR operator / (CONST INTERVAL_VECTOR & a, REAL b)
{
  INT dim = Dimension (a);
  INTERVAL_VECTOR t (dim);

  MakeTemporary (t);
  BiasDivVIR (t.theElements, a.theElements, &b, dim);
  return t;
}

INTERVAL_VECTOR operator / (CONST INTERVAL_VECTOR & a, CONST INTERVAL & b)
{
  INT dim = Dimension (a);
  INTERVAL_VECTOR t (dim);

  MakeTemporary (t);
  BiasDivVII (t.theElements, a.theElements, Bias (b), dim);
  return t;
}

INTERVAL operator * (CONST VECTOR & a, CONST INTERVAL_VECTOR & b)
{
  INT dim = Dimension (a);
  INTERVAL t;

  CheckDimensions (a, b);
  BiasMacVRVI (Bias (t), a.theElements, b.theElements, dim);
  return t;
}

INTERVAL operator * (CONST INTERVAL_VECTOR & a, CONST VECTOR & b)
{
  INT dim = Dimension (a);
  INTERVAL t;

  CheckDimensions (a, b);
  BiasMacVIVR (Bias (t), a.theElements, b.theElements, dim);
  return t;
}

INTERVAL operator * (CONST INTERVAL_VECTOR & a, CONST INTERVAL_VECTOR & b)
{
  INT dim = Dimension (a);
  INTERVAL t;

  CheckDimensions (a, b);
  BiasMacVIVI (Bias (t), a.theElements, b.theElements, dim);
  return t;
}

INTERVAL MulBounds (CONST VECTOR & a, CONST VECTOR & b)
{
  INT dim = Dimension (a);
  INTERVAL t;

  CheckDimensions (a, b);
  BiasMacVRVR (Bias (t), a.theElements, b.theElements, dim);
  return t;
}

VECTOR Inf (CONST INTERVAL_VECTOR & a)
{
  INT dim = Dimension (a);
  VECTOR t (dim);

  MakeTemporary (t);
  BiasInfV (t.theElements, a.theElements, dim);
  return t;
}

VECTOR Sup (CONST INTERVAL_VECTOR & a)
{
  INT dim = Dimension (a);
  VECTOR t (dim);

  MakeTemporary (t);
  BiasSupV (t.theElements, a.theElements, dim);
  return t;
}

VECTOR Mid (CONST INTERVAL_VECTOR & a)
{
  INT dim = Dimension (a);
  VECTOR t (dim);

  MakeTemporary (t);
  BiasMidV (t.theElements, a.theElements, dim);
  return t;
}

VECTOR Diam (CONST INTERVAL_VECTOR & a)
{
  INT dim = Dimension (a);
  VECTOR t (dim);

  MakeTemporary (t);
  BiasDiamV (t.theElements, a.theElements, dim);
  return t;
}

VECTOR Abs (CONST INTERVAL_VECTOR & a)
{
  INT dim = Dimension (a);
  VECTOR t (dim);

  MakeTemporary (t);
  BiasAbsV (t.theElements, a.theElements, dim);
  return t;
}

INT Intersection (INTERVAL_VECTOR & r, CONST INTERVAL_VECTOR & a, CONST INTERVAL_VECTOR & b)
{
  INT dim = Dimension (a);

  CheckDimensions (a, b);
  if (r.theElements == NULL) Resize (r, dim);
  else CheckDimensions (a, r);
  return BiasIntersectionV (r.theElements, a.theElements, b.theElements, dim);
}

VOID Clear (INTERVAL_VECTOR & a)
{
  if (a.theElements != NULL)
    memset (a.theElements, 0, Dimension (a) * sizeof (BIASINTERVAL));
}

VOID Initialize (INTERVAL_VECTOR & a, CONST INTERVAL & b)
{
  INT i;
  BIASINTERVAL *pa = a.theElements;
  CONST BIASINTERVAL *pr = Bias (b);

  for (i = 0; i < Dimension (a); i++) *(pa++) = *pr;
}

INT operator <= (CONST VECTOR & a, CONST INTERVAL_VECTOR & b)
{
  CheckDimensions (a, b);
  return BiasInVR (a.theElements, b.theElements, Dimension (a));
}

INT operator <= (CONST INTERVAL_VECTOR & a, CONST INTERVAL_VECTOR & b)
{
  CheckDimensions (a, b);
  return BiasInVI (a.theElements, b.theElements, Dimension (a));
}

INT operator < (CONST VECTOR & a, CONST INTERVAL_VECTOR & b)
{
  CheckDimensions (a, b);
  return BiasInInteriorVR (a.theElements, b.theElements, Dimension (a));
}

INT operator < (CONST INTERVAL_VECTOR & a, CONST INTERVAL_VECTOR & b)
{
  CheckDimensions (a, b);
  return BiasInInteriorVI (a.theElements, b.theElements, Dimension (a));
}

INT operator == (CONST INTERVAL_VECTOR & a, CONST INTERVAL_VECTOR & b)
{
  CheckDimensions (a, b);
  return BiasIsEqualV (a.theElements, b.theElements, Dimension (a));
}

INT operator != (CONST INTERVAL_VECTOR & a, CONST INTERVAL_VECTOR & b)
{
  CheckDimensions (a, b);
  return !BiasIsEqualV (a.theElements, b.theElements, Dimension (a));
}

INTERVAL Sqr (CONST INTERVAL_VECTOR & x)
// Calculates  Sum_i (x_i^2)
{
  INT i;
  INT dim = Dimension (x);
  BIASINTERVAL *px = x.theElements;
  INTERVAL sum, tmp;

  sum = 0.0;
  for (i = 0; i < dim; i++) {
    BiasSqr (Bias (tmp), px++);
    sum += tmp;
  }
  return sum;
}

INTERVAL Norm (CONST INTERVAL_VECTOR & x)
{
  return Sqrt (Sqr (x));
}

VOID GetNonHomogeneous(INTERVAL_VECTOR& dst,CONST INTERVAL_VECTOR& src){
    INTERVAL_VECTOR tmpsrc;
    tmpsrc = src;
    Resize(dst,Dimension(tmpsrc)-1);
    if(0.0 <= src(Dimension(src))){
        Initialize(dst,NAN);
    }
    REAL tmpInf,tmpSup;
    tmpInf = Inf(tmpsrc(Dimension(tmpsrc)));
    tmpSup = Sup(tmpsrc(Dimension(tmpsrc)));
    for(int i = 1;i <= Dimension(dst);i++){
        dst(i) = Hull(tmpsrc(i)/tmpInf,tmpsrc(i)/tmpSup);
    }
}
VOID GetHomogeneous(INTERVAL_VECTOR& dst,CONST INTERVAL_VECTOR& src){
    INTERVAL_VECTOR tmpsrc;
    tmpsrc = src;
    Resize(dst,Dimension(tmpsrc)+1);
    INT i;
    for(i = 1;i <= Dimension(tmpsrc);i++)
        dst(i) = tmpsrc(i);
    dst(i)=Constant::UM;
}
ostream & operator << (ostream & os, CONST INTERVAL_VECTOR & x)
{
  INT i;
  INT dim = Dimension (x);
  BIASINTERVAL *px = x.theElements;
  INTERVAL iv;

  os << '(';
  for (i = 0; i < dim; i++, px++) {
    *(Bias(iv)) = *px;
    os << iv;
    if (i < dim - 1) os << " ; ";
  }
  return os << ')';
}

istream & operator >> (istream & is, INTERVAL_VECTOR & x)
{
  INT i;
  INT dim = Dimension (x);
  BIASINTERVAL *px = x.theElements;
  INTERVAL iv;

  for (i = 0; i < dim; i++) {
    is >> iv;
    *(px++) = *(Bias(iv));
  }
  return is;
}
VOID PointwiseMul(INTERVAL_VECTOR & dst,const INTERVAL_VECTOR src1,CONST INTERVAL_VECTOR src2){
    CheckDimensions(src1,src2);
    Resize(dst,Dimension(src1));
    for(int i = 1;i <= Dimension(src1);i++)
        dst(i) = src1(i)*src2(i);
}
VOID PointwiseDiv(INTERVAL_VECTOR & dst,const INTERVAL_VECTOR src1,CONST INTERVAL_VECTOR src2){
    CheckDimensions(src1,src2);
    Resize(dst,Dimension(src1));
    for(int i = 1;i <= Dimension(src1);i++)
        dst(i) = src1(i)/src2(i);    
}
VOID Sum(INTERVAL& dst,CONST INTERVAL_VECTOR src){
    dst = INTERVAL(0);
    for(int i = 1;i <= Dimension(src);i++)
        dst += src(i);
}
INTERVAL_VECTOR Cross(CONST INTERVAL_VECTOR& V,CONST INTERVAL_VECTOR& W){
    INTERVAL_VECTOR out;
    if(Dimension(V) != 3 || Dimension(W) != 3){
        cerr << "Vectors must be threedimensional" << endl;
        return out;
    }
    Resize(out,3);
    out(1) = V(2)*W(3)-V(3)*W(2);
    out(2) = -(V(1)*W(3)-V(3)*W(1));
    out(3) = V(1)*W(2)-V(2)*W(1);
    return out;
}
bool AnyNAN(CONST INTERVAL_VECTOR & src){
    for(INT i = 0;i < src.nElements;i++)
        if(std::isnan(src.theElements[i].inf) || std::isnan(src.theElements[i].sup))return true;
    return false;
}
VECTOR INTERVAL_VECTOR::diam(){
  VECTOR t (nElements);

  MakeTemporary (t);
  BiasDiamV (t.theElements, theElements, nElements);
  return t;
}
INTERVAL_VECTOR INTERVAL_VECTOR::pointwisesqr(){
    INTERVAL_VECTOR out(nElements);
    BIASINTERVAL pR;
    for(int i = 0;i < nElements;i++){
        BiasSqr(&pR,&theElements[i]);
        out.theElements[i] = pR;
    }
    return out;
}