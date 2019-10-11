//maximum of iteration in the Laguerre method for determining
//bounds on the root of univariate polynomial

extern int Max_Iter_Laguerre_Interval;

//step for the Laguerre method for determining
//bounds on the root of univariate polynomial. If this value
//is changed to some positive value then this step will always be
// used

extern double Step_Laguerre_Interval;


//Maximum number of iteration for Newton scheme used in 
//Solve_General_JH_Interval

extern int Max_Iter_Newton_JH_Interval;

//minimal step for Laguerre's method
extern double Min_Step_Laguerre_Interval;

//flag set to n+1 if we are using the Reverse Storage mode (n= number
//of unknowns)
extern int Reverse_Storage;


extern int ALIAS_Safety_Factor;
