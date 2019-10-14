/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools  Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: darlan
 *
 * Created on 11 de outubro de 2019, 06:37
 */

#include <cstdlib>
#include <iostream>
#include <BIAS/Bias0.h>
#include <BIAS/SSEBIASINTERVAL.hpp>
#include <cstring>
#include <algorithm> 
#include <chrono> 
#ifdef __SSE2__
  #include <emmintrin.h>
#else
  #warning SSE2 support is not available. Code will not compile
#endif

using namespace std;
using namespace std::chrono; 
/*
 * 
 */
int main(int argc, char** argv) {
    SSEBIASINTERVAL SSEA(1,2),SSEB(3,4),SSEC;
    BIASINTERVAL A,B,C;
    int opcao = 1,repeticoes = 10000000;
    for(int contarg = 1;contarg < argc;contarg++){
        if(strcmp(argv[contarg],"-repeticoes") == 0){
            repeticoes = atoi(argv[contarg+1]);
            contarg++;
        }else if(strcmp(argv[contarg],"-opcao") == 0){
            opcao = atoi(argv[contarg+1]);
            contarg++;
        }
    }
    int i = 0;
    if(opcao == 1){
        auto start = high_resolution_clock::now();
        for(;i < repeticoes;i++){
            __m128d a = _mm_set_pd(1.0,2.0);
            __m128d b = _mm_set_pd(1.0,2.0);
            __m128d presultSSE = _mm_add_pd(a,b);
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl; 
    } else if(opcao == 2){
        auto start = high_resolution_clock::now();
        for(;i < repeticoes;i++){
            A.inf = 1.0;A.sup = 2.0;
            B.inf = 1.0;B.sup = 2.0;
            C.inf = A.inf + B.inf;
            C.sup = A.sup + B.sup;
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl; 
    }    
    cout << "Numero de repetições realizadas: " << i << endl;
    return 0;
}

