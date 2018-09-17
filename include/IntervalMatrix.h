/************************************************************************
 *
 * Definition of type INTERVAL_MATRIX
 * ----------------------------------
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
 * $Id: IntervalMatrix.h 478 2006-08-09 13:13:30Z keil $
 *
 ************************************************************************/

#ifndef __INTERVAL_MATRIX__
#define __INTERVAL_MATRIX__


#include <eigen3/Eigen/Core>
#include <Matrix.h>
#include <Error.h>
#include <IntervalVector.h>
#include <memory>
#include <Configuration.h>
#include <assert.h>
#include <exception>

class INTERVAL_MATRIX {
  INT nRows;
  INT nCols;
#ifdef __DONTCOPY__
  INT IsTemporary;
#endif
public:
  BIASINTERVAL *theElements;
  INTERVAL_MATRIX (){
#ifdef __DONTCOPY__
      IsTemporary = 0;
#endif
      nRows = 0; nCols = 0; theElements = NULL;
    };
  INTERVAL_MATRIX (INT r, INT c)
    {
#ifdef __DONTCOPY__
      IsTemporary = 0;
#endif
      CheckMatrixRange (r, c);
      nRows = r; nCols = c;
      theElements = new BIASINTERVAL[r * c];
      CheckMemory (theElements);
    }
  ~INTERVAL_MATRIX ()
  { if (theElements != NULL){
      delete [] theElements;
      theElements = NULL;
      nRows = 0;
      nCols = 0;
    }
  }
  INTERVAL_MATRIX (CONST INTERVAL_MATRIX &);
  INTERVAL_MATRIX(CONST INTERVAL_VECTOR & x);
  INTERVAL_MATRIX (INT nRows, INT nCols,std::initializer_list<INTERVAL> IN);
  INTERVAL_MATRIX(const Eigen::MatrixXd& A);
  INTERVAL & operator () (INT i, INT j) CONST
    { assert(i <= nRows && j <= nCols); return * ((INTERVAL *)(theElements + (i-1) * nCols + (j-1))); }
  INTERVAL_MATRIX & operator =  (CONST INTERVAL_MATRIX &);
  INTERVAL_MATRIX & operator =  (CONST MATRIX &);
  INTERVAL_MATRIX & operator += (CONST INTERVAL_MATRIX &);
  INTERVAL_MATRIX & operator -= (CONST INTERVAL_MATRIX &);
  INTERVAL_MATRIX & operator *= (CONST INTERVAL &);
  INTERVAL_MATRIX & operator /= (CONST INTERVAL &);
  INTERVAL_MATRIX & operator += (CONST MATRIX &);
  INTERVAL_MATRIX & operator -= (CONST MATRIX &);
  INTERVAL_MATRIX & operator *= (REAL);
  INTERVAL_MATRIX & operator /= (REAL);
  /*Lê uma parte da matriz, definida pelos limites iniciais
   e finais.*/
  INTERVAL_MATRIX Box(INT iniRow, INT endRow, INT iniCol, INT endCol);
  VOID Delete(){ 
    if(theElements != NULL){
        delete [] theElements; 
        theElements = NULL; 
        nRows = 0; 
        nCols = 0;
    }
  }
  INT rows() CONST {return nRows;}
  INT cols() CONST {return nCols;}
  /*Concatena colunas a matrix this*/
  VOID hcat(CONST INTERVAL_MATRIX &);
  /*Concatena colunas a matrix this*/
  VOID hcat(CONST INTERVAL_VECTOR &);
  /*Concatena colunas a matrix this*/
  void hcat(CONST INTERVAL_MATRIX &, CONST INTERVAL_MATRIX &);
  /*Concatena colunas a matrix this*/
  void hcat(CONST INTERVAL_MATRIX &, CONST INTERVAL_VECTOR &);
  /*Concatena linhas a matrix this*/
  VOID vcat(CONST INTERVAL_MATRIX &);
  /*Concatena linhas a matrix this*/
  VOID vcat(CONST INTERVAL_VECTOR &);
  /*Concatena linhas a matrix this*/
  void vcat(CONST INTERVAL_MATRIX &, CONST INTERVAL_MATRIX &);
  /*Concatena linhas a matrix this*/
  void vcat(CONST INTERVAL_MATRIX &, CONST INTERVAL_VECTOR &);
  bool hasNan();
  bool hasInf();
  bool isSquare() const{return nRows == nCols;};
  double absmax() const;
  bool empty() const{return ((nRows == 0) || (nCols == 0));}
  INTERVAL_VECTOR row (INT i) CONST;
  INTERVAL_VECTOR col (INT j) CONST;
  INTERVAL_VECTOR toINTERVAL_VECTOR();
  /*Retorna uma matrix com o diametro
   de cada um dos elementos.*/
  MATRIX diam();
  /*Retona os elementos da diagonal principal
   da matriz em um vetor intervalar*/
  INTERVAL_VECTOR diag();
  /*Redimensiona a matriz eliminando todos
   os elementos armazendos*/
  VOID resize(INT rows,INT cols);
  /*Calcula o determinante da matriz*/
  INTERVAL det();
  /*Decomposição LU da matrix.
   Saída:
        Matriz A = U/L*/
  INTERVAL_MATRIX LU();
  MATRIX compare(CONST INTERVAL_MATRIX& );
  friend INT RowDimension (CONST INTERVAL_MATRIX &);
  friend INT ColDimension (CONST INTERVAL_MATRIX &);
  friend INT Dimension(CONST INTERVAL_MATRIX &);
  friend VOID Resize (INTERVAL_MATRIX &, INT, INT);
  friend VOID MakeTemporary (INTERVAL_MATRIX &);
  friend VOID MakePermanent (INTERVAL_MATRIX &);
  friend VOID Clear (INTERVAL_MATRIX &);
  friend VOID Initialize (INTERVAL_MATRIX &, CONST INTERVAL &);
  friend VOID Reshape(INTERVAL_MATRIX&,INT,INT,const INTERVAL_VECTOR&);
  friend INTERVAL_VECTOR Row (CONST INTERVAL_MATRIX &, INT);
  friend INTERVAL_VECTOR Col (CONST INTERVAL_MATRIX &, INT);
  friend VOID SetRow (INTERVAL_MATRIX &, INT, CONST INTERVAL_VECTOR &);
  friend VOID SetCol (INTERVAL_MATRIX &, INT, CONST INTERVAL_VECTOR &);
  friend MATRIX Inf  (CONST INTERVAL_MATRIX &);
  friend MATRIX Sup  (CONST INTERVAL_MATRIX &);
  friend MATRIX Mid  (CONST INTERVAL_MATRIX &);
  friend MATRIX Diam (CONST INTERVAL_MATRIX &);
  friend MATRIX Abs  (CONST INTERVAL_MATRIX &);
  friend INT Intersection (INTERVAL_MATRIX &, CONST INTERVAL_MATRIX &, CONST INTERVAL_MATRIX &);
  friend INT operator <= (CONST MATRIX &         , CONST INTERVAL_MATRIX &);
  friend INT operator <= (CONST INTERVAL_MATRIX &, CONST INTERVAL_MATRIX &);
  friend INT operator <  (CONST MATRIX &         , CONST INTERVAL_MATRIX &);
  friend INT operator <  (CONST INTERVAL_MATRIX &, CONST INTERVAL_MATRIX &);
  friend INT operator == (CONST INTERVAL_MATRIX &, CONST INTERVAL_MATRIX &);
  friend INT operator != (CONST INTERVAL_MATRIX &, CONST INTERVAL_MATRIX &);
  friend INTERVAL_MATRIX Hull (CONST MATRIX &);
  friend INTERVAL_MATRIX Hull (CONST MATRIX &, CONST MATRIX &);
  friend INTERVAL_MATRIX Hull (CONST MATRIX &, CONST INTERVAL_MATRIX &);
  friend INTERVAL_MATRIX Hull (CONST INTERVAL_MATRIX &, CONST MATRIX &);
  friend INTERVAL_MATRIX Hull (CONST INTERVAL_MATRIX &, CONST INTERVAL_MATRIX &);
  friend INTERVAL_MATRIX SymHull (CONST MATRIX &);
  friend INTERVAL_MATRIX operator + (CONST INTERVAL_MATRIX &);
  friend INTERVAL_MATRIX operator - (CONST INTERVAL_MATRIX &);
  friend INTERVAL_MATRIX operator + (CONST MATRIX &         , CONST INTERVAL_MATRIX &);
  friend INTERVAL_MATRIX operator + (CONST INTERVAL_MATRIX &, CONST MATRIX &         );
  friend INTERVAL_MATRIX operator + (CONST INTERVAL_MATRIX &, CONST INTERVAL_MATRIX &);
  friend INTERVAL_MATRIX AddBounds  (CONST MATRIX &, CONST MATRIX &);
  friend INTERVAL_MATRIX operator - (CONST MATRIX &         , CONST INTERVAL_MATRIX &);
  friend INTERVAL_MATRIX operator - (CONST INTERVAL_MATRIX &, CONST MATRIX &         );
  friend INTERVAL_MATRIX operator - (CONST INTERVAL_MATRIX &, CONST INTERVAL_MATRIX &);
  friend INTERVAL_MATRIX SubBounds  (CONST MATRIX &, CONST MATRIX &);
  friend INTERVAL_MATRIX operator * (REAL            , CONST INTERVAL_MATRIX &);
  friend INTERVAL_MATRIX operator * (CONST INTERVAL &, CONST MATRIX &         );
  friend INTERVAL_MATRIX operator * (CONST INTERVAL &, CONST INTERVAL_MATRIX &);
  friend INTERVAL_MATRIX MulBounds  (REAL, CONST MATRIX &);
  friend INTERVAL_MATRIX operator / (CONST INTERVAL_MATRIX &, REAL            );
  friend INTERVAL_MATRIX operator / (CONST MATRIX &         , CONST INTERVAL &);
  friend INTERVAL_MATRIX operator / (CONST INTERVAL_MATRIX &, CONST INTERVAL &);
  friend INTERVAL_MATRIX DivBounds  (CONST MATRIX &, REAL);
  friend INTERVAL_VECTOR operator * (CONST MATRIX &         , CONST INTERVAL_VECTOR &);
  friend INTERVAL_VECTOR operator * (CONST INTERVAL_MATRIX &, CONST VECTOR &         );
  friend INTERVAL_VECTOR operator * (CONST INTERVAL_MATRIX &, CONST INTERVAL_VECTOR &);
  friend INTERVAL_VECTOR MulBounds  (CONST MATRIX &, CONST VECTOR &);
  friend INTERVAL_MATRIX operator * (CONST MATRIX &         , CONST INTERVAL_MATRIX &);
  friend INTERVAL_MATRIX operator * (CONST INTERVAL_MATRIX &, CONST MATRIX &         );
  friend INTERVAL_MATRIX operator * (CONST INTERVAL_MATRIX &, CONST INTERVAL_MATRIX &);
  friend INTERVAL_MATRIX MulBounds  (CONST MATRIX &, CONST MATRIX &);
  friend INTERVAL_MATRIX Eye (CONST INT);
  friend INTERVAL_MATRIX Eye (CONST INT,CONST INT);
  friend INTERVAL_MATRIX Diag (CONST INTERVAL_VECTOR &);
  friend INTERVAL_MATRIX Diag (INT,INT,CONST INTERVAL_VECTOR &);
  friend INTERVAL_VECTOR Diag (CONST INTERVAL_MATRIX& src);
  friend INTERVAL_MATRIX Zeros (INT, INT);
  friend INTERVAL_MATRIX Ones (INT, INT);
  friend INTERVAL_MATRIX Random (INT,INT);
  friend VOID PointwiseMul(INTERVAL_MATRIX & dst, const INTERVAL_MATRIX src1,CONST INTERVAL_MATRIX src2);
  friend VOID PointwiseDiv(INTERVAL_MATRIX & dst,const INTERVAL_MATRIX src1,CONST INTERVAL_MATRIX src2);
  friend VOID PointwiseSqr(INTERVAL_MATRIX & dst,CONST INTERVAL_MATRIX& src);
  friend VOID Sum(INTERVAL_VECTOR& dst,CONST INTERVAL_MATRIX src);
  friend VOID GetNonHomogeneous(INTERVAL_MATRIX& dst,CONST INTERVAL_MATRIX& src);
  friend VOID GetHomogeneous(INTERVAL_MATRIX& dst,CONST INTERVAL_MATRIX& src);
  friend ostream & operator << (ostream &, CONST INTERVAL_MATRIX &);
  friend istream & operator >> (istream &, INTERVAL_MATRIX &);
  friend bool HasDivisionByZero(CONST INTERVAL_MATRIX& src);
  friend VOID GetMatrixOfRowColIdx(INTERVAL_MATRIX& dst,
                        CONST INTERVAL_MATRIX& src, 
                        CONST VECTOR& rows,
                        CONST VECTOR& cols);
  friend VOID GetMatrixOfColIdx(INTERVAL_MATRIX& dst,
                            CONST MATRIX& src,
                            CONST VECTOR& cols);
  friend VOID GetMatrixOfRowIdx(INTERVAL_MATRIX& dst,
                            CONST INTERVAL_MATRIX& src,
                            CONST VECTOR& rows);
  friend INTERVAL Determinant(INTERVAL_MATRIX a);
};

inline INT RowDimension (CONST INTERVAL_MATRIX & x) {
  return x.nRows; 
}

inline INT ColDimension (CONST INTERVAL_MATRIX & x) { 
  return x.nCols; 
}

inline INT Dimension(CONST INTERVAL_MATRIX & x){
    return x.nRows*x.nCols;
}
VOID Resize (INTERVAL_MATRIX &, INT, INT);

#ifdef __DONTCOPY__
inline VOID MakeTemporary (INTERVAL_MATRIX & x) { 
  x.IsTemporary = 1; 
}

inline VOID MakePermanent (INTERVAL_MATRIX & x) { 
  x.IsTemporary = 0; 
}
#else
inline VOID MakeTemporary (INTERVAL_MATRIX & x) { }

inline VOID MakePermanent (INTERVAL_MATRIX & x) { }
#endif

VOID Clear (INTERVAL_MATRIX &);
VOID Initialize (INTERVAL_MATRIX &, CONST INTERVAL &);
VOID Reshape(INTERVAL_MATRIX&,INT,INT,const INTERVAL_VECTOR&);
INTERVAL_VECTOR Row (CONST INTERVAL_MATRIX &, INT);
INTERVAL_VECTOR Col (CONST INTERVAL_MATRIX &, INT);
VOID SetRow (INTERVAL_MATRIX &, INT, CONST INTERVAL_VECTOR &);
VOID SetCol (INTERVAL_MATRIX &, INT, CONST INTERVAL_VECTOR &);
MATRIX Inf (CONST INTERVAL_MATRIX &);
MATRIX Sup (CONST INTERVAL_MATRIX &);
MATRIX Mid (CONST INTERVAL_MATRIX &);
MATRIX Diam (CONST INTERVAL_MATRIX &);
MATRIX Abs (CONST INTERVAL_MATRIX &);
INT Intersection (INTERVAL_MATRIX &, CONST INTERVAL_MATRIX &, CONST INTERVAL_MATRIX &);
INT operator <= (CONST MATRIX &, CONST INTERVAL_MATRIX &);
INT operator <= (CONST INTERVAL_MATRIX &, CONST INTERVAL_MATRIX &);
INT operator <  (CONST MATRIX &, CONST INTERVAL_MATRIX &);
INT operator <  (CONST INTERVAL_MATRIX &, CONST INTERVAL_MATRIX &);
INT operator == (CONST INTERVAL_MATRIX &, CONST INTERVAL_MATRIX &);
INT operator != (CONST INTERVAL_MATRIX &, CONST INTERVAL_MATRIX &);
INTERVAL_MATRIX Hull (CONST MATRIX &);
INTERVAL_MATRIX Hull (CONST MATRIX &, CONST MATRIX &);
INTERVAL_MATRIX Hull (CONST MATRIX &, CONST INTERVAL_MATRIX &);
INTERVAL_MATRIX Hull (CONST INTERVAL_MATRIX &, CONST MATRIX &);
INTERVAL_MATRIX Hull (CONST INTERVAL_MATRIX &, CONST INTERVAL_MATRIX &);

inline INTERVAL_MATRIX SymHull (CONST MATRIX & x) { 
  return Hull (-x, x); 
}

inline INTERVAL_MATRIX operator + (CONST INTERVAL_MATRIX & a) { 
  return (INTERVAL_MATRIX &) a; 
}

INTERVAL_MATRIX operator - (CONST INTERVAL_MATRIX &);
INTERVAL_MATRIX operator + (CONST MATRIX &         , CONST INTERVAL_MATRIX &);
INTERVAL_MATRIX operator + (CONST INTERVAL_MATRIX &, CONST MATRIX &         );
INTERVAL_MATRIX operator + (CONST INTERVAL_MATRIX &, CONST INTERVAL_MATRIX &);
INTERVAL_MATRIX AddBounds  (CONST MATRIX &, CONST MATRIX &);
INTERVAL_MATRIX operator - (CONST MATRIX &         , CONST INTERVAL_MATRIX &);
INTERVAL_MATRIX operator - (CONST INTERVAL_MATRIX &, CONST MATRIX &         );
INTERVAL_MATRIX operator - (CONST INTERVAL_MATRIX &, CONST INTERVAL_MATRIX &);
INTERVAL_MATRIX SubBounds  (CONST MATRIX &, CONST MATRIX &);
INTERVAL_MATRIX operator * (REAL            , CONST INTERVAL_MATRIX &);
INTERVAL_MATRIX operator * (CONST INTERVAL &, CONST MATRIX &         );
INTERVAL_MATRIX operator * (CONST INTERVAL &, CONST INTERVAL_MATRIX &);
INTERVAL_MATRIX MulBounds  (REAL, CONST MATRIX &);
INTERVAL_MATRIX operator / (CONST INTERVAL_MATRIX &, REAL            );
INTERVAL_MATRIX operator / (CONST MATRIX &         , CONST INTERVAL &);
INTERVAL_MATRIX operator / (CONST INTERVAL_MATRIX &, CONST INTERVAL &);
INTERVAL_MATRIX DivBounds  (CONST MATRIX &, REAL);
INTERVAL_VECTOR operator * (CONST MATRIX &         , CONST INTERVAL_VECTOR &);
INTERVAL_VECTOR operator * (CONST INTERVAL_MATRIX &, CONST VECTOR &         );
INTERVAL_VECTOR operator * (CONST INTERVAL_MATRIX &, CONST INTERVAL_VECTOR &);
INTERVAL_VECTOR MulBounds  (CONST MATRIX &, CONST VECTOR &);
INTERVAL_MATRIX operator * (CONST MATRIX &         , CONST INTERVAL_MATRIX &);
INTERVAL_MATRIX operator * (CONST INTERVAL_MATRIX &, CONST MATRIX &         );
INTERVAL_MATRIX operator * (CONST INTERVAL_MATRIX &, CONST INTERVAL_MATRIX &);
INTERVAL_MATRIX MulBounds  (CONST MATRIX &, CONST MATRIX &);
INTERVAL_MATRIX Eye (CONST INT);
INTERVAL_MATRIX Eye (CONST INT,CONST INT);
INTERVAL_MATRIX Diag (CONST INTERVAL_VECTOR &);
INTERVAL_MATRIX Diag (INT,INT,CONST INTERVAL_VECTOR &);
INTERVAL_MATRIX Zeros (INT, INT);
INTERVAL_MATRIX Ones (INT, INT);
INTERVAL_MATRIX Random (INT,INT);
INTERVAL_VECTOR Diag (CONST INTERVAL_MATRIX& src);
VOID PointwiseMul(INTERVAL_MATRIX & dst, const INTERVAL_MATRIX src1,CONST INTERVAL_MATRIX src2);
VOID PointwiseDiv(INTERVAL_MATRIX & dst,const INTERVAL_MATRIX src1,CONST INTERVAL_MATRIX src2);
VOID PointwiseSqr(INTERVAL_MATRIX & dst,CONST INTERVAL_MATRIX& src);
VOID Sum(INTERVAL_VECTOR& dst,CONST INTERVAL_MATRIX src);
VOID GetNonHomogeneous(INTERVAL_MATRIX& dst,CONST INTERVAL_MATRIX& src);
VOID GetHomogeneous(INTERVAL_MATRIX& dst,CONST INTERVAL_MATRIX& src);
bool HasDivisionByZero(CONST INTERVAL_MATRIX& src);
VOID GetMatrixOfRowColIdx(INTERVAL_MATRIX& dst,
                        CONST INTERVAL_MATRIX& src, 
                        CONST VECTOR& rows,
                        CONST VECTOR& cols);
VOID GetMatrixOfColIdx(INTERVAL_MATRIX& dst,
                            CONST INTERVAL_MATRIX& src,
                            CONST VECTOR& cols);
VOID GetMatrixOfRowIdx(INTERVAL_MATRIX& dst,
                            CONST INTERVAL_MATRIX& src,
                            CONST VECTOR& rows);

ostream & operator << (ostream &, CONST INTERVAL_MATRIX &);
istream & operator >> (istream &, INTERVAL_MATRIX &);

#endif /* __INTERVAL_MATRIX__ */
