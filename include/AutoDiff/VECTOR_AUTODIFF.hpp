/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VECTOR_AUTODIFF.hpp
 * Author: darlan
 *
 * Created on 8 de Abril de 2016, 08:54
 */
#include <assert.h>
#include <AutoDiff/IntervalAutoDiff.h>
#include <AutoDiff/AUTODIFF_ELEMENT.hpp>
#include <IntervalMatrix.h>
#include <Vector.h>
#include <Interval.h>
#include <Functions.h>

#ifndef VECTOR_AUTODIFF_HPP
#define VECTOR_AUTODIFF_HPP

template<class simple,class vec,class mat>
class VECTOR_AUTODIFF {
public:
    /*Vector de vetor que contém os 
     elementos da matriz.*/
    vector<AUTODIFF_ELEMENT<simple,vec,mat> >theElements;
    /*Número de linhas da matriz.*/
    INT nRows;
    /*Indica se a matriz Hessiana deverá
     ser calculada.*/
    bool ComputeHessian;
    /*Inicializa a matriz de autodiferenciação
     com todos os elementos vazios e determina
     o cálculo da matriz Hessiana.*/
    VECTOR_AUTODIFF (){
        nRows = 0;
        ComputeHessian = true;
    };
    /*Inicializa a matriz de autodiferenciação
     com todos os elementos vazios e determina
     o cálculo da matriz Hessiana.*/
    VECTOR_AUTODIFF (bool cptHess){
        nRows = 0;
        ComputeHessian = cptHess;
    };
    /*Inicializa a matriz de autodiferenciação
     com todos os elementos com valores iguais
     a matriz de entrada e gradiente e hessiana
     vazios e tamanho igual a zero.*/    
    VECTOR_AUTODIFF (CONST vec& values):ComputeHessian(true){
        nRows = (INT)RowDimension(values);
        AUTODIFF_ELEMENT<simple,vec,mat> tmpVAD;
        for(int i = 1;i <= nRows;i++){
                tmpVAD.value = values(i);
                theElements.push_back(tmpVAD);
        }
    }
    /*Inicializa a matriz de autodiferenciação
     com todos os elementos com valores iguais
     a matriz de entrada e gradiente e hessiana
     de tamanhos iguais a diffsizes elemento por
     * elemento e valores iguais a zero.*/    
    VECTOR_AUTODIFF (CONST vec& values,CONST VECTOR& diffsizes):ComputeHessian(true){
        nRows = (INT)RowDimension(values);
        AUTODIFF_ELEMENT<simple,vec,mat> tmpVAD;
        for(int i = 1;i <= nRows;i++){
            tmpVAD.value = values(i);
            Resize(tmpVAD.grd,diffsizes(i));
            Initialize(tmpVAD.grd,0.0);
            Initialize(tmpVAD.hess,0.0);
            Resize(tmpVAD.hess,diffsizes(i),diffsizes(i));
            theElements.push_back(tmpVAD);
        }
    }
    /*Inicializa a matriz de autodiferenciação
     com todos os elementos com valores iguais
     a matriz de entrada e gradiente e hessiana
     de tamanhos iguais a diffsizes elemento por
     * elemento e valores iguais a zero.*/    
    VECTOR_AUTODIFF (INT r, CONST vec& values,INT dim,bool CompHess){
        nRows = r;
        ComputeHessian = CompHess;
        AUTODIFF_ELEMENT<simple,vec,mat> tmpVAD;
        for(int i = 1;i <= nRows;i++){
                tmpVAD.value = values(i);
                Resize(tmpVAD.grd,dim);
                Initialize(tmpVAD.grd,1.0);
                tmpVAD.ComputeHessian = CompHess;
                tmpVAD.dim = dim;
                if(CompHess){
                    Resize(tmpVAD.hess,dim,dim);
                    Initialize(tmpVAD.hess,0.0);
                }
                theElements.push_back(tmpVAD);
        }
    }
    /*Inicializa a matriz de autodiferenciação
     com todos os elementos com valores iguais
     a matriz de entrada e gradiente e hessiana
     de tamanhos iguais a diffsizes elemento por
     * elemento e valores iguais a zero.*/    
    VECTOR_AUTODIFF (CONST vec& values,CONST vec& inigrd,CONST mat& inihess):ComputeHessian(true){
        nRows = RowDimension(values);
        AUTODIFF_ELEMENT<simple,vec,mat> tmpVAD;
        for(int i = 1;i <= nRows;i++){
            tmpVAD.value = values(i);
            tmpVAD.grd=inigrd;
            tmpVAD.hess=inihess;
            theElements.push_back(tmpVAD);
        }
    }
    /*Inicializa a matriz de autodiferenciação
     com todos os elementos com valores iguais
     a matriz de entrada e gradiente e hessiana
     iguais aos elementos das matrizes inigrd e
     inihess respectivamente.*/    
    VECTOR_AUTODIFF (CONST vec& values,CONST vector<vec>& inigrd,CONST vector<mat>& inihess):ComputeHessian(true){
        nRows = RowDimension(values);
        AUTODIFF_ELEMENT<simple,vec,mat> tmpVAD;
        for(int i = 1;i <= nRows;i++){
                tmpVAD.value = values(i);
                tmpVAD.grd=inigrd[i];
                tmpVAD.hess=inihess[i];
                theElements.push_back(tmpVAD);
        }
    }
    /*Inicializa a matriz de autodiferenciação
     com o número de linhas iguais a r e 
     colunas iguais c. O gradiente e hessiana
     iguais aos elementos das matrizes nos vetores 
     inigrd e inihess respectivamente.*/    
    VECTOR_AUTODIFF (INT r,CONST vector<vec>& inigrd,CONST vector<mat>& inihess):ComputeHessian(true){
        nRows = r;
        AUTODIFF_ELEMENT<simple,vec,mat> tmpVAD;
        for(int i = 1;i <= nRows;i++){
                tmpVAD.value = 0.0;
                tmpVAD.grd=inigrd[i];
                tmpVAD.hess=inihess[i];
                theElements.push_back(tmpVAD);
        }
    }
    /*Inicializa a matriz de autodiferenciação
     com o número de linhas iguais a r e 
     colunas iguais c. O gradiente iguais aos 
     elementos das matrizes nos vetores 
     inigrd e a hessiana igual a zero.*/    
    VECTOR_AUTODIFF (INT r,CONST vector<vec>& inigrd,bool CompHess){
        nRows = r;
        ComputeHessian = CompHess;
        AUTODIFF_ELEMENT<simple,vec,mat> tmpVAD;
        for(int i = 1;i <= nRows;i++){
                tmpVAD.dim = Dimension(inigrd[i]);
                tmpVAD.value = 0.0;
                Resize(tmpVAD.grd,tmpVAD.dim);
                tmpVAD.grd=inigrd[i];
                tmpVAD.ComputeHessian = CompHess;
                if(CompHess){
                    Resize(tmpVAD.hess,tmpVAD.dim,tmpVAD.dim);
                    Clear(tmpVAD.hess);
                }
                theElements.push_back(tmpVAD);
        }
    }
    /*Inicializa a matriz de autodiferenciação
     com o número de linhas iguais a r e 
     colunas iguais c. O gradiente iguais aos 
     elementos das matrizes nos vetores 
     inigrd e a hessiana igual a zero.*/    
    VECTOR_AUTODIFF (INT r,CONST INTERVAL_AUTODIFF& srcIAD){
        nRows = r;
        ComputeHessian = srcIAD.ComputeHessian;
        AUTODIFF_ELEMENT<simple,vec,mat> tmpVAD;
        tmpVAD = srcIAD;
        for(int i = 1;i <= nRows;i++){
                theElements.push_back(tmpVAD);
        }
    }
    VECTOR_AUTODIFF (INT r,INT nGRD,bool ComputeHess){
        nRows = r;
        AUTODIFF_ELEMENT<simple,vec,mat> tmpVAD;
        tmpVAD.dim = nGRD;
        tmpVAD.value = 0.0;
        Resize(tmpVAD.grd,tmpVAD.dim);
        Clear(tmpVAD.grd);
        ComputeHessian = ComputeHess;
        tmpVAD.ComputeHessian = ComputeHess;
        if(ComputeHess){
            Resize(tmpVAD.hess,tmpVAD.dim,tmpVAD.dim);
            Clear(tmpVAD.hess);
        }
        for(int i = 1;i <= nRows;i++){
                theElements.push_back(tmpVAD);
        }
    }
    VECTOR_AUTODIFF (INT r):ComputeHessian(true){
        nRows = r;
        theElements.resize(nRows);
    }
    VECTOR_AUTODIFF(const VECTOR_AUTODIFF& orig){
        nRows = orig.nRows;
        AUTODIFF_ELEMENT<simple,vec,mat> tmpVAD;
        for(int i = 0;i < nRows;i++){
                tmpVAD.value = orig.theElements[i].value;
                Resize(tmpVAD.grd,Dimension(orig.theElements[i].grd));
                tmpVAD.grd=orig.theElements[i].grd;
                Resize(tmpVAD.hess,RowDimension(orig.theElements[i].hess),ColDimension(orig.theElements[i].hess));
                tmpVAD.hess=orig.theElements[i].hess;
                tmpVAD.dim = orig.theElements[i].dim;
                tmpVAD.ComputeHessian = orig.theElements[i].ComputeHessian;
                theElements.push_back(tmpVAD);
        }
        ComputeHessian = orig.ComputeHessian;
    };
    VECTOR_AUTODIFF & operator =  (CONST VECTOR_AUTODIFF & orig){
        nRows = orig.nRows;
        theElements = orig.theElements;
        ComputeHessian = orig.ComputeHessian;
    };
    virtual ~VECTOR_AUTODIFF<simple,vec,mat>(){
        theElements.clear();
        nRows = 0;
    };
    AUTODIFF_ELEMENT<simple,vec,mat>& operator ()  (INT i)
    { 
        assert(i <= theElements.size());
        return theElements[i-1];
    }
    AUTODIFF_ELEMENT<simple,vec,mat> operator ()  (INT i) CONST
    { 
        assert(i <= theElements.size());
        return theElements[i-1];
    }

    AUTODIFF_ELEMENT<simple,vec,mat> getGRDelement (INT i, INT k){
        return theElements[i-1](k-1);
    }
    INT rows( ){
        return nRows;
    }
    friend INT RowDimension(CONST VECTOR_AUTODIFF& src){
        return src.nRows;
    }
    AUTODIFF_ELEMENT<simple,vec,mat> operator *  (VECTOR_AUTODIFF & src){
        assert(nRows == src.nRows);
        AUTODIFF_ELEMENT<simple,vec,mat> out(src(1).dim,src.ComputeHessian);
        Clear(out);
        for(INT i = 1;i <= nRows;i++){
            out = out+(*this)(i)*src(i);
        }
        out.ComputeHessian = ComputeHessian;
        return out;
    }
    VECTOR_AUTODIFF operator *  (CONST INTERVAL_AUTODIFF & src){
        AUTODIFF_ELEMENT<simple,vec,mat> out(Dimension(src),src.ComputeHessian);
            Clear(out);
            for(INT i = 1;i <= nRows;i++){
                out = out+(*this)(i)*src(i);
            }
        out.ComputeHessian = ComputeHessian;
        return out;
    }
    template<class s,class v,class m>
    friend VECTOR_AUTODIFF operator *  (CONST REAL a,CONST VECTOR_AUTODIFF<s,v,m> & src){
        VECTOR_AUTODIFF<s,v,m> out(src);
        for(INT i = 1;i <= src.nRows;i++){
            out(i) = a*out(i);
        }
        out.ComputeHessian = src.ComputeHessian;
        return out;
    }
    template<class s,class v,class m>
    friend VECTOR_AUTODIFF operator *  (CONST VECTOR_AUTODIFF<s,v,m> & src,CONST REAL a){
        return a*src;
    }

    VECTOR_AUTODIFF operator -  (CONST VECTOR_AUTODIFF& s1){
        VECTOR_AUTODIFF out(nRows,theElements[0].dim,theElements[0].ComputeHessian);
        assert(nRows == s1.nRows);
        for(int i = 1;i <= nRows;i++)
                out(i)=(*this)(i)+s1(i);
        return out;
    }
    VECTOR_AUTODIFF operator -  (CONST INTERVAL_AUTODIFF& s1){
        VECTOR_AUTODIFF out(nRows,1,theElements[0][0].dim,theElements[0][0].ComputeHessian);
        assert(nRows == Dimension(s1));
        for(int i = 1;i <= nRows;i++)
                out(i)=(*this)(i)-s1(i);
        return out;
    }
    VECTOR_AUTODIFF operator -  (CONST vec& s1){
        VECTOR_AUTODIFF out;
        assert(nRows == Dimension(s1));
        out.ComputeHessian = ComputeHessian;
        out.nRows = nRows;
        out.theElements = theElements;
        for(int i = 1;i <= nRows;i++)
                out(i,1).value=theElements[i-1].value-s1(i);
        return out;
    }
    VECTOR_AUTODIFF operator -  (){
        VECTOR_AUTODIFF<simple,vec,mat> h(nRows,theElements[0].dim,ComputeHessian);
        for(int i = 0;i < theElements.size();i++){
                h.theElements[i].value = -theElements[i].value;
                h.theElements[i].grd = -theElements[i].grd;
                if(ComputeHessian)h.theElements[i].hess = -theElements[i].hess;
                h.theElements[i].dim = theElements[i].dim;
        }
        return h;
    }
    VOID resize(INT r,INT nGRD,bool ComputeHess){
        if (!theElements.empty()) theElements.clear();
        nRows = r;
        if (r != 0) {
            AUTODIFF_ELEMENT<simple,vec,mat> tmpVAD;
            tmpVAD.dim = nGRD;
            tmpVAD.value = 0.0;
            Resize(tmpVAD.grd,tmpVAD.dim);
            Clear(tmpVAD.grd);
            ComputeHessian = ComputeHess;
            tmpVAD.ComputeHessian = ComputeHess;
            if(ComputeHess){
                Resize(tmpVAD.hess,tmpVAD.dim,tmpVAD.dim);
                Clear(tmpVAD.hess);
            }
            for(int i = 1;i <= r;i++){
                    theElements.push_back(tmpVAD);
            }
        }
    }
    template<class s,class v,class m>
    friend ostream & operator << (ostream & os,CONST VECTOR_AUTODIFF<s,v,m>& src)
    {
        os << '{';
        for (int i = 0; i < src.nRows; i++) {
                os << "ftk=(" << src.theElements[i].value << ")" << endl;
                if(Dimension(src.theElements[i].grd) != 0)
                    os << "gtk=(" << src.theElements[i].grd << ")" << endl;
                if(src.ComputeHessian)
                    if(RowDimension(INTERVAL_MATRIX(src.theElements[i].hess)) != 0 && ColDimension(INTERVAL_MATRIX(src.theElements[i].hess)) != 0)
                        os << "htk=(" << src.theElements[i].hess << ")" << endl;
        }
        return os << '}';
    }
    template<class s,class v,class m>
    friend INTERVAL_AUTODIFF VECTOR_AUTODIFF2INTERVAL_AUTODIFF(CONST VECTOR_AUTODIFF<s,v,m>& src){
        AUTODIFF_ELEMENT<s,v,m> sum(src.theElements[0].dim);
        INTERVAL_AUTODIFF out;
        Clear(sum);
        for(int i = 1;i <= src.theElements.size();i++){
                sum = sum+src.theElements[i];
        }
        out = VECTOR_AD_EL2INTERVAL_AD(sum);
        return out;
    }
    template<class s,class v,class m>
    friend VECTOR_AUTODIFF<s,v,m> INTERVAL_AD2VECTOR_AD(INT r, INT c, CONST INTERVAL_AUTODIFF& src){
        VECTOR_AUTODIFF<s,v,m> out(r,c,Dimension(src));
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
private:

};
template<class s,class v,class m>
ostream & operator << (ostream & os,CONST VECTOR_AUTODIFF<s,v,m>& src);

/*Define o tipo padrão para matriz de autodiferenciação
 cujos elementos são baseados em intervalos*/
typedef VECTOR_AUTODIFF<INTERVAL,INTERVAL_VECTOR,INTERVAL_MATRIX> VECTOR_AUTODIFF_INTERVAL ;
/*Define o tipo padrão para matriz de autodiferenciação
 cujos elementos são baseados em números reais*/
typedef VECTOR_AUTODIFF<REAL,VECTOR,MATRIX> VECTOR_AUTODIFF_REAL ;
/*Define o tipo padrão para o elementos da 
 matriz de autodiferenciação baseados intervalos*/
typedef AUTODIFF_ELEMENT<INTERVAL,INTERVAL_VECTOR,INTERVAL_MATRIX> AUTODIFF_ELEMENT_INTERVAL ;
/*Define o tipo padrão para o elementos da 
 matriz de autodiferenciação baseados em números
 reais.*/
typedef AUTODIFF_ELEMENT<REAL,VECTOR,MATRIX> AUTODIFF_ELEMENT_REAL ;

template<class s,class v,class m>
INT RowDimension(CONST VECTOR_AUTODIFF<s,v,m>& src);

#endif /* VECTOR_AUTODIFF_HPP */

