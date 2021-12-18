#define MAX_UNSIGNED_SHORT	std::numeric_limits<unsigned short>::max()
#define MAX_INT				std::numeric_limits<int>::max()
#define MIN_INT				std::numeric_limits<int>::min()
#define MAX_UNSIGNED_INT	std::numeric_limits<unsigned int>::max()
#define MAX_LONG_INT		std::numeric_limits<unsigned long>::max()
#define MIN_LONG_INT		std::numeric_limits<long int>::min()
#define MAX_FLOAT			std::numeric_limits<float>::max()
#define MIN_FLOAT			std::numeric_limits<float>::min()
#define MAX_DOUBLE			std::numeric_limits<double>::max()
#define MIN_DOUBLE			std::numeric_limits<double>::min()
//#define EPSILON				1E-12
#define EPSILON_SMALL		1E-2
#define ABS(x) 				( (x < 0) ? -(x) : (x))

//#define NUM_OPOS			58
//#define NUM_REGIONS		11

//#define DEBUG				0	// setting value to 1 will print many things to the debug file
//#define TEMPDEBUG			0	// setting value to 1 will print temporary test functions
//
//#define REPORTING_INTERVAL 	7		// screen progress display
//
//#define earthRadiusKm 6371.0	// to find distance between centers given their longitudes and latitudes (Haversine formula)#pragma once


// ASSUMING CYCLES OF 1 DAY
//SIR parameters
#define BETA_SS		0.184     //Base: 0.184    , Best: 0.153   ,  Worst: 0.214
#define BETA_SF		0.0204   //Base: 0.0204   , Best: 0.017   ,  Worst: 0.0238
#define BETA_FF		0.0109    //Base: 0.0109   , Best: 0.00748 ,  Worst: 0.0143
#define BETA_FS		0.098   //Base: 0.098    , Best: 0.0673  ,  Worst: 0.128

#define Se			0.8   			  //70%-80%... sensitivity of the screening test
#define Sp          0.98 			  //98%-99.7% ... specificity of the screening test
#define X           10               //Base 5, 10, 25 ... number of imported infections in a given exogenous shock
//Base case: Sensitivity = 0.8,   Specificity=98% and    X=10/week => jama
//Best case: Sensitivity = 0.8 ,  Specificity=99.7% and  X=5/week
//Worst case: Sensitivity = 0.7 , Specificity=98% and    X=25/week


#define THETA       1.0/(3*3.0)     //(mean incubation time) or rate at which exposed individuals advance to the asymptomatic, infectious compartment
#define RHO         1.0/(3*14.0)            // (1/rho is the time to recover) rate at which infected individuals recover from disease and are removed
#define SIGMA       0.0102             //0.04423  (65%)   //0.0102 (30%)	 //(rate of symptom development) rate of symptom onset for infected individuals
#define MU           1.0/(3*4.0) //1.0/(3*1.0)             //(1/mu is the time to false positive return)rate at which false positives are returned to the Uninfected compartment


#define EPSILON     0.9464              //success rate of the vaccine, vaccine efficacy, 1 when 100% efficiency (add it next to all lambdas, it's not the case now)
#define PHI         1/(3*(7*5.4))  // 5.4 weeks         //rate of delay of vaccination effect => assumption: halflife
//#define ALPHA        1          //vaccination compliance rate
//#define ETA        1          //screening compliance rate

#define DELTA         0.0008817  		//death rate for students  //(ie. fatality rate of 0.05%=0.005) rate at which individuals in the symptomatic compartment die
#define PI            0.001166          //hospitalization rate for students (1.4%)

#define DELTA_f        0.00744		  //death rate for faculty //(ie. fatality rate of 2%) rate at which individuals in the symptomatic compartment die
#define PI_f           0.009263       //hospitalization rate for faculty (8.4%)