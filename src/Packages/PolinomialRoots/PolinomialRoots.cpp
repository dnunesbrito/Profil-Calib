/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: darlan
 *
 * Created on 24 de Maio de 2016, 12:33
 */

#include <PolinomialRoots/PolinomialRoots.hpp>

INTERVAL_VECTOR Roots(CONST INTERVAL_VECTOR & coeffs){
    INT A = 1,B = 2,C = 3;
    VECTOR ValInf,ValSup;
    ValInf = Inf(coeffs);
    ValSup = Sup(coeffs);
    INTERVAL_VECTOR roots(3),S(8);
    Initialize(roots,Machine::NaN);
    if(ValInf(A) == 0 && ValSup(A) == 0){
        roots(1) = -coeffs(C)/coeffs(B);
        return roots;
    }
    if(ValInf(B) == 0 && ValSup(B) == 0){
        roots(1) = Sqrt(-coeffs(3)/coeffs(1));
        return roots;        
    }
    if(ValInf(C) == 0 && ValSup(C) == 0){
        roots(1) = 0;
        roots(2) = -coeffs(B)/coeffs(A);
        return roots;        
    }
    if(ValInf(A) >= 0 && ValSup(B) <= 0 && ValInf(3) >= 0){
        roots(1) = (-coeffs(2)+Sqrt(Sqr(coeffs(2))-4*coeffs(1)*coeffs(3)))/(2*coeffs(1));
        roots(2) = (2*coeffs(3))/(-coeffs(2)+Sqrt(Sqr(coeffs(2))-4*coeffs(1)*coeffs(3)));
        return roots;
    }
    if(ValInf(A) >= 0 && ValInf(B) >= 0 && ValInf(C) >= 0){
        roots(1) = (-coeffs(2)-Sqrt(Sqr(coeffs(2))-4*coeffs(1)*coeffs(3)))/(2*coeffs(1));
        roots(2) = (2*coeffs(3))/(-coeffs(2)-Sqrt(Sqr(coeffs(2))-4*coeffs(1)*coeffs(3)));
        return roots;
    }
    INT contRoot = 1;
    if(ValInf(A) == 0){
        S(contRoot) = -ValInf(C)/coeffs(B);
        contRoot++;
    }
    if(ValSup(A) == 0){
        S(contRoot) = -ValSup(C)/coeffs(2);
        contRoot++;
    }
    if(ValInf(A) < 0){
        S(contRoot) = SymHull(Machine::PosInfinity);
        contRoot++;
    }else{
        S(contRoot) = (-ValInf(B)-Sqrt(Sqr(ValInf(B))-4*ValInf(A)*ValInf(C)))/(2*ValInf(A));
        contRoot++;
        S(contRoot) = (2*ValInf(C))/(-ValInf(B)-Sqrt(Sqr(ValInf(B))-4*ValInf(A)*ValInf(C)));
        contRoot++;
        S(contRoot) = (-ValSup(B)-Sqrt(Sqr(ValSup(B))-4*ValInf(A)*ValInf(C)))/(2*ValInf(A));
        contRoot++;
        S(contRoot) = (2*ValInf(C))/(-ValInf(B)-Sqrt(Sqr(ValInf(B))-4*ValInf(A)*ValInf(C)));
        contRoot++;
    }
    S(contRoot) = (-ValSup(B)-Sqrt(Sqr(ValSup(B))-4*ValSup(A)*ValSup(C)))/(2*ValSup(A));
    contRoot++;
    S(contRoot) = (2*ValSup(C))/(-ValSup(B)-Sqrt(Sqr(ValSup(B))-4*ValSup(A)*ValSup(C)));
    contRoot++;
    S(contRoot) = (-ValInf(B)-Sqrt(Sqr(ValInf(B))-4*ValSup(A)*ValSup(C)))/(2*ValSup(A));
    contRoot++;
    S(contRoot) = (2*ValSup(C))/(-ValInf(B)-Sqrt(Sqr(ValInf(B))-4*ValSup(A)*ValSup(C)));
    if(contRoot == 5){
        for(int i = 1;i <= contRoot-1;i++){
            int Min = i;
            INTERVAL x;
            for(int j = i+1;j <= contRoot;j++){
                if(S(j).ival.inf <= S(Min).ival.inf){
                    x = S(Min);
                    S(Min) = S(j);
                    S(j) = x;
                }
            }
        }
        roots(1) = INTERVAL(Inf(S(1)),Sup(S(2)));
        roots(2) = INTERVAL(Inf(S(3)),Sup(S(4)));
        roots(3) = INTERVAL(Sup(S(5)),Sup(S(1)));
    }
    if(contRoot == 4){
        roots(1) = INTERVAL(Inf(S(1)),Sup(S(2)));
        roots(2) = INTERVAL(Inf(S(3)),Sup(S(4)));
    }
}