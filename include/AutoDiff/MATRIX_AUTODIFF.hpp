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
#include <assert.h>
#include <AutoDiff/IntervalAutoDiff.h>
#include <AutoDiff/AUTODIFF_ELEMENT.hpp>
#include <IntervalMatrix.h>
#include <Interval.h>
#include <Functions.h>

#ifndef MATRIX_AUTODIFF_HPP
#define MATRIX_AUTODIFF_HPP

/*Matriz de autodiferenciação.
 Utilizada para realizar a autdiferenciação.
 completar*/
template<class simple,class vec,class mat>
class MATRIX_AUTODIFF {
public:
    /*Vector de vetor que contém os 
     elementos da matriz.*/
    vector<vector<AUTODIFF_ELEMENT<simple,vec,mat> > >theElements;
    /*Número de colunas da matriz.*/
    INT nCols;
    /*Número de linhas da matriz.*/
    INT nRows;
    /*Indica se a matriz Hessiana deverá
     ser calculada.*/
    bool ComputeHessian;
    /*Inicializa a matriz de autodiferenciação
     com todos os elementos vazios e determina
     o cálculo da matriz Hessiana.*/
    MATRIX_AUTODIFF (){
        nCols = 0;
        nRows = 0;
        ComputeHessian = true;
    };
    /*Inicializa a matriz de autodiferenciação
     com todos os elementos vazios e determina
     o cálculo da matriz Hessiana.*/
    MATRIX_AUTODIFF (bool cptHess){
        nCols = 0;
        nRows = 0;
        ComputeHessian = cptHess;
    };
    /*Inicializa a matriz de autodiferenciação
     com todos os elementos com valores iguais
     a matriz de entrada e gradiente e hessiana
     vazios e tamanho igual a zero.*/    
    MATRIX_AUTODIFF (CONST mat& values):ComputeHessian(true){
        nCols = (INT)ColDimension(values);
        nRows = (INT)RowDimension(values);
        AUTODIFF_ELEMENT<simple,vec,mat> tmpMAD;
        vector<AUTODIFF_ELEMENT<simple,vec,mat> > tmpVMAD;
        for(int i = 1;i <= nRows;i++){
            for(int j = 1;j <= nCols;j++){
                tmpMAD.value = values(i,j);
                tmpVMAD.push_back(tmpMAD);
            }
            theElements.push_back(tmpVMAD);
            tmpVMAD.clear();
        }
    }
    /*Inicializa a matriz de autodiferenciação
     com todos os elementos com valores iguais
     a matriz de entrada e gradiente e hessiana
     de tamanhos iguais a diffsizes elemento por
     * elemento e valores iguais a zero.*/    
    MATRIX_AUTODIFF (CONST mat& values,CONST MATRIX& diffsizes):ComputeHessian(true){
        nCols = (INT)ColDimension(values);
        nRows = (INT)RowDimension(values);
        AUTODIFF_ELEMENT<simple,vec,mat> tmpMAD;
        vector<AUTODIFF_ELEMENT<simple,vec,mat> > tmpVMAD;
        for(int i = 1;i <= nRows;i++){
            for(int j = 1;j <= nCols;j++){
                tmpMAD.value = values(i,j);
                Resize(tmpMAD.grd,diffsizes(i,j));
                Initialize(tmpMAD.grd,0.0);
                Initialize(tmpMAD.hess,0.0);
                Resize(tmpMAD.hess,diffsizes(i,j),diffsizes(i,j));
                tmpVMAD.push_back(tmpMAD);
            }
            theElements.push_back(tmpVMAD);
            tmpVMAD.clear();
        }
    }
    /*Inicializa a matriz de autodiferenciação
     com todos os elementos com valores iguais
     a matriz de entrada e gradiente e hessiana
     de tamanhos iguais a diffsizes elemento por
     * elemento e valores iguais a zero.*/    
    MATRIX_AUTODIFF (INT r, INT c,CONST mat& values,INT dim,bool CompHess){
        nCols = c;
        nRows = r;
        ComputeHessian = CompHess;
        AUTODIFF_ELEMENT<simple,vec,mat> tmpMAD;
        vector<AUTODIFF_ELEMENT<simple,vec,mat> > tmpVMAD;
        for(int i = 1;i <= nRows;i++){
            for(int j = 1;j <= nCols;j++){
                tmpMAD.value = values(i,j);
                Resize(tmpMAD.grd,dim);
                Initialize(tmpMAD.grd,0.0);
                tmpMAD.ComputeHessian = CompHess;
                if(CompHess){
                    Resize(tmpMAD.hess,dim,dim);
                    Initialize(tmpMAD.hess,0.0);
                }
                tmpVMAD.push_back(tmpMAD);
            }
            theElements.push_back(tmpVMAD);
            tmpVMAD.clear();
        }
    }
    /*Inicializa a matriz de autodiferenciação
     com todos os elementos com valores iguais
     a matriz de entrada e gradiente e hessiana
     de tamanhos iguais a diffsizes elemento por
     * elemento e valores iguais a zero.*/    
    MATRIX_AUTODIFF (CONST mat& values,CONST vec& inigrd,CONST mat& inihess):ComputeHessian(true){
        nCols = ColDimension(values);
        nRows = RowDimension(values);
        AUTODIFF_ELEMENT<simple,vec,mat> tmpMAD;
        vector<AUTODIFF_ELEMENT<simple,vec,mat> > tmpVMAD;
        for(int i = 1;i <= nRows;i++){
            for(int j = 1;j <= nCols;j++){
                tmpMAD.value = values(i,j);
                tmpMAD.grd=inigrd;
                tmpMAD.hess=inihess;
                tmpVMAD.push_back(tmpMAD);
            }
            theElements.push_back(tmpVMAD);
            tmpVMAD.clear();
        }
    }
    /*Inicializa a matriz de autodiferenciação
     com todos os elementos com valores iguais
     a matriz de entrada e gradiente e hessiana
     iguais aos elementos das matrizes inigrd e
     inihess respectivamente.*/    
    MATRIX_AUTODIFF (CONST mat& values,CONST vector<vector<vec> >& inigrd,CONST vector<vector<mat> >& inihess):ComputeHessian(true){
        nCols = ColDimension(values);
        nRows = RowDimension(values);
        AUTODIFF_ELEMENT<simple,vec,mat> tmpMAD;
        vector<AUTODIFF_ELEMENT<simple,vec,mat> > tmpVMAD;
        for(int i = 1;i <= nRows;i++){
            for(int j = 1;j <= nCols;j++){
                tmpMAD.value = values(i,j);
                tmpMAD.grd=inigrd[i][j];
                tmpMAD.hess=inihess[i][j];
                tmpVMAD.push_back(tmpMAD);
            }
            theElements.push_back(tmpVMAD);
            tmpVMAD.clear();
        }
    }
    /*Inicializa a matriz de autodiferenciação
     com o número de linhas iguais a r e 
     colunas iguais c. O gradiente e hessiana
     iguais aos elementos das matrizes nos vetores 
     inigrd e inihess respectivamente.*/    
    MATRIX_AUTODIFF (INT r,INT c,CONST vector<vector<vec> >& inigrd,CONST vector<vector<mat> >& inihess):ComputeHessian(true){
        nCols = c;
        nRows = r;
        AUTODIFF_ELEMENT<simple,vec,mat> tmpMAD;
        vector<AUTODIFF_ELEMENT<simple,vec,mat> > tmpVMAD;
        for(int i = 1;i <= nRows;i++){
            for(int j = 1;j <= nCols;j++){
                tmpMAD.value = 0.0;
                tmpMAD.grd=inigrd[i][j];
                tmpMAD.hess=inihess[i][j];
                tmpVMAD.push_back(tmpMAD);
            }
            theElements.push_back(tmpVMAD);
            tmpVMAD.clear();
        }
    }
    /*Inicializa a matriz de autodiferenciação
     com o número de linhas iguais a r e 
     colunas iguais c. O gradiente iguais aos 
     elementos das matrizes nos vetores 
     inigrd e a hessiana igual a zero.*/    
    MATRIX_AUTODIFF (INT r,INT c,CONST vector<vector<vec> >& inigrd,bool CompHess){
        nCols = c;
        nRows = r;
        ComputeHessian = CompHess;
        AUTODIFF_ELEMENT<simple,vec,mat> tmpMAD;
        vector<AUTODIFF_ELEMENT<simple,vec,mat> > tmpVMAD;
        for(int i = 1;i <= nRows;i++){
            for(int j = 1;j <= nCols;j++){
                tmpMAD.dim = Dimension(inigrd[i][j]);
                tmpMAD.value = 0.0;
                Resize(tmpMAD.grd,tmpMAD.dim);
                tmpMAD.grd=inigrd[i][j];
                tmpMAD.ComputeHessian = CompHess;
                if(CompHess){
                    Resize(tmpMAD.hess,tmpMAD.dim,tmpMAD.dim);
                    Clear(tmpMAD.hess);
                }
                tmpVMAD.push_back(tmpMAD);
            }
            theElements.push_back(tmpVMAD);
            tmpVMAD.clear();
        }
    }
    /*Inicializa a matriz de autodiferenciação
     com o número de linhas iguais a r e 
     colunas iguais c. O gradiente iguais aos 
     elementos das matrizes nos vetores 
     inigrd e a hessiana igual a zero.*/    
    MATRIX_AUTODIFF (INT r,INT c,CONST INTERVAL_AUTODIFF& srcIAD){
        nCols = c;
        nRows = r;
        ComputeHessian = srcIAD.ComputeHessian;
        AUTODIFF_ELEMENT<simple,vec,mat> tmpMAD;
        vector<AUTODIFF_ELEMENT<simple,vec,mat> > tmpVMAD;
        tmpMAD = srcIAD;
        for(int i = 1;i <= nRows;i++){
            for(int j = 1;j <= nCols;j++){
                tmpVMAD.push_back(tmpMAD);
            }
            theElements.push_back(tmpVMAD);
            tmpVMAD.clear();
        }
    }
    MATRIX_AUTODIFF (INT r,INT c,INT nGRD,bool ComputeHess){
        nCols = c;
        nRows = r;
        AUTODIFF_ELEMENT<simple,vec,mat> tmpMAD;
        vector<AUTODIFF_ELEMENT<simple,vec,mat> > tmpVMAD;
        tmpMAD.dim = nGRD;
        tmpMAD.value = 0.0;
        Resize(tmpMAD.grd,tmpMAD.dim);
        Clear(tmpMAD.grd);
        ComputeHessian = ComputeHess;
        tmpMAD.ComputeHessian = ComputeHess;
        if(ComputeHess){
            Resize(tmpMAD.hess,tmpMAD.dim,tmpMAD.dim);
            Clear(tmpMAD.hess);
        }
        for(int i = 1;i <= nRows;i++){
            for(int j = 1;j <= nCols;j++){
                tmpVMAD.push_back(tmpMAD);
            }
            theElements.push_back(tmpVMAD);
        }
    }
    MATRIX_AUTODIFF (INT r,INT c):ComputeHessian(true){
        nCols = c;
        nRows = r;
        theElements.resize(nCols);
    }
    MATRIX_AUTODIFF(const MATRIX_AUTODIFF& orig){
        nCols = orig.nCols;
        nRows = orig.nRows;
        AUTODIFF_ELEMENT<simple,vec,mat> tmpMAD;
        vector<AUTODIFF_ELEMENT<simple,vec,mat> > tmpVMAD;
        for(int i = 0;i < nRows;i++){
            for(int j = 0;j < nCols;j++){
                tmpMAD.value = orig.theElements[i][j].value;
                Resize(tmpMAD.grd,Dimension(orig.theElements[i][j].grd));
                tmpMAD.grd=orig.theElements[i][j].grd;
                Resize(tmpMAD.hess,RowDimension(orig.theElements[i][j].hess),ColDimension(orig.theElements[i][j].hess));
                tmpMAD.hess=orig.theElements[i][j].hess;
                tmpMAD.dim = orig.theElements[i][j].dim;
                tmpMAD.ComputeHessian = orig.theElements[i][j].ComputeHessian;
                tmpVMAD.push_back(tmpMAD);
            }
            theElements.push_back(tmpVMAD);
            tmpVMAD.clear();
        }
        ComputeHessian = orig.ComputeHessian;
    };
    MATRIX_AUTODIFF & operator =  (CONST MATRIX_AUTODIFF & orig){
        nCols = orig.nCols;
        nRows = orig.nRows;
        theElements = orig.theElements;
        ComputeHessian = orig.ComputeHessian;
    };
    virtual ~MATRIX_AUTODIFF<simple,vec,mat>(){
        theElements.clear();
        nCols = 0;
        nRows = 0;
    };
    AUTODIFF_ELEMENT<simple,vec,mat>& operator () (INT i, INT j)
    { 
        assert(i <= theElements.size());
        assert(j <= theElements[i-1].size());
        return theElements[i-1][j-1];
    }

    AUTODIFF_ELEMENT<simple,vec,mat> getGRDelement (INT i, INT j, INT k){
        return theElements[i-1][j-1](k-1);
    }
    friend INT RowDimension(CONST MATRIX_AUTODIFF& src){
        return src.nRows;
    }
    friend INT ColDimension(CONST MATRIX_AUTODIFF& src){
        return src.nCols;
    }
    MATRIX_AUTODIFF operator *  (MATRIX_AUTODIFF & src){
//   para linha de 1 até "numero de linhas de mat1" faça
//     para coluna de 1 até "numero de colunas de mat2" faça
//       acumula=0;
//       para i de 1 até "numero de colunas de mat1" faça
//         acumula=acumula+mat1[linha][i]*mat2[i][coluna];
//       fimpara;
//       mat3[linha][coluna]=acumula;
//     fimpara;
//   fimpara;
        MATRIX_AUTODIFF out(nRows,src.nCols);
        assert(nCols == src.nRows);
        AUTODIFF_ELEMENT<simple,vec,mat> acumula(src(1,1).dim,src.ComputeHessian);
        vector<AUTODIFF_ELEMENT<simple,vec,mat> > tmpEl;
        for(int row = 1;row <= nRows;row++){
            for(INT col = 1;col <= src.nCols;col++){
                Clear(acumula);
                for(INT i = 1;i <= nCols;i++){
                    acumula = acumula+(*this)(row,i)*src(i,col);
                }
                tmpEl.push_back(acumula);
            }
            out.theElements.push_back(tmpEl);
            tmpEl.clear();
        }
        out.ComputeHessian = ComputeHessian;
        return out;
    }
    MATRIX_AUTODIFF operator *  (CONST INTERVAL_AUTODIFF & src){
//   para linha de 1 até "numero de linhas de mat1" faça
//     para coluna de 1 até "numero de colunas de mat2" faça
//       acumula=0;
//       para i de 1 até "numero de colunas de mat1" faça
//         acumula=acumula+mat1[linha][i]*mat2[i][coluna];
//       fimpara;
//       mat3[linha][coluna]=acumula;
//     fimpara;
//   fimpara;
        MATRIX_AUTODIFF out(nRows,1);
        assert(nCols == Dimension(src));
        AUTODIFF_ELEMENT<simple,vec,mat> acumula(Dimension(src),src.ComputeHessian);
        vector<AUTODIFF_ELEMENT<simple,vec,mat> > tmpEl;
        for(int row = 1;row <= nRows;row++){
            Clear(acumula);
            for(INT i = 1;i <= nCols;i++){
                acumula = acumula+(*this)(row,i)*src(i);
            }
            tmpEl.push_back(acumula);
            out.theElements.push_back(tmpEl);
            tmpEl.clear();
        }
        out.ComputeHessian = ComputeHessian;
        return out;
    }
    MATRIX_AUTODIFF operator -  (CONST MATRIX_AUTODIFF& s1){
        MATRIX_AUTODIFF out(nRows,nCols,theElements[0][0].dim,theElements[0][0].ComputeHessian);
        assert(nRows == s1.nRows || nCols == s1.nCols);
        for(int i = 1;i <= nRows;i++)
            for(int j = 1;j <= nCols;j++)
                out(i,j)=(*this)(i,j)+s1(i,j);
        return out;
    }
    MATRIX_AUTODIFF operator -  (CONST INTERVAL_AUTODIFF& s1){
        MATRIX_AUTODIFF out(nRows,1,theElements[0][0].dim,theElements[0][0].ComputeHessian);
        assert(nRows == Dimension(s1) || nCols == 1);
        for(int i = 1;i <= nRows;i++)
                out(i,1)=(*this)(i,1)-s1(i);
        return out;
    }
    MATRIX_AUTODIFF operator -  (CONST vec& s1){
        MATRIX_AUTODIFF out;
        assert(nRows == Dimension(s1) || nCols == 1);
        out.ComputeHessian = ComputeHessian;
        out.nCols = nCols;
        out.nRows = nRows;
        out.theElements = theElements;
        for(int i = 1;i <= nRows;i++)
                out(i,1).value=theElements[i-1][0].value-s1(i);
        return out;
    }
    MATRIX_AUTODIFF operator -  (){
        MATRIX_AUTODIFF<simple,vec,mat> h(nRows,nCols,theElements[0][0].dim,ComputeHessian);
        for(int i = 0;i < theElements.size();i++){
            for(int j = 0;j < theElements[i].size();j++){
                h.theElements[i][j].value = -theElements[i][j].value;
                h.theElements[i][j].grd = -theElements[i][j].grd;
                if(ComputeHessian)h.theElements[i][j].hess = -theElements[i][j].hess;
                h.theElements[i][j].dim = theElements[i][j].dim;
            }
        }
        return h;
    }
    template<class s,class v,class m>
    friend ostream & operator << (ostream & os,CONST MATRIX_AUTODIFF<s,v,m>& src)
    {
        os << '{';
        for (int i = 0; i < src.nRows; i++) {
            for(int j = 0;j < src.nCols;j++){
                os << "ftk=(" << src.theElements[i][j].value << ")" << endl;
                if(Dimension(src.theElements[i][j].grd) != 0)
                    os << "gtk=(" << src.theElements[i][j].grd << ")" << endl;
                if(src.ComputeHessian)
                    if(RowDimension(INTERVAL_MATRIX(src.theElements[i][j].hess)) != 0 && ColDimension(INTERVAL_MATRIX(src.theElements[i][j].hess)) != 0)
                        os << "htk=(" << src.theElements[i][j].hess << ")" << endl;
            }
        }
        return os << '}';
    }
    template<class s,class v,class m>
    friend INTERVAL_AUTODIFF MATRIX_AUTODIFF2INTERVAL_AUTODIFF(CONST MATRIX_AUTODIFF<s,v,m>& src){
        AUTODIFF_ELEMENT<s,v,m> sum(src.theElements[0][0].dim);
        INTERVAL_AUTODIFF out;
        Clear(sum);
        for(int i = 1;i <= src.theElements.size();i++){
            for(int j = 1;j <= src.theElements[i].size();j++){
                sum = sum+src.theElements[i][j];
            }
        }
        out = MATRIX_AD_EL2INTERVAL_AD(sum);
        return out;
    }
    template<class s,class v,class m>
    friend MATRIX_AUTODIFF<s,v,m> INTERVAL_AD2MATRIX_AD(INT r, INT c, CONST INTERVAL_AUTODIFF& src){
        MATRIX_AUTODIFF<s,v,m> out(r,c,Dimension(src));
        for(INT i = 1;i <= r;i++){
            for(INT j = 1;j <= c;j++){
                out(i,j).value = src.fkt();
                out(i,j).grd = src.grd();
                if(src.ComputeHessian)
                    out(i,j).hess = src.hessian();
                out(i,j).dim = Dimension(src);
                out(i,j).ComputeHessian = src.ComputeHessian;
            }
        }
    }
    template<class s,class v,class m>
    friend MATRIX_AUTODIFF<s,v,m> Eul2rtmAD(CONST INTERVAL_AUTODIFF& src)
    {
        MATRIX_AUTODIFF<s,v,m> out(3,3,Dimension(src),src.ComputeHessian);
        INTERVAL_AUTODIFF sa(Dimension(src),src.ComputeHessian),ca(Dimension(src),src.ComputeHessian);
        sa = Sin(src(1)); ca = Cos(src(1));
        INTERVAL_AUTODIFF sb(Dimension(src),src.ComputeHessian),cb(Dimension(src),src.ComputeHessian);
        sb = Sin(src(2)); cb = Cos(src(2));
        INTERVAL_AUTODIFF sc(Dimension(src),src.ComputeHessian),cc(Dimension(src),src.ComputeHessian);
        sc = Sin(src(3)); cc = Cos(src(3));
        MATRIX_AUTODIFF<s,v,m> rz(3,3,Dimension(src),src.ComputeHessian);
//        rz = INTERVAL_MATRIX(3,3,{ -cc,            sc,            Constant::ZERO,
//                           -sc,            -cc,            Constant::ZERO,
//                           Constant::ZERO, Constant::ZERO,Constant::UM});
        rz(1,1) = -cc; 
        rz(1,2)=sc;
        rz(2,1) = -sc; rz(2,2)=-cc;
        rz(3,3).value = 1.0;
        MATRIX_AUTODIFF<s,v,m> ry(3,3,Dimension(src),src.ComputeHessian);
//        ry = INTERVAL_MATRIX(3,3,{-cb,            Constant::ZERO,sb,
//                                  Constant::ZERO,Constant::UM,  Constant::ZERO,
//                                  -sb,           Constant::ZERO,-cb});
        ry(1,1)=-cb;ry(1,3)=sb;
        ry(2,2).value=1.0;
        ry(3,1) = -sb;ry(3,3)=-cb;
        MATRIX_AUTODIFF<s,v,m> rx(3,3,Dimension(src),src.ComputeHessian);
//        rx = INTERVAL_MATRIX(3,3,{Constant::UM,Constant::ZERO,Constant::ZERO,
//                                  Constant::ZERO,-ca, sa,
//                                  Constant::ZERO,-sa, -ca});
        rx(1,1).value = 1.0;
        rx(2,2) = -ca;rx(2,3)=sa;
        rx(3,2) = -sa;rx(3,3)=-ca;
        out = rx*ry*rz;
        return out;
    }
    /*Função utilizada para determinar a matriz de rotação
     com o parâmetro de entrada sendo uma matriz do tipo
     MATRIX_AUTODIFF com tamanho 1x3.*/
    template<class s,class v,class m>
    friend MATRIX_AUTODIFF<s,v,m> Eul2rtmAD(MATRIX_AUTODIFF<s,v,m> src)
    {
        MATRIX_AUTODIFF<s,v,m> out(3,3,src(1,1).dim,src.ComputeHessian);
        MATRIX_AUTODIFF<s,v,m> sa(1,1,src(1,1).dim,src.ComputeHessian),ca(1,1,src(1,1).dim,src.ComputeHessian);
        sa(1,1) = Sin(src(1,1)); ca(1,1) = Cos(src(1,1));
        MATRIX_AUTODIFF<s,v,m> sb(1,1,src(1,1).dim,src.ComputeHessian),cb(1,1,src(1,1).dim,src.ComputeHessian);
        sb(1,1) = Sin(src(1,2)); cb(1,1) = Cos(src(1,2));
        MATRIX_AUTODIFF<s,v,m> sc(1,1,src(1,1).dim,src.ComputeHessian),cc(1,1,src(1,1).dim,src.ComputeHessian);
        sc(1,1) = Sin(src(1,3)); cc(1,1) = Cos(src(1,3));
        MATRIX_AUTODIFF<s,v,m> rz(3,3,src(1,1).dim,src.ComputeHessian);
//        rz = INTERVAL_MATRIX(3,3,{ -cc,            sc,            Constant::ZERO,
//                           -sc,            -cc,            Constant::ZERO,
//                           Constant::ZERO, Constant::ZERO,Constant::UM});
        rz(1,1) = -cc(1,1); 
        rz(1,2)=sc(1,1);
        rz(2,1) = -sc(1,1); rz(2,2)=-cc(1,1);
        rz(3,3).value = 1.0;
        MATRIX_AUTODIFF<s,v,m> ry(3,3,src(1,1).dim,src.ComputeHessian);
//        ry = INTERVAL_MATRIX(3,3,{-cb,            Constant::ZERO,sb,
//                                  Constant::ZERO,Constant::UM,  Constant::ZERO,
//                                  -sb,           Constant::ZERO,-cb});
        ry(1,1)=-cb(1,1);ry(1,3)=sb(1,1);
        ry(2,2).value=1.0;
        ry(3,1) = -sb(1,1);ry(3,3)=-cb(1,1);
        MATRIX_AUTODIFF<s,v,m> rx(3,3,src(1,1).dim,src.ComputeHessian);
//        rx = INTERVAL_MATRIX(3,3,{Constant::UM,Constant::ZERO,Constant::ZERO,
//                                  Constant::ZERO,-ca, sa,
//                                  Constant::ZERO,-sa, -ca});
        rx(1,1).value = 1.0;
        rx(2,2) = -ca(1,1);rx(2,3)=sa(1,1);
        rx(3,2) = -sa(1,1);rx(3,3)=-ca(1,1);
        out = rx*ry*rz;
        return out;
    }
    template<class s,class v,class m>
    friend MATRIX_AUTODIFF<s,v,m> rtm2EulAD(CONST MATRIX_AUTODIFF<s,v,m>& r){
        MATRIX_AUTODIFF Theta(3,1);
        Theta(2) = ArcTan2(r(3,2),r(3,3));
    }
    template<class s,class v,class m>
    friend MATRIX_AUTODIFF<s,v,m> Abs (CONST MATRIX_AUTODIFF<s,v,m> & src)
    {
//        MATRIX_AUTODIFF out(src.nCols,src.nRows,Dimension(src(1,1)));
//        for(int i = 1;i <= src.nRows;i++)
//            for(int j = 1;j <= src.nCols;j++)
//                out(i,j)=Abs(src(i,j));
//        return out;
    }
private:

};
template<class s,class v,class m>
MATRIX_AUTODIFF<s,v,m> Eul2rtmAD(CONST INTERVAL_AUTODIFF& src);

template<class s,class v,class m>
MATRIX_AUTODIFF<s,v,m> Eul2rtmAD(MATRIX_AUTODIFF<s,v,m> src);

template<class s,class v,class m>
ostream & operator << (ostream & os,CONST MATRIX_AUTODIFF<s,v,m>& src);

/*Calcula o valor absoluto de cada elemento
 da matriz de acordo com a álgebra intervalar.*/
template<class s,class v,class m>
MATRIX_AUTODIFF<s,v,m> Abs (CONST MATRIX_AUTODIFF<s,v,m> & g);

template<class s,class v,class m>
VOID Resize(MATRIX_AUTODIFF<s,v,m>& src,INT r,INT c,INT nGRD,bool ComputeHess){
    CheckMatrixRange (r, c);
    if ((r * c) && (src.nRows == r) && (src.nCols == c)) return;
    if (!src.theElements.empty()) src.theElements.clear();
    src.nRows = r; src.nCols = c;
    if (r * c != 0) {
        AUTODIFF_ELEMENT<s,v,m> tmpMAD;
        vector<AUTODIFF_ELEMENT<s,v,m> > tmpVMAD;
        tmpMAD.dim = nGRD;
        tmpMAD.value = 0.0;
        Resize(tmpMAD.grd,tmpMAD.dim);
        Clear(tmpMAD.grd);
        src.ComputeHessian = ComputeHess;
        tmpMAD.ComputeHessian = ComputeHess;
        if(ComputeHess){
            Resize(tmpMAD.hess,tmpMAD.dim,tmpMAD.dim);
            Clear(tmpMAD.hess);
        }
        for(int i = 1;i <= r;i++){
            for(int j = 1;j <= c;j++){
                tmpVMAD.push_back(tmpMAD);
            }
            src.theElements.push_back(tmpVMAD);
        }
    }
}
/*Define o tipo padrão para matriz de autodiferenciação
 cujos elementos são baseados em intervalos*/
typedef MATRIX_AUTODIFF<INTERVAL,INTERVAL_VECTOR,INTERVAL_MATRIX> MATRIX_AUTODIFF_INTERVAL ;
/*Define o tipo padrão para matriz de autodiferenciação
 cujos elementos são baseados em números reais*/
typedef MATRIX_AUTODIFF<REAL,VECTOR,MATRIX> MATRIX_AUTODIFF_REAL ;
/*Define o tipo padrão para o elementos da 
 matriz de autodiferenciação baseados intervalos*/
typedef AUTODIFF_ELEMENT<INTERVAL,INTERVAL_VECTOR,INTERVAL_MATRIX> AUTODIFF_ELEMENT_INTERVAL ;
/*Define o tipo padrão para o elementos da 
 matriz de autodiferenciação baseados em números
 reais.*/
typedef AUTODIFF_ELEMENT<REAL,VECTOR,MATRIX> AUTODIFF_ELEMENT_REAL ;

template<class s,class v,class m>
INT RowDimension(CONST MATRIX_AUTODIFF<s,v,m>& src);

template<class s,class v,class m>
INT ColDimension(CONST MATRIX_AUTODIFF<s,v,m>& src);

#endif /* MATRIX_AUTODIFF_HPP */

