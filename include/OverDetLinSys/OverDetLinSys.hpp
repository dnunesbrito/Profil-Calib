/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OverDetLinSys.hpp
 * Author: darlan
 *
 * Created on 11 de Agosto de 2016, 14:19
 */

#ifndef OVERDETLINSYS_HPP
#define OVERDETLINSYS_HPP

#include <Interval.h>
#include <IntervalMatrix.h>
#include <IntervalVector.h>
#include <Vector.h>
#include <Matrix.h>
#include <Utilities.h>
#include <Constants.h>

VOID Gauss_Seidel_pivoting(MATRIX& FactA,MATRIX& B,CONST MATRIX& A);
VOID Solve_Over_Lin_Sys(CONST INTERVAL_MATRIX& A,CONST INTERVAL_VECTOR b,INTERVAL_VECTOR& x);

#endif /* OVERDETLINSYS_HPP */

