int Kantorovitch(int Dimension,
	  INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
	  INTERVAL_MATRIX (* Gradient)(int, int, INTERVAL_VECTOR &), 
	  INTERVAL_MATRIX (* Hessian)(int, int, INTERVAL_VECTOR &), 
	  VECTOR &Input, double *eps);
int Kantorovitch(int Dimension,int Dimension_Eq,
	  INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
	  INTERVAL_MATRIX (* Gradient)(int, int, INTERVAL_VECTOR &), 
	  INTERVAL_MATRIX (* Hessian)(int, int, INTERVAL_VECTOR &), 
	  VECTOR &Input, double *eps);
int Kantorovitch(int Dimension,
	  VECTOR (* TheFunction)(VECTOR &), 
	  MATRIX (* Gradient)(VECTOR &), 
	  INTERVAL_MATRIX (* Hessian)(int, int, INTERVAL_VECTOR &), 
	  VECTOR &Input,double *eps);
int Newton(int Dimension,
	  INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
	  INTERVAL_MATRIX (* Gradient)(int, int, INTERVAL_VECTOR &),
	  VECTOR &Input,double Accuracy,int Max_Iter, VECTOR &Residu);
int Newton(int Dimension,int Dimension_Eq,
	  INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
	  INTERVAL_MATRIX (* Gradient)(int, int, INTERVAL_VECTOR &),
	  VECTOR &Input,double Accuracy,int Max_Iter, VECTOR &Residu);
int Newton(int Dimension,int Dimension_Eq,
	  INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
	  INTERVAL_MATRIX (* Gradient)(int, int, INTERVAL_VECTOR &),
	  VECTOR &Input,double Accuracy,int Max_Iter,VECTOR &Residu,
	   INTERVAL_VECTOR &In);
int Newton(int Dimension,
	  VECTOR (* TheIntervalFunction)(VECTOR &), 
	  MATRIX (* Gradient)( VECTOR &),
	  VECTOR &Input,double Accuracy,int Max_Iter, VECTOR &Residu);
int Newton(int Dimension,
	  VECTOR (* TheIntervalFunction)(VECTOR &), 
	  MATRIX &InvGrad,
	  VECTOR &Input,double Accuracy,int Max_Iter, VECTOR &Residu);

int Ridder(REAL (* TheFunction)(REAL), 
	  INTERVAL &Input,double Accuracy_Var,double Accuracy,int MaxIter,
	   double *Sol, double *Residu);
int Brent(REAL (* TheFunction)(REAL), 
	  INTERVAL &Input,double Accuracy_Var,double Accuracy,int MaxIter,
	   double *Sol, double *Residu);

int Krawczyk_Analyzer(int Dimension,  int Dimension_Eq,
	  INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
	  INTERVAL_MATRIX (* Gradient)(int, int, INTERVAL_VECTOR &),
		      INTERVAL_VECTOR &Input);
int Krawczyk_Solver(int Dimension,  int Dimension_Eq,
	  INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
	  INTERVAL_MATRIX (* Gradient)(int, int, INTERVAL_VECTOR &),
		      INTERVAL_VECTOR &Input,double Acc,VECTOR &Result);
int Krawczyk_Solver_Safe(int Dimension,int Dimension_Eq,  
	  INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
	  INTERVAL_MATRIX (* Gradient)(int, int, INTERVAL_VECTOR &),
		      INTERVAL_VECTOR &Input1,double Acc,VECTOR &Result);
int Arc_Cos_Multiple(INTERVAL &U_in,INTERVAL &beta,INTERVAL_VECTOR &BETA);
int Filtre_Arc_Cos_Multiple(INTERVAL &U_in,INTERVAL &beta1);
double rint_RF(double x);
