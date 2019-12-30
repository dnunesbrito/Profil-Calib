/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NonLinOpt.cpp
 * Author: darlan
 * 
 * Created on 7 de Novembro de 2016, 08:46
 */

#include <NonLinOpt/NonLinOpt.hpp>
#include <cmath>

extern struct  OPTMICALIBDATA optmicalibdata;

NonLinOpt::~NonLinOpt() {
}

vector<INTERVAL> NonLinOpt::IntervalNewtonMethod(INTERVAL& X0,REAL epsilon_f){
    vector<INTERVAL> L;
    L.push_back(X0);
    vector<INTERVAL> x_star;
    while(!L.empty()){
        INTERVAL IX;
        IX = L[L.size()-1];
        L.erase(L.end());
        while(1){
            INTERVAL_VECTOR xIV(1),XIV(1);
            INTERVAL fI;
            INTERVAL_VECTOR dotfI;
            INTERVAL fVal;
            REAL x = Mid(IX);
            xIV(1) = x;
            XIV(1) = IX;
            fI = Function(fcn,xIV,userdata);
            dotfI = Gradient(fcn,XIV,userdata);
            if(!x_star.empty())
                if(Abs(fVal) < Inf(fI))
                    break;
            if(0.0 <= dotfI(1)){
                if(0.0 <= fI){
                    status = NewtonStopCriteria(x,IX);
                    switch(status){
                        case 1:
                            break;
                        case 2:
                            L.push_back(INTERVAL(Inf(IX),Mid(IX)));
                            L.push_back(INTERVAL(Mid(IX),Sup(IX)));
                            break;
                        case 3:
                            x_star.push_back(IX);
                            break;
                    }
                }else{
                    REAL epsilon_X = Diam(IX)/Abs(IX);
                    if(epsilon_X < epsilon_f){
                        if(x_star.size() >= 1){
                            for(int i = 0;i < x_star.size();i++){
                                INTERVAL inter;
                                if(Intersection(inter,IX,x_star[i]) == 1){
                                    x_star[i] = inter;
                                }
                            }
                            break;
                        }
                        x_star.push_back(IX);
                        fVal = fI;
                        cout << "X=" << IX << '\r';
                        cout.flush();
                        break;
                    }
                }
            }
            if(status == 3)break;
            EINTERVAL tR;
            tR = NewtonStep(x,IX);
            if(tR.empty())
                break;
            if(tR.nINTERVAL == 2){
                L.push_back(tR(1));
                L.push_back(tR(2));
                break;
            }else{
                if(Diam(tR(1)) < Diam(IX)/2){
                    IX = tR(1);
                    continue;
                }else{
                    L.push_back(INTERVAL(Mid(IX),Sup(IX)));
                    IX = (INTERVAL(Inf(IX),Mid(IX)));
                    continue;
                }
            }
        }
    }
    return x_star;
}
vector<INTERVAL> NonLinOpt::IntervalNewtonMethod(INT XIdx,REAL epsilon_f){
    vector<INTERVAL> L;
    L.push_back(X(XIdx));
    vector<INTERVAL> x_star;
    status = STATUS::NLUNDEFINED;
    while(!L.empty()){
        X(XIdx) = L[L.size()-1];
        L.erase(L.end());
        while(1){
            INTERVAL_VECTOR xIV(X),XIV(X);
            INTERVAL fI;
            INTERVAL_VECTOR dotfI;
            INTERVAL fVal;
            REAL x = Mid(X(XIdx));
            xIV(XIdx) = x;
            fI = Function(fcn,xIV,userdata);
            dotfI = Gradient(fcn,XIV,userdata);
            if(!x_star.empty())
                if(Abs(fVal) < Inf(fI))
                    break;
            if(0.0 <= dotfI(XIdx)){
                if(0.0 <= fI){
                    status = NewtonStopCriteria(x,XIdx);
                    switch(status){
                        case INFERIOR_EXPANSION:
                            break;
                        case SUPERIOR_EXPANSION:
                            break;
                        case HALF_DIVIDE:
                            L.push_back(INTERVAL(Inf(X(XIdx)),Mid(X(XIdx))));
                            L.push_back(INTERVAL(Mid(X(XIdx)),Sup(X(XIdx))));
                            break;
                        case ACCEPT_X:
                            x_star.push_back(X(XIdx));
                            break;
                    }
                }else{
                    REAL epsilon_X = Diam(X(XIdx))/Abs(X(XIdx));
                    if(epsilon_X < epsilon_f){
                        if(x_star.size() >= 1){
                            for(int i = 0;i < x_star.size();i++){
                                INTERVAL inter;
                                if(Intersection(inter,X(XIdx),x_star[i]) == 1){
                                    x_star[i] = inter;
                                }
                            }
                            break;
                        }
                        x_star.push_back(X(XIdx));
                        fVal = fI;
                        break;
                    }
                }
            }
            if(status == ACCEPT_X)break;
            EINTERVAL tR;
            tR = NewtonStep(x,XIdx);
            if(tR.empty()){
                break;
            }
            if(tR.nINTERVAL == 2){
                L.push_back(tR(1));
                L.push_back(tR(2));
                break;
            }else{
                if(Diam(tR(1)) < Diam(X(XIdx))/2){
                    X(XIdx) = tR(1);
                    continue;
                }else{
                    L.push_back(INTERVAL(Mid(X(XIdx)),Sup(X(XIdx))));
                    X(XIdx) = (INTERVAL(Inf(X(XIdx)),Mid(X(XIdx))));
                    continue;
                }
            }
        }
    }
    return x_star;
}
NONLINSTATUS NonLinOpt::NewtonStopCriteria(REAL& x,INTERVAL& IX){
    INTERVAL Ix;
    INTERVAL_VECTOR a(1),b(1);
    INTERVAL_VECTOR x1(1),x2(1);
    a(1) = Inf(IX);
    b(1) = Sup(IX);
    Ix = Function(fcn,a,userdata);
    if(!(0.0 <= Ix)){
        x = Inf(IX);
        return INFERIOR_EXPANSION;
    }
    Ix = Function(fcn,b,userdata);
    if(!(0.0 <= Ix)){
        x = Sup(IX);
        return SUPERIOR_EXPANSION;
    }
    x1(1) = (1.0/4.0)*(3*a(1) + b(1));
    Ix = Function(fcn,x1,userdata);
    if(!(0.0 <= Ix))
        return HALF_DIVIDE;
    x2(1) = (1.0/4.0)*(a(1) + 3*b(1));
    Ix = Function(fcn,x2,userdata);
    if(!(0.0 <= Ix))
        return HALF_DIVIDE;
    return ACCEPT_X;
}
NONLINSTATUS NonLinOpt::NewtonStopCriteria(REAL& x,INT XIdx){
    INTERVAL Ix;
    INTERVAL_VECTOR a(X),b(X);
    INTERVAL_VECTOR x1(X),x2(X);
    a(XIdx) = Inf(X(XIdx));
    b(XIdx) = Sup(X(XIdx));
    if(useidxtofcn){
        INTERVAL_VECTOR tmpfI;
        tmpfI = VectorFunction(fcn,a,userdata);
        Ix = tmpfI(XIdx);
    }else{
        Ix = Function(fcn,a,userdata);
    }
    if(!(0.0 <= Ix)){
        x = Inf(X(XIdx));
        return INFERIOR_EXPANSION;
    }
    if(useidxtofcn){
        INTERVAL_VECTOR tmpfI;
        tmpfI = VectorFunction(fcn,b,userdata);
        Ix = tmpfI(XIdx);
    }else{
        Ix = Function(fcn,b,userdata);
    }
    if(!(0.0 <= Ix)){
        x = Sup(X(XIdx));
        return SUPERIOR_EXPANSION;
    }
    x1(XIdx) = (1.0/4.0)*(3*a(XIdx) + b(XIdx));
    if(useidxtofcn){
        INTERVAL_VECTOR tmpfI;
        tmpfI = VectorFunction(fcn,x1,userdata);
        Ix = tmpfI(XIdx);
    }else{
        Ix = Function(fcn,x1,userdata);
    }
    if(!(0.0 <= Ix))
        return HALF_DIVIDE;
    x2(XIdx) = (1.0/4.0)*(a(XIdx) + 3*b(XIdx));
    if(useidxtofcn){
        INTERVAL_VECTOR tmpfI;
        tmpfI = VectorFunction(fcn,x2,userdata);
        Ix = tmpfI(XIdx);
    }else{
        Ix = Function(fcn,x2,userdata);
    }
    if(!(0.0 <= Ix))
        return HALF_DIVIDE;
    return ACCEPT_X;
}
EINTERVAL NonLinOpt::NewtonStep(REAL x,INTERVAL IX,INT fIdx){
    INTERVAL_VECTOR grd;
    EINTERVAL NxX;
    INTERVAL_VECTOR xIV(1),XIV(1);
    xIV(1) = x;
    XIV(1) = IX;
    grd = Gradient(fcn,XIV,userdata);
    EINTERVAL fI,dotfI,tR;
    fI = Function(fcn,xIV,userdata);
    dotfI = grd(1);
    NxX = x-fI/dotfI;
    if(EIntervalIntersection(tR,NxX,IX) == 0)
        return tR;
    return tR;
}
EINTERVAL NonLinOpt::NewtonStep(REAL x,INT XIdx,INT fIdx){
    INTERVAL_VECTOR grd;
    EINTERVAL NxX;
    INTERVAL_VECTOR xIV(X),XIV(X);
    xIV(XIdx) = x;
    EINTERVAL fI,dotfI,tR;
    if(useidxtofcn){
        INTERVAL_VECTOR tmpfI;
        if(useBtofcn){
            grd = Gradient(fcn,XIV,XIdx,userdata,B);
            tmpfI = VectorFunction(fcn,xIV,userdata,B);
        }else{
            grd = Gradient(fcn,XIV,XIdx,userdata);
            tmpfI = VectorFunction(fcn,xIV,userdata);            
        }
        fI = tmpfI(fIdx);
    }else{
        grd = Gradient(fcn,XIV,userdata);
        fI = Function(fcn,xIV,userdata);
        fIdx = XIdx;
    }
    dotfI = grd(fIdx);
    NxX = x-fI/dotfI;
    EINTERVAL EX(X(XIdx));
    if(EX <= NxX){
        status = ALLXCONTAINED;
        tR = EX;
    }else{
        status = REDUCED;
        if(EIntervalIntersection(tR,NxX,X(XIdx)) == 0)
            status = EMPTY;
    }
    return tR;
}
INT NonLinOpt::ExpansionStep(INTERVAL& IX){
    int Fa = 0,Fb = 0;
    INTERVAL_VECTOR a(1),b(1);
    INTERVAL Ix;
    INTERVAL tilde_x(NAN,NAN);
    for(int n = 0;n < 4;n++){
        EINTERVAL tR;
        if(Fa != 1){
            a(1) = Inf(IX);
            Ix = Function(fcn,a,userdata);
            EINTERVAL tR;
            if(!(0.0 <= Ix)){
                tR = NewtonStep(Inf(IX),IX);
                if(tR.empty())return 0;
            }else{
                if(std::isnan(Inf(tilde_x)))
                    tilde_x = a(1);
                Fa = 1;
            }
        }
        if(Fb != 1){
            b(1) = Inf(IX);
            Ix = Function(fcn,b,userdata);
            if(!(0.0 <= Ix)){
                if(!std::isnan(Inf(tilde_x))){
                    tR = NewtonStep(Inf(IX),IX);
                }else{
                    tR = NewtonStep(Mid(IX),IX);
                }
                if(tR.empty()){
                    return 0;
                }
            }else{
                if(std::isnan(Inf(tilde_x)))
                    tilde_x = a(1);
                Fb = 1;
            }
        }
        if(Fa == 1 && Fb == 1)
            return 1;
        tR = NewtonStep(Mid(IX),IX);
        if(tR.empty())return 0;
    }    
}
EINTERVAL_VECTOR NonLinOpt::Ycalc(){
    //assert(!fcn.isNULL());
    INTERVAL f_x;
    f_x = Function(fcn,Mid(X),userdata);
    VECTOR x = Mid(X);
    INTERVAL Sum(0,0);
    INTERVAL_VECTOR grd(X.rows()),grdI(X.rows());
    INTERVAL U;
    EINTERVAL T,tR;
    INTERVAL_VECTOR Y(X);
    EINTERVAL_VECTOR EIY(X.rows());
    for(int j = 1;j <= Y.rows();j++){
        INTERVAL_VECTOR yj(Y);
        for(int k = j;k <= yj.rows();k++)
            yj(k) = Mid(Y(k));
        grd = Gradient(fcn,yj,userdata);
        grdI = Gradient(fcn,Y,userdata);
        for(int i = 1;i <= Y.rows();i++){
            if(i == j)continue;
            Sum += (Y(i)-x(i))*grd(i);
        }
        U = f_x + Sum - UpperBound;
        T = EINTERVAL(Machine::NegInfinity,U.inf())/grdI(j);
        tR = T+x(j);
        if(EIntervalIntersection(tR,tR,X(j)) == 1){
            Y(j) = INTERVAL(tR.inf(),tR.sup());
            EIY(j) = tR;
        }else{
            EIY.clear();
            return EIY;
        }
    }
    return EIY;
}
enum CONSISTENCY{HC,BC}consistency;
/*
 * HCf = 0
 * HCgrd = 0
 * atualizaX = verdadeiro
 * Enquanto a lista L1 não estiver vazia faça
 *      Se atualizaX então
 *          X = o vetor da lista L1 que produziu o menor valor inferior da função
 *          Dele X da lista
 *          atualizaX = falso
 *          HCf = 0
 *          HCgrd = 0
 *      fim se
 *      Se HCf <= n então
 *          Aplique consistência para f(x) = f_bar
 *          Se X for vazio então
 *              autalizaX = verdadeiro
 *              continue
 *          fim se
 *          Se passo6 for verdadeiro então
 *              Coloque X na lista final L2;
 *              atualizaX = verdadeiro
 *              continue
 *          fim se
 *          Se a caixa foi suficientemente reduzida então
 *              Coloque X na lista L1
 *              atualizaX = verdadeiro
 *              Continue
 *          fim se
 *      fim se
 *      Se HCgrd <= n então
 *          HCf = 1;
 *          Aplique consistência para o gradiente
 *          Incrementa HCgrd
 *          Se X é vazio então
 *              atualizaX = verdadeiro
 *              continue
 *          fim se
 *          Faça uma busca linear em gI(x);
 *          Se f_bar reduziu então
 *              Incrementa HCf
 *              Aplique a consistencia para a função
 *          fim se 
 *          Aplique o método linear para f(xI) <= f_bar
 *          Se X é vazio então
 *              atualizaX = verdadeiro
 *              continue
 *          fim se
 *          Se passo6 for verdadeiro então 
 *              atualizaX = verdadeiro
 *              continue
 *          fim se
 *          Se passo13 for verdadeiro então 
 *              atualizaX = verdadeiro
 *              continue
 *          fim se
 *          Se w(X) < wH então
 *              atualizaX = falso
 *              consistência = BC
 *              HCf = 1
 *              HCgrd = 1
 *              continue
 *          fim se             
 *          Aplique a consistência para Hii >= 0
 *          Se o resultado for vazio então continue
 *          Se Hii < 0 para algum i faça
 *              Se passo6 for verdadeiro então 
 *                  atualizaX = verdadeiro
 *                  continue
 *              fim se
 *              Se passo13 for verdadeiro então 
 *                  atualizaX = verdadeiro
 *                  continue
 *              fim se
 *              atualizaX = falso
 *              consistência = BC
 *              continue
 *          fim se
 *          Atualiza wH
 *      senão
 *          passo20 = verdadeiro
 *      fim se
 *      Se w(X) < (wR + wI)/2 ou passo20 então
 *          faça
 *              Calcule o Jacobiano do gradiente
 *              Se a diagonal de JxxI é estritamente negativa então
 *                  atualizaX = verdadeiro
 *                  passo3 = verdadeiro
 *                  pare
 *              fim se
 *              Delete qualquer parte negative de JxxI
 *              B = JxxI^-1
 *              MxxI = B*JxxI
 *              Se MxxI é regular então
 *                  Determine a solução do sistema linear g(x) - MxxI(y - x) = 0
 *              senão
 *                  Aplique uma passada do método de Gauss-Seidel
 *              fim se
 *              Atualize wI e wR
 *              Se o resultado for vazio então
 *                  atualizaX = verdadeiro
 *                  passo3 = verdadeiro
 *                  pare
 *              fim se
 *              Se o método intervalar de newton provou a existencia da solução então
 *                  SolucaoExiste = verdadeiro
 *              fim se
 *              HCgrd = 1
 *              Se passo6 for verdadeiro então 
 *                  atualizaX = verdadeiro
 *                  passo3 = verdadeiro
 *                  pare
 *              fim se
 *          enquanto a largura da caixa teve redução menor que 8 continue
 *          Se passo3 for verdadeiro então
 *              passo3 = falso
 *              continue
 *          fim se
 *          Se passo13 for verdadeiro então 
 *              atualizaX = verdadeiro
 *              continue
 *          fim se
 *          Cacule o valor y = x - Bg(x)
 *          Use o valor de f(y) para atualizar f_bar
 *          Use um método quadrático para resolver f(x) menor ou igual a f_bar
 *          Se passo6 for verdadeiro então 
 *              atualizaX = verdadeiro
 *              continue
 *          fim se
 *          Se passo13 for verdadeiro então 
 *              atualizaX = verdadeiro
 *              continue
 *          fim se
 *          Determine analiticamente Bg(X)
 *          Aplique a consistência de casco para Bg(X)
 *          Se o método de consistência provou a existencia da solução então
 *              SolucaoExiste = verdadeiro
 *          fim se
 *          Se passo6 for verdadeiro então 
 *              atualizaX = verdadeiro
 *              continue
 *          fim se
 *          Se passo13 for verdadeiro então 
 *              atualizaX = verdadeiro
 *              continue
 *          fim se
 *          Aplique a consistência de casco para Bg(X)
 *      fim se
 *      Se passo6 for verdadeiro então 
 *          atualizaX = verdadeiro
 *          continue
 *      fim se
 *      Junte todos os intervalos em apenas 1
 *      Divida a caixa X
 *      Avalie f no centro de cada nova caixa
 *      Atualize o limite superior
 *      atualizaX = verdadeiro
 * fim enquanto
 * Delete todas as caixas da lista L2 que o limite inferior é maior do f_bar
 * Função passo6 (lista)
 *      Se w(X) < E_x e w(f(xI)) < E_f então
 *          retorna verdadeiro
 *      senão
 *          retorne falso
 * fim passo6
 * Funçao passo13 (lista)
 *      Se a caixa foi suficientemente reduzida então
 *          Coloque X na lista L1
 *          retorne verdadeiro
 *      senão
 *          retorne falso
 *      fim se
 * fim passo13
 */
bool NonLinOpt::passo6(vector<INTERVAL_VECTOR>& L){
    REAL wX = X.diam().max();
    INTERVAL wf;
    wf = Function(fcn,X,userdata);
    if(wX < epsilon_X && wf.diam() < epsilon_f){
        L.push_back(X);
        return true;
    }
    return false;
}
bool NonLinOpt::passo13(vector<INTERVAL_VECTOR>& L){
    REAL D = 0.25*wR-(wII-wR);
    if(D <= 0){
        L.push_back(X);
        return true;
    }
    return false;
}
INT NonLinOpt::GlobalOptimization(vector<INTERVAL_VECTOR>& L1){
    assert(!L1.empty());
    EINTERVAL_VECTOR Xl,grd;
    EINTERVAL_MATRIX Hess;
    vector<INTERVAL_VECTOR> L2,L3;
    cdim_f = L1[0].rows();
    INTERVAL f_bar;
    EINTERVAL f,Minf;
    INTERVAL_VECTOR smallX,medXvec;
    REAL smallXsup = Machine::PosInfinity;
    REAL smallXinf = Machine::PosInfinity;
    REAL medX = Machine::PosInfinity;
    /********* Inicializações ***********/
    wI = L1[0].diam().max();
    wR = 0;
    wH = Machine::PosInfinity;
    /***********************************/
    /********** Passo 1 ****************/
//    vector<INTERVAL_VECTOR>::iterator it;
//    for(it = L1.begin();
//        it != L1.end();){
//        EINTERVAL_VECTOR midvec(Hull(Mid(*it)));
//        f = Function(fcn,midvec,userdata);
////        if(f.hasNaN())return -1;
////        if(f.inf() < UpperBound)
////            UpperBound = f.inf();
//    /***********************************/
//    /********** Passo 2 ***/
//        Xl = (*it);
//        f = Function(fcn,Xl,userdata);
//        if(f.inf() > UpperBound){
//            it = L1.erase(it);
//            continue;
//        }
//        it++;
//        if((*it).diam().max() > wI)
//            wI = (*it).diam().max();
//    }
    /************************************/
    std::vector<INTERVAL_VECTOR> XlParse;
    bool atualizaX = true;
    INT HCf = 0;
    INT HCgrd = 0;
    INT contBranches;
    EINTERVAL_VECTOR EX;
    bool gradientpass;
    bool bar = true;
    bool star =true;
    int iter = 1;
    bool menormax,menormed;
    for(int iter1 = 0;iter1 <= optmiset.MaxIterNonlin && !L1.empty();iter1++){
        bool passo3 = true;
        contBranches = 0;
        menormax = false;
        menormed = false;
        for(;(passo3 == true) && iter <= optmiset.MaxIterInnerLoop;iter++){
//            if(star)
//                cout << " + iter1 = " << iter1 << '\r';
//            else
//                cout << " * iter1 = " << iter1 << '\r';
//            cout.flush();
//            star = !star;
            if(UpperBound < epsilon_f)
                break;
            vector<INTERVAL_VECTOR>::iterator it,itsmall;
            bool stopactual = false;
            /************ Passo 3 ******************/
            if(atualizaX){
                gradientpass = false;
                LowerBound = 0;
//                cout << endl << "************ Eliminação *************" << endl;
                REAL MinVal = Machine::PosInfinity;
                for(it = L1.begin();it != L1.end();){
                    if((*it).nrows() == cdim_f){
                        EX = (*it);
                        f = Function(fcn,EX,userdata);
                        if(!f.hasNaN()){
                            if(f.inf() > UpperBound){
                                it = L1.erase(it);
                                stopactual = true;
                                continue;
                            }
                        }
                        INTERVAL_VECTOR tmpX(EX.rows()+1);
                        for(int i = 1;i <= tmpX.nrows()-1;i++)
                            tmpX(i) = (*it)(i);
                        tmpX(tmpX.nrows()) = f(1);
                        (*it).clear();
                        (*it) = tmpX;
                    }else{
                        f = (*it)(cdim_f+1);
                    }
                    if(Inf(f(1)) <= MinVal){
                        X = (*it).Box(1,cdim_f);
                        itsmall = it;
                        MinVal = Inf(f(1));
                        Minf = f;
                    }
                    it++;
                    stopactual = false;
                }
                f = Minf;
                if(stopactual)continue;
                if(L1.empty())
                    break;
                L1.erase(itsmall);
                double diffXinf,diffXsup;
                diffXinf = smallXinf - Inf(f(1));
                diffXsup = smallXsup - Sup(f(1));
                if(diffXinf  >= epsilon_f || iter == 1){
                    if(Abs(diffXinf) > epsilon_f || iter == 1){
                        smallX = X;
                        smallXinf = Inf(f(1));
                        smallXsup = Sup(f(1));
                        if(showfx){
                            cout << " *****  Menor X *****" << endl;
                            cout << "X=" << X;
                            EX = X;
                            cout << "  f = " << Sqrt(Function(fcn,EX,userdata))/DimensionData << endl;
                        }
                        menormax = true;
                        if(UpperBound > smallXsup)
                            UpperBound = smallXsup;
                        contBranches = 0;
                    }else{
                        if(diffXsup >= epsilon_f){
                            smallX = X;
                            smallXinf = Inf(f(1));
                            smallXsup = Sup(f(1));
                            if(showfx){
                                cout << " *****  Menor X *****" << endl;
                                cout << "X=" << X;
                                EX = X;
                                cout << "  f = " << Sqrt(Function(fcn,EX,userdata))/DimensionData << endl;
                            }
                                menormax = true;
                            if(UpperBound > smallXsup)
                                UpperBound = smallXsup;
                            contBranches = 0;                        
                        }
                    }
                }else{
                    if(Abs(diffXinf) < epsilon_f){
                        if(diffXsup >= epsilon_f){
                            smallX = X;
                            smallXinf = Inf(f(1));
                            smallXsup = Sup(f(1));
                            if(showfx){
                                cout << " *****  Menor X *****" << endl;
                                cout << "X=" << X;
                                EX = X;
                                cout << "  f = " << Sqrt(Function(fcn,EX,userdata))/DimensionData << endl;
                            }
                            menormax = true;
                            if(UpperBound > smallXsup)
                                UpperBound = smallXsup;
                            contBranches = 0;
                        }
                    }            
                }
                diffXinf = medX - Mid(f(1));
                if(diffXinf  >= epsilon_f || iter == 1){
                    medXvec = X;
                    medX = Mid(f(1));
                    if(showfx){
                        cout << " *****  Menor X médio *****" << endl;
                        cout << "X=" << X;
                        EX = X;
                        cout << "  f = " << Sqrt(Function(fcn,EX,userdata))/DimensionData << endl;
                    }
                    menormed = true;
                }
                HCf = 0;
                HCgrd = 0;
                consistency = HC;
                if(f.sup() == Machine::PosInfinity && f.inf() <= UpperBound){
                    if(EX.maxdiam() < epsilon_f){
                        atualizaX = true;
                        continue;
                    }
                    SplittingaBox(L1);
                    passo3 = true;
                    continue;
                }
            }
//            if(bar)
//                cout << " |  " << '\r';
//            else
//                cout << " -- " << '\r';
//            cout.flush();
//            bar = !bar;
            if(contBranches >= optmiset.MaxBranches){
                cout << "MaxBranches reached" << " - Iterations: " << iter1 << endl;
                break;
            }else{
                contBranches++;
            }
            if(showfx){
                cout << "X=" << X;
                EX = X;
                cout << "  f = " << Sqrt(Function(fcn,EX,userdata))/DimensionData << endl;
            }
            wI = X.diam().max();
            /****************************************/
            f_bar = INTERVAL(LowerBound,UpperBound);
            XlParse.clear();
            wII = X.diam().max();
            VECTOR wb = X.diam();
            /********Passo 5 *************************/
            if(HCf < cdim_f){
                if(consistency == HC){
                    Xl = X;
                    f = Function_HC(fcn,f_bar,Xl,userdata);
                    if(Xl.empty()){
                        atualizaX = true;
                        passo3 = false;
                        continue;
                    }
                    Parse(XlParse,Xl);
                    X = XlParse[0];
                    std::copy(XlParse.begin()+1,XlParse.end(),L1.end());
                }else{
                    Xl = X;
                    INTERVAL_VECTOR tmpX = X;
                    for(int i = 1;i <= cdim_f;i++){
                        EINTERVAL Xi;
                        useidxtofcn = false;
                        useBtofcn = false;
                        Xi = BoxConsistency(Mid(X(i)),i);
                        if(status == EXPANDED){
                            Xl(i) = Xi;
                        }else if(status == NOTEXPANDED){
                            Xl(i) =tmpX(i);
                        }else if(status == ALLXDELETED && !gradientpass){
                            atualizaX = true;
                            passo3 = false;
                            cout << "Box consistency retornou vaizo" << endl;
                            break;
                        }
                        if(!Xl.empty())
                            X = Xl.getIV(1);
                    }
                    if(status == ALLXDELETED && !gradientpass){
                        continue;
                    }
                    Parse(XlParse,Xl);
                    X = XlParse[0];
                    std::copy(XlParse.begin()+1,XlParse.end(),L1.end());
                }
                HCf++;
                /*****************************************/          
                /********* Passo 6 ***********************/
                if(passo6(L2)){
                    atualizaX = true;
                    passo3 = false;
                    continue;
                }
                /****************************************/
                /********** Passo 7 **********************/
                wR = X.diam().max();
                VECTOR wa = X.diam();
                VECTOR diffw = wb-wa;
                REAL D = 0.25*wR-(diffw.max());
                if(D <= 0){
                    L1.push_back(X);
                    passo3 == true;
                    atualizaX = true;
                    continue;
                }
                /*****************************************/
            }
            bool passo20 = false;
            if(HCgrd < cdim_f){ 
                HCf = 0;
                Xl = X;
                /******** Passo 9 ********************/
                bool stop = false;
                f_bar = 0.0;
                for(int var = 1;var <= X.nrows();var++){
                    grd = Gradient_HC(fcn,f_bar,Xl,var,userdata);
                    if(Xl.empty()){
                        X.Delete();
                        atualizaX = true;
                        passo3 = false;
                        stop = true;
                        break;
                    }else{
                        stop = false;
                    }
                }
                f_bar = INTERVAL(LowerBound,UpperBound);
                if(stop)
                    continue;
                gradientpass = true;
                Parse(XlParse,Xl);
                X = XlParse[0];
                std::copy(XlParse.begin()+1,XlParse.end(),L1.end());
                HCgrd++;
                /**************************************/
                if(consistency == HC){
                    /******** Passo 10 ********************/
                    status = UpdateUpperBound(true);
                    if(status == REDUCED){
                        passo3 == true;
                        atualizaX = false;
                        continue;
                    }
                    /*************************************/
                    /************* Passo 11 **************/
                    EINTERVAL_VECTOR Y = Ycalc();
                    if(Y.empty() && !gradientpass){
                        X.clear();
                        atualizaX = true;
                        passo3 = false;
                        continue;
                    }
                    if(!Y.empty()){
                        Parse(XlParse,Y);
                        X = XlParse[0];
                        std::copy(XlParse.begin()+1,XlParse.end(),L1.end());
                    }
                    /*************************************/
                    /************* Passo 12 **************/
                    if(passo6(L2)){
                        atualizaX = true;
                        passo3 = false;
                        continue;
                    }
                    /*************************************/
                    /************ Passo 13 ***************/
                    if(passo13(L1) == true){
                        atualizaX = true;
                        passo3 = true;
                        continue;
                    }
                    /*************************************/
                    /************ Passo 14 ***************/
                    wR = X.diam().max();
                    if(wR < wH && consistency == CONSISTENCY::HC){
                        /******** Passo 18 ***************/
                        atualizaX = false;
                        consistency = CONSISTENCY::BC;
                        continue;
                        /*********************************/
                    }
                    /*********************/
                }
                passo20 = true;
            }else{
                passo20 = false;
            }
            if(passo20){
                /*** Passo 15 ********/
                Xl = X;
                f_bar = INTERVAL(0,Machine::PosInfinity);
                for(int var = 1;var <= X.nrows();var++){
                    Hess = Hessian_HC(fcn,f_bar,Xl,var,userdata);
                    if(Xl.empty()){
                        atualizaX = true;
                        passo3 = false;
                        break;
                    }
                }
                f_bar = INTERVAL(LowerBound,UpperBound);
                if(atualizaX && !passo3)
                    continue;
                Parse(XlParse,Xl);
                X = XlParse[0];
                std::copy(XlParse.begin()+1,XlParse.end(),L1.end());
                INTERVAL_MATRIX H;
                H = Hessian(fcn,X,1,userdata);
                INTERVAL_VECTOR Hdiag;
                Hdiag = H.diag();
                if(Hdiag.min() < 0){
                    /************* Passo 16 **************/
                    if(passo6(L2)){
                        atualizaX = true;
                        passo3 = false;
                        continue;
                    }
                    /*************************************/
                    /************ Passo 17 ***************/
                    if(passo13(L1) == true){
                        atualizaX = true;
                        passo3 = false;
                        continue;
                    }
                    /*************************************/
                    /************ Passo 18 ***************/
                    atualizaX = false;
                    consistency = CONSISTENCY::BC;
                    continue;
                    /*************************************/
                }
                wR = X.diam().max();
                if(wH == Machine::PosInfinity)
                    wH = wR;
                else
                    if(wR > wH)wH = wR;
                /**********************/
            }
            REAL wxI = X.diam().max();
            REAL wxIafter;
            if(wxI < (wI + wR)/2){
                if(passo20){
                    INTERVAL_VECTOR grd;
                    passo3 = false;
                    int iter = 0;
                    do{
                        /************ Passo 20 e 21 *********/
                        status = onepassNewtonstep(true,Hull(Mid(X)));
                        if(status == STRICTILYNEGATIVE){
                            atualizaX = false;
                            passo3 = true;
                            break;
                        }
                        if(status == REDUCED){
                            wxIafter = X.diam().max();
                            if(wxI >= 8*wxIafter)passo20 = true;
                            else passo20 = false;
                        }
                        if(status == UNLIMITED)
                            passo20 = false;
                        HCgrd = 0;
                        /*************************************/
                        /************* Passo 22 **************/
                        if(passo6(L2)){
                            atualizaX = true;
                            passo3 = true;
                            break;
                        }
                        /*************************************/
                        iter++;
                    }while(passo20 && iter < 100000);
                    passo20 = false;
                    if(passo3){
                        continue;
                    }
                    /************ Passo 24 ***************/
                    if(passo13(L2) == true){
                        atualizaX = true;
                        continue;
                    }
                    /*************************************/
                    /*********** Passo 25 *******/
                    INTERVAL_VECTOR y;
                    grd = Gradient(fcn,X,userdata);
                    y = Mid(X)-B*Mid(grd);
                    f = Function(fcn,y,userdata);
                    /************************/
                    /*********** Passo 26 ****************/
                    UpdateUpperBound(false);
                    /*************************************/
                    /************* Passo 27 **************/
                    if(passo6(L2)){
                        atualizaX = true;
                        passo3 = true;
                        continue;
                    }
                    /*************************************/
                    /************ Passo 28 ***************/
                    if(passo13(L1) == true){
                        atualizaX = true;
                        passo3 = false;
                        continue;
                    }
                    /*************************************/
                    /************ Passo 29 ***************/
                    bool stop = false;
                    f_bar = INTERVAL(LowerBound,UpperBound);
                    Xl = X;
                    for(int var = 1;var <= X.nrows();var++){
                        BFunction_HC(fcn,f_bar,Xl,var,userdata,B);;
                        if(Xl.empty()){
                            X.Delete();
                            atualizaX = true;
                            passo3 = false;
                            stop = true;
                            cout << "B*Gradiente retornou vaizo" << endl;
                            break;
                        }else{
                            stop = false;;
                        }
                    }
                if(stop)
                    continue;
                    /*************************************/
                    /************* Passo 30 **************/
                    if(passo6(L2)){
                        atualizaX = true;
                        passo3 = true;
                        continue;
                    }
                    /*************************************/
                    /************ Passo 31 ***************/
                    if(passo13(L1) == true){
                        atualizaX = true;
                        passo3 = false;
                        continue;
                    }
                    /*************************************/
                    /************ Passo 32 ***************/
                    INTERVAL_VECTOR tmpX = X;
                    for(int i = 1;i <= cdim_f;i++){
                        useidxtofcn = true;
                        useBtofcn = true;
                        EINTERVAL Xi;
                        Xi = BoxConsistency(Mid(X(i)),i,i);
                        if(status == EXPANDED){
                            Xl(i) = Xi;
                        }else if(status == NOTEXPANDED){
                            Xl(i) =tmpX(i);
                        }else if(status == ALLXDELETED && !gradientpass){
                            atualizaX = true;
                            passo3 = false;
                            cout << "Box consistency retornou vaizo" << endl;
                            break;
                        }
                        if(!Xl.empty())
                            X = Xl.getIV(1);
                    }
                    Parse(XlParse,Xl);
                    X = XlParse[0];
                    std::copy(XlParse.begin()+1,XlParse.end(),L1.end());
//                    userdata.reset();
                    /*************************************/
                }
            }
            /************* Passo 33 **************/
            if(passo6(L2)){
                atualizaX = true;
                passo3 = false;
                continue;
            }
            /*************************************/
            /************ Passo 35 ***************/
    //        cout << endl << "************ Antes da divisão *************" << endl;
    //        cout << "X=" << X << endl;
    //        cout << "f=" << Function(fcn,X,NULL) << endl;
    //        INT tam1 = L1.size();
            SplittingaBox(L1);
//            cout << "************* Depois da divisão **************" << endl;
//            for(std::vector<INTERVAL_VECTOR>::iterator it = L1.begin();
//                    it != L1.end();it++){
//                cout << "X=" << (*it) << " -> ";
//                EX = (*it);
//                cout << "f_val=" << Function(fcn,EX,userdata) << endl;
//            }
            atualizaX = true;
        }
        if(iter >= optmiset.MaxIterInnerLoop)
            cout << "MaxIter reached" << endl;
        iter = 2;
        if(!menormax && !menormed)continue;
        L3.clear();
        if(L2.empty()){
            L3.push_back(smallX);
            L3.push_back(medXvec);
        }else{
            if(L2.size() > 1){
                for(vector<INTERVAL_VECTOR>::iterator it = L2.begin();it != L2.end();){
                    Xl = (*it);
                    f = Function(fcn,Xl,userdata);
                    for(int i = 1;i <= f.size();i++){
                        if(f(i).inf() > UpperBound)
                            f.erase(i);
                        if(!f.empty())
                            if(f(i).inf() < LowerBound)
                                LowerBound = f(i).inf();
                    }
                    if(f.empty())
                        it = L2.erase(it);
                    else
                        it++;
                }
            }
            copy(L2.begin(), L2.end(), back_inserter(L3));
        }
        L2.clear();
    }
    L1.clear();
    L1 = L3;
}
EINTERVAL NonLinOpt::BoxConsistency(REAL ExpPt,INT XIdx,INT fIdx){
    REAL w0;
    REAL a = Inf(X(XIdx));
    REAL b = Sup(X(XIdx));
    INTERVAL fI;
    INTERVAL_VECTOR IVfI;
    INTERVAL_VECTOR Xl(X);
    REAL Limits[2];
    Limits[0] = a;
    Limits[1] = b;
    EINTERVAL tR(0,0,0,0);
    for(int lim = 0;lim < 2;lim++){
        do{
            Xl(XIdx) = Limits[lim];
            EINTERVAL EfI;
            EINTERVAL_VECTOR EX(Xl);
            REAL beta = 1.0/4.0;
            w0 = b - a;
            while(1){
                if(useidxtofcn){
                    if(useBtofcn)
                        IVfI = VectorFunction(fcn,Xl,userdata,B);
                    else
                        IVfI = VectorFunction(fcn,Xl,userdata);
                    fI = IVfI(fIdx);
                }else{
                    if(useBtofcn){
                        IVfI = VectorFunction(fcn,Xl,userdata,B);
                        fI = IVfI(fIdx);
                    }else{
                        EfI = Function(fcn,EX,userdata);
                        fI = EfI(1);
                    }
                }
                if(0.0 <= fI){
                    status = NOTEXPANDED;
                    return INTERVAL(Machine::NaN,Machine::NaN);
                }
                REAL w = b - a;
                INTERVAL Y;
                REAL c;
                EINTERVAL Yl;
                if(lim == 0){
                    c = a + beta*w;
                    Y = INTERVAL(a,c);
                    //INTERVAL_VECTOR tmpX(X);
                    X(XIdx) = Y;
                    Yl = NewtonStep(a,XIdx,fIdx);
                    //X = tmpX;
                }else if(lim == 1){
                    c = b - beta*w;
                    Y = INTERVAL(c,b);
                    //INTERVAL_VECTOR tmpX(X);
                    X(XIdx) = Y;
                    Yl = NewtonStep(b,XIdx,fIdx);
                    //X = tmpX;
                }
                if(Yl.empty()){
                    if(beta == 1){
                        status = ALLXDELETED;
                        return EINTERVAL(Machine::NaN,Machine::NaN);
                    }else if(beta < 1){
                        if(lim == 0){
                            a = c;
                            beta = 2*beta;
                            Limits[lim] = a;
                        }else{
                            b = c;
                            beta = 2*beta;
                            Limits[lim] = b;
                        }
                        continue;
                    }
                }else{
                    if(Yl.nINTERVAL == 2)
                        return Yl;
                    if(Diam(Yl(1)) < epsilon_X && Beta == 1){
                        status = NOTEXPANDED;
                        return Yl(1);
                    }else if(Diam(Yl(1)) < 0.5*Diam(Y) && Beta == 1){
                        if(beta == 1){
                            a = Inf(Yl(1));
                            b = Sup(Yl(1));
                            if(lim == 0)
                                Limits[lim] = a;
                            else
                                Limits[lim] = b;
                            continue;
                        }
                    }
                }
                if(lim == 0)
                    a = Inf(Yl(1));
                else if(lim == 1)
                    b = Sup(Yl(1));
                if(a < Inf(Yl(1)) && Sup(Yl(1)) < c){
                    INTERVAL_VECTOR grd;
                    EINTERVAL NaY;
                    INTERVAL_VECTOR xIV(X),XIV(X);
                    xIV(XIdx) = a;
                    grd = Gradient(fcn,XIV,userdata);
                    EINTERVAL fI,dotfI;
                    fI = Function(fcn,xIV,userdata);
                    dotfI = grd(XIdx);
                    NaY = a-fI/dotfI;
                    tR(1) = NaY(1);
                    tR(2) = INTERVAL(c,b);
                    status = EXPANDED;
                    return tR;
                }
                break;
            }
        }while((b-a) < 0.5*w0);
    }
    status = EXPANDED;
    return EINTERVAL(a,b);
}
NONLINSTATUS NonLinOpt::calcJxxI(INT useJstrictlypositive,INTERVAL_VECTOR xB){
    INTERVAL_VECTOR grd(cdim_f);
    JxxI.resize(cdim_f,cdim_f);
    if(xB.empty())
        xB = Mid(X);
    for(int i = 1;i <= cdim_f;i++){
        INT contreal = 2;
        for(int j = 1;j <= cdim_f;j++){
            INTERVAL_VECTOR Xj(X);
            if(j != i){
                for(int k = contreal;k <= cdim_f;k++)
                    Xj(k) = xB(k);
                contreal++;
            }
            grd = Gradient(fcn,Xj,i,userdata);
            if(grd(j).sup() <= 0 && useJstrictlypositive){
                JxxI.Delete();
                return STRICTILYNEGATIVE;
            }
            if(useJstrictlypositive){
                INTERVAL inter(0,Machine::PosInfinity);
                Intersection(inter,inter,grd(j));
                JxxI(i,j) = inter;
            }else{
                JxxI(i,j) = grd(j);
            }
        }
    }    
}
NONLINSTATUS NonLinOpt::onepassNewtonstep(INT useJstrictlypositive,CONST INTERVAL_VECTOR xB){
    INTERVAL_VECTOR grd(cdim_f);
    if(calcJxxI(useJstrictlypositive,xB) == STRICTILYNEGATIVE){
        status = STRICTILYNEGATIVE;
        return STRICTILYNEGATIVE;
    }
    INTERVAL_MATRIX M;
    INTERVAL_VECTOR r;
    if(B.empty())
        B = Inverse(Mid(JxxI));
    M = B*JxxI;
    if(rdim_f == 1){
        grd = Gradient(fcn,Mid(X),userdata);
        r = grd;
    }else{
        INTERVAL_VECTOR f_x;
        f_x = VectorFunction(fcn,Mid(X),userdata);
        r = B*f_x;
    }
    INTERVAL_VECTOR b;
    if(xB.empty())
        b = M*Mid(X)-r;
    else
        b = M*xB-r;
    LinOpt linopt(M,b,X);
    if(isRegular(M)){
        MATRIX S;
        linopt.intervalhull(S);
        INTERVAL_VECTOR tR;
        if(Intersection(tR,X,linopt.X) == 1){
            X = tR;
        }else{
            status = EMPTY;
            return EMPTY;
        }
        statusM = REGULAR;
        wR = M.diam().max().max();
    }else{
        INTERVAL_VECTOR diag;
        diag = M.diag();
        int i = 1;
        for(;i <= diag.nrows();i++)
            if(!(0.0 <= diag(i)))break;
        if(i > diag.nrows()){
            status = UNLIMITED;
            return UNLIMITED;
        }
        linopt.HansenWalsterOverLinSys();
        X = linopt.X;
        statusM = IRREGULAR;
        wI = M.diam().max().max();
    }
    status = REDUCED;
    return REDUCED;
}
NONLINSTATUS NonLinOpt::UpdateUpperBound(bool usealpha) {
    INTERVAL_VECTOR grd,Xl;
    Xl = Mid(X);
    grd = Gradient(fcn,Mid(X),userdata);
    if(grd.min() == 0 && grd.max() == 0)
        return NOTREDUCED;
    INTERVAL_VECTOR x,xl;
    x = Mid(X);
    if(B.empty()){
        REAL alpha = 0;
        INTERVAL_VECTOR y_alpha;
        REAL Xsup = Sup(X).max();
        int iter = 1;
        do{
            y_alpha = Mid(X)-alpha*grd;
            alpha += alpha_exp_factor*Xsup;
            iter++;
        }while(y_alpha <= EINTERVAL_VECTOR(X) && iter < 100000);
        alpha -= alpha_exp_factor*Xsup;
        xl = Mid(X)-alpha*grd;
    }else{
        xl = Mid(X)-B*grd;
    }
    EINTERVAL f_xl,f_x;
    for(int contvez = 1;contvez <= 8;contvez++){
        f_xl = Function(fcn,xl,userdata);
        f_x = Function(fcn,x,userdata);
        if(f_xl.sup() < f_x.sup())
            x = (x+xl)/2;
        else
            xl = (x+xl/2);
    }
    bool reduced = false;
    if(f_xl.sup() < f_x.sup()){
        if(f_xl.sup() < UpperBound){
            UpperBound = f_xl.sup();
            reduced = true;
        }
    }else{
        if(f_x.sup() < UpperBound){
            UpperBound = f_x.sup();
            reduced = true;
        }
    }
    if(reduced)
        return REDUCED;
    return NOTREDUCED;
}
NONLINSTATUS NonLinOpt::QuadraticMethod(){
    INTERVAL_VECTOR Xl;
    INTERVAL_MATRIX HxxI(cdim_f,cdim_f);
    for(int i = 1;i <= cdim_f;i++){
        for(int j = 1;j <= cdim_f;j++){
            INTERVAL_MATRIX H;
            if(i > j)HxxI(i,j)=0;
            for(int k = j+1;k <= cdim_f;k++){
                Xl(k) = Mid(X(k));
            }
            H = Hessian(fcn,Xl,userdata);
            HxxI(i,j) = H(i,j);
        }
    }
    INTERVAL f_x;
    f_x = Function(fcn,Mid(X),userdata);
    INTERVAL_VECTOR Z,grd,diagH;
    diagH = HxxI.diag();
    grd = Gradient(fcn,Mid(X),userdata);
    INTERVAL Zgrd;
    INTERVAL_VECTOR Coeffs(3);
    for(int i = 1;i <= Xl.nrows();i++){
        //z1*(H1_1*z1 + H2_1*z2 + H3_1*z3) + z2*(H1_2*z1 + H2_2*z2 + H3_2*z3) + z3*(H1_3*z1 + H2_3*z2 + H3_3*z3)
        Z = Xl-Mid(Xl);
        Z(i) = 0;
        Zgrd = Z*grd;
        Coeffs(3) = Hull(Machine::NegInfinity,f_x-UpperBound+Zgrd+0.5*Z.pointwisesqr()*diagH);
        Coeffs(2) = grd(i) + 0.5*Z*HxxI.col(i);
        Coeffs(1) = 0.5*HxxI(i,i);        
        INTERVAL_VECTOR roots;
        roots = Roots(Coeffs);
        Z(i) = Hull(roots(1),roots(2));
        if(roots.nrows() == 3)
            Z(i) = Hull(Z(i),roots(3));
        Xl(i) = Z(i)+Mid(X(i));
        INTERVAL Xll;
        if(Intersection(Xll,Xl(i),X(i)) == 0)
            return EMPTY;
    }
}
NONLINSTATUS NonLinOpt::SplittingaBox(std::vector<INTERVAL_VECTOR>& L){
    INTERVAL_VECTOR storeX(X);
    if(cdim_f > 3 && !JxxI.empty()){
        VECTOR T(cdim_f);
        for(int j = 1;j <= cdim_f;j++){
            T(j) = 0.0;
            for(int i =1;i <= cdim_f;i++)
                T(j) += X(j).diam()*Abs(JxxI(i,j));
        }
        INTEGER_VECTOR TIdx;
        TIdx = T.sort('d');
        if(TIdx(4) == 0)
            return NLUNDEFINED;
        REAL wl;
        VECTOR alpha(cdim_f);
        alpha(cdim_f) = 0.5;
        alpha(cdim_f-1) = 0.5+3*Sqr(T(cdim_f))/(8*Sqr(T(cdim_f-1)));
        for(int k = cdim_f-2;k >= 1;k--){
            alpha(k) = 0.5*(1 + alpha(k+1)*(2 - alpha(k+1))*(Sqr(T(k+1))/Sqr(T(k))));
        }
        for(int j = 1;j <= cdim_f;j++){
            wl = alpha(j)*X(TIdx(j)).diam();
            storeX = X;
            if(Abs(X(TIdx(j)).inf()) < Abs(X(TIdx(j)).sup())){
                storeX(TIdx(j)).ival.inf = X(TIdx(j)).inf();
                storeX(TIdx(j)).ival.sup = storeX(TIdx(j)).inf()+wl;
                X(TIdx(j)).ival.inf = storeX(TIdx(j)).sup();
            }else{
                storeX(TIdx(j)).ival.inf = X(TIdx(j)).sup()-wl;
                storeX(TIdx(j)).ival.sup = X(TIdx(j)).sup();
                X(TIdx(j)).ival.sup = storeX(TIdx(j)).inf();
            }
            L.push_back(storeX);
        }
        if(X.hasNan())
            return NLUNDEFINED;
        L.push_back(X);
    }else{
        std::vector<INTERVAL_VECTOR> l;
        INTERVAL_VECTOR tmpVector(X.nrows());
        INT combinacoes,n;
        INTEGER_VECTOR Idx;
        if(X.nrows() <= 3){
            n = X.nrows();
            Resize(Idx,n);
            for(int i = 1;i <= n;i++)Idx(i)=i;
        }else{
            n = 3;
            VECTOR T;
            T = X.diam();
            INTEGER_VECTOR tmpIdx;
            tmpIdx = T.sort('d');
            Resize(Idx,n);
            for(int i = 1;i <= n;i++){
                Idx(i) = tmpIdx(i);
            }
        }
        combinacoes = pow(2.0,n);
        for(int i = 1;i <= combinacoes;i++)l.push_back(X);
        INTERVAL val;
        for(int i = 1;i <= n;i++){
            int muda = pow(2.0,i-1);
            bool infval = true;
            for(int j = 0;j < combinacoes;j++){
                if(j%muda == 0){
                    if(!infval)
                        val = Hull(X(Idx(i)).mid(),X(Idx(i)).sup());
                    else
                        val = Hull(X(Idx(i)).inf(),X(Idx(i)).mid());
                    infval = !infval;
                }
                l[j](Idx(i)) = val;
            }
        }
        L.insert(L.end(),l.begin(),l.end());
    }
}
/*
INICIO
    reduzida = false;
    trocaX = true;
    Enquanto L não for vaiza faça
        Se trocaX == true
            X = Item mais recente da lista;
            Delete XI da lista.
            XI1 = XI;
            Se LB não for vazia então
                inicializa B com LB;
            Fim se
        Fim se
        trocaX = true;
        passo1 = false;
        consistencia = hull;
        Para i = 1 até n (dimensão do vetor) faça
            Aplique consistencia para cada f_i(x) = 0
            Se X retornar vazio então 
                passo1 = true;
                pare;
            Fim se
            Se w(X) menor E_x e ||f(xI)|| menor E_f 
                Salve X como solução;
                passo1 = true;
                pare;
            Fim se
            diffw = max(|Xdepois - Xantes|);
            D = 0.25w(X) - max(diffw)
            Se D menor ou igual a 0 então //w(X) é o maior intervalo de X
                Se consistencia = hull então
                    i = i + 1;
                Senão
                    i = 1;
                Fim se
                trocaX = false;
                continue;
            Senão
                Se consistencia == hull
                    consistencia = BC;
                Senão
                    pare;
                Fim se
            Fim se
        Fim para
        Se passo1 == true então continue;
        Se w(X) menor ou igual 0.5*(omega_r + omega_I ou i >= n então
            passo9 = true;
            passo28 = false;
            Enquanto passo9 = true
                Se B não é vazia // j é o mesmo índice de XI na lista L;
                    Chama função calcula X_B;
                    faça x_real = x_B;
                Senão
                    x_real = centro XI;
                Fim se
                XI2 = XI;
                calcule JxxI os pontos reais são iguais a x_real;
                calcule B como inversa JxxI_c;
                calcule MxxI = BJxxI;
                Se MxxI é irregular então 
                    atualize omegaI;
                    passo12 = true;
                    Enquanto passo12 == true
                        Se algum elemento da diagonal principal de MxxI não contém o 0
                            aplique uma passagem do método de gauss-seidel para MxxI(y-x)=r(X);
                            Se w(X) menor E_x e ||f(xI)|| menor E_f 
                                 Salve X como solução;
                                passo1 = true;
                                pare;
                            Fim se
                        Fim se
                        D = 0.25w(X) - max(diffw)
                        Se D menor ou igual a 0 então //w(X) é o maior intervalo de X
                            atualize omegaR;
                            continue;
                        Senão
                            pare;
                        Fim se
                    Fim enquanto
                    Se passo1 == true então pare;
                    D = 0.25w(X) - max(diffw)
                    Se D = menor ou igual a 0 então //Neste caso x_i' é obtido de XI1;
                        L = X;
                        passo1 = true;
                        pare;
                    Senão
                        passo28 = true;
                        pare;
                    Fim se
                Senão
                    atualize omegaR;
                Fim se
                Use metodo Hansem Walster linear para resolver MxxI(y-x)=r
                Se o resultado for vazio então
                    passo1 = true;
                    pare;
                Fim se
                Se w(X) menor E_x e ||f(xI)|| menor E_f 
                    Salve X como solução;
                    passo1 = true;
                    pare;
                Fim se
                D = 0.25w(X) - max(diffw)
                Se D menor ou igual a 0 então //w(X) é o maior intervalo de X
                    reduzida = true;
                Senão
                    reduzida = false;
                Fim se
                omegaNB = w(X) para cada X_i;
                Execute um passo de Newton;
                omegaNA = w(X) para cada X_i;
                Se fI(X) contém o 0 e MxxI é regular e omegaNB == omegaNA então
                    savle X como solução
                    passo 1 = true;
                    pare;
                Fim se
                LB = B;
                Se w(XI) menor ou igual 0.125*w(XI2) então
                    continue;
                Senão
                    pare;
                Fim se
            Fim enquanto
            Se passo28 == false e passo1 == false então
                Para j = 1 até n faça
                    Aplique a consistência para Bf(X)_j
                    calcule B;
                    Se B não mudou então
                        j = j + 1;
                    Fim se
                    Fim se
                    Se w(X) menor E_x e ||f(xI)|| menor E_f 
                        Salve X como solução;
                        passo1 = true;
                        pare;
                    Fim se
                    Se reduzida == true então
                        continue;
                    Fim se
                Fim para
                Aplique a consistencia de caixa para Bf(X) para cada i;
                Se o resultado for vazio então
                    passo 1 = true;
                    pare;
                Fim se
                Se w(X) menor E_x e ||f(xI)|| menor E_f 
                     Salve X como solução;
                    passo1 = true;
                Senão
                    D = 0.25w(X) - max(diffw)
                    Se D menor ou igual a 0 então x_i de XI1
                        L = XI;
                        LB = xB;
                        passo1 = true
                    Fim se
                Fim se
            Fim se
        Fim se
        Se passo1 == true
            continue;
        Fim se
        faça a divisão da caiza XI e salve na lista L;
        para cada nova caixa adicione um espaço em LB;
    Fim enquanto
FIM*/
NONLINSTATUS NonLinOpt::NewtonMethod(vector<INTERVAL_VECTOR>& L){
    bool reduzida = false;
    bool trocaX = true;
    bool passo1 = false;
    INTERVAL_VECTOR XI1,smallvalueX;
    vector < INTERVAL_VECTOR> LxB;
    vector < INTERVAL_VECTOR> LR;
    INTERVAL_VECTOR xB,xI;
    LxB.push_back(xI);
    wR = 0;
    bool Bchanged = false;
    VECTOR diffw;
    EINTERVAL_VECTOR Xl;
    std::vector<INTERVAL_VECTOR> XlParse;
    EINTERVAL_VECTOR f;
    INTERVAL_VECTOR IVf;
    for(vector<INTERVAL_VECTOR>::iterator it = L.begin();it != L.end();it++){
        Xl = (*it);
        IVf = VectorFunction(fcn,Xl.getIV(1),userdata);
        if(Norm(IVf).sup() <= UpperBound && !IVf.hasNan()){
            X = (*it);
            UpperBound = Norm(IVf).sup()+1;
        }
    }
    REAL MinValue = Machine::PosInfinity;
    for(int iter = 1;!L.empty() && iter <= optmiset.MaxIter;iter++){        
        if(trocaX){
            vector<INTERVAL_VECTOR>::iterator it = L.begin();
            X = L[L.size()-1];
            L.pop_back();
            wI = X.diam().max();
            XI1 = X;
            xB = Mid(X);
            B.Delete();
            Bchanged = false;
        }
        INTERVAL_VECTOR fx = VectorFunction(fcn,X,userdata);
        if(Norm(fx).sup() < UpperBound){
            smallvalueX = X;
            UpperBound = Norm(fx).sup();
            cout << "smallvalueX=" << smallvalueX << " <-> Norm(fx) = " << Sqrt(Norm(fx))/rdim_f << endl; 
        }
        if(Norm(fx).inf() != 0 && !fx.hasNan()){
            trocaX = true;
            continue;
        }else{
            if(Norm(fx).sup() < MinValue){
                smallvalueX = X;
                MinValue = Norm(fx).sup();
                cout << "smallvalueX(0)=" << smallvalueX << " <-> Norm(fx) = " << Sqrt(Norm(fx))/rdim_f << endl; 
            }
        }
        if(showfx){
                cout << "X=" << X << " = (" << Sqrt(Norm(fx))/rdim_f << ")    \r";
                cout.flush();
        }
        trocaX = true;
        passo1 = false;
        consistency = HC;
        INTERVAL f_bar(0);
        int i;
        VECTOR wb,wa;
        REAL D;
        for(i = 1;i <= X.nrows();){
            wb = X.diam();
            if(consistency == HC){
                Xl = X;
                for(int j = 1;j <= rdim_f;j++){
                    f = Function_HC(fcn,f_bar,Xl,j,userdata);
                    if(Xl.empty()){
                        passo1 = true;
                        trocaX = true;
                        break;
                    }
                    Parse(XlParse,Xl);
                    X = XlParse[0];
                    std::copy(XlParse.begin()+1,XlParse.end(),L.end());
                }
                if(X.diam().max() < epsilon_X && f.norm().max() < epsilon_f && !passo1){
                    LR.push_back(X);
                    passo1 = true;
                    break;
                }
            }else if(consistency == BC){
                for (int j = 1; j <= rdim_f; j++) {
                    INTERVAL_VECTOR tmpX = X;
                    for(int k = 1;k <= cdim_f;k++){
                        EINTERVAL Xi;
                        useidxtofcn = true;
                        useBtofcn = false;
                        Xi = BoxConsistency(Mid(xB(k)),k,j);
                        if(status == EXPANDED){
                            Xl(k) = Xi;
                        }else if(status == NOTEXPANDED){
                            Xl(k) = tmpX(k);
                        }
                    }
                    Parse(XlParse,Xl);
                    X = XlParse[0];
                    std::copy(XlParse.begin()+1,XlParse.end(),L.end());                
                }
            }
            if(passo1)break;
            wa = X.diam();
            diffw = wb-wa;
            D = 0.25*X.diam().max() - diffw.max();
            if(D <= 0){
                if(consistency == HC)
                    i = i + 1;
                else
                    i = 1;
                trocaX = false;
                continue;
            }else{
                if(consistency == HC)
                    consistency = BC;
                else
                    break;
            }
        }
        if(passo1)continue;
        if(X.diam().max() <= 0.5*(wR + wI) || i > X.nrows()){
            bool passo9 = true;
            bool passo28 = false;
            while(passo9){
                if(!B.empty() || Bchanged){
                    xB = ComputexB();
                }else{
                    xB = Mid(X);
                }
                INTERVAL_VECTOR XI2 = X;
                wb = XI2.diam();
                calcJxxI(false,xB);
                INTERVAL_MATRIX MxxI;
                INTERVAL_VECTOR r;
                B = Inverse(Mid(JxxI));
                if(ErrorHandler::LastErrorCode != 0){
                    JxxI.Delete();
                    Bchanged = false;
                    passo1 = true;
                    break;
                }
                MxxI = B*JxxI;
                INTERVAL_VECTOR fx;
                fx = VectorFunction(fcn,X,userdata);
                r = B*fx;
                INTERVAL_VECTOR b;
                b = MxxI*xB-r;
                LinOpt linopt(MxxI,b,X);                      
                if(!isRegular(MxxI)){
                    wI = MxxI.diam().max().max();
                    bool passo12 = true;
                    INTERVAL_VECTOR f_x,r;
                    f_x = VectorFunction(fcn,xB,userdata);
                    r = B*f_x;                    
                    while(passo12){
                        INTERVAL_VECTOR diag;
                        diag = MxxI.diag();
                        for(int i = 1;i <= diag.nrows();i++){
                            if((0.0 <= diag(i)))continue;
                            INTERVAL sum(0);
                            for(int j = 1;j <= diag.nrows();j++){
                                if(j == i) continue;
                                sum = MxxI(i,j)*(X(j)-xB(j));
                            }
                            INTERVAL N;
                            N = xB(i) + 1/MxxI(i,i)*(r(i)-sum);
                            if(Intersection(N,N,X(i)) == 1)
                                X(i) = N;
                        }
                        if(X.diam().max() < epsilon_X && f.norm().max() < epsilon_f){
                            LR.push_back(X);
                            passo1 = true;
                            break;
                        }
                        wa = X.diam();
                        diffw = wb-wa;
                        D = 0.25*wa.max() - diffw.max();
                        if(D <= 0){
                            wR = MxxI.diam().max().max();
                            continue;
                        }else{
                            break;
                        }
                    }
                    wb = XI1.diam();
                    wa = X.diam();
                    diffw = wb-wa;
                    D = 0.25*wa.max() - diffw.max();
                    if(D <= 0){
                        L.push_back(X);
                        passo1 = true;
                    }else{
                        passo28 = true;
                    }
                    break;
                }else{
                    wR = MxxI.diam().max().max();
                }
                if(passo1)break;
                MATRIX S;
                linopt.intervalhull(S);
                if(linopt.status != STATUS::REGULAR){
                    passo1 = true;
                    break;
                }
                if(X.diam().max() < epsilon_X && f.norm().max() < epsilon_f){
                    LR.push_back(X);
                    passo1 = true;
                    break;
                }
                wb = XI1.diam();
                wa = X.diam();
                diffw = wb-wa;
                D = 0.25*wa.max() - diffw.max();
                if(D <= 0)
                    reduzida = true;
                else
                    reduzida = false;
                INTERVAL_VECTOR fI;
                fI = VectorFunction(fcn,X,userdata);
                for(int i = 1;i <= rdim_f;i++){
                    for(int j = 1;j <= cdim_f;j++){
                        useBtofcn = false;
                        NewtonStep(Mid(X(j)),j,i);
                        if(status != ALLXCONTAINED)break;
                    }
                }
                INTERVAL_VECTOR zeros(fI.nrows());
                Clear(zeros);
                if(zeros <= fI && status == ALLXCONTAINED){
                    LR.push_back(X);
                    passo1 = true;
                    break;
                }
                Bchanged = true;
                if(wa.max() <= 0.125*XI2.maxdiam())
                    continue;
                else
                    break;
            }
            if(!passo28 && !passo1){
                userdata = make_shared<MATRIX>(B);
                INTERVAL fbar(0);
                INTERVAL_MATRIX  Bb = Hull(B);
                for(int i = 1;i <= cdim_f;i++){
                    EINTERVAL_VECTOR Xl(X);
//                    f = Bfcn_vec_hc(fbar,Xl,userdata);
                    calcJxxI(false,xB);
                    if(Bb.compare(Hull(B)).max().max() < 1e-15){
                        break;
                    }
                    if(X.diam().max() < epsilon_X && f.norm().max() < epsilon_f){
                        LR.push_back(X);
                        passo1 = true;
                        break;
                    }
                }
                if(passo1)continue;
                FUNCTION2 tmpfcn = fcn;
                fcn = Bfunc;
                INTERVAL_VECTOR tmpX = X;
                for (int j = 1; j < rdim_f; j++) {
                    for(int i = 1;i <= cdim_f;i++){
                        EINTERVAL Xi;
                        useidxtofcn = true;
                        useBtofcn = true;
                        Xi = BoxConsistency(Mid(xB(i)),i,j);
                        if(status == EXPANDED){
                            Xl(i) = Xi;
                        }else if(status == NOTEXPANDED){
                            Xl(i) =tmpX(i);
                        }else if(status == ALLXDELETED){
                            passo1 = true;
                            break;
                        }
                    }
                    if(passo1)break;
                    Parse(XlParse,Xl);
                    X = XlParse[0];
                    std::copy(XlParse.begin()+1,XlParse.end(),L.end());                
                }
                useBtofcn = false;
                fcn = tmpfcn;
                if(passo1)continue;
                Parse(XlParse,Xl);
                X = XlParse[0];
                std::copy(XlParse.begin()+1,XlParse.end(),L.end());
                fcn = tmpfcn;
                userdata.reset();
                if(X.diam().max() < epsilon_X && f.norm().max() < epsilon_f){
                    LR.push_back(X);
                    passo1 = true;
                    break;
                }
                wb = XI1.diam();
                wa = X.diam();
                diffw = wb-wa;
                D = 0.25*wa.max() - diffw.max();
                if(D <= 0){
                    L.push_back(X);
                    LxB.push_back(xB);
                    passo1 = true;
                    continue;
                }
            }           
        }
        INT oldsize = L.size();
        SplittingaBox(L);
        for(int i = oldsize;i < L.size();i++){
            INTERVAL_VECTOR tmpxB;
            LxB.push_back(tmpxB);
        }
    }
    L = LR;
    if(L.empty()){
        cout << "Solução não foi encontrada com a precisão desejada" << endl;
        cout << "retornado assim a melhor solução encontrada" << endl;
        L.push_back(smallvalueX);
    }
}
/*
 *  INICIO algoritmo para calcular XB
 *      z(1) = Mid(XI)
 *      Para i = 0 até 3 faça
 *          z(i+1) = z(i) - Bf(z(i));
 *          Se z(i+1) pertence a XI então
 *              Se ||f(z(i+1)|| maior ou igual ||f(z(i)|| então
 *                  x = z(i);
 *                  pare;
 *              Senão
 *                  x = z(i+1);
 *              Fim se
 *          Senão
 *              Para i = 1 até n faça
 *                  Se z(i+1)(j) pertence XI(j) então
 *                      continue;
 *                  Fim se
 *                  Se z(i+1)(j) menor que o limite inferior de XI(j) então
 *                      t = (Limite inferior de XI(j) - z(i+1)(j))/(z(i)(j)-z(i+1)(j));
 *                      j = 1;
 *                      Para j até n faça
 *                          zl(j) = t*z(i)(j) + (1-t)*z(i)(j);
 *                          Se pt(j) não pertence XI(j) então
 *                              pare;
 *                          Fim se
 *                      Fim para
 *                      Se j maior ou igual a n então
 *                          Se ||f(zl)|| menor que ||f(zi)|| então
 *                              x = zl
 *                          Senão
 *                              x = z(i);
 *                          Fim se
 *                      Fim se
 *                  Fim se
 *              Fim para
 *              pare;
 *          Fim se
 *      Fim para
 *      Se x_i não pertence a X_i para algum i então
 *          x_i = o limite de X_i mais próximo de x_i;
 *      Fim se
 *      retorna x;
 *  FIM
 */

INTERVAL_VECTOR NonLinOpt::ComputexB(){

    INTERVAL_VECTOR xB;
    vector<INTERVAL_VECTOR> z;
    z.push_back(Hull(Mid(X)));
    INTERVAL_VECTOR fz_i;
    for(int i = 0;i < 3;i++){
        fz_i = VectorFunction(fcn,z[i],userdata);
        INTERVAL_VECTOR zBfzi = z[i]-B*fz_i;
        z.push_back(zBfzi);
        INTERVAL_VECTOR fz_i1;
        INTERVAL fz_inorm,fz_i1norm;
        if(z[i+1] <= X){
            fz_i1 = VectorFunction(fcn,z[i+1],userdata);
            fz_inorm = Norm(fz_i);
            fz_i1norm = Norm(fz_i1);
            if(fz_i1norm.sup() >= fz_inorm.sup()){
                xB = z[i];
                break;
            }else{
                xB = z[i+1];
            }
        }else{
            INTERVAL_VECTOR zl(X.nrows());
            for(int j = 1; j <= X.nrows();j++){
                if(z[i+1](j) <= X(j))
                    continue;
                if(Sup(z[i+1](j)) < Inf(X(j))){
                    INTERVAL t = (X(j).inf() - z[i+1](j).mid())/(z[i](j).mid()-z[i+1](j).mid());
                    INT k = 1;
                    for(;k <= X.nrows();k++){
                        if(k == j)continue;
                        zl(k) = t*z[i](k).mid() + (1-t)*z[i+1](k).mid();
                        if(!(zl(k) <= X(k)))
                            break;
                    }
                    if(k > X.nrows()){
                        fz_i = VectorFunction(fcn,z[i],userdata);
                        fz_i1 = VectorFunction(fcn,zl,userdata);
                        fz_inorm = Norm(fz_i);
                        fz_i1norm = Norm(fz_i1);
                        if(fz_inorm.sup() < fz_i1norm.sup()){
                            xB = zl;
                        }else{
                            xB = z[i];
                        }
                        break;
                    }
                }
            }
            break;
        }
    }
    if(xB.empty())
        return Hull(Mid(X));
    for(int i = 1;i <= X.nrows();i++){
        if(xB(i).sup() < X(i).inf())
            xB(i) = X(i).inf();
        if(xB(i).inf() > X(i).sup())
            xB(i) = X(i).sup();
    }
    return xB;
}