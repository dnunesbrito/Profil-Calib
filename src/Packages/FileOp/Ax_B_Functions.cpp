/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IniTsaiAx_B_Functions.cpp
 * Author: darlan
 *
 * Created on 12 de Abril de 2018, 16:03
 */
#include <OptFunctions.h>
#include <cstdlib>

using namespace std;

INTERVAL Ax_B(CONST INTERVAL_VECTOR & X, std::shared_ptr<VOID> userdata){
    std::shared_ptr<LINSYSOPT> opt = std::static_pointer_cast<LINSYSOPT>(userdata);
    INTERVAL_MATRIX A = opt.get()->A;
    INTERVAL_VECTOR B = opt.get()->B;
    INTERVAL_VECTOR Ax_B;
    Ax_B = A*X-B;
    INTERVAL r_2(0.0);
    for(int i = 1;i <= Ax_B.nrows();i++)
        r_2 += Sqr(Ax_B(i));
    return r_2;
}
EINTERVAL EAx_B(CONST EINTERVAL_VECTOR & X, std::shared_ptr<VOID> userdata){
    std::shared_ptr<LINSYSOPT> opt = std::static_pointer_cast<LINSYSOPT>(userdata);
    EINTERVAL_MATRIX A = opt.get()->A;
    EINTERVAL_VECTOR B = opt.get()->B;
    EINTERVAL_VECTOR Ax_B;
    Ax_B = A*X-B;
    EINTERVAL r_2(0.0);
    for(int i = 1;i <= Ax_B.rows();i++)
        r_2 += Sqr(Ax_B(i));
    return r_2;
}
EINTERVAL Ax_B_HC(INTERVAL f_bar,EINTERVAL_VECTOR & X, std::shared_ptr<VOID> userdata){
    std::shared_ptr<LINSYSOPT> opt = std::static_pointer_cast<LINSYSOPT>(userdata);
    EINTERVAL_MATRIX A = opt.get()->A;
    EINTERVAL_VECTOR B = opt.get()->B;
    EINTERVAL_VECTOR sqrAX(A.rows());
    EINTERVAL_VECTOR AX_B;
    AX_B = A*X;
    AX_B = AX_B-B;
    for(int i = 1;i <= AX_B.rows();i++)
        sqrAX(i) = Sqr(AX_B(i));
    EINTERVAL tmpXi1,tmpXi2,tmpXi;
    for(int contX = 1;contX <= A.cols();contX++){
        for(int contEq = 1;contEq <= A.rows();contEq++){
            EINTERVAL sumsqrAXrows(0.0),sumax(0.0);
            for(int k = 1;k <= A.rows();k++){
                if(k == contEq)continue;
                sumsqrAXrows += sqrAX(k);
            }
            for(int k = 1;k <= A.cols();k++){
                if(k == contX)continue;
                sumax += A(contEq,k)*X(k);
            }
            EINTERVAL T1,inter,zeroinf;
            zeroinf = INTERVAL(0,Machine::PosInfinity);
            T1 = f_bar/2 - sumsqrAXrows;
            if(EIntervalIntersection(inter,zeroinf,T1) == 1){
                tmpXi1 = (Sqrt(inter)-(sumax-B(contEq)))/A(contEq,contX);
                tmpXi2 = (-Sqrt(inter)-(sumax-B(contEq)))/A(contEq,contX);
                tmpXi = Hull(tmpXi1,tmpXi2);
            }else{
                X.clear();
                return EINTERVAL(1);
            }
            if(EIntervalIntersection(inter,X(contX),tmpXi) == 1){
                X(contX) = inter;
            }else{
                X.clear();
                return EINTERVAL(1);
            }
        }
    }
    return EINTERVAL(0.0);
}
INTERVAL_VECTOR Ax_B_grd(CONST INTERVAL_VECTOR & X, std::shared_ptr<VOID> userdata){
    std::shared_ptr<LINSYSOPT> opt = std::static_pointer_cast<LINSYSOPT>(userdata);
    INTERVAL_MATRIX A = opt.get()->A;
    INTERVAL_VECTOR B = opt.get()->B;
    INTERVAL_VECTOR AX_B,grd(A.cols());
    AX_B = A*X-B;
    for(int i = 1;i <= A.cols();i++){
        for(int j = 1;j <= A.rows();j++){
            grd(i) += 2*AX_B(j)*A(j,i);
        }
    }
    return grd;
}
EINTERVAL_VECTOR Ax_B_Egrd(CONST EINTERVAL_VECTOR & X, std::shared_ptr<VOID> userdata){
    std::shared_ptr<LINSYSOPT> opt = std::static_pointer_cast<LINSYSOPT>(userdata);
    EINTERVAL_MATRIX A = opt.get()->A;
    EINTERVAL_VECTOR B = opt.get()->B;
    EINTERVAL_VECTOR AX_B,grd(A.cols());
    AX_B = A*X-B;
    for(int i = 1;i <= A.cols();i++){
        for(int j = 1;j <= A.rows();j++){
            if(j == 1)
                grd(i) = 2*AX_B(j)*A(j,i);
            else
                grd(i) += 2*AX_B(j)*A(j,i);
        }
    }
    return grd;
}
EINTERVAL_VECTOR Ax_B_grdHC(INTERVAL f_bar,EINTERVAL_VECTOR & X, INT contX,std::shared_ptr<VOID> userdata){
    std::shared_ptr<LINSYSOPT> opt = std::static_pointer_cast<LINSYSOPT>(userdata);
    EINTERVAL_MATRIX A = opt.get()->A;
    EINTERVAL_VECTOR B = opt.get()->B;
    EINTERVAL_VECTOR AX_B;
    AX_B = A*X-B;
    EINTERVAL tmpXi;
    EINTERVAL_VECTOR grd;
    for(int contEq = 1;contEq <= A.rows();contEq++){
        EINTERVAL sumAXrows(0.0),sumax(0.0);
        for(int k = 1;k <= A.rows();k++){
            if(k == contEq)continue;
            sumAXrows += AX_B(k)*A(k,contX);
        }
        for(int k = 1;k <= A.cols();k++){
            if(k == contX)continue;
            sumax += A(contEq,k)*X(k);
        }
        tmpXi = -f_bar/(2*(-Sqr(A(contEq,contX)))) + (sumAXrows)/(-Sqr(A(contEq,contX)))+(sumax-B(contEq))/-A(contEq,contX);
        EINTERVAL inter;
        if(EIntervalIntersection(inter,X(contX),tmpXi) == 1){
            X(contX) = inter;
        }else{
            X.clear();
            return grd;
        }
    } 
    return grd;
}
EINTERVAL_VECTOR Ax_B_BgrdHC(INTERVAL f_bar,EINTERVAL_VECTOR & X, INT contX,std::shared_ptr<VOID> userdata,CONST MATRIX& Bjac){
    std::shared_ptr<LINSYSOPT> opt = std::static_pointer_cast<LINSYSOPT>(userdata);
    EINTERVAL_MATRIX A = opt.get()->A;
    EINTERVAL_VECTOR B = opt.get()->B;
    EINTERVAL_VECTOR grd;
    EINTERVAL sumgrd(0.0);
    grd = Ax_B_Egrd(X,userdata);
    for(int k = 1;k <= X.rows();k++)
        if(k != contX)
            sumgrd += Bjac(contX,k)*grd(k);
    EINTERVAL tmpXi;
    EINTERVAL_VECTOR AX_B;
    AX_B = A*X-B;
    for(int contEq = 1;contEq <= A.rows();contEq++){
        EINTERVAL sumAXrows(0.0),sumax(0.0);
        for(int k = 1;k <= A.rows();k++){
            if(k == contEq)continue;
            sumAXrows += AX_B(k)*A(k,contX);
        }
        for(int k = 1;k <= A.cols();k++){
            if(k == contX)continue;
            sumax += A(contEq,k)*X(k);
        }
        tmpXi = -f_bar/(2*(Bjac(contX,contX)*-Sqr(A(contEq,contX)))) + (sumAXrows)/(-Sqr(A(contEq,contX)))+(sumax-B(contEq))/-A(contEq,contX)+sumgrd/(Bjac(contX,contX)*-Sqr(A(contEq,contX)));
        EINTERVAL inter;
        if(EIntervalIntersection(inter,X(contX),tmpXi) == 1){
            X(contX) = inter;
        }else{
            X.clear();
            return grd;
        }
    } 
    return grd;    
}
INTERVAL_VECTOR Ax_B_Bgrd(CONST INTERVAL_VECTOR & X, std::shared_ptr<VOID> userdata,CONST MATRIX& Bjac){
    INTERVAL_VECTOR Bgrd,grd;
    grd = Ax_B_grd(X,userdata);
    Bgrd = Bjac*grd;
    return  Bgrd;   
}
EINTERVAL_MATRIX Ax_B_HessHC(INTERVAL f_bar,EINTERVAL_VECTOR & X, INT i,std::shared_ptr<VOID> userdata){
    return EINTERVAL_MATRIX(1,1);
}
INTERVAL_MATRIX Ax_B_Hess(CONST INTERVAL_VECTOR & X, INT l,std::shared_ptr<VOID> userdata){
    std::shared_ptr<LINSYSOPT> opt = std::static_pointer_cast<LINSYSOPT>(userdata);
    INTERVAL_MATRIX A = opt.get()->A;
    INTERVAL_MATRIX Hess(A.rows(),A.rows());
    Initialize(Hess,0.0);
    int m = A.rows();
    int n = A.cols();
    for(int k = 1;k <= n;k++)
        for(int l = 1;l <= n;l++)
            for(int i = 1;i <= m;i++)
                Hess(k,l) += A(i,k)*A(i,l);
    return Hess;
}
INTERVAL_VECTOR Ax_B_Jac(CONST INTERVAL_VECTOR & X, INT i,std::shared_ptr<VOID> userdata){
    std::shared_ptr<LINSYSOPT> opt = std::static_pointer_cast<LINSYSOPT>(userdata);
    INTERVAL_MATRIX A = opt.get()->A;
    INTERVAL_VECTOR grd(A.cols());
    Initialize(grd,0.0);
    int m = A.rows();
    int n = A.cols();
    for(int l = 1;l <= n;l++)
        for(int k = 1;k <= m;k++)
            grd(l) += A(k,i)*A(k,l);
    return grd;
}
INTERVAL_VECTOR Ax_B_BJac(CONST INTERVAL_VECTOR & X, INT idx,std::shared_ptr<VOID> userdata,CONST MATRIX& Bjac){
    std::shared_ptr<LINSYSOPT> opt = std::static_pointer_cast<LINSYSOPT>(userdata);
    INTERVAL_MATRIX A = opt.get()->A;
    int n = A.cols();
    int m = A.rows();
    INTERVAL_VECTOR grd(A.cols());
    Initialize(grd,0.0);
    INTERVAL sum;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            for(int k = 1;k <= m;k++){
                sum += A(k,j)*A(k,i);
            }
            grd(i) += Bjac(idx,j)*2*sum;
        }
    }
    return grd;
}