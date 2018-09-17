/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NonLinOpt.hpp
 * Author: darlan
 *
 * Created on 7 de Novembro de 2016, 08:46
 */

#ifndef NONLINOPT_HPP
#define NONLINOPT_HPP
#include <Utilities.h>
#include <AutoDiff/IntervalAutoDiff.h>
#include <functional>
#include <EINTERVAL.hpp>
#include <EINTERVALVECTOR.hpp>
#include <EINTERVAL_MATRIX.hpp>
#include <Vector.h>
#include <IntervalVector.h>
#include <Matrix.h>
#include <ctime>
#include <random>
#include <NLF/NLF.hpp>
#include <NLF/NLF2.hpp>
#include <omp.h>
#include <Constants.h>
#include <Functions.h>
#include <GlobalOpt/UnconstrainedOpt.h>
#include <LinOpt/LinOpt.hpp>
#include <EFunctions.h>
#include <functional>
#include <Constants.h>
#include <PolinomialRoots/PolinomialRoots.hpp>
#include <math.h>

#define IL_STD
#include <ilcplex/ilocplex.h>

ILOSTLBEGIN

using namespace std;
typedef enum STATUS NONLINSTATUS;
struct OPTMNONLIN{
    REAL epsilon_X;
    REAL epsilon_f;
};
class NonLinOpt {
public:
    INTERVAL_VECTOR X;
    MATRIX B;
    /*Exemplo de declaração:
         FUNCTION2 fcn(2,NULL,
                    More_Garbow_Hillstrom_AD,
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    More_Garbow_Hillstrom_func);
    */
    FUNCTION2 fcn;
    /*FUNCTION2 Bjac(2,2,More_Garbow_Hillstrom_Bgrd_AD);*/
    FUNCTION2 jac;
    /*FUNCTION2 Bjac(2,2,More_Garbow_Hillstrom_Bgrd_AD);*/
    FUNCTION2 Bfunc;
    /*Exemplo de declaração:
        function<EINTERVAL (INTERVAL f_bar,EINTERVAL_VECTOR& X,shared_ptr<VOID>)> fcn_hc = More_Garbow_Hillstrom_HC;
     */
    function<EINTERVAL (INTERVAL f_bar,EINTERVAL_VECTOR& X,shared_ptr<VOID>)> fcn_hc;
    function<EINTERVAL_VECTOR (INTERVAL f_bar,EINTERVAL_VECTOR& X,shared_ptr<VOID>)> fcn_vec_hc;
    function<EINTERVAL_VECTOR (INTERVAL f_bar,EINTERVAL_VECTOR& X,shared_ptr<VOID>,MATRIX B)> Bfcn_vec_hc;
    function<EINTERVAL_VECTOR (INTERVAL f_bar,EINTERVAL_VECTOR& X,shared_ptr<VOID>,MATRIX B)> Bfcn_vec;
    /*Exemplo de declaração:
        function<EINTERVAL (INTERVAL f_bar,EINTERVAL_VECTOR& X,shared_ptr<VOID>)> fcn_hc = More_Garbow_Hillstrom_grd_HC;
     */
    function<EINTERVAL (INTERVAL f_bar,EINTERVAL_VECTOR& X,shared_ptr<VOID>)> grd_hc;
    /*Exemplo de declaração:
        function<EINTERVAL (INTERVAL f_bar,EINTERVAL_VECTOR& X,shared_ptr<VOID>)> fcn_hc = More_Garbow_Hillstrom_Hess_HC;
     */
    function<EINTERVAL (INTERVAL f_bar,EINTERVAL_VECTOR& X,shared_ptr<VOID>)> hess_hc;
    OPTMISET optmiset;
    REAL epsilon_X;
    REAL epsilon_f;
    REAL UpperBound;
    REAL LowerBound;
    bool showfx;
    INT DimensionData;
    std::shared_ptr<VOID> userdata;
    /*Fator utilizado para multiplicar o limite superior
     de X e calcular o alpha:
        alpha = alpha_exp_factor*X.sup();*/
    REAL alpha_exp_factor;
    NonLinOpt(){
        status = NLUNDEFINED;
        optmiset.UpperBound = Machine::PosInfinity;
        epsilon_X = 1e-3;
        epsilon_f = 1e-3;
        UpperBound = Machine::PosInfinity;
        LowerBound = Machine::NegInfinity;
        alpha_exp_factor = 1e-4;
        rdim_f = 1;
        useidxtofcn = false;
        useBtofcn = false;
        showfx = false;
        DimensionData = 32;
    }
    NonLinOpt(INTERVAL_VECTOR& Xin){
        X = Xin;
        status = NLUNDEFINED;
        optmiset.UpperBound = Machine::PosInfinity;
        epsilon_X = 1e-3;
        epsilon_f = 1e-3;
        UpperBound = Machine::PosInfinity;
        LowerBound = Machine::NegInfinity;
        alpha_exp_factor = 1e-4;
        rdim_f = 1;
        cdim_f = X.nrows();
        useidxtofcn = false;
        useBtofcn = false;
        showfx = false;
        DimensionData = 32;
    }
    /*rdim determina a quantidade de funcoes f(x)
     cdim determina a quantidade de variaveis de f(x)*/
    NonLinOpt(INT rdim,INT cdim,INTERVAL_VECTOR& Xin){
        if(Xin.empty())
            Resize(X,cdim);
        X = Xin;
        status = NLUNDEFINED;
        optmiset.UpperBound = Machine::PosInfinity;
        epsilon_X = 1e-3;
        epsilon_f = 1e-3;
        UpperBound = Machine::PosInfinity;
        LowerBound = Machine::NegInfinity;
        alpha_exp_factor = 1e-4;
        rdim_f = rdim;
        cdim_f = cdim;
        useidxtofcn = false;
        useBtofcn = false;
        showfx = false;
        DimensionData = 32;
    }
    NonLinOpt(const NonLinOpt& orig){
        X = orig.X;
        fcn = orig.fcn;
        fcn_hc = orig.fcn_hc;
        grd_hc = orig.grd_hc;
        optmiset = orig.optmiset;
        status = orig.status;
        epsilon_X = orig.epsilon_X;
        epsilon_f = orig.epsilon_f;
        UpperBound = orig.UpperBound;
        LowerBound = orig.LowerBound;
        alpha_exp_factor = orig.alpha_exp_factor;
        rdim_f = orig.rdim_f;
        JxxI = orig.JxxI;
        useidxtofcn = orig.useidxtofcn;
        useBtofcn = orig.useBtofcn;
        showfx = orig.showfx;
        DimensionData = 32;
    }
    virtual ~NonLinOpt();
    /*
      Função de otimização baseado no método de Newton              
      intervalar.
      (Global optmization methods pag. 185)
     Parâmetros de entrada:
        X0 -> Interval inicial.
        epsilon_f -> Tolerância para o diâmetro da
                     função objetivo para a parada
    */
    vector<INTERVAL> IntervalNewtonMethod(INTERVAL& X0,REAL epsilon_f);
    /*
      Função de otimização baseado no método de Newton 
      intervalar.
      (Global optmization methods pag. 185)
     Parâmetros de entrada:
        Xidx -> Índice da variável fixa no vetor X.
        epsilon_f -> Tolerância para o diâmetro da
                     função objetivo para a parada
    */
    vector<INTERVAL> IntervalNewtonMethod(INT XIdx,REAL epsilon_f);
    INT GlobalOptimization(vector<INTERVAL_VECTOR>& L1);
    /*Funcao utilizada para dividir os intervalos
     dos componentes de xI quando os processos
     de consistencia e Newton não fizeram efeito.*/
    NONLINSTATUS SplittingaBox(std::vector<INTERVAL_VECTOR>& L);
    NONLINSTATUS NewtonMethod(vector<INTERVAL_VECTOR>& L);
private:
    /* Função utilizada para determinar o afinamento
     de um intervalo X baseado no método de box
     consistency descrito por Hansen e Walster
     (Global Optmization (pag. 217)
     Parâmetros de entrada:
        ExpPt -> Valor real do ponto que será utilizado
                 na expansão.
        epsilon_X -> Tolerância do diâmetro do intervalo
                     de X.
        XIdx -> Índice do vetor X para variável em
                análise.
     Parâmetros de saída:
        INTERVAL -> Com o intervalo [a,b] da variável
                    Xi que não contém o zero.
        status -> A variável status da classe é setada
                    com a resposta da função.*/
    EINTERVAL BoxConsistency(REAL ExpPt,INT XIdx,INT fIdx = 0);
    /*Calculo do U de acordo com o livro  de
     Hansen e Walster
     (Global Optmization (pag. 311)
     As variaveis X e userdata da classe
     devem ser inicializada antes da chamada
     da funcao.
     O parâmetro de saida e o vetor U de acordo
     com o livro so que um vetor com todos os t
     no lugar de um valor real.*/
    NONLINSTATUS NewtonStopCriteria(REAL& x,INTERVAL& X);
    NONLINSTATUS NewtonStopCriteria(REAL& x,INT XIdx);
    EINTERVAL NewtonStep(REAL x,INT Xidx,INT fIdx = 0);
    EINTERVAL NewtonStep(REAL x,INTERVAL X,INT fIdx = 0);
    INT ExpansionStep(INTERVAL& IX);
    EINTERVAL_VECTOR Ycalc( );
    /*Realiza um passo do método de Newton
     conforme descrito na seção 11.11 do livro
     do Hansen e Walster para utilizacao no
     algoritmo do capitulo 12 existe uma variavel
     de entrada que diz se e para fazer o J(x,xI)
     estritamente positivo. Neste caso toda parte
     negativa da diagonal principal do J(x,xI) e
     deletada.*/
    NONLINSTATUS onepassNewtonstep(INT useJstrictlypositive,INTERVAL_VECTOR xB);
    /*Funcao utilizada para atualizar o limite
     superior (UpperBound).*/
    NONLINSTATUS UpdateUpperBound(bool usealpha);
    /*Determinando a solução f(y) utilizando
     o método quadrático.*/
    NONLINSTATUS QuadraticMethod();
    INT rdim_f;
    INT cdim_f;
    NONLINSTATUS status;
    NONLINSTATUS statusM;
    INTERVAL_MATRIX JxxI;
    bool useBtofcn;
    REAL wR;
    REAL wI;
    REAL wII;
    REAL wH;
    /*Funcao utilizada apenas dentro da funcao de otimizacao global*/
    bool passo6(vector<INTERVAL_VECTOR>& L);
    /*Funcao utilizada apenas dentro da funcao de otimizacao global*/
    bool passo13(vector<INTERVAL_VECTOR>& L);
    bool useidxtofcn;
    /*Calcula a matriz jacobiana intervalar*/
    NONLINSTATUS calcJxxI(INT useJstrictlypositive,INTERVAL_VECTOR xB);
    INTERVAL_VECTOR ComputexB();
};

#endif /* NONLINOPT_HPP */

