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
#include <IntervalMatrix.h>
#include <Vector.h>
#include <Interval.h>
#include <Functions.h>

#ifndef AUTODIFF_ELEMENT_HPP
#define AUTODIFF_ELEMENT_HPP

/*Classe que representa o elemento da matriz 
 de autodiferenciação. Os membros da classe
 da classe são:
 INTERVAL/REAL value -> valor da função em no ponto.
 INTERVAL_VECTOR/VECTOR grd -> Gradiente da função.
 INTERVAL_MATRIX/MATRIX hess -> Matriz hessiana*/
template<class simple,class vec,class mat>
class AUTODIFF_ELEMENT{
public:
    /*Valor da função no ponto.*/
    simple value;
    /*Valor do gradiente no ponto*/
    vec grd;
    /*Matriz hessiana no ponto*/
    mat hess;
    /*Dimensão do vetor gradiente*/
    INT dim;
    /*Determina se a matriz Hessiana deverá ser
     calculada. O padrão é sim (true)
     caso necessário deve ser modificado explicitamente*/
    bool ComputeHessian;
    /*Inicializa o elemento com grd e hess com tamanhos iguais
     a zero.*/
    AUTODIFF_ELEMENT():ComputeHessian(false){
        grd = INTERVAL_VECTOR( );
        hess = INTERVAL_MATRIX( );
        dim = 0;
    };
    /*Inicializa o elemento com o vetor de gradiente
     com tamanho igual a n e a matriz hessiana com
     o tamanho igual a nxn*/
    AUTODIFF_ELEMENT(INT n,bool CompHess):value(0){
        Resize(grd,n);
        Clear(grd);
        if(CompHess){
            Resize(hess,n,n);
            Clear(hess);
        }
        ComputeHessian = CompHess;
        dim = n;
    };
    AUTODIFF_ELEMENT(CONST AUTODIFF_ELEMENT & src){
        ComputeHessian = src.ComputeHessian;
        grd = src.grd;
        if(ComputeHessian)
            hess = src.hess;
        value = src.value;
        dim = src.dim;
    }
    AUTODIFF_ELEMENT & operator =  (CONST AUTODIFF_ELEMENT & src){
        Resize(grd,Dimension(src.grd));
        grd = src.grd;
        if(src.ComputeHessian){
            Resize(hess,RowDimension(src.hess),ColDimension(src.hess));
            hess = src.hess;
        }
        value = src.value;
        ComputeHessian = src.ComputeHessian;
        dim = src.dim;
    }
    AUTODIFF_ELEMENT & operator =  (CONST INTERVAL_AUTODIFF & src){
        Resize(grd,Dimension(src.grd()));
        grd = src.grd();
        if(src.ComputeHessian){
            Resize(hess,RowDimension(src.hessian()),ColDimension(src.hessian()));
            hess = src.hessian();
        }
        value = src.fkt();
        ComputeHessian = src.ComputeHessian;
        dim = Dimension(src);
    }
    virtual ~AUTODIFF_ELEMENT<simple,vec,mat>(){
        grd.Delete();
        hess.Delete();
    }
    mat TransposedMul(CONST vec& a,CONST vec& b){
        // returns a * b^T
        INT aDim = Dimension (a);
        INT bDim = Dimension (b);
        INT i;
        mat t(aDim, bDim);

        for (i = 1; i <= aDim; i++) SetRow (t, i, a(i) * b);
        return t;
    }
    AUTODIFF_ELEMENT operator () (INT i){
        AUTODIFF_ELEMENT h(dim,ComputeHessian);
        h.value = grd(i);
        Clear(h.grd); h.grd(i) = 1.0;
        if (ComputeHessian) Clear(h.hess);
        return h;
    }
    AUTODIFF_ELEMENT operator () (INT i) CONST{
        AUTODIFF_ELEMENT h(dim,ComputeHessian);
        h.value = grd(i);
        Clear(h.grd); h.grd(i) = 1.0;
        if (ComputeHessian) Clear(h.hess);
        return h;
    }
    template<class s,class v,class m>
    friend INT Dimension(CONST AUTODIFF_ELEMENT<s,v,m>& src){
        return src.dim;
    }
    template<class s,class v,class m>
    friend VOID Clear(AUTODIFF_ELEMENT<s,v,m>& src){
        src.value = 0;
        Clear(src.grd);
        Clear(src.hess);
    }
//    friend INT Dimension(CONST INTERVAL_VECTOR& src){
//        return src.nElements;
//    }
    template<class s,class v,class m>
    friend ostream & operator << (ostream & os,CONST AUTODIFF_ELEMENT<s,v,m>& src)
    {
        os << '{';
        os << "ftk=(" << src.value << ")" << endl;
        if(Dimension(src.grd) != 0)
            os << "gtk=(" << src.grd << ")" << endl;
        if(RowDimension(src.hess) != 0 && ColDimension(src.hess) != 0)
            os << "htk=(" << src.hess << ")" << endl;
        return os << '}';
    }
    AUTODIFF_ELEMENT operator *  (CONST AUTODIFF_ELEMENT & m2){
        AUTODIFF_ELEMENT h(dim,ComputeHessian);
        h.value = value * m2.value;
        h.grd = m2.value * grd + value * m2.grd;
        if (ComputeHessian && m2.ComputeHessian) {
          h.hess = value * m2.hess
            + TransposedMul (grd, m2.grd)
            + TransposedMul (m2.grd, grd)
            + m2.value * hess;
          h.ComputeHessian = TRUE;
        }
        return h;
    }
    AUTODIFF_ELEMENT operator *  (CONST INTERVAL_AUTODIFF & m2){
        AUTODIFF_ELEMENT h(dim,ComputeHessian);
        h.value = value * m2.fkt();
        h.grd = m2.fkt() * grd + value * m2.grd();
        if (ComputeHessian && m2.ComputeHessian) {
          h.hess = value * m2.hessian()
            + TransposedMul (grd, m2.grd())
            + TransposedMul (m2.grd(), grd)
            + m2.fkt() * hess;
          h.ComputeHessian = TRUE;
        }
        return h;
    }
    AUTODIFF_ELEMENT operator * (REAL a)
    {
        AUTODIFF_ELEMENT h(dim,ComputeHessian);

        h.value = a * value;
        h.grd = a * grd;
        if (ComputeHessian) {
            h.hess = a * hess;
            h.ComputeHessian = TRUE;
        }
        return h;
    }
    template<class s,class v,class m>
    friend AUTODIFF_ELEMENT<s,v,m> operator * (REAL a,CONST AUTODIFF_ELEMENT<s,v,m>& m2){
        AUTODIFF_ELEMENT h(m2.dim,m2.ComputeHessian);

        h.value = a * m2.value;
        h.grd = a * m2.grd;
        if (m2.ComputeHessian) {
            h.hess = a * m2.hess;
            h.ComputeHessian = TRUE;
        }
        return h;
    }
    AUTODIFF_ELEMENT operator * (simple a)
    {
        AUTODIFF_ELEMENT h(dim,ComputeHessian);

        h.value = a * value;
        h.grd = a * grd;
        if (ComputeHessian) {
            h.hess = a * hess;
            h.ComputeHessian = TRUE;
        }
        return h;
    }
    template<class s,class v,class m>
    friend AUTODIFF_ELEMENT<s,v,m> operator * (s a,CONST AUTODIFF_ELEMENT<s,v,m>& m2){
        return m2*a;
    }
    AUTODIFF_ELEMENT operator /  (CONST AUTODIFF_ELEMENT & d2){
        AUTODIFF_ELEMENT h(dim,ComputeHessian);

        h.value = value / d2.value;
        h.grd = grd / d2.value - value * d2.grd / Sqr(d2.value);
        if (ComputeHessian && d2.ComputeHessian) {
            h.hess = (hess
		   - h.TransposedMul (h.grd, d2.grd)
		   - h.TransposedMul (d2.grd, h.grd)
		   - h.value * d2.hess) / d2.value;
            h.ComputeHessian = TRUE;
        }
        return h;
    }
    AUTODIFF_ELEMENT operator /  (CONST INTERVAL_AUTODIFF & d2){
        AUTODIFF_ELEMENT h(dim,ComputeHessian);

        h.value = value / d2.fkt();
        h.grd = grd / d2.fkt() - value * d2.grd() / Sqr(d2.fkt());
        if (ComputeHessian && d2.ComputeHessian) {
            h.hess = (hess
		   - h.TransposedMul (h.grd, d2.grd())
		   - h.TransposedMul (d2.grd, h.grd())
		   - h.value * d2.hessian()) / d2.fkt();
            h.ComputeHessian = TRUE;
        }
        return h;
    }
    AUTODIFF_ELEMENT operator / (REAL a)
    {
        AUTODIFF_ELEMENT h(dim,ComputeHessian);

        h.value = value / a;
        h.grd = grd / a;
        if (ComputeHessian) {
            h.hess = hess / a;
            h.ComputeHessian = TRUE;
        }
        return h;
    }
    template<class s,class v,class m>
    friend AUTODIFF_ELEMENT<s,v,m> operator / (REAL a,CONST AUTODIFF_ELEMENT<s,v,m>& d2){
        AUTODIFF_ELEMENT h(d2.dim,d2.ComputeHessian);

        h.value = a / d2.value;
        h.grd = -a * d2.grd / Sqr(d2.value);
        if (d2.ComputeHessian) {
            h.hess = (h.TransposedMul (h.grd, d2.grd)
		   + h.TransposedMul (d2.grd, h.grd)
		   + h.value * d2.hess) / (-d2.value);
            h.ComputeHessian = TRUE;
        }
        return h;
    }
    AUTODIFF_ELEMENT operator / (simple a)
    {
        AUTODIFF_ELEMENT h(dim,ComputeHessian);

        h.value = value / a;
        h.grd = grd / a;
        if (ComputeHessian) {
            h.hess = hess / a;
            h.ComputeHessian = TRUE;
        }
        return h;
    }
    template<class s,class v,class m>
    friend AUTODIFF_ELEMENT<s,v,m> operator / (s a,CONST AUTODIFF_ELEMENT<s,v,m>& d2){
        AUTODIFF_ELEMENT h(d2.dim,d2.ComputeHessian);

        h.value = a / d2.value;
        h.grd = -a * d2.grd / Sqr(d2.value);
        if (d2.ComputeHessian) {
            h.hess = (h.TransposedMul (h.grd, d2.grd)
		   + h.TransposedMul (d2.grd, h.grd)
		   + h.value * d2.hess) / (-d2.value);
            h.ComputeHessian = TRUE;
        }
        return h;
    }
    AUTODIFF_ELEMENT operator + (REAL a){
        AUTODIFF_ELEMENT h(dim,ComputeHessian);
        h.value = a + value;
        h.grd = grd;
        if (ComputeHessian) {
            h.hess = hess;
            h.ComputeHessian = TRUE;
        }
        return h;
    }
    template<class s,class v,class m>
    friend AUTODIFF_ELEMENT<s,v,m> operator + (REAL a,CONST AUTODIFF_ELEMENT<s,v,m>& s2){
        return s2+a;
    }
    template<class s,class v,class m>
    friend AUTODIFF_ELEMENT<s,v,m> operator + (CONST AUTODIFF_ELEMENT<s,v,m>& s2,REAL a){
        AUTODIFF_ELEMENT<s,v,m> h(s2.dim,s2.ComputeHessian);
        h.value = a + s2.value;
        h.grd = s2.grd;
        if (s2.ComputeHessian) {
            h.hess = s2.hess;
            h.ComputeHessian = TRUE;
        }
        return h;
    }
    AUTODIFF_ELEMENT operator + (simple a){
        AUTODIFF_ELEMENT h(dim,ComputeHessian);
        h.value = a + value;
        h.grd = grd;
        if (ComputeHessian) {
            h.hess = hess;
            h.ComputeHessian = TRUE;
        }
        return h;
    }
    template<class s,class v,class m>
    friend AUTODIFF_ELEMENT<s,v,m> operator + (s a,CONST AUTODIFF_ELEMENT<s,v,m>& s2){
        return s2+a;
    }
    AUTODIFF_ELEMENT operator + (CONST AUTODIFF_ELEMENT& s2){
        AUTODIFF_ELEMENT h(dim,s2.ComputeHessian);

        h.value = value + s2.value;
        h.grd = grd + s2.grd;
        if (ComputeHessian && s2.ComputeHessian) {
            h.hess = hess + s2.hess;
            h.ComputeHessian = TRUE;
        }
        return h;
    }
    AUTODIFF_ELEMENT operator + (CONST INTERVAL_AUTODIFF& s2){
        AUTODIFF_ELEMENT h(dim,s2.ComputeHessian);

        h.value = value + s2.fkt();
        h.grd = grd + s2.grd();
        if (ComputeHessian && s2.ComputeHessian) {
            h.hess = hess + s2.hessian();
            h.ComputeHessian = TRUE;
        }
        return h;
    }
    AUTODIFF_ELEMENT operator - (CONST AUTODIFF_ELEMENT& s2){
        AUTODIFF_ELEMENT h(dim,s2.ComputeHessian);

        h.value = value - s2.value;
        h.grd = grd - s2.grd;
        if (ComputeHessian && s2.ComputeHessian) {
            h.hess = hess - s2.hess;
            h.ComputeHessian = TRUE;
        }
        return h;
    }
    AUTODIFF_ELEMENT operator - (CONST INTERVAL_AUTODIFF& s2){
        AUTODIFF_ELEMENT h(dim,s2.ComputeHessian);

        h.value = value - s2.fkt();
        h.grd = grd - s2.grd();
        if (ComputeHessian && s2.ComputeHessian) {
            h.hess = hess - s2.hessian();
            h.ComputeHessian = TRUE;
        }
        return h;
    }
    AUTODIFF_ELEMENT operator - ( )
    {
        AUTODIFF_ELEMENT h(dim,ComputeHessian);

        h.value = -value;
        h.grd = -grd;
        if (ComputeHessian) {
            h.hess = -hess;
            h.ComputeHessian = TRUE;
        }
        return h;
    }
    AUTODIFF_ELEMENT operator - (REAL a){
        AUTODIFF_ELEMENT h(dim,ComputeHessian);
        h.value = value - a;
        h.grd = grd;
        if (ComputeHessian) {
            h.hess = hess;
            h.ComputeHessian = TRUE;
        }
        return h;
    }
    template<class s,class v,class m>
    friend AUTODIFF_ELEMENT<s,v,m> operator - (REAL a,CONST AUTODIFF_ELEMENT<s,v,m>& s2){
        AUTODIFF_ELEMENT h(s2.dim,s2.ComputeHessian);
        h.value = a - s2.value;
        h.grd = -s2.grd;
        if (s2.ComputeHessian) {
            h.hess = -s2.hess;
            h.ComputeHessian = TRUE;
        }
        return h;
    }
    AUTODIFF_ELEMENT operator - (simple a){
        AUTODIFF_ELEMENT h(dim,ComputeHessian);
        h.value = a - value;
        h.grd = -grd;
        if (ComputeHessian) {
            h.hess = -hess;
            h.ComputeHessian = TRUE;
        }
        return h;
    }
    template<class s,class v,class m>
    friend AUTODIFF_ELEMENT<s,v,m> operator - (s a,CONST AUTODIFF_ELEMENT<s,v,m>& s2){
        return -s2+a;
    }
    template<class s,class v,class m>
    friend AUTODIFF_ELEMENT<s,v,m> Sqr (CONST AUTODIFF_ELEMENT<s,v,m> & g)
    {
        INT dim = Dimension(g);
        AUTODIFF_ELEMENT h(dim,g.ComputeHessian);

        h.value = Sqr(g.value);
        h.grd = 2.0 * g.value * g.grd;
        if (g.ComputeHessian) {
            h.hess = 2.0 * (g.value * g.hess + h.TransposedMul (g.grd, g.grd));
            h.ComputeHessian = TRUE;
        }
        return h;
    }

    template<class st,class v,class m>
    friend AUTODIFF_ELEMENT<st,v,m> Sin (CONST AUTODIFF_ELEMENT<st,v,m> & g)
    {
        INT dim = Dimension(g);
        AUTODIFF_ELEMENT h(dim,g.ComputeHessian);
        st s, c;

        s = Sin(g.value); c = Cos(g.value);
        h.value = s;
        h.grd = c * g.grd;
        if (g.ComputeHessian) {
            h.hess = c * g.hess - s * h.TransposedMul (g.grd, g.grd);
            h.ComputeHessian = TRUE;
        }
        return h;
    }

    template<class st,class v,class m>
    friend AUTODIFF_ELEMENT<st,v,m> Cos (CONST AUTODIFF_ELEMENT<st,v,m> & g)
    {
        INT dim = Dimension(g);
        AUTODIFF_ELEMENT h(dim,g.ComputeHessian);
        st s, c;

        s = Sin(g.value); c = Cos(g.value);
        h.value = c;
        h.grd = -s * g.grd;
        if (g.ComputeHessian) {
            h.hess = -s * g.hess - c * h.TransposedMul (g.grd, g.grd);
            h.ComputeHessian = TRUE;
        }
        return h;
    }

    template<class st,class v,class m>
    friend AUTODIFF_ELEMENT<st,v,m> Exp (CONST AUTODIFF_ELEMENT<st,v,m> & g)
    {
        INT dim = Dimension(g);
        AUTODIFF_ELEMENT h(dim,g.ComputeHessian);
        st s;

        h.value = Exp(g.value);
        s = Exp(g.value);
        h.grd = s * g.grd;
        if (g.ComputeHessian) {
            h.hess = s * (g.hess + h.TransposedMul (g.grd, g.grd));
            h.ComputeHessian = TRUE;
        }
        return h;
    }

    template<class st,class v,class m>
    friend AUTODIFF_ELEMENT<st,v,m> Sqrt (CONST AUTODIFF_ELEMENT<st,v,m> & g)
    {
        INT dim = Dimension(g);
        AUTODIFF_ELEMENT h(dim,g.ComputeHessian);
        st s;

        h.value = Sqrt(g.value);
        s = 2.0 * Sqrt(g.value);
        h.grd = g.grd / s;
        if (g.ComputeHessian) {
            h.hess = (g.hess - h.TransposedMul (g.grd, g.grd) / (2.0 * g.value)) / s;
            h.ComputeHessian = TRUE;
        }
        return h;
    }
    template<class s,class v,class m>
    friend AUTODIFF_ELEMENT<s,v,m> Abs (CONST AUTODIFF_ELEMENT<s,v,m> & g)
    {
        INT dim = Dimension(g);
        AUTODIFF_ELEMENT h(dim,g.ComputeHessian);

        h.value = Abs(g.value);
        h.grd = g.grd;
        if (g.ComputeHessian) {
            h.hess = g.hess;
            h.ComputeHessian = TRUE;
        }
        return h;
    }
    template<class s,class v,class m>
    friend INTERVAL_AUTODIFF VECTOR_AD_EL2INTERVAL_AD(CONST AUTODIFF_ELEMENT<s,v,m>& in){
        INTERVAL_AUTODIFF out;
        out.fkt() = in.value;
        out.grd() = in.grd;
        if(out.ComputeHessian)
            out.hessian() = in.hess;
    }
};
typedef AUTODIFF_ELEMENT<INTERVAL,INTERVAL_VECTOR,INTERVAL_MATRIX> AUTODIFF_ELEMENT_INTERVAL ;
/*Define o tipo padrão para o elementos da 
 matriz de autodiferenciação baseados em números
 reais.*/
typedef AUTODIFF_ELEMENT<REAL,VECTOR,MATRIX> AUTODIFF_ELEMENT_REAL ;


#endif /* AUTODIFF_ELEMENT_HPP */

