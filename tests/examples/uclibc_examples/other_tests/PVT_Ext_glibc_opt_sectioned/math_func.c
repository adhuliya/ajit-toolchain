#include<stdio.h>
#ifdef AJIT
// include AJIT related header files here.

#include "core_portme.h"
#endif

#include "math_func.h"

#ifdef AJIT
#define PRINTF ee_printf
#else
#define PRINTF printf
#endif

#define EPSILON 1.0e-7
/*
#define PI 3.14159265
#define PIx2 6.2831853
#define PI_BY2 1.570796325
#define PI_BY4 0.785398162
*/
#define HPI 3.141592653589
#define HPIx2 6.283185307178
#define HPI_BY2 1.570796326794
#define HPI_BY4 0.785398163397


double xx__fabs(double x){

	double y;
	if(x>0.0){
		y=x;
	}else{
		y=0.0-x;
	}

	return y;
}

double xx__fmod(double x, double y) {

	//Remainder function

	double t;
	int t_int;


	if(xx__fabs(x) < xx__fabs(y)){

		return x;			
	}else{
	
		t = x/y;
		t_int = t/1;
		t = x - (t_int*y);
		return t;		
	}
	
}

double xx__pow(double x, int y) {

	double z = 1;
	int i;
	
	if(x == 0){
		return 0;
	}

	if(y==0){
		return 1;
	}

	if(y<0){

		y = -y;
		for (i=0; i<y; i++)
			z *= x;

		z = 1/z;

	}else{

		for (i=0; i<y; i++)
			z *= x;
	}

	return z;

}

// assumption x > 0.0;
// recursive form:  will at most need to have a recursive
//                  call depth of  log-base-4(depth)
double xx__pow_opt (double x, int exponent, int depth)
{

	//
	//  take care of small exponents
	//
	if(exponent < 0)
	{
		x = 1.0/x;	
		exponent = - exponent;
	}
	else if(exponent == 0)
		return(1.0);
	else if(exponent == 1)
		return (x);
	else if(exponent == 2)
		return (x*x);
	else if(exponent == 3)
		return (x*x*x);
	else if(exponent == 4)
	{
		double r = x*x;
		return (r*r);
	}

	// 
	// large exponents by recursion.
	//
	int e_by_4_floor = exponent / 4;
	int delta  = exponent & 0x3; // remainder after div by 4.

	double xroot = xx__pow_opt (x, e_by_4_floor, depth+1);

	double ret_val = xroot * xroot;
	ret_val = ret_val*ret_val;
	if(delta > 0)
		ret_val = ret_val * xx__pow_opt (x, delta, depth+1);

	//ee_printf("xx__pow_opt(%f,%d,%d) = %f\n", x,exponent,depth,ret_val);
	return(ret_val);
}

double xx__fact(double x) {

	double ret = 1;
	int i;
	for (i=1; i<=x; i++)
		ret *= i;
	return ret;
}

double xx__cos_base (double x)
{
		
	int sign_val = 0;

	double curr_term = 1.0;
	double curr_sum  = 0;
	double xsquared = x * x;
	double curr_inv_factorial = 1.0;

	int I=0;

	while (curr_term > EPSILON)
	 {
		curr_sum = (sign_val ?  (curr_sum - curr_term) :   (curr_sum + curr_term));

		curr_inv_factorial = 1.0 / ((I+1)*(I+2));
		curr_term = curr_term * xsquared * curr_inv_factorial;

		I += 2;
		sign_val = !sign_val;

		
	}
	return curr_sum;
}

double xx__sin_base (double x)
{
		
	int sign_val = 0;

	double curr_term = x;
	double curr_sum  = 0.0;
	double xsquared = x * x;
	double curr_inv_factorial = 1.0;

	int I=1;

	while (curr_term > EPSILON)
	 {
		curr_sum = (sign_val ?  (curr_sum - curr_term) :   (curr_sum + curr_term));

		curr_inv_factorial = 1.0 / ((I+1)*(I+2));
		curr_term = curr_term * xsquared * curr_inv_factorial;

		I += 2;
		sign_val = !sign_val;
	}
	return curr_sum;
}

//z: Reducing number of iterations for better timing
//Final range around 0 to pi/4;  
//Assuming input x is max < 4*pi; if not extra ifelse to be put.
//For this check range of input theta is PVT code ***
double xx__cos(double x)
{
	int flag1 = 0;
	int flag2 = 0;
	int temp;

	double result;	
	
	if(x<0.0){
		x = -x; 	
	}

	if(x >= HPIx2){	//z: x >= 2*HPI
		
		x = x - HPIx2;	//z: cos(2*HPI + theta) = cos(theta)
		if(x > HPIx2){

			temp = (int)(x/HPIx2) ;
			x = x - temp*HPIx2;
		}

	}	

	if(x >= HPI){	//z: x >= pi

		x = x - HPI;	//z: cos(pi + theta) = -cos(theta)
		flag1 = 1;
	}

	if(x >= HPI_BY2){	//z: x >= pi/2

		x = x - HPI_BY2;	//z: cos(pi/2 + theta) = -sin(theta)
		flag2 = 1;
	}

	if(x > HPI_BY4){	//z: x >= pi/4

		x = HPI_BY2 - x;	//z: cos(theta) = sin(pi/2-theta)
				//sin(theta) = cos(pi/2-theta)
		
		result = (flag2 ? (flag1 ? xx__cos_base(x) : -xx__cos_base(x)) : (flag1 ? -xx__sin_base(x) : xx__sin_base(x)));

	}else {

		result = (flag2 ? (flag1 ? xx__sin_base(x) : -xx__sin_base(x)) : (flag1 ? -xx__cos_base(x) : xx__cos_base(x)));

	}

	return result;
}

//z: Reducing number of iterations for better timing
//Final range around 0 to pi/4;
//Assuming input x is max < 4*pi; if not extra ifelse to be put.
//For this check range of input theta is PVT code ***
double xx__sin(double x)
{
	int flag1 = 0;
	int flag2 = 0;
	int flag_res = 0;
	int temp;
	double result;

	if(x<0.0){
		x = -x; 
		flag_res =1;	
	}	
	
	if(x >= HPIx2){	//z: x >= 2*pi
		
		x = x - HPIx2;	//z: sin(2*pi + theta) = sin(theta)
		if(x > HPIx2){

			temp = (int)(x/HPIx2) ;
			x = x - temp*HPIx2;
		}
	}	

	if(x >= HPI){	//z: x >= pi

		x = x - HPI;	//z: sin(pi + theta) = -sin(theta)
		flag1 = 1;
	}

	if(x >= HPI_BY2){	//z: x >= pi/2

		x = x - HPI_BY2;	//z: sin(pi/2 + theta) = cos(theta)
		flag2 = 1;
	}

	if(x > HPI_BY4){		//z: x >= pi/4

		x = HPI_BY2 - x;	//z: cos(theta) = sin(pi/2-theta)
				//sin(theta) = cos(pi/2-theta)
		
		result = (flag2 ? (flag1 ? -xx__sin_base(x) : xx__sin_base(x)) : (flag1 ? -xx__cos_base(x) : xx__cos_base(x)));

	}else {

		result = (flag2 ? (flag1 ? -xx__cos_base(x) : xx__cos_base(x)) : (flag1 ? -xx__sin_base(x) : xx__sin_base(x)));

	}

	return (flag_res ? -result : result);
}


double xx__tan(double x) {

	double y;
	
	y = xx__sin(x)/xx__cos(x);

	return y;
}
/*
double tan_inverse(double sn,double cs) {

	//Replicating atan2 function
	//answer in range from (-pie,pie) 

	//Thus, in the main program wherever atan function
	//is used the input range should not cross
	//over (-pie/2,pie/2). Otherwise its not possible 
	//to resolve using atan function.
	//atan functionality is subset of atan2 functionality.

	double temp, fx, fx_der_reciprocal;
	double theta1, theta2, theta3, theta4;
	double temp1;

	temp = (sn/cs);		//val

	
	if(temp == 0){		
		return 0.0;		//0
	}else if (temp == 1){
	  	return 0.78539815;	//pie/4
	}else if (temp == -1){
	  	return -0.78539815;	//-pie/4	
	}else if (temp == 0.546302){
	  	return 0.5;		//temp. workaround	
	}else if (temp == 1.557408){
	  	return 1;		//temp. workaround	
	}

	
	//pie = 3.1415926, pie/2 = 1.5707963
	//3*pie/8 = 1.178097225, pie/4 = 0.78539815

	
	temp1 = xx__fabs(temp);
	theta1 = 0.0;

	if((temp1 >= 0) && (temp1 < 1)){ 			// 0 < theta1 < pie/4,(0.78 rad)
		
		theta1 = 0.392699075;				//pie/8, 1st approx. x(n)

	}else if((temp1 >= 1) && (temp1 < 2.5)){ 		// pie/4(0.78rad) < theta1 < 3*pie/8 (1.17rad)(around up/down)

		theta1 = 0.981747687;				//5*pie/16, 1st approx. x(n)

	}else if((temp1 >= 2.5) && (temp1 < 7)){ 		// 3*pie/8 (1.17rad)(around up/down) < theta1 < 1.43rad

		theta1 = 1.374446762;				//7*pie/16, 1st approx. x(n)

	}else if((temp1 >= 7) && (temp1 < 10)){ 		// 1.43rad < theta1 < 1.47rad
		
		theta1 = 1.45;	

	}else if((temp1 >= 10) && (temp1 < 14)){ 		// 1.47rad < theta1 < 1.5rad
		
		theta1 = 1.485;	

	}else if((temp1 >= 14) && (temp1 < 17)){ 		// 1.47rad < theta1 < 1.5rad
		
		theta1 = 1.485;	

	}else if((temp1 >= 17) && (temp1 < 24)){ 		// 1.5rad < theta1 < 1.53rad
		
		theta1 = 1.515;	

	}else if((temp1 >= 24) && (temp1 < 32)){ 		// 1.53rad < theta1 < 1.54rad
		
		theta1 = 1.535;	

	}else if((temp1 >= 32) && (temp1 < 48)){ 		// 1.54rad < theta1 < 1.55rad
		
		theta1 = 1.545;	

	}else if((temp1 >= 48) && (temp1 < 67)){ 		// 1.55rad < theta1 < 1.555rad
		
		theta1 = 1.5525;	

	}else if((temp1 >= 67) && (temp1 < 92)){ 		// 1.555rad < theta1 < 1.56rad
		
		theta1 = 1.5557;	

	}else if((temp1 >= 92)){ 				// 1.57rad < theta1 
		
		theta1 = 1.57;	

	}


	fx = xx__tan(theta1) - temp1;				//f(x(n)) ; for x(n)
	fx_der_reciprocal = xx__cos(theta1)*xx__cos(theta1);  	//1/f'(x(n))
	theta2 = theta1 - (fx*fx_der_reciprocal);		//x(n+1) = {x(n) - f(x(n))*(1/f'(x(n)))};
 
	fx = xx__tan(theta2) - temp1;				//f(x(n+1)) ; for x(n+1)
	fx_der_reciprocal = xx__cos(theta2)*xx__cos(theta2);  	//1/f'(x(n+1))
	theta3 = theta2 - (fx*fx_der_reciprocal);		//x(n+2) = {x(n+1) - f(x(n+1))*(1/f'(x(n+1)))};

	fx = xx__tan(theta3) - temp1;				//f(x(n+1)) ; for x(n+1)
	fx_der_reciprocal = xx__cos(theta3)*xx__cos(theta3);  	//1/f'(x(n+1))
	theta4 = theta3 - (fx*fx_der_reciprocal);		//x(n+2) = {x(n+1) - f(x(n+1))*(1/f'(x(n+1)))};

	if((cs < 0) && (sn >= 0)){		//2nd quadrant
		theta4 = 3.1415926-theta4;

	}else if((cs > 0) && (sn <= 0)){	//4nd quadrant
		theta4 = -theta4;

	}else if((cs < 0) && (sn <= 0)){	//3rd quadrant
		//theta4 = 3.1415926+theta4;
		theta4 = -(3.1415926-theta4);		//Can use any

	}


	//PRINTF("theta1 = %f, theta2 = %f, theta3 = %f, theta4 = %f\n", theta1, theta2, theta3, theta4);

	return theta4;
}
*/

double tan_inverse(double sn,double cs) {

	//Replicating atan2 function
	//answer in range from (-pie,pie) 

	//Thus, in the main program wherever atan function
	//is used the input range should not cross
	//over (-pie/2,pie/2). Otherwise its not possible 
	//to resolve using atan function.
	//atan functionality is subset of atan2 functionality.

	double temp, fx, fx_der_reciprocal;
	double theta1, theta2, theta3, theta4;
	double temp1;

	temp = (sn/cs);		//val


	
	if(temp == 0){		
		return 0.0;		//0
	}else if (temp == 1){
	  	return 0.785398163397;	//pie/4
	}else if (temp == -1){
	  	return -0.785398163397;	//-pie/4	
	}else if (temp == 0.546302){
	  	return 0.5;		//temp. workaround	
	}else if (temp == 1.557408){
	  	return 1;		//temp. workaround	
	}

	
	
	temp1 = xx__fabs(temp);
	theta1 = 0.0;

	if((temp1 >= 0) && (temp1 < 1)){ 			// 0 < theta1 < pie/4,(0.78 rad)
		
		theta1 = 0.392699075;				//pie/8, 1st approx. x(n)

	}else if((temp1 >= 1) && (temp1 < 2.5)){ 		// pie/4(0.78rad) < theta1 < 3*pie/8 (1.17rad)(around up/down)

		theta1 = 0.981747687;				//5*pie/16, 1st approx. x(n)

	}else if((temp1 >= 2.5) && (temp1 < 7)){ 		// 3*pie/8 (1.17rad)(around up/down) < theta1 < 1.43rad

		theta1 = 1.374446762;				//7*pie/16, 1st approx. x(n)

	}else if((temp1 >= 7) && (temp1 < 10)){ 		// 1.43rad < theta1 < 1.47rad
		
		theta1 = 1.45;	

	}else if((temp1 >= 10) && (temp1 < 14)){ 		// 1.47rad < theta1 < 1.5rad
		
		theta1 = 1.485;	

	}else if((temp1 >= 14) && (temp1 < 17)){ 		// 1.47rad < theta1 < 1.5rad
		
		theta1 = 1.485;	

	}else if((temp1 >= 17) && (temp1 < 24)){ 		// 1.5rad < theta1 < 1.53rad
		
		theta1 = 1.515;	

	}else if((temp1 >= 24) && (temp1 < 32)){ 		// 1.53rad < theta1 < 1.54rad
		
		theta1 = 1.535;	

	}else if((temp1 >= 32) && (temp1 < 48)){ 		// 1.54rad < theta1 < 1.55rad
		
		theta1 = 1.545;	

	}else if((temp1 >= 48) && (temp1 < 67)){ 		// 1.55rad < theta1 < 1.555rad
		
		theta1 = 1.5525;	

	}else if((temp1 >= 67) && (temp1 < 92)){ 		// 1.555rad < theta1 < 1.56rad
		
		theta1 = 1.5557;	

	}else if((temp1 >= 92)){ 				// 1.57rad < theta1 
		
		theta1 = 1.57;	

	}


	fx = xx__tan(theta1) - temp1;				//f(x(n)) ; for x(n)
	fx_der_reciprocal = xx__cos(theta1)*xx__cos(theta1);  	//1/f'(x(n))
	theta2 = theta1 - (fx*fx_der_reciprocal);		//x(n+1) = {x(n) - f(x(n))*(1/f'(x(n)))};
 
	fx = xx__tan(theta2) - temp1;				//f(x(n+1)) ; for x(n+1)
	fx_der_reciprocal = xx__cos(theta2)*xx__cos(theta2);  	//1/f'(x(n+1))
	theta3 = theta2 - (fx*fx_der_reciprocal);		//x(n+2) = {x(n+1) - f(x(n+1))*(1/f'(x(n+1)))};

	fx = xx__tan(theta3) - temp1;				//f(x(n+1)) ; for x(n+1)
	fx_der_reciprocal = xx__cos(theta3)*xx__cos(theta3);  	//1/f'(x(n+1))
	theta4 = theta3 - (fx*fx_der_reciprocal);		//x(n+2) = {x(n+1) - f(x(n+1))*(1/f'(x(n+1)))};

	if((cs < 0) && (sn >= 0)){		//2nd quadrant
		theta4 = 3.141592653589-theta4;

	}else if((cs > 0) && (sn <= 0)){	//4nd quadrant
		theta4 = -theta4;

	}else if((cs < 0) && (sn <= 0)){	//3rd quadrant
		//theta4 = 3.141592653589+theta4;
		theta4 = -(3.141592653589-theta4);		//Can use any

	}


	//PRINTF("theta1 = %f, theta2 = %f, theta3 = %f, theta4 = %f\n", theta1, theta2, theta3, theta4);

	return theta4;
}





