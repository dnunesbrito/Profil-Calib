/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Teste PROFIL.cpp
 * Author: darlan
 *
 * Created on 11 de dezembro de 2019, 10:34
 */

#include <stdlib.h>
#include <iostream>
#include <time.h>

#include <EINTERVAL.hpp>
/*
 * Simple C++ Test Suite
 */

void test1() {
    EINTERVAL A(1.1,2.2),B(-1.1,2.2),C;
    REAL a = -1.1;
    for(double i = 1;i <= 10000;i++)
        C = A/B;
}
void test3() {
    EINTERVAL A(1.1,2.2),B(-1.1,2.2),C;
    REAL a = -1.1;
    for(double i = 1;i <= 10000;i++)
        C = Divisao(A,B);
}

void test4(){
    REAL Inf,Isup;
    EINTERVAL A,B,C;
    for(int teste = 1;teste <= 4; teste++){
        for(int i = 1; i <= 4;i++){
            switch(i){
                case 1:
                    Inf = 1.0;
                    Isup = 2.0;
                    break;
                case 2:
                    Inf = 0;
                    Isup = 2.0;
                    break;
                case 3:
                    Inf = 0;
                    Isup = INFINITY;
                    break;
                case 4:
                    Inf = INFINITY;
                    Isup = INFINITY;
                    break;                
            }
            for(int j = 1;j <= 3;j++){
                switch(j){
                    case 1:
                        A = EINTERVAL(Inf,Isup);
                        break;
                    case 2:
                        A = EINTERVAL(-Inf,Isup);
                        break;
                    case 3:
                        A = EINTERVAL(-Inf,-Isup);
                        break;
                }
                for(int k = 1;k <= 5;k++){
                    switch(k){
                        case 1:
                            B = EINTERVAL(Inf,Isup);
                            break;
                        case 2:
                            B = EINTERVAL(-Inf,Isup);
                            break;
                        case 3:
                            B = EINTERVAL(-Inf,-Isup);
                            break;
                        case 4:
                            B = EINTERVAL(0,Isup);
                            break;
                        case 5:
                            B = EINTERVAL(-Inf,0);
                    }
                    cout << "A: " << A << endl;
                    cout << "B: " << B << endl;
                    switch(teste){
                        case 1:
                            C = A+B;
                            cout << endl << "C (operador +): " << C << endl;
                            C = Mais(A,B);
                            cout << endl << "C (funcão +): " << C << endl;
                            break;
                        case 2:
                            C = A-B;
                            cout << endl << "C (operador -): " << C << endl;
                            C = Menos(A,B);
                            cout << endl << "C (funcão - ): " << C << endl;
                            break;
                        case 3:
                            C = A*B;
                            cout << endl << "C (operador *): " << C << endl;
                            C = Multiplica(A,B); 
                            cout << endl << "C (funcão *): " << C << endl;
                            break;
                        case 4:
                            C = A/B;
                            cout << endl << "C (operador /): " << C << endl;
                            C = Divisao(A,B);
                            cout << endl << "C (funcão /): " << C << endl;
                            break;
                    }
                }
            }
        }
    }
}


void test5(){
    REAL Inf,Isup;
    for(int teste = 1;teste <= 4; teste++){
        EINTERVAL A,B,C;
        for(int i = 1; i <= 4;i++){
            switch(i){
                case 1:
                    Inf = 1.0;
                    Isup = 2.0;
                    break;
                case 2:
                    Inf = 0;
                    Isup = 2.0;
                    break;
                case 3:
                    Inf = 0;
                    Isup = INFINITY;
                    break;
                case 4:
                    Inf = INFINITY;
                    Isup = INFINITY;
                    break;                
            }
            for(int j = 1;j <= 3;j++){
                switch(j){
                    case 1:
                        A = EINTERVAL(Inf,Isup,Inf+1,Isup+1);
                        break;
                    case 2:
                        A = EINTERVAL(-Inf,Isup,-(Inf+1),(Isup+1));
                        break;
                    case 3:
                        A = EINTERVAL(-Inf,-Isup,(Inf+1),-(Isup+1));
                        break;
                }
                for(int k = 1;k <= 3;k++){
                    switch(k){
                        case 1:
                            B = EINTERVAL(-Inf,Isup,-(Inf+1),(Isup+1));
                            break;
                        case 2:
                            B = EINTERVAL(Inf,Isup,(Inf+1),(Isup+1));
                            break;
                        case 3:
                            B = EINTERVAL(-Inf,-Isup,-(Inf+1),(Isup+1));
                            break;
                    }
                    cout << "A: " << A << endl;
                    cout << "B: " << B << endl;
                    switch(teste){
                        case 1:
                            C = A+B;
                            cout << endl << "C (operador +): " << C << endl;
                            C = Mais(A,B);
                            cout << endl << "C (funcão +): " << C << endl;
                            break;
                        case 2:
                            C = A-B;
                            cout << endl << "C (operador -): " << C << endl;
                            C = Menos(A,B);
                            cout << endl << "C (funcão - ): " << C << endl;
                            break;
                        case 3:
                            C = A*B;
                            cout << endl << "C (operador *): " << C << endl;
                            C = Multiplica(A,B); 
                            cout << endl << "C (funcão *): " << C << endl;
                            break;
                        case 4:
                            C = A/B;
                            cout << endl << "C (operador /): " << C << endl;
                            C = Divisao(A,B);
                            cout << endl << "C (funcão /): " << C << endl;
                            break;
                    }
                }
            }
        }
    }
}

void test6(){
    REAL Inf,Isup;
    EINTERVAL A,C;
    REAL a;
    for(int teste = 1;teste <= 4; teste++){
        for(int i = 1; i <= 4;i++){
            switch(i){
                case 1:
                    Inf = 1.0;
                    Isup = 2.0;
                    break;
                case 2:
                    Inf = 0;
                    Isup = 2.0;
                    break;
                case 3:
                    Inf = 0;
                    Isup = INFINITY;
                    break;
                case 4:
                    Inf = INFINITY;
                    Isup = INFINITY;
                    break;                
            }
            for(int j = 1;j <= 3;j++){
                switch(j){
                    case 1:
                        A = EINTERVAL(Inf,Isup);
                        break;
                    case 2:
                        A = EINTERVAL(-Inf,Isup);
                        break;
                    case 3:
                        A = EINTERVAL(-Inf,-Isup);
                        break;
                }
                for(int k = 1;k <= 2;k++){
                    switch(k){
                        case 1:
                            a = Inf;
                            break;
                        case 2:
                            a = -Inf;
                            break;
                    }
                    cout << "A: " << A << endl;
                    cout << "a: " << a << endl;
                    switch(teste){
                        case 1:
                            C = a+A;
                            cout << endl << "C (operador +): " << C << endl;
                            C = Mais(a,A);
                            cout << endl << "C (funcão +): " << C << endl;
                            break;
                        case 2:
                            C = a-A;
                            cout << endl << "C (operador -): " << C << endl;
                            C = Menos(a,A);
                            cout << endl << "C (funcão - ): " << C << endl;
                            break;
                        case 3:
                            C = a*A;
                            cout << endl << "C (operador *): " << C << endl;
                            C = Multiplica(a,A); 
                            cout << endl << "C (funcão *): " << C << endl;
                            break;
                        case 4:
                            C = a/A;
                            cout << endl << "C (operador /): " << C << endl;
                            C = Divisao(a,A);
                            cout << endl << "C (funcão /): " << C << endl;
                            break;
                    }
                }
            }
        }
    }
}

void test2() {
    std::cout << "Teste PROFIL test 2" << std::endl;
    std::cout << "%TEST_FAILED% time=0 testname=test2 (Teste PROFIL) message=error message sample" << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% Teste PROFIL" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (Teste PROFIL)" << std::endl;
    clock_t Ticks[4];
    Ticks[0] = clock();
    test1();
    Ticks[1] = clock();
    double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
    printf("Tempo gasto: %g ms.", Tempo);

    Ticks[2] = clock();
    test3();
    Ticks[3] = clock();
    Tempo = (Ticks[3] - Ticks[2]) * 1000.0 / CLOCKS_PER_SEC;
    printf("\nTempo gasto: %g ms.", Tempo);
    
    test4();
    
//    test5();
//    test6();
    
    std::cout << "%TEST_FINISHED% time=0 test1 (Teste PROFIL)" << std::endl;


    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

