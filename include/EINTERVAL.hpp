/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EINTERVAL.hpp
 * Author: darlan
 *
 * Created on 25 de Setembro de 2016, 08:43
 */

#ifndef EINTERVAL_HPP
#define EINTERVAL_HPP
#include <BIAS/Bias0Ext.hpp>
#include <BIAS/Bias0.h>
#include <BIAS/BiasF.h>
#include <Constants.h>
#include <Configuration.h>
#include <Interval.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <assert.h>

using namespace std;

class EINTERVAL {
public:
    INT nINTERVAL;
    vector<BIASINTERVAL> ival;
    EINTERVAL(){
        nINTERVAL = 0;
    }
    EINTERVAL(const EINTERVAL& orig){
        ival = orig.ival;
        nINTERVAL = orig.nINTERVAL;
    };
    EINTERVAL (INT a)
    {
        ival.resize(a);
        nINTERVAL = a;
    }
    EINTERVAL (REAL a)
    {
        BIASINTERVAL t;
        BiasHullR(&t, & a);
        ival.push_back(t);
        nINTERVAL = 1;
    }
    EINTERVAL (REAL a, REAL b){
        BIASINTERVAL t;
        BiasHullRR(&t, & a, & b);
        ival.push_back(t);
        nINTERVAL = 1;
    }
    EINTERVAL (REAL a, REAL b, INT c){
        BIASINTERVAL t;
        BiasHullRR(&t, & a, & b);
        ival.resize(c);
        ival[0] = t;
        nINTERVAL = c;
    }
    EINTERVAL (REAL a, REAL b, REAL c, REAL d){
        BIASINTERVAL t;
        BiasHullRR(&t, & a, & b);
        ival.push_back(t);
        BiasHullRR(&t, & c, & d);
        ival.push_back(t);
        nINTERVAL = 2;
    }
    virtual ~EINTERVAL();
    EINTERVAL (CONST BIASINTERVAL& IN){
        BIASINTERVAL t;
        BiasHullRR(&t, & IN.inf, & IN.sup);
        ival.push_back(t);
        nINTERVAL = 1;
    }
    EINTERVAL (CONST INTERVAL& IN){
        assert(Machine::PosInfinity != 0);
        ival.push_back(IN.ival);
        nINTERVAL = 1;
    }
    EINTERVAL & operator = (CONST EINTERVAL& x){
        nINTERVAL = x.nINTERVAL;
        ival = x.ival;
    }
    INTERVAL & operator () (INT i) CONST{
        assert(i <= ival.size());
        return (INTERVAL &)ival[i-1];
    }
    EINTERVAL & operator += (REAL x){
        assert(!(*this).empty());
        EINTERVAL t(nINTERVAL);
        BIASINTERVAL pR;
        for(INT i = 1;i <= nINTERVAL;i++)
            EBiasAddIR (Bias(t,i),Bias((*this),i) , & x);
        t.selfintersections();
        *this = t; return *this;
    }
    EINTERVAL & operator -= (REAL x){
        assert(!(*this).empty());
        EINTERVAL t(nINTERVAL);
        for(int i = 1;i <= nINTERVAL;i++)
            EBiasSubIR (Bias(t,i), Bias((*this),i), &x);
        t.selfintersections();
        *this = t; return *this;
    }
    EINTERVAL & operator *= (REAL x){
        assert(!(*this).empty());
        EINTERVAL t(nINTERVAL);
        for(int i = 1;i <= nINTERVAL;i++)
            EBiasMulIR (Bias(t,i), Bias((*this),i), & x);
        t.selfintersections();
        *this = t; return *this;
    }
    EINTERVAL & operator /= (REAL x){
        assert(!(*this).empty());
        EINTERVAL t(nINTERVAL);
        for(int i = 1;i <= nINTERVAL;i++)
            EBiasDivIR (Bias(t,i), Bias((*this),i), & x);
        t.selfintersections();
        *this = t; return *this;
    }
    EINTERVAL & operator += (CONST EINTERVAL & x);
    EINTERVAL & operator -= (CONST EINTERVAL & x);
    EINTERVAL & operator *= (CONST EINTERVAL & x);
    EINTERVAL & operator /= (CONST EINTERVAL & x);
    INT size() CONST {ival.size();}
    bool empty() CONST{ival.empty();}
    REAL inf();
    REAL sup();
    std::vector<REAL> diam();
    REAL maxdiam();
    REAL mindiam();
    INT selfintersections();
    VOID clear(){ival.clear();nINTERVAL=0;}
    REAL maxabs();
    bool hasNaN(){
        for(int i = 0;i < nINTERVAL;i++)
            if(std::isnan(ival[i].sup) || std::isnan(ival[i].inf))
                return true;
        return false;
    }
    INT erase(INT Idx);
    friend BIASINTERVAL * Bias (CONST EINTERVAL &,INT );
    friend EINTERVAL operator + (CONST EINTERVAL &);
    friend EINTERVAL operator - (CONST EINTERVAL &);
    friend EINTERVAL AddReal  (REAL pa, REAL pb);
    friend EINTERVAL operator + (REAL            , CONST EINTERVAL &);
    friend EINTERVAL operator + (CONST EINTERVAL &, REAL            );
    friend EINTERVAL operator + (CONST EINTERVAL &, CONST EINTERVAL &);
    friend EINTERVAL SubReal  (REAL, REAL);
    friend EINTERVAL operator - (REAL            , CONST EINTERVAL &);
    friend EINTERVAL operator - (CONST EINTERVAL &, REAL            );
    friend EINTERVAL operator - (CONST EINTERVAL &, CONST EINTERVAL &);
    friend EINTERVAL MulReal  (REAL, REAL);
    friend EINTERVAL operator * (REAL            , CONST EINTERVAL &);
    friend EINTERVAL operator * (CONST EINTERVAL &, REAL            );
    friend EINTERVAL operator * (CONST EINTERVAL &, CONST EINTERVAL &);
    friend EINTERVAL DivReal  (REAL, REAL);
    friend EINTERVAL operator / (REAL            , CONST EINTERVAL &);
    friend EINTERVAL operator / (CONST EINTERVAL &, REAL            );
    friend EINTERVAL operator / (CONST EINTERVAL &, CONST EINTERVAL &);
    friend EINTERVAL operator ^ (CONST EINTERVAL &, INT );
    friend bool operator <= (CONST EINTERVAL &, CONST EINTERVAL &);
    friend INT EIntervalIntersection(EINTERVAL& tR,CONST EINTERVAL& t1,CONST EINTERVAL& t2);
    friend ostream & operator << (ostream &, CONST EINTERVAL &);
    friend EINTERVAL Hull(CONST EINTERVAL& ,CONST EINTERVAL &);
//    friend istream & operator >> (istream &, EINTERVAL &);
//    friend EINTERVAL Sqr(CONST EINTERVAL& );
//    friend EINTERVAL Sqrt(CONST EINTERVAL& );
//    friend EINTERVAL Abs(CONST EINTERVAL &);
private:

};

inline BIASINTERVAL * Bias (CONST EINTERVAL & x,INT i) {
  return (BIASINTERVAL *) &(x.ival[i-1]); 
}

EINTERVAL operator + (CONST EINTERVAL &);
EINTERVAL operator - (CONST EINTERVAL &);
EINTERVAL AddReal  (REAL, REAL);
EINTERVAL operator + (REAL            , CONST EINTERVAL &);
EINTERVAL operator + (CONST EINTERVAL &, REAL            );
EINTERVAL operator + (CONST EINTERVAL &, CONST EINTERVAL &);
EINTERVAL SubReal  (REAL, REAL);
EINTERVAL operator - (REAL            , CONST EINTERVAL &);
EINTERVAL operator - (CONST EINTERVAL &, REAL            );
EINTERVAL operator - (CONST EINTERVAL &, CONST EINTERVAL &);
EINTERVAL MulReal  (REAL, REAL);
EINTERVAL operator * (REAL            , CONST EINTERVAL &);
EINTERVAL operator * (CONST EINTERVAL &, REAL            );
EINTERVAL operator * (CONST EINTERVAL &, CONST EINTERVAL &);
EINTERVAL DivReal  (REAL, REAL);
EINTERVAL operator / (REAL            , CONST EINTERVAL &);
EINTERVAL operator / (CONST EINTERVAL &, REAL            );
EINTERVAL operator / (CONST EINTERVAL &, CONST EINTERVAL &);
EINTERVAL operator ^ (CONST EINTERVAL &, INT );
/**********************************************************************
*  Result: true if A is contained in B, false otherwise
*/
bool operator <= (CONST EINTERVAL & A, CONST EINTERVAL & B);

INT EIntervalIntersection(EINTERVAL& tR,CONST EINTERVAL& t1,CONST EINTERVAL& t2);
ostream & operator << (ostream &, CONST EINTERVAL &);
//istream & operator >> (istream &, EINTERVAL &);
//
inline EINTERVAL AddReal  (REAL a, REAL b){
  EINTERVAL result(1);
  EBiasAddRR (Bias(result,1), & a, & b);
  return result;    
}

inline EINTERVAL SubReal  (REAL a, REAL b){
  EINTERVAL result(1);
  EBiasSubRR (Bias(result,1), & a, & b);
  return result;        
}

inline EINTERVAL MulReal  (REAL a, REAL b){
  EINTERVAL result(1);
  EBiasMulRR (Bias(result,1), & a, & b);
  return result;        
}

inline EINTERVAL DivReal  (REAL a, REAL b){
  EINTERVAL result(1);
  EBiasDivRR (Bias(result,1), & a, & b);
  return result;        
}
/*Determina o casco convexo de dois EINTERVAL
 faz o casco convexo de todo mundo com todo mundo*/
EINTERVAL Hull(CONST EINTERVAL& ,CONST EINTERVAL &);
//EINTERVAL Abs(CONST EINTERVAL &);
#endif /* EINTERVAL_HPP */

