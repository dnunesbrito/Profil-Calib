int Evaluate_Interval_With_Parser(char *texte,INTERVAL_VECTOR &P,
				       int Unknowns, INTERVAL &Value);
int Evaluate_Equations_With_Parser(char *texte,INTERVAL_VECTOR &P,
				       int Unknowns,int Nb_Eq, 
				   INTERVAL_VECTOR &Value);
int Evaluate_Equations_With_Parser(char *texte,INTERVAL_VECTOR &P,
				       int Unknowns,int Nb_Eq, int eq,
				   int *Eq_Start,
				   INTERVAL &Value);
int Evaluate_Equations_With_Parser(char *texte,INTERVAL_VECTOR &P,
				       int Unknowns,int Nb_Eq, int eq,int eq1,
				   int *Eq_Start,
				   INTERVAL_VECTOR &Value);
int Evaluate_Equations_With_Parser_Gradient(int Dimension,
          int Dimension_Eq,
	  char * Equations_File,
	  char * Gradient_File,
	  INTERVAL_VECTOR &Input, INTERVAL_VECTOR &Output,int Exact);

int Init_Evaluate_Equations_With_Parser(char *texte, int *Eq_Start);
int Equation_Analyzer(int Dimension,int Dimension_Eq,
		      int Iteration,
		      char *formula_file,
		      char *gradient_file,
		      char *hessian_file,
		      char *inequalities_file,
		      char *dimension_file,
		      char *coeff_file,
		      char *gradient_coeff_file,
		      int method,
		      int nb_inequalities,
		      int equation_processed,
		      INTERVAL_VECTOR &Input,
		      double Acc_Var,
		      double Acc_Eq,
		      double Acc_Kanto,
		      int Depth_Level,
		      INTERVAL_MATRIX &Range,
		      int *Nb_Range);

int Kantorovitch_Analyzer(int Dimension,  
		 char *Function_File,char *Gradient_File,
		 char *Hessian_File,
	  VECTOR &Input,double *eps);

int Newton(int Dimension,
	  char * TheIntervalFunction_File,
	  char * Gradient_File,
	  VECTOR &Input,double Accuracy,int Max_Iter,VECTOR &Residu);

int Solve_General_Interval(int Dimension_Var,int Dimension_Eq,
	char * TheIntervalFunction_File,
		INTERVAL_VECTOR & TheDomain, 
		int Order,
		int Iteration,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution,int Nb_Max_Solution,
			   int nb_inequalities,char *Ineq_File);
int Solve_General_Gradient_Interval(int Dimension,int Dimension_Eq,
	char * TheIntervalFunction_File,
		char * Gradient_File,
		INTERVAL_VECTOR & TheDomain, 
		int Order,
		int Iteration,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution,int Nb_Max_Solution,
				    int nb_inequalities,char *Ineq_File);
int Solve_General_Gradient_Interval(int Dimension,int Dimension_Eq,
	char * TheIntervalFunction_File,
		char * Gradient_File,
		INTERVAL_VECTOR & TheDomain, 
		int Order,
		int Iteration,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution,int Nb_Max_Solution,
				    INTEGER_VECTOR &Init_Grad,
				    int nb_inequalities,
				    char *Ineq_File);
int Solve_General_JH_Interval(int Dimension,int Dimension_Eq,
	char * TheIntervalFunction_File,
		char * Gradient_File,
		char * Hessian_File,
		INTERVAL_VECTOR & TheDomain, 
		int Order,
		int Iteration,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		INTERVAL_MATRIX & Solution,
                INTEGER_VECTOR & Is_Kanto,
		int Apply_Kanto,
			      int Nb_Max_Solution,
			      int nb,char *file);

extern char variable_name_IS[200][200];
extern char parameter_name_IS[200][200];
extern int Nb_Parameter_IA;
extern double parameter_value_IS[200];
extern double Mini_Variation_IA;
extern double Min_Variation_IA;
extern int Nb_Parameter_Valued_IA;
