#define MAX_DEGRE 100
INT Number_is_even(REAL f);
VECTOR Derivative_Polynomial_Interval(int Dimension,VECTOR &Coeff);
INTEGER_VECTOR Derivative_Polynomial_Interval(int Dimension,INTEGER_VECTOR &Coeff);
INTERVAL_VECTOR Derivative_Polynomial_Safe_Interval(int Dimension,
						    VECTOR &Coeff);
INTERVAL_VECTOR Derivative_Polynomial_Fast_Safe_Interval(int Dimension,
						INTERVAL_VECTOR &Coeff);
VECTOR Nth_Derivative_Polynomial_Interval(int Dimension,VECTOR &Coeff,int n);
INTERVAL_VECTOR Derivative_Polynomial_Interval(int Dimension,
					       INTERVAL_VECTOR &Coeff);
INTERVAL_VECTOR Nth_Derivative_Polynomial_Interval(int Dimension,
					   INTERVAL_VECTOR &Coeff,int n);
VECTOR Add_Polynomial_Interval(int n1,VECTOR &Coeff1,int n2,VECTOR &Coeff2);
INTERVAL_VECTOR Add_Polynomial_Interval(int n1,INTERVAL_VECTOR &Coeff1,
			int n2,INTERVAL_VECTOR &Coeff2);
INTEGER_VECTOR Add_Polynomial_Interval(int n1,INTEGER_VECTOR &Coeff1,
	int n2,INTEGER_VECTOR &Coeff2);
INTERVAL_VECTOR Add_Polynomial_Safe_Interval(int n1,VECTOR &Coeff1,int n2,
		VECTOR &Coeff2);
int Degree_Product_Polynomial_Interval(int n1,VECTOR &Coeff1,int n2,
	VECTOR &Coeff2);
int Degree_Product_Polynomial_Interval(int n1,INTEGER_VECTOR &Coeff1,int n2,
	INTEGER_VECTOR &Coeff2);
VECTOR Multiply_Polynomial_Interval(int n1,VECTOR &Coeff1,int n2,
	VECTOR &Coeff2);
INTEGER_VECTOR Multiply_Polynomial_Interval(int n1,INTEGER_VECTOR &Coeff1,
	int n2,INTEGER_VECTOR &Coeff2);
INTERVAL_VECTOR Multiply_Polynomial_Interval(int n1,INTERVAL_VECTOR &Coeff1,
	int n2,INTERVAL_VECTOR &Coeff2);
INTERVAL_VECTOR Multiply_Polynomial_Safe_Interval(int n1,VECTOR &Coeff1,int n2,
	VECTOR &Coeff2);
void Quotient_UP_Derivative(int Degree,VECTOR &Coeff,VECTOR &CoeffD,VECTOR &Quo,
		       VECTOR &Rem);
int Fast_Newton_Safe(int Dimension,
	  REAL *Input,VECTOR &Coeff,double Accuracy,int Max_Iter,REAL *Residu);
int Fast_Newton_Safe(int Dimension,INTERVAL &Sol,
	  REAL *Input,VECTOR &Coeff,double Accuracy,int Max_Iter,REAL *Residu);
int Fast_Newton_Safe(int Dimension,
	  REAL *Input,VECTOR &Coeff,VECTOR &CoeffG,VECTOR &CoeffH,
		double Accuracy,
		int Max_Iter,REAL *Residu);
int Fast_Newton_Safe(int Dimension,INTERVAL &Sol,
	  REAL *Input,VECTOR &Coeff,VECTOR &CoeffG,
		double Accuracy,int Max_Iter,REAL *Residu);
int Fast_Newton(int Dimension,
	  REAL *Input,VECTOR &Coeff,VECTOR &CoeffG,
		double Accuracy,int Max_Iter,REAL *Residu);
int Newton(int Dimension,
	  REAL *Input,VECTOR &Coeff,double Accuracy,int Max_Iter,REAL *Residu);
int Newton_Safe(int Dimension,
	  REAL *Input,VECTOR &Coeff,double Accuracy,int Max_Iter,REAL *Residu);
int Newton_Safe(int Dimension,INTERVAL &Sol,
	  REAL *Input,VECTOR &Coeff,double Accuracy,int Max_Iter,REAL *Residu);
int Newton_Safe(int Dimension,
	  REAL *Input,VECTOR &Coeff,VECTOR &CoeffG,VECTOR &CoeffH,
		double Accuracy,
		int Max_Iter,REAL *Residu);
int Newton_Safe(int Dimension,INTERVAL &Sol,
	  REAL *Input,VECTOR &Coeff,VECTOR &CoeffG,
		double Accuracy,int Max_Iter,REAL *Residu);
