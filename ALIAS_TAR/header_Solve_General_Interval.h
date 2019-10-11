#define MAX_FUNCTION_ORDER 0
#define MAX_MIDDLE_FUNCTION_ORDER 1
#define MAX_GRADIENT_FUNCTION 2
#define MAX_CONSTRAINT_FUNCTION 3
#include <IntegerMatrix.h>
//les boites pour les algorithmes 
INTERVAL_MATRIX Box_Solve_General_Interval;
//les boites qui vont contenir les signes des derivees des expressions
//selon le code: -1 derivee toujours negative, 0 derivee nulle ou evaluation
//pour une variable reduite a un point, 1 derivee toujours positive, 2
//derivee dont l'evaluation n'est pas de signe constant
INTEGER_MATRIX Gradient_Solve_General_Interval;
//les boites qui vont contenir l'evaluation des derivees des expressions
INTERVAL_MATRIX Gradient_Solve_JH_Interval;
//un tableau qui indique si l'on utilise le gradient pour chaque equation
INTEGER_VECTOR ALIAS_Use_Grad_Equation;
//pour les variete de dimension >0 le volume des boites dans la
//variete et le volume des boites negligees
double ALIAS_Volume_In=0;
double ALIAS_Volume_Neglected=0;
//a flag to indicate that a division by 0 will occur if we continue
int ALIAS_Divide0=0;
//est ce que l'on utilise l'inflation pour essayer d'elargir
//l'intervalle donne par Kanto?
int ALIAS_Always_Use_Inflation=0;
//l'eps avec lequel on commence l'inflation
double ALIAS_Eps_Inflation=1.e-6;
//time out en minute pour les process paralleles ou non
double ALIAS_TimeOut=0;
//pour indiquer que le time out a ete active
int ALIAS_TimeOut_Activated=0;
//shall we store the gradient: by default yes
int ALIAS_Store_Gradient=1;
//shall we transmit the gradient: by default yes
int ALIAS_Transmit_Gradient=1;
//shall we use the 3B test, 1=yes
int ALIAS_Use3B=0;
//threshold for the 3B test
VECTOR ALIAS_Delta3B;
//if the diameter of the interval islower than Delta3B we usually don't
//do the 3B. But if this flag is set to 1 we will always do one
//step of the 3B
int ALIAS_Always3B=0;
//the 3B method will not be applied if the width of the range is larger
//than these values
VECTOR ALIAS_Max3B;
//the 3B method is applied only on a subset of the equations if this flag
//is set to 1 and the concerned equation have a 1 in the array of integers
int ALIAS_Use_SubEq3B=0;
//un flag qui passe a 1 pour indiquer que l'on appelle une procedure
//de simplification dans le cadre de la 3B
int ALIAS_Simp_3B;
INTEGER_VECTOR ALIAS_SubEq3B;
//shall we use the 3B method at maximum power?
int ALIAS_Full3B=0;
//we restart the 3B if the maximal change on one variable has exceeded
//this threshold
double ALIAS_Full3B_Change=0.1;
//for the 3B we will try to decrease the size of the box by starting by a
//a small value if the size of the interval is larger than the size of the
//initial value for the variable multiplied by ALIAS_Switch_3B. Otherwise
//we will start by the large values
double ALIAS_Switch_3B=0;
//for the 3B method should we use the simplification procedure 
//given by the user? By default yes
int ALIAS_Use_Simp_In_3B=1;

//for the method with the gradient shall we evaluate the equations
//with the gradient or not. Yes if the maximal width of the input is lower
//than this value
double ALIAS_Diam_Max_Gradient=1.e10;
//for the method using Kraw operator we will use the operator only 
//if the maximal width of the input is lower
//than this value
double ALIAS_Diam_Max_Kraw=1.e10;
//always use Kraw method (if the radius is ok) 
int ALIAS_Use_Kraw=1;
//for the method with the gradient shall we use interval Newton. 
//Yes if the maximal width of the input is lower than this value
double ALIAS_Diam_Max_Newton=1.e10;
//type of the equation
// 0: full equation
// 1: equation>=0
//-1: equation<=0
//2: quantite a maximiser
//-2:quantite a minimiser
INTEGER_VECTOR ALIAS_Type_Eq;
//number of pure equations in a system
int ALIAS_Pure_Equation=0;
//type of storage used for the box created after a bisection. With the default
//value 0 (direct storage mode)
// one the new box will take the place of the current and the remaining
//new boxes will be stored at the end of the list. If Reverse_Storage is equal
//to the number of unknown +1 (reverse storage mode), 
//then all the new boxes will be stored
//starting at the current position. Otherwise a mix of the 2 previous storage
//mode is used.
int Reverse_Storage=0;
//the direct storage mode may lead to the storage of a large number of box
//This flag will allow to switch to the reverse storage mode 
//(which is minimal in
//term of storage needed) as soon as the total number of boxes to be processed
//exceed a given threshold
int Switch_Reverse_Storage=-1;

//des variables pour gerer la geometrie pour les polynomes

int ALIAS_Has_OptimumG=0;
INTERVAL_VECTOR ALIAS_Vector_OptimumG;
INTERVAL ALIAS_OptimumG;
//boite, mode de bissection et de stockage pour les algo utilisant
//un niveau au dessus des algo standards
int Reverse_StorageG=0;
int Single_BisectionG=1;
INTERVAL_MATRIX BoxUP;
//polynomial degree
int ALIAS_Degree; 
INTEGER_VECTOR DependG;

//flag qui indique leniveau de debug:0 pas de debug, 1 debug sommaire
//2 debug detaille
int Debug_Level_Solve_General_Interval=0;
int Enable_Delete_Fast_Interval=1;
int Interval_Combinatory_Level= -1;
//evaluation des expressions en bloc ou une par une: par defaut en bloc
int Interval_Evaluate_Equation_Alone=0;
//flag qui indique le type de bisection utilise:0 on coupe toutes les
//variables, >0 une seule
int Single_Bisection=0;
//pour la bisection mixte le nombre de variable sur laquelle
// on fait de la bisection complete
int ALIAS_Mixed_Bisection=0;
//1 si la variable i est completemt bissecte
INTEGER_VECTOR ALIAS_Bisection;
//un tableau de poids pour guider la bissection
VECTOR ALIAS_Bisection_Weight;
//1 si on fait de la bisection ordonnee
int ALIAS_Ordered_Bisection=0;
//le tableau contenant les ordres possibles dans la bisection
INTEGER_MATRIX ALIAS_Order_Bisection;

//0 si c'est un pb de resolution, 1 un problem de maximisation,-1 de
//minimisation
//1 si on maximise, -1 si on minimise, 10 pour les deux
int ALIAS_Optimize=0;
//precision sur l'extremum
double ALIAS_Accuracy_Extremum=1.e-6;
//1 si on a trouve un extremum
int ALIAS_Has_Optimum=0;
//1 si c'est le programme qui l'a trouve (et non par initialisation)
int ALIAS_Algo_Find_Optimum=0;
//extremum d'une fonction que l'on minimise ou maximise, ou minimum quand
//on fait les 2
INTERVAL ALIAS_Optimum;
//maximum d'une fonction que l'on minimise et maximise
INTERVAL ALIAS_Optimum_Max;
//la localisation des extremums
INTERVAL_MATRIX ALIAS_Vector_Optimum;
//1 si dans un probleme d'optimisation ou l'on recherche le minimum
//et le maximum on desire s'arreter quand on est sur que les extremums
//sont de signe oppose
int ALIAS_Stop_Sign_Extremum=0;
//1 si dans les fonctions a traiter il y a des coeff intervalle
int ALIAS_Func_Has_Interval=0;
//numero de la fonction a optimise
int ALIAS_Opt_Func;
//on fera appel a l'optimisateur local si pour un point on trouve F tel
//alors que l'extremum courant est E alors a*E<F<b*E
double ALIAS_LO_A=0.9;
double ALIAS_LO_B=1.1;
//1 si onb desire stopper des que l'on a trouve un meilleur extremum
//que ALIAS_Extremum (si on cherche min et max on prend Extremum et _Max)
int ALIAS_Stop=0;
double ALIAS_Extremum;
double ALIAS_Extremum_Max;
//si la fonction a optimiser apres un premier passage de l'optimisateur
//local a une valeur superieur a ce double on ne modifie pas le step
//de l'optimisateur local
double ALIAS_Threshold_Optimiser=100;
//1 if we allow to store the intermediate result of the optimization
//in the ALIAS_Storage_File
int ALIAS_Allow_Storage=0;
//name of the file where temporary result for the optimization will
//be strored
char ALIAS_Storage_File[200]={'.','o','p','t','i'};
//1 if we guide the choice of the bisected variables
int ALIAS_Guide_Bisection=0;
//the choice table
INTEGER_MATRIX ALIAS_Bisecting_Table;
//the ordering
int ALIAS_Order;
//dans le cas ou on fait de l'optimisation avec une valeur initiale
// de l'extremum  il peut etre interessant
//d'avoir une idee de ce qu'a trouve l'algo (comme ca si on ne trouve
//pas d'extremum meilleur que la valeur donne on aura quand meme une
//idee d'une borne sur l'extremum). Cette idee est dans
//ALIAS_Algo_Optimum
int ALIAS_Algo_Has_Optimum=0;
INTERVAL ALIAS_Algo_Optimum;
INTERVAL ALIAS_Algo_Optimum_Max;
//est que l'on utilise aussi Kraw dans la continuation ?
//par defaut non, oui si 1
int ALIAS_Use_Kraw_Continuation=0;
//pour la continuation: si en cours de process on voit apparaitre plus
//de branches qu'au coup precedent cela veut pouvoir dire que l'on a
//rate des branches: on stocke alors les points a problemes pour traitement
//ulterieur: ici le nombre de point a probleme
int ALIAS_Problem_Continuation=0;
//valeur du parametre ou est apparu le probleme: pas plus de 10
VECTOR ALIAS_z_Start_Problem(10);
//valeur du sens ou est apparu le probleme: pas plus de 10
INTEGER_VECTOR ALIAS_sens_Start_Problem(10);

//pour les methodes utilisant le simplex: on n'applique pas le
//simplex si la largeur maximale des intervalles est inferieure a
//Max_Diam_Simplex ou si elle est superieure a Min_Diam_Simplex
double Max_Diam_Simplex=1.e-4;
double Min_Diam_Simplex=1.e10;
double Min_Improve_Simplex=1.e-4;
//shall we avoid the use of the simplex. We dont if 1
//(utile pour le processing en parallele pour eviter que le maitre rame)
int ALIAS_DONT_USE_SIMPLEX=0;
//popur le simplexe on peut utiliser une
//forme decentre (x^2=(x0+e)^2 ou e est la variable. C'est le cas
//si cette variable est a 1
int ALIAS_Simplex_Expanded=0;

// pour le processing en parallele: si>0 nombre maximal de boite retourne,
//si <0 nombre minimal de bisection a faire et ALIAS_Parallel_Max_Box
//donne le nombre maximal de boite a retourne (si -1 pas de limite: on
//sort des que l'on a fait le nombre de bissection demandee). Pour eviter
//qu'une boite soit exclusivement traitee par un esclave quand 
//ALIAS_Parallel_Max_Bisection<0 on limite le nombre d'iteration a 
//|ALIAS_Parallel_Max_Bisection|*ALIAS_Safety_Factor. Si on depasse ce 
//seuil on retourne un signal d'erreur qui fait que la boite sera decoupee
//en deux et redistribuee sur les processeurs
int ALIAS_Parallel_Max_Bisection=0;
int ALIAS_Parallel_Max_Box=-1;
int ALIAS_Safety_Factor=2;
//pour le processing en parallele: nom du fichier resultat
char ALIAS_Parallel_File[200];
//pour le processing en parallele: 1 si le processus est esclave, 0
//si c'est le maitre
int ALIAS_Parallel_Slave=0;
//pour le processing en parallele: pour le processus maitre le numero de la
//boite ou on est sorti et le nombre total de boite a faire encore
int ALIAS_Parallel_Box[2];
//pour le processing en parallele: si on est en Reverse_Storage le nombre
//maximum de bisection
int ALIAS_Parallel_Max_Reverse=30;
//si non nul on ne fera jamais plus de ce nombre de bisection dans le
//cas ou ALIAS_Parallel_Max_Bisection>0 et que le nombre de boite
//restant a traiter n'excede pas ALIAS_Parallel_Max_Bisection
int ALIAS_Parallel_Max_Split=0;

//1 si on a affaire a un systeme qui n'est pas de dimension 0
int ALIAS_ND=0;
//dans le cas precedent le nom du fichier dans lequel on va stocker
//les boites resultats
char ALIAS_ND_File[400];

//pour les methodes de continuation, si on a pas trouve de branche
//pour la valeur initiale du parametre on le change de dz. On
//recommence une resolution prour z+dz et ainsi de suite jusqua
//z+n*dz. Mais on peut backtracker entre z+(n-1)dz et z+n*dz pour
//ameliorer le point initial des branches. Mais c'est couteux
//On ne fait ca que si cette variable est a 1
int ALIAS_Allow_Backtrack=1;

//si on utilise smear_bounded on ne considere par pour la bisection
//les variables dont le diametre divise par le diametre max est +
//petit que cette valeur
double ALIAS_Bound_Smear=1.e-5;

//pour les equations de distance, seuil a partir duquel on arrete
//l'ajustement de variable puis la meme chose en pourcentage du Diam
double ALIAS_Seuil_Ajuste=0.5;
int ALIAS_Seuil_Ajuste_Percent=100;

//numero de la prochaine variable a couper pour le mode round robin
//de la bisection
int ALIAS_Round_Robin=1;

//pour certaine procedure on peut avoir besoin de transmettre la boite
//courante sans passer par les arguments. On utilise alors ce vecteur
INTERVAL_VECTOR ALIAS_v_IS;


//pour certaine procedure au bout d'un certain nombre d'iteration
//on permute les boite de la liste. Ici le nombre d'iteration
//pour cela
int ALIAS_Permute_List=1000;

//pour la resolution si on trouve une solution que l'on pense
//singuliere le diametre d'exclusion de la boule autour
double ALIAS_Diam_Sing=0;
//valeur du determinant a partir de laquell on considere qu'une
//matrice est singuliere
double ALIAS_Sing_Determinant=1.e-3;

//pour eviter que Newton ne diverge on peut limiter la taille des 
//variables dans Newton et sortir si cette taille est depassee

VECTOR ALIAS_Newton_Max_Dim;

//dans les fonctions ou on evalue les equations avec les gradients on
//peut ne pas le fairetant que les variables n'ont pas un diametre
//inferieure a ce seuil

VECTOR ALIAS_Func_Grad;

//maximum number of iteration for the Newton scheme
int Max_Iter_Newton_JH_Interval=100;

//a limit for a counter that allow to switch the bisection mode as soon
//as ALIAS_RANDG bissection have been performed
int ALIAS_RANDG=1000000;

//maximum de boites que l'on peut creer lors de la reduction d'une boite 
//par des solutions
int ALIAS_Allows_N_New_Boxes=2;
//lors de la reduction par une solution pour n inconnues on peut
//creer 2n nouvelles boites. Si on demande d'en creer moins alors il
//faut choisir lesquelles on traite en priorite. 
//si 2: les + importante selon fonction smear
//si 1: dans l'ordre decroissant des diametres
//0 : dans l'ordre des variables

int ALIAS_Type_N_New_Boxes=0;

//1 si on ne veut pas utiliser la hessienne pour les evaluations
int ALIAS_No_Hessian_Evaluation=0;

int ALIAS_Tranche_Bisection=1;
double ALIAS_Size_Tranche_Bisection=0.1;
int ALIAS_Selected_For_Bisection=1;

//si |X|<ALIAS_Value_Sign_Signum alors ALIAS_Signum(X) retournera
//ALIAS_Sign_Signum
double ALIAS_Value_Sign_Signum=1.e-6;
double ALIAS_Sign_Signum=0;

//les solutions trouvees par ALIAS, sous forme d'intervalle meme pour les
//solutions garantis et leur nombre
INTERVAL_MATRIX ALIAS_Solution;
int ALIAS_Nb_Solution;

//domaine initial de recherche
INTERVAL_VECTOR ALIAS_Init_Domain;

//si on demarre avec un domaine de recherche deja decompose en boite
//nombre de boite et les boites
int ALIAS_Initial_Box_Number=0;
INTERVAL_MATRIX ALIAS_Initial_Box;

//on ne fera pas de 3B si une des variables a un interval >ALIAS_Global_Max_3B
//si -1 ce test n'est pas effectue
double ALIAS_Global_Max_3B=-1;

//1, on utilisera l'elimination de Gauss pour evaluer les determinants
int ALIAS_Use_Gaussian_Elim_In_Det=0;

//1 si ALIAS est en train de choisir la variable a couper
int ALIAS_In_Bisection=0;

//1 si on a employe Verif_Problem pour eviter les probleme d'eval
int ALIAS_ChangeF=0;
int ALIAS_ChangeJ=0;
int ALIAS_ChangeH=0;
//1 si la procedure gradient permet l'evaluation de toute la jacobienne en une
//seule etape
int ALIAS_Gradient_One_Step=0;

//---------------------------------------------
//PROCEDURES
//--------------------------------------------
int Solve_General_Interval(int Dimension_Var,int Dimension_Eq,
			   INTEGER_VECTOR &Type_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_VECTOR & TheDomain, 
		int Order,
		int Iteration,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution,int Nb_Max_Solution,
				    int (* Simp_Proc)(INTERVAL_VECTOR &));
int Solve_General_Interval(int Dimension_Var,int Dimension_Eq,
			   INTEGER_VECTOR &Type_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_VECTOR & TheDomain, 
		int Order,
		int Iteration,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution,int Nb_Max_Solution);

int Solve_General_Interval(int Dimension,int Dimension_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_VECTOR & TheDomain, 
		int order,
		int Iterations,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution, int Nb_Max_Solution);
int Solve_General_Ordered_Interval(int Dimension,int Dimension_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_VECTOR & TheDomain, 
		int order,
		int Iterations,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution, int Nb_Max_Solution);
int ALIAS_Read_Buffer(char *mess,
		       int Nb_Var, int Nb_Eq,INTERVAL_MATRIX &Box,
		       int *Nb_Total,
		       INTERVAL_MATRIX &Sol,int *Nb_Sol,int *Nb_Split,
		      INTEGER_VECTOR &IPar,int *Nb_Ipar,
		      VECTOR &FPar,int *Nb_Fpar,INTERVAL_MATRIX &BoxPar,
		      int *Nb_BoxPar);
int ALIAS_Add_Box(int DimVar,INTERVAL_MATRIX &Box,int *Current_Box,int *Nb_Box,
		  INTERVAL_MATRIX New_Box, int Nb_New_Box,int MaxBox);
void ALIAS_Prepare_Buffer(int DimVar,INTERVAL_VECTOR &X,char *buffer);
int ALIAS_Sort_Sol(int Dimension_Var,int Dimension_Eq,int MaxSol,
		   int Order,double Dist_Sol_Diff,
	  INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		   INTERVAL_MATRIX &Local_Sol,int total_sol,
		   INTERVAL_MATRIX &Solution);
void ALIAS_Eventual_New_Optimum(int DimVar,
				VECTOR &Fpar,INTERVAL_MATRIX &Sol,int Nb_Sol);

int ALIAS_Simp_Proc_Void(INTERVAL_VECTOR &Box);

int Solve_General_Gradient_Interval(int Dimension_Var,int Dimension_Eq,
				    INTEGER_VECTOR &Type_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int, int,INTERVAL_VECTOR &), 
		INTERVAL_VECTOR & TheDomain, 
		int Order,
		int Iteration,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution,int Nb_Max_Solution,
				    INTEGER_MATRIX &GradInit,
				    int (* Simp_Proc)(INTERVAL_VECTOR &));
int Solve_General_Gradient_Interval(int Dimension_Var,int Dimension_Eq,
				    INTEGER_VECTOR &Type_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int, int,INTERVAL_VECTOR &), 
		INTERVAL_VECTOR & TheDomain, 
		int Order,
		int Iteration,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution,int Nb_Max_Solution,
				    int (* Simp_Proc)(INTERVAL_VECTOR &));

int Solve_General_Gradient_Interval(int Dimension_Var,int Dimension_Eq,
				    INTEGER_VECTOR &Type_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int, int,INTERVAL_VECTOR &), 
		INTERVAL_VECTOR & TheDomain, 
		int Order,
		int Iteration,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution,int Nb_Max_Solution,
				    INTEGER_MATRIX &GradInit);
int Solve_General_Gradient_Interval(int Dimension,int Dimension_Eq,
				    INTEGER_VECTOR &Type_Eq,
		INTERVAL_VECTOR 
		    (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int , int ,INTERVAL_VECTOR &), 
		INTERVAL_VECTOR & TheDomain, 
		int order,
		int Iterations,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution, int Nb_Max_Solution);

int Solve_General_Gradient_Interval(int Dimension,int Dimension_Eq,
		INTERVAL_VECTOR 
		    (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int , int ,INTERVAL_VECTOR &), 
		INTERVAL_VECTOR & TheDomain, 
		int order,
		int Iterations,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution, int Nb_Max_Solution);

int Solve_General_Gradient_Ordered_Interval(int Dimension,int Dimension_Eq,
		INTERVAL_VECTOR 
		    (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int , int ,INTERVAL_VECTOR &), 
		INTERVAL_VECTOR & TheDomain, 
		int order,
		int Iterations,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution, int Nb_Max_Solution);
int ALIAS_Read_Buffer_Gradient(char *mess,
		       int Nb_Var, int Nb_Eq,INTERVAL_MATRIX &Box,
			       INTEGER_MATRIX &GBox,
		       int *Nb_Total,
		       INTERVAL_MATRIX &Sol,int *Nb_Sol,int *Nb_Split,
		      INTEGER_VECTOR &IPar,int *Nb_Ipar,
		      VECTOR &FPar,int *Nb_Fpar,INTERVAL_MATRIX &BoxPar,
		      int *Nb_BoxPar);
int ALIAS_Add_Box_Gradient(int DimVar,int DimEq,INTERVAL_MATRIX &Box,
			   INTEGER_MATRIX &GBox,
			   int *Current_Box,int *Nb_Box,
		  INTERVAL_MATRIX New_Box, 
			   INTEGER_MATRIX GNew_Box,int Nb_New_Box,int MaxBox);

int Solve_General_JH_Interval(int Dimension,int Dimension_Eq,
			      INTEGER_VECTOR &Type_Eq,
		INTERVAL_VECTOR 
		    (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int , int ,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Hessian)(int , int ,INTERVAL_VECTOR &), 
		INTERVAL_VECTOR & TheDomain, 
		int order,
		int Iterations,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		INTERVAL_MATRIX & Solution, 
		INTEGER_VECTOR &Is_Kanto,
                int Apply_Kanto,
			      int Nb_Max_Solution,
			      INTERVAL_MATRIX &Grad_Init,
				    int (* Simp_Proc)(INTERVAL_VECTOR &));
int Solve_General_JH_Interval(int Dimension,int Dimension_Eq,
			      INTEGER_VECTOR &Type_Eq,
		INTERVAL_VECTOR 
		    (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int , int ,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Hessian)(int , int ,INTERVAL_VECTOR &), 
		INTERVAL_VECTOR & TheDomain, 
		int order,
		int Iterations,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		INTERVAL_MATRIX & Solution, 
		INTEGER_VECTOR &Is_Kanto,
                int Apply_Kanto,
			      int Nb_Max_Solution,
				    int (* Simp_Proc)(INTERVAL_VECTOR &));
int Solve_General_JH_Interval(int Dimension,int Dimension_Eq,
			      INTEGER_VECTOR &Type_Eq,
		INTERVAL_VECTOR 
		    (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int , int ,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Hessian)(int , int ,INTERVAL_VECTOR &), 
		INTERVAL_VECTOR & TheDomain, 
		int order,
		int Iterations,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		INTERVAL_MATRIX & Solution, 
		INTEGER_VECTOR &Is_Kanto,
                int Apply_Kanto,
			      int Nb_Max_Solution,
			      INTERVAL_MATRIX &Grad_Init);
int Solve_General_JH_Interval(int Dimension,int Dimension_Eq,
		INTERVAL_VECTOR 
		    (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int , int ,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Hessian)(int , int ,INTERVAL_VECTOR &), 
		INTERVAL_VECTOR & TheDomain, 
		int order,
		int Iterations,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		INTERVAL_MATRIX & Solution, 
		INTEGER_VECTOR &Is_Kanto,
                int Apply_Kanto,
			      int Nb_Max_Solution);
int Solve_General_JH_Interval(int Dimension,int Dimension_Eq,
		INTEGER_VECTOR &Type_Eq,
		INTERVAL_VECTOR 
		    (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int , int ,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Hessian)(int , int ,INTERVAL_VECTOR &), 
		INTERVAL_VECTOR & TheDomain, 
		int order,
		int Iterations,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		INTERVAL_MATRIX & Solution, 
		INTEGER_VECTOR &Is_Kanto,
                int Apply_Kanto,
			      int Nb_Max_Solution);
int Solve_General_JH_Ordered_Interval(int Dimension,int Dimension_Eq,
		INTERVAL_VECTOR 
		    (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int , int ,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Hessian)(int , int ,INTERVAL_VECTOR &), 
		INTERVAL_VECTOR & TheDomain, 
		int order,
		int Iterations,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		INTERVAL_MATRIX & Solution, 
		INTEGER_VECTOR &Is_Kanto,
                int Apply_Kanto,
			      int Nb_Max_Solution);

int ALIAS_Read_Buffer_Hessian(char *mess,
		       int Nb_Var, int Nb_Eq,INTERVAL_MATRIX &Box,
			       INTERVAL_MATRIX &GBox,
		       int *Nb_Total,
		       INTERVAL_MATRIX &Sol,INTEGER_VECTOR &Is_Kanto,
			      int *Nb_Sol,int *Nb_Split,
		      INTEGER_VECTOR &IPar,int *Nb_Ipar,
		      VECTOR &FPar,int *Nb_Fpar,INTERVAL_MATRIX &BoxPar,
		      int *Nb_BoxPar);
int ALIAS_Add_Box_Hessian(int DimVar,int DimEq,INTERVAL_MATRIX &Box,
			   INTERVAL_MATRIX &GBox,
			   int *Current_Box,int *Nb_Box,
		  INTERVAL_MATRIX New_Box, 
			   INTERVAL_MATRIX GNew_Box,int Nb_New_Box,int MaxBox);

INTERVAL_VECTOR Compute_Interval_Function_Gradient(int Dimension,
          int Dimension_Eq,
	  INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
	  INTERVAL_MATRIX (* Gradient)(int , int ,INTERVAL_VECTOR &), 
	  INTERVAL_VECTOR &Input,int Exact);
INTERVAL_VECTOR Compute_Interval_Function_Gradient(int Dimension,
          int Dimension_Eq,INTEGER_VECTOR &Type_Eq,
	  INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
	  INTERVAL_MATRIX (* Gradient)(int , int ,INTERVAL_VECTOR &), 
	  INTERVAL_VECTOR &Input,int Exact);
INTERVAL_VECTOR Compute_Interval_Function_Gradient(int Dimension,
          int Dimension_Eq,
	  INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
	  INTERVAL_MATRIX (* Gradient)(int , int ,INTERVAL_VECTOR &), 
	  INTERVAL_MATRIX (* Hessian)(int , int ,INTERVAL_VECTOR &), 
	  INTERVAL_VECTOR &Input,int Exact);
INTERVAL_VECTOR Compute_Interval_Function_Gradient(int Dimension,
          int Dimension_Eq,INTEGER_VECTOR &Type_Eq,
	  INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
	  INTERVAL_MATRIX (* Gradient)(int, int, INTERVAL_VECTOR &), 
	  INTERVAL_VECTOR &Input, int Exact);
int Compute_Interval_Ratio_Gradient(int u,int v,int uv,
						int Dimension,
          int Dimension_Eq,
	  INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
	  INTERVAL_MATRIX (* Gradient)(int, int, INTERVAL_VECTOR &), 
	  INTERVAL_VECTOR &Input, int Exact, INTERVAL &Result);
int Slow_Solve_General_JH_Interval(int Dimension,int Dimension_Eq,
		INTERVAL_VECTOR 
		    (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int , int ,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Hessian)(int , int ,INTERVAL_VECTOR &), 
		INTERVAL_VECTOR & TheDomain, 
		int order,
		int Iterations,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		INTERVAL_MATRIX & Solution, 
		INTEGER_VECTOR &Is_Kanto,
                int Apply_Kanto,
			      int Nb_Max_Solution);
int Minimize_Maximize(int Dimension_Var,int Dimension_Eq,
			   INTEGER_VECTOR &Type_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_VECTOR & TheDomain, 
		int Iteration,int Order,
		double Accuracy_Variable,
		double Accuracy,
		double AccuracyM,
			       int Func_Has_Interval,
		      INTERVAL &Optimum,
		INTERVAL_MATRIX & Solution);
int Minimize_Maximize(int Dimension_Var,int Dimension_Eq,
			   INTEGER_VECTOR &Type_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_VECTOR & TheDomain, 
		int Iteration,int Order,
		double Accuracy_Variable,
		double Accuracy,
		double AccuracyM,
			       int Func_Has_Interval,
		      INTERVAL &Optimum,
		INTERVAL_MATRIX & Solution,
		      int (* Simp_Proc)(INTERVAL_VECTOR &));
int Minimize_Maximize(int Dimension_Var,int Dimension_Eq,
		      INTEGER_VECTOR &Type_Eq,
		      INTERVAL_VECTOR (* TheIntervalFunction)
		      (int,int,INTERVAL_VECTOR &), 
		      INTERVAL_VECTOR & TheDomain, 
		      int Iteration,int Order,
		      double Accuracy_Variable,
		      double Accuracy,
		      double AccuracyM,
		      int Func_Has_Interval,
		      INTERVAL &Optimum,
		      INTERVAL &Optimum_Max,
		      INTERVAL_MATRIX & Solution);
int Minimize_Maximize(int Dimension_Var,int Dimension_Eq,
		      INTEGER_VECTOR &Type_Eq,
		      INTERVAL_VECTOR (* TheIntervalFunction)
		      (int,int,INTERVAL_VECTOR &), 
		      INTERVAL_VECTOR & TheDomain, 
		      int Iteration,int Order,
		      double Accuracy_Variable,
		      double Accuracy,
		      double AccuracyM,
		      int Func_Has_Interval,
		      INTERVAL &Optimum,
		      INTERVAL &Optimum_Max,
		      INTERVAL_MATRIX & Solution,
		      int (* Simp_Proc)(INTERVAL_VECTOR &));
int Minimize_Maximize_Gradient(int Dimension_Var,int Dimension_Eq,
				    INTEGER_VECTOR &Type_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int, int,INTERVAL_VECTOR &), 
		INTERVAL_VECTOR & TheDomain, 
		int Iteration,int Order,
		double Accuracy_Variable,
		double Accuracy,
		double Accuracy_Extremum,
			       int Func_Has_Interval,
		      INTERVAL &Optimum,
		INTERVAL_MATRIX & Solution,
		      int (* Simp_Proc)(INTERVAL_VECTOR &));
int Minimize_Maximize_Gradient(int Dimension_Var,int Dimension_Eq,
				    INTEGER_VECTOR &Type_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int, int,INTERVAL_VECTOR &), 
		INTERVAL_VECTOR & TheDomain, 
		int Iteration,int Order,
		double Accuracy_Variable,
		double Accuracy,
		double Accuracy_Extremum,
			       int Func_Has_Interval,
		      INTERVAL &Optimum,
		INTERVAL_MATRIX & Solution);
int Minimize_Maximize_Gradient(int Dimension_Var,int Dimension_Eq,
				    INTEGER_VECTOR &Type_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int, int,INTERVAL_VECTOR &), 
		INTERVAL_VECTOR & TheDomain, 
		int Iteration,
			       int Order,
		double Accuracy_Variable,
		double Accuracy,
		double Accuracy_Extremum,
			       int Func_Has_Interval,
			       INTERVAL &Optimum,
			       INTERVAL &Optimum_Max,
		INTERVAL_MATRIX & Solution);
int Minimize_Maximize_Gradient(int Dimension_Var,int Dimension_Eq,
				    INTEGER_VECTOR &Type_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int, int,INTERVAL_VECTOR &), 
		INTERVAL_VECTOR & TheDomain, 
		int Iteration,
			       int Order,
		double Accuracy_Variable,
		double Accuracy,
		double Accuracy_Extremum,
			       int Func_Has_Interval,
			       INTERVAL &Optimum,
			       INTERVAL &Optimum_Max,
		INTERVAL_MATRIX & Solution,
		      int (* Simp_Proc)(INTERVAL_VECTOR &));
int Solve_Simplex(int Dimension_Var,int Dimension_Eq,int Nb_nl,
		  INTEGER_VECTOR &Type_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
        void (* Compute_Non_Linear)(INTERVAL_VECTOR &x,INTERVAL_VECTOR &X),
        void (* Compute_Coeff_Linear)(MATRIX &U),
        double Max_Diam,int Full_Simplex,
		INTERVAL_VECTOR & TheDomain, 
		int Order,
		int Iteration,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution,int Nb_Max_Solution,
				    int (* Simp_Proc)(INTERVAL_VECTOR &));

int Solve_Simplex(int Dimension_Var,int Dimension_Eq,int Nb_nl,
		  INTEGER_VECTOR &Type_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
        void (* Compute_Non_Linear)(INTERVAL_VECTOR &x,INTERVAL_VECTOR &X),
        void (* Compute_Coeff_Linear)(MATRIX &U),
        double Max_Diam,int Full_Simplex,
		INTERVAL_VECTOR & TheDomain, 
		int Order,
		int Iteration,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution,int Nb_Max_Solution);
int Solve_Simplex(int Dimension_Var,int Dimension_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
        void (* Compute_Non_Linear)(INTERVAL_VECTOR &x,INTERVAL_VECTOR &X),
        void (* Compute_Coeff_Linear)(MATRIX &U),
		  double Max_Diam,int Full_Simplex,
		INTERVAL_VECTOR & TheDomain, 
		int Order,
		int Iteration,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution,int Nb_Max_Solution);
int Solve_Simplex_Gradient(int Dimension_Var,int Dimension_Eq,
			   int Dimension_NL,INTEGER_VECTOR &Type_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int, int,INTERVAL_VECTOR &), 
	void (* Compute_Non_Linear)(INTERVAL_VECTOR &x,INTERVAL_VECTOR &X),
	void (* Compute_Gradient_Non_Linear)(INTERVAL_VECTOR &x,
					     INTERVAL_MATRIX &X),
	void (* Compute_Coeff_Linear)(MATRIX &U),
        double Max_Diam,int Full_Simplex,
		INTERVAL_VECTOR & TheDomain, 
		int Order,
		int Iteration,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution,int Nb_Max_Solution,
			   int Use_GradNL);
int Solve_Simplex_Gradient(int Dimension_Var,int Dimension_Eq,
			   int Dimension_NL,INTEGER_VECTOR &Type_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int, int,INTERVAL_VECTOR &), 
	void (* Compute_Non_Linear)(INTERVAL_VECTOR &x,INTERVAL_VECTOR &X),
	void (* Compute_Gradient_Non_Linear)(INTERVAL_VECTOR &x,
					     INTERVAL_MATRIX &X),
	void (* Compute_Coeff_Linear)(MATRIX &U),
        double Max_Diam,int Full_Simplex,
		INTERVAL_VECTOR & TheDomain, 
		int Order,
		int Iteration,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution,int Nb_Max_Solution,
			   int Use_GradNL,
				    int (* Simp_Proc)(INTERVAL_VECTOR &));
void Compute_Gradient_Non_Linear_Void(INTERVAL_VECTOR &X,INTERVAL_MATRIX &J);
int Solve_Simplex_Gradient(int Dimension_Var,int Dimension_Eq,
			   int Dimension_NL,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int, int,INTERVAL_VECTOR &), 
	void (* Compute_Non_Linear)(INTERVAL_VECTOR &x,INTERVAL_VECTOR &X),
	void (* Compute_Gradient_Non_Linear)(INTERVAL_VECTOR &x,
					     INTERVAL_MATRIX &X),
	void (* Compute_Coeff_Linear)(MATRIX &U),
        double Max_Diam,int Full_Simplex,
		INTERVAL_VECTOR & TheDomain, 
		int Order,
		int Iteration,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution,int Nb_Max_Solution,
			   int Use_GradNL);
int Solve_Simplex_Gradient(int Dimension_Var,int Dimension_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int, int,INTERVAL_VECTOR &), 
	void (* Compute_Non_Linear)(INTERVAL_VECTOR &x,INTERVAL_VECTOR &X),
	void (* Compute_Gradient_Non_Linear)(INTERVAL_VECTOR &x,
					     INTERVAL_MATRIX &X),
	void (* Compute_Coeff_Linear)(MATRIX &U),
        double Max_Diam,int Full_Simplex,
		INTERVAL_VECTOR & TheDomain, 
		int Order,
		int Iteration,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution,int Nb_Max_Solution,
			   int Use_GradNL);
int Solve_Simplex_Gradient(int Dimension_Var,int Dimension_Eq,
			   int Dimension_NL,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int, int,INTERVAL_VECTOR &), 
	void (* Compute_Non_Linear)(INTERVAL_VECTOR &x,INTERVAL_VECTOR &X),
	void (* Compute_Coeff_Linear)(MATRIX &U),
        double Max_Diam,int Full_Simplex,
		INTERVAL_VECTOR & TheDomain, 
		int Order,
		int Iteration,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution,int Nb_Max_Solution);
int Solve_Simplex_Gradient(int Dimension_Var,int Dimension_Eq,
			   int Dimension_NL,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int, int,INTERVAL_VECTOR &), 
	void (* Compute_Non_Linear)(INTERVAL_VECTOR &x,INTERVAL_VECTOR &X),
	void (* Compute_Coeff_Linear)(MATRIX &U),
        double Max_Diam,int Full_Simplex,
		INTERVAL_VECTOR & TheDomain, 
		int Order,
		int Iteration,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution,int Nb_Max_Solution,
				    int (* Simp_Proc)(INTERVAL_VECTOR &));
int Solve_Simplex_Gradient(int Dimension_Var,int Dimension_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int, int,INTERVAL_VECTOR &), 
	void (* Compute_Non_Linear)(INTERVAL_VECTOR &x,INTERVAL_VECTOR &X),
	void (* Compute_Gradient_Non_Linear)(INTERVAL_VECTOR &x,
					     INTERVAL_MATRIX &X),
	void (* Compute_Coeff_Linear)(MATRIX &U),
        double Max_Diam,int Full_Simplex,
		INTERVAL_VECTOR & TheDomain, 
		int Order,
		int Iteration,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution,int Nb_Max_Solution);
int Solve_Simplex_Gradient(int Dimension_Var,int Dimension_Eq,int nbl,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int, int,INTERVAL_VECTOR &), 
	void (* Compute_Non_Linear)(INTERVAL_VECTOR &x,INTERVAL_VECTOR &X),
	void (* Compute_Gradient_Non_Linear)(INTERVAL_VECTOR &x,
					     INTERVAL_MATRIX &X),
	void (* Compute_Coeff_Linear)(MATRIX &U),
        double Max_Diam,int Full_Simplex,
		INTERVAL_VECTOR & TheDomain, 
		int Order,
		int Iteration,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution,int Nb_Max_Solution);
int Solve_Simplex_Gradient(int Dimension_Var,int Dimension_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int, int,INTERVAL_VECTOR &), 
	void (* Compute_Non_Linear)(INTERVAL_VECTOR &x,INTERVAL_VECTOR &X),
	void (* Compute_Coeff_Linear)(MATRIX &U),
        double Max_Diam,int Full_Simplex,
		INTERVAL_VECTOR & TheDomain, 
		int Order,
		int Iteration,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution,int Nb_Max_Solution);
int Solve_Simplex_Gradient(int Dimension_Var,int Dimension_Eq,
			   int Dimension_NL,INTEGER_VECTOR &Type_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int, int,INTERVAL_VECTOR &), 
	void (* Compute_Non_Linear)(INTERVAL_VECTOR &x,INTERVAL_VECTOR &X),
	void (* Compute_Coeff_Linear)(MATRIX &U),
        double Max_Diam,int Full_Simplex,
		INTERVAL_VECTOR & TheDomain, 
		int Order,
		int Iteration,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution,int Nb_Max_Solution);
int Solve_Simplex_Gradient(int Dimension_Var,int Dimension_Eq,
			   int Dimension_NL,INTEGER_VECTOR &Type_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int, int,INTERVAL_VECTOR &), 
	void (* Compute_Non_Linear)(INTERVAL_VECTOR &x,INTERVAL_VECTOR &X),
	void (* Compute_Coeff_Linear)(MATRIX &U),
        double Max_Diam,int Full_Simplex,
		INTERVAL_VECTOR & TheDomain, 
		int Order,
		int Iteration,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution,int Nb_Max_Solution,
			   INTEGER_MATRIX &Grad_Init);
int Solve_Simplex_Gradient(int Dimension_Var,int Dimension_Eq,
			   int Dimension_NL,INTEGER_VECTOR &Type_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int, int,INTERVAL_VECTOR &), 
	void (* Compute_Non_Linear)(INTERVAL_VECTOR &x,INTERVAL_VECTOR &X),
	void (* Compute_Gradient_Non_Linear)(INTERVAL_VECTOR &x,
					     INTERVAL_MATRIX &X),
	void (* Compute_Coeff_Linear)(MATRIX &U),
        double Max_Diam,int Full_Simplex,
		INTERVAL_VECTOR & TheDomain, 
		int Order,
		int Iteration,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution,int Nb_Max_Solution,
			   int Use_GradNL,INTEGER_MATRIX &Grad_Init);
int Solve_Simplex_Gradient(int Dimension_Var,int Dimension_Eq,
			   int Dimension_NL,INTEGER_VECTOR &Type_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int, int,INTERVAL_VECTOR &), 
	void (* Compute_Non_Linear)(INTERVAL_VECTOR &x,INTERVAL_VECTOR &X),
	void (* Compute_Coeff_Linear)(MATRIX &U),
        double Max_Diam,int Full_Simplex,
		INTERVAL_VECTOR & TheDomain, 
		int Order,
		int Iteration,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution,int Nb_Max_Solution,
			   int (* Simp_Proc)(INTERVAL_VECTOR &));
int Solve_Simplex_Gradient(int Dimension_Var,int Dimension_Eq,
			   int Dimension_NL,INTEGER_VECTOR &Type_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int, int,INTERVAL_VECTOR &), 
	void (* Compute_Non_Linear)(INTERVAL_VECTOR &x,INTERVAL_VECTOR &X),
	void (* Compute_Coeff_Linear)(MATRIX &U),
        double Max_Diam,int Full_Simplex,
		INTERVAL_VECTOR & TheDomain, 
		int Order,
		int Iteration,
		int Stop_First_Sol,
		double Accuracy_Variable,
		double Accuracy,
		double Dist_Sol_Diff,
		INTERVAL_MATRIX & Solution,int Nb_Max_Solution,
			   INTEGER_MATRIX &Grad_Init,
			   int (* Simp_Proc)(INTERVAL_VECTOR &));

int ALIAS_Start_Continuation(int Nb_Var,int Dimension_Eq,int NUM,
			     INTERVAL_MATRIX &Solutions,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int, int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Hessian)(int, int, INTERVAL_VECTOR &), 
		     double Accuracy_Var,
		     double Accuracy,
	 	     double *z,
		     double delta_l25,
		     double min_delta_l25,INTERVAL &L25,int sens,
			     MATRIX &BRANCH,int *NB_BRANCH);
int ALIAS_Start_Continuation(int Nb_Var,int Dimension_Eq,int NUM,
			     INTERVAL_MATRIX &Solutions,
		 INTEGER_MATRIX &APOW,MATRIX &ACONS,
		 VECTOR &LI,
		 int NB_EQV,int NB_VARV,MATRIX &AVARV,
		     double Accuracy_Var,
		     double Accuracy,
	 	     double *ALIAS_z,
		     double delta_l25,
		     double min_delta_l25,INTERVAL &ALIAS_L25,int sens,
			     MATRIX &BRANCH,int *NB_BRANCH,
			     void (* Update)(INTEGER_MATRIX &APOW,
					     MATRIX &ACONS,VECTOR &LI,
					     MATRIX &AVARV,double param));
int ALIAS_Start_Continuation(int Nb_Var,int Dimension_Eq,int NUM,
			     INTERVAL_MATRIX &Solutions,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int, int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Hessian)(int, int, INTERVAL_VECTOR &), 
		     double Accuracy_Var,
		     double Accuracy,
	 	     double *ALIAS_z,
		     double delta_l25,
		     double min_delta_l25,INTERVAL &ALIAS_L25,int sens,
			     MATRIX &BRANCH,int *NB_BRANCH,
	      int  ALIAS_End_Continuation(MATRIX &,int,int,double,INTERVAL &));
int ALIAS_Full_Continuation(int Nb_Var,int Dimension_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int, int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Hessian)(int, int, INTERVAL_VECTOR &), 
			    INTERVAL_VECTOR &Domain,
			    int Iterations,
		     double Accuracy_Var,
		     double Accuracy,
	 	     double *z,
		     double delta_l25,
		     double min_delta_l25,double min_delta_init,
			    INTERVAL &L25,int sens,
			     MATRIX &FINAL_BRANCH,int *Nb_Point);
int ALIAS_Full_Continuation(int Nb_Var,int Dimension_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int, int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Hessian)(int, int, INTERVAL_VECTOR &), 
		int NUM,INTERVAL_MATRIX &Solutions,
	INTERVAL_VECTOR &Domain,
			    int Iterations,
		     double Accuracy_Var,
		     double Accuracy,
	 	     double *ALIAS_z,
		     double delta_l25,
		     double min_delta_l25,INTERVAL &ALIAS_L25,int sens,
			     MATRIX &FINAL_BRANCH,int *Nb_Point);
int ALIAS_Full_Continuation(int Nb_Var,int Dimension_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int, int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Hessian)(int, int, INTERVAL_VECTOR &), 
	INTERVAL_VECTOR (* RangeFunction)(double,INTERVAL_VECTOR &), 
			    INTERVAL_VECTOR &Domain,
			    int Iterations,
		     double Accuracy_Var,
		     double Accuracy,
	 	     double *ALIAS_z,
		     double delta_l25,
		     double min_delta_l25,
			    double min_delta_init,INTERVAL &ALIAS_L25,int sens,
			     MATRIX &FINAL_BRANCH,int *Nb_Point);
int ALIAS_Full_Continuation(int Nb_Var,int Dimension_Eq,
	INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Gradient)(int, int,INTERVAL_VECTOR &), 
		INTERVAL_MATRIX (* Hessian)(int, int, INTERVAL_VECTOR &), 
	INTERVAL_VECTOR (* RangeFunction)(double,INTERVAL_VECTOR &), 
		int NUM,INTERVAL_MATRIX &Solutions,
	INTERVAL_VECTOR &Domain,
			    int Iterations,
		     double Accuracy_Var,
		     double Accuracy,
	 	     double *ALIAS_z,
		     double delta_l25,
		     double min_delta_l25,INTERVAL &ALIAS_L25,int sens,
			     MATRIX &FINAL_BRANCH,int *Nb_Point);
INTERVAL Slow_Determinant(INTERVAL_MATRIX &A);
INTERVAL Slow_NonZero_Determinant(INTERVAL_MATRIX &A);
INTERVAL Medium_Determinant(INTERVAL_MATRIX &A);
INTERVAL Fast_Determinant(INTERVAL_MATRIX &A);
INTERVAL Very_Fast_Determinant(INTERVAL_MATRIX &A);
INTERVAL Medium_Determinant22(INTERVAL_MATRIX &A,int Dim,
			      INTEGER_VECTOR &ROW,
			      INTEGER_VECTOR &COL,
	  INTERVAL (* TheDet22)(INTEGER_VECTOR &,
				INTEGER_VECTOR &,INTERVAL_VECTOR &),
			      INTERVAL_VECTOR &Input);
INTERVAL Medium_Determinant22(INTERVAL_MATRIX &A,
	  INTERVAL (* TheDet22)(INTEGER_VECTOR &,
				INTEGER_VECTOR &,INTERVAL_VECTOR &),
			      INTERVAL_VECTOR &Input);
INTERVAL Slow_Determinant22(INTERVAL_MATRIX &A,int Dim,
			      INTEGER_VECTOR &ROW,
			      INTEGER_VECTOR &COL,
	  INTERVAL (* TheDet22)(INTEGER_VECTOR &,
				INTEGER_VECTOR &,INTERVAL_VECTOR &),
			      INTERVAL_VECTOR &Input);
INTERVAL Slow_Determinant22(INTERVAL_MATRIX &A,
	  INTERVAL (* TheDet22)(INTEGER_VECTOR &,
				INTEGER_VECTOR &,INTERVAL_VECTOR &),
			      INTERVAL_VECTOR &Input);
INTERVAL Fast_Determinant22(INTERVAL_MATRIX &A,int Dim,
			      INTEGER_VECTOR &ROW,
			      INTEGER_VECTOR &COL,
	  INTERVAL (* TheDet22)(INTEGER_VECTOR &,
				INTEGER_VECTOR &,INTERVAL_VECTOR &),
			      INTERVAL_VECTOR &Input);
INTERVAL Fast_Determinant22(INTERVAL_MATRIX &A,
	  INTERVAL (* TheDet22)(INTEGER_VECTOR &,
				INTEGER_VECTOR &,INTERVAL_VECTOR &),
			      INTERVAL_VECTOR &Input);
double Determinant(MATRIX &J);
double Hadamard_Determinant(MATRIX &J);
INTERVAL Fast_Derivative_Determinant(INTERVAL_MATRIX &A,INTERVAL_MATRIX &AG);
INTERVAL Medium_Derivative_Determinant(INTERVAL_MATRIX &A,INTERVAL_MATRIX &AG);
INTERVAL Slow_Derivative_Determinant(INTERVAL_MATRIX &A,INTERVAL_MATRIX &AG);
INTERVAL Fast_Hessian_Determinant(INTERVAL_MATRIX &A,INTERVAL_MATRIX &AG,
				  INTERVAL_MATRIX &AH);
INTERVAL Medium_Hessian_Determinant(INTERVAL_MATRIX &A,INTERVAL_MATRIX &AG,
				  INTERVAL_MATRIX &AH);
INTERVAL Slow_Hessian_Determinant(INTERVAL_MATRIX &A,INTERVAL_MATRIX &AG,
				  INTERVAL_MATRIX &AH);
INTERVAL Medium_Determinant22(INTERVAL_MATRIX &A,int Dim,
			      INTEGER_VECTOR &ROW,
			      INTEGER_VECTOR &COL,int Minor,
	  INTERVAL (* TheDet22)(INTEGER_VECTOR &,
				INTEGER_VECTOR &,INTERVAL_VECTOR &),
			      INTERVAL_VECTOR &Input);
INTERVAL Medium_Determinant22(INTERVAL_MATRIX &A,int Minor,
	  INTERVAL (* TheDet22)(INTEGER_VECTOR &,
				INTEGER_VECTOR &,INTERVAL_VECTOR &),
			      INTERVAL_VECTOR &Input);
INTERVAL Slow_Determinant22(INTERVAL_MATRIX &A,int Dim,
			      INTEGER_VECTOR &ROW,
			      INTEGER_VECTOR &COL,int Minor,
	  INTERVAL (* TheDet22)(INTEGER_VECTOR &,
				INTEGER_VECTOR &,INTERVAL_VECTOR &),
			      INTERVAL_VECTOR &Input);
INTERVAL Slow_Determinant22(INTERVAL_MATRIX &A,int Minor,
	  INTERVAL (* TheDet22)(INTEGER_VECTOR &,
				INTEGER_VECTOR &,INTERVAL_VECTOR &),
			      INTERVAL_VECTOR &Input);
INTERVAL Fast_Determinant22(INTERVAL_MATRIX &A,int Dim,
			      INTEGER_VECTOR &ROW,
			      INTEGER_VECTOR &COL,int Minor,
	  INTERVAL (* TheDet22)(INTEGER_VECTOR &,
				INTEGER_VECTOR &,INTERVAL_VECTOR &),
			      INTERVAL_VECTOR &Input);
INTERVAL Fast_Determinant22(INTERVAL_MATRIX &A,int Minor,
	  INTERVAL (* TheDet22)(INTEGER_VECTOR &,
				INTEGER_VECTOR &,INTERVAL_VECTOR &),
			      INTERVAL_VECTOR &Input);

INTERVAL Determinant22(INTERVAL_MATRIX &A,int Dim,
			      INTEGER_VECTOR &ROW,
			      INTEGER_VECTOR &COL,int Minor,int Row,
	  INTERVAL (* TheDet22)(INTEGER_VECTOR &,
				INTEGER_VECTOR &,INTERVAL_VECTOR &),
			      INTERVAL_VECTOR &Input);
INTERVAL Determinant22(INTERVAL_MATRIX &A,int Minor,int Row,
	  INTERVAL (* TheDet22)(INTEGER_VECTOR &,
				INTEGER_VECTOR &,INTERVAL_VECTOR &),
			      INTERVAL_VECTOR &Input);
int Solve_Distance(int Dimension_Var,int Dimension_Eq,
		   int Dim_Var_Aux,int Dim_Eq_Aux,
		   INTEGER_VECTOR &Type_Eq,
		   INTEGER_MATRIX &APOW,MATRIX &ACONS,
		   VECTOR &LI,
		   int NB_EQV,int NB_VARV,MATRIX &AVARV,
		   INTERVAL_VECTOR & TheDomain, 
		   int Iteration,
		   double Accuracy,
		   int Stop_First_Sol,
		   INTERVAL_MATRIX & Solution,
		   int Nb_Max_Solution,
		   int (* Simp_Proc)(INTERVAL_VECTOR &));

int Solve_Distance(int Dimension_Var,int Dimension_Eq,
		   INTEGER_VECTOR &Type_Eq,
		   INTEGER_MATRIX &APOW,MATRIX &ACONS,
		   VECTOR &LI,
		   int NB_EQV,int NB_VARV,MATRIX &AVARV,
		   INTERVAL_VECTOR & TheDomain, 
		   int Iteration,
		   double Accuracy,
		   int Stop_First_Sol,
		   INTERVAL_MATRIX & Solution,
		   int Nb_Max_Solution,
		   int (* Simp_Proc)(INTERVAL_VECTOR &));
int Solve_Distance(int Dimension_Var,int Dimension_Eq,
		   INTEGER_VECTOR &Type_Eq,
		   INTEGER_MATRIX &APOW,MATRIX &ACONS,
		   VECTOR &LI,
		   int NB_EQV,int NB_VARV,MATRIX &AVARV,
		   INTERVAL_VECTOR & TheDomain, 
		   int Iteration,
		   double Accuracy,
		   int Stop_First_Sol,
		   INTERVAL_MATRIX & Solution,
		   int Nb_Max_Solution);
int Solve_Distance(int Dimension_Var,int Dimension_Eq,
		   INTEGER_VECTOR &Type_Eq,
		   INTEGER_MATRIX &APOW,MATRIX &ACONS,
		   VECTOR &LI,
		   INTERVAL_VECTOR & TheDomain, 
		   int Iteration,
		   double Accuracy,
		   int Stop_First_Sol,
		   INTERVAL_MATRIX & Solution,
		   int Nb_Max_Solution);
int Solve_Distance(int Dimension_Var,int Dimension_Eq,
		   INTEGER_VECTOR &Type_Eq,
		   INTEGER_MATRIX &APOW,MATRIX &ACONS,
		   VECTOR &LI,
		   INTERVAL_VECTOR & TheDomain, 
		   int Iteration,
		   double Accuracy,
		   int Stop_First_Sol,
		   INTERVAL_MATRIX & Solution,
		   int Nb_Max_Solution,
		   int (* Simp_Proc)(INTERVAL_VECTOR &));
int Solve_Distance(int Dimension_Var,int Dimension_Eq,
		   INTEGER_MATRIX &APOW,MATRIX &ACONS,
		   VECTOR &LI,
		   INTERVAL_VECTOR & TheDomain, 
		   int Iteration,
		   double Accuracy,
		   int Stop_First_Sol,
		   INTERVAL_MATRIX & Solution,
		   int Nb_Max_Solution);
int Solve_Distance(int Dimension_Var,int Dimension_Eq,
		   INTEGER_MATRIX &APOW,MATRIX &ACONS,
		   VECTOR &LI,
		   INTERVAL_VECTOR & TheDomain, 
		   int Iteration,
		   double Accuracy,
		   int Stop_First_Sol,
		   INTERVAL_MATRIX & Solution,
		   int Nb_Max_Solution,
		   int (* Simp_Proc)(INTERVAL_VECTOR &));
int Solve_Distance(int Dimension_Var,int Dimension_Eq,
		   INTEGER_MATRIX &APOW,MATRIX &ACONS,
		   VECTOR &LI,
		   int NB_EQV,int NB_VARV,MATRIX &AVARV,
		   INTERVAL_VECTOR & TheDomain, 
		   int Iteration,
		   double Accuracy,
		   int Stop_First_Sol,
		   INTERVAL_MATRIX & Solution,
		   int Nb_Max_Solution);
int Solve_Distance(int Dimension_Var,int Dimension_Eq,
		   INTEGER_MATRIX &APOW,MATRIX &ACONS,
		   VECTOR &LI,
		   int NB_EQV,int NB_VARV,MATRIX &AVARV,
		   INTERVAL_VECTOR & TheDomain, 
		   int Iteration,
		   double Accuracy,
		   int Stop_First_Sol,
		   INTERVAL_MATRIX & Solution,
		   int Nb_Max_Solution,
		   int (* Simp_Proc)(INTERVAL_VECTOR &));
int ALIAS_Ajuste_Square(INTERVAL &U,INTERVAL &W,double *LOW,double *HIGH);
int Newton(int Dimension,int Dimension_Eq,
	   INTEGER_MATRIX &APOW,MATRIX &ACONS,VECTOR &LI,
	   int NB_EQV,int NB_VARV,MATRIX &AVARV,
	   VECTOR &Input,double Accuracy,int Max_Iter,VECTOR &Residu);
int Newton(int Dimension,int Dimension_Eq,
	   INTEGER_MATRIX &APOW,MATRIX &ACONS,VECTOR &LI,
	   int NB_EQV,int NB_VARV,MATRIX &AVARV,
	   VECTOR &Input,INTERVAL_VECTOR &Boite,
	   double Accuracy,int Max_Iter,VECTOR &Residu);
void ALIAS_Free_Storage(int *Current,int *nb_box,int DimVar,
		       INTERVAL_MATRIX &Box);
void ALIAS_Free_Storage(int *Current,int *nb_box,int DimVar,int DimEq,
		       INTERVAL_MATRIX &Box,INTERVAL_MATRIX &GBox);
int Use_Simplex(INTERVAL_VECTOR &Input, int n,int nb_eq,
        void (* Compute_Non_Linear)(INTERVAL_VECTOR &x,INTERVAL_VECTOR &X,
				    MATRIX &A),
	MATRIX (* Compute_Linear)(INTERVAL_VECTOR &x));

INTERVAL_VECTOR Coeff_CharPoly(int Size,INTERVAL_MATRIX &A);
//filtrage des boites par la solutions dans PP1
int Sol_Reduction(int Dimension,int Dimension_Eq,
		  INTERVAL_MATRIX &BBOX,
		  INTERVAL_VECTOR &P, INTERVAL_VECTOR &PP1,
		  int *nb_box,
		  int type,
		  int (* Simp_Proc)(INTERVAL_VECTOR &));
int Sol_Reduction(int Dimension_Var,int Dimension_Eq,
		  INTERVAL_MATRIX &BBOX,
		  INTERVAL_MATRIX &GBBOX,
		  INTERVAL_MATRIX (* Gradient)(int, int,INTERVAL_VECTOR &), 
		  INTERVAL_VECTOR &P, INTERVAL_VECTOR &PP1,
		  int current_box,int *nb_box,
		  int nb_max_box,
		  int type,
		  int (* Simp_Proc)(INTERVAL_VECTOR &));
INTERVAL ALIAS_Signum(INTERVAL &X);
INTERVAL ALIAS_Diff_Signum(INTERVAL &X);
INTERVAL ALIAS_Diff_Abs(INTERVAL &X);
INTERVAL ALIAS_Ceil(INTERVAL &X);
INTERVAL ALIAS_Floor(INTERVAL &X);
INTERVAL ALIAS_Round(INTERVAL &X);
int Gauss_Elimination_Derivative(const MATRIX Cond,INTERVAL_MATRIX &Ain,
INTERVAL_MATRIX &ACondin,
 const INTERVAL_VECTOR bin, 
 const INTERVAL_VECTOR bCondin, 
INTERVAL_VECTOR &bout, 
INTERVAL_VECTOR & Param,
INTERVAL_VECTOR (* Func)(int l1, int l2, INTERVAL_VECTOR & v_IS),
INTERVAL_MATRIX (* JFunc)(int l1, int l2, INTERVAL_VECTOR & v_IS),
INTERVAL_VECTOR (* bFunc)(int l1, int l2, INTERVAL_VECTOR & v_IS),
INTERVAL_MATRIX (* JbFunc)(int l1, int l2, INTERVAL_VECTOR & v_IS));
int Gauss_Elimination(INTERVAL_MATRIX &Ain,
		      INTERVAL_VECTOR &b,INTERVAL_VECTOR &b_out);
//calcul de determinant par elimination de Gauss
int ALIAS_Det_By_Gaussian_Elim(INTERVAL_MATRIX &B, INTERVAL &DET);

//procedure de calcul d'integrale definie 
int Integrate(
	      INTERVAL_VECTOR (* TheIntervalFunction)
	      (int,int,INTERVAL_VECTOR &), 
	      INTERVAL & TheDomain, 
	      int Iteration,
	      double Accuracy,
	      INTERVAL & Result);
int IntegrateTrapeze(
	      INTERVAL_VECTOR (* TheIntervalFunction)
	      (int,int,INTERVAL_VECTOR &), 
	      INTERVAL_VECTOR (* SecondDerivative)
	      (int,int,INTERVAL_VECTOR &), 
	      INTERVAL & TheDomain, 
	      int Iteration,
	      double Accuracy,
	      INTERVAL & Result);
int IntegrateRectangle(
	      INTERVAL_VECTOR (* TheIntervalFunction)
	      (int,int,INTERVAL_VECTOR &), 
	      INTERVAL_VECTOR (* SecondDerivative)
	      (int,int,INTERVAL_VECTOR &), 
	      INTERVAL & TheDomain, 
	      int Iteration,
	      double Accuracy,
	      INTERVAL & Result);
int IntegrateTaylor(
	      INTERVAL_VECTOR (* CoeffTaylor)
	      (int,int,INTERVAL_VECTOR &), 
	      int Order,
	      INTERVAL & TheDomain, 
	      int Iteration,
	      double Accuracy,
	      INTERVAL & Result);
int IntegrateMultiRectangle(
	      INTERVAL_VECTOR (* Function)
	      (int,int,INTERVAL_VECTOR &), 
	      INTERVAL_VECTOR (* Second_Derivative)
	      (int,int,INTERVAL_VECTOR &), 
	      INTERVAL_MATRIX (* Gradient)(int, int,INTERVAL_VECTOR &),
	      INTERVAL_VECTOR & TheDomain, 
	      int Iteration,
	      double Accuracy,
	      INTERVAL & Result);
int IntegrateMultiRectangle(
	      INTERVAL_VECTOR (* Function)
	      (int,int,INTERVAL_VECTOR &), 
	      INTERVAL_VECTOR (* Second_Derivative)
	      (int,int,INTERVAL_VECTOR &), 
	      INTERVAL_VECTOR & TheDomain, 
	      int Iteration,
	      double Accuracy,
	      INTERVAL & Result);
int IntegrateMultiTaylor(
	      INTERVAL_VECTOR (* CoeffInt)
	      (int,int,INTERVAL_VECTOR &), 
	      INTERVAL_VECTOR (* Rest_Taylor)
	      (int,int,INTERVAL_VECTOR &), 
	      INTEGER_MATRIX &APOWERINT,
	      INTEGER_MATRIX &APOWERREM,
	      int nb_rem,
	      int Order,
	      INTERVAL_VECTOR & TheDomain, 
	      int Iteration,
	      double Accuracy,
	      INTERVAL & Result);
int IntegrateMultiTaylor(
	      INTERVAL_VECTOR (* CoeffInt)
	      (int,int,INTERVAL_VECTOR &), 
	      INTERVAL_VECTOR (* Rest_Taylor)
	      (int,int,INTERVAL_VECTOR &), 
	      INTEGER_MATRIX &APOWERINT,
	      int Order,
	      INTERVAL_VECTOR & TheDomain, 
	      int Iteration,
	      double Accuracy,
	      INTERVAL & Result);
INTERVAL ALIAS_Fast_Determinant_Void(INTERVAL_MATRIX &A,INTERVAL_VECTOR &X);
int ALIAS_A_Cond_Void(int dimA,
INTERVAL_VECTOR (* Func)(int l1, int l2,INTERVAL_VECTOR & v_IS), INTERVAL_VECTOR & v_IS,INTERVAL_MATRIX &A);
INTERVAL_MATRIX ALIAS_Cond_Void(INTERVAL_VECTOR &v_IS);
int Matrix_Is_Regular(int dimA,
	INTERVAL_VECTOR (* Func)(int l1, int l2,INTERVAL_VECTOR & v_IS),
	int (* A_Cond)(int dimA,INTERVAL_VECTOR (* Func)(int l1, int l2,INTERVAL_VECTOR & v_IS),INTERVAL_VECTOR & v_IS,INTERVAL_MATRIX &A),
	INTERVAL_MATRIX (* A_Cond_Left)(INTERVAL_VECTOR & v_IS_Left),
	INTERVAL_MATRIX (* A_Cond_Right)(INTERVAL_VECTOR & v_IS_Right),
	INTERVAL Determinant_Matrix(INTERVAL_MATRIX &A,INTERVAL_VECTOR &X),
	INTERVAL Determinant_A_Cond_Left(INTERVAL_MATRIX &A,INTERVAL_VECTOR &X),
	INTERVAL Determinant_A_Cond_Right(INTERVAL_MATRIX &A,INTERVAL_VECTOR &X),
	int Type_Cond,
        INTEGER_VECTOR &Type_Determinant,
	int Iteration,
	INTERVAL_VECTOR &Domain,
	int (* Simp)(int dimA,INTERVAL_MATRIX & Acond,INTERVAL_VECTOR & v_IS));
//sans fonction de simplification
int Matrix_Is_Regular(int dimA,
	INTERVAL_VECTOR (* Func)(int l1, int l2,INTERVAL_VECTOR & v_IS),
	int (* A_Cond)(int dimA,INTERVAL_VECTOR (* Func)(int l1, int l2,INTERVAL_VECTOR & v_IS),INTERVAL_VECTOR & v_IS,INTERVAL_MATRIX &A),
	INTERVAL_MATRIX (* A_Cond_Left)(INTERVAL_VECTOR & v_IS_Left),
	INTERVAL_MATRIX (* A_Cond_Right)(INTERVAL_VECTOR & v_IS_Right),
	INTERVAL Determinant_Matrix(INTERVAL_MATRIX &A,INTERVAL_VECTOR &X),
	INTERVAL Determinant_A_Cond_Left(INTERVAL_MATRIX &A,INTERVAL_VECTOR &X),
	INTERVAL Determinant_A_Cond_Right(INTERVAL_MATRIX &A,INTERVAL_VECTOR &X),
	int Type_Cond,
        INTEGER_VECTOR &Type_Determinant,
	int Iteration,
	INTERVAL_VECTOR &Domain);
int Matrix_Is_Regular(int dimA,
	INTERVAL_VECTOR (* Func)(int l1, int l2,INTERVAL_VECTOR & v_IS),
	INTERVAL_MATRIX (* A_Cond_Left)(INTERVAL_VECTOR & v_IS_Left),
	INTERVAL_MATRIX (* A_Cond_Right)(INTERVAL_VECTOR & v_IS_Right),
	int Type_Cond,
        INTEGER_VECTOR &Type_Determinant,
	int Iteration,
	INTERVAL_VECTOR &Domain);
int Matrix_Is_Regular(int dimA,
	INTERVAL_VECTOR (* Func)(int l1, int l2,INTERVAL_VECTOR & v_IS),
        int Type_Determinant,
	int Iteration,
	INTERVAL_VECTOR &Domain);
int Matrix_Is_Regular(int dimA,
	INTERVAL_VECTOR (* Func)(int l1, int l2,INTERVAL_VECTOR & v_IS),
        int Type_Determinant,
	int Iteration,
	INTERVAL_VECTOR &Domain,
	int (* Simp)(int dimA,INTERVAL_MATRIX & Acond,INTERVAL_VECTOR &v_IS));
int Matrix_Is_Regular(int dimA,
	INTERVAL_VECTOR (* Func)(int l1, int l2,INTERVAL_VECTOR & v_IS),
	INTERVAL_MATRIX (* A_Cond_Left)(INTERVAL_VECTOR & v_IS_Left),
	INTERVAL_MATRIX (* A_Cond_Right)(INTERVAL_VECTOR & v_IS_Right),
	int Type_Cond,
        INTEGER_VECTOR &Type_Determinant,
	int Iteration,
	INTERVAL_VECTOR &Domain,
	int (* Simp)(int dimA,INTERVAL_MATRIX & Acond,INTERVAL_VECTOR &v_IS));
int Matrix_Is_Regular(int dimA,
	INTERVAL_VECTOR (* Func)(int l1, int l2,INTERVAL_VECTOR & v_IS),
	INTERVAL_MATRIX (* A_Cond_Left)(INTERVAL_VECTOR & v_IS_Left),
	INTERVAL_MATRIX (* A_Cond_Right)(INTERVAL_VECTOR & v_IS_Right),
	int Type_Cond,
        INTEGER_VECTOR &Type_Determinant,
	int Iteration,
	INTERVAL_VECTOR &Domain);
int Matrix_Is_Regular(int dimA,
	INTERVAL_VECTOR (* Func)(int l1, int l2,INTERVAL_VECTOR & v_IS),
	INTERVAL_MATRIX (* A_Cond_Left)(INTERVAL_VECTOR & v_IS_Left),
	INTERVAL_MATRIX (* A_Cond_Right)(INTERVAL_VECTOR & v_IS_Right),
	int Type_Cond,
        INTEGER_VECTOR &Type_Determinant,
	int Iteration,
	INTERVAL_VECTOR &Domain,
	int (* Simp)(int dimA,INTERVAL_MATRIX & Acond,INTERVAL_VECTOR &v_IS));
//calcul de polynome caracteristique
INTERVAL_VECTOR Poly_Characteristic(INTERVAL_MATRIX &A);
INTERVAL_VECTOR Poly_Characteristic(MATRIX &A);
//calcul d'une borne sure sur le rayon spectral d'une matrice
int Spectral_Radius(INTERVAL_MATRIX &AA,double eps,double *ro);
int Spectral_Radius(MATRIX &AA,double eps,double *ro);
int Spectral_Radius(INTERVAL_MATRIX &AA,double eps,double *ro,double seuil);
int Spectral_Radius(MATRIX &AA,double eps,double *ro,double seuil);
int Spectral_Radius(INTERVAL_MATRIX &AA,double eps,double *ro,int iter_max);
int Spectral_Radius(MATRIX &AA,double eps,double *ro,int iter_max);
int Spectral_Radius(INTERVAL_MATRIX &AA,double eps,double *ro,int iter_max,double seuil);
int Spectral_Radius(MATRIX &AA,double eps,double *ro,int iter_max,double seuil);


int IntervalNewton(int Dim,INTERVAL_VECTOR &P,INTERVAL_VECTOR &FDIM,
		   INTERVAL_MATRIX &Grad,MATRIX &GradMid,MATRIX &InvGradMid,
		   int has_BGrad,
		   INTERVAL_VECTOR (* BgradFunc)(int,int,INTERVAL_VECTOR &), 
		   INTERVAL_MATRIX (* BgradJFunc)(int, int,INTERVAL_VECTOR &), 
		   int grad1,int grad3B1);
int IntervalNewton(int Dim,INTERVAL_VECTOR &P,INTERVAL_VECTOR &FMID,
		   INTERVAL_MATRIX &Grad,MATRIX &GradMid,MATRIX &InvGradMid);
int IntervalNewton(int Dim,INTERVAL_VECTOR &P,INTERVAL_VECTOR &FDIM,
		   INTERVAL_MATRIX &Grad,MATRIX &GradMid,MATRIX &InvGradMid,
		   int has_BGrad,
		   INTERVAL_VECTOR (* BgradFunc)(int,int,INTERVAL_VECTOR &), 
		   int grad1,int grad3B1);
int IntervalNewton(int Dim,INTERVAL_VECTOR &P,int DimVar,int DimEq,
		   int Type_Grad_Mid,MATRIX &InvGradMid,
	  INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		   INTERVAL_MATRIX (* Gradient)(int, int, INTERVAL_VECTOR &));
int IntervalNewton(int Dim,INTERVAL_VECTOR &P,
		   int Type_Grad_Mid,MATRIX &InvGradMid,
	  INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		   INTERVAL_MATRIX (* Gradient)(int, int, INTERVAL_VECTOR &));
int IntervalNewton(int Dim,INTERVAL_VECTOR &P,int DimEq,int DimVar,
		   int has_BGrad,
		   INTERVAL_VECTOR (* BgradFunc)(int,int,INTERVAL_VECTOR &), 
		   INTERVAL_MATRIX (* BgradJFunc)(int, int,INTERVAL_VECTOR &), 
		   int grad1,int grad3B1,
		   int Type_Grad_Mid,
		   MATRIX &Grad_Func_Mid,
       		   MATRIX &InvGradMid,
		  INTERVAL_VECTOR (* TheIntervalFunction)(int,int,INTERVAL_VECTOR &), 
		   INTERVAL_MATRIX (* Gradient)(int, int, INTERVAL_VECTOR &));
