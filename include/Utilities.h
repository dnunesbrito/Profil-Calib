/************************************************************************
 *
 * Definition of Some utility routines
 * -----------------------------------
 *
 * Copyright (C) 1993, 1997 Olaf Knueppel
 *               2009 Christian Keil
 *
 * This file is part of PROFIL/BIAS.
 *
 * PROFIL/BIAS is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 *
 * $Id: Utilities.h 592 2009-01-28 10:04:19Z christian $
 *
 ************************************************************************/

#ifndef __UTILITIES__
#define __UTILITIES__

#include <eigen3/Eigen/Eigenvalues>
#include <eigen3/Eigen/src/Core/Matrix.h>

#include <IntervalMatrix.h>
#include <EINTERVAL_MATRIX.hpp>
#include <EFunctions.h>
#include <assert.h>

enum SYSTEMSTATUS {regular , singular , hull_computed , solution_computed, enclosure_not_computed};
MATRIX Inverse (CONST MATRIX &);
MATRIX Transpose (CONST MATRIX &);
INTERVAL_MATRIX Transpose (CONST INTERVAL_MATRIX &);
/*Converte um vetor contendo ângulos
 de Euler para uma matriz intervalar.
 A ordem para os ângulos é XYZ.*/
EINTERVAL_MATRIX Eul2rtm(CONST EINTERVAL_VECTOR& src);
EINTERVAL_MATRIX Eul2rtm(CONST EINTERVAL_MATRIX& src);
INTERVAL_MATRIX Eul2rtm(CONST INTERVAL_MATRIX &);
INTERVAL_MATRIX Eul2rtm(CONST INTERVAL_VECTOR& src);
INTERVAL_MATRIX Eul2rtm(CONST REAL AngX,CONST REAL AngY,CONST REAL AngZ);
INTERVAL_MATRIX Eul2rtm(CONST INTERVAL AngX,CONST INTERVAL AngY,CONST INTERVAL AngZ);
INTERVAL_MATRIX rtm2Eul(CONST INTERVAL_MATRIX & R);
MATRIX MEul2rtm(CONST VECTOR & src);
INTERVAL_VECTOR Lower (CONST INTERVAL_VECTOR &, INT);
INTERVAL_VECTOR Upper (CONST INTERVAL_VECTOR &, INT);
MATRIX Id (INT);
INTERVAL_VECTOR ZEROS(INT nElementos);
INTERVAL_MATRIX ZEROS(INT nRows, INT nCols);
REAL RelDiam (CONST INTERVAL &);
VECTOR RelDiam (CONST INTERVAL_VECTOR &);
VECTOR sgn(const INTERVAL_VECTOR&);
VECTOR sgn(const VECTOR& x);
REAL SpectralRadius(const Eigen::MatrixXd& IN);
Eigen::MatrixXd MATRIX2MatrixXd(const MATRIX& A);
MATRIX MatrixXd2MATRIX(const Eigen::MatrixXd& A);
Eigen::VectorXd VECTOR2VectorXd(const VECTOR& A);
VECTOR VectorXd2VECTOR(const Eigen::VectorXd& A);
bool isRegular(INTERVAL_MATRIX IN);
bool isSingular(MATRIX& As,CONST INTERVAL_MATRIX& A);
MATRIX ynset(INT n);

int Inverse_Interval_Matrix(int Dim,int cond,INTERVAL_MATRIX &Jac,INTERVAL_MATRIX &InvJac);
int Gauss_Elimination(INTERVAL_MATRIX &Ain,INTERVAL_VECTOR &b,INTERVAL_MATRIX &A_out,INTERVAL_VECTOR &b_out);
INTERVAL_MATRIX SkewSymmetricMatrix(INTERVAL_VECTOR A);
float MaxDiffPair(CONST std::pair<REAL,REAL> src1,CONST std::pair<REAL,REAL> src2);
INTERVAL_VECTOR Mean(const INTERVAL_MATRIX& IN);
INTERVAL Mean(const INTERVAL_VECTOR& IN);
VOID Normalize2DpointsCentroid(INTERVAL_MATRIX& XOUT,const INTERVAL_MATRIX& XIN,INTERVAL_VECTOR& T);
REAL Meandistance(const INTERVAL_MATRIX& IN);
VOID Normalize2Dpoints(INTERVAL_MATRIX& X,const INTERVAL_MATRIX& X1,INTERVAL_MATRIX& T);
INTERVAL MeanDistance(CONST INTERVAL_VECTOR& X1,CONST INTERVAL_VECTOR X2);
INTERVAL_VECTOR OverLinSys(CONST INTERVAL_MATRIX& Ain,CONST INTERVAL_VECTOR& bin);
INTERVAL_VECTOR Join3pontos(INTERVAL_MATRIX Pontos);
#endif /* __UTILITIES__ */
