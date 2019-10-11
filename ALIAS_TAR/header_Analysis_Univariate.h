
REAL Evaluate_Polynomial_Interval(int Dimension,VECTOR &Coeff,REAL P);
REAL Evaluate_Polynomial_Interval(int Dimension,INTEGER_VECTOR &Coeff,REAL P);
int Evaluate_Polynomial_Interval(int Dimension,INTEGER_VECTOR &Coeff,INT P);
INTERVAL Evaluate_Polynomial_Interval(int Dimension,
				      INTERVAL_VECTOR &Coeff,REAL P);
INTERVAL Evaluate_Polynomial_Interval_Fast(int Dimension,
				      INTERVAL_VECTOR &Coeff,INTERVAL P);
INTERVAL Evaluate_Polynomial_Interval(int Dimension,
				      VECTOR &Coeff,INTERVAL P);
INTERVAL Evaluate_Polynomial_Interval(int Dimension,
				      INTERVAL_VECTOR &Coeff,INTERVAL P);
INT Budan_Fourier_Interval(int Dimension,VECTOR &Coeff,INTERVAL In);
INT Budan_Fourier_Interval(int Dimension,VECTOR &Coeff,VECTOR &CoeffG,
			   VECTOR &CoeffH,INTERVAL In);
INT Budan_Fourier_Interval(int Dimension,INTEGER_VECTOR &Coeff,INTERVAL In);
INT Budan_Fourier_Interval(int Dimension,INTEGER_VECTOR &Coeff,int Inf,int Sup);
INT Budan_Fourier_Interval(int Dimension,INTERVAL_VECTOR &Coeff,INTERVAL In,
			   int *Confidence);
INT Budan_Fourier_Fast_Safe_Interval(int Dimension,INTERVAL_VECTOR &Coeff,
				INTERVAL In,INTERVAL &Nb_Root);
INT Budan_Fourier_Safe_Interval(int Dimension,VECTOR &Coeff,
				INTERVAL In,INTERVAL &Nb_Root);
int Kantorovitch(int Dimension,VECTOR &Coeff,REAL Input,double *eps);
int Kantorovitch(int Dimension,INTERVAL_VECTOR &Coeff,REAL Input,double *eps);
int Kantorovitch(int Dimension,VECTOR &Coeff,VECTOR &CoeffG,VECTOR &CoeffH,
		 REAL Input,double *eps);
INT Descartes_Lemma_Interval(int Dimension,VECTOR &Coeff);
INT Descartes_Lemma_Interval(int Dimension,INTERVAL_VECTOR &Coeff,
			     int *Confidence);
INT Descartes_Lemma_Negative_Interval(int Dimension,VECTOR &Coeff);
INT Descartes_Lemma_Negative_Interval(int Dimension,INTERVAL_VECTOR &Coeff,
			     int *Confidence);
int Cauchy_First_Bound_Interval(int Dimension,VECTOR &Coeff,INTERVAL &Bound);
int Cauchy_First_Bound_Interval(int Dimension,
				INTERVAL_VECTOR &Coeff,INTERVAL &Bound);
int Cauchy_Second_Bound_Interval(int Dimension,VECTOR &Coeff,double *Bound);
int Cauchy_Second_Bound_Inverse_Interval(int Dimension,VECTOR &Coeff,
					 double *Bound);
int Cauchy_Second_Bound_Interval(int Dimension,VECTOR &Coeff,INTERVAL &Bound);
int Cauchy_Second_Bound_Interval(int Dimension,
				 INTERVAL_VECTOR &Coeff,INTERVAL &Bound);
int Cauchy_Second_Bound_Inverse_Interval(int Dimension,
				 INTERVAL_VECTOR &Coeff,INTERVAL &Bound);
int Cauchy_Second_Bound_Negative_Interval(int Dimension,
					  VECTOR &Coeff,double *Bound);
int Cauchy_Second_Bound_Negative_Interval(int Dimension,
				  INTERVAL_VECTOR &Coeff,INTERVAL &Bound);
int Cauchy_Second_Bound_Negative_Inverse_Interval(int Dimension,
					  VECTOR &Coeff,double *Bound);
int Cauchy_Second_Bound_Negative_Inverse_Interval(int Dimension,
				  INTERVAL_VECTOR &Coeff,INTERVAL &Bound);
int Cauchy_Second_Bound_Interval(int Dimension,INTERVAL_VECTOR &Coeff,
				 INTERVAL &Lower,INTERVAL &Upper);
int Cauchy_Second_Bound_Negative_Interval(int Dimension,
				 VECTOR &Coeff,INTERVAL &Bound);
int Cauchy_Second_Bound_Negative_Interval(int Dimension,
				 INTERVAL_VECTOR &Coeff,
				 INTERVAL &Lower,INTERVAL &Upper);
int Cauchy_Third_Bound_Interval(int Dimension,
				INTERVAL_VECTOR &Coeff,INTERVAL &Bound);
int Cauchy_All_Bound_Interval(int Dimension,
				INTERVAL_VECTOR &Coeff,INTERVAL &Bound);
int MacLaurin_Bound_Interval(int Dimension,VECTOR &Coeff,double *Bound);
int MacLaurin_Bound_Interval(int Dimension,
			     INTERVAL_VECTOR &Coeff,INTERVAL &Bound);
int MacLaurin_Bound_Negative_Interval(int Dimension,
				      VECTOR &Coeff,double *Bound);
int MacLaurin_Bound_Negative_Interval(int Dimension,
			     INTERVAL_VECTOR &Coeff,INTERVAL &Bound);
int MacLaurin_Bound_Interval(int Dimension,VECTOR &Coeff,INTERVAL &Bound);
int MacLaurin_Bound_Interval(int Dimension,INTERVAL_VECTOR &Coeff,
			     INTERVAL &Lower,INTERVAL &Upper);
int MacLaurin_Bound_Inverse_Interval(int Dimension,VECTOR &Coeff,
				     double *Bound);
int MacLaurin_Bound_Inverse_Interval(int Dimension,
			     INTERVAL_VECTOR &Coeff,INTERVAL &Bound);
int MacLaurin_Bound_Negative_Inverse_Interval(int Dimension,VECTOR &Coeff,
				     double *Bound);
int MacLaurin_Bound_Negative_Inverse_Interval(int Dimension,
			     INTERVAL_VECTOR &Coeff,INTERVAL &Bound);
int MacLaurin_Bound_Negative_Interval(int Dimension,VECTOR &Coeff,
				      INTERVAL &Bound);
int MacLaurin_Bound_Negative_Interval(int Dimension,INTERVAL_VECTOR &Coeff,
			     INTERVAL &Lower,INTERVAL &Upper);
int Montel_Bound_Interval(int Dimension,VECTOR &Coeff,INTERVAL &Bound);
int Montel_Bound_Interval(int Dimension,INTERVAL_VECTOR &Coeff,
			     INTERVAL &Lower,INTERVAL &Upper);
int Laguerre_Bound_Interval(int Dimension,VECTOR &Coeff,double sens,
				      int MaxIter,double *bound);
int Laguerre_Bound_Interval(int Dimension,VECTOR &Coeff,double sens,
				      int MaxIter,INTERVAL &Bound);
int Laguerre_Bound_Interval(int Dimension,INTERVAL_VECTOR &Coeff,double sens,
				      int MaxIter,INTERVAL &Bound);
int Laguerre_Bound_Interval(int Dimension,INTERVAL_VECTOR &Coeff,double sens,
			      int MaxIter,INTERVAL &Lower,INTERVAL &Upper);
int Kantorovitch(int Dimension,INTERVAL_VECTOR &Coeff,REAL Input,double *eps);
int Kantorovitch(int Dimension,VECTOR &Coeff,REAL Input,double *eps);
int Kantorovitch_Fast_Safe(int Dimension,INTERVAL_VECTOR &Coeff,
			   REAL Input,double *eps);
int Global_Positive_Bound_Interval(int Dimension,VECTOR &Coeff,
				   INTERVAL &Bound);
int Global_Negative_Bound_Interval(int Dimension,VECTOR &Coeff,
				   INTERVAL &Bound);
int Global_Positive_Bound_Interval(int Dimension,INTERVAL_VECTOR &Coeff,
				   INTERVAL &Lower,INTERVAL &Upper);
int Global_Negative_Bound_Interval(int Dimension,INTERVAL_VECTOR &Coeff,
				   INTERVAL &Lower,INTERVAL &Upper);

int Newton_Bound_Interval(int Dimension,VECTOR &Coeff1,double amp_sens,
			    int MaxIter,double *bound);
int Newton_Bound_Inverse_Interval(int Dimension,VECTOR &Coeff1,double amp_sens,
			    int MaxIter,double *bound);
int Newton_Bound_Interval(int Dimension,VECTOR &Coeff1,double amp_sens,
			    int MaxIter,INTERVAL &Bound);

int Newton_Bound_Interval(int Dimension,INTERVAL_VECTOR &Coeff1,
			  double amp_sens,
			    int MaxIter,INTERVAL &Bound);
int Newton_Bound_Inverse_Interval(int Dimension,INTERVAL_VECTOR &Coeff1,
				  double amp_sens,
			    int MaxIter,INTERVAL &Bound);
int Newton_Bound_Interval(int Dimension,INTERVAL_VECTOR &Coeff1,
			  double amp_sens,
			    int MaxIter,INTERVAL &Lower,INTERVAL &Upper);
INTERVAL Evaluate_Polynomial_Safe_Interval(int Dimension,
					   VECTOR &Coeff,REAL P);
INTERVAL Evaluate_Polynomial_Safe_Interval(int Dimension,
					   VECTOR &Coeff,INTERVAL P);
INTERVAL Evaluate_Polynomial_Safe_Interval(int Dimension,
					   INTERVAL_VECTOR &Coeff,REAL P);
INTERVAL Evaluate_Polynomial_Safe_Interval(int Dimension,
					   INTERVAL_VECTOR &Coeff,INTERVAL P);
INTERVAL Evaluate_Polynomial_Fast_Safe_Interval(int Dimension,
					   INTERVAL_VECTOR &Coeff,REAL P);
INTERVAL Evaluate_Polynomial_Fast_Safe_Interval(int Dimension,
					   INTERVAL_VECTOR &Coeff,INTERVAL P);
VECTOR Coeff_Polynomial_Centered_Interval(int Dimension,VECTOR &Coeff,REAL P);
INTERVAL_VECTOR Coeff_Polynomial_Centered_Interval(int Dimension,
					  INTERVAL_VECTOR &Coeff,REAL P);
INTERVAL_VECTOR Coeff_Polynomial_Centered_Fast_Safe_Interval(int Dimension,
					    INTERVAL_VECTOR &Coeff,REAL P);
INTERVAL_VECTOR Coeff_Polynomial_Centered_Safe_Interval(int Dimension,
					    VECTOR &Coeff,REAL P);
REAL Evaluate_Polynomial_Centered_Interval(int Dimension,VECTOR &Coeff,
					   REAL Center,REAL P);
INTERVAL Evaluate_Polynomial_Centered_Interval(int Dimension,VECTOR &Coeff,
					   INTERVAL P);
INTERVAL Evaluate_Polynomial_Centered_Interval(int Dimension,
					       INTERVAL_VECTOR &Coeff,
					   REAL Center,REAL P);
INTERVAL Evaluate_Polynomial_Centered_Interval(int Dimension,
					       INTERVAL_VECTOR &Coeff,
					   INTERVAL P);
INTERVAL Evaluate_Polynomial_Centered_Safe_Interval(int Dimension,
						    VECTOR &Coeff,
					   REAL Center,REAL P);
INTERVAL Evaluate_Polynomial_Centered_Fast_Safe_Interval(int Dimension,
						INTERVAL_VECTOR &Coeff,
					   REAL Center,REAL P);
INTERVAL Evaluate_Polynomial_Centered_Fast_Safe_Interval(int Dimension,
						VECTOR &Coeff,
					   INTERVAL P);
INTERVAL Evaluate_Polynomial_Centered_Fast_Safe_Interval(int Dimension,
						INTERVAL_VECTOR &Coeff,
					   INTERVAL P);
int Sign_Polynomial_Interval(int Dimension,VECTOR &Coeff,REAL P);
int Sign_Polynomial_Interval(int Dimension,INTERVAL_VECTOR &Coeff,REAL P);
int Sign_Polynomial_Interval(int Dimension,INTERVAL_VECTOR &Coeff,REAL P);
int Sign_Polynomial_Interval(int Dimension,INTERVAL_VECTOR &Coeff,INTERVAL P);

int Huat_Polynomial_Interval(int Dimension,VECTOR &Coeff);
int Huat_Polynomial_Interval(int Dimension,INTERVAL_VECTOR &Coeff);

int Newton_Second_Bound_Interval(int Dimension,VECTOR &Coeff,double *bound);
int Newton_Second_Bound_Inverse_Interval(int Dimension,VECTOR &Coeff,
					 double *bound);
int Newton_Second_Bound_Interval(int Dimension,VECTOR &Coeff,INTERVAL &Bound);

int Newton_Second_Bound_Interval(int Dimension,INTERVAL_VECTOR &Coeff,
				 INTERVAL &Bound);
int Newton_Second_Bound_Inverse_Interval(int Dimension,INTERVAL_VECTOR &Coeff,
					 INTERVAL &Bound);
int Newton_Second_Bound_Interval(int Dimension,INTERVAL_VECTOR &Coeff,
				 INTERVAL &Lower, INTERVAL &Upper);
int Laguerre_Second_Bound_Interval(int Dimension,VECTOR &Coeff,
				   INTERVAL &Bound);
int Laguerre_Second_Bound_Interval(int Dimension,
	INTERVAL_VECTOR &Coeff,INTERVAL &Lower,INTERVAL &Upper);
INTERVAL_VECTOR SumN_Polynomial_Interval(int Dimension,INTERVAL_VECTOR &Coeff);
VECTOR SumN_Polynomial_Interval(int Dimension,VECTOR &Coeff);
VECTOR ProdN_Polynomial_Interval(int Dimension,VECTOR &Coeff);
INTERVAL_VECTOR ProdN_Polynomial_Interval(int Dimension,
					  INTERVAL_VECTOR &Coeff);
INTERVAL_VECTOR Evaluate_Coeff_Safe_Interval(int Dimension,VECTOR &Coeff);
int Sturm_Interval(int Dimension,VECTOR &Coeff,INTERVAL &In);
int Sturm_Interval(int Dimension,INTEGER_VECTOR &Coeff,INTERVAL &In);
int Sturm_Interval(int Dimension,INTEGER_VECTOR &Coeff,int Inf,int Sup);
int Sturm_Safe_Interval(int Dimension,VECTOR &Coeff,INTERVAL &In,INTERVAL 
			&Nb_Root);
int Min_Sep_Root_Interval(int Degree,VECTOR &Coeff,double *min);
int Max_Sep_Root_Interval(int Degree,VECTOR &Coeff,double *max);
int Bound_Sep_Root_Interval(int Degree,VECTOR &Coeff,INTERVAL &Bound);
int Min_Sep_Root_Interval(int Degree,INTERVAL_VECTOR &Coeff,INTERVAL &Lower);
int Gerschgorin(INTERVAL_MATRIX &P,int Size, int Type_Matrix, INTERVAL &Bound);
int Gerschgorin(int (* TheMatrix)(INTERVAL_VECTOR &, INTERVAL_MATRIX &),
		INTERVAL_VECTOR &Input,
		int Size, int Type_Matrix, INTERVAL &Bound);
int Gerschgorin_Simplification(INTERVAL_MATRIX &P,int Size, 
			       int Type_Matrix, INTERVAL &Input);
int Gerschgorin_Simplification(
	     int (* TheMatrix)(INTERVAL_VECTOR &, INTERVAL_MATRIX &),
		INTERVAL_VECTOR &Param,
		int Size, int Type_Matrix, INTERVAL &Input);
int Gerschgorin_Simplification(INTERVAL_MATRIX &P,int Size, 
			       int Type_Matrix, INTERVAL &Input,
			       INTERVAL_VECTOR &Circle);
int Gerschgorin_Simplification(
	     int (* TheMatrix)(INTERVAL_VECTOR &, INTERVAL_MATRIX &),
		INTERVAL_VECTOR &Param,
		int Size, int Type_Matrix, INTERVAL &Input,
	     INTERVAL_VECTOR &Circle);

int Pellet(int Degree,INTERVAL_VECTOR &Coeff,double Radius);
