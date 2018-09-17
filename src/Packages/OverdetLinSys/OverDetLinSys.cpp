/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <OverDetLinSys/OverDetLinSys.hpp>

VOID Gauss_Seidel_pivoting(MATRIX& FactA,MATRIX& B,CONST MATRIX& A){
    FactA = A;
    B = Id(RowDimension(FactA));
    VECTOR tmpRowA,tmpRowB;
    MATRIX Factabs = Abs(FactA);
    for(INT k = 1;k <= ColDimension(FactA);k++){
        VECTOR tmpColFac;
        tmpColFac = Col(FactA,k).Box(k,RowDimension(FactA));
        cout << "Col(FactA," << k << ")=" << tmpColFac << endl;
        INT IdMax = tmpColFac.maxID()+(k-1);
        if(IdMax > k){
            tmpRowA = Row(FactA,k);
            tmpRowB = Row(B,k);
            SetRow(FactA,k,Row(FactA,IdMax));
            SetRow(B,k,Row(B,IdMax));
            SetRow(FactA,IdMax,tmpRowA);
            SetRow(B,IdMax,tmpRowB);
        }
        for(INT i = k+1;i <= RowDimension(FactA);i++){
            if(FactA(k,k) == 0)
                break;
            REAL pivot = -FactA(i,k)/FactA(k,k);
            for(INT j = 1;j <= ColDimension(FactA);j++){
                FactA(i,j) += pivot*FactA(k,j);
                B(i,j) += pivot*B(k,j);
            }
        }
    }
}
VOID Solve_Over_Lin_Sys(CONST INTERVAL_MATRIX& A,CONST INTERVAL_VECTOR b,INTERVAL_VECTOR& X){
    MATRIX FactA,B,Ac;
    Ac = Mid(A);
    INT rdim = RowDimension(A);
    INT cdim = ColDimension(A);
    Gauss_Seidel_pivoting(FactA,B,Ac);
    INTERVAL_MATRIX M,A_out;
    M = B*A;
    INTERVAL_VECTOR r,x_out;
    r = B*b;
    if(Gauss_Elimination(M,r,A_out,x_out)==0)
        return;
    INTERVAL_MATRIX T,W;
    INTERVAL_VECTOR u,v,z;
    T = A_out.Box(1,cdim,1,cdim);
    W = A_out.Box(cdim+1,rdim,1,cdim);
    z = Col(W,cdim);
    u = x_out.Box(1,cdim);
    v = x_out.Box(cdim+1,rdim);
    Resize(X,cdim);
    X(cdim) = u(cdim)/T(cdim,cdim);
    for(INT i = 1;i <= rdim-cdim;i++){
        Intersection(X(cdim),X(cdim),v(i)/z(i));
    }
    INTERVAL sum;
    for(INT i=cdim-1;i>=1;i--)
    {
        if((0.0 <= T(i,i))|| fabs(Sup(T(i,i)))<=Machine::MinPositive ||
                fabs(Inf(T(i,i)))<=Machine::MinPositive)return;
        sum=u(i);
        for(INT j=i+1;j<=cdim;j++)
            sum-=T(i,j)*X(j);
        X(i)=sum/T(i,i);
    }
}