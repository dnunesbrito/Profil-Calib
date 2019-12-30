/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EINTERVAL_MATRIX.cpp
 * Author: darlan
 * 
 * Created on 27 de Setembro de 2016, 09:53
 */

#include "EINTERVAL_MATRIX.hpp"

EINTERVAL_MATRIX::EINTERVAL_MATRIX() {
}

EINTERVAL_MATRIX::EINTERVAL_MATRIX(const EINTERVAL_MATRIX& orig) {
}

EINTERVAL_MATRIX::~EINTERVAL_MATRIX() {
    for(int i = 0;i < theElements.size();i++){
        theElements[i].theElements.clear();
    }
    theElements.clear();
    nRows = 0;
    nCols = 0;
}

EINTERVAL_MATRIX::EINTERVAL_MATRIX(INT nrows,INT ncols, std::initializer_list<EINTERVAL> IN){
    assert((nrows*ncols) == IN.size());
    theElements.resize(ncols);
    INT i = 0;
    INT j = 0;
    for(i = 0;i < ncols;i++){
        theElements[i].theElements.resize(nrows);
        theElements[i].nElements = nrows;
    }
    initializer_list<EINTERVAL>::iterator it=IN.begin();
    i = 0;
    j = 0;
    for (;it!=IN.end();it++){
        theElements[i].theElements[j] = (*it);
        i++;
        if(i == ncols){
            i = 0;
            j++;
        }
    }
    nRows = nrows;
    nCols = ncols;
}
EINTERVAL_MATRIX::EINTERVAL_MATRIX(CONST INTERVAL_MATRIX& src){
    nRows = src.rows();
    nCols = src.cols();
    for(int i = 1;i <= src.cols();i++){
        theElements.push_back(src.col(i));
    }
}
EINTERVAL_MATRIX & EINTERVAL_MATRIX::operator =(const EINTERVAL_MATRIX& A){
    nRows = A.nRows;
    nCols = A.nCols;
    theElements = A.theElements;
}
EINTERVAL_MATRIX & EINTERVAL_MATRIX::operator +=(const EINTERVAL_MATRIX& A){
    if(nRows != A.nRows || nCols != A.nCols)EXIT_FAILURE;
    for(INT i = 0;i < theElements.size();i++){
            theElements[i] += A.theElements[i];
    }
}
EINTERVAL_MATRIX & EINTERVAL_MATRIX::operator -=(const EINTERVAL_MATRIX& A){
    if(nRows != A.nRows || nCols != A.nCols)EXIT_FAILURE;
    for(INT i = 0;i < theElements.size();i++){
            theElements[i] -= A.theElements[i];
    }
}
EINTERVAL_MATRIX EINTERVAL_MATRIX::operator *=(CONST EINTERVAL_VECTOR& A){
    EINTERVAL_MATRIX out(1,A.nElements);
    if(nRows != A.nElements)EXIT_FAILURE;
    for(INT i = 0;i < theElements.size();i++){
            out(1,i) = theElements[i] * A;
    }
    *this = out;
}
EINTERVAL_MATRIX  EINTERVAL_MATRIX::operator *= (CONST REAL & a){
    EINTERVAL_MATRIX out(nRows,nCols);
    for(INT i = 0;i < theElements.size();i++){
            out(i) = a*(*this)(i);
    }
    *this = out;    
}
ostream & operator << (ostream & os,CONST EINTERVAL_MATRIX & A){
    os << "(";
    for(int i = 1;i <= A.nRows;i++){
        for(int j = 1;j <= A.nCols;j++){
            os << A(i,j);
            if(j != A.nCols)
                os << ",";
        }
        if(i != A.nRows)
            os << ";" << endl;
    }
    os << ")";
}
EINTERVAL_MATRIX operator + (CONST EINTERVAL_MATRIX & A){
    return A;
}
EINTERVAL_MATRIX operator - (CONST EINTERVAL_MATRIX & A){
    EINTERVAL_MATRIX out(A.nRows,A.nCols);
    for(INT i = 1;i <= A.nCols;i++)
        out(i) = -A(i);
    return out;
}
EINTERVAL_MATRIX operator + (EINTERVAL_MATRIX & A, EINTERVAL_MATRIX & B){
    EINTERVAL_MATRIX result(A.nRows,A.nCols);
    if(A.nRows != B.nRows || B.nCols != A.nCols)EXIT_FAILURE;
    for(INT i = 0;i < A.theElements.size();i++){
            result(i) = A(i) + B(i);
    }
    return result;
}
EINTERVAL_MATRIX operator - (CONST EINTERVAL_MATRIX & A,CONST  EINTERVAL_MATRIX & B){
    EINTERVAL_MATRIX result(A.nRows,A.nCols);
    if(A.nRows != B.nRows || B.nCols != A.nCols)EXIT_FAILURE;
    for(INT i = 0;i < A.theElements.size();i++){
            result(i) = A(i) - B(i);
    }
    return result;
}
EINTERVAL_MATRIX operator * (REAL  a,CONST  EINTERVAL_MATRIX &A){
    EINTERVAL_MATRIX result(A.nRows,A.nCols);
    for(INT i = 0;i < A.theElements.size();i++){
            result(i) = A(i) * a;
    }
    return result;
}
EINTERVAL_MATRIX operator * (CONST EINTERVAL &  a,CONST  EINTERVAL_MATRIX & A){
    EINTERVAL_MATRIX result(A.nRows,A.nCols);
    for(INT i = 0;i < A.theElements.size();i++){
            result(i) = A(i) * a;
    }
    return result;    
}
EINTERVAL_MATRIX operator / (CONST EINTERVAL_MATRIX & A, REAL  a){
    EINTERVAL_MATRIX result(A.nRows,A.nCols);
    for(INT i = 0;i < A.theElements.size();i++){
            result(i) = A(i) / a;
    }
    return result;    
}
EINTERVAL_MATRIX operator / (CONST EINTERVAL_MATRIX & A, CONST EINTERVAL &  a){
    EINTERVAL_MATRIX result(A.nRows,A.nCols);
    for(INT i = 0;i < A.theElements.size();i++){
            result(i) = A(i) / a;
    }
    return result;    
}
EINTERVAL_MATRIX operator * (CONST EINTERVAL_VECTOR & A,CONST EINTERVAL_MATRIX & B){
    EINTERVAL_MATRIX result(1,A.nElements);
    if(B.nRows != A.nElements)EXIT_FAILURE;
    for(INT i = 0;i < B.theElements.size();i++){
            result(1,i) = B.theElements[i] * A;
    }
    return result;
}
EINTERVAL_VECTOR operator * (CONST EINTERVAL_MATRIX & A,CONST EINTERVAL_VECTOR & B){
    if(A.nCols != B.nElements)EXIT_FAILURE;
    EINTERVAL_VECTOR result(A.nRows);
    result.reset();
    for(int i = 1;i <= A.nRows;i++){
        for(int j = 1;j <= A.nCols;j++){
            result(i) += A(i,j)*B(j);
        }
    }
    return result;
}
EINTERVAL_MATRIX operator * (CONST EINTERVAL_MATRIX & A,CONST EINTERVAL_MATRIX & B){
    if(A.nRows != B.nCols)EXIT_FAILURE;
    EINTERVAL_MATRIX result(A.nRows,B.nCols);
    result.reset();
    for(int i = 1;i <= A.nRows;i++){
        for(int j = 1;j <= B.nCols;j++){
            EINTERVAL sum(0.0);
            for(int k = 1;k <= A.nCols;k++)
                sum += A(i,k)*B(k,j);
            result(i,j) = sum;
        }
    }
    return result;
}
EINTERVAL_VECTOR operator * (CONST INTERVAL_MATRIX & A,CONST EINTERVAL_VECTOR & B){
    assert(A.cols() == B.rows());
    EINTERVAL_VECTOR result(A.rows());
    for(int i = 1;i <= A.rows();i++){
        result(i) = (CONST EINTERVAL_VECTOR)A.row(i)*B;
    }
    return result;    
}

EINTERVAL_MATRIX EINTERVAL_MATRIX::operator *= (CONST EINTERVAL_MATRIX & A){
    assert(nRows == A.nCols);
    EINTERVAL_MATRIX out(nRows,A.nCols);
    out.reset();
    for(int i = 1;i <= nRows;i++){
        for(int j = 1;j <= A.nCols;j++){
            for(int k = 1;k <= A.nRows;k++){
                out(i,j) += (*this)(i,k)*A(k,j);
            }
        }
    }
    cout << out << endl;
    theElements = out.theElements;
    nRows = out.nRows;
    nCols = out.nCols;
    return out;
}
VOID EINTERVAL_MATRIX::reset( ){
    for(int i = 1;i <= nRows;i++)
        for(int j = 1;j <= nCols;j++)
            (*this)(i,j) = EINTERVAL(0,0);
}
EINTERVAL_VECTOR EINTERVAL_MATRIX::row(INT rowIdx) const{
    assert(rowIdx > 0);
    assert(rowIdx <= nRows);
    EINTERVAL_VECTOR result(nRows);
    for(int i = 0;i < nCols;i++){
        result(i+1) = theElements[i].theElements[rowIdx-1];
    }
    return result;
}
VOID Parse(vector<INTERVAL_MATRIX>& out,CONST EINTERVAL_MATRIX& A){
    vector<vector<INTERVAL_VECTOR> > VP;
    for(int i = 1;i <= A.cols();i++){
        std::vector<INTERVAL_VECTOR> IVrows;
        Parse(IVrows,A.row(i));
        VP.push_back(IVrows);
    }
    INTERVAL_MATRIX tmpMatrix(A.nRows,A.nCols);
    INT combinacoes = 1;
    for(int i = 0;i < VP.size();i++){
        combinacoes *= VP[i].size();
    }
    out.clear();
    for(int i = 1;i <= combinacoes;i++)out.push_back(tmpMatrix);
    int contcol = 0;
    for(int i = 1;i <= A.nCols;){
        int muda = 1;
        for(int k = 1;k < i;k++)muda *= VP[k-1].size();
        for(int j = 1;j <= VP[i-1].size();){
            SetCol(out[contcol],i,VP[i-1][j-1]);
            contcol++;
            if(contcol%muda == 0)j++;
        }
        if(contcol >= combinacoes){
            i++;
            contcol = 0;
        }
    }
}
EINTERVAL_VECTOR EINTERVAL_MATRIX::torowvector(){
    EINTERVAL_VECTOR out;
    for(int i = 1;i <= nRows;i++){
        out.vcat((*this).row(i));
    }
}
EINTERVAL_MATRIX Hull(CONST EINTERVAL_MATRIX& A, CONST EINTERVAL_MATRIX& B){
    assert(A.rows() == B.rows() && A.cols() == B.cols());
    EINTERVAL_MATRIX C(A.rows(),A.cols());
    for(int i = 1;i <= A.cols();i++)
        C(i) = Hull(A(i),B(i));
    return C;
}
EINTERVAL_VECTOR EINTERVAL_MATRIX::col(INT j) {
    EINTERVAL_VECTOR out(nRows);
    for(int i = 1;i <= nRows;i++){
        out(i) = (*this)(i,j);
    }
    return out;
}
VOID EINTERVAL_MATRIX::setrow(INT i,CONST EINTERVAL_VECTOR& A){
    for(int j = 1;j <= nRows;j++)
        (*this)(i,j) = A(j);
}
VOID EINTERVAL_MATRIX::setcol(INT i, const EINTERVAL_VECTOR& A){
    theElements[i-1] = A;
}