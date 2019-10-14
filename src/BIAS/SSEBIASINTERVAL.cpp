/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SSEBIASINTERVAL.cpp
 * Author: darlan
 * 
 * Created on 11 de outubro de 2019, 02:54
 */

#include <BIAS/SSEBIASINTERVAL.hpp>/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SSEBIASINTERVAL.cpp
 * Author: darlan
 * 
 * Created on 11 de outubro de 2019, 04:33
 */

#include <BIAS/SSEBIASINTERVAL.hpp>
#include <iostream>

SSEBIASINTERVAL::SSEBIASINTERVAL(double A, double B){
    Interval.presultSSE = _mm_set_pd(A,B);
}

SSEBIASINTERVAL::SSEBIASINTERVAL(const SSEBIASINTERVAL& orig) {
    Interval.presultSSE = _mm_set_pd(orig.Interval.presult[1],orig.Interval.presult[0]);
}

SSEBIASINTERVAL::~SSEBIASINTERVAL() {
}

SSEBIASINTERVAL operator + (const SSEBIASINTERVAL& pA,const SSEBIASINTERVAL& pB){
    SSEBIASINTERVAL t;
    __m128d a = _mm_set_pd(1.0,2.0);
    __m128d b = _mm_set_pd(1.0,2.0);
    __m128d presultSSE = _mm_add_pd(pA.Interval.presultSSE,pB.Interval.presultSSE);
    return t;
}


