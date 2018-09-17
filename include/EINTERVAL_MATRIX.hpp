/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EINTERVAL_MATRIX.hpp
 * Author: darlan
 *
 * Created on 27 de Setembro de 2016, 09:53
 */

#ifndef EINTERVAL_MATRIX_HPP
#define EINTERVAL_MATRIX_HPP

#include "EINTERVAL.hpp"
#include "EINTERVALVECTOR.hpp"
#include <Vector.h>
#include <IntervalVector.h>

using namespace std;
class EINTERVAL_MATRIX {
public:
    vector<EINTERVAL_VECTOR> theElements;
    INT nRows;
    INT nCols;
    EINTERVAL_MATRIX();
    EINTERVAL_MATRIX(const EINTERVAL_MATRIX& orig);
    EINTERVAL_MATRIX(CONST INTERVAL_MATRIX& src);
    EINTERVAL_MATRIX(INT nrows,INT ncols){
        theElements.resize(ncols);
        for(int i = 0;i < ncols;i++){
            theElements[i].theElements.resize(nrows);
            theElements[i].nElements = nrows;
        }
        nRows = nrows;
        nCols = ncols;
    }
    EINTERVAL & operator () (INT i,INT j) CONST
    { assert(i<=nRows && j<=nCols); return (EINTERVAL& )theElements[j-1].theElements[i-1]; }
    EINTERVAL_VECTOR & operator () (INT i) CONST
    { assert(i<=nRows); return (EINTERVAL_VECTOR& )theElements[i]; }
    EINTERVAL_MATRIX (INT nrows,INT ncols,std::initializer_list<EINTERVAL> IN);
    virtual ~EINTERVAL_MATRIX();
    EINTERVAL_MATRIX & operator = (CONST EINTERVAL_MATRIX & A);
    EINTERVAL_MATRIX & operator += (CONST EINTERVAL_MATRIX & A);
    EINTERVAL_MATRIX & operator -= (CONST EINTERVAL_MATRIX & A);
    EINTERVAL_MATRIX operator *= (CONST EINTERVAL_VECTOR & A);
    EINTERVAL_MATRIX operator *= (CONST REAL & a);
    EINTERVAL_MATRIX operator *= (CONST EINTERVAL_MATRIX & A);
    EINTERVAL_VECTOR row(INT rowIdx) const;
    VOID reset();
    VOID clear(){theElements.clear();nRows = 0;nCols = 0;}
    INT rows( ) const {return nRows;}
    VOID setrow(INT i,CONST EINTERVAL_VECTOR&);
    VOID setcol(INT i,CONST EINTERVAL_VECTOR&);
    INT cols( ) const {return nCols;}
    
    EINTERVAL_VECTOR col(INT j);
    EINTERVAL_VECTOR torowvector();
    friend ostream & operator << (ostream & os,CONST  EINTERVAL_MATRIX & A);
    friend EINTERVAL_MATRIX operator + (CONST EINTERVAL_MATRIX &);
    friend EINTERVAL_MATRIX operator - (CONST EINTERVAL_MATRIX &);
    friend EINTERVAL_MATRIX operator + (CONST EINTERVAL_MATRIX &,CONST  EINTERVAL_MATRIX &);
    friend EINTERVAL_MATRIX operator - (CONST EINTERVAL_MATRIX &,CONST  EINTERVAL_MATRIX &);
    friend EINTERVAL_MATRIX operator * (REAL                   ,CONST  EINTERVAL_MATRIX &);
    friend EINTERVAL_MATRIX operator * (CONST EINTERVAL &       ,CONST  EINTERVAL_MATRIX &);
    friend EINTERVAL_MATRIX operator / (CONST EINTERVAL_MATRIX &, REAL                   );
    friend EINTERVAL_MATRIX operator / (CONST EINTERVAL_MATRIX &, CONST EINTERVAL &       );
    friend EINTERVAL_MATRIX operator * (CONST EINTERVAL_VECTOR &,CONST  EINTERVAL_MATRIX & );
    friend EINTERVAL_MATRIX operator * (CONST EINTERVAL_MATRIX &,CONST VECTOR & );
    friend EINTERVAL_VECTOR operator * (CONST EINTERVAL_MATRIX & ,CONST EINTERVAL_VECTOR &);
    friend EINTERVAL_MATRIX operator * (CONST EINTERVAL_MATRIX &,CONST  EINTERVAL_MATRIX &);
    friend EINTERVAL_VECTOR operator * (CONST INTERVAL_MATRIX &         ,CONST  EINTERVAL_VECTOR &);
    friend EINTERVAL_MATRIX Hull(CONST EINTERVAL_MATRIX& , CONST EINTERVAL_MATRIX& );
    friend VOID Parse(vector<INTERVAL_MATRIX>& out,CONST EINTERVAL_VECTOR A);
    friend VOID Parse(vector<INTERVAL_MATRIX>& out,CONST EINTERVAL_MATRIX& A);
private:

};

ostream & operator << (ostream & os,CONST  EINTERVAL_MATRIX & A);
EINTERVAL_MATRIX operator + (CONST EINTERVAL_MATRIX &);
EINTERVAL_MATRIX operator - (CONST EINTERVAL_MATRIX &);
EINTERVAL_MATRIX operator + (CONST EINTERVAL_MATRIX &,CONST  EINTERVAL_MATRIX &);
EINTERVAL_MATRIX operator - (CONST EINTERVAL_MATRIX &,CONST  EINTERVAL_MATRIX &);
EINTERVAL_MATRIX operator * (REAL                   , CONST EINTERVAL_MATRIX &);
EINTERVAL_MATRIX operator * (CONST EINTERVAL &       , CONST EINTERVAL_MATRIX &);
EINTERVAL_MATRIX operator / (CONST EINTERVAL_MATRIX &, REAL                   );
EINTERVAL_MATRIX operator / (CONST EINTERVAL_MATRIX &, CONST EINTERVAL &       );
EINTERVAL_MATRIX operator * (CONST EINTERVAL_VECTOR &, CONST EINTERVAL_MATRIX & );
EINTERVAL_VECTOR operator * (CONST EINTERVAL_MATRIX & ,CONST EINTERVAL_VECTOR &);
EINTERVAL_MATRIX operator * (CONST EINTERVAL_MATRIX &,CONST  EINTERVAL_MATRIX &);
EINTERVAL_VECTOR operator * (CONST INTERVAL_MATRIX &         ,CONST  EINTERVAL_VECTOR &);
EINTERVAL_MATRIX Hull(CONST EINTERVAL_MATRIX& , CONST EINTERVAL_MATRIX& );
VOID Parse(vector<INTERVAL_MATRIX>& out,CONST EINTERVAL_VECTOR A);
VOID Parse(vector<INTERVAL_MATRIX>& out,CONST EINTERVAL_MATRIX& A);
#endif /* EINTERVAL_MATRIX_HPP */

