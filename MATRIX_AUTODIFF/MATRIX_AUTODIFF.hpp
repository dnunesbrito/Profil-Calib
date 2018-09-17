/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MATRIX_AUTODIFF.hpp
 * Author: darlan
 *
 * Created on 8 de Abril de 2016, 08:54
 */
#include <AutoDiff/IntervalAutoDiff.h>
#include <IntervalMatrix.h>

#ifndef MATRIX_AUTODIFF_HPP
#define MATRIX_AUTODIFF_HPP

class MATRIX_AUTODIFF {
public:
    INTERVAL_AUTODIFF theElements;
    INT nCols;
    INT nRows;
    MATRIX_AUTODIFF ();
    MATRIX_AUTODIFF (CONST INTERVAL_MATRIX&);
    MATRIX_AUTODIFF(const MATRIX_AUTODIFF& orig);
    virtual ~MATRIX_AUTODIFF();
    AUTODIFF_TYPE operator () (INT i, INT j) CONST
    { return  theElements((i-1)*nRows+j);}

    MATRIX_AUTODIFF & operator *  (CONST MATRIX_AUTODIFF &);
    MATRIX_AUTODIFF & operator /  (CONST MATRIX_AUTODIFF &);
    MATRIX_AUTODIFF & operator *= (CONST MATRIX_AUTODIFF &);
    MATRIX_AUTODIFF & operator /= (CONST MATRIX_AUTODIFF &);
private:

};

#endif /* MATRIX_AUTODIFF_HPP */

