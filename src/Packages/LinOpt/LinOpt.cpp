/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LocalOpt.cpp
 * Author: darlan
 * 
 * Created on 27 de Setembro de 2016, 12:29
 */

#include <LinOpt/LinOpt.hpp>

LinOpt::LinOpt() {
}

LinOpt::LinOpt(const LinOpt& orig){
        A = orig.A;
        B = orig.B;
        X = orig.X;
}

LinOpt::~LinOpt() {
    
}

INT LinOpt::RohnOverLinSys(INTERVAL_VECTOR& Xout){
    MATRIX Delta;
    VECTOR delta;
    MATRIX R;
    MATRIX AcT,Acinv;
    Delta = Sup(A)-Ac;
//    bc = Mid(B);
    delta = Sup(B)-bc;
    AcT = Transpose(Ac);
    Acinv = Inverse(AcT*Ac);
    if(ErrorHandler::LastErrorCode != 0)return 0;
    R = Acinv*AcT;
    VECTOR x0;
    x0 = R*bc;
    MATRIX G;
    VECTOR g;
    G = Abs(Id(RowDimension(R))-R*Ac)+Abs(R)*Delta;
    g = Abs(R*(Ac*x0-bc))+Abs(R)*(Delta*Abs(x0)+delta);
    VECTOR f(Dimension(g)),dl(Dimension(g)),d(Dimension(g));
    Initialize(dl,0);
    Initialize(f,optmiset.fRohn);
    int iter = 0;
    do{
        d = dl;
        dl = G*d+g+f;
        iter++;
    }while(Norm(dl-d) > Norm(f) && iter < optmiset.MaxIter);
    if(std::isinf(Norm(dl)) || std::isinf(Norm(d)))
        return 0;
    Xout = Hull(x0-d,x0+d);
    if(iter < optmiset.MaxIter)
        return 1;
    else
        return 0;
}
INT LinOpt::RohnOptimalLinSys( ){
    INTERVAL_VECTOR tmpX;
    Resize(Ac,RowDimension(A),ColDimension(A));
    INTERVAL_MATRIX Delta;
    Resize(bc,Dimension(B));
    VECTOR delta;
    mt19937_64 rng;
    rng.seed(random_device()());
    for(int k = 0;k <= optmiset.MaxIter;k++){
        if(k > 0){
            for(int i = 1;i <= RowDimension(A);i++){
                uniform_real_distribution<> distb(Inf(B(i)),Sup(B(i)));
                bc(i) = distb(rng);
                for(int j = 1;j <= ColDimension(A);j++){
                    uniform_real_distribution<> distA(Inf(A(i,j)),Sup(A(i,j)));
                    Ac(i,j) = distA(rng);
                }
            }
            if(RohnOverLinSys(tmpX) == 0){
                continue;
            }
            INTERVAL_VECTOR inter;
            if(Intersection(inter,X,tmpX) == 1){
                X = inter;
            }
        }else{
            Ac = Mid(A);
            bc = Mid(B);
            Delta = Sup(A)-Ac;
            delta = Sup(B)-bc;
            if(RohnOverLinSys(X) == 0){
                status = STATUS::SOLUTIONNOTFOUNDED;
                return 0;
            }
        }
    }
    INTERVAL_VECTOR r;
    INTERVAL rNorm;
    r = A*X-B;
    rNorm = Norm(r);
    if(X.hasInf()){
        status = STATUS::SOLUTIONNOTFOUNDED;
        return 0;
    }
    if(Diam(X).max() > optmiset.Eps || Sup(rNorm) > optmiset.Eps){
        MATRIX z,Delta,Amais,Amenos;
        z = ynset(A.cols());
        Ac = Mid(A);
        bc = Mid(B);
        Delta = Sup(A)-Ac;
        INTERVAL_VECTOR IVx;
        INT contsol = 0;
        for(int iz = 1;iz <= z.cols();iz++){
            MATRIX Tz;
            Tz = Diag(z.col(iz));
            Amais = Ac-Delta*Tz;
            Amenos = -(Ac+Delta*Tz);
            Oettli_Prager_Solvability(Amais,Amenos,IVx);
            if(status == STATUS::SOLUTIONFOUNDED)
                contsol++;
        }
        if(contsol == 0){
            status = STATUS::NOOPTIMAL;
        }else if(contsol < z.cols()){
            status = STATUS::WEAKSOLUTION;
            WeakX = X;
        }else{
            status = STATUS::STRONGSOLUTION;
        }
        INTERVAL_VECTOR inter;
        if(!IVx.empty())
            if(Intersection(inter,X,IVx) != 0)
                X = inter;
    }else{
        status = STATUS::STRONGSOLUTION;
    }
    return 1;
}
INT LinOpt::NonSquarePrecondMatrix(MATRIX& M){
    MATRIX Ac;
    Ac = Mid(A);
    INT n = RowDimension(Ac);
    INT m = ColDimension(Ac);
    M = Id(n);
    MATRIX Al = Ac;
    for (int i = 1; i < m; i++) {
        MATRIX tmpMCol;
        tmpMCol = Al.Box(i,Al.rows(),i,i);
        INT pivotID = (i-1)+tmpMCol.col(1).maxID();
        if(pivotID != i){
            VECTOR tmpRow;
            tmpRow = Al.row(i);
            SetRow(Al,i,Al.row(pivotID));
            SetRow(Al,pivotID,tmpRow);
            tmpRow.clear();
            tmpRow = M.row(i);
            SetRow(M,i,M.row(pivotID));
            SetRow(M,pivotID,tmpRow);
        }
        if(Al(i,i) != 0){
            VECTOR L1,L2;
            double pivot = 1/Al(i,i);
            for(int j=i+1;j<=n;j++)
            {
                L1 = pivot*Al(j,i)*Al.row(i)-Al.row(j);
                SetRow(Al,j,L1);
                L2 = pivot*Al(j,i)*M.row(i)-M.row(j);
                SetRow(M,j,L2);
            }
            L1 = pivot*Al.row(i);
            SetRow(Al,i,L1);
            L2 = pivot*M.row(i);
            SetRow(M,i,L2);
        }
    }
    for (int i = m; i > 1; i--) {
        if(Al(i,i) != 0){
            double pivot = 1/Al(i,i);
            for(int j=i-1;j>=1;j--)
            {
                VECTOR L1,L2;
                L1 = Al.row(j)-pivot*Al(j,i)*Al.row(i);
                SetRow(Al,j,L1);
                L2 = M.row(j)-pivot*Al(j,i)*M.row(i);
                SetRow(M,j,L2);
            }
        }
    }
    for(int i = m;i <= n;i++){
        if(A(i,m) != 0){
            VECTOR T;
            double pivot2 = 1/Al(i,m);
            T = pivot2*Al.row(i);
            SetRow(Al,i,T);
            T.clear();
            T = pivot2*M.row(i);
            SetRow(M,i,T);
        }
    }    
}
INT LinOpt::HansenWalsterOverLinSys( ){
    INT n = RowDimension(A);
    INT m = ColDimension(A);
    MATRIX Ac = Mid(A);
    MATRIX M;
    NonSquarePrecondMatrix(M);
    INTERVAL_MATRIX Al = M*A;
    INTERVAL_VECTOR Bl = M*B;
    INTERVAL_VECTOR Xl = X;
    A = Al;
    B = Bl;
    INTERVAL_MATRIX Ml = Hull(M);
    for (int i = 1; i <= m-1; i++) {
        INTERVAL pivot = 1/Al(i,i);
        if(0 <= pivot){
            continue;
        }
        for(int j=i+1;j<=n;j++)
        {
            INTERVAL_VECTOR L;
            L = pivot*Al(j,i)*Al.row(i)-Al.row(j);
            SetRow(Al,j,L);
            Bl(j) = pivot*Al(j,i)*Bl(i)-Bl(j);
        }
    }
    INTERVAL x;
    for(int i = n;i >= m;i--){
        x = Bl(i)/Al(i,m);
        if(std::isnan(x.sup()) || std::isnan(x.inf()))
            x = SymHull(Machine::PosInfinity);
        INTERVAL inter;
        if(!Xl.empty()){
            if(Intersection(inter,x,Xl(m)) != 0){
                Xl(m) = inter;
            }
        }else{
            Resize(Xl,m);
            Initialize(Xl,INTERVAL(Machine::NegInfinity,Machine::PosInfinity));
            Xl(m) = x;
        }
    }
    INTERVAL sum;
    for(int i = m-1;i >= 1;i--){
        sum = Bl(i)/Al(i,i);
        for(int j = m;j > i;j--){
            sum += Al(i,j)*Xl(j)/Al(i,i);
        }
        if(std::isnan(sum.inf()) || std::isnan(sum.sup()))
            sum = SymHull(Machine::PosInfinity);
        INTERVAL inter;
        if(Intersection(inter,sum,Xl(i)) != 0){
            Xl(i) = inter;
        }else{
            X.Delete();
            status = EMPTY;
            return 0;
        }
    }
    X = Xl;
}
INT LinOpt::Oettli_Prager_Solvability(const MATRIX& Amais,const MATRIX& Amenos,INTERVAL_VECTOR& IVx){
    try {
        IloEnv   env;
        IloNumVarArray x(env);
        IloRangeArray con(env);
        IloModel model(env);
        IloObjective obj = IloMinimize(env);
        for(int i = 1;i <= X.nrows();i++){
            x.add(IloNumVar(env, Inf(X(i)), Sup(X(i))));
            obj.setLinearCoef(x[i-1], 0.0);
        }
        int contRow = 1;
        for(int i = 1;i <= 2*Amais.rows();i+=2,contRow++){
            con.add(IloRange(env, -IloInfinity, Sup(B(contRow))));
            con.add(IloRange(env, -IloInfinity, -Inf(B(contRow))));
            for(int j = 1;j <= Amais.cols();j++){
                con[i-1].setLinearCoef(x[j-1], Amais(contRow,j));
                con[i].setLinearCoef(x[j-1], Amenos(contRow,j));
            }
        }
        model.add(obj);
        model.add(con);
        IloCplex cplex(model);
//        cplex.exportModel("lpex1.lp");

        // Optimize the problem and obtain solution.
        cplex.setOut(env.getNullStream());
        if ( !cplex.solve() ) {
            env.error() << "Failed to optimize LP" << '\r';
            env.end();
            throw(-1);
        }
        IloNumArray vals(env);
//        env.out() << "Solution status = " << cplex.getStatus() << endl;
//        env.out() << "Solution value  = " << cplex.getObjValue() << endl;
        cplex.getValues(vals, x);
        if(IVx.empty()){
            Resize(IVx,cdim);
            for(int i = 1;i <= vals.getSize();i++)
                IVx(i) = vals[i-1];
        }else{
            for(int i = 1;i <= vals.getSize();i++)
                IVx(i) = Hull(IVx(i),vals[i-1]);
        }
//        env.out() << "Values        = " << IVx << endl;
//        cplex.getSlacks(vals, con);
//        env.out() << "Slacks        = " << vals << endl;
//        cplex.getDuals(vals, con);
//        env.out() << "Duals         = " << vals << endl;
//        cplex.getReducedCosts(vals, x);
//        env.out() << "Reduced Costs = " << vals << endl;
        status = STATUS::SOLUTIONFOUNDED;
        env.end();
    }
    catch (IloException& e) {
        cerr << "Concert exception caught: " << e << endl;
    }
    catch (...) {
        cerr << "Problem is weakly unsolvable" << '\r';
        cerr.flush();
        status = STATUS::SOLUTIONNOTFOUNDED;
        return 0;
    }
    return 1;
}
/*
 Calcula o casco convexo de x do 
 conjunto de Ax=b,
 ou uma matriz singular S pertencente a A.
*/
STATUS LinOpt::intervalhull(MATRIX& S){
    MATRIX Ac,invAc;
    INT n = A.cols();
    Ac = Mid(A);
    invAc = Inverse(Ac);
    if(ErrorHandler::LastErrorCode != 0){
        S = Ac;
        return SINGULAR;
    }
    VECTOR xc,bc,d;
    bc = Mid(B);
    xc = invAc*bc;
    VECTOR z;
    z = sgn(xc);
    X = xc;
    vector<VECTOR> Z;
    Z.push_back(z);
    vector<VECTOR> D;
    d = Sup(B)-bc;
    while(!Z.empty()){
        z = Z[Z.size()-1];
        Z.pop_back();
        D.push_back(z);
        MATRIX Qz(A.rows(),A.rows());
        if(qzmatrix(z,S,Qz) == SINGULAR){
            X.Delete();
            return SINGULAR;
        }
        MATRIX Q_z(A.rows(),A.cols());
        if(qzmatrix(-z,S,Q_z) == SINGULAR){
            X.Delete();
            return SINGULAR;
        }
        VECTOR xz,x_z;
        xz = Qz*bc+Abs(Qz)*d;
        x_z = Q_z*bc-Abs(Q_z)*d;
        if(xz <= x_z){
            for(int i = 1;i <= xz.rows();i++){
                if(Inf(X(i))>x_z(i))
                    X(i).ival.inf = xz(i);
                if(Sup(X(i)) < xz(i))
                    X(i).ival.sup = xz(i);
            }
            for(int j = 1;j <= n;j++){
                VECTOR zl;
                zl = z;
                zl(j) = -zl(j);
                bool belongsZ = false,belongsD = false;
                for(int k = 0;k < Z.size();k++){
                    if(!(zl != Z[k])){
                        belongsZ = true;
                        break;
                    }
                    if(!(zl != D[k])){
                        belongsD = true;
                    }
                }
                if((xz(j)*x_z(j) <= 0) && !belongsZ && !belongsD){
                    Z.push_back(zl);
                } 
            }
        }
    }
    status = REGULAR;
    return REGULAR;
}
/*
 Calcula ou a solução Qz da equação QAc-|Q|DTz = I
 ou uma matriz singular S em A
*/
STATUS LinOpt::qzmatrix(const VECTOR& z, MATRIX& S, MATRIX& Qz){
    MATRIX Ac;
    Ac = Mid(A);
    MATRIX AcT,TzDT,Tz,D,e;
    e = Id(A.cols());
    Tz = Diag(z);
    AcT = Transpose(Ac);
    D = Sup(A)-Ac;
    TzDT = Tz*Transpose(D);
    for(int i = 1;i <= A.cols();i++){
        VECTOR x;
        if(absvaleqn(AcT,-TzDT,e.col(i),x,S) == SINGULAR){
            S = Transpose(S);
            if(!Qz.empty())
                Qz.Delete();
            return SINGULAR;
        }
        SetRow(Qz,i,x);
    }
    return REGULAR;
}
/*
 Determina ou a solução x para Ax + B|x|=b, ou
 uma matriz singular S que satisfaz |S-A|<=B
*/
STATUS LinOpt::absvaleqn(const MATRIX& Al, const MATRIX Bl, const VECTOR& b,VECTOR& x,MATRIX& S){
    INT i = 0;
    INT n = Al.cols();
    VECTOR r(n);
    Initialize(r,0);
    MATRIX Xl(n,n);
    Initialize(Xl,0);
    MATRIX invA;
    invA = Inverse(Al);
    if(ErrorHandler::LastErrorCode != 0){
        S = Al;
        return SINGULAR;
    }
    VECTOR z;
    z = sgn(invA*b);
    MATRIX Tz;
    Tz = Diag(z);
    S = Al+Bl*Tz;
    MATRIX invS;
    invS = Inverse(S);
    if(ErrorHandler::LastErrorCode != 0)
        return SINGULAR;
    S = invS;
    x = S*b;
    MATRIX C;
    C = -S*Bl;
    MATRIX e = Id(Al.cols());
    while(1){
        bool zjxjgz = false;
        INT k;
        for(INT j = 1;j <= x.rows();j++){
            if(z(j)*x(j) < 0){
                zjxjgz = true;
                k = j;
                break;
            }
        }
        if(!zjxjgz)break;
        i++;
        MATRIX ek(1,n);
        SetRow(ek,1,e.row(k));
        if(1+2*z(k)*C(k,k) <= 0){
            S = Al + Bl*(Tz+(1/C(k,k)*e.row(k)*ek));
            x.clear();
            return SINGULAR;
        }
        bool rkgreaterrj = false;
        for(int l = k;l <= r.rows();l++)
            if(r(k) > r(l))true;
        if(((k < n) && rkgreaterrj) || (k == n && r(n) > 0)){
            x = x - Xl.col(k);
            VECTOR y(Dimension(x));
            VECTOR Bx,Ax;
            Bx = Abs(Bl)*Abs(x);
            Ax = Al*x;
            for(int j = 1;j <= n;j++){
                if(Bx(j) > 0)
                    y(j) = Ax(j)/Bx(j);
                else
                    y(j) = 1;
            }
            z = sgn(x);
            MATRIX Ty;
            Ty = Diag(y);
            S = Al - Ty*Bl*Tz;
            x.clear();
            return SINGULAR;
        }
        r(k) = i;
        SetCol(Xl,k,x);
        z(k) = -z(k);
        REAL alpha = 2*z(k)/(1-2*z(k)*C(k,k));
        x = x + alpha*x(k)*C.col(k);
        MATRIX Ck(1,C.cols());
        SetRow(Ck,1,C.col(k));
        C = C + alpha*C.col(k)*Ck;
    }
    return REGULAR;
}

/* Funcao utilizada para eliminacao
 gaussiana*/
INT LinOpt::GaussElimination(INTERVAL_MATRIX& A_out, INTERVAL_VECTOR& B_out, INTERVAL_MATRIX& M){
    INTERVAL sum,U;
    int i,j,k;
    B_out=B;
    A_out=A;

//Gauss elimination
    for(k=1;k<=cdim-1;k++)
    {
        if((0.0 <= A_out(k,k))|| fabs(Sup(A_out(k,k)))<=Machine::MinPositive ||
                fabs(Inf(A_out(k,k)))<=Machine::MinPositive)
        {
            INTERVAL_VECTOR tmpRowA;
            INTERVAL tmpb;
            tmpRowA = Row(A_out,k);
            tmpb = B_out(k);
            INT l;
            for(l = k+1;l <= RowDimension(A_out);l++){
                if(!(0.0 <= A_out(l,k))){
                    SetRow(A_out,k,Row(A_out,l));
                    B_out(k) = B_out(l);
                    B_out(l) = tmpb;
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
            U=B_out(i);
            B_out(i)=U-A_out(i,k)*B_out(k)/A_out(k,k);
            
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
        sum=B_out(i);
        for(j=i+1;j<=cdim;j++) sum-=A_out(i,j)*B_out(j);
        B_out(i)=sum/A_out(i,i);
    }
    return 1;
}
