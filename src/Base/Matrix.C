/************************************************************************
 *
 * Implementation of type MATRIX
 * -----------------------------
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
 * $Id: Matrix.C 478 2006-08-09 13:13:30Z keil $
 *
 ************************************************************************/

static const char rcs_id[] = "$Id: Matrix.C 478 2006-08-09 13:13:30Z keil $";

#include <Matrix.h>
#include <RealOp.h>
#include <string.h>
#include <math.h>

#include "IntegerMatrix.h"

MATRIX::MATRIX (CONST MATRIX & x)
{
#ifdef __DONTCOPY__
  IsTemporary = 1;
  nRows = x.nRows; nCols = x.nCols;
  if (x.IsTemporary) {
    theElements = x.theElements;
    *((REAL **) & x.theElements) = NULL;
    *((INT *) & x.nRows) = 0;
    *((INT *) & x.nCols) = 0;
  }
  else {
    theElements = new REAL[nRows * nCols];
    CheckMemory (theElements);
    memcpy (theElements, x.theElements, nRows * nCols * sizeof (REAL));
  }
#else
  nRows = x.nRows; nCols = x.nCols;
  theElements = new REAL[nRows * nCols];
  CheckMemory (theElements);
  memcpy (theElements, x.theElements, nRows * nCols * sizeof (REAL));
#endif
}
MATRIX::MATRIX (INT nRows, INT nCols,std::initializer_list<REAL> IN)
{
    this->nRows = nRows;
    this->nCols = nCols;
    theElements = new REAL[nRows * nCols];
    if (nCols*nRows!=IN.size()) return;
    else
    {
        initializer_list<REAL>::iterator i=IN.begin();
        INT k=0;
        for (i=IN.begin();i!=IN.end();i++) theElements[k++]=(*i);
    }
    
}
MATRIX & MATRIX::operator = (CONST MATRIX & x)
{
#ifdef __DONTCOPY__
  if (x.IsTemporary) {
    if (theElements != NULL) delete [] theElements;
    theElements = x.theElements;
    nRows = x.nRows; nCols = x.nCols;
    ((MATRIX &) x).theElements = NULL;
    ((MATRIX &) x).nRows = 0;
    ((MATRIX &) x).nCols = 0;
  }
  else {
    if (theElements == NULL) {
      theElements = new REAL[x.nRows * x.nCols];
      CheckMemory (theElements);
      nRows = x.nRows; nCols = x.nCols;
    }
    else CheckMatrixDimensions (*this, x);
    memcpy (theElements, x.theElements, nRows * nCols * sizeof (REAL));
  }
#else
  if (theElements == NULL) {
    theElements = new REAL[x.nRows * x.nCols];
    CheckMemory (theElements);
    nRows = x.nRows; nCols = x.nCols;
  }
  else CheckMatrixDimensions (*this, x);
  memcpy (theElements, x.theElements, nRows * nCols * sizeof (REAL));
#endif
  return *this;
}

MATRIX & MATRIX::operator += (CONST MATRIX & x)
{
  CheckMatrixDimensions (*this, x);
  RealOpAddTo (theElements, x.theElements,
	       RowDimension (x) * ColDimension (x));
  return *this;
}

MATRIX & MATRIX::operator -= (CONST MATRIX & x)
{
  CheckMatrixDimensions (*this, x);
  RealOpSubFrom (theElements, x.theElements,
		 RowDimension (x) * ColDimension (x));
  return *this;
}

MATRIX & MATRIX::operator *= (REAL a)
{
  RealOpMulWith (theElements, a,
		 RowDimension (*this) * ColDimension (*this));
  return *this;
}

MATRIX & MATRIX::operator /= (REAL a)
{
  RealOpDivBy (theElements, a,
	       RowDimension (*this) * ColDimension (*this));
  return *this;
}

VOID MATRIX::print(const string& name,CONST Iformat& format){
    if(format == Iformat::MATLAB){
        cout << name << "= [";
        int contEl = 0;
        for(int i = 0;i < nRows;i++){
            for(int j = 0;j < nCols;j++){
                cout << theElements[contEl] << " ";
                contEl++;
            }
            if(i < nRows-1)
                cout << ";" << endl;
        }
        cout << "];" << endl;
    }
}

VOID Resize (MATRIX & x, INT r, INT c)
{
  CheckMatrixRange (r, c);
  if ((r * c) && (x.nRows == r) && (x.nCols == c)) return;
  if (x.theElements != NULL) delete [] x.theElements;
  x.nRows = r; x.nCols = c;
  if (r * c != 0) {
    x.theElements = new REAL[r * c];
    CheckMemory (x.theElements);
  }
  else x.theElements = NULL;
}

MATRIX operator - (CONST MATRIX & a)
{
  INT dim = RowDimension (a) * ColDimension (a);
  MATRIX t (RowDimension (a), ColDimension (a));

  MakeTemporary (t);
  RealOpNeg (t.theElements, a.theElements, dim);
  return t;
}

MATRIX operator + (CONST MATRIX & a, CONST MATRIX & b)
{
  INT dim = RowDimension (a) * ColDimension(a);
  MATRIX t (RowDimension (a), ColDimension (a));

  CheckMatrixDimensions (a, b);
  MakeTemporary (t);
  RealOpAdd (t.theElements, a.theElements, b.theElements, dim);
  return t;
}

MATRIX operator - (CONST MATRIX & a, CONST MATRIX & b)
{
  INT dim = RowDimension (a) * ColDimension(a);
  MATRIX t (RowDimension (a), ColDimension (a));

  CheckMatrixDimensions (a, b);
  MakeTemporary (t);
  RealOpSub (t.theElements, a.theElements, b.theElements, dim);
  return t;
}

MATRIX operator - (CONST MATRIX & a, CONST VECTOR & b)
{
    INT dim = RowDimension (a) * ColDimension(a);
    MATRIX t (RowDimension (a), ColDimension (a));
    if(ColDimension(a) != Dimension(b))return t;

    MakeTemporary (t);
    RealOpSub (t.theElements, a.theElements, b.theElements, dim);
    return t;
}

MATRIX operator * (REAL a, CONST MATRIX & b)
{
  INT dim = RowDimension (b) * ColDimension(b);
  MATRIX t (RowDimension (b), ColDimension (b));

  MakeTemporary (t);
  RealOpMul (t.theElements, a, b.theElements, dim);
  return t;
}
MATRIX operator * (CONST VECTOR& a,CONST MATRIX& b){
    assert(b.rows() == 1);
    MATRIX t(a.rows(),b.cols());
    for(int i = 1;i <= a.rows();i++){
        for(int j = 1;j <= b.cols();j++){
            t(i,j) = a(i)*b(1,j);
        }
    }
    return t;
}
MATRIX operator / (CONST MATRIX & a, REAL b)
{
  INT dim = RowDimension (a) * ColDimension(a);
  MATRIX t (RowDimension (a), ColDimension (a));

  MakeTemporary (t);
  RealOpDiv (t.theElements, a.theElements, b, dim);
  return t;
}

VECTOR operator * (CONST MATRIX & a, CONST VECTOR & b)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  VECTOR t (rows);

  CheckColumnDimensions (a, b);
  MakeTemporary (t);
  RealOpVecMul (t.theElements, a.theElements, b.theElements, rows, cols);
  return t;
}

MATRIX operator * (CONST MATRIX & a, CONST MATRIX & b)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (b);
  INT a_cols = ColDimension (a);
  MATRIX t (rows, cols);

  CheckMatrixMatrixDimensions (a, b);
  MakeTemporary (t);
  RealOpMatMul (t.theElements, a.theElements, b.theElements,
		rows, a_cols, cols);
  return t;
}

INT operator < (CONST MATRIX & a, CONST MATRIX & b)
{
  CheckMatrixDimensions (a, b);
  return RealOpLessThan (a.theElements, b.theElements,
			 RowDimension (a) * ColDimension(a));
}

INT operator <= (CONST MATRIX & a, CONST MATRIX & b)
{
  CheckMatrixDimensions (a, b);
  return RealOpLessEqual (a.theElements, b.theElements,
			  RowDimension (a) * ColDimension(a));
}

INT operator > (CONST MATRIX & a, CONST MATRIX & b)
{
  CheckMatrixDimensions (a, b);
  return RealOpGreaterThan (a.theElements, b.theElements,
			    RowDimension (a) * ColDimension(a));
}

INT operator >= (CONST MATRIX & a, CONST MATRIX & b)
{
  CheckMatrixDimensions (a, b);
  return RealOpGreaterEqual (a.theElements, b.theElements,
			     RowDimension (a) * ColDimension(a));
}
// Calculates  |x_ij|
MATRIX Abs (CONST MATRIX & a)
{
  INT i;
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  MATRIX t (rows, cols);
  REAL *pa, *pt;

  MakeTemporary (t);
  pa = a.theElements; pt = t.theElements;
  for (i = 0; i < rows * cols; i++) *(pt++) = fabs(*(pa++));
  return t;
}

VOID Clear (MATRIX & a)
{
  if (a.theElements != NULL)
    memset (a.theElements, 0, RowDimension (a) * ColDimension (a) * sizeof (REAL));
}

VOID Initialize (MATRIX & a, REAL r)
{
  INT dim = RowDimension (a) * ColDimension (a);
  INT i;
  REAL *pa = a.theElements;

  for (i = 0; i < dim; i++) *(pa++) = r;
}

VECTOR Row (CONST MATRIX & a, INT i)
{
  INT dim = ColDimension (a);
  VECTOR t(dim);

  CheckMatrixRowIndex (i, a);
  MakeTemporary (t);
  memcpy (t.theElements, a.theElements + (i - 1) * dim, dim * sizeof (REAL));
  return t;
}

VECTOR MATRIX::row (INT i) CONST
{
  VECTOR t(nCols);

  CheckMatrixRowIndex (i, (*this));
  MakeTemporary (t);
  memcpy (t.theElements, theElements + (i - 1) * nCols, nCols * sizeof (REAL));
  return t;
}


VECTOR Col (CONST MATRIX & a, INT k)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  INT i;
  REAL *pa, *pt;
  VECTOR t(rows);

  CheckMatrixColIndex (k, a);
  MakeTemporary (t);
  pa = a.theElements + k - 1;
  pt = t.theElements;
  for (i = 0; i < rows; i++, pa += cols) *(pt++) = *pa;
  return t;
}

VECTOR MATRIX::col (INT k) CONST
{
  INT i;
  REAL *pa, *pt;
  VECTOR t(nRows);

  CheckMatrixColIndex (k, (*this));
  MakeTemporary (t);
  pa = theElements + k - 1;
  pt = t.theElements;
  for (i = 0; i < nRows; i++, pa += nCols) *(pt++) = *pa;
  return t;
}


VOID SetRow (MATRIX & a, INT i, CONST VECTOR & t)
{
  INT dim = ColDimension (a);

  CheckMatrixRowIndex (i, a);
  CheckColumnDimensions (a, t);
  memcpy (a.theElements + (i - 1) * dim, t.theElements, dim * sizeof (REAL));
}

VOID SetCol (MATRIX & a, INT k, CONST VECTOR & t)
{
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  INT i;
  REAL *pa, *pt;

  CheckMatrixColIndex (k, a);
  CheckRowDimensions (a, t);
  pa = a.theElements + k - 1;
  pt = t.theElements;
  for (i = 0; i < rows; i++, pa += cols) *pa = *(pt++);
}

ostream & operator << (ostream & os, CONST MATRIX & x)
{
  INT i, j;
  INT rows = RowDimension (x);
  INT cols = ColDimension (x);
  REAL *px = x.theElements;

  os << '(';
  for (i = 0; i < rows; i++) {
    os << '(';
    for (j = 0; j < cols; j++) {
      os << (*(px++));
      if (j < cols - 1) os << " ; ";
    }
    os << ')';
    if (i < rows - 1) os << endl << ' ';
  }
  return os << ')';
}

istream & operator >> (istream & is, MATRIX & x)
{
  INT i, j;
  INT rows = RowDimension (x);
  INT cols = ColDimension (x);
  REAL *px = x.theElements;

  for (i = 0; i < rows; i++)
    for (j = 0; j < cols; j++)
      is >> (*(px++));
  return is;
}
MATRIX MatrixZeros (INT nRows, INT nCols){
    MATRIX out(nRows,nCols);
    for(int i=1;i<=nRows;i++)
        for(int j=1;j<=nCols;j++)
            out(i,j)=0;
    return out;
}
MATRIX MatrixOnes (INT nRows, INT nCols){
    MATRIX out(nRows,nCols);
    for(int i=1;i<=nRows;i++)
        for(int j=1;j<=nCols;j++)
            out(i,j)=0;
    return out;
}

MATRIX MatrixDiag (CONST VECTOR & VEC)
{
    MATRIX out(Dimension(VEC),Dimension(VEC));
    out = MatrixZeros(Dimension(VEC),Dimension(VEC));
    for(int i=1;i<=Dimension(VEC);i++) out(i,i)=VEC(i);
    return out;
}
MATRIX MatrixDiag (INT nRow,INT nCol,CONST VECTOR & VEC)
{
    MATRIX out(nRow,nCol);
    if(nRow != Dimension(VEC)) return out;
    out = MatrixZeros(nRow,nCol);
    for(int i=1;i<=Dimension(VEC);i++)out(i,i)=VEC(i);
    return out;
}
VOID PointwiseMul(MATRIX & dst,const MATRIX src1,CONST MATRIX src2){
    Resize(dst,RowDimension(src1),ColDimension(src1));
    for(int i = 1;i <= RowDimension(src1);i++)
        for(int j = 1;j <= ColDimension(src1);j++)
            dst(i,j) = src1(i,j)*src2(i,j);
}
VOID PointwiseDiv(MATRIX & dst,const MATRIX src1,CONST MATRIX src2){
    Resize(dst,RowDimension(src1),ColDimension(src1));
    for(int i = 1;i <= RowDimension(src1);i++)
        for(int j = 1;j <= ColDimension(src1);j++)
            dst(i,j) = src1(i,j)/src2(i,j);
}
VOID Sum(VECTOR & dst,CONST MATRIX src){
    Resize(dst,ColDimension(src));
    Initialize(dst,0.0);
    for(int i = 1;i <= ColDimension(src);i++)
        for(int j = 1;j <= RowDimension(src);j++)
            dst(i)+=src(i,j);
}
VOID PointwiseSqr(MATRIX & dst,CONST MATRIX& src){
    Resize(dst,RowDimension(src),ColDimension(src));
    Initialize(dst,0.0);
    for(int i = 1;i <= ColDimension(src);i++)
        for(int j = 1;j <= RowDimension(src);j++)
            dst(i,j)=Sqr(src(i,j));
}
VOID Mean(VECTOR& dst,CONST MATRIX& src, INT RowOrCol){
    if(RowOrCol == 1){
        Resize(dst,RowDimension(src));
        for(int i = 1;i <= RowDimension(src);i++)
            for(int j = 1;j <= ColDimension(src);j++)
                dst(i) += src(i,j)/ColDimension(src);
    }
    else{
        Resize(dst,ColDimension(src));
        for(int i = 1;i <= RowDimension(src);i++)
            for(int j = 1;j <= ColDimension(src);j++)
                dst(j) += src(i,j)/RowDimension(src);
    }
}
VOID GetNonHomogeneous(MATRIX& dst,CONST MATRIX& src){
    Resize(dst,RowDimension(src)-1,ColDimension(src));
    VECTOR Colsrc,Coldst;
    for(int i = 1;i <= ColDimension(src);i++){
        Colsrc = Col(src,i);
        GetNonHomogeneous(Coldst,Colsrc);
        SetCol(dst,i,Coldst);
    }
}
VOID GetHomogeneous(MATRIX& dst,CONST MATRIX& src){
    Resize(dst,RowDimension(src)+1,ColDimension(src));
    VECTOR Colsrc,Coldst;
    for(int i = 1;i <= ColDimension(src);i++){
        Colsrc = Col(src,i);
        GetHomogeneous(Coldst,Colsrc);
        SetCol(dst,i,Coldst);
    }
}
VOID MATRIX::hcat(const MATRIX& src1)
{
    assert(src1.nCols != 0);
    assert(src1.nRows != 0);
    if(theElements != NULL){
        REAL *tmptheElements;
        tmptheElements = new REAL[nRows*nCols];
        CheckDimensions(Col(*this,1),Col(src1,1));
        assert(nRows == src1.nRows);
        memcpy(tmptheElements,theElements,nRows*nCols*sizeof(REAL));
        theElements = new REAL[nRows*(nCols+ColDimension(src1))];
        CheckMemory(theElements);
        int contRow1 = 0,contRow2 = 0,contRow3 = 0;
        for(int i = 0;i < nRows;i++){
            if(contRow1 > nRows*(nCols+ColDimension(src1)) || contRow2 > (nRows*nCols) 
                    || contRow3 > src1.nRows*src1.nCols){
                cerr << "Wrong dimension" << endl;
            }
            memcpy(&theElements[contRow1],&tmptheElements[contRow2],nCols*sizeof(REAL));
            contRow1 += nCols;
            contRow2 += nCols;
            memcpy(&theElements[contRow1],&src1.theElements[contRow3],src1.nCols*sizeof(REAL));
            contRow1 += src1.nCols;
            contRow3 += src1.nCols;
        }
        nCols = (nCols+ColDimension(src1));
        delete [] tmptheElements;
    }
    else{
        nRows = RowDimension(src1);
        nCols = ColDimension(src1);
        theElements = new REAL[nRows*nCols];
        CheckMemory(theElements);
        memcpy(theElements,src1.theElements,nRows*nCols*sizeof(REAL));
    }
}
VOID MATRIX::hcat(const VECTOR& src1)
{
    assert(Dimension(src1) > 0);
    if(theElements != NULL){
        CheckRowDimensions(*this,src1);
        REAL *tmptheElements;
        tmptheElements = new REAL[nRows*nCols];
        assert(nRows == Dimension(src1));
        memcpy(tmptheElements,theElements,nRows*nCols*sizeof(REAL));
        theElements = new REAL[nRows*(nCols+1)];
        CheckMemory(theElements);
        int contRow1 = 0,contRow2 = 0,contRow3 = 0;
        for(int i = 0;i < nRows;i++){
            if(contRow1 > nRows*(nCols+1) || contRow2 > (nRows*nCols) 
                    || contRow3 > Dimension(src1)*1){
                cerr << "Wrong dimension" << endl;
            }
            memcpy(&theElements[contRow1],&tmptheElements[contRow2],nCols*sizeof(REAL));
            contRow1 += nCols;
            contRow2 += nCols;
            memcpy(&theElements[contRow1],&src1.theElements[contRow3],1*sizeof(REAL));
            contRow1++;
            contRow3++;
        }
        nCols = (nCols+1);
        delete [] tmptheElements;
    }
    else{
        nRows = Dimension(src1);
        nCols = 1;
        theElements = new REAL[nRows*nCols];
        CheckMemory(theElements);
        memcpy(theElements,src1.theElements,nRows*nCols*sizeof(REAL));
    }
}
void hcat(MATRIX & dst,CONST MATRIX & src2)
{
    MATRIX out;
    if(dst.theElements != NULL){
        Resize(out,dst.nRows,dst.nCols+src2.nCols);
        assert(out.nRows == RowDimension(src2));
    }else{
        Resize(out,src2.nRows,src2.nCols);
    }
    INT i;
    for(i=1;i<=ColDimension(dst);i++)
        SetCol(out,i,Col(dst,i));
    for(int j=i;j<=ColDimension(src2)+ColDimension(dst);j++)
        SetCol(out,j,Col(src2,j-ColDimension(dst)));
    Resize(dst,RowDimension(out),ColDimension(out));
    dst = out;
}
void hcat(MATRIX& dst,CONST VECTOR& src)
{
    MATRIX out;
    if(dst.theElements != NULL){
        Resize(out,dst.nRows,dst.nCols+1);
        if(out.nRows != Dimension(src)) return;
    }else{
        Resize(out,Dimension(src),1);
    }
    INT i;
    for(i=1;i<=ColDimension(dst);i++)
        SetCol(out,i,Col(dst,i));
    SetCol(out,i,src);
    Resize(dst,RowDimension(out),ColDimension(out));
    dst = out;
}
VOID MATRIX::vcat(const MATRIX& src1)
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
    MATRIX out;
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
VOID MATRIX::vcat(const VECTOR& src1)
{
    MATRIX out(nRows+1,nCols);
    if(out.nCols != Dimension(src1)) return;
    INT i,j;
    for(i=1;i<=nRows;i++)
        SetRow(out,i,Row(*this,i));
    SetRow(out,i,src1);
    *this=out;
}
void MATRIX::vcat(CONST MATRIX & src1,CONST MATRIX & src2)
{
    if(theElements != NULL) delete [] theElements;
    nRows = src1.nRows;
    nCols = src1.nCols+src2.nCols;
    theElements = new REAL[nRows * nCols * sizeof(REAL)];
    CheckMemory(theElements);
    memcpy (theElements,src1.theElements,src1.nRows * src1.nCols * sizeof (REAL));
    memcpy (&theElements[src1.nRows * src1.nCols * sizeof (REAL)],src2.theElements,
            src2.nRows * src2.nCols * sizeof (REAL));
}
void MATRIX::vcat(const MATRIX& MAT,CONST VECTOR& VEC)
{
    MATRIX out(MAT.nRows,MAT.nCols+1);
    if(out.nRows != Dimension(VEC)) return;
    INT i;
    for(i=1;i<=RowDimension(MAT);i++)
        SetCol(out,i,Row(MAT,i));
    SetCol(out,i,VEC);
    *this=out;
}
VOID GetMatrixOfRowColIdx(MATRIX& dst,
                        CONST MATRIX& src, 
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
VOID GetMatrixOfColIdx(MATRIX& dst,
                            CONST MATRIX& src,
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
VOID GetMatrixOfRowIdx(MATRIX& dst,
                            CONST MATRIX& src,
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
MATRIX MATRIX::Box(INT iniRow, INT endRow, INT iniCol, INT endCol) CONST{
    MATRIX mNULL;
    CheckMatrixRowIndex(iniRow,(*this));
    CheckMatrixRowIndex(endRow,(*this));
    CheckMatrixColIndex(iniCol,(*this));
    CheckMatrixColIndex(endCol,(*this));
    MATRIX box((endRow-iniRow)+1,(endCol-iniCol)+1);
    INT row = 1;
    for(int i = iniRow;i <= endRow;i++,row++){
        INT col = 1;
        for(int j = iniCol;j <= endCol;j++,col++){
            box(row,col)=theElements[((i-1)*nCols+j)-1];
        }
    }
    return box;
}
MATRIX Diag(CONST VECTOR& VEC){
    MATRIX out(Dimension(VEC),Dimension(VEC));
    Initialize(out,0);
    for(int i=1;i<=Dimension(VEC);i++) out(i,i)=VEC(i);
    return out;    
}
bool MATRIX::contains(const VECTOR& A){
    for(int j = 0;j < nCols;j++){
        bool equal = true;
        for(int i = 0;i < nRows;i++){
            if((*this)(i,j) != A(i)){
                equal = false;
                break;
            }
        }
        if(equal)return true;
    }
}
VECTOR MATRIX::max(){
    VECTOR out(nCols);
    out.setzeros();
    for(int i = 1;i <= nRows;i++)
        out(i) = (*this).row(i).max();
    return out;
}