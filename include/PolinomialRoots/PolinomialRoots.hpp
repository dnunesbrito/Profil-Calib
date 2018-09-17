/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Polinomial.hpp
 * Author: darlan
 *
 * Created on 21 de Julho de 2016, 15:49
 */

#ifndef POLINOMIAL_HPP
#define POLINOMIAL_HPP

#include <Interval.h>
#include <IntervalMatrix.h>
#include <IntervalVector.h>
#include <NLF/NLF.hpp>
#include <functional>
#include <list>
#include <Constants.h>
#include <Functions.h>

/*Função utilizada para determinar a raiz de uma função quadrática
 Entrada:
 * coeffs: Coeficientes da função quadrática na ordem -
 *    coeffs(1) = A;
 *    coeffs(2) = B;
 *    coeffs(3) = C;
 Retorno:
 * Vetor intervalar contendo as raízes.
 */
INTERVAL_VECTOR Roots(CONST INTERVAL_VECTOR & coeffs);

#endif /* POLINOMIAL_HPP */

