/************************************************************************
 *
 * Implementation of type INTERVAL_MATRIX
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
 * $Id: IntervalMatrix.C 478 2006-08-09 13:13:30Z keil $
 *
 ************************************************************************/

static const char rcs_id[] = "$Id: IntervalMatrix.C 478 2006-08-09 13:13:30Z keil $";

#include <IntervalMatrix.h>
#include <BIAS/Bias1.h>
#include <BIAS/Bias2.h>
#include <string.h>
#include <Functions.h>
#include <eigen3/Eigen/Core>
#include <Utilities.h>

#include "IntegerVector.h"
#include "Constants.h"


INTERVAL_MATRIX::INTERVAL_MATRIX(CONST INTERVAL_MATRIX & x)
{
#ifdef __DONTCOPY__
  IsTemporary = 1;
  nRows = x.nRows; nCols = x.nCols;
  if (x.IsTemporary) {
    theElements = x.theElements;
    *((BIASINTERVAL **) & x.theElements) = NULL;
    *((INT *) & x.nRows) = 0;
    *((INT *) & x.nCols) = 0;
  }
  else {
    theElements = new BIASINTERVAL[nRows * nCols];
    CheckMemory (theElements);
    memcpy (theElements, x.theElements, nRows * nCols * sizeof (BIASINTERVAL));
  }
#else
  nRows = x.nRows; nCols = x.nCols;
  theElements = new BIASINTERVAL[nRows * nCols];
  CheckMemory (theElements);
  memcpy (theElements, x.theElements, nRows * nCols * sizeof (BIASINTERVAL));
#endif
}
INTERVAL_MATRIX::INTERVAL_MATRIX(CONST INTERVAL_VECTOR & x)
{
#ifdef __DONTCOPY__
  IsTemporary = 1;
  nRows = Dimension(x); nCols = 1;
  if (x.IsTemporary) {
    theElements = x.theElements;
    *((BIASINTERVAL **) & x.theElements) = NULL;
    *((INT *) & Dimension(x)) = 0;
    *((INT *) & 1) = 0;
  }
  else {
    theElements = new BIASINTERVAL[nRows * nCols];
    CheckMemory (theElements);
    memcpy (theElements, x.theElements, nRows * nCols * sizeof (BIASINTERVAL));
  }
#else
  nRows = Dimension(x); nCols = 1;
  theElements = new BIASINTERVAL[nRows * nCols];
  CheckMemory (theElements);
  memcpy (theElements, x.theElements, nRows * nCols * sizeof (BIASINTERVAL));
#endif
}
INTERVAL_MATRIX::INTERVAL_MATRIX (INT nR, INT nC,std::initializer_list<INTERVAL> IN)
{
    nRows = nR;
    nCols = nC;
    theElements = new BIASINTERVAL[nRows * nCols];
    if (nCols*nRows!=IN.size()) return;
    else
    {
        initializer_list<INTERVAL>::iterator i=IN.begin();
        INT k=0;
        for (i=IN.begin();i!=IN.end();i++) memcpy (&theElements[k++], &(*i).ival, sizeof (BIASINTERVAL));
    }
}
INTERVAL_MATRIX & INTERVAL_MATRIX::operator = (CONST INTERVAL_MATRIX & x)
{
#ifdef __DONTCOPY__
  if (x.IsTemporary) {
    if (theElements != NULL) delete [] theElements;
    theElements = x.theElements;
    nRows = x.nRows; nCols = x.nCols;
    ((INTERVAL_MATRIX &) x).theElements = NULL;
    ((INTERVAL_MATRIX &) x).nRows = 0;
    ((INTERVAL_MATRIX &) x).nCols = 0;
  }
  else {
    if (theElements == NULL) {
      theElements = new BIASINTERVAL[x.nRows * x.nCols];
      CheckMemory (theElements);
      nRows = x.nRows; nCols = x.nCols;
    }
    else CheckMatrixDimensions (*this, x);
    memcpy (theElements, x.theElements, nRows * nCols * sizeof (BIASINTERVAL));
  }
#else
  if(theElements != NULL) delete [] theElements;
  theElements = new BIASINTERVAL[x.nRows * x.nCols];
  CheckMemory (theElements);
  nRows = x.nRows; nCols = x.nCols;
  memcpy (theElements, x.theElements, nRows * nCols * sizeof (BIASINTERVAL));
#endif
  return *this;
}

// Because the appropiate routines are missing in Bias, a temporary
// variable is needed for +=, -=, *=, /=.

INTERVAL_MATRIX & INTERVAL_MATRIX::operator += (CONST INTERVAL_MATRIX & x)
{
  INT rows = RowDimension (x);
  INT cols = ColDimension (x);
  INTERVAL_MATRIX t(rows, cols);

  CheckMatrixDimensions (*this, x);
  MakeTemporary (t);
  BiasAddMIMI (t.theElements, theElements, x.theElements, rows, cols);
  *this = t; return *this;
}

INTERVAL_MATRIX & INTERVAL_MATRIX::operator -= (CONST INTERVAL_MATRIX & x)
{
  INT rows = RowDimension (x);
  INT cols = ColDimension (x);
  INTERVAL_MATRIX t(rows, cols);

  CheckMatrixDimensions (*this, x);
  MakeTemporary (t);
  BiasSubMIMI (t.theElements, theElements, x.theElements, rows, cols);
  *this = t; return *this;
}

INTERVAL_MATRIX & INTERVAL_MATRIX::operator *= (CONST INTERVAL & x)
{
  INT rows = RowDimension (*this);
  INT cols = ColDimension (*this);
  INTERVAL_MATRIX t(rows, cols);

  MakeTemporary (t);
  BiasMulIMI (t.theElements, Bias (x), theElements, rows, cols);
  *this = t; return *this;
}

INTERVAL_MATRIX & INTERVAL_MATRIX::operator /= (CONST INTERVAL & x)
{
  INT rows = RowDimension (*this);
  INT cols = ColDimension (*this);
  INTERVAL_MATRIX t(rows, cols);

  MakeTemporary (t);
  BiasDivMII (t.theElements, theElements, Bias (x), rows, cols);
  *this = t; return *this;
}

INTERVAL_MATRIX & INTERVAL_MATRIX::operator = (CONST MATRIX & x)
{
  INT i;
  REAL *px = x.theElements;
  INT dim = RowDimension (x) * ColDimension (x);
  BIASINTERVAL *pt;

  if (theElements == NULL) {
    theElements = new BIASINTERVAL[dim];
    CheckMemory (theElements);
    nRows = RowDimension (x); nCols = ColDimension (x);
  }
  else CheckMatrixDimensions (*this, x);
  pt = theElements;
  for (i = 0; i < dim; i++) BiasHullR (pt++, px++);
  return *this;
}

INTERVAL_MATRIX & INTERVAL_MATRIX::operator += (CONST MATRIX & x)
{
  INT rows = RowDimension (x);
  INT cols = ColDimension (x);
  INTERVAL_MATRIX t(rows, cols);

  CheckMatrixDimensions (*this, x);
  MakeTemporary (t);
  BiasAddMIMR (t.theElements, theElements, x.theElements, rows, cols);
  *this = t; return *this;
}

INTERVAL_MATRIX & INTERVAL_MATRIX::operator -= (CONST MATRIX & x)
{
  INT rows = RowDimension (x);
  INT cols = ColDimension (x);
  INTERVAL_MATRIX t(rows, cols);

  CheckMatrixDimensions (*this, x);
  MakeTemporary (t);
  BiasSubMIMR (t.theElements, theElements, x.theElements, rows, cols);
  *this = t; return *this;
}

INTERVAL_MATRIX & INTERVAL_MATRIX::operator *= (REAL x)
{
  INT rows = RowDimension (*this);
  INT cols = ColDimension (*this);
  INTERVAL_MATRIX t(rows, cols);

  MakeTemporary (t);
  BiasMulRMI (t.theElements, & x, theElements, rows, cols);
  *this = t; return *this;
}

INTERVAL_MATRIX & INTERVAL_MATRIX::operator /= (REAL x)
{
  INT rows = RowDimension (*this);
  INT cols = ColDimension (*this);
  INTERVAL_MATRIX t(rows, cols);

  MakeTemporary (t);
  BiasDivMIR (t.theElements, theElements, & x, rows, cols);
  *this = t; return *this;
}
VOID INTERVAL_MATRIX::hcat(const INTERVAL_MATRIX& src1)
{
    assert(src1.nCols != 0);
    assert(src1.nRows != 0);
    if(theElements != NULL){
        BIASINTERVAL *tmptheElements;
        tmptheElements = new BIASINTERVAL[nRows*nCols];
        CheckDimensions(Col(*this,1),Col(src1,1));
        if(nRows != src1.nRows)return;
        memcpy(tmptheElements,theElements,nRows*nCols*sizeof(BIASINTERVAL));
        theElements = new BIASINTERVAL[nRows*(nCols+ColDimension(src1))];
        CheckMemory(theElements);
        int contRow1 = 0,contRow2 = 0,contRow3 = 0;
        for(int i = 0;i < nRows;i++){
            assert(contRow1 <= nRows*(nCols+ColDimension(src1)) || contRow2 <= (nRows*nCols));
            memcpy(&theElements[contRow1],&tmptheElements[contRow2],nCols*sizeof(BIASINTERVAL));
            contRow1 += nCols;
            contRow2 += nCols;
            memcpy(&theElements[contRow1],&src1.theElements[contRow3],src1.nCols*sizeof(BIASINTERVAL));
            contRow1 += src1.nCols;
            contRow3 += src1.nCols;
        }
        nCols = (nCols+ColDimension(src1));
        delete [] tmptheElements;
    }
    else{
        nRows = RowDimension(src1);
        nCols = ColDimension(src1);
        theElements = new BIASINTERVAL[nRows*nCols];
        CheckMemory(theElements);
        memcpy(theElements,src1.theElements,nRows*nCols*sizeof(BIASINTERVAL));
    }
}
VOID INTERVAL_MATRIX::hcat(const INTERVAL_VECTOR& src1)
{
    assert(Dimension(src1) != 0);
    if(theElements != NULL){
        CheckRowDimensions(*this,src1);
        BIASINTERVAL *tmptheElements;
        tmptheElements = new BIASINTERVAL[nRows*nCols];
        assert(nRows == Dimension(src1));
        memcpy(tmptheElements,theElements,nRows*nCols*sizeof(BIASINTERVAL));
        theElements = new BIASINTERVAL[nRows*(nCols+1)];
        CheckMemory(theElements);
        int contRow1 = 0,contRow2 = 0,contRow3 = 0;
        for(int i = 0;i < nRows;i++){
            if(contRow1 > nRows*(nCols+1) || contRow2 > (nRows*nCols) 
                    || contRow3 > Dimension(src1)*1){
                cerr << "Wrong dimension" << endl;
            }
            memcpy(&theElements[contRow1],&tmptheElements[contRow2],nCols*sizeof(BIASINTERVAL));
            contRow1 += nCols;
            contRow2 += nCols;
            memcpy(&theElements[contRow1],&src1.theElements[contRow3],1*sizeof(BIASINTERVAL));
            contRow1++;
            contRow3++;
        }
        nCols = (nCols+1);
        delete [] tmptheElements;
    }
    else{
        nRows = Dimension(src1);
        nCols = 1;
        theElements = new BIASINTERVAL[nRows*nCols];
        CheckMemory(theElements);
        memcpy(theElements,src1.theElements,nRows*nCols*sizeof(BIASINTERVAL));
    }
}
void INTERVAL_MATRIX::hcat(CONST INTERVAL_MATRIX & src1,CONST INTERVAL_MATRIX & src2)
{
    if(theElements != NULL) delete [] theElements;
    nRows = src1.nRows;
    nCols = src1.nCols+src2.nCols;
    theElements = new BIASINTERVAL[nRows * nCols * sizeof(BIASINTERVAL)];
    CheckMemory(theElements);
    memcpy (theElements,src1.theElements,src1.nRows * src1.nCols * sizeof (BIASINTERVAL));
    memcpy (&theElements[src1.nRows * src1.nCols * sizeof (BIASINTERVAL)],src2.theElements,
            src2.nRows * src2.nCols * sizeof (BIASINTERVAL));
}
void INTERVAL_MATRIX::hcat(const INTERVAL_MATRIX& MAT,CONST INTERVAL_VECTOR& VEC)
{
    INTERVAL_MATRIX out(MAT.nRows,MAT.nCols+1);
    if(out.nRows != Dimension(VEC)) return;
    INT i;
    for(i=1;i<=RowDimension(MAT);i++)
        SetCol(out,i,Row(MAT,i));
    SetCol(out,i,VEC);
    *this=out;
}
VOID INTERVAL_MATRIX::vcat(const INTERVAL_MATRIX& src1)
{
//    if (theElements == NULL){
//        *this=src1;
//        return;
//    }
//    BIASINTERVAL *tmptheElements;
//    if(nRows != src1.nRows){
//        return;            
//    }
//    tmptheElements = new BIASINTERVAL[nRows * (nCols+src1.nCols)];
//    CheckMemory (tmptheElements);
//    memcpy (tmptheElements,theElements,nRows * nCols * sizeof (BIASINTERVAL));
//    memcpy (&tmptheElements[nRows * nCols * sizeof (BIASINTERVAL)],src1.theElements,
//            src1.nRows * src1.nCols * sizeof (BIASINTERVAL));
//    theElements=tmptheElements;
//    nCols += src1.nCols;
    INTERVAL_MATRIX out;
    INT i,j;
    if(theElements != NULL){
        Resize(out,nRows+RowDimension(src1),nCols);
        if(out.nCols != ColDimension(src1)) return;
        for(i=1;i<=nRows;i++)
            SetRow(out,i,Row(*this,i));
        for(j=i;j<i+RowDimension(src1);j++)
            SetRow(out,j,Row(src1,j-(i-1)));
    }
    else{
        Resize(out,RowDimension(src1),ColDimension(src1));
        for(i=1;i<=RowDimension(src1);i++)
            SetRow(out,i,Row(src1,i));
    }
    *this=out;
}
VOID INTERVAL_MATRIX::vcat(const INTERVAL_VECTOR& src1)
{
    if(theElements != NULL){
        assert(nCols == Dimension(src1));
        BIASINTERVAL *tmptheElements;
        tmptheElements = new BIASINTERVAL[nRows*nCols];
        memcpy(tmptheElements,theElements,nRows*nCols*sizeof(BIASINTERVAL));
        theElements = new BIASINTERVAL[nCols*(nRows+1)];
        CheckMemory(theElements);
        memcpy(theElements,tmptheElements,nRows*nCols*sizeof(BIASINTERVAL));
        memcpy(&theElements[nRows*nCols],src1.theElements,Dimension(src1)*sizeof(BIASINTERVAL));
        nRows++;
        delete [] tmptheElements;
    }
    else{
        nRows = 1;
        nCols = Dimension(src1);
        theElements = new BIASINTERVAL[nRows*nCols];
        CheckMemory(theElements);
        memcpy(theElements,src1.theElements,nRows*nCols*sizeof(BIASINTERVAL));
    }
}
void INTERVAL_MATRIX::vcat(CONST INTERVAL_MATRIX & src1,CONST INTERVAL_MATRIX & src2)
{
    assert(nRows == src1.nRows);
    if(theElements != NULL) delete [] theElements;
    nRows = src1.nRows;
    nCols = src1.nCols+src2.nCols;
    theElements = new BIASINTERVAL[nRows * nCols * sizeof(BIASINTERVAL)];
    CheckMemory(theElements);
    memcpy (theElements,src1.theElements,src1.nRows * src1.nCols * sizeof (BIASINTERVAL));
    memcpy (&theElements[src1.nRows * src1.nCols * sizeof (BIASINTERVAL)],src2.theElements,
            src2.nRows * src2.nCols * sizeof (BIASINTERVAL));
}
void INTERVAL_MATRIX::vcat(const INTERVAL_MATRIX& MAT,CONST INTERVAL_VECTOR& VEC)
{
    INTERVAL_MATRIX out(MAT.nRows,MAT.nCols+1);
    if(out.nRows != Dimension(VEC)) return;
    INT i;
    for(i=1;i<=RowDimension(MAT);i++)
        SetCol(out,i,Row(MAT,i));
    SetCol(out,i,VEC);
    *this=out;
}
bool INTERVAL_MATRIX::hasNan(){
    for(int i = 0;i < (nRows*nCols);i++){
        if(std::isnan(theElements[i].inf))return true;
        if(std::isnan(theElements[i].sup))return true;
    }
    return false;
}
bool INTERVAL_MATRIX::hasInf(){
    for(int i = 0;i < (nRows*nCols);i++){
        if(std::isinf(theElements[i].inf))return true;
        if(std::isinf(theElements[i].sup))return true;
    }
    return false;
}
double INTERVAL_MATRIX::absmax() const{
    REAL Maxval = Machine::NegInfinity;
    for(int i = 0;i < (nRows*nCols);i++){
        double tmpmax = Abs(theElements[i]);
        if(tmpmax > Maxval)
            Maxval = tmpmax;
    }
    return Maxval;
}
INTERVAL_VECTOR INTERVAL_MATRIX::toINTERVAL_VECTOR(){
    INTERVAL_VECTOR out(nRows*nCols);
    for(int i = 0;i < nRows*nCols;i++){
        out.theElements[i] = theElements[i];
    }
}
INTERVAL INTERVAL_MATRIX::det(){
    assert(nRows == nCols);
    return Determinant((*this));
}
INTERVAL_MATRIX INTERVAL_MATRIX::LU(){
    assert(nRows == nCols);
    INTERVAL_MATRIX A,L,U;
    L = ZEROS(nRows,nCols);
    U = L;
    for(int i = 1;i <= nRows;i++){
        for(int j = i;j <= nCols;j++){
            INTERVAL sum(0);
            for(int k = 1;k < i-1;k++){
                sum += U(k,j)*L(i,k);
            }
            if(i <= i)
                U(i,j)=(*this)(i,j)-sum;
            if(i > j)
                L(i,j)=((*this)(i,j)-sum)/U(j,j);
        }
    }
    for(int i = 1;i <= L.nCols;i++)
        L(i,i) = 1;
    cout << (*this) << "==" << L*U << endl;
    return U+L;
}

MATRIX INTERVAL_MATRIX::compare(const INTERVAL_MATRIX& A){
    assert(nCols == A.nCols && nRows == A.nRows);
    MATRIX out(nRows,nCols);
    for(int i = 1;i <= nRows;i++){
        for(int j = 1;j <= nCols;j++){
            out(i,j) = Abs((*this)(i,j)-A(i,j));
        }
    }
    return out;
}

VOID Resize (INTERVAL_MATRIX & x, INT r, INT c)
{
  CheckMatrixRange (r, c);
  if ((r * c) && (x.nRows == r) && (x.nCols == c)) return;
  if (x.theElements != NULL) delete [] x.theElements;
  x.nRows = r; x.nCols = c;
  if (r * c != 0) {
    x.theElements = new BIASINTERVAL[r * c];
    CheckMemory (x.theElements);
  }
  else x.theElements = NULL;
}

INTERVAL_MATRIX operator - (CONST INTERVAL_MATRIX & a)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  INTERVAL_MATRIX t (rows, cols);

  MakeTemporary (t);
  BiasNegM (t.theElements, a.theElements, rows, cols);
  return t;
}

INTERVAL_MATRIX Hull (CONST MATRIX & a)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  INTERVAL_MATRIX t (rows, cols);

  MakeTemporary (t);
  BiasHullMR (t.theElements, a.theElements, rows, cols);
  return t;
}

INTERVAL_MATRIX Hull (CONST MATRIX & a, CONST MATRIX & b)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  INTERVAL_MATRIX t (rows, cols);

  CheckMatrixDimensions (a, b);
  MakeTemporary (t);
  BiasHullMRMR (t.theElements, a.theElements, b.theElements, rows, cols);
  return t;
}

INTERVAL_MATRIX Hull (CONST MATRIX & a, CONST INTERVAL_MATRIX & b)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  INTERVAL_MATRIX t (rows, cols);

  CheckMatrixDimensions (a, b);
  MakeTemporary (t);
  BiasHullMRMI (t.theElements, a.theElements, b.theElements, rows, cols);
  return t;
}

INTERVAL_MATRIX Hull (CONST INTERVAL_MATRIX & a, CONST MATRIX & b)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  INTERVAL_MATRIX t (rows, cols);

  CheckMatrixDimensions (a, b);
  MakeTemporary (t);
  BiasHullMIMR (t.theElements, a.theElements, b.theElements, rows, cols);
  return t;
}

INTERVAL_MATRIX Hull (CONST INTERVAL_MATRIX & a, CONST INTERVAL_MATRIX & b)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  INTERVAL_MATRIX t (rows, cols);

  CheckMatrixDimensions (a, b);
  MakeTemporary (t);
  BiasHullMIMI (t.theElements, a.theElements, b.theElements, rows, cols);
  return t;
}

INTERVAL_MATRIX AddBounds (CONST MATRIX & a, CONST MATRIX & b)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  INTERVAL_MATRIX t (rows, cols);

  CheckMatrixDimensions (a, b);
  MakeTemporary (t);
  BiasAddMRMR (t.theElements, a.theElements, b.theElements, rows, cols);
  return t;
}

INTERVAL_MATRIX operator + (CONST MATRIX & a, CONST INTERVAL_MATRIX & b)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  INTERVAL_MATRIX t (rows, cols);

  CheckMatrixDimensions (a, b);
  MakeTemporary (t);
  BiasAddMRMI (t.theElements, a.theElements, b.theElements, rows, cols);
  return t;
}

INTERVAL_MATRIX operator + (CONST INTERVAL_MATRIX & a, CONST MATRIX & b)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  INTERVAL_MATRIX t (rows, cols);

  CheckMatrixDimensions (a, b);
  MakeTemporary (t);
  BiasAddMIMR (t.theElements, a.theElements, b.theElements, rows, cols);
  return t;
}

INTERVAL_MATRIX operator + (CONST INTERVAL_MATRIX & a, CONST INTERVAL_MATRIX & b)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  INTERVAL_MATRIX t (rows, cols);

  CheckMatrixDimensions (a, b);
  MakeTemporary (t);
  BiasAddMIMI (t.theElements, a.theElements, b.theElements, rows, cols);
  return t;
}

INTERVAL_MATRIX SubBounds (CONST MATRIX & a, CONST MATRIX & b)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  INTERVAL_MATRIX t (rows, cols);

  CheckMatrixDimensions (a, b);
  MakeTemporary (t);
  BiasSubMRMR (t.theElements, a.theElements, b.theElements, rows, cols);
  return t;
}

INTERVAL_MATRIX operator - (CONST MATRIX & a, CONST INTERVAL_MATRIX & b)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  INTERVAL_MATRIX t (rows, cols);

  CheckMatrixDimensions (a, b);
  MakeTemporary (t);
  BiasSubMRMI (t.theElements, a.theElements, b.theElements, rows, cols);
  return t;
}

INTERVAL_MATRIX operator - (CONST INTERVAL_MATRIX & a, CONST MATRIX & b)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  INTERVAL_MATRIX t (rows, cols);

  CheckMatrixDimensions (a, b);
  MakeTemporary (t);
  BiasSubMIMR (t.theElements, a.theElements, b.theElements, rows, cols);
  return t;
}

INTERVAL_MATRIX operator - (CONST INTERVAL_MATRIX & a, CONST INTERVAL_MATRIX & b)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  INTERVAL_MATRIX t (rows, cols);

  CheckMatrixDimensions (a, b);
  MakeTemporary (t);
  BiasSubMIMI (t.theElements, a.theElements, b.theElements, rows, cols);
  return t;
}

INTERVAL_MATRIX MulBounds (REAL a, CONST MATRIX & b)
{
  INT rows = RowDimension (b);
  INT cols = ColDimension (b);
  INTERVAL_MATRIX t (rows, cols);

  MakeTemporary (t);
  BiasMulRMR (t.theElements, &a, b.theElements, rows, cols);
  return t;
}

INTERVAL_MATRIX operator * (REAL a, CONST INTERVAL_MATRIX & b)
{
  INT rows = RowDimension (b);
  INT cols = ColDimension (b);
  INTERVAL_MATRIX t (rows, cols);

  MakeTemporary (t);
  BiasMulRMI (t.theElements, &a, b.theElements, rows, cols);
  return t;
}

INTERVAL_MATRIX operator * (CONST INTERVAL & a, CONST MATRIX & b)
{
  INT rows = RowDimension (b);
  INT cols = ColDimension (b);
  INTERVAL_MATRIX t (rows, cols);

  MakeTemporary (t);
  BiasMulIMR (t.theElements, Bias (a), b.theElements, rows, cols);
  return t;
}

INTERVAL_MATRIX operator * (CONST INTERVAL & a, CONST INTERVAL_MATRIX & b)
{
  INT rows = RowDimension (b);
  INT cols = ColDimension (b);
  INTERVAL_MATRIX t (rows, cols);

  MakeTemporary (t);
  BiasMulIMI (t.theElements, Bias (a), b.theElements, rows, cols);
  return t;
}

INTERVAL_MATRIX DivBounds (CONST MATRIX & a, REAL b)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  INTERVAL_MATRIX t (rows, cols);

  MakeTemporary (t);
  BiasDivMRR (t.theElements, a.theElements, &b, rows, cols);
  return t;
}

INTERVAL_MATRIX operator / (CONST MATRIX & a, CONST INTERVAL & b)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  INTERVAL_MATRIX t (rows, cols);

  MakeTemporary (t);
  BiasDivMRI (t.theElements, a.theElements, Bias (b), rows, cols);
  return t;
}

INTERVAL_MATRIX operator / (CONST INTERVAL_MATRIX & a, REAL b)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  INTERVAL_MATRIX t (rows, cols);

  MakeTemporary (t);
  BiasDivMIR (t.theElements, a.theElements, &b, rows, cols);
  return t;
}

INTERVAL_MATRIX operator / (CONST INTERVAL_MATRIX & a, CONST INTERVAL & b)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  INTERVAL_MATRIX t (rows, cols);

  MakeTemporary (t);
  BiasDivMII (t.theElements, a.theElements, Bias (b), rows, cols);
  return t;
}

INTERVAL_VECTOR MulBounds (CONST MATRIX & a, CONST VECTOR & b)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  INTERVAL_VECTOR t (rows);

  CheckColumnDimensions (a, b);
  MakeTemporary (t);
  BiasMulMRVR (t.theElements, a.theElements, b.theElements, rows, cols);
  return t;
}

INTERVAL_VECTOR operator * (CONST MATRIX & a, CONST INTERVAL_VECTOR & b)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  INTERVAL_VECTOR t (rows);

  CheckColumnDimensions (a, b);
  MakeTemporary (t);
  BiasMulMRVI (t.theElements, a.theElements, b.theElements, rows, cols);
  return t;
}

INTERVAL_VECTOR operator * (CONST INTERVAL_MATRIX & a, CONST VECTOR & b)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  INTERVAL_VECTOR t (rows);

  CheckColumnDimensions (a, b);
  MakeTemporary (t);
  BiasMulMIVR (t.theElements, a.theElements, b.theElements, rows, cols);
  return t;
}

INTERVAL_VECTOR operator * (CONST INTERVAL_MATRIX & a, CONST INTERVAL_VECTOR & b)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  INTERVAL_VECTOR t (rows);

  CheckColumnDimensions (a,b);
  MakeTemporary (t);
  BiasMulMIVI (t.theElements, a.theElements, b.theElements, rows, cols);
  return t;
}

INTERVAL_MATRIX MulBounds (CONST MATRIX & a, CONST MATRIX & b)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (b);
  INTERVAL_MATRIX t (rows, cols);

  CheckMatrixMatrixDimensions (a, b);
  MakeTemporary (t);
  BiasMulMRMR (t.theElements, a.theElements, b.theElements,
	       rows, ColDimension (a), cols);
  return t;
}
INTERVAL_MATRIX Zeros (INT nRows, INT nCols){
    INTERVAL_MATRIX out(nRows,nCols);
    for(int i=1;i<=nRows;i++)
        for(int j=1;j<=nCols;j++)
            out(i,j)=Constant::ZERO;
    return out;
}
INTERVAL_MATRIX Ones (INT nRows, INT nCols){
    INTERVAL_MATRIX out(nRows,nCols);
    for(int i=1;i<=nRows;i++)
        for(int j=1;j<=nCols;j++)
            out(i,j)=Constant::UM;
    return out;
}
INTERVAL_MATRIX Eye (CONST INT n)
{
    INTERVAL_MATRIX EYE(n,n);
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
            if(i == j)EYE(i,j)=Constant::UM;
            else EYE(i,j)=Constant::ZERO;
    return EYE;
}
INTERVAL_MATRIX Eye (CONST INT n,CONST INT m){
    INTERVAL_MATRIX EYE(n,m);
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++)
            if(i == j)EYE(i,j)=Constant::UM;
            else EYE(i,j)=Constant::ZERO;
    return EYE;
}
INTERVAL_MATRIX Diag (CONST INTERVAL_VECTOR & VEC)
{
    INTERVAL_MATRIX out(Dimension(VEC),Dimension(VEC));
    out = Zeros(Dimension(VEC),Dimension(VEC));
    for(int i=1;i<=Dimension(VEC);i++) out(i,i)=VEC(i);
    return out;
}
INTERVAL_MATRIX Diag (INT nRow,INT nCol,CONST INTERVAL_VECTOR & VEC)
{
    INTERVAL_MATRIX out(nRow,nCol);
    if(nRow != Dimension(VEC)) return out;
    out = Zeros(nRow,nCol);
    for(int i=1;i<=Dimension(VEC);i++)out(i,i)=VEC(i);
    return out;
}
INTERVAL_MATRIX operator * (CONST MATRIX & a, CONST INTERVAL_MATRIX & b)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (b);
  INTERVAL_MATRIX t (rows, cols);

  CheckMatrixMatrixDimensions (a, b);
  MakeTemporary (t);
  BiasMulMRMI (t.theElements, a.theElements, b.theElements,
	       rows, ColDimension (a), cols);
  return t;
}

INTERVAL_MATRIX operator * (CONST INTERVAL_MATRIX & a, CONST MATRIX & b)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (b);
  INTERVAL_MATRIX t (rows, cols);

  CheckMatrixMatrixDimensions (a, b);
  MakeTemporary (t);
  BiasMulMIMR (t.theElements, a.theElements, b.theElements,
	       rows, ColDimension (a), cols);
  return t;
}

INTERVAL_MATRIX operator * (CONST INTERVAL_MATRIX & a, CONST INTERVAL_MATRIX & b)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (b);
  INTERVAL_MATRIX t (rows, cols);

  CheckMatrixMatrixDimensions (a, b);
  MakeTemporary (t);
  BiasMulMIMI (t.theElements, a.theElements, b.theElements,
	       rows, ColDimension (a), cols);
  return t;
}

MATRIX Inf (CONST INTERVAL_MATRIX & a)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  MATRIX t (rows, cols);

  MakeTemporary (t);
  BiasInfM (t.theElements, a.theElements, rows, cols);
  return t;
}

MATRIX Sup (CONST INTERVAL_MATRIX & a)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  MATRIX t (rows, cols);

  MakeTemporary (t);
  BiasSupM (t.theElements, a.theElements, rows, cols);
  return t;
}

MATRIX Mid (CONST INTERVAL_MATRIX & a)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  MATRIX t (rows, cols);

  MakeTemporary (t);
  BiasMidM (t.theElements, a.theElements, rows, cols);
  return t;
}

MATRIX Diam (CONST INTERVAL_MATRIX & a)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  MATRIX t (rows, cols);

  MakeTemporary (t);
  BiasDiamM (t.theElements, a.theElements, rows, cols);
  return t;
}

MATRIX INTERVAL_MATRIX::diam ( ){
  MATRIX t (nRows, nCols);

  MakeTemporary (t);
  BiasDiamM (t.theElements, theElements, nRows, nCols);
  return t;
}
INTERVAL_VECTOR INTERVAL_MATRIX::diag(){
    int dim;
    if(nRows < nCols)
        dim = nRows;
    else
        dim = nCols;
    INTERVAL_VECTOR out(dim);
    for(int i = 1;i <= dim;i++)
        out(i) = (*this)(i,i);
    return out;
}

MATRIX Abs (CONST INTERVAL_MATRIX & a)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  MATRIX t (rows, cols);

  MakeTemporary (t);
  BiasAbsM (t.theElements, a.theElements, rows, cols);
  return t;
}

INT Intersection (INTERVAL_MATRIX & r, CONST INTERVAL_MATRIX & a, CONST INTERVAL_MATRIX & b)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);

  CheckMatrixDimensions (a, b);
  if (r.theElements == NULL) Resize (r, rows, cols);
  else CheckMatrixDimensions (a, r);
  return BiasIntersectionM (r.theElements, a.theElements,
			 b.theElements, rows, cols);
}

INT operator <= (CONST MATRIX & a, CONST INTERVAL_MATRIX & b)
{
  CheckMatrixDimensions (a, b);
  return BiasInMR (a.theElements, b.theElements,
		   RowDimension (a), ColDimension (a));
}

INT operator <= (CONST INTERVAL_MATRIX & a, CONST INTERVAL_MATRIX & b)
{
  CheckMatrixDimensions (a, b);
  return BiasInMI (a.theElements, b.theElements,
		   RowDimension (a), ColDimension (a));
}

INT operator < (CONST MATRIX & a, CONST INTERVAL_MATRIX & b)
{
  CheckMatrixDimensions (a, b);
  return BiasInInteriorMR (a.theElements, b.theElements,
			   RowDimension (a), ColDimension (a));
}

INT operator < (CONST INTERVAL_MATRIX & a, CONST INTERVAL_MATRIX & b)
{
  CheckMatrixDimensions (a, b);
  return BiasInInteriorMI (a.theElements, b.theElements,
			   RowDimension (a), ColDimension (a));
}

INT operator == (CONST INTERVAL_MATRIX & a, CONST INTERVAL_MATRIX & b)
{
  CheckMatrixDimensions (a, b);
  return BiasIsEqualM (a.theElements, b.theElements,
		       RowDimension (a), ColDimension (a));
}

INT operator != (CONST INTERVAL_MATRIX & a, CONST INTERVAL_MATRIX & b)
{
  CheckMatrixDimensions (a, b);
  return !BiasIsEqualM (a.theElements, b.theElements,
			RowDimension (a), ColDimension (a));
}

VOID Clear (INTERVAL_MATRIX & a)
{
  if (a.theElements != NULL)
    memset (a.theElements, 0,
	    RowDimension (a) * ColDimension (a) * sizeof (BIASINTERVAL));
}

VOID Initialize (INTERVAL_MATRIX & a, CONST INTERVAL & r)
{
  INT dim = RowDimension (a) * ColDimension (a);
  INT i;
  BIASINTERVAL *pa = a.theElements;
  CONST BIASINTERVAL *pr = Bias (r);

  for (i = 0; i < dim; i++) *(pa++) = *pr;
}

VOID Reshape(INTERVAL_MATRIX& out,INT nRows,INT nCols,const INTERVAL_VECTOR& in){
    if(nRows*nCols != Dimension(in)){
        cerr << "Wrong dimensions" << endl;
        return;
    }
    Resize(out,nRows,nCols);
    INT cont_vec = 1;
    for(int i = 1;i <= nRows;i++)
        for(int j = 1;j <= nCols;j++){
            out(i,j) = in(cont_vec);
            cont_vec++;
        }
}

INTERVAL_VECTOR Row (CONST INTERVAL_MATRIX & a, INT i)
{
  INT dim = ColDimension (a);
  INTERVAL_VECTOR t(dim);

  CheckMatrixRowIndex (i, a);
  MakeTemporary (t);
  memcpy (t.theElements, a.theElements + (i - 1) * dim, dim * sizeof (BIASINTERVAL));
  return t;
}

INTERVAL_VECTOR INTERVAL_MATRIX::row (INT i) CONST
{
  INTERVAL_VECTOR t(nCols);

  assert(i <= nRows);
  MakeTemporary (t);
  memcpy (t.theElements, theElements + (i - 1) * nCols, nCols * sizeof (BIASINTERVAL));
  return t;
}


INTERVAL_VECTOR Col (CONST INTERVAL_MATRIX & a, INT k)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  INT i;
  BIASINTERVAL *pa, *pt;
  INTERVAL_VECTOR t(rows);

  CheckMatrixColIndex (k, a);
  MakeTemporary (t);
  pa = a.theElements + k - 1;
  pt = t.theElements;
  for (i = 0; i < rows; i++, pa += cols) *(pt++) = *pa;
  return t;
}

INTERVAL_VECTOR INTERVAL_MATRIX::col (INT Idx) CONST
{
  INT i;
  BIASINTERVAL *pa, *pt;
  INTERVAL_VECTOR t(nRows);

  //CheckMatrixColIndex (j, (*this));
  assert(Idx <= nCols);
  MakeTemporary (t);
  pa = theElements + Idx - 1;
  pt = t.theElements;
  for (i = 0; i < nRows; i++, pa += nCols) *(pt++) = *pa;
  return t;
}


VOID SetRow (INTERVAL_MATRIX & a, INT i, CONST INTERVAL_VECTOR & t)
{
  INT dim = ColDimension (a);

  CheckMatrixRowIndex (i, a);
  CheckColumnDimensions (a, t);
  memcpy (a.theElements + (i - 1) * dim, t.theElements, dim * sizeof (BIASINTERVAL));
}

VOID SetCol (INTERVAL_MATRIX & a, INT k, CONST INTERVAL_VECTOR & t)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  INT i;
  BIASINTERVAL *pa, *pt;

  CheckMatrixColIndex (k, a);
  CheckRowDimensions (a, t);
  pa = a.theElements + k - 1;
  pt = t.theElements;
  for (i = 0; i < rows; i++, pa += cols) *pa = *(pt++);
}
ostream & operator << (ostream & os, CONST INTERVAL_MATRIX & x)
{
  INT i, j;
  INT rows = RowDimension (x);
  INT cols = ColDimension (x);
  BIASINTERVAL *px = x.theElements;
  INTERVAL iv;

  os << '(';
  for (i = 0; i < rows; i++) {
    os << '(';
    for (j = 0; j < cols; j++, px++) {
      *(Bias(iv)) = *px;
      os << iv;
      if (j < cols - 1) os << " ; ";
    }
    os << ')';
    if (i < rows - 1) os << endl << ' ';
  }
  return os << ')';
}

istream & operator >> (istream & is, INTERVAL_MATRIX & x)
{
  INT i, j;
  INT rows = RowDimension (x);
  INT cols = ColDimension (x);
  BIASINTERVAL *px = x.theElements;
  INTERVAL iv;

  for (i = 0; i < rows; i++)
    for (j = 0; j < cols; j++) {
      is >> iv;
      *(px++) = *(Bias(iv));
    }
  return is;
}
INTERVAL_MATRIX Random (INT nRows,INT nCols){
    Eigen::MatrixXd inf(nRows,nCols),sup(nRows,nCols);
    inf.setRandom();
    sup.setRandom();
    MATRIX a,b;
    a = MatrixXd2MATRIX(inf);
    b = MatrixXd2MATRIX(sup);
    return Hull(a,b);
}

INTERVAL_MATRIX INTERVAL_MATRIX::Box(INT iniRow, INT endRow, INT iniCol, INT endCol){
    INTERVAL_MATRIX mNULL;
    CheckMatrixRowIndex(iniRow,(*this));
    CheckMatrixRowIndex(endRow,(*this));
    CheckMatrixColIndex(iniCol,(*this));
    CheckMatrixColIndex(endCol,(*this));
    INTERVAL_MATRIX box((endRow-iniRow)+1,(endCol-iniCol)+1);
    INT row = 1;
    for(int i = iniRow;i <= endRow;i++,row++){
        INT col = 1;
        for(int j = iniCol;j <= endCol;j++,col++){
            box(row,col)=theElements[((i-1)*nCols+j)-1];
        }
    }
    return box;
}
VOID GetNonHomogeneous(INTERVAL_MATRIX& dst,CONST INTERVAL_MATRIX& src){
    INTERVAL_MATRIX tmpsrc;
    tmpsrc = src;
    Resize(dst,RowDimension(src)-1,ColDimension(src));
    INTERVAL_VECTOR Colsrc,Coldst;
    for(int i = 1;i <= ColDimension(src);i++){
        Colsrc = Col(tmpsrc,i);
        GetNonHomogeneous(Coldst,Colsrc);
        SetCol(dst,i,Coldst);
    }
}
VOID GetHomogeneous(INTERVAL_MATRIX& dst,CONST INTERVAL_MATRIX& src){
    INTERVAL_MATRIX tmpsrc;
    tmpsrc = src;
    Resize(dst,RowDimension(src)+1,ColDimension(src));
    INTERVAL_VECTOR Colsrc,Coldst;
    for(int i = 1;i <= ColDimension(src);i++){
        Colsrc = Col(tmpsrc,i);
        GetHomogeneous(Coldst,Colsrc);
        SetCol(dst,i,Coldst);
    }
}
VOID PointwiseMul(INTERVAL_MATRIX & dst,const INTERVAL_MATRIX src1,CONST INTERVAL_MATRIX src2){
    CheckDimensions(src1,src2);
    Resize(dst,RowDimension(src1),ColDimension(src1));
    for(int i = 1;i <= RowDimension(src1);i++)
        for(int j = 1;j <= ColDimension(src1);j++)
            dst(i,j) = src1(i,j)*src2(i,j);
}
VOID PointwiseDiv(INTERVAL_MATRIX & dst,const INTERVAL_MATRIX src1,CONST INTERVAL_MATRIX src2){
    CheckDimensions(src1,src2);
    Resize(dst,RowDimension(src1),ColDimension(src1));
    for(int i = 1;i <= RowDimension(src1);i++)
        for(int j = 1;j <= ColDimension(src1);j++)
            dst(i,j) = src1(i,j)/src2(i,j);
}
VOID Sum(INTERVAL_VECTOR & dst,CONST INTERVAL_MATRIX src){
    dst = ZEROS(ColDimension(src));
    for(int i = 1;i <= ColDimension(src);i++)
        for(int j = 1;j <= RowDimension(src);j++)
            dst(i)+=src(i,j);
}
VOID PointwiseSqr(INTERVAL_MATRIX & dst,CONST INTERVAL_MATRIX& src){
    dst = ZEROS(RowDimension(src),ColDimension(src));
    for(int i = 1;i <= ColDimension(src);i++)
        for(int j = 1;j <= RowDimension(src);j++)
            dst(i,j)=Sqr(src(i,j));
}
INTERVAL_VECTOR Diag (CONST INTERVAL_MATRIX& src){
    INTERVAL_VECTOR dst(RowDimension(src));
    for(int i = 1;i <= RowDimension(src);i++)
        dst(i)=src(i,i);
    return dst;
}
bool HasDivisionByZero(CONST INTERVAL_MATRIX& src){
    for(int i = 1;i <= RowDimension(src);i++)
        for(int j = 1; j <= ColDimension(src);j++)
            if(Inf(src(i,j)) <= 0 && Sup(src(i,j)) >= 0)
                return true;
    return false;
}
VOID GetMatrixOfRowColIdx(INTERVAL_MATRIX& dst,
                        CONST INTERVAL_MATRIX& src, 
                        CONST VECTOR& rows,
                        CONST VECTOR& cols){
    int RowDim = Dimension(rows);
    int ColDim = Dimension(cols);
    Resize(dst,RowDim,ColDim);
    for(int i = 1;i <= RowDim;i++)
        for(int j = 1;j <= ColDim;j++){
            if(rows(i) > RowDimension(src) || cols(i) > ColDimension(src)){
                dst.Delete();
                return;
            }
            dst(i,j)=src(rows(i),cols(j));
        }
}
VOID GetMatrixOfColIdx(INTERVAL_MATRIX& dst,
                            CONST INTERVAL_MATRIX& src,
                            CONST VECTOR& cols){
    int RowDim = RowDimension(src);
    int ColDim = Dimension(cols);
    Resize(dst,RowDim,ColDim);
    for(int i = 1;i <= RowDim;i++)
        for(int j = 1;j <= ColDim;j++){
            if(cols(i) > ColDimension(src)){
                dst.Delete();
                return;
            }
            dst(i,j)=src(i,cols(j));
        }    
}
VOID GetMatrixOfRowIdx(INTERVAL_MATRIX& dst,
                            CONST INTERVAL_MATRIX& src,
                            CONST VECTOR& rows){
    int RowDim = Dimension(rows);
    int ColDim = ColDimension(src);
    Resize(dst,RowDim,ColDim);
    for(int i = 1;i <= RowDim;i++)
        for(int j = 1;j <= ColDim;j++){
            if(rows(i) > RowDimension(src)){
                dst.Delete();
                return;
            }
            dst(i,j)=src(rows(i),j);
        }        
}
INTERVAL_VECTOR INTERVAL_VECTORfromINTERVAL_MATRIX(CONST INTERVAL_MATRIX& src){
    INTERVAL_VECTOR out;
    if(RowDimension(src) == 1){
        Resize(out,ColDimension(src));
        ColDimension(src);
        memcpy (out.theElements, src.theElements, ColDimension(src) * sizeof (BIASINTERVAL));
    }
    if(ColDimension(src) == 1){
        Resize(out,RowDimension(src));
        memcpy (out.theElements, src.theElements, RowDimension(src) * sizeof (BIASINTERVAL));
    }
    return out;
}
INTERVAL_MATRIX::INTERVAL_MATRIX(const Eigen::MatrixXd& A){
    INTERVAL_MATRIX B(A.rows(),A.cols());
    for(int i = 0;i < A.rows();i++)
        for(int j = 0;j < A.cols();j++)
            B(i+1,j+1)=A(i,j);
    nRows = RowDimension(B);
    nCols = ColDimension(B);
    theElements = new BIASINTERVAL[nRows*nCols*sizeof(BIASINTERVAL)];
    CheckMemory(theElements);
    memcpy(theElements,B.theElements,nRows*nCols*sizeof(BIASINTERVAL));
}
//==============================================================================
// Recursive definition of determinate using expansion by minors.
//
// Notes: 1) arguments:
//             a (double **) pointer to a pointer of an arbitrary square matrix
//             n (int) dimension of the square matrix
//
//        2) Determinant is a recursive function, calling itself repeatedly
//           each time with a sub-matrix of the original till a terminal
//           2X2 matrix is achieved and a simple determinat can be computed.
//           As the recursion works backwards, cumulative determinants are
//           found till untimately, the final determinate is returned to the
//           initial function caller.
//
//        3) m is a matrix (4X4 in example)  and m13 is a minor of it.
//           A minor of m is a 3X3 in which a row and column of values
//           had been excluded.   Another minor of the submartix is also
//           possible etc.
//             m  a b c d   m13 . . . .
//                e f g h       e f . h     row 1 column 3 is elminated
//                i j k l       i j . l     creating a 3 X 3 sub martix
//                m n o p       m n . p
//
//        4) the following function finds the determinant of a matrix
//           by recursively minor-ing a row and column, each time reducing
//           the sub-matrix by one row/column.  When a 2X2 matrix is
//           obtained, the determinat is a simple calculation and the
//           process of unstacking previous recursive calls begins.
//
//                m n
//                o p  determinant = m*p - n*o
//
//        5) this function uses dynamic memory allocation on each call to
//           build a m X m matrix  this requires **  and * pointer variables
//           First memory allocation is ** and gets space for a list of other
//           pointers filled in by the second call to malloc.
//
//        6) C++ implements two dimensional arrays as an array of arrays
//           thus two dynamic malloc's are needed and have corresponsing
//           free() calles.
//
//        7) the final determinant value is the sum of sub determinants
//
//==============================================================================
INTERVAL Determinant(INTERVAL_MATRIX a)
{
    assert(ColDimension(a) == RowDimension(a));
    INT i,j,j1,j2 ;                    // general loop and matrix subscripts
    INTERVAL det(0) ;                   // init determinant
    INT n = a.nCols;
    INTERVAL_MATRIX m(n-1,n-1);
    if (n == 1) {                 // should not get here
        det = a(1,1) ;
    }else if (n == 2)  {                // basic 2X2 sub-matrix determinate
                                       // definition. When n==2, this ends the
        det = a(1,1) * a(2,2) - a(2,1) * a(1,2);// the recursion series
    }
                                       // recursion continues, solve next sub-matrix
    else {                             // solve the next minor by building a
                                       // sub matrix
        det = 0 ;                      // initialize determinant of sub-matrix

                                           // for each column in sub-matrix
        for (j1 = 1 ; j1 <= n ; j1++) {
                                           // get space for the pointer list

            for (i = 1 ; i <= n-1 ; i++)
            for (i = 2 ; i <= n ; i++) {
                j2 = 1 ;               // start at first sum-matrix column position
                                       // loop to copy source matrix less one column
                for (j = 1 ; j <= n ; j++) {
                    if (j == j1) continue ; // don't copy the minor column element

                    m(i-1,j2) = a(i,j) ;  // copy source element into new sub-matrix
                                            // i-1 because new sub-matrix is one row
                                            // (and column) smaller with excluded minors
                    j2++ ;                  // move to next sub-matrix column position
                    }
                }

            det = det + pow(-1.0,1.0 + j1) * a(1,j1) * Determinant(m) ;
                                            // sum x raised to y power
                                            // recursively get determinant of next
                                            // sub-matrix which is now one
                                            // row & column smaller

        }
    }
    return(det) ;
}
VOID INTERVAL_MATRIX::resize(INT r, INT c){
    assert(r > 0 && c > 0);
    if (theElements != NULL) delete [] theElements;
    nRows = r; nCols = c;
    theElements = new BIASINTERVAL[r * c];
    CheckMemory (theElements);
}