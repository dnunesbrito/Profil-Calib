/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EINTERVALVECTOR.cpp
 * Author: darlan
 * 
 * Created on 26 de Setembro de 2016, 19:31
 */

#include "EINTERVALVECTOR.hpp"

EINTERVAL_VECTOR::EINTERVAL_VECTOR() {
    nElements = 0;
}

EINTERVAL_VECTOR::EINTERVAL_VECTOR(const EINTERVAL_VECTOR& orig) {
    nElements = orig.nElements;
    theElements = orig.theElements;
}
EINTERVAL_VECTOR::EINTERVAL_VECTOR(CONST INTERVAL_VECTOR& A) {
    nElements = Dimension(A);
    for(int i = 1;i <= Dimension(A);i++)
        theElements.push_back(A(i));
}
EINTERVAL_VECTOR::EINTERVAL_VECTOR(CONST VECTOR& A) {
    nElements = Dimension(A);
    for(int i = 1;i <= Dimension(A);i++)
        theElements.push_back(A(i));
}

EINTERVAL_VECTOR::EINTERVAL_VECTOR(INT n) {
    nElements = n;
    theElements.resize(n);
}

EINTERVAL_VECTOR::EINTERVAL_VECTOR(INT nEl, std::initializer_list<EINTERVAL> IN){
    assert(nEl == IN.size());
    initializer_list<EINTERVAL>::iterator i=IN.begin();
    for (;i!=IN.end();i++) theElements.push_back(*i);
    nElements = nEl;
}


EINTERVAL_VECTOR::~EINTERVAL_VECTOR() {
    theElements.clear();
}

EINTERVAL_VECTOR & EINTERVAL_VECTOR::operator =(const EINTERVAL_VECTOR& A){
    nElements = A.nElements;
    theElements = A.theElements;
}

EINTERVAL_VECTOR & EINTERVAL_VECTOR::operator +=(const EINTERVAL_VECTOR& A){
    if(nElements != A.nElements)EXIT_FAILURE;
    for(int i = 0;i < theElements.size();i++)
        theElements[i] += A.theElements[i];
}

EINTERVAL_VECTOR & EINTERVAL_VECTOR::operator -=(const EINTERVAL_VECTOR& A){
    if(nElements != A.nElements)EXIT_FAILURE;
    for(int i = 0;i <= theElements.size();i++)
        theElements[i] -= A.theElements[i];
}

EINTERVAL_VECTOR & EINTERVAL_VECTOR::operator *=(const EINTERVAL& A){
    for(int i = 0;i <= theElements.size();i++)
        theElements[i] *= A;
}

EINTERVAL_VECTOR operator + (CONST EINTERVAL_VECTOR &A){
    return A;
}
EINTERVAL_VECTOR operator - (CONST EINTERVAL_VECTOR &A){
    EINTERVAL_VECTOR result(A.nElements);
    for(int i = 1;i <= A.nElements;i++)
        result(i) = -A(i);
    return result;
}
EINTERVAL_VECTOR operator + (CONST VECTOR & A,CONST  EINTERVAL_VECTOR & B){
    EINTERVAL_VECTOR result(Dimension(A));
    assert(Dimension(A) == B.nElements);
    for(int i = 1;i <= Dimension(A);i++)
        result(i) = A(i)+B(i);
    return result;
}
EINTERVAL_VECTOR operator + (CONST EINTERVAL_VECTOR & A,CONST  VECTOR &       B  ){
    return B-A;
}
EINTERVAL_VECTOR operator + (CONST EINTERVAL_VECTOR & A,CONST EINTERVAL_VECTOR &B){
    EINTERVAL_VECTOR result(A.nElements);
    assert(A.nElements == B.nElements);
    for(int i = 1;i <= A.nElements;i++)
        result(i) = A(i)+B(i);
    return result;
}
EINTERVAL_VECTOR operator - (CONST VECTOR &       A  ,CONST  EINTERVAL_VECTOR &B){
    EINTERVAL_VECTOR result(Dimension(A));
    assert(Dimension(A) == B.nElements);
    for(int i = 1;i <= Dimension(A);i++)
        result(i) = A(i)-B(i);
    return result;    
}
EINTERVAL_VECTOR operator - (CONST EINTERVAL_VECTOR & A,CONST  VECTOR &   B){
    EINTERVAL_VECTOR result(A.nElements);
    assert(A.nElements == Dimension(B));
    for(int i = 1;i <= Dimension(B);i++)
        result(i) = A(i)-B(i);
    return result;        
}
EINTERVAL_VECTOR operator - (CONST EINTERVAL_VECTOR & A,CONST EINTERVAL_VECTOR & B){
    EINTERVAL_VECTOR result(A.nElements);
    assert(A.nElements == B.nElements);
    for(int i = 1;i <= A.nElements;i++){
        result(i) = A(i)-B(i);
    }
    return result;
}
EINTERVAL_VECTOR operator * (REAL a,CONST  EINTERVAL_VECTOR &A){
    EINTERVAL_VECTOR result(A.nElements);
    for(int i = 1;i <= A.nElements;i++)
        result(i) = a*A(i);
    return result;
}
EINTERVAL_VECTOR operator * (CONST EINTERVAL_VECTOR & A,REAL  a){
    return a*A;
}
EINTERVAL_VECTOR operator * (CONST EINTERVAL & A,CONST  EINTERVAL_VECTOR & B){
    EINTERVAL_VECTOR result(B.nElements);
    for(int i = 1;i <= B.nElements;i++)
        result(i) = A*B(i);
    return result;    
}
EINTERVAL_VECTOR operator * (CONST  EINTERVAL_VECTOR & B,CONST EINTERVAL & A){;
    return A*B;    
}
EINTERVAL_VECTOR operator / (CONST EINTERVAL_VECTOR & A, REAL a){
    EINTERVAL_VECTOR result(A.nElements);
    for(int i = 1;i <= A.nElements;i++)
        result(i) = A(i)/a;
    return result;    
}
EINTERVAL_VECTOR operator / (CONST VECTOR & A,CONST  EINTERVAL &   B){
    EINTERVAL_VECTOR result(Dimension(A));
    for(int i = 1;i <= Dimension(A);i++)
        result(i) = A(i)/B;
    return result;        
}
EINTERVAL_VECTOR operator / (CONST EINTERVAL_VECTOR & A,CONST  EINTERVAL &  B){
    EINTERVAL_VECTOR result(A.nElements);
    for(int i = 1;i <= A.nElements;i++)
        result(i) = A(i)/B;
    return result;            
}
EINTERVAL operator * (CONST VECTOR &   B,CONST  EINTERVAL_VECTOR & A){
    EINTERVAL result(0,0);
    assert(A.nElements == Dimension(B));
    for(int i = 1;i <= A.nElements;i++)
        result += A(i)*B(i);
    return result;    
}
EINTERVAL operator * (CONST EINTERVAL_VECTOR & A,CONST  VECTOR &  B){
    EINTERVAL result(0,0);
    assert(A.nElements == Dimension(B));
    for(int i = 1;i <= A.nElements;i++)
        result += A(i)*B(i);
    return result;    
}
EINTERVAL operator * (CONST EINTERVAL_VECTOR & A,CONST EINTERVAL_VECTOR & B){
    EINTERVAL result(0,0);
    assert(A.nElements == B.nElements);
    for(int i = 1;i <= A.nElements;i++)
        result += A(i)*B(i);
    return result;        
}
ostream & operator << (ostream & os,CONST  EINTERVAL_VECTOR & A){
    os << "(";
    for(int i = 1;i <= A.nElements;i++){
        os << A(i);
        if(i != A.nElements)os << endl;
    }
    os << ")";
    return os;
}
INTERVAL_VECTOR EINTERVAL_VECTOR::getIV(INT idx) CONST {
    assert(idx > 0 && idx <= nElements);
    INTERVAL_VECTOR out(nElements);
    for(int i = 1;i <= nElements;i++)
        out(i) = theElements[i-1](idx);
    return out;
}
VOID Parse(vector<INTERVAL_VECTOR>& out,CONST EINTERVAL_VECTOR A){
    INTERVAL_VECTOR tmpVector(A.nElements);
    INT combinacoes = 1;
    for(int i = 1;i <= A.nElements;i++){
        combinacoes *= A(i).size();
    }
    out.clear();
    for(int i = 1;i <= combinacoes;i++)out.push_back(tmpVector);
    int contcol = 0;
    for(int i = 1;i <= A.nElements;){
        int muda = 1;
        for(int k = 1;k < i;k++)muda *= A(k).size();
        for(int j = 1;j <= A(i).size();){
            out[contcol](i) = A(i)(j);
            contcol++;
            if(contcol%muda == 0)j++;
        }
        if(contcol >= combinacoes){
            i++;
            contcol = 0;
        }
    }
}
EINTERVAL_VECTOR EINTERVAL_VECTOR::Box(INT iniRow, INT endRow) CONST{
    assert(iniRow >= 1);
    assert(endRow <= nElements);
    EINTERVAL_VECTOR out;
    out.resize(endRow-iniRow+1);
    copy(theElements.begin()+(iniRow-1),theElements.begin()+(endRow),out.theElements.begin());
    return out;    
}
VOID EINTERVAL_VECTOR::resize(INT newsize){
    theElements.resize(newsize);
    nElements = newsize;
}
VOID EINTERVAL_VECTOR::vcat(CONST EINTERVAL_VECTOR& A){
    theElements.resize(theElements.size()+A.rows());
    copy(A.theElements.begin(),A.theElements.end(),theElements.begin()+nElements);
    nElements = theElements.size();
}
EINTERVAL Sqr(CONST EINTERVAL_VECTOR& A){
    EINTERVAL Sum(0,0,1);
    for(int i = 1;i <= A.rows();i++)
//        Sum += Sqr(A(i));
    return Sum;
}
INTERVAL_VECTOR EINTERVAL_VECTOR::norm(const EINTERVAL_VECTOR& A){
    assert(!A.empty());
    vector<INTERVAL_VECTOR> X;
    Parse(X,A);
    vector<INTERVAL> tmpresult;
    for(int i = 0;i < X.size();i++)
        tmpresult.push_back(Norm(X[i]));
    INTERVAL_VECTOR result(tmpresult.size());
    for(int i = 1;i <= tmpresult.size();i++)
        result(i) = tmpresult[i-1];
    return result;
}
INTERVAL_VECTOR EINTERVAL_VECTOR::norm( ){
    vector<INTERVAL_VECTOR> X;
    Parse(X,(*this));
    vector<INTERVAL> tmpresult;
    for(int i = 0;i < X.size();i++)
        tmpresult.push_back(Norm(X[i]));
    INTERVAL_VECTOR result(tmpresult.size());
    for(int i = 1;i <= tmpresult.size();i++)
        result(i) = tmpresult[i-1];
    return result;
}
VOID EINTERVAL_VECTOR::reset( ){
    for(int i = 0;i < nElements;i++)
        theElements[i] = EINTERVAL(0,0);
}
std::vector<std::vector <REAL> >EINTERVAL_VECTOR::diam(){
    std::vector<std::vector <REAL> > out;
    for(int i = 0;i < nElements;i++)
        out.push_back(theElements[i].diam());
    return out;
}
REAL EINTERVAL_VECTOR::maxdiam(){
    REAL MaxDiam = Machine::NegInfinity;
    for(int i = 0;i < nElements;i++){
        std::vector<REAL> vecdiam;
        vecdiam = theElements[i].diam();
        for(std::vector<REAL>::iterator it = vecdiam.begin();
                it != vecdiam.end();it++)
        if((*it) > MaxDiam)
            MaxDiam = (*it);
    }
    return MaxDiam;
}
bool operator <= (CONST EINTERVAL_VECTOR & A, CONST EINTERVAL_VECTOR & B){
    assert(A.rows() == B.rows());
    for(int i = 1;i <= A.rows();i++)
        if(!(A(i) <= B(i)))return false;
    return true;
}
INT EIntervalIntersection(EINTERVAL_VECTOR& tR,CONST EINTERVAL_VECTOR& pA,CONST EINTERVAL_VECTOR& pB){
    if(pA.rows() != pB.rows())return 0;
    EINTERVAL ItR;
    tR.resize(pA.rows());
    for(int i = 1;i <= pA.rows();i++)
        if(EIntervalIntersection(ItR,pA(i),pB(i)) == 1)
            tR(i) = ItR;
        else
            return 0;
    return 1;
}
EINTERVAL_VECTOR Hull(CONST EINTERVAL_VECTOR& A, CONST EINTERVAL_VECTOR & B){
    assert(A.rows() == B.rows());
    EINTERVAL_VECTOR C(A.rows());
    for(int i = 1;i <= A.rows();i++)
        C(i) = Hull(A(i),B(i));
    return C;
}