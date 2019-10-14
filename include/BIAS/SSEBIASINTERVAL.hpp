/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SSEBIASINTERVAL.hpp
 * Author: darlan
 *
 * Created on 11 de outubro de 2019, 02:54
 */

#ifndef SSEBIASINTERVAL_HPP
#define SSEBIASINTERVAL_HPP
#include <BIAS/BiasType.h>
#ifdef __SSE2__
  #include <emmintrin.h>
#else
  #warning SSE2 support is not available. Code will not compile
#endif

class SSEBIASINTERVAL {
public:
    SSEBIASINTERVAL(){};
    SSEBIASINTERVAL(double A,double B);
    SSEBIASINTERVAL(const SSEBIASINTERVAL& orig);
    virtual ~SSEBIASINTERVAL();
    double inf(){return Interval.presult[1];}
    double sup(){return Interval.presult[0];}
    friend SSEBIASINTERVAL operator + (const SSEBIASINTERVAL& pA,const SSEBIASINTERVAL& pB);
    SSEBIASINTERVAL & operator = (const SSEBIASINTERVAL& pA){
        Interval.presultSSE = _mm_set_pd(pA.Interval.presult[1],pA.Interval.presult[0]);
    };
    __m128d AddII(double a1,double a2,double b1,double b2){
    __m128d a = _mm_set_pd(1.0,2.0);
    __m128d b = _mm_set_pd(1.0,2.0);
    __m128d presultSSE = _mm_add_pd(a,b);
    return presultSSE;
    };
private:
    union interval{
        double  presult[2];
        __m128d presultSSE;
    }Interval;
};

#endif /* SSEBIASINTERVAL_HPP */

