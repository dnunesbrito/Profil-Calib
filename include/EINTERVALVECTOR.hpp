/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EINTERVALVECTOR.hpp
 * Author: darlan
 *
 * Created on 26 de Setembro de 2016, 19:31
 */

#ifndef EINTERVALVECTOR_HPP
#define EINTERVALVECTOR_HPP
#include <initializer_list>
#include <IntervalMatrix.h>
#include <EINTERVAL.hpp>
#include <Vector.h>
#include <IntervalVector.h>


class EINTERVAL_VECTOR {
public:
    vector<EINTERVAL> theElements;
    INT nElements;
    EINTERVAL_VECTOR();
    EINTERVAL_VECTOR(const EINTERVAL_VECTOR& orig);
    EINTERVAL_VECTOR(CONST INTERVAL_VECTOR& A);
    EINTERVAL_VECTOR(CONST VECTOR& A);
    EINTERVAL_VECTOR(INT n);
    EINTERVAL_VECTOR (INT nElements,std::initializer_list<EINTERVAL> IN);
    virtual ~EINTERVAL_VECTOR();
    EINTERVAL& operator () (INT i) CONST
    { assert(i<=nElements && i > 0); return (EINTERVAL&)theElements[i-1]; }
    EINTERVAL_VECTOR & operator = (CONST EINTERVAL_VECTOR & A);
    EINTERVAL_VECTOR & operator += (CONST EINTERVAL_VECTOR & A);
    EINTERVAL_VECTOR & operator -= (CONST EINTERVAL_VECTOR & A);
    EINTERVAL_VECTOR & operator *= (CONST EINTERVAL & A);
    bool empty() CONST{theElements.empty();}
    INT rows() CONST{return nElements;}
    EINTERVAL_VECTOR Box(INT iniRow, INT endRow) CONST;
    VOID resize(INT newsize);
    VOID clear(){theElements.clear();nElements = 0;}
    VOID vcat(CONST EINTERVAL_VECTOR& A);
    INTERVAL_VECTOR norm(CONST EINTERVAL_VECTOR& );
    INTERVAL_VECTOR norm( );
    VOID reset();
    std::vector<std::vector<REAL> > diam();
    REAL maxdiam();
    INTERVAL_VECTOR getIV(INT idx) CONST;
    friend EINTERVAL_VECTOR operator + (CONST EINTERVAL_VECTOR &);
    friend EINTERVAL_VECTOR operator - (CONST EINTERVAL_VECTOR &);
    friend EINTERVAL_VECTOR operator + (CONST VECTOR &         ,CONST EINTERVAL_VECTOR &);
    friend EINTERVAL_VECTOR operator + (CONST EINTERVAL_VECTOR &,CONST VECTOR &         );
    friend EINTERVAL_VECTOR operator + (CONST EINTERVAL_VECTOR &,CONST EINTERVAL_VECTOR &);
    friend EINTERVAL_VECTOR AddReals  (CONST VECTOR &,CONST VECTOR &);
    friend EINTERVAL_VECTOR operator - (CONST VECTOR &         ,CONST EINTERVAL_VECTOR &);
    friend EINTERVAL_VECTOR operator - (CONST EINTERVAL_VECTOR &,CONST VECTOR &         );
    friend EINTERVAL_VECTOR operator - (CONST EINTERVAL_VECTOR &,CONST EINTERVAL_VECTOR &);
    friend EINTERVAL_VECTOR SubReals  (CONST VECTOR &,CONST VECTOR &);
    friend EINTERVAL_VECTOR operator * (REAL                   ,CONST EINTERVAL_VECTOR &);
    friend EINTERVAL_VECTOR operator * (CONST EINTERVAL_VECTOR &,REAL                   );
    friend EINTERVAL_VECTOR operator * (CONST EINTERVAL &       ,CONST VECTOR &         );
    friend EINTERVAL_VECTOR operator * (CONST EINTERVAL &       ,CONST EINTERVAL_VECTOR &);
    friend EINTERVAL_VECTOR operator * (CONST EINTERVAL_VECTOR &, CONST EINTERVAL &      );
    friend EINTERVAL        operator * (CONST VECTOR &         ,CONST EINTERVAL_VECTOR &);
    friend EINTERVAL        operator * (CONST EINTERVAL_VECTOR &,CONST VECTOR &         );
    friend EINTERVAL        operator * (CONST EINTERVAL_VECTOR &,CONST EINTERVAL_VECTOR &);
    friend EINTERVAL_VECTOR MulREals  (REAL,CONST VECTOR &);
    friend EINTERVAL_VECTOR operator / (CONST EINTERVAL_VECTOR &, REAL                   );
    friend EINTERVAL_VECTOR operator / (CONST VECTOR &         ,CONST EINTERVAL &       );
    friend EINTERVAL_VECTOR operator / (CONST EINTERVAL_VECTOR &,CONST EINTERVAL &       );
    friend bool operator <= (CONST EINTERVAL_VECTOR& ,CONST EINTERVAL_VECTOR&);
    friend EINTERVAL_VECTOR Hull(CONST EINTERVAL_VECTOR& , CONST EINTERVAL_VECTOR &);
    friend EINTERVAL_VECTOR DivReals  (CONST VECTOR &, REAL);
    friend EINTERVAL MulReals  (CONST VECTOR &,CONST  VECTOR &);
    friend ostream & operator << (ostream &,CONST EINTERVAL_VECTOR &);
    friend istream & operator >> (istream &,CONST EINTERVAL_VECTOR &);
    friend VOID Parse(vector<INTERVAL_VECTOR>& out,CONST EINTERVAL_VECTOR A);
    friend EINTERVAL Sqr(CONST EINTERVAL_VECTOR& A);
    friend INT EIntervalIntersection(EINTERVAL_VECTOR& tR,CONST EINTERVAL_VECTOR& pA,CONST EINTERVAL_VECTOR& pB);
private:

};

EINTERVAL_VECTOR operator + (CONST EINTERVAL_VECTOR &);
EINTERVAL_VECTOR operator - (CONST EINTERVAL_VECTOR &);
EINTERVAL_VECTOR operator + (CONST VECTOR &         ,CONST  EINTERVAL_VECTOR &);
EINTERVAL_VECTOR operator + (CONST EINTERVAL_VECTOR &,CONST VECTOR &         );
EINTERVAL_VECTOR operator + (CONST EINTERVAL_VECTOR &,CONST   EINTERVAL_VECTOR &);
EINTERVAL_VECTOR AddReals  (CONST  VECTOR &,CONST   VECTOR &);
EINTERVAL_VECTOR operator - (CONST  VECTOR &         ,CONST   EINTERVAL_VECTOR &);
EINTERVAL_VECTOR operator - (CONST  EINTERVAL_VECTOR &,CONST   VECTOR &         );
EINTERVAL_VECTOR operator - (CONST  EINTERVAL_VECTOR &,CONST   EINTERVAL_VECTOR &);
EINTERVAL_VECTOR SubReals  (CONST  VECTOR &,CONST   VECTOR &);
EINTERVAL_VECTOR operator * (REAL                   ,CONST   EINTERVAL_VECTOR &);
EINTERVAL_VECTOR operator * (CONST  EINTERVAL &       ,CONST   VECTOR &         );
EINTERVAL_VECTOR operator * (CONST  EINTERVAL &       ,CONST   EINTERVAL_VECTOR &);
EINTERVAL_VECTOR operator * (CONST EINTERVAL_VECTOR &,REAL                   );
EINTERVAL        operator * (CONST  VECTOR &         ,CONST   EINTERVAL_VECTOR &);
EINTERVAL        operator * (CONST  EINTERVAL_VECTOR &,CONST   VECTOR &         );
EINTERVAL        operator * (CONST EINTERVAL_VECTOR &,CONST EINTERVAL_VECTOR &);
EINTERVAL_VECTOR operator * (CONST EINTERVAL_VECTOR &, CONST EINTERVAL &      );
EINTERVAL_VECTOR MulReals  (REAL,CONST   VECTOR &);
EINTERVAL_VECTOR operator / (CONST  EINTERVAL_VECTOR &, REAL                   );
EINTERVAL_VECTOR operator / (CONST  VECTOR &         , CONST  EINTERVAL &       );
EINTERVAL_VECTOR operator / (CONST  EINTERVAL_VECTOR &,CONST   EINTERVAL &       );
/*Determina o casco convexo de dois EINTERVAL
 faz o casco convexo de todo mundo com todo mundo*/
EINTERVAL_VECTOR Hull(CONST EINTERVAL_VECTOR& , CONST EINTERVAL_VECTOR &);
/**********************************************************************
*  Result: true if A is contained in B, false otherwise
*/
bool operator <= (CONST EINTERVAL_VECTOR& A,CONST EINTERVAL_VECTOR& B);
EINTERVAL_VECTOR DivReals  (CONST  VECTOR &, REAL);
EINTERVAL MulReals  (CONST  VECTOR &,CONST   VECTOR &);
ostream & operator << (ostream &,CONST  EINTERVAL_VECTOR &);
istream & operator >> (istream &,CONST  EINTERVAL_VECTOR &);
VOID Parse(vector<INTERVAL_VECTOR>& out,CONST EINTERVAL_VECTOR A);
EINTERVAL Sqr(CONST EINTERVAL_VECTOR& A);
/*Determina a intersecao entre os vetores pA e pB
 se existe a intersecao retorna 1 caso qualquer
 um dos elementos nao tenha intersecao
 retorna zero e o vetor resultado e
 imprevizivel.*/
INT EIntervalIntersection(EINTERVAL_VECTOR& tR,CONST EINTERVAL_VECTOR& pA,CONST EINTERVAL_VECTOR& pB);

#endif /* EINTERVALVECTOR_HPP */

