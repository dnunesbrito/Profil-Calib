/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EINTERVAL.cpp
 * Author: darlan
 * 
 * Created on 25 de Setembro de 2016, 08:43
 */

#include <EINTERVAL.hpp>

EINTERVAL::~EINTERVAL() {
}

EINTERVAL & EINTERVAL::operator +=(const EINTERVAL& x){ 
    assert(x.nINTERVAL != 0);
    assert(!(*this).empty());
    BIASINTERVAL pR;
    EINTERVAL t(nINTERVAL*x.nINTERVAL);
    INT k = 1;
    for(int i = 1;i <= nINTERVAL;i++){
        for(int j = 1;j <= x.nINTERVAL;j++){
            EBiasAddII (Bias(t,k), Bias((*this),i), Bias(x,j));
            k++;
        }
    }
    t.selfintersections();
    *this = t;return *this;
}
EINTERVAL & EINTERVAL::operator -=(const EINTERVAL& x){ 
    assert(x.nINTERVAL != 0);
    assert(!(*this).empty());
    EINTERVAL t(nINTERVAL*x.nINTERVAL);
    INT k = 1;
    for(int i = 1;i <= nINTERVAL;i++){
        for(int j = 1;j <= x.nINTERVAL;j++){
            EBiasSubII (Bias(t,k), Bias((*this),i), Bias(x,j));
        }
    }
    t.selfintersections();
    *this = t;return *this;
}
EINTERVAL & EINTERVAL::operator *=(const EINTERVAL& x){
    assert(x.nINTERVAL != 0);
    assert(!(*this).empty());
    EINTERVAL t(nINTERVAL*x.nINTERVAL);
    INT k = 1;
    for(int i = 1;i <= nINTERVAL;i++){
        for(int j = 1;j <= x.nINTERVAL;j++){
            EBiasMulII (Bias(t,k), Bias((*this),i), Bias(x,j));
        }
    }
    t.selfintersections();
    *this = t;return *this;
}
EINTERVAL & EINTERVAL::operator /=(const EINTERVAL& x){ 
    assert(x.nINTERVAL != 0);
    assert(!(*this).empty());
    EINTERVAL t;
    BIASINTERVAL div1,div2;
    for(int i = 1;i <= nINTERVAL;i++){
        for(int j = 1;j <= x.nINTERVAL;j++){    
            EBiasDivII (&div1, &div2, Bias((*this),i), Bias(x,j));
            t.ival.push_back(div1);
            t.nINTERVAL++;
            if(!std::isnan(div2.inf) && !std::isnan(div2.sup)){
                t.ival.push_back(div2);
                t.nINTERVAL++;
            }
        }
    }
    t.selfintersections();
    *this = t;return *this;
}
INT EINTERVAL::selfintersections(){
    if(nINTERVAL == 1)
        return 1;
    BIASINTERVAL pR;
    std::vector<BIASINTERVAL>::iterator it = ival.begin();
    for(;it != ival.end();it++){
        for(std::vector<BIASINTERVAL>::iterator jt = it+1;jt != ival.end();){
            if(BiasIntersection(&pR,&(*it),&(*jt)) == 1){
                BiasHullII(&pR,&(*it),&(*jt));
                (*it) = pR;
                jt = ival.erase(jt);
                nINTERVAL--;
            }else{
                jt++;
            }
        }
    }
}
INT EIntervalIntersection(EINTERVAL& tR,CONST EINTERVAL& t1,CONST EINTERVAL& t2){
    EINTERVAL tl1,tl2;
    BIASINTERVAL pR;
    INT hasIntersection = 0;
    tl1 = t1;
    tl2 = t2;
    tR.clear();
    tl1.selfintersections();
    tl2.selfintersections();
    for(int i = 1;i <= tl1.size();i++){
        if(EBiasPosInfinity(Bias(tl1,i)) || EBiasNegInfinity(Bias(tl1,i))){
            tl1.ival[i-1].inf = Machine::NegInfinity;
            tl1.ival[i-1].sup = Machine::PosInfinity;
        }
        for(int j = 1;j <= tl2.size();j++){
            if(EBiasPosInfinity(Bias(tl2,j)) || EBiasNegInfinity(Bias(tl2,j))){
                tl2.ival[j-1].inf = Machine::NegInfinity;
                tl2.ival[j-1].sup = Machine::PosInfinity;
            }
            if(BiasIntersection(&pR,Bias(tl1,i),Bias(tl2,j)) == 1){
                tR.ival.push_back(pR);
                tR.nINTERVAL++;
                hasIntersection = 1;
            }
        }
    }
    tR.selfintersections();
    return hasIntersection;
}
ostream & operator << (ostream & os, CONST EINTERVAL & x){
    assert(!x.empty());
    os << "{";
    for(INT i = 1;i <= x.nINTERVAL;i++)
        os  << x(i) ;
    os << "}";
}
//
//istream & operator >> (istream & is, EINTERVAL & x){
//  REAL a, b;
//
//  is >> a;
//  is >> b;
//  BiasHullRR (Bias1(x), & a, & b);
//  return is;
//}
//
EINTERVAL operator + (CONST EINTERVAL &A){
    return A;
}
EINTERVAL operator - (CONST EINTERVAL &A){
    assert(!A.empty());
    EINTERVAL result(A.size());
    for(int i = 1;i <= A.size();i++)
        BiasNeg(Bias(result,i),Bias(A,i));
    return result;
}
EINTERVAL operator + (REAL           a , CONST EINTERVAL &A){
    assert(!A.empty());
    EINTERVAL t(A.size());
    for(int i = 1;i <= A.size();i++)
        EBiasAddIR (Bias(t,i),Bias(A,i) , & a);
    t.selfintersections();
    return t;   
}
EINTERVAL operator + (CONST EINTERVAL &A, REAL           a ){
    return a+A;
}
EINTERVAL operator + (CONST EINTERVAL &A, CONST EINTERVAL &B){
    assert(!A.empty());
    assert(!B.empty());
    EINTERVAL t(A.size()*B.size());
    INT k = 1;
    for(int i = 1;i <= A.size();i++){
        for(int j = 1;j <= B.size();j++){
            EBiasAddII (Bias(t,k), Bias(A,i), Bias(B,j));
            k++;
        }
    }
    t.selfintersections();
    return t;    
}
EINTERVAL operator - (REAL          a  , CONST EINTERVAL &A){
    assert(!A.empty());
    EINTERVAL t(A.size());
    for(int i = 1;i <= A.size();i++)
        EBiasSubRI (Bias(t,i), &a,Bias(A,i));
    return t;
}
EINTERVAL operator - (CONST EINTERVAL &A, REAL          a  ){
    assert(!A.empty());
    EINTERVAL t(A.size());
    for(int i = 1;i <= A.size();i++)
        EBiasSubIR (Bias(t,1),Bias(A,1), &a);
    t.selfintersections();
    return t;    
}
EINTERVAL operator - (CONST EINTERVAL &A, CONST EINTERVAL &B){
    assert(!A.empty());
    assert(!B.empty());
    EINTERVAL t(A.size()*B.size());
    INT k = 1;
    for(int i = 1;i <= A.size();i++){
        for(int j = 1;j <= B.size();j++){
            EBiasSubII (Bias(t,k), Bias(A,i), Bias(B,i));
            k++;
        }
    }
    t.selfintersections();
    return t;    
}
EINTERVAL operator * (REAL          a  , CONST EINTERVAL &A){
    assert(!A.empty());
    EINTERVAL t(A.size());
    for(int i = 1;i <= A.size();i++)
        EBiasMulIR (Bias(t,i), Bias(A,i), & a);
    t.selfintersections();
    return t;
}
EINTERVAL operator * (CONST EINTERVAL &A, REAL          a  ){
    return a*A;
}
EINTERVAL operator * (CONST EINTERVAL &A, CONST EINTERVAL &B){
    assert(!A.empty());
    assert(!B.empty());
    EINTERVAL t(A.size()*B.size());
    INT k = 1;
    for(int i = 1;i <= A.size();i++){
        for(int j = 1;j <= B.size();j++){    
            EBiasMulII (Bias(t,k), Bias(A,i), Bias(B,j));
            k++;
        }
    }
    t.selfintersections();
    return t;    
}
EINTERVAL operator / (REAL          a  , CONST EINTERVAL &A){
    assert(!A.empty());
    EINTERVAL t;
    BIASINTERVAL pR1,pR2;
    for(int i = 1;i <= A.size();i++){
        EBiasDivRI (&pR1,&pR2, &a, Bias(A,i));
        t.ival.push_back(pR1);
        t.nINTERVAL++;
        if(!std::isnan(pR2.sup) && !std::isnan(pR2.sup)){
            t.ival.push_back(pR2);
            t.nINTERVAL++;
        }
    }
    t.selfintersections();
    return t;
}
EINTERVAL operator / (CONST EINTERVAL & A, REAL          a  ){
    assert(!A.empty());
    EINTERVAL t(A.size());
    for(int i = 1;i <= A.size();i++)
        EBiasDivIR (Bias(t,i), Bias(A,i), &a);
    t.selfintersections();
    return t;    
}
EINTERVAL operator / (CONST EINTERVAL &A, CONST EINTERVAL &B){
    assert(!A.empty());
    assert(!B.empty());
    EINTERVAL t;
    BIASINTERVAL div1,div2;
    for(int i = 1;i <= A.size();i++){
        for(int j = 1;j <= B.size();j++){
            EBiasDivII (&div1, &div2, Bias(A,i), Bias(B,j));
            t.ival.push_back(div1);
            t.nINTERVAL++;
            if(!std::isnan(div2.sup) && !std::isnan(div2.sup)){
                t.ival.push_back(div2);
                t.nINTERVAL++;
            }
        }
    }
    return t;
    
}
//EINTERVAL Sqrt(CONST EINTERVAL& A){
//    assert(!A.empty());
//    EINTERVAL Xout;
//    Xout = A;
//    if(Xout.SingleInterval()){
//        BiasSqrt(Bias1(Xout),Bias1(A));
//    }else{
//        BiasSqrt(Bias1(Xout),Bias1(A));
//        BiasSqrt(Bias2(Xout),Bias2(A));
//        Xout.SingleInterval();
//    }
//    return Xout;
//}
//EINTERVAL Sqr(CONST EINTERVAL& A){
//    assert(!A.empty());
//    EINTERVAL Xout;
//    Xout = A;
//    if(Xout.SingleInterval()){
//        BiasSqr(Bias1(Xout),Bias1(A));
//    }else{
//        BiasSqr(Bias1(Xout),Bias1(A));
//        BiasSqr(Bias2(Xout),Bias2(A));
//        Xout.SingleInterval();
//    }
//    return Xout;    
//}
REAL EINTERVAL::sup(){
    assert(nINTERVAL != 0);
    REAL supval = Machine::NegInfinity;
    assert(nINTERVAL != 0);
    for(int i = 0;i < nINTERVAL;i++)
        if(ival[i].sup > supval)
            supval = ival[i].sup;
    return supval;
}
REAL EINTERVAL::inf(){
    assert(nINTERVAL != 0);
    REAL infval = Machine::PosInfinity;
    for(int i = 0;i < nINTERVAL;i++)
        if(ival[i].inf < infval)
            infval = ival[i].inf;
    return infval;
}
std::vector<REAL> EINTERVAL::diam(){
    std::vector<REAL> diamvec(nINTERVAL);
    for(int i = 0;i < nINTERVAL;i++){
        diamvec[i] = BiasDiam(&ival[i]);
    }
    return diamvec;
}
//EINTERVAL Abs(CONST EINTERVAL &A){
//    assert(!A.empty());
//    EINTERVAL tR(0,0,A.nINTERVAL);
//    tR(1) = Abs(A(1));
//    if(A.nINTERVAL == 2)
//        tR(2) = Abs(A(2));
//    return tR;
//}
REAL EINTERVAL::maxabs(){
    assert(nINTERVAL != 0);
    REAL Maxabs = Machine::NegInfinity;
    for(int i = 0;i < nINTERVAL;i++)
        if(BiasAbs(&ival[i]) > Maxabs)
            Maxabs = BiasAbs(&ival[i]);
    return Maxabs;
}
INT EINTERVAL::erase(INT Idx){
    std::vector<BIASINTERVAL>::iterator it = ival.begin();
    it += Idx-1;
    ival.erase(it);
    nINTERVAL--;
}
REAL EINTERVAL::maxdiam(){
    REAL Maxdiam = Machine::NegInfinity;
    for(int i = 0;i < nINTERVAL;i++)
        if(BiasDiam(&ival[i]) > Maxdiam)
            Maxdiam = BiasDiam(&ival[i]);
    return Maxdiam;
}
REAL EINTERVAL::mindiam(){
    REAL Mindiam = Machine::PosInfinity;
    for(int i = 0;i < nINTERVAL;i++)
        if(BiasDiam(&ival[i]) > Mindiam)
            Mindiam = BiasDiam(&ival[i]);
    return Mindiam;
}
bool operator <= (CONST EINTERVAL & A, CONST EINTERVAL &B){
    EINTERVAL Al(A),Bl(B);
    bool isin = false;
    for(int i = 1;i <= A.nINTERVAL;i++){
        if(EBiasPosInfinity(Bias(A,i)) || EBiasNegInfinity(Bias(A,i))){
            BiasHullRR(Bias(Al,i),&BiasNegInf,&BiasPosInf);
        }
        for(int j = 1;j <= B.nINTERVAL;j++){
            if(EBiasPosInfinity(Bias(B,j)) || EBiasNegInfinity(Bias(B,j))){
                BiasHullRR(Bias(Bl,j),&BiasNegInf,&BiasPosInf);
            }
            if(!BiasInI(Bias(Al,i),Bias(Bl,j)))
                isin = false;
            else
                isin = true;
            if(isin)return true;
        }
    }
    return isin;
}
EINTERVAL Hull(CONST EINTERVAL& A,CONST EINTERVAL & B){
    EINTERVAL out(A.size()*B.size());
    int k = 1;
    for(int i = 1;i <= A.size();i++)
        for(int j = 1;j <= B.size();j++,k++)
            BiasHullII(Bias(out,k),Bias(A,i),Bias(B,j));
    return out;
}
EINTERVAL operator ^ (CONST EINTERVAL & A, INT power){
    EINTERVAL r(A.size());    
    switch(power){
        case 1:
            r = A;
            break;
        case 2:
            for(int i = 1;i <= A.size();i++){
              BiasSqr(Bias(r,i), Bias(A,i));
            }
            break;
        default:
            for(int i = 1;i <= A.size();i++){
              BiasPowerN(Bias(r,i), Bias(A,i),power);
            }
    }
    return r;
}