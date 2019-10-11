/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BiasType.hpp
 * Author: darlan
 *
 * Created on 11 de outubro de 2019, 01:00
 */

#ifndef BIASTYPE_HPP
#define BIASTYPE_HPP
typedef double REAL;
typedef int    INT;
typedef void   VOID;


class BIASINTERVAL{
    BIASINTERVAL(){
        REAL * presult = (REAL *)aligned_alloc(2* sizeof (REAL),16);
    }
    REAL *presult;
};

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* BIASTYPE_HPP */

