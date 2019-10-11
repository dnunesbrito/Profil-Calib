int Angle_Ok_Interval(double angle,double b1,double b2);
double Distance_Angle(double a1,double a2);
int Degree_Max_Convert_Trigo_Interval(int n,VECTOR &A,INTEGER_VECTOR &SSin,
			      INTEGER_VECTOR &CCos);
int Degree_Max_Convert_Trigo_Interval(int n,INTEGER_VECTOR &A,
			      INTEGER_VECTOR &SSin,INTEGER_VECTOR &CCos);
VOID Convert_Trigo_Interval(int n,VECTOR &A,INTEGER_VECTOR &SSin,
			      INTEGER_VECTOR &CCos,VECTOR &Coeff,int *degree);
VOID Convert_Trigo_Interval(int n,INTEGER_VECTOR &A,INTEGER_VECTOR &SSin,
	      INTEGER_VECTOR &CCos,INTEGER_VECTOR &Coeff,int *degree);
VOID Convert_Trigo_Interval(int n,INTERVAL_VECTOR &A,INTEGER_VECTOR &SSin,
		      INTEGER_VECTOR &CCos,INTERVAL_VECTOR &Coeff,
			    INTERVAL &degree);
VOID Convert_Trigo_Pi_Interval(int n,VECTOR &A,INTEGER_VECTOR &SSin,
	      INTEGER_VECTOR &CCos,VECTOR &Coeff,int *degree);
VOID Convert_Trigo_Pi_Interval(int n,INTEGER_VECTOR &A,INTEGER_VECTOR &SSin,
	      INTEGER_VECTOR &CCos,INTEGER_VECTOR &Coeff,int *degree);
VOID Convert_Trigo_Pi_Interval(int n,INTERVAL_VECTOR &A,INTEGER_VECTOR &SSin,
	      INTEGER_VECTOR &CCos,INTERVAL_VECTOR &Coeff,INTERVAL &degree);
int Nb_Root_Trigo_Interval(int n,VECTOR &A,INTEGER_VECTOR &SSin,
			      INTEGER_VECTOR &CCos,REAL Inf,REAL Sup);
int Solve_Trigo_Interval(int n,VECTOR &A,INTEGER_VECTOR &SSin,
	      INTEGER_VECTOR &CCos,
		double Accuracy_Variable,
		double Accuracy,
		int MaxIter,int Stop,
		INTERVAL_VECTOR &Solution,
		int NbMaxSol,
		REAL Inf,REAL Sup);
int Solve_Trigo_Interval(int n,VECTOR &A,INTEGER_VECTOR &SSin,
	      INTEGER_VECTOR &CCos,
		double Accuracy_Variable,
		double Accuracy,
		int MaxIter,int Stop,
		INTERVAL_VECTOR &Solution,
		int NbMaxSol);

int Fast_Solve_Trigo_Interval(int n,VECTOR &A,INTEGER_VECTOR &SSin,
	      INTEGER_VECTOR &CCos,
		double Accuracy_Variable,
		double Accuracy,
		int MaxIter,int Stop,
		INTERVAL_VECTOR &Solution,
		int NbMaxSol,
		REAL Inf,REAL Sup);
int Fast_Solve_Trigo_Interval(int n,VECTOR &A,INTEGER_VECTOR &SSin,
	      INTEGER_VECTOR &CCos,
		double Accuracy_Variable,
		double Accuracy,
		int MaxIter,int Stop,
		INTERVAL_VECTOR &Solution,
		int NbMaxSol);
int Bound_Root_Trigo_Interval(int n,VECTOR &A,INTEGER_VECTOR &SSin,
	      INTEGER_VECTOR &CCos,int *nbsol,VECTOR &Inf,VECTOR &Sup);


