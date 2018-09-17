/************************************************************************
 *
 * Definition of type MATRIX
 * -------------------------
 *
 * Copyright (C) 1993, 1995, 1997 Olaf Knueppel
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
 * $Id: Matrix.h 478 2006-08-09 13:13:30Z keil $
 *
 ************************************************************************/

#ifndef __MATRIX__
#define __MATRIX__

#include <Vector.h>
#include <Configuration.h>
#include <Error.h>
#include <initializer_list>
#include <assert.h>


class MATRIX {
  INT nRows;
  INT nCols;
#ifdef __DONTCOPY__
  INT IsTemporary;
#endif
public:
  REAL *theElements;
  MATRIX ()
    {
#ifdef __DONTCOPY__
      IsTemporary = 0;
#endif
      nRows = nCols = 0; theElements = NULL; }
  MATRIX (INT r, INT c)
    {
#ifdef __DONTCOPY__
      IsTemporary = 0;
#endif
      CheckMatrixRange (r, c);
      nRows = r; nCols = c;
      theElements = new REAL[r * c];
      CheckMemory (theElements);
    }
  MATRIX (INT nRows, INT nCols,std::initializer_list<REAL> IN);
  ~MATRIX ()
    { if (theElements != NULL) delete [] theElements; }
  MATRIX (CONST MATRIX &);
  REAL & operator () (INT i, INT j) CONST
    { CheckMatrixIndex (i, j, *this); return theElements[(i-1) * nCols + (j-1)]; }
  MATRIX & operator =  (CONST MATRIX &);
  MATRIX & operator += (CONST MATRIX &);
  MATRIX & operator -= (CONST MATRIX &);
  MATRIX & operator *= (REAL);
  MATRIX & operator /= (REAL);
  VOID print(CONST string& name,CONST Iformat& format = Iformat::MATLAB);
  VECTOR row (INT) CONST;
  VECTOR col (INT) CONST;
  INT cols() CONST{return nCols;}
  INT rows() CONST{return nRows;}
  bool empty( ) {return theElements == NULL;}
  VECTOR max();
  MATRIX Box(INT iniRow, INT endRow, INT iniCol, INT endCol) CONST;
  friend INT RowDimension (CONST MATRIX &);
  friend INT ColDimension (CONST MATRIX &);
  friend VOID Resize (MATRIX &, INT, INT);
  friend VOID MakeTemporary (MATRIX &);
  friend VOID MakePermanent (MATRIX &);
  friend VOID Clear (MATRIX &);
  friend VOID Initialize (MATRIX &, REAL);
  friend VECTOR Row (CONST MATRIX &, INT);
  friend VECTOR Col (CONST MATRIX &, INT);
  friend VOID SetRow (MATRIX &, INT, CONST VECTOR &);
  friend VOID SetCol (MATRIX &, INT, CONST VECTOR &);
  VOID Delete(){ delete theElements; theElements = NULL; nRows = 0; nCols = 0;}
  VOID hcat(CONST MATRIX &);
  VOID hcat(CONST VECTOR &);
  bool contains(CONST VECTOR&);
  friend void hcat(MATRIX & dst, CONST MATRIX & src);
  friend void hcat(MATRIX & dst, CONST VECTOR & src);
  VOID vcat(CONST MATRIX &);
  VOID vcat(CONST VECTOR &);
  void vcat(CONST MATRIX &, CONST MATRIX &);
  void vcat(CONST MATRIX &, CONST VECTOR &);
  friend MATRIX operator + (CONST MATRIX &);
  friend MATRIX operator - (CONST MATRIX &);
  friend MATRIX operator + (CONST MATRIX &, CONST MATRIX &);
  friend MATRIX operator + (CONST MATRIX &, CONST VECTOR &);
  friend MATRIX operator - (CONST MATRIX &, CONST MATRIX &);
  friend MATRIX operator * (REAL          , CONST MATRIX &);
  friend MATRIX operator / (CONST MATRIX &, REAL          );
  friend VECTOR operator * (CONST MATRIX &, CONST VECTOR &);
  friend MATRIX operator * (CONST VECTOR &,CONST MATRIX  &);
  friend MATRIX operator * (CONST MATRIX &, CONST MATRIX &);
  friend INT    operator <  (CONST MATRIX &, CONST MATRIX &);
  friend INT    operator <= (CONST MATRIX &, CONST MATRIX &);
  friend INT    operator >  (CONST MATRIX &, CONST MATRIX &);
  friend INT    operator >= (CONST MATRIX &, CONST MATRIX &);
  friend MATRIX Abs (CONST MATRIX &);
  friend ostream & operator << (ostream &, CONST MATRIX &);
  friend istream & operator >> (istream &, MATRIX &);
  friend bool operator != (CONST MATRIX& src1,CONST MATRIX& src2);
  friend MATRIX MatrixDiag (CONST VECTOR &);
  friend MATRIX MatrixDiag (INT,INT,CONST VECTOR &);
  friend MATRIX MatrixZeros (INT nRows, INT nCols);
  friend MATRIX MatrixOnes (INT nRows, INT nCols);
  friend VOID PointwiseMul(MATRIX & dst, const MATRIX src1,CONST MATRIX src2);
  friend VOID PointwiseDiv(MATRIX & dst,const MATRIX src1,CONST MATRIX src2);
  friend VOID PointwiseSqr(MATRIX & dst,CONST MATRIX& src);
  friend VOID Sum(VECTOR& dst,CONST MATRIX src);
  friend VOID Mean(VECTOR& dst,CONST MATRIX& src,INT RowOrCol = 2);
  friend VOID GetNonHomogeneous(MATRIX& dst,CONST MATRIX& src);
  friend VOID GetHomogeneous(MATRIX& dst,CONST MATRIX& src);
  friend VOID GetMatrixOfRowColIdx(MATRIX& dst,
                        CONST MATRIX& src, 
                        CONST VECTOR& rows,
                        CONST VECTOR& cols);
  friend VOID GetMatrixOfColIdx(MATRIX& dst,
                            CONST MATRIX& src,
                            CONST VECTOR& cols);
  friend VOID GetMatrixOfRowIdx(MATRIX& dst,
                            CONST MATRIX& src,
                            CONST VECTOR& rows);
  friend MATRIX Diag(CONST VECTOR&);
};

inline INT RowDimension (CONST MATRIX & x) {
  return x.nRows; 
}

inline INT ColDimension (CONST MATRIX & x) { 
  return x.nCols; 
}

VOID Resize (MATRIX &, INT, INT);

#ifdef __DONTCOPY__
inline VOID MakeTemporary (MATRIX & x) { 
  x.IsTemporary = 1; 
}

inline VOID MakePermanent (MATRIX & x) { 
  x.IsTemporary = 0; 
}
#else
inline VOID MakeTemporary (MATRIX & x) { }

inline VOID MakePermanent (MATRIX & x) { }
#endif

VOID Clear (MATRIX &);
VOID Initialize (MATRIX &, REAL);
VECTOR Row (CONST MATRIX &, INT);
VECTOR Col (CONST MATRIX &, INT);
VOID SetRow (MATRIX &, INT, CONST VECTOR &);
VOID SetCol (MATRIX &, INT, CONST VECTOR &);

inline MATRIX operator + (CONST MATRIX & a) {
  return (MATRIX &) a; 
}

MATRIX operator - (CONST MATRIX &);
MATRIX operator + (CONST MATRIX &, CONST MATRIX &);
MATRIX operator - (CONST MATRIX &, CONST MATRIX &);
MATRIX operator - (CONST MATRIX &, CONST VECTOR &);
MATRIX operator * (REAL          , CONST MATRIX &);
MATRIX operator / (CONST MATRIX &, REAL          );
MATRIX operator * (CONST MATRIX &, CONST MATRIX &);
VECTOR operator * (CONST MATRIX &, CONST VECTOR &);
MATRIX operator * (CONST VECTOR& a,CONST MATRIX& b);
INT    operator <  (CONST MATRIX &, CONST MATRIX &);
INT    operator <= (CONST MATRIX &, CONST MATRIX &);
INT    operator >  (CONST MATRIX &, CONST MATRIX &);
INT    operator >= (CONST MATRIX &, CONST MATRIX &);
MATRIX Abs (CONST MATRIX &);
ostream & operator << (ostream &, CONST MATRIX &);
istream & operator >> (istream &, MATRIX &);
MATRIX MatrixDiag (CONST VECTOR &);
MATRIX MatrixDiag (INT,INT,CONST VECTOR &);
MATRIX MatrixZeros (INT nRows, INT nCols);
MATRIX MatrixOnes (INT nRows, INT nCols);
VOID PointwiseMul(MATRIX & dst, const MATRIX src1,CONST MATRIX src2);
VOID PointwiseDiv(MATRIX & dst,const MATRIX src1,CONST MATRIX src2);
VOID PointwiseSqr(MATRIX & dst,CONST MATRIX& src);
VOID Sum(VECTOR& dst,CONST MATRIX src);
VOID Mean(VECTOR& dst,CONST MATRIX& src,INT RowOrCol);
VOID GetNonHomogeneous(MATRIX& dst,CONST MATRIX& src);
VOID GetHomogeneous(MATRIX& dst,CONST MATRIX& src);
void hcat(MATRIX &, CONST VECTOR &);
void hcat(MATRIX & dst, CONST MATRIX & src);
VOID GetMatrixOfRowColIdx(MATRIX& dst,
                        CONST MATRIX& src, 
                        CONST VECTOR& rows,
                        CONST VECTOR& cols);
VOID GetMatrixOfColIdx(MATRIX& dst,
                            CONST MATRIX& src,
                            CONST VECTOR& cols);
VOID GetMatrixOfRowIdx(MATRIX& dst,
                            CONST MATRIX& src,
                            CONST VECTOR& rows);
MATRIX Diag(CONST VECTOR&);

#endif /* __MATRIX__ */
