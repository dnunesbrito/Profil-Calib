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
#ifndef OPTIMIZED
#define OPTIMIZED
#endif

EINTERVAL::~EINTERVAL() {
}

EINTERVAL & EINTERVAL::operator +=(const EINTERVAL& x){ 
    assert(x.nINTERVAL != 0);
    assert(!(*this).empty());
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
#ifdef OPTIMIZED
    REAL pa,pb;
    if(t.size() > 1){
        INT k = 0;
        for(int i = 0;i < A.size();i++){
                pa = A.ival[i].inf;
                pb = a;
                t.ival[k].inf = pa + pb;
                if(isnan(t.ival[k].inf)){
                    t.clear();
                    t = EINTERVAL(1);
                    t.ival[0].inf = BiasNegInf;
                    t.ival[0].sup = BiasPosInf;
                    t.nINTERVAL++;
                    return t;
                }

                pa = A.ival[i].sup;
                pb = a;
                t.ival[k].sup = pa + pb;
                if(isnan(t.ival[k].sup)){
                    t.clear();
                    t = EINTERVAL(1);
                    t.ival[0].inf = BiasNegInf;
                    t.ival[0].sup = BiasPosInf;
                    t.nINTERVAL++;
                    return t;
                }
                k++;
        }
        BIASINTERVAL pR;
        std::vector<BIASINTERVAL>::iterator it = t.ival.begin();
        for(;it != t.ival.end();it++){
            for(std::vector<BIASINTERVAL>::iterator jt = it+1;jt != t.ival.end();){
                if(BiasIntersection(&pR,&(*it),&(*jt)) == 1){
                    BiasHullII(&pR,&(*it),&(*jt));
                    (*it) = pR;
                    jt = t.ival.erase(jt);
                    t.nINTERVAL--;
                }else{
                    jt++;
                }
            }
        }
    }else{
        pa = A.ival[0].inf;
        pb = a;
        t.ival[0].inf = pa + pb;
        if(isnan(t.ival[0].inf)){
            t.ival[0].inf = BiasNegInf;
            t.ival[0].sup = BiasPosInf;
            return t;
        }

        pa = A.ival[0].sup;
        pb = a;
        t.ival[0].sup = pa + pb;
        if(isnan(t.ival[0].sup)){
            t.ival[0].inf = BiasNegInf;
            t.ival[0].sup = BiasPosInf;
            return t;
        }
    }
#else    
    
    for(int i = 1;i <= A.size();i++)
        EBiasAddIR (Bias(t,i),Bias(A,i) , & a);
    t.selfintersections();
#endif
    return t;   
}
EINTERVAL Mais (REAL           a , CONST EINTERVAL &A){
    assert(!A.empty());
    EINTERVAL t(A.size());
    REAL pa,pb;
    if(t.size() > 1){
        INT k = 0;
        for(int i = 0;i < A.size();i++){
                pa = A.ival[i].inf;
                pb = a;
                t.ival[k].inf = pa + pb;
                if(isnan(t.ival[k].inf)){
                    t.clear();
                    t = EINTERVAL(1);
                    t.ival[0].inf = BiasNegInf;
                    t.ival[0].sup = BiasPosInf;
                    t.nINTERVAL++;
                    return t;
                }

                pa = A.ival[i].sup;
                pb = a;
                t.ival[k].sup = pa + pb;
                if(isnan(t.ival[k].sup)){
                    t.clear();
                    t = EINTERVAL(1);
                    t.ival[0].inf = BiasNegInf;
                    t.ival[0].sup = BiasPosInf;
                    t.nINTERVAL++;
                    return t;
                }
                k++;
        }
        BIASINTERVAL pR;
        std::vector<BIASINTERVAL>::iterator it = t.ival.begin();
        for(;it != t.ival.end();it++){
            for(std::vector<BIASINTERVAL>::iterator jt = it+1;jt != t.ival.end();){
                if(BiasIntersection(&pR,&(*it),&(*jt)) == 1){
                    BiasHullII(&pR,&(*it),&(*jt));
                    (*it) = pR;
                    jt = t.ival.erase(jt);
                    t.nINTERVAL--;
                }else{
                    jt++;
                }
            }
        }
    }else{
        pa = A.ival[0].inf;
        pb = a;
        t.ival[0].inf = pa + pb;
        if(isnan(t.ival[0].inf)){
            t.ival[0].inf = BiasNegInf;
            t.ival[0].sup = BiasPosInf;
            return t;
        }

        pa = A.ival[0].sup;
        pb = a;
        t.ival[0].sup = pa + pb;
        if(isnan(t.ival[0].sup)){
            t.ival[0].inf = BiasNegInf;
            t.ival[0].sup = BiasPosInf;
            return t;
        }
    }
    return t;
}

EINTERVAL operator + (CONST EINTERVAL &A, REAL           a ){
    return a+A;
}
EINTERVAL operator + (CONST EINTERVAL &A, CONST EINTERVAL &B){
    assert(!A.empty());
    assert(!B.empty());
    EINTERVAL t(A.size()*B.size());
#ifdef OPTIMIZED
    REAL pa,pb;
    if(t.size() > 1){
        INT k = 0;
        for(int i = 0;i < A.size();i++){
            for(int j = 0;j < B.size();j++){
                pa = A.ival[i].inf;
                pb = B.ival[j].inf;
                t.ival[k].inf = pa + pb;
                if(isnan(t.ival[k].inf)){
                    t.clear();
                    t = EINTERVAL(1);
                    t.ival[0].inf = BiasNegInf;
                    t.ival[0].sup = BiasPosInf;
                    return t;
                }
                pa = A.ival[i].sup;
                pb = B.ival[j].sup;
                t.ival[k].sup = pa + pb;
                if(isnan(t.ival[k].sup)){
                    t.clear();
                    t = EINTERVAL(1);
                    t.ival[0].inf = BiasNegInf;
                    t.ival[0].sup = BiasPosInf;
                    return t;
                }
                k++;
            }
        }
        BIASINTERVAL pR;
        std::vector<BIASINTERVAL>::iterator it = t.ival.begin();
        for(;it != t.ival.end();it++){
            for(std::vector<BIASINTERVAL>::iterator jt = it+1;jt != t.ival.end();){
                if(BiasIntersection(&pR,&(*it),&(*jt)) == 1){
                    BiasHullII(&pR,&(*it),&(*jt));
                    (*it) = pR;
                    jt = t.ival.erase(jt);
                    t.nINTERVAL--;
                }else{
                    jt++;
                }
            }
        }
    }else{
        pa = A.ival[0].inf;
        pb = B.ival[0].inf;
        t.ival[0].inf = pa + pb;
        if(isnan(t.ival[0].inf)){
            t.ival[0].inf = BiasNegInf;
            t.ival[0].sup = BiasPosInf;
            return t;
        }

        pa = A.ival[0].sup;
        pb = B.ival[0].sup;
        t.ival[0].sup = pa + pb;
        if(isnan(t.ival[0].sup)){
            t.ival[0].inf = BiasNegInf;
            t.ival[0].sup = BiasPosInf;
            return t;
        }
    }
#else
    INT k = 1;
    for(int i = 1;i <= A.size();i++){
        for(int j = 1;j <= B.size();j++){
            EBiasAddII (Bias(t,k), Bias(A,i), Bias(B,j));
            k++;
        }
    }
    t.selfintersections();
#endif
    return t;    
}
EINTERVAL Mais (CONST EINTERVAL & A, CONST EINTERVAL & B){
    assert(!A.empty());
    assert(!B.empty());
    EINTERVAL t(A.size()*B.size());
    REAL pa,pb;
    if(t.size() > 1){
        INT k = 0;
        for(int i = 0;i < A.size();i++){
            for(int j = 0;j < B.size();j++){
                pa = A.ival[i].inf;
                pb = B.ival[j].inf;
                t.ival[k].inf = pa + pb;
                if(isnan(t.ival[k].inf)){
                    t.clear();
                    t = EINTERVAL(1);
                    t.ival[0].inf = BiasNegInf;
                    t.ival[0].sup = BiasPosInf;
                    return t;
                }
                pa = A.ival[i].sup;
                pb = B.ival[j].sup;
                t.ival[k].sup = pa + pb;
                if(isnan(t.ival[k].sup)){
                    t.clear();
                    t = EINTERVAL(1);
                    t.ival[0].inf = BiasNegInf;
                    t.ival[0].sup = BiasPosInf;
                    return t;
                }
                k++;
            }
        }
        BIASINTERVAL pR;
        std::vector<BIASINTERVAL>::iterator it = t.ival.begin();
        for(;it != t.ival.end();it++){
            for(std::vector<BIASINTERVAL>::iterator jt = it+1;jt != t.ival.end();){
                if(BiasIntersection(&pR,&(*it),&(*jt)) == 1){
                    BiasHullII(&pR,&(*it),&(*jt));
                    (*it) = pR;
                    jt = t.ival.erase(jt);
                    t.nINTERVAL--;
                }else{
                    jt++;
                }
            }
        }
    }else{
        pa = A.ival[0].inf;
        pb = B.ival[0].inf;
        t.ival[0].inf = pa + pb;
        if(isnan(t.ival[0].inf)){
            t.ival[0].inf = BiasNegInf;
            t.ival[0].sup = BiasPosInf;
            return t;
        }

        pa = A.ival[0].sup;
        pb = B.ival[0].sup;
        t.ival[0].sup = pa + pb;
        if(isnan(t.ival[0].sup)){
            t.ival[0].inf = BiasNegInf;
            t.ival[0].sup = BiasPosInf;
            return t;
        }
    }
    return t;
}

EINTERVAL operator - (REAL          a  , CONST EINTERVAL &A){
    assert(!A.empty());
    EINTERVAL t(A.size());
#ifdef OPTIMIZED
    REAL pa,pb;
    if(t.size() > 1){
        INT k = 0;
        for(int i = 0;i < A.size();i++){
            pa = -A.ival[i].inf;
            pb = a;
            t.ival[k].inf = pa + pb;
            if(isnan(t.ival[k].inf)){
                    t.clear();
                    t = EINTERVAL(1);
                    t.ival[0].inf = BiasNegInf;
                    t.ival[0].sup = BiasPosInf;
                    return t;
            }
            pa = -A.ival[i].sup;
            pb = a;
            t.ival[0].sup = pa + pb;
            if(isnan(t.ival[k].sup)){
                    t.clear();
                    t = EINTERVAL(1);
                    t.ival[0].inf = BiasNegInf;
                    t.ival[0].sup = BiasPosInf;
                    return t;
            }
            k++;
        }
        BIASINTERVAL pR;
        std::vector<BIASINTERVAL>::iterator it = t.ival.begin();
        for(;it != t.ival.end();it++){
            for(std::vector<BIASINTERVAL>::iterator jt = it+1;jt != t.ival.end();){
                if(BiasIntersection(&pR,&(*it),&(*jt)) == 1){
                    BiasHullII(&pR,&(*it),&(*jt));
                    (*it) = pR;
                    jt = t.ival.erase(jt);
                    t.nINTERVAL--;
                }else{
                    jt++;
                }
            }
        }
    }else{
        pa = -A.ival[0].inf;
        pb = a;
        t.ival[0].inf = pa + pb;
        if(isnan(t.ival[0].inf)){
            t.ival[0].inf = BiasNegInf;
            t.ival[0].sup = BiasPosInf;
            return t;
        }
        pa = -A.ival[0].sup;
        pb = a;
        t.ival[0].sup = pa + pb;
        if(isnan(t.ival[0].sup)){
            t.ival[0].inf = BiasNegInf;
            t.ival[0].sup = BiasPosInf;
            return t;
        }
    }
#else
    for(int i = 1;i <= A.size();i++)
        EBiasSubRI (Bias(t,i), &a,Bias(A,i));
#endif
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
#ifdef OPTIMIZED
    REAL pa,pb;
    if(t.size() > 1){
        INT k = 0;
        for(int i = 0;i < A.size();i++){
            for(int j = 0;j < B.size();j++){
                pa = A.ival[i].inf;
                pb = -B.ival[j].sup;
                t.ival[k].inf = pa + pb;
                if(isnan(t.ival[k].inf)){
                    t.clear();
                    t = EINTERVAL(1);
                    t.ival[0].inf = BiasNegInf;
                    t.ival[0].sup = BiasPosInf;
                    return t;
                }
                pa = A.ival[i].sup;
                pb = -B.ival[j].inf;
                t.ival[k].sup = pa + pb;
                if(isnan(t.ival[k].sup)){
                    t.clear();
                    t = EINTERVAL(1);
                    t.ival[0].inf = BiasNegInf;
                    t.ival[0].sup = BiasPosInf;
                    return t;
                }
                k++;
            }
        }
        BIASINTERVAL pR;
        std::vector<BIASINTERVAL>::iterator it = t.ival.begin();
        for(;it != t.ival.end();it++){
            for(std::vector<BIASINTERVAL>::iterator jt = it+1;jt != t.ival.end();){
                if(BiasIntersection(&pR,&(*it),&(*jt)) == 1){
                    BiasHullII(&pR,&(*it),&(*jt));
                    (*it) = pR;
                    jt = t.ival.erase(jt);
                    t.nINTERVAL--;
                }else{
                    jt++;
                }
            }
        }
    }else{
        pa = A.ival[0].inf;
        pb = -B.ival[0].sup;
        t.ival[0].inf = pa + pb;
        if(isnan(t.ival[0].inf)){
            t.ival[0].inf = BiasNegInf;
            t.ival[0].sup = BiasPosInf;
            return t;
        }
        pa = A.ival[0].sup;
        pb = -B.ival[0].inf;
        t.ival[0].sup = pa + pb;
        if(isnan(t.ival[0].sup)){
            t.ival[0].inf = BiasNegInf;
            t.ival[0].sup = BiasPosInf;
            return t;
        }
    }
#else
    INT k = 1;
    for(int i = 1;i <= A.size();i++){
        for(int j = 1;j <= B.size();j++){
            EBiasSubII (Bias(t,k), Bias(A,i), Bias(B,j));
            k++;
        }
    }
    t.selfintersections();
#endif
    return t;    
}
EINTERVAL Menos (CONST EINTERVAL & A, CONST EINTERVAL & B){
    EINTERVAL t(A.size()*B.size());
    REAL pa,pb;
    if(t.size() > 1){
        INT k = 0;
        for(int i = 0;i < A.size();i++){
            for(int j = 0;j < B.size();j++){
                pa = A.ival[i].inf;
                pb = -B.ival[j].sup;
                t.ival[k].inf = pa + pb;
                if(isnan(t.ival[k].inf)){
                    t.clear();
                    t = EINTERVAL(1);
                    t.ival[0].inf = BiasNegInf;
                    t.ival[0].sup = BiasPosInf;
                    return t;
                }
                pa = A.ival[i].sup;
                pb = -B.ival[j].inf;
                t.ival[k].sup = pa + pb;
                if(isnan(t.ival[k].sup)){
                    t.clear();
                    t = EINTERVAL(1);
                    t.ival[0].inf = BiasNegInf;
                    t.ival[0].sup = BiasPosInf;
                    return t;
                }
                k++;
            }
        }
        BIASINTERVAL pR;
        std::vector<BIASINTERVAL>::iterator it = t.ival.begin();
        for(;it != t.ival.end();it++){
            for(std::vector<BIASINTERVAL>::iterator jt = it+1;jt != t.ival.end();){
                if(BiasIntersection(&pR,&(*it),&(*jt)) == 1){
                    BiasHullII(&pR,&(*it),&(*jt));
                    (*it) = pR;
                    jt = t.ival.erase(jt);
                    t.nINTERVAL--;
                }else{
                    jt++;
                }
            }
        }
    }else{
        pa = A.ival[0].inf;
        pb = -B.ival[0].sup;
        t.ival[0].inf = pa + pb;
        if(isnan(t.ival[0].inf)){
            t.ival[0].inf = BiasNegInf;
            t.ival[0].sup = BiasPosInf;
            return t;
        }
        pa = A.ival[0].sup;
        pb = -B.ival[0].inf;
        t.ival[0].sup = pa + pb;
        if(isnan(t.ival[0].sup)){
            t.ival[0].inf = BiasNegInf;
            t.ival[0].sup = BiasPosInf;
            return t;
        }
    }
    return t;
}
EINTERVAL Menos (CONST REAL & a, CONST EINTERVAL & A){
    EINTERVAL t(A.size());
    REAL pa,pb;
    if(t.size() > 1){
        INT k = 0;
        for(int i = 0;i < A.size();i++){
            pa = -A.ival[i].inf;
            pb = a;
            t.ival[k].inf = pa + pb;
            if(isnan(t.ival[k].inf)){
                    t.clear();
                    t = EINTERVAL(1);
                    t.ival[0].inf = BiasNegInf;
                    t.ival[0].sup = BiasPosInf;
                    return t;
            }
            pa = -A.ival[i].sup;
            pb = a;
            t.ival[0].sup = pa + pb;
            if(isnan(t.ival[k].sup)){
                    t.clear();
                    t = EINTERVAL(1);
                    t.ival[0].inf = BiasNegInf;
                    t.ival[0].sup = BiasPosInf;
                    return t;
            }
            k++;
        }
        BIASINTERVAL pR;
        std::vector<BIASINTERVAL>::iterator it = t.ival.begin();
        for(;it != t.ival.end();it++){
            for(std::vector<BIASINTERVAL>::iterator jt = it+1;jt != t.ival.end();){
                if(BiasIntersection(&pR,&(*it),&(*jt)) == 1){
                    BiasHullII(&pR,&(*it),&(*jt));
                    (*it) = pR;
                    jt = t.ival.erase(jt);
                    t.nINTERVAL--;
                }else{
                    jt++;
                }
            }
        }
    }else{
        pa = -A.ival[0].inf;
        pb = a;
        t.ival[0].inf = pa + pb;
        if(isnan(t.ival[0].inf)){
            t.ival[0].inf = BiasNegInf;
            t.ival[0].sup = BiasPosInf;
            return t;
        }
        pa = -A.ival[0].sup;
        pb = a;
        t.ival[0].sup = pa + pb;
        if(isnan(t.ival[0].sup)){
            t.ival[0].inf = BiasNegInf;
            t.ival[0].sup = BiasPosInf;
            return t;
        }
    }
    return t;
}

VOID EBiasMulRRl (BIASINTERVAL * const pR,
		CONST REAL &pa, CONST REAL &pb)
  /**********************************************************************
  *  R = a * b
  */
{
    REAL test = pa * pb;
    if(isnan(test) || isinf(test)){
        if(pa == BiasNegInf){
            if(pb == BiasNegInf){
                pR->inf = BiasPosInf;
                pR->sup = BiasPosInf;
            }else if(pb == BiasPosInf){
                pR->inf = BiasNegInf;
                pR->sup = BiasNegInf;
            }else if(pb == 0){
                pR->inf = BiasPosInf;
                pR->sup = BiasNegInf;
            }else if(pb > 0){
                pR->inf = BiasNegInf;
                pR->sup = BiasNegInf;
            }else if(pb > 0){
                pR->inf = BiasPosInf;
                pR->sup = BiasPosInf;
            }
            return;
        }else if(pa == BiasPosInf){
            if(pb == BiasNegInf){
                pR->inf = BiasPosInf;
                pR->sup = BiasPosInf;
            }else if(pb == BiasPosInf){
                pR->inf = BiasNegInf;
                pR->sup = BiasPosInf;
            }else if(pb == 0){
                pR->inf = BiasNegInf;
                pR->sup = BiasPosInf;
            }else if(pb > 0){
                pR->inf = BiasPosInf;
                pR->sup = BiasPosInf;
            }else if(pb > 0){
                pR->inf = BiasNegInf;
                pR->sup = BiasNegInf;
            }
            return;
        }else if(pa == 0 && (pb == BiasPosInf || pb == BiasNegInf)){
            pR->inf = BiasNegInf;
            pR->sup = BiasPosInf;
        }
    }else{
        pR->inf = pa * pb;
        pR->sup = pa * pb;
    }

} /* BiasMulRR */

EINTERVAL operator * (REAL          a  , CONST EINTERVAL &A){
    assert(!A.empty());
#ifdef OPTIMIZED
    EINTERVAL t;
    for(int i = 0;i < A.size();i++){
        BIASINTERVAL mul1,mul2,pR,pB;
        pB = A.ival[i];
        if (Sign (a) == 0) {                                /* a >= 0 */
            EBiasMulRRl(&mul1,a,pB.inf);
            EBiasMulRRl(&mul2,a,pB.sup);
            BiasHullII(&pR,&mul1,&mul2);
        }
        else {                                                /* a < 0  */
            EBiasMulRRl(&mul1,a,pB.sup);
            EBiasMulRRl(&mul2,a,pB.inf);
            BiasHullII(&pR,&mul1,&mul2);
        }
        t.ival.push_back(pR);
        t.nINTERVAL++;
    }
    t.selfintersections();
    return t;
#else
    assert(!A.empty());
    EINTERVAL t(A.size());
    for(int i = 1;i <= A.size();i++)
        EBiasMulIR (Bias(t,i), Bias(A,i), & a);
    t.selfintersections();
    return t;
#endif
}
EINTERVAL operator * (CONST EINTERVAL &A, REAL          a  ){
    return a*A;
}
EINTERVAL operator * (CONST EINTERVAL &A, CONST EINTERVAL &B){
    assert(!A.empty());
    assert(!B.empty());
    EINTERVAL t(A.size()*B.size());
    INT k = 0;
#ifdef OPTIMIZED
    BIASINTERVAL pA,pB,pR;
    if(t.size() > 1){
        for(int i = 0;i < A.size();i++){
            for(int j = 0;j < B.size();j++){
                pA = A.ival[i];
                pB = B.ival[j];
                if(pA.inf == BiasNegInf){
                    if(pB.inf == 0 || pB.sup == 0){
                       t.ival[k].inf = BiasNegInf;
                       t.ival[k].sup = BiasPosInf;
                       continue;
                    }else if(Sign(pB.inf) == 0){ /*B >= 0*/
                        t.ival[k].inf = BiasNegInf;
                        if(pA.sup == BiasPosInf){
                            t.ival[k].sup = BiasPosInf;
                            continue;
                        }else if (Sign(pA.sup) == 0){ /*A.sup >= 0*/
                            t.ival[k].sup = pA.sup * pB.sup;
                            continue;
                        }else{ /*A.sup < 0 e não é infinito*/
                            t.ival[k].sup = pA.sup * pB.inf;
                        }
                    }else if(Sign(pB.sup)){ /*B < 0*/
                        t.ival[k].sup = BiasPosInf;
                        if(pA.sup == BiasPosInf){ 
                            t.ival[k].inf = BiasNegInf;
                            continue;
                        }else if(Sign(pA.sup) == 0){
                            t.ival[k].inf = pA.sup * pB.inf;
                            continue;
                        }else{
                            t.ival[k].inf = pA.sup * pB.sup;
                            continue;
                        }
                    }else{
                        t.ival[k].inf = BiasNegInf;
                        t.ival[k].sup = BiasPosInf;
                        continue;
                    }
                    if(pA.sup == BiasPosInf){
                        t.ival[k].inf = BiasNegInf;
                        t.ival[k].sup = BiasPosInf;
                        continue;
                    }
                }
                if(pA.sup == BiasPosInf){
                    if(pB.inf == 0 || pB.sup == 0){
                       t.ival[k].inf = BiasNegInf;
                       t.ival[k].sup = BiasPosInf;
                       continue;
                    }else if(Sign(pB.inf) == 0){ /*B >= 0*/
                        t.ival[k].sup = BiasPosInf;
                        if(Sign(pA.inf) == 0){ /*A.inf >= 0*/
                            t.ival[k].inf = pA.inf * pB.inf;
                            continue;
                        }else{
                            t.ival[k].inf = pA.inf * pB.sup;
                            continue;
                        }
                    }else if(Sign(pB.sup)){ /*B < 0*/
                        t.ival[k].inf = BiasNegInf;
                        if(Sign(pA.inf) == 0){ /*A.inf >= 0*/
                            t.ival[k].sup = pA.inf * pB.sup;
                            continue;
                        }else{
                            t.ival[k].sup = pA.inf * pB.inf;
                            continue;
                        }
                    }else{
                        t.ival[k].inf = BiasNegInf;
                        t.ival[k].sup = BiasPosInf;
                        continue;            
                    }
                }





                if(pB.inf == BiasNegInf){
                    if(pA.inf == 0 || pA.sup == 0){
                       t.ival[k].inf = BiasNegInf;
                       t.ival[k].sup = BiasPosInf;
                       continue;
                    }else if(Sign(pA.inf) == 0){ /*B >= 0*/
                        t.ival[k].inf = BiasNegInf;
                        if(pB.sup == BiasPosInf){
                            t.ival[k].sup = BiasPosInf;
                            continue;
                        }else if (Sign(pB.sup) == 0){ /*A.sup >= 0*/
                            t.ival[k].sup = pB.sup * pA.sup;
                            continue;
                        }else{ /*A.sup < 0 e não é infinito*/
                            t.ival[k].sup = pB.sup * pA.inf;
                        }
                    }else if(Sign(pA.sup)){ /*B < 0*/
                        t.ival[k].sup = BiasPosInf;
                        if(pB.sup == BiasPosInf){ 
                            t.ival[k].inf = BiasNegInf;
                            continue;
                        }else if(Sign(pB.sup) == 0){
                            t.ival[k].inf = pB.sup * pA.inf;
                            continue;
                        }else{
                            t.ival[k].inf = pB.sup * pA.sup;
                            continue;
                        }
                    }else{
                        t.ival[k].inf = BiasNegInf;
                        t.ival[k].sup = BiasPosInf;
                        continue;
                    }
                    if(pA.sup == BiasPosInf){
                        t.ival[k].inf = BiasNegInf;
                        t.ival[k].sup = BiasPosInf;
                        continue;
                    }
                }
                if(pB.sup == BiasPosInf){
                    if(pA.inf == 0 || pA.sup == 0){
                       t.ival[k].inf = BiasNegInf;
                       t.ival[k].sup = BiasPosInf;
                       continue;
                    }else if(Sign(pA.inf) == 0){ /*B >= 0*/
                        t.ival[k].sup = BiasPosInf;
                        if(Sign(pB.inf) == 0){ /*A.inf >= 0*/
                            t.ival[k].inf = pB.inf * pA.inf;
                            continue;
                        }else{
                            t.ival[k].inf = pB.inf * pA.sup;
                            continue;
                        }
                    }else if(Sign(pA.sup)){ /*B < 0*/
                        t.ival[k].inf = BiasNegInf;
                        if(Sign(pB.inf) == 0){ /*A.inf >= 0*/
                            t.ival[k].sup = pB.inf * pA.sup;
                            continue;
                        }else{
                            t.ival[k].sup = pB.inf * pA.inf;
                            continue;
                        }
                    }else{
                        t.ival[k].inf = BiasNegInf;
                        t.ival[k].sup = BiasPosInf;
                        continue;            
                    }
                }



                if (Sign (pA.inf) == 0) {                            /* A >= 0 */
                    if (Sign (pB.inf) == 0) {                          /* B >= 0 */
                        t.ival[k].inf = pA.inf * pB.inf;
                        t.ival[k].sup = pA.sup * pB.sup;
                    }
                    else if (Sign (pB.sup)) {                          /* B <= 0 */
                        t.ival[k].inf = pA.sup * pB.inf;
                        t.ival[k].sup = pA.inf * pB.sup;
                    }
                    else {                                              /* 0 in B */
                        t.ival[k].inf = pA.sup * pB.inf;
                        t.ival[k].sup = pA.sup * pB.sup;
                    }
                }
                else if (Sign (pA.sup)) {                            /* A <= 0 */
                    if (Sign (pB.inf) == 0) {                          /* B >= 0 */
                        t.ival[k].inf = pA.inf * pB.sup;
                        t.ival[k].sup = pA.sup * pB.inf;
                    }
                    else if (Sign (pB.sup)) {                          /* B <= 0 */
                        t.ival[k].inf = pA.sup * pB.sup;
                        t.ival[k].sup = pA.inf * pB.inf;
                    }
                    else {                                              /* 0 in B */
                        t.ival[k].inf = pA.inf * pB.sup;
                        t.ival[k].sup = pA.inf * pB.inf;
                    }
                }
                else {                                                /* 0 in A */
                    if (Sign (pB.inf) == 0) {                          /* B >= 0 */
                        t.ival[k].inf = pA.inf * pB.sup;
                        t.ival[k].sup = pA.sup * pB.sup;
                    }
                    else if (Sign (pB.sup)) {                          /* B <= 0 */
                        t.ival[k].inf = pA.sup * pB.inf;
                        t.ival[k].sup = pA.inf * pB.inf;
                    }
                    else {                                              /* 0 in B */
                        REAL r1 = pA.inf * pB.sup;
                        REAL r2 = pA.sup * pB.inf;

                        t.ival[k].inf = r1 < r2 ? r1 : r2;

                        r1 = pA.inf * pB.inf;
                        r2 = pA.sup * pB.sup;

                        t.ival[k].sup = r1 > r2 ? r1 : r2;
                    }
                }
                k++;
            }
        }
        t.selfintersections();
    }else{
        pA = A.ival[0];
        pB = B.ival[0];
        REAL test = pA.inf*pA.sup*pB.inf*pB.sup;
        if(isnan(test) || isinf(test)){
            if(pA.inf == BiasNegInf){
                if(pB.inf == 0 || pB.sup == 0){
                   t.ival[0].inf = BiasNegInf;
                   t.ival[0].sup = BiasPosInf;
                   return t;
                }else if(Sign(pB.inf) == 0){ //B >= 0
                    t.ival[0].inf = BiasNegInf;
                    if(pA.sup == BiasPosInf){
                        t.ival[0].sup = BiasPosInf;
                        return t;
                    }else if (Sign(pA.sup) == 0){ //A.sup >= 0
                        t.ival[0].sup = pA.sup * pB.sup;
                        return t;
                    }else{ //A.sup < 0 e não é infinito
                        t.ival[0].sup = pA.sup * pB.inf;
                    }
                }else if(Sign(pB.sup)){ //B < 0
                    t.ival[0].sup = BiasPosInf;
                    if(pA.sup == BiasPosInf){ 
                        t.ival[0].inf = BiasNegInf;
                        return t;
                    }else if(Sign(pA.sup) == 0){
                        t.ival[0].inf = pA.sup * pB.inf;
                        return t;
                    }else{
                        t.ival[0].inf = pA.sup * pB.sup;
                        return t;
                    }
                }else{
                    t.ival[0].inf = BiasNegInf;
                    t.ival[0].sup = BiasPosInf;
                    return t;
                }
                if(pA.sup == BiasPosInf){
                    t.ival[0].inf = BiasNegInf;
                    t.ival[0].sup = BiasPosInf;
                    return t;
                }
            }
            if(pA.sup == BiasPosInf){
                if(pB.inf == 0 || pB.sup == 0){
                   t.ival[0].inf = BiasNegInf;
                   t.ival[0].sup = BiasPosInf;
                   return t;
                }else if(Sign(pB.inf) == 0){ //B >= 0
                    t.ival[0].sup = BiasPosInf;
                    if(Sign(pA.inf) == 0){ //A.inf >= 0
                        t.ival[0].inf = pA.inf * pB.inf;
                        return t;
                    }else{
                        t.ival[0].inf = pA.inf * pB.sup;
                        return t;
                    }
                }else if(Sign(pB.sup)){ //B < 0
                    t.ival[0].inf = BiasNegInf;
                    if(Sign(pA.inf) == 0){ //A.inf >= 0
                        t.ival[0].sup = pA.inf * pB.sup;
                        return t;
                    }else{
                        t.ival[k].sup = pA.inf * pB.inf;
                        return t;
                    }
                }else{
                    t.ival[0].inf = BiasNegInf;
                    t.ival[0].sup = BiasPosInf;
                    return t;            
                }
            }





            if(pB.inf == BiasNegInf){
                if(pA.inf == 0 || pA.sup == 0){
                   t.ival[0].inf = BiasNegInf;
                   t.ival[0].sup = BiasPosInf;
                   return t;
                }else if(Sign(pA.inf) == 0){ //B >= 0
                    t.ival[0].inf = BiasNegInf;
                    if(pB.sup == BiasPosInf){
                        t.ival[0].sup = BiasPosInf;
                        return t;
                    }else if (Sign(pB.sup) == 0){ //A.sup >= 0
                        t.ival[0].sup = pB.sup * pA.sup;
                        return t;
                    }else{ //A.sup < 0 e não é infinito
                        t.ival[0].sup = pB.sup * pA.inf;
                    }
                }else if(Sign(pA.sup)){ //B < 0
                    t.ival[0].sup = BiasPosInf;
                    if(pB.sup == BiasPosInf){ 
                        t.ival[0].inf = BiasNegInf;
                        return t;
                    }else if(Sign(pB.sup) == 0){
                        t.ival[0].inf = pB.sup * pA.inf;
                        return t;
                    }else{
                        t.ival[k].inf = pB.sup * pA.sup;
                        return t;
                    }
                }else{
                    t.ival[0].inf = BiasNegInf;
                    t.ival[0].sup = BiasPosInf;
                    return t;
                }
                if(pA.sup == BiasPosInf){
                    t.ival[0].inf = BiasNegInf;
                    t.ival[0].sup = BiasPosInf;
                    return t;
                }
            }
            if(pB.sup == BiasPosInf){
                if(pA.inf == 0 || pA.sup == 0){
                   t.ival[0].inf = BiasNegInf;
                   t.ival[0].sup = BiasPosInf;
                   return t;
                }else if(Sign(pA.inf) == 0){ //B >= 0
                    t.ival[0].sup = BiasPosInf;
                    if(Sign(pB.inf) == 0){ //A.inf >= 0
                        t.ival[0].inf = pB.inf * pA.inf;
                        return t;
                    }else{
                        t.ival[0].inf = pB.inf * pA.sup;
                        return t;
                    }
                }else if(Sign(pA.sup)){ //B < 0
                    t.ival[0].inf = BiasNegInf;
                    if(Sign(pB.inf) == 0){ //A.inf >= 0
                        t.ival[0].sup = pB.inf * pA.sup;
                        return t;
                    }else{
                        t.ival[0].sup = pB.inf * pA.inf;
                        return t;
                    }
                }else{
                    t.ival[0].inf = BiasNegInf;
                    t.ival[0].sup = BiasPosInf;
                    return t;            
                }
            }
        }

        if (Sign (pA.inf) == 0) {                            /* A >= 0 */
            if (Sign (pB.inf) == 0) {                          /* B >= 0 */
                t.ival[0].inf = pA.inf * pB.inf;
                t.ival[0].sup = pA.sup * pB.sup;
            }
            else if (Sign (pB.sup)) {                          /* B <= 0 */
                t.ival[0].inf = pA.sup * pB.inf;
                t.ival[0].sup = pA.inf * pB.sup;
            }
            else {                                              /* 0 in B */
                t.ival[0].inf = pA.sup * pB.inf;
                t.ival[0].sup = pA.sup * pB.sup;
            }
        }
        else if (Sign (pA.sup)) {                            /* A <= 0 */
            if (Sign (pB.inf) == 0) {                          /* B >= 0 */
                t.ival[0].inf = pA.inf * pB.sup;
                t.ival[0].sup = pA.sup * pB.inf;
            }
            else if (Sign (pB.sup)) {                          /* B <= 0 */
                t.ival[0].inf = pA.sup * pB.sup;
                t.ival[0].sup = pA.inf * pB.inf;
            }
            else {                                              /* 0 in B */
                t.ival[0].inf = pA.inf * pB.sup;
                t.ival[0].sup = pA.inf * pB.inf;
            }
        }
        else {                                                /* 0 in A */
            if (Sign (pB.inf) == 0) {                          /* B >= 0 */
                t.ival[0].inf = pA.inf * pB.sup;
                t.ival[0].sup = pA.sup * pB.sup;
            }
            else if (Sign (pB.sup)) {                          /* B <= 0 */
                t.ival[0].inf = pA.sup * pB.inf;
                t.ival[0].sup = pA.inf * pB.inf;
            }
            else {                                              /* 0 in B */
                REAL r1 = pA.inf * pB.sup;
                REAL r2 = pA.sup * pB.inf;

                t.ival[0].inf = r1 < r2 ? r1 : r2;

                r1 = pA.inf * pB.inf;
                r2 = pA.sup * pB.sup;

                t.ival[0].sup = r1 > r2 ? r1 : r2;
            }
        }
      
    }
#else
    k = 1;
    for(int i = 1;i <= A.size();i++){
        for(int j = 1;j <= B.size();j++){    
            EBiasMulII (Bias(t,k), Bias(A,i), Bias(B,j));
            k++;
        }
    }
    t.selfintersections();
#endif
    return t;    
}
EINTERVAL Multiplica(CONST EINTERVAL &A, CONST EINTERVAL &B){
    assert(!A.empty());
    assert(!B.empty());
    EINTERVAL t(A.size()*B.size());
    INT k = 0;

    BIASINTERVAL pA,pB,pR;
    if(t.size() > 1){
        for(int i = 0;i < A.size();i++){
            for(int j = 0;j < B.size();j++){
                pA = A.ival[i];
                pB = B.ival[j];
                if(pA.inf == BiasNegInf){
                    if(pB.inf == 0 || pB.sup == 0){
                       t.ival[k].inf = BiasNegInf;
                       t.ival[k].sup = BiasPosInf;
                       continue;
                    }else if(Sign(pB.inf) == 0){ /*B >= 0*/
                        t.ival[k].inf = BiasNegInf;
                        if(pA.sup == BiasPosInf){
                            t.ival[k].sup = BiasPosInf;
                            continue;
                        }else if (Sign(pA.sup) == 0){ /*A.sup >= 0*/
                            t.ival[k].sup = pA.sup * pB.sup;
                            continue;
                        }else{ /*A.sup < 0 e não é infinito*/
                            t.ival[k].sup = pA.sup * pB.inf;
                        }
                    }else if(Sign(pB.sup)){ /*B < 0*/
                        t.ival[k].sup = BiasPosInf;
                        if(pA.sup == BiasPosInf){ 
                            t.ival[k].inf = BiasNegInf;
                            continue;
                        }else if(Sign(pA.sup) == 0){
                            t.ival[k].inf = pA.sup * pB.inf;
                            continue;
                        }else{
                            t.ival[k].inf = pA.sup * pB.sup;
                            continue;
                        }
                    }else{
                        t.ival[k].inf = BiasNegInf;
                        t.ival[k].sup = BiasPosInf;
                        continue;
                    }
                    if(pA.sup == BiasPosInf){
                        t.ival[k].inf = BiasNegInf;
                        t.ival[k].sup = BiasPosInf;
                        continue;
                    }
                }
                if(pA.sup == BiasPosInf){
                    if(pB.inf == 0 || pB.sup == 0){
                       t.ival[k].inf = BiasNegInf;
                       t.ival[k].sup = BiasPosInf;
                       continue;
                    }else if(Sign(pB.inf) == 0){ /*B >= 0*/
                        t.ival[k].sup = BiasPosInf;
                        if(Sign(pA.inf) == 0){ /*A.inf >= 0*/
                            t.ival[k].inf = pA.inf * pB.inf;
                            continue;
                        }else{
                            t.ival[k].inf = pA.inf * pB.sup;
                            continue;
                        }
                    }else if(Sign(pB.sup)){ /*B < 0*/
                        t.ival[k].inf = BiasNegInf;
                        if(Sign(pA.inf) == 0){ /*A.inf >= 0*/
                            t.ival[k].sup = pA.inf * pB.sup;
                            continue;
                        }else{
                            t.ival[k].sup = pA.inf * pB.inf;
                            continue;
                        }
                    }else{
                        t.ival[k].inf = BiasNegInf;
                        t.ival[k].sup = BiasPosInf;
                        continue;            
                    }
                }





                if(pB.inf == BiasNegInf){
                    if(pA.inf == 0 || pA.sup == 0){
                       t.ival[k].inf = BiasNegInf;
                       t.ival[k].sup = BiasPosInf;
                       continue;
                    }else if(Sign(pA.inf) == 0){ /*B >= 0*/
                        t.ival[k].inf = BiasNegInf;
                        if(pB.sup == BiasPosInf){
                            t.ival[k].sup = BiasPosInf;
                            continue;
                        }else if (Sign(pB.sup) == 0){ /*A.sup >= 0*/
                            t.ival[k].sup = pB.sup * pA.sup;
                            continue;
                        }else{ /*A.sup < 0 e não é infinito*/
                            t.ival[k].sup = pB.sup * pA.inf;
                        }
                    }else if(Sign(pA.sup)){ /*B < 0*/
                        t.ival[k].sup = BiasPosInf;
                        if(pB.sup == BiasPosInf){ 
                            t.ival[k].inf = BiasNegInf;
                            continue;
                        }else if(Sign(pB.sup) == 0){
                            t.ival[k].inf = pB.sup * pA.inf;
                            continue;
                        }else{
                            t.ival[k].inf = pB.sup * pA.sup;
                            continue;
                        }
                    }else{
                        t.ival[k].inf = BiasNegInf;
                        t.ival[k].sup = BiasPosInf;
                        continue;
                    }
                    if(pA.sup == BiasPosInf){
                        t.ival[k].inf = BiasNegInf;
                        t.ival[k].sup = BiasPosInf;
                        continue;
                    }
                }
                if(pB.sup == BiasPosInf){
                    if(pA.inf == 0 || pA.sup == 0){
                       t.ival[k].inf = BiasNegInf;
                       t.ival[k].sup = BiasPosInf;
                       continue;
                    }else if(Sign(pA.inf) == 0){ /*B >= 0*/
                        t.ival[k].sup = BiasPosInf;
                        if(Sign(pB.inf) == 0){ /*A.inf >= 0*/
                            t.ival[k].inf = pB.inf * pA.inf;
                            continue;
                        }else{
                            t.ival[k].inf = pB.inf * pA.sup;
                            continue;
                        }
                    }else if(Sign(pA.sup)){ /*B < 0*/
                        t.ival[k].inf = BiasNegInf;
                        if(Sign(pB.inf) == 0){ /*A.inf >= 0*/
                            t.ival[k].sup = pB.inf * pA.sup;
                            continue;
                        }else{
                            t.ival[k].sup = pB.inf * pA.inf;
                            continue;
                        }
                    }else{
                        t.ival[k].inf = BiasNegInf;
                        t.ival[k].sup = BiasPosInf;
                        continue;            
                    }
                }



                if (Sign (pA.inf) == 0) {                            /* A >= 0 */
                    if (Sign (pB.inf) == 0) {                          /* B >= 0 */
                        t.ival[k].inf = pA.inf * pB.inf;
                        t.ival[k].sup = pA.sup * pB.sup;
                    }
                    else if (Sign (pB.sup)) {                          /* B <= 0 */
                        t.ival[k].inf = pA.sup * pB.inf;
                        t.ival[k].sup = pA.inf * pB.sup;
                    }
                    else {                                              /* 0 in B */
                        t.ival[k].inf = pA.sup * pB.inf;
                        t.ival[k].sup = pA.sup * pB.sup;
                    }
                }
                else if (Sign (pA.sup)) {                            /* A <= 0 */
                    if (Sign (pB.inf) == 0) {                          /* B >= 0 */
                        t.ival[k].inf = pA.inf * pB.sup;
                        t.ival[k].sup = pA.sup * pB.inf;
                    }
                    else if (Sign (pB.sup)) {                          /* B <= 0 */
                        t.ival[k].inf = pA.sup * pB.sup;
                        t.ival[k].sup = pA.inf * pB.inf;
                    }
                    else {                                              /* 0 in B */
                        t.ival[k].inf = pA.inf * pB.sup;
                        t.ival[k].sup = pA.inf * pB.inf;
                    }
                }
                else {                                                /* 0 in A */
                    if (Sign (pB.inf) == 0) {                          /* B >= 0 */
                        t.ival[k].inf = pA.inf * pB.sup;
                        t.ival[k].sup = pA.sup * pB.sup;
                    }
                    else if (Sign (pB.sup)) {                          /* B <= 0 */
                        t.ival[k].inf = pA.sup * pB.inf;
                        t.ival[k].sup = pA.inf * pB.inf;
                    }
                    else {                                              /* 0 in B */
                        REAL r1 = pA.inf * pB.sup;
                        REAL r2 = pA.sup * pB.inf;

                        t.ival[k].inf = r1 < r2 ? r1 : r2;

                        r1 = pA.inf * pB.inf;
                        r2 = pA.sup * pB.sup;

                        t.ival[k].sup = r1 > r2 ? r1 : r2;
                    }
                }
                k++;
            }
        }
        t.selfintersections();
    }else{
        pA = A.ival[0];
        pB = B.ival[0];
        REAL test = pA.inf*pA.sup*pB.inf*pB.sup;
        if(isnan(test) || isinf(test)){
            if(pA.inf == BiasNegInf){
                if(pB.inf == 0 || pB.sup == 0){
                   t.ival[0].inf = BiasNegInf;
                   t.ival[0].sup = BiasPosInf;
                   return t;
                }else if(Sign(pB.inf) == 0){ //B >= 0
                    t.ival[0].inf = BiasNegInf;
                    if(pA.sup == BiasPosInf){
                        t.ival[0].sup = BiasPosInf;
                        return t;
                    }else if (Sign(pA.sup) == 0){ //A.sup >= 0
                        t.ival[0].sup = pA.sup * pB.sup;
                        return t;
                    }else{ //A.sup < 0 e não é infinito
                        t.ival[0].sup = pA.sup * pB.inf;
                    }
                }else if(Sign(pB.sup)){ //B < 0
                    t.ival[0].sup = BiasPosInf;
                    if(pA.sup == BiasPosInf){ 
                        t.ival[0].inf = BiasNegInf;
                        return t;
                    }else if(Sign(pA.sup) == 0){
                        t.ival[0].inf = pA.sup * pB.inf;
                        return t;
                    }else{
                        t.ival[0].inf = pA.sup * pB.sup;
                        return t;
                    }
                }else{
                    t.ival[0].inf = BiasNegInf;
                    t.ival[0].sup = BiasPosInf;
                    return t;
                }
                if(pA.sup == BiasPosInf){
                    t.ival[0].inf = BiasNegInf;
                    t.ival[0].sup = BiasPosInf;
                    return t;
                }
            }
            if(pA.sup == BiasPosInf){
                if(pB.inf == 0 || pB.sup == 0){
                   t.ival[0].inf = BiasNegInf;
                   t.ival[0].sup = BiasPosInf;
                   return t;
                }else if(Sign(pB.inf) == 0){ //B >= 0
                    t.ival[0].sup = BiasPosInf;
                    if(Sign(pA.inf) == 0){ //A.inf >= 0
                        t.ival[0].inf = pA.inf * pB.inf;
                        return t;
                    }else{
                        t.ival[0].inf = pA.inf * pB.sup;
                        return t;
                    }
                }else if(Sign(pB.sup)){ //B < 0
                    t.ival[0].inf = BiasNegInf;
                    if(Sign(pA.inf) == 0){ //A.inf >= 0
                        t.ival[0].sup = pA.inf * pB.sup;
                        return t;
                    }else{
                        t.ival[k].sup = pA.inf * pB.inf;
                        return t;
                    }
                }else{
                    t.ival[0].inf = BiasNegInf;
                    t.ival[0].sup = BiasPosInf;
                    return t;            
                }
            }





            if(pB.inf == BiasNegInf){
                if(pA.inf == 0 || pA.sup == 0){
                   t.ival[0].inf = BiasNegInf;
                   t.ival[0].sup = BiasPosInf;
                   return t;
                }else if(Sign(pA.inf) == 0){ //B >= 0
                    t.ival[0].inf = BiasNegInf;
                    if(pB.sup == BiasPosInf){
                        t.ival[0].sup = BiasPosInf;
                        return t;
                    }else if (Sign(pB.sup) == 0){ //A.sup >= 0
                        t.ival[0].sup = pB.sup * pA.sup;
                        return t;
                    }else{ //A.sup < 0 e não é infinito
                        t.ival[0].sup = pB.sup * pA.inf;
                    }
                }else if(Sign(pA.sup)){ //B < 0
                    t.ival[0].sup = BiasPosInf;
                    if(pB.sup == BiasPosInf){ 
                        t.ival[0].inf = BiasNegInf;
                        return t;
                    }else if(Sign(pB.sup) == 0){
                        t.ival[0].inf = pB.sup * pA.inf;
                        return t;
                    }else{
                        t.ival[k].inf = pB.sup * pA.sup;
                        return t;
                    }
                }else{
                    t.ival[0].inf = BiasNegInf;
                    t.ival[0].sup = BiasPosInf;
                    return t;
                }
                if(pA.sup == BiasPosInf){
                    t.ival[0].inf = BiasNegInf;
                    t.ival[0].sup = BiasPosInf;
                    return t;
                }
            }
            if(pB.sup == BiasPosInf){
                if(pA.inf == 0 || pA.sup == 0){
                   t.ival[0].inf = BiasNegInf;
                   t.ival[0].sup = BiasPosInf;
                   return t;
                }else if(Sign(pA.inf) == 0){ //B >= 0
                    t.ival[0].sup = BiasPosInf;
                    if(Sign(pB.inf) == 0){ //A.inf >= 0
                        t.ival[0].inf = pB.inf * pA.inf;
                        return t;
                    }else{
                        t.ival[0].inf = pB.inf * pA.sup;
                        return t;
                    }
                }else if(Sign(pA.sup)){ //B < 0
                    t.ival[0].inf = BiasNegInf;
                    if(Sign(pB.inf) == 0){ //A.inf >= 0
                        t.ival[0].sup = pB.inf * pA.sup;
                        return t;
                    }else{
                        t.ival[0].sup = pB.inf * pA.inf;
                        return t;
                    }
                }else{
                    t.ival[0].inf = BiasNegInf;
                    t.ival[0].sup = BiasPosInf;
                    return t;            
                }
            }
        }

        if (Sign (pA.inf) == 0) {                            /* A >= 0 */
            if (Sign (pB.inf) == 0) {                          /* B >= 0 */
                t.ival[0].inf = pA.inf * pB.inf;
                t.ival[0].sup = pA.sup * pB.sup;
            }
            else if (Sign (pB.sup)) {                          /* B <= 0 */
                t.ival[0].inf = pA.sup * pB.inf;
                t.ival[0].sup = pA.inf * pB.sup;
            }
            else {                                              /* 0 in B */
                t.ival[0].inf = pA.sup * pB.inf;
                t.ival[0].sup = pA.sup * pB.sup;
            }
        }
        else if (Sign (pA.sup)) {                            /* A <= 0 */
            if (Sign (pB.inf) == 0) {                          /* B >= 0 */
                t.ival[0].inf = pA.inf * pB.sup;
                t.ival[0].sup = pA.sup * pB.inf;
            }
            else if (Sign (pB.sup)) {                          /* B <= 0 */
                t.ival[0].inf = pA.sup * pB.sup;
                t.ival[0].sup = pA.inf * pB.inf;
            }
            else {                                              /* 0 in B */
                t.ival[0].inf = pA.inf * pB.sup;
                t.ival[0].sup = pA.inf * pB.inf;
            }
        }
        else {                                                /* 0 in A */
            if (Sign (pB.inf) == 0) {                          /* B >= 0 */
                t.ival[0].inf = pA.inf * pB.sup;
                t.ival[0].sup = pA.sup * pB.sup;
            }
            else if (Sign (pB.sup)) {                          /* B <= 0 */
                t.ival[0].inf = pA.sup * pB.inf;
                t.ival[0].sup = pA.inf * pB.inf;
            }
            else {                                              /* 0 in B */
                REAL r1 = pA.inf * pB.sup;
                REAL r2 = pA.sup * pB.inf;

                t.ival[0].inf = r1 < r2 ? r1 : r2;

                r1 = pA.inf * pB.inf;
                r2 = pA.sup * pB.sup;

                t.ival[0].sup = r1 > r2 ? r1 : r2;
            }
        }
      
    }
    return t;
}

EINTERVAL Multiplica(CONST REAL &a, CONST EINTERVAL &A){
    assert(!A.empty());
    EINTERVAL t(A.size());
    for(int i = 0;i < A.size();i++){
        BIASINTERVAL mul1,mul2,pR,pB;
        pB = A.ival[i];
        if (Sign (a) == 0) {                                /* a >= 0 */
            EBiasMulRRl(&mul1,a,pB.inf);
            EBiasMulRRl(&mul2,a,pB.sup);
            BiasHullII(&pR,&mul1,&mul2);
        }
        else {                                                /* a < 0  */
            EBiasMulRRl(&mul1,a,pB.sup);
            EBiasMulRRl(&mul2,a,pB.inf);
            BiasHullII(&pR,&mul1,&mul2);
        }
    }
    t.selfintersections();
    return t;
}

VOID EBiasDivRRl (BIASINTERVAL * const pR,
		const REAL * const pa, const REAL * const pb)
  /**********************************************************************
  *  R = a / b
  */
{
    REAL test = (*pa)/(*pb);
    if(isnan(test)){
        if((*pa) == BiasNegInf){
            if(*pb == BiasNegInf){
                pR->inf = 0;
                pR->sup = BiasPosInf;
            }else if(*pb < 0 && !isinf(*pb)){
                pR->inf = BiasPosInf;
                pR->sup = BiasPosInf;
            }else if(*pb == 0){
                pR->inf = BiasNegInf;
                pR->sup = BiasPosInf;
            }else if(*pb > 0 && !isinf(*pb)){
                pR->inf = BiasNegInf;
                pR->sup = BiasNegInf;
            }else if(*pb == BiasPosInf){
                pR->inf = BiasNegInf;
                pR->sup = 0;
            }
            return;
        }else if((*pa) > 0 && !isinf(*pa)){
            if(*pb == BiasNegInf){
                pR->inf = 0;
                pR->sup = 0;
                return;
            }else if(*pb == 0){
                pR->inf = BiasNegInf;
                pR->sup = BiasPosInf;
                return;
            }else if(*pb == BiasPosInf){
                pR->inf = 0;
                pR->sup = 0;
                return;
            }
        }else if((*pa) == 0){
            if(*pb == 0){
                pR->inf = BiasNegInf;
                pR->sup = BiasPosInf;
                return;
            }
        }
        if((*pa) == BiasPosInf){
            if(*pb == BiasNegInf){
                pR->inf = BiasNegInf;
                pR->sup = 0;
            }else if(*pb < 0 && !isinf(*pb)){
                pR->inf = BiasNegInf;
                pR->sup = BiasNegInf;
            }else if(*pb == 0){
                pR->inf = BiasNegInf;
                pR->sup = BiasPosInf;
            }else if(*pb > 0 && !isinf(*pb)){
                pR->inf = BiasPosInf;
                pR->sup = BiasPosInf;
            }else if(*pb == BiasPosInf){
                pR->inf = 0;
                pR->sup = BiasPosInf;
            }
            return;
        }
    }
    pR->inf = (*pa) / (*pb);
    pR->sup = (*pa) / (*pb);
} /* BiasDivRR */

EINTERVAL operator / (REAL          a  , CONST EINTERVAL &A){
    assert(!A.empty());
    EINTERVAL t;
#ifdef OPTIMIZED
    BIASINTERVAL pR1,pR2,pb;
    for(int i = 0;i < A.size();i++){
        pb = A.ival[i];
        BIASINTERVAL div1,div2;
        if(pb.inf == 0){
            if(a > 0){
                EBiasDivRRl(&div1,&a,&pb.sup);
                pR1.inf = BiasNegInf;
                pR1.sup = BiasNegInf;
                t.ival.push_back(pR1);
                t.nINTERVAL++;
                pR2.inf = div1.inf;
                pR2.sup = BiasPosInf;
                t.ival.push_back(pR2);
                t.nINTERVAL++;
                return t;
            }else if(a < 0){
                EBiasDivRRl(&div1,&a,&pb.sup);
                pR1.inf = BiasNegInf;
                pR1.sup = div1.inf;
                t.ival.push_back(pR1);
                t.nINTERVAL++;
                pR2.inf = BiasPosInf;
                pR2.sup = BiasPosInf;
                t.ival.push_back(pR2);
                t.nINTERVAL++;
                return t;
            }
        }else if(pb.sup == 0){
            if(a > 0){
                EBiasDivRRl(&div1,&a,&pb.inf);
                pR1.inf = div1.sup;
                pR1.sup = BiasNegInf;
                t.ival.push_back(pR1);
                t.nINTERVAL++;
                pR2.inf = BiasPosInf;
                pR2.sup = BiasPosInf;
                t.ival.push_back(pR2);
                t.nINTERVAL++;
                return t;
            }else if(a < 0){
                EBiasDivRRl(&div1,&a,&pb.inf);
                pR1.inf = BiasNegInf;
                pR1.sup = BiasNegInf;
                t.ival.push_back(pR1);
                t.nINTERVAL++;
                pR2.inf = div1.inf;
                pR2.sup = BiasPosInf;
                t.ival.push_back(pR2);
                t.nINTERVAL++;
                return t;
            }
        }else if(pb.inf < 0 && pb.sup > 0){
            if(a == BiasNegInf || a == BiasPosInf){
                pR1.inf = BiasNegInf;
                pR1.sup = BiasPosInf;
                t.ival.push_back(pR1);
                t.nINTERVAL++;
                return t;
            }
            if(a > 0){
                EBiasDivRRl(&div1,&a,&pb.inf);
                EBiasDivRRl(&div2,&a,&pb.sup);
                pR1.inf = BiasNegInf;
                pR1.sup = div1.inf;
                t.ival.push_back(pR1);
                t.nINTERVAL++;
                pR2.inf = div2.inf;
                pR2.sup = BiasPosInf;
                t.ival.push_back(pR2);
                t.nINTERVAL++;
                return t;
            }else if(a < 0){
                EBiasDivRRl(&div1,&a,&pb.inf);
                EBiasDivRRl(&div2,&a,&pb.sup);
                pR1.inf = BiasNegInf;
                pR1.sup = div2.inf;
                t.ival.push_back(pR1);
                t.nINTERVAL++;
                pR2.inf = div1.inf;
                pR2.sup = BiasPosInf;
                t.ival.push_back(pR2);
                t.nINTERVAL++;
                return t;
            }
        }
        EBiasDivRRl(&div1,&a,&pb.inf);
        EBiasDivRRl(&div2,&a,&pb.sup);
        BiasHullII(&pR1,&div1,&div2);
        t.ival.push_back(pR1);
        t.nINTERVAL++;
        /*if(!std::isnan(pR2.sup) && !std::isnan(pR2.sup)){
            t.ival.push_back(pR2);
            t.nINTERVAL++;
        }*/
    }
    t.selfintersections();
    return t;
#else
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
#endif
}
EINTERVAL operator / (CONST EINTERVAL & A, REAL          a  ){
    assert(!A.empty());
    EINTERVAL t(A.size());
#ifdef OPTIMIZED
    for(int i = 0;i < A.size();i++){
        BIASINTERVAL div1,div2,pR;
        EBiasDivRRl(&div1,&A.ival[i].inf,&a);
        EBiasDivRRl(&div2,&A.ival[i].sup,&a);
        BiasHullII(&pR,&div1,&div2);
    }
    t.selfintersections();
    return t;
#else
    for(int i = 1;i <= A.size();i++)
        EBiasDivIR (Bias(t,i), Bias(A,i), &a);
    t.selfintersections();
    return t; 
#endif
}
EINTERVAL operator / (CONST EINTERVAL &A, CONST EINTERVAL &B){
    assert(!A.empty());
    assert(!B.empty());
    EINTERVAL t;
#ifdef OPTIMIZED
    BIASINTERVAL div1,div2,pA,pB;
    if(A.size()*B.size() > 1){
        for(int i = 0;i < A.size();i++){
            for(int j = 0;j < B.size();j++){
                pA = A.ival[i];
                pB = B.ival[j];
                BIASINTERVAL divinf1,divinf2,divsup1,divsup2;
                if(pB.inf == 0){
                    if(pA.inf > 0 && !isinf(pA.sup)){
                        EBiasDivRRl(&divinf1,&pA.inf,&pB.sup);
                        div1.inf = BiasNegInf;
                        div1.sup = BiasNegInf;
                        t.ival.push_back(div1);
                        t.nINTERVAL++;
                        div2.inf = divinf1.inf;
                        div2.sup = BiasPosInf;
                        t.ival.push_back(div2);
                        t.nINTERVAL++;
                        return t;
                    }else if(pA.sup < 0 && !isinf(pA.sup)){
                        EBiasDivRRl(&divinf1,&pA.sup,&pB.sup);
                        div1.inf = BiasNegInf;
                        div1.sup = divinf1.inf;
                        t.ival.push_back(div1);
                        t.nINTERVAL++;
                        div2.inf = BiasPosInf;
                        div2.sup = BiasPosInf;
                        t.ival.push_back(div2);
                        t.nINTERVAL++;
                        return t;
                    }
                }else if(pB.sup == 0){
                    if(pA.inf > 0 && !isinf(pA.sup)){
                        EBiasDivRRl(&divinf1,&pA.inf,&pB.inf);
                        div1.inf = divinf1.sup;
                        div1.sup = BiasNegInf;
                        t.ival.push_back(div1);
                        t.nINTERVAL++;
                        div2.inf = BiasPosInf;
                        div2.sup = BiasPosInf;
                        t.ival.push_back(div2);
                        t.nINTERVAL++;
                        return t;
                    }else if(pA.sup < 0 && !isinf(pA.sup)){
                        EBiasDivRRl(&divinf1,&pA.sup,&pB.inf);
                        div1.inf = BiasNegInf;
                        div1.sup = BiasNegInf;
                        t.ival.push_back(div1);
                        t.nINTERVAL++;
                        div2.inf = divinf1.inf;
                        div2.sup = BiasPosInf;
                        t.ival.push_back(div2);
                        t.nINTERVAL++;
                        return t;
                    }
                }else if(pB.inf < 0 && pB.sup > 0){
                    if(pA.inf == BiasNegInf || pA.sup == BiasPosInf){
                        div1.inf = BiasNegInf;
                        div1.sup = BiasPosInf;
                        t.ival.push_back(div1);
                        t.nINTERVAL++;
                        return t;
                    }
                    if(pA.inf > 0 && !isinf(pA.inf)){
                        EBiasDivRRl(&divinf1,&pA.inf,&pB.inf);
                        EBiasDivRRl(&divinf2,&pA.inf,&pB.sup);
                        div1.inf = BiasNegInf;
                        div1.sup = divinf1.inf;
                        t.ival.push_back(div1);
                        t.nINTERVAL++;
                        div2.inf = divinf2.inf;
                        div2.sup = BiasPosInf;
                        t.ival.push_back(div2);
                        t.nINTERVAL++;
                        return t;
                    }else if(pA.sup < 0 && !isinf(pA.sup)){
                        EBiasDivRRl(&divinf1,&pA.sup,&pB.inf);
                        EBiasDivRRl(&divinf2,&pA.sup,&pB.sup);
                        div1.inf = BiasNegInf;
                        div1.sup = divinf2.inf;
                        t.ival.push_back(div1);
                        t.nINTERVAL++;
                        div2.inf = divinf1.inf;
                        div2.sup = BiasPosInf;
                        t.ival.push_back(div2);
                        t.nINTERVAL++;
                        return t;
                    }else if(pB.inf < 0 && pB.sup > 0){
                        div1.inf = BiasNegInf;
                        div1.sup = BiasPosInf;
                        t.ival.push_back(div1);
                        t.nINTERVAL++;
                        return t;
                    }
                }
                EBiasDivRRl(&divinf1,&pA.inf,&pB.inf);
                EBiasDivRRl(&divinf2,&pA.inf,&pB.sup);
                EBiasDivRRl(&divsup1,&pA.sup,&pB.inf);
                EBiasDivRRl(&divsup2,&pA.sup,&pB.sup);
                BiasHullII(&div1,&divinf1,&divinf2);
                BiasHullII(&div1,&div1,&divsup1);
                BiasHullII(&div1,&div1,&divsup2);
                t.ival.push_back(div1);
                t.nINTERVAL++;
            }
        }
    }else{
        BIASINTERVAL divinf1,divinf2,divsup1,divsup2;
        pA = A.ival[0];
        pB = B.ival[0];
        if(pB.inf == 0){
            if(pA.inf > 0 && !isinf(pA.sup)){
                EBiasDivRRl(&divinf1,&pA.inf,&pB.sup);
                div1.inf = BiasNegInf;
                div1.sup = BiasNegInf;
                t.ival.push_back(div1);
                t.nINTERVAL++;
                div2.inf = divinf1.inf;
                div2.sup = BiasPosInf;
                t.ival.push_back(div2);
                t.nINTERVAL++;
                return t;
            }else if(pA.sup < 0 && !isinf(pA.sup)){
                EBiasDivRRl(&divinf1,&pA.sup,&pB.sup);
                div1.inf = BiasNegInf;
                div1.sup = divinf1.inf;
                t.ival.push_back(div1);
                t.nINTERVAL++;
                div2.inf = BiasPosInf;
                div2.sup = BiasPosInf;
                t.ival.push_back(div2);
                t.nINTERVAL++;
                return t;
            }
        }else if(pB.sup == 0){
            if(pA.inf > 0 && !isinf(pA.sup)){
                EBiasDivRRl(&divinf1,&pA.inf,&pB.inf);
                div1.inf = divinf1.sup;
                div1.sup = BiasNegInf;
                t.ival.push_back(div1);
                t.nINTERVAL++;
                div2.inf = BiasPosInf;
                div2.sup = BiasPosInf;
                t.ival.push_back(div2);
                t.nINTERVAL++;
                return t;
            }else if(pA.sup < 0 && !isinf(pA.sup)){
                EBiasDivRRl(&divinf1,&pA.sup,&pB.inf);
                div1.inf = BiasNegInf;
                div1.sup = BiasNegInf;
                t.ival.push_back(div1);
                t.nINTERVAL++;
                div2.inf = divinf1.inf;
                div2.sup = BiasPosInf;
                t.ival.push_back(div2);
                t.nINTERVAL++;
                return t;
            }
        }else if(pB.inf < 0 && pB.sup > 0){
            if(pA.inf == BiasNegInf || pA.sup == BiasPosInf){
                div1.inf = BiasNegInf;
                div1.sup = BiasPosInf;
                t.ival.push_back(div1);
                t.nINTERVAL++;
                return t;
            }
            if(pA.inf > 0 && !isinf(pA.inf)){
                EBiasDivRRl(&divinf1,&pA.inf,&pB.inf);
                EBiasDivRRl(&divinf2,&pA.inf,&pB.sup);
                div1.inf = BiasNegInf;
                div1.sup = divinf1.inf;
                t.ival.push_back(div1);
                t.nINTERVAL++;
                div2.inf = divinf2.inf;
                div2.sup = BiasPosInf;
                t.ival.push_back(div2);
                t.nINTERVAL++;
                return t;
            }else if(pA.sup < 0 && !isinf(pA.sup)){
                EBiasDivRRl(&divinf1,&pA.sup,&pB.inf);
                EBiasDivRRl(&divinf2,&pA.sup,&pB.sup);
                div1.inf = BiasNegInf;
                div1.sup = divinf2.inf;
                t.ival.push_back(div1);
                t.nINTERVAL++;
                div2.inf = divinf1.inf;
                div2.sup = BiasPosInf;
                t.ival.push_back(div2);
                t.nINTERVAL++;
                return t;
            }else if(pB.inf < 0 && pB.sup > 0){
                div1.inf = BiasNegInf;
                div1.sup = BiasPosInf;
                t.ival.push_back(div1);
                t.nINTERVAL++;
                return t;
            }
        }
        EBiasDivRRl(&divinf1,&pA.inf,&pB.inf);
        EBiasDivRRl(&divinf2,&pA.inf,&pB.sup);
        EBiasDivRRl(&divsup1,&pA.sup,&pB.inf);
        EBiasDivRRl(&divsup2,&pA.sup,&pB.sup);
        BiasHullII(&div1,&divinf1,&divinf2);
        BiasHullII(&div1,&div1,&divsup1);
        BiasHullII(&div1,&div1,&divsup2);
        t.ival.push_back(div1);
        t.nINTERVAL++;
    }
    return t;    
#else
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
#endif    
}

EINTERVAL Divisao(CONST EINTERVAL &A, CONST EINTERVAL &B){
    assert(!A.empty());
    assert(!B.empty());
    EINTERVAL t;
    BIASINTERVAL div1,div2,pA,pB;
    if(A.size()*B.size() > 1){
        for(int i = 0;i < A.size();i++){
            for(int j = 0;j < B.size();j++){
                pA = A.ival[i];
                pB = B.ival[j];
                BIASINTERVAL divinf1,divinf2,divsup1,divsup2;
                if(pB.inf == 0){
                    if(pA.inf > 0 && !isinf(pA.sup)){
                        EBiasDivRRl(&divinf1,&pA.inf,&pB.sup);
                        div1.inf = BiasNegInf;
                        div1.sup = BiasNegInf;
                        t.ival.push_back(div1);
                        t.nINTERVAL++;
                        div2.inf = divinf1.inf;
                        div2.sup = BiasPosInf;
                        t.ival.push_back(div2);
                        t.nINTERVAL++;
                        return t;
                    }else if(pA.sup < 0 && !isinf(pA.sup)){
                        EBiasDivRRl(&divinf1,&pA.sup,&pB.sup);
                        div1.inf = BiasNegInf;
                        div1.sup = divinf1.inf;
                        t.ival.push_back(div1);
                        t.nINTERVAL++;
                        div2.inf = BiasPosInf;
                        div2.sup = BiasPosInf;
                        t.ival.push_back(div2);
                        t.nINTERVAL++;
                        return t;
                    }
                }else if(pB.sup == 0){
                    if(pA.inf > 0 && !isinf(pA.sup)){
                        EBiasDivRRl(&divinf1,&pA.inf,&pB.inf);
                        div1.inf = divinf1.sup;
                        div1.sup = BiasNegInf;
                        t.ival.push_back(div1);
                        t.nINTERVAL++;
                        div2.inf = BiasPosInf;
                        div2.sup = BiasPosInf;
                        t.ival.push_back(div2);
                        t.nINTERVAL++;
                        return t;
                    }else if(pA.sup < 0 && !isinf(pA.sup)){
                        EBiasDivRRl(&divinf1,&pA.sup,&pB.inf);
                        div1.inf = BiasNegInf;
                        div1.sup = BiasNegInf;
                        t.ival.push_back(div1);
                        t.nINTERVAL++;
                        div2.inf = divinf1.inf;
                        div2.sup = BiasPosInf;
                        t.ival.push_back(div2);
                        t.nINTERVAL++;
                        return t;
                    }
                }else if(pB.inf < 0 && pB.sup > 0){
                    if(pA.inf == BiasNegInf || pA.sup == BiasPosInf){
                        div1.inf = BiasNegInf;
                        div1.sup = BiasPosInf;
                        t.ival.push_back(div1);
                        t.nINTERVAL++;
                        return t;
                    }
                    if(pA.inf > 0 && !isinf(pA.inf)){
                        EBiasDivRRl(&divinf1,&pA.inf,&pB.inf);
                        EBiasDivRRl(&divinf2,&pA.inf,&pB.sup);
                        div1.inf = BiasNegInf;
                        div1.sup = divinf1.inf;
                        t.ival.push_back(div1);
                        t.nINTERVAL++;
                        div2.inf = divinf2.inf;
                        div2.sup = BiasPosInf;
                        t.ival.push_back(div2);
                        t.nINTERVAL++;
                        return t;
                    }else if(pA.sup < 0 && !isinf(pA.sup)){
                        EBiasDivRRl(&divinf1,&pA.sup,&pB.inf);
                        EBiasDivRRl(&divinf2,&pA.sup,&pB.sup);
                        div1.inf = BiasNegInf;
                        div1.sup = divinf2.inf;
                        t.ival.push_back(div1);
                        t.nINTERVAL++;
                        div2.inf = divinf1.inf;
                        div2.sup = BiasPosInf;
                        t.ival.push_back(div2);
                        t.nINTERVAL++;
                        return t;
                    }else if(pB.inf < 0 && pB.sup > 0){
                        div1.inf = BiasNegInf;
                        div1.sup = BiasPosInf;
                        t.ival.push_back(div1);
                        t.nINTERVAL++;
                        return t;
                    }
                }
                EBiasDivRRl(&divinf1,&pA.inf,&pB.inf);
                EBiasDivRRl(&divinf2,&pA.inf,&pB.sup);
                EBiasDivRRl(&divsup1,&pA.sup,&pB.inf);
                EBiasDivRRl(&divsup2,&pA.sup,&pB.sup);
                BiasHullII(&div1,&divinf1,&divinf2);
                BiasHullII(&div1,&div1,&divsup1);
                BiasHullII(&div1,&div1,&divsup2);
                t.ival.push_back(div1);
                t.nINTERVAL++;
            }
        }
    }else{
        BIASINTERVAL divinf1,divinf2,divsup1,divsup2;
        pA = A.ival[0];
        pB = B.ival[0];
        if(pB.inf == 0){
            if(pA.inf > 0 && !isinf(pA.sup)){
                EBiasDivRRl(&divinf1,&pA.inf,&pB.sup);
                div1.inf = BiasNegInf;
                div1.sup = BiasNegInf;
                t.ival.push_back(div1);
                t.nINTERVAL++;
                div2.inf = divinf1.inf;
                div2.sup = BiasPosInf;
                t.ival.push_back(div2);
                t.nINTERVAL++;
                return t;
            }else if(pA.sup < 0 && !isinf(pA.sup)){
                EBiasDivRRl(&divinf1,&pA.sup,&pB.sup);
                div1.inf = BiasNegInf;
                div1.sup = divinf1.inf;
                t.ival.push_back(div1);
                t.nINTERVAL++;
                div2.inf = BiasPosInf;
                div2.sup = BiasPosInf;
                t.ival.push_back(div2);
                t.nINTERVAL++;
                return t;
            }
        }else if(pB.sup == 0){
            if(pA.inf > 0 && !isinf(pA.sup)){
                EBiasDivRRl(&divinf1,&pA.inf,&pB.inf);
                div1.inf = divinf1.sup;
                div1.sup = BiasNegInf;
                t.ival.push_back(div1);
                t.nINTERVAL++;
                div2.inf = BiasPosInf;
                div2.sup = BiasPosInf;
                t.ival.push_back(div2);
                t.nINTERVAL++;
                return t;
            }else if(pA.sup < 0 && !isinf(pA.sup)){
                EBiasDivRRl(&divinf1,&pA.sup,&pB.inf);
                div1.inf = BiasNegInf;
                div1.sup = BiasNegInf;
                t.ival.push_back(div1);
                t.nINTERVAL++;
                div2.inf = divinf1.inf;
                div2.sup = BiasPosInf;
                t.ival.push_back(div2);
                t.nINTERVAL++;
                return t;
            }
        }else if(pB.inf < 0 && pB.sup > 0){
            if(pA.inf == BiasNegInf || pA.sup == BiasPosInf){
                div1.inf = BiasNegInf;
                div1.sup = BiasPosInf;
                t.ival.push_back(div1);
                t.nINTERVAL++;
                return t;
            }
            if(pA.inf > 0 && !isinf(pA.inf)){
                EBiasDivRRl(&divinf1,&pA.inf,&pB.inf);
                EBiasDivRRl(&divinf2,&pA.inf,&pB.sup);
                div1.inf = BiasNegInf;
                div1.sup = divinf1.inf;
                t.ival.push_back(div1);
                t.nINTERVAL++;
                div2.inf = divinf2.inf;
                div2.sup = BiasPosInf;
                t.ival.push_back(div2);
                t.nINTERVAL++;
                return t;
            }else if(pA.sup < 0 && !isinf(pA.sup)){
                EBiasDivRRl(&divinf1,&pA.sup,&pB.inf);
                EBiasDivRRl(&divinf2,&pA.sup,&pB.sup);
                div1.inf = BiasNegInf;
                div1.sup = divinf2.inf;
                t.ival.push_back(div1);
                t.nINTERVAL++;
                div2.inf = divinf1.inf;
                div2.sup = BiasPosInf;
                t.ival.push_back(div2);
                t.nINTERVAL++;
                return t;
            }else if(pB.inf < 0 && pB.sup > 0){
                div1.inf = BiasNegInf;
                div1.sup = BiasPosInf;
                t.ival.push_back(div1);
                t.nINTERVAL++;
                return t;
            }
        }
        EBiasDivRRl(&divinf1,&pA.inf,&pB.inf);
        EBiasDivRRl(&divinf2,&pA.inf,&pB.sup);
        EBiasDivRRl(&divsup1,&pA.sup,&pB.inf);
        EBiasDivRRl(&divsup2,&pA.sup,&pB.sup);
        BiasHullII(&div1,&divinf1,&divinf2);
        BiasHullII(&div1,&div1,&divsup1);
        BiasHullII(&div1,&div1,&divsup2);
        t.ival.push_back(div1);
        t.nINTERVAL++;
    }
    return t;    
}

EINTERVAL Divisao(CONST REAL &a, CONST EINTERVAL &A){
    assert(!A.empty());
    EINTERVAL t;
    BIASINTERVAL pR1,pR2,pb;
    for(int i = 0;i < A.size();i++){
        pb = A.ival[i];
        BIASINTERVAL div1,div2;
        if(pb.inf == 0){
            if(a > 0){
                EBiasDivRRl(&div1,&a,&pb.sup);
                pR1.inf = BiasNegInf;
                pR1.sup = BiasNegInf;
                t.ival.push_back(pR1);
                t.nINTERVAL++;
                pR2.inf = div1.inf;
                pR2.sup = BiasPosInf;
                t.ival.push_back(pR2);
                t.nINTERVAL++;
                return t;
            }else if(a < 0){
                EBiasDivRRl(&div1,&a,&pb.sup);
                pR1.inf = BiasNegInf;
                pR1.sup = div1.inf;
                t.ival.push_back(pR1);
                t.nINTERVAL++;
                pR2.inf = BiasPosInf;
                pR2.sup = BiasPosInf;
                t.ival.push_back(pR2);
                t.nINTERVAL++;
                return t;
            }
        }else if(pb.sup == 0){
            if(a > 0){
                EBiasDivRRl(&div1,&a,&pb.inf);
                pR1.inf = div1.sup;
                pR1.sup = BiasNegInf;
                t.ival.push_back(pR1);
                t.nINTERVAL++;
                pR2.inf = BiasPosInf;
                pR2.sup = BiasPosInf;
                t.ival.push_back(pR2);
                t.nINTERVAL++;
                return t;
            }else if(a < 0){
                EBiasDivRRl(&div1,&a,&pb.inf);
                pR1.inf = BiasNegInf;
                pR1.sup = BiasNegInf;
                t.ival.push_back(pR1);
                t.nINTERVAL++;
                pR2.inf = div1.inf;
                pR2.sup = BiasPosInf;
                t.ival.push_back(pR2);
                t.nINTERVAL++;
                return t;
            }
        }else if(pb.inf < 0 && pb.sup > 0){
            if(a == BiasNegInf || a == BiasPosInf){
                pR1.inf = BiasNegInf;
                pR1.sup = BiasPosInf;
                t.ival.push_back(pR1);
                t.nINTERVAL++;
                return t;
            }
            if(a > 0){
                EBiasDivRRl(&div1,&a,&pb.inf);
                EBiasDivRRl(&div2,&a,&pb.sup);
                pR1.inf = BiasNegInf;
                pR1.sup = div1.inf;
                t.ival.push_back(pR1);
                t.nINTERVAL++;
                pR2.inf = div2.inf;
                pR2.sup = BiasPosInf;
                t.ival.push_back(pR2);
                t.nINTERVAL++;
                return t;
            }else if(a < 0){
                EBiasDivRRl(&div1,&a,&pb.inf);
                EBiasDivRRl(&div2,&a,&pb.sup);
                pR1.inf = BiasNegInf;
                pR1.sup = div2.inf;
                t.ival.push_back(pR1);
                t.nINTERVAL++;
                pR2.inf = div1.inf;
                pR2.sup = BiasPosInf;
                t.ival.push_back(pR2);
                t.nINTERVAL++;
                return t;
            }
        }
        EBiasDivRRl(&div1,&a,&pb.inf);
        EBiasDivRRl(&div2,&a,&pb.sup);
        BiasHullII(&pR1,&div1,&div2);
        t.ival.push_back(pR1);
        t.nINTERVAL++;
        /*if(!std::isnan(pR2.sup) && !std::isnan(pR2.sup)){
            t.ival.push_back(pR2);
            t.nINTERVAL++;
        }*/
    }
    t.selfintersections();
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