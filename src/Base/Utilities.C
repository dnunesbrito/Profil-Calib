/************************************************************************
 *
 * Implementation of Some Utility Routines
 * ---------------------------------------
 *
 * Copyright (C) 1993, 1997 Olaf Knueppel
 *               2005, 2009 Christian Keil
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
 * $Id: Utilities.C 592 2009-01-28 10:04:19Z christian $
 *
 ************************************************************************/

static const char rcs_id[] = "$Id: Utilities.C 592 2009-01-28 10:04:19Z christian $";

#include <Utilities.h>
#include <IntervalMatrix.h>
#include <Constants.h>
#include <Functions.h>
#include <Error.h>
#include <cstring>
#include <math.h>
#include <eigen3/Eigen/src/Core/Matrix.h>
#include <eigen3/Eigen/src/Core/VectorBlock.h>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Eigenvalues>

#include <header_2B.h>
#include <GlobalOpt/VecUtils.h>
#include <math.h>
#include <LSS.h>


#define MAXDIM 200 // larger dimensions will allocate temporary memory
#define Debug_Level_Solve_General_Interval 2

MATRIX Inverse (CONST MATRIX & A){
  INT i, j, k, imax, ip, kk, l;
  INT isSingular = 0;
  INT dim = RowDimension (A);
  static INT _ipiv[MAXDIM];
  static REAL _vv[MAXDIM];

  CheckQuadratic (A);
  MATRIX R(dim, dim);
  MATRIX Result(dim, dim);
  MakeTemporary (R);

  REAL *pr   = R.theElements;
  REAL *pres = Result.theElements;
  REAL *pa   = A.theElements;
  INT  *ipiv;
  REAL *vv;
  REAL dummy, big, sum;

  memcpy (pr, pa, dim * dim * sizeof(REAL));

  if (dim <= MAXDIM) {
    ipiv = _ipiv;
    vv   = _vv;
  }
  else {
    ipiv = new INT[dim];
    vv   = new REAL[dim];
    if ((ipiv == NULL) || (vv == NULL))
      FatalError ("Out of Memory in Inverse");
  }

  // LU Decomposition
  for (i = 0; i < dim; i++) {
    big = 0.0;
    for (j = 0; j < dim; j++)
      if ((dummy = fabs (pr[i * dim + j])) > big) big = dummy;
    if (big == 0.0) {
      if (!isSingular){
	Error ("Singular Matrix in Inverse", 1, ErrorHandler::Warning);
        Clear(Result);
        return Result;
      }
      isSingular = 1;
      big = Machine::Epsilon;
    }
    vv[i] = 1.0 / big;
  }
  for (j = 0; j < dim; j++) {
    for (i = 0; i < j; i++) {
      sum = pr[i * dim + j];
      for (k = 0; k < i; k++)
	sum -= pr[i * dim + k] * pr[k * dim + j];
      pr[i * dim + j] = sum;
    }
    big = 0.0;
    imax = j;
    for (i = j; i < dim; i++) {
      sum = pr[i * dim + j];
      for (k = 0; k < j; k++)
	sum -= pr[i * dim + k] * pr[k * dim + j];
      pr[i * dim + j] = sum;
      if ((dummy = vv[i] * fabs (sum)) >= big) {
	big = dummy;
	imax = i;
      }
    }
    if (j != imax) {
      for (k = 0; k < dim; k++) {
	dummy              = pr[imax * dim + k];
	pr[imax * dim + k] = pr[j * dim + k];
	pr[j * dim + k]    = dummy;
      }
      vv[imax] = vv[j];
    }
    ipiv[j] = imax;
    if (pr[(dim + 1) * j] == 0.0) {
      if (!isSingular)
	Error ("Singular Matrix in Inverse", 1, ErrorHandler::Warning);
      isSingular = 1;
      pr[(dim + 1) * j] = Machine::Epsilon;
    }
    if (j != dim - 1) {
      dummy = 1.0 / pr[(dim + 1) * j];
      for (i = j + 1; i < dim; i++) pr[i * dim + j] *= dummy;
    }
  }
  // Backsubstitution
  for (j = 0; j < dim; j++) {
    for (i = 0; i < dim; i++) vv[i] = 0.0;
    vv[j] = 1.0;
    kk = -1;
    for (k = 0; k < dim; k++) {
      ip = ipiv[k];
      sum = vv[ip];
      vv[ip] = vv[k];
      if (kk >= 0)
	for (l = kk; l <= k - 1; l++)
	  sum -= pr[k * dim + l] * vv[l];
      else if (sum != 0.0) kk = k;
      vv[k] = sum;
    }
    for (k = dim - 1; k >= 0; k--) {
      sum = vv[k];
      for (l = k + 1; l < dim; l++)
	sum -= pr[k * dim + l] * vv[l];
      vv[k] = sum / pr[(dim + 1) * k];
    }
    for (i = 0; i < dim; i++) pres[i * dim + j] = vv[i];
  }

  if (dim > MAXDIM) {
    delete [] ipiv;
    delete [] vv;
  }
  return Result;
}

#undef MAXDIM

MATRIX Transpose (CONST MATRIX & a){
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  INT i, j;
  MATRIX t (cols, rows);
  REAL *pa, *pt, *pt_start;

  MakeTemporary (t);
  pa = a.theElements; pt_start = t.theElements;
  for (i = 0; i < rows; i++) {
    pt = pt_start;
    for (j = 0; j < cols; j++, pt += rows)
      *pt = *(pa++);
    pt_start++;
  }
  return t;
}

INTERVAL_MATRIX Transpose (CONST INTERVAL_MATRIX & a){
  INT rows = RowDimension (a);
  INT cols = ColDimension (a);
  INT i, j;
  INTERVAL_MATRIX t (cols, rows);
  BIASINTERVAL *pa, *pt, *pt_start;

  MakeTemporary (t);
  pa = a.theElements; pt_start = t.theElements;
  for (i = 0; i < rows; i++) {
    pt = pt_start;
    for (j = 0; j < cols; j++, pt += rows)
      *pt = *(pa++);
    pt_start++;
  }
  return t;
}
EINTERVAL_MATRIX Eul2rtm(CONST EINTERVAL_VECTOR& src){
    EINTERVAL_MATRIX out(3,3);
    EINTERVAL sa,ca;
    sa = Sin(src(1)); ca = Cos(src(1));
    EINTERVAL sb,cb;
    sb = Sin(src(2)); cb = Cos(src(2));
    EINTERVAL sc,cc;
    sc = Sin(src(3)); cc = Cos(src(3));
    EINTERVAL_MATRIX r(3,3,{           cb*cc,          -cb*sc,      sb,
                            ca*sc + cc*sa*sb, ca*cc - sa*sb*sc, -cb*sa,
                            sa*sc - ca*cc*sb, cc*sa + ca*sb*sc,  ca*cb});

//
//    EINTERVAL_MATRIX rz(3,3,{ -cc,            sc,            Constant::ZERO,
//                       -sc,            -cc,            Constant::ZERO,
//                       Constant::ZERO, Constant::ZERO,Constant::UM});
//    EINTERVAL_MATRIX ry(3,3,{-cb,            Constant::ZERO,sb,
//                              Constant::ZERO,Constant::UM,  Constant::ZERO,
//                              -sb,           Constant::ZERO,-cb});
//    EINTERVAL_MATRIX rx(3,3,{Constant::UM,Constant::ZERO,Constant::ZERO,
//                              Constant::ZERO,-ca, sa,
//                              Constant::ZERO,-sa, -ca});
//    out = rx*ry*rz;
    return r;
}
EINTERVAL_MATRIX Eul2rtm(CONST EINTERVAL_MATRIX& src){
    EINTERVAL_MATRIX out(3,3);
    EINTERVAL sa,ca;
    sa = Sin(src(1,1)); ca = Cos(src(1,1));
    EINTERVAL sb,cb;
    sb = Sin(src(1,2)); cb = Cos(src(1,2));
    EINTERVAL sc,cc;
    sc = Sin(src(1,3)); cc = Cos(src(1,3));

    EINTERVAL_MATRIX r(3,3,{           cb*cc,          -cb*sc,      sb,
                            ca*sc + cc*sa*sb, ca*cc - sa*sb*sc, -cb*sa,
                            sa*sc - ca*cc*sb, cc*sa + ca*sb*sc,  ca*cb});
    return r;
}
INTERVAL_MATRIX Eul2rtm(CONST INTERVAL_MATRIX& src){
    INTERVAL_MATRIX out(3,3);
    INTERVAL sa,ca;
    sa = Sin(src(1,1)); ca = Cos(src(1,1));
    INTERVAL sb,cb;
    sb = Sin(src(1,2)); cb = Cos(src(1,2));
    INTERVAL sc,cc;
    sc = Sin(src(1,3)); cc = Cos(src(1,3));

    INTERVAL_MATRIX rz(3,3);
    rz = INTERVAL_MATRIX(3,3,{ -cc,            sc,            Constant::ZERO,
                       -sc,            -cc,            Constant::ZERO,
                       Constant::ZERO, Constant::ZERO,Constant::UM});
    INTERVAL_MATRIX ry(3,3);
    ry = INTERVAL_MATRIX(3,3,{-cb,            Constant::ZERO,sb,
                              Constant::ZERO,Constant::UM,  Constant::ZERO,
                              -sb,           Constant::ZERO,-cb});
    INTERVAL_MATRIX rx(3,3);
    rx = INTERVAL_MATRIX(3,3,{Constant::UM,Constant::ZERO,Constant::ZERO,
                              Constant::ZERO,-ca, sa,
                              Constant::ZERO,-sa, -ca});
    out = rx*ry*rz;
    return out;
}
INTERVAL_MATRIX Eul2rtm(CONST INTERVAL_VECTOR& src){
    INTERVAL_MATRIX out(3,3);
    INTERVAL sa,ca;
    sa = Sin(src(1)); ca = Cos(src(1));
    INTERVAL sb,cb;
    sb = Sin(src(2)); cb = Cos(src(2));
    INTERVAL sc,cc;
    sc = Sin(src(3)); cc = Cos(src(3));

    INTERVAL_MATRIX r(3,3,{           cb*cc,          -cb*sc,      sb,
                            ca*sc + cc*sa*sb, ca*cc - sa*sb*sc, -cb*sa,
                            sa*sc - ca*cc*sb, cc*sa + ca*sb*sc,  ca*cb});
    return r;
}
INTERVAL_MATRIX Eul2rtm(CONST REAL AngX,CONST REAL AngY,CONST REAL AngZ){
    INTERVAL_MATRIX out(3,3);
    INTERVAL sa,ca;
    sa = Sin(AngX); ca = Cos(AngX);
    INTERVAL sb,cb;
    sb = Sin(AngY); cb = Cos(AngY);
    INTERVAL sc,cc;
    sc = Sin(AngZ); cc = Cos(AngZ);

    INTERVAL_MATRIX r(3,3,{           cb*cc,          -cb*sc,      sb,
                            ca*sc + cc*sa*sb, ca*cc - sa*sb*sc, -cb*sa,
                            sa*sc - ca*cc*sb, cc*sa + ca*sb*sc,  ca*cb});
    return r;
}
INTERVAL_MATRIX Eul2rtm(CONST INTERVAL AngX,CONST INTERVAL AngY,CONST INTERVAL AngZ){
    INTERVAL_MATRIX out(3,3);
    INTERVAL sa,ca;
    sa = Sin(AngX); ca = Cos(AngX);
    INTERVAL sb,cb;
    sb = Sin(AngY); cb = Cos(AngY);
    INTERVAL sc,cc;
    sc = Sin(AngZ); cc = Cos(AngZ);

    INTERVAL_MATRIX r(3,3,{           cb*cc,          -cb*sc,      sb,
                            ca*sc + cc*sa*sb, ca*cc - sa*sb*sc, -cb*sa,
                            sa*sc - ca*cc*sb, cc*sa + ca*sb*sc,  ca*cb});
    return r;
}
INTERVAL_MATRIX rtm2Eul(CONST INTERVAL_MATRIX & R){
    INTERVAL_VECTOR Psy(2),Theta(2),Phi(2),tmpAng(3);
    INTERVAL_MATRIX EulAngles(3,2);
    INTERVAL_MATRIX r = R;
    for(int i = 1;i <= 3;i++){
        INTERVAL_VECTOR Lnorm;
        if(R.row(i).max() > 1){
            Lnorm = R.row(i)/Sup(Norm(R.row(i)));
            SetRow(r,i,Lnorm);
        }
    }
    Theta(1) = ArcSin(r(1,3));
    if(!(1 <= r(1,3)) && !(-1 <= r(1,3))){
        Theta(2) = Constant::Pi - Theta(1);
        if(0.0 <= Cos(Theta(1))){
            Psy(1) = INTERVAL(-Constant::Pi/2,Constant::Pi/2);
            Phi(1) = INTERVAL(-Constant::Pi/2,Constant::Pi/2);
        }else{
            Psy(1) = ArcTan2(-r(1,2)/Cos(Theta(1)),r(1,1)/Cos(Theta(1)));
            Phi(1) = ArcTan2(-r(2,3)/Cos(Theta(1)),r(3,3)/Cos(Theta(1)));
        }
        if(0.0 <= Cos(Theta(2))){
            Psy(2) = INTERVAL(-Constant::Pi/2,Constant::Pi/2);
            Phi(2) = INTERVAL(-Constant::Pi/2,Constant::Pi/2);
        }else{
            Psy(2) = ArcTan2(-r(1,2)/Cos(Theta(2)),r(1,1)/Cos(Theta(2)));
            Phi(2) = ArcTan2(-r(2,3)/Cos(Theta(2)),r(3,3)/Cos(Theta(2)));
        }
    }else{
        if(Diam(r(1,3)) <= 0){
            Phi(1) = INTERVAL(0.0);
            if(-1 <= r(1,3)){
                Psy(1)=ArcTan2(-r(2,1),-r(3,1));
            }else{
                Psy(1)=ArcTan2(r(2,1),r(3,1));            
            }
        }else if(Diam(r(1,2)) == 0 && Inf(r(1,2)) == 0){
            Psy(1)=ArcTan2(r(2,1),r(3,1));
            Phi(1) = ArcTan2(-Sup(r(2,3))/Cos(Sup(Theta(1))),Sup(r(3,3))/Cos(Sup(Theta(1))));
        }else{
            Psy(1) = ArcTan2(-Inf(r(1,2))/Cos(Sup(Theta(1))),Sup(r(1,1))/Cos(Sup(Theta(1))));
            Phi(1) = ArcTan2(-Inf(r(2,3))/Cos(Sup(Theta(1))),Sup(r(3,3))/Cos(Sup(Theta(1))));
        }
    }
    tmpAng(3)=Psy(1);
    tmpAng(2)=Theta(1);
    tmpAng(1)=Phi(1);
    SetCol(EulAngles,1,tmpAng);
    tmpAng(3)=Psy(2);
    tmpAng(2)=Theta(2);
    tmpAng(1)=Phi(2);
    SetCol(EulAngles,2,tmpAng);
    return EulAngles;
}
MATRIX MEul2rtm(CONST VECTOR& src){
    MATRIX out(3,3);
    REAL sa,ca;
    sa = Sin(src(1)); ca = Cos(src(1));
    REAL sb,cb;
    sb = Sin(src(2)); cb = Cos(src(2));
    REAL sc,cc;
    sc = Sin(src(3)); cc = Cos(src(3));

    MATRIX rz;
    rz = MATRIX(3,3,{ -cc,            sc,            0,
                       -sc,            -cc,            0,
                       0, 0,1});
    MATRIX ry;
    ry = MATRIX(3,3,{-cb,            0,sb,
                              0,1,  0,
                              -sb,           0,-cb});
    MATRIX rx;
    rx = MATRIX(3,3,{1,0,0,
                              0,-ca, sa,
                              0,-sa, -ca});
    out = rx*ry*rz;
    return out;
}
// Bisect x normal to direction "split" and
// return the lower half.
INTERVAL_VECTOR Lower (CONST INTERVAL_VECTOR & x, INT split){
  INT dim = Dimension (x);
  INTERVAL_VECTOR t (dim);

  CheckVectorIndex (split, x);
  MakeTemporary (t);
  t = x;
  t(split) = Hull (Inf (x(split)), Mid (x(split)));
  return t;
}
// Bisect x normal to direction "split" and
// return the upper half.

INTERVAL_VECTOR Upper (CONST INTERVAL_VECTOR & x, INT split){
  INT dim = Dimension (x);
  INTERVAL_VECTOR t (dim);

  CheckVectorIndex (split, x);
  MakeTemporary (t);
  t = x;
  t(split) = Hull (Mid (x(split)), Sup (x(split)));
  return t;
}

MATRIX Id (INT dim){
  INT i;
  MATRIX I (dim, dim);

  MakeTemporary (I);
  Clear (I);

  for (i = 1; i <= dim; i++) I(i,i) = 1.0;
  return I;
}

REAL RelDiam (CONST INTERVAL & x){
  if (0.0 <= x) return Diam (x);
  else return (Diam (x) / fabs (Mid (x)));
}

VECTOR RelDiam (CONST INTERVAL_VECTOR & x){
  INT i;
  INT dim = Dimension (x);
  VECTOR temp (dim);

  MakeTemporary (temp);
  for (i = 1; i <= dim; i++) temp (i) = RelDiam (x(i));
  return temp;
}
INTERVAL_VECTOR ZEROS(INT nElementos){
    INTERVAL_VECTOR OUT(nElementos);
    for(int i = 1;i <= nElementos;i++)
        OUT(i)=Constant::ZERO;
    return OUT;
}
INTERVAL_MATRIX ZEROS(INT nRows, INT nCols){
    INTERVAL_MATRIX OUT(nRows,nCols);
    for(int i = 1;i <= nRows;i++)
        for(int j = 1;j <= nCols;j++)
            OUT(i,j)=Constant::ZERO;
    return OUT;
}
VECTOR sgn(const INTERVAL_VECTOR& x){
    VECTOR z(Dimension(x));
    for(int i = 1;i <= Dimension(x);i++){
        if(Inf(x(i)) > 0)z(i) = 1;
        else if(Sup(x(i)) < 0)z(i) = -1;
        else z(i)=1;
    }
    return z;
}
VECTOR sgn(const VECTOR& x){
    VECTOR z(Dimension(x));
    for(int i = 1;i <= Dimension(x);i++){
        if(x(i) >= 0)z(i) = 1;
        else z(i) = -1;
    }
    return z;
}
Eigen::MatrixXd MATRIX2MatrixXd(const MATRIX& A){
    Eigen::MatrixXd B(RowDimension(A),ColDimension(A));
    for(int i = 0;i < RowDimension(A);i++)
        for(int j = 0;j < ColDimension(A);j++)
            B(i,j)=A(i+1,j+1);
    return B;
}
MATRIX MatrixXd2MATRIX(const Eigen::MatrixXd& A){
    MATRIX B(A.rows(),A.cols());
    for(int i = 0;i < A.rows();i++)
        for(int j = 0;j < A.cols();j++)
            B(i+1,j+1)=A(i,j);
    return B;
   
}
Eigen::VectorXd VECTOR2VectorXd(const VECTOR& A){
    Eigen::VectorXd B(A.rows());
    for(int i = 0;i < A.rows();i++)
            B(i)=A(i+1);
    return B;
}
VECTOR VectorXd2VECTOR(const Eigen::VectorXd& A){
    VECTOR B(A.rows());
    for(int i = 0;i < A.rows();i++)
        B(i+1)=A(i);
    return B;
   
}
REAL SpectralRadius(const Eigen::MatrixXd & IN){
    Eigen::EigenSolver<Eigen::MatrixXd> EigSol(IN);
    Eigen::VectorXcd eivals = EigSol.eigenvalues();
    Eigen::VectorXd normeivals = eivals.rowwise().norm();
    return normeivals.maxCoeff();
}
/*
 Teste para determinar se a matriz intervalar é regular e consequentemente se 
 possui inversa de acordo com o artigo:                                       
 /home/darlan/Dropbox/PhD/Papers/Interval Algebra/vol18_pp500-512.pdf        
*/
bool isRegular(INTERVAL_MATRIX A){
    //Teste ii
    MATRIX Amid = Mid(A),R,Rabs,RDelta;
    MATRIX Delta = Diam(A)/2;
    Eigen::MatrixXd Ac,EMRD;
    Eigen::MatrixXd D;
    Ac = MATRIX2MatrixXd(Amid);
    D = MATRIX2MatrixXd(Delta);
    R = Inverse(Amid);
    if(ErrorHandler::LastErrorCode != 0)return false;
    Rabs = Abs(R);
    RDelta = Rabs*Delta;
    EMRD = MATRIX2MatrixXd(RDelta);
    REAL epsilon = SpectralRadius(EMRD);
    if(epsilon < 1.0)return true;
    for(int j = 1;j <= ColDimension(RDelta);j++)
        if(RDelta(j,j) >= 1)return false;
    VECTOR b(ColDimension(A)),bl(ColDimension(A));
    Initialize(b,1);
    VECTOR Rb,Rbl;
    Rb = R*b;
    REAL lambda;
    lambda = Rb.Min();
    for(int i = 1;i <= ColDimension(A);i++){
        for(int j = 1;j <= ColDimension(A);j++){
            bl = b;
            bl(j) = -bl(j);
            Rbl = R*bl;
            if(Rbl.Min() > lambda){
                lambda = Rbl.Min();
                b = bl;
            }
        }
    }
}
void printMATRIXMatlabformat(CONST string& name,CONST MATRIX& A){
    cout << name << "= [";
    for(int i = 1;i <= RowDimension(A);i++){
        for(int j = 1;j <= ColDimension(A);j++)
            cout << A(i,j) << " ";
        if(i < RowDimension(A))
            cout << ";" << endl;
    }
    cout << "];" << endl;
}
void printMATRIXMatlabformat(CONST string& name,CONST VECTOR& A){
    cout << name << "= [";
    for(int i = 1;i <= Dimension(A);i++){
            cout << A(i);
            if(i < Dimension(A))
                cout << ";" << endl;
    }
    cout << "];" << endl;
}
void printMATRIXMatlabformat(CONST string& name,CONST REAL& A){
    cout << name << "=" << A << ";" << endl;
}
MATRIX VECTOR2MATRIX(CONST VECTOR& v){
    MATRIX out(Dimension(v),1);
    for(int i = 1;i <= Dimension(v);i++)
        out(i,1)=v(i);
    return out;
}
bool isSingular(MATRIX& As,CONST INTERVAL_MATRIX& A){
    MATRIX D;
    INT n = RowDimension(A);
    MATRIX Ac(n,n);
    Ac = Mid(A);
    Resize(As,n,n);
    ErrorHandler::LastErrorCode = 0;
    Inverse(Ac);
    if(ErrorHandler::LastErrorCode != 0){
        As = Ac;
        return true;
    }
    VECTOR y(n),z(n),t(2*n-1);
    Initialize(y,1);Initialize(z,1);Clear(t);
    VECTOR e1(2*n-1);
    Initialize(e1,1);
    MATRIX eid;
    eid = Id(n);
    ErrorHandler::LastErrorCode = 0;
    D = Inverse(Inf(A));
    if(ErrorHandler::LastErrorCode != 0){
        As = Inf(A);
        return true;
    }
    REAL tau,alpha;
    MATRIX Ty(n,n),Tz(n,n),Delta(n,n);
    Delta = Diam(A)/2;
    MATRIX ei,ei_t,ej,ej_t;
    while(t != e1){
        int k = 1;
        for(;t(k) != 0;k++);
        int i;
        for(i = 1;i < k;i++)t(i)=0;
        t(k)=1;
        MATRIX p;
        if(k <= n){
            i = k;
            ei = VECTOR2MATRIX(Col(eid,i));
            ei_t = Transpose(ei);
            p = ei_t*Ac*D-ei_t;
            if(2*p(1,i)+1 <= 0){
                MATRIX AcD;
                AcD = Ac*D;
                tau = -y(i)/(2*p(1,i));
                Ty = Mid(Diag(n,n,Hull(y)));
                Tz = Mid(Diag(n,n,Hull(z)));
                As = Ac-(Ty-2*tau*ei*ei_t)*Delta*Tz;
                As.print("As");
                Inverse(As);
                return true;
            }
            alpha = 2/(2*p(1,i)+1);
            D = D - alpha*D*ei*p;
            y(i) = -y(i);
        }else{
            int j = k - n;
            ej = VECTOR2MATRIX(Col(eid,j));
            ej_t = Transpose(ej);
            p = D*Ac*ej;
            if(2*p(1,j)+1 <= 0){
                tau = -z(j)/(2*p(1,j));
                As = Ac-Ty*Delta*(Tz-2*tau*ej*ej_t);
                return true;
            }
            alpha = 2/(2*p(1,j)+1);
            D = D - alpha*p*ej*D;
            z(j) = -z(j);
        }
    }
    return false;
}

MATRIX ynset(INT n){
    MATRIX Y;
    VECTOR z(n),y(n),e(n);
    Clear(z);
    Initialize(y,1);
    Initialize(e,1);
    Y.hcat(y);
    while( z != e){
        int k = 1;
        for(;z(k) != 0;k++);
        for(int i = 1;i < k;i++)z(i)=0;
        z(k)=1;
        y(k)=-y(k);
        Y.hcat(y);
    }
    return Y;
}
/*-------------------------
La plus simple des eliminations de Gauss
Returns in bout the solution enclosure. This procedure returns:
1: algo has succeeded
0: algo has failed
-------------------------*/
int Gauss_Elimination(INTERVAL_MATRIX &Ain,
                      INTERVAL_VECTOR &b,
                      INTERVAL_MATRIX &A_out,
                      INTERVAL_VECTOR &b_out){
    INT rdim=RowDimension(Ain);
    INT cdim=ColDimension(Ain);
    INTERVAL sum,U;
    int i,j,k;
    b_out=b;
    A_out=Ain;

//Gauss elimination
    for(k=1;k<=cdim-1;k++)
    {
        if((0.0 <= A_out(k,k))|| fabs(Sup(A_out(k,k)))<=Machine::MinPositive ||
                fabs(Inf(A_out(k,k)))<=Machine::MinPositive)
        {
            INTERVAL_VECTOR tmpRowA;
            INTERVAL tmpb;
            tmpRowA = Row(A_out,k);
            tmpb = b_out(k);
            INT l;
            for(l = k+1;l <= RowDimension(A_out);l++){
                if(!(0.0 <= A_out(l,k))){
                    SetRow(A_out,k,Row(A_out,l));
                    b_out(k) = b_out(l);
                    b_out(l) = tmpb;
                    SetRow(A_out,l,tmpRowA);
                    break;
                }
            }
            if(l > RowDimension(A_out))
                return 0;
        }
        for(i=k+1;i<=rdim;i++)
        {
            //computation of the b
            U=b_out(i);
            b_out(i)=U-A_out(i,k)*b_out(k)/A_out(k,k);
            
            //calcul des A
            for(j=1;j<=cdim;j++)
            {
                A_out(i,j)=A_out(i,j)-A_out(k,j)*A_out(i,k)/A_out(k,k);
            }
        }
    }
    //calcul final des b
    //une ameliorarion possible serait de prendre en compte les derivees
    //mais ce n'est pas de la tarte
    if(rdim != cdim)return 1;
    for(i=rdim;i>=1;i--)
    {
        if((0.0 <= A_out(i,i))|| fabs(Sup(A_out(i,i)))<=Machine::MinPositive ||
                fabs(Inf(A_out(i,i)))<=Machine::MinPositive)return 0;
        sum=b_out(i);
        for(j=i+1;j<=cdim;j++) sum-=A_out(i,j)*b_out(j);
        b_out(i)=sum/A_out(i,i);
    }
//    if(Debug_Level_Solve_General_Interval==2)cout<<"New bcond:"<<b_out<<endl;
    return 1;
}
/*-----------------------------
Compute the inverse of an interval matrix

Dim: dimension of the matrix
cond: 1 if a pre-conditionning is used (mid of Jac is used)
Jac: the matrix
Invjac: the inverse

return 1 if an inverse has been determined, 0 otherwise
-----------------------------*/
int Inverse_Interval_Matrix(int Dim,int cond,INTERVAL_MATRIX &Jac,INTERVAL_MATRIX &InvJac){
    int i,j,ierr,old,wl,sl;
    INTERVAL_VECTOR b(Dim);
    INTERVAL_VECTOR b_out(Dim),b2(Dim);
    MATRIX Jac1(Dim,Dim),InvJac1(Dim,Dim);
    INTERVAL_MATRIX Jac2(Dim,Dim),A_out;
    Resize(InvJac,Dim,Dim);
    if(cond==0)
    {
        for(i=1;i<=Dim;i++)
        {
            Clear(b);
            b(i)=1;
            ierr=Gauss_Elimination(Jac,b,A_out,b_out);
            if(ierr!=1)return 0;
            for(j=1;j<=Dim;j++)
                InvJac(j,i)=b_out(j);
       }
     return 1;
    }
    Jac1=Mid(Jac);
    old=ErrorHandler::LastErrorCode;
    ErrorHandler::LastErrorCode=0;
    wl=ErrorHandler::WarningLevel;
    sl=ErrorHandler::SevereLevel;
    ErrorHandler::WarningLevel=2500;
    ErrorHandler::SevereLevel=3500;
    InvJac1=Inverse(Jac1);
    ErrorHandler::WarningLevel=wl;
    ErrorHandler::SevereLevel=sl;
    if(ErrorHandler::LastErrorCode==1)return 0;
    if(ErrorHandler::LastErrorCode!=1)
    {
        for(i=1;i<=Dim;i++)
        {
            Clear(b);
            b(i)=1;
            Jac2=InvJac1*Jac;
            b2=InvJac1*b;
            ierr=Gauss_Elimination(Jac2,b2,A_out,b_out);
            if(ierr!=1)return 0;
            for(j=1;j<=Dim;j++)InvJac(j,i)=b_out(j);
        }
        return 1;
    }
    return 0;
}
INTERVAL_MATRIX SkewSymmetricMatrix(INTERVAL_VECTOR A){
    INTERVAL_MATRIX s(3,3);
    
    s(1,1)=INTERVAL(0,0);   s(1,2)=-A(3);           s(1,3)=A(2);
    s(2,1)=A(3);            s(2,2)=INTERVAL(0,0);   s(2,3)=-A(1); 
    s(3,1)=-A(2);           s(3,2)= A(1);           s(3,3)=INTERVAL(0,0);
    return s;
}
float MaxDiffPair(CONST std::pair<REAL,REAL> src1,CONST std::pair<REAL,REAL> src2){
    float Diff1,Diff2;
    Diff1 = abs(src1.first-src2.first);
    Diff2 = abs(src1.second-src2.second);
    if(Diff1 > Diff2)return Diff1;
    return Diff2;
}
//Eigen::Hyperplane Join3Pontos(CONST Eigen::MatrixXd& PTS){
    
//    Eigen::MatrixXd Pontos;
//    Eigen::Matrix<double,4,1> join;
//    Eigen::Vector3d P0(PTS.row(0)),P1(PTS.row(1)),P2(PTS.row(2));
//    Eigen::Hyperplane<double,3> PI = Eigen::Hyperplane<double,3>::Through( P0,P1,P2 );
//    cout << "Error=" << PI.absDistance(P0) << endl;
    
//    Eigen::Hyperplane<Eigen::Vector4d,3>::Through(P0,P1,P2);
//    join = PI.coeffs();
    
//    if(PTS.rows() > 3)
//        Pontos=PTS.transpose();
//    else
//        Pontos=PTS;
//    if(Pontos.rows() < 3 || Pontos.cols() < 4){
//        cerr << "Os vetores devem ser tridimensionais em coordenadas homogêneas" << endl;
//        return;
//    }
//    Eigen::MatrixXd E1(3,3),E2(3,3),E3(3,3),E4(3,3);
//    E1.block<3,1>(0,0) = Pontos.block<1,3>(0,1).transpose(); //Pontos(1,2:4)'
//    E1.block<3,1>(0,1) = Pontos.block<1,3>(1,1).transpose(); //Pontos(2,2:4)'
//    E1.block<3,1>(0,2) = Pontos.block<1,3>(2,1).transpose(); //Pontos(3,2:4)'
//
//    E2(0,0) = Pontos(0,0); E2(0,1) = Pontos(1,0); E2(0,2) = Pontos(2,0); 
//  //E2=[Pontos(1,1,1)       Pontos(2,1,1)          Pontos(3,1,1);
//    E2.block<2,1>(1,0) = Pontos.block<1,2>(0,2).transpose(); //Pontos(1,3:4)'
//    E2.block<2,1>(1,1) = Pontos.block<1,2>(1,2).transpose(); //Pontos(2,3:4)'
//    E2.block<2,1>(1,2) = Pontos.block<1,2>(2,2).transpose(); //Pontos(3,3:4)'
//      
//    
//    E3.block<2,1>(0,0) = Pontos.block<1,2>(0,0).transpose(); //Pontos(1,1:2)'
//    E3.block<2,1>(0,1) = Pontos.block<1,2>(1,0).transpose(); //Pontos(2,1:2)'
//    E3.block<2,1>(0,2) = Pontos.block<1,2>(2,0).transpose(); //Pontos(3,1:2)'
//    E3(2,0) = Pontos(0,3); //Pontos(1,4)
//    E3(2,1) = Pontos(1,3); //Pontos(2,4)
//    E3(2,2) = Pontos(2,3); //Pontos(3,4)
//
//    E4.row(0) = Pontos..block<1,3>(0,0).transpose(); //Pontos(1,1:3)'
//    E4.row(1) = Pontos..block<1,3>(1,0).transpose(); //Pontos(2,1:3)'
//    E4.row(2) = Pontos..block<1,3>(2,0).transpose(); //Pontos(3,1:3)'
//    
//    //join=[det(E1);-det(E2);det(E3);-det(E4)];
//    join << E1.determinant(),-E2.determinant(),E3.determinant(),-E4.determinant();
//    
//    //Erro=norm(join'*Pontos');
//    Eigen::MatrixXd Error;
//    Error = join*Pontos.transpose();
//    cout << "Error=" << Error.norm() << endl;
//}
INTERVAL_VECTOR Mean(const INTERVAL_MATRIX& IN){
    INTERVAL sum;
    INTERVAL_VECTOR out(RowDimension(IN));
    for(int i = 1;i <= RowDimension(IN);i++){
        sum = 0;
        for(int j = 1;j <= ColDimension(IN);j++){
            sum = sum + IN(i,j);
        }
        out(i) = sum/ColDimension(IN);
    }
    return out;
}
INTERVAL Mean(const INTERVAL_VECTOR& IN){
    INTERVAL out = 0;
    for(int i = 1;i <= Dimension(IN);i++)
        out = out + IN(i);
    return out/Dimension(IN);
}
INTERVAL MeanDistance(CONST INTERVAL_VECTOR& X1,CONST INTERVAL_VECTOR X2){
    INTERVAL out;
    if(Dimension(X1) != Dimension(X2))
        return Machine::NaN;
    INTERVAL_VECTOR sumsqrt(Dimension(X1));
    Initialize(sumsqrt,0);
    for(int i = 1;i <= Dimension(X1);i++)
        sumsqrt(i) = Sqrt(Sqr(X1(i))+Sqr(X2(i)));
    return Mean(sumsqrt);
}
VOID Normalize2DpointsCentroid(INTERVAL_MATRIX& XOUT,const INTERVAL_MATRIX& XIN,INTERVAL_VECTOR& T){
//  Calculate centroid
    INTERVAL_VECTOR c;
    c = Mean(XIN);
    Resize(XOUT,RowDimension(XIN),ColDimension(XIN));
//  Adjust points so that the origin is at the centroid
    for(int i = 1;i <= RowDimension(XIN);i++){
        for(int j = 1;j <= ColDimension(XIN);j++){
            XOUT(i,j) = XIN(i,j)-c(i);
        }
    }
    T = c;
}
VOID Normalize2Dpoints(INTERVAL_MATRIX& X,const INTERVAL_MATRIX& X1,INTERVAL_MATRIX& T){
    INTERVAL_MATRIX Xt,X1n;
    INTERVAL_VECTOR c1;
//  Normalize with the centroid
    if(ColDimension(X1) < 2){
        X = Xt;
        T = T;
        return;
    }
    Normalize2DpointsCentroid(X1n,X1,c1);
    
    if(RowDimension(X1)==2){
        GetHomogeneous(Xt,X1);
    }

    X1n = X1;
    
//  Compute the mean distance
    REAL meandistance1 = Mid(MeanDistance(Row(X1n,1),Row(X1n,2)));

//  Compute the scale factor
    REAL scale1 = Sqrt(2)/meandistance1;

//  Transformation matrix
    T = INTERVAL_MATRIX(3,3,{scale1, 0,      -scale1*c1(1),
                             0,    scale1, -scale1*c1(2),
                             0,    0,       1});

//  Recalculate points
    X = T*Xt;    
}
INTERVAL_VECTOR OverLinSys(CONST INTERVAL_MATRIX& Ain,CONST INTERVAL_VECTOR& bin){
    INTERVAL_MATRIX A,Azeros(ColDimension(Ain),ColDimension(Ain)),AT;
    INTERVAL_VECTOR b,bzeros(ColDimension(Ain));
    A = Id(RowDimension(Ain));
    Clear(Azeros);
    AT = Transpose(Ain);
    A.hcat(Ain);
    AT.hcat(Azeros);
    A.vcat(AT);
    b = bin;
    Clear(bzeros);
    b.vcat(bzeros);
    INT info;
    b = ILSS(A,b,info);
    return b;
}
INTERVAL_VECTOR Join3pontos(INTERVAL_MATRIX Pontos){
    INTERVAL_VECTOR join(4);
    if(Pontos.rows() > 3)
        Pontos=Transpose(Pontos);
    if(Pontos.rows() < 3 || Pontos.cols() < 4){
        cerr << "Os vetores devem ser tridimensionais em coordenadas homogêneas" << endl;
        return join;
    }
    INTERVAL_MATRIX E1;
    INTERVAL_MATRIX P1_2_4,P2_2_4,P3_2_4;
//  E1=[Pontos(1,2:4)' Pontos(2,2:4)' Pontos(3,2:4)'];
    P1_2_4 = Pontos.Box(1,1,2,4);
    P2_2_4 = Pontos.Box(2,2,2,4);
    P3_2_4 = Pontos.Box(3,3,2,4);
    E1.vcat(P1_2_4);
    E1.vcat(P2_2_4);
    E1.vcat(P3_2_4);
//  E2=[Pontos(1,1,1) Pontos(2,1,1) Pontos(3,1,1);Pontos(1,3:4)' Pontos(2,3:4)' Pontos(3,3:4)'];
    INTERVAL_MATRIX E2(3,3);
    E2(1,1) = Pontos(1,1);E2(1,2) = Pontos(2,1);E2(1,3) = Pontos(3,1);
    E2(2,1) = Pontos(1,3);E2(2,2) = Pontos(2,3);E2(2,3) = Pontos(3,3);
    E2(3,1) = Pontos(1,4);E2(3,2) = Pontos(2,4);E2(3,3) = Pontos(3,4);
//  E3=[Pontos(1,1:2)' Pontos(2,1:2)' Pontos(3,1:2)';Pontos(1,4) Pontos(2,4) Pontos(3,4)'];
    INTERVAL_MATRIX E3(3,3);
    E3(1,1) = Pontos(1,1);E3(1,2) = Pontos(2,1);E3(1,3) = Pontos(3,1);
    E3(2,1) = Pontos(1,2);E3(2,2) = Pontos(2,2);E3(2,3) = Pontos(3,2);
    E3(3,1) = Pontos(1,4);E3(3,2) = Pontos(2,4);E3(3,3) = Pontos(3,4);
//  E4=[Pontos(1,1:3)' Pontos(2,1:3)' Pontos(3,1:3)'];
    INTERVAL_MATRIX E4;
    INTERVAL_MATRIX P1_1_3,P2_1_3,P3_1_3;
    P1_1_3 = Pontos.Box(1,1,1,3);
    P2_1_3 = Pontos.Box(2,2,1,3);
    P3_1_3 = Pontos.Box(3,3,1,3);
    E4.vcat(P1_1_3);E4.vcat(P2_1_3);E4.vcat(P3_1_3);  
//  join=[det(E1);-det(E2);det(E3);-det(E4)];
    join(1)=E1.det();join(2)=-E2.det();join(3)=E3.det();join(4)=-E4.det();
    INTERVAL_MATRIX MErro;
    MErro = Pontos*join;
    return join;
}