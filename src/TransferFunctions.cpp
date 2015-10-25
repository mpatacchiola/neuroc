
#include <math.h>  //  "isnan" function
#include <stdlib.h>     /* abs */
#include <vector>
#include <cmath>  //  "exp" function
#include <numeric> //  inner_product
#include <random>
#include <iostream>
#include <functional>
#include<TransferFunctions.h>

namespace neuroc{

namespace TransferFunctions{


/**
* It returns the same value given as input
* @param input value
* @return the output of the function
*/
double Linear(double input) {
return input;
}	


double PositiveLinear(double input) {
if(input<0.0) return -input;
else return input;
}

/**
* For input less than -1 it returns -1
* For input greater than +1 it returns +1
* For input in the range -1 +1 it returns the input value
* This activation function is used in Hopefield Networks
* @param input value
* @return the output of the function
*/
double SaturatedLinear(double input) {
if(input > 1) return 1;
else if (input < -1) return -1;
else return input;	
}

double Sigmoid(double input) {
double result =  ( 1.0 / (1.0 + std::exp(-input)) );
if( std::isnan(result) == true ) return 0; //protection against large negative number
return result;
}

double FastSigmoid(double input) {
return input / (1.0 + std::abs(input));
}

double SigmoidDerivative(double input) {
return (1.0 / (1.0 + std::exp(-input))) * (1.0 - (1.0 / (1.0 + std::exp(-input))));
}

double Tanh(double input) {
return tanh(input);
}	

double TanhDerivative(double input) {
return (1.0-std::tanh(input)) * (1.0+std::tanh(input));
}

/**
* used in Radial Basis Neurons
* @param input value
* @return the output of the function
*/
double RadialBasis(double input) {		
return exp( -std::pow(input, 2) );
}

/**
* used in Radial Basis Neurons
* @param input value
* @return the output of the function
*/
double MultiQuadratic(double input) {
double t1 = 1 + std::pow(input, 2);		
return std::sqrt(t1);
}


/**
* Step funcion that returns 0 or 1
* It returns 1 for input grater than 0
* It returns 0 in all the other cases
* @param input value
* @return the output of the function
*/
double HardLimit(double input) {
if(input > 0) return 1;
else return 0;	
}



}
}


