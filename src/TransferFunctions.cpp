
#include <math.h>  //  "isnan" function
#include <stdlib.h>     /* abs */
#include <vector>
#include <cmath>  //  "exp" function
#include <numeric> //  inner_product
#include <random>
#include <iostream>
#include <functional>
#include <TransferFunctions.h>

namespace neuroc{

namespace TransferFunctions{


/**
* It returns the same value given as input
* @param input value
* @return the output of the function
*/
Eigen::VectorXd Linear(Eigen::VectorXd inputVector) {
return inputVector;
}	

/**
* If the value is less than zero then it is switched to -value
* @param input value
* @return the output of the function
*/
Eigen::VectorXd PositiveLinear(Eigen::VectorXd inputVector) {
 for(int i=0; i<inputVector.size(); i++){
  if(inputVector[i]<0.0) inputVector[i]=-inputVector[i];
 }
 return inputVector;
}

/**
* For input less than -1 it returns -1
* For input greater than +1 it returns +1
* For input in the range -1 +1 it returns the input value
* This activation function is used in Hopefield Networks
* @param input value
* @return the output of the function
*/
Eigen::VectorXd SaturatedLinear(Eigen::VectorXd inputVector) {
 for(int i=0; i<inputVector.size(); i++){
  if(inputVector[i] > 1) inputVector[i] = 1;
  else if (inputVector[i] < -1) inputVector[i] = -1;
 }
 return inputVector;	
}

/**
* The shape of the sigmoid function is a S.
* The output values are between 0 and 1.
* @param input value
* @return the output of the function
*/
Eigen::VectorXd Sigmoid(Eigen::VectorXd inputVector) {
 for(int i=0; i<inputVector.size(); i++){
  double divisor = 1.0 + std::exp(-inputVector[i]);
  double result =  1.0 / divisor;
  if( std::isnan(result) == true ) inputVector[i] = 0; //protection against large negative number
  else inputVector[i] = result;
 }
 return inputVector;
}

/**
* The shape of the sigmoid function is a S.
* The output values are between 0 and 1.
* This is the fast version of the classic
* sigmoid function. It does not use the
* exp() function for calculating the output.
* @param input value
* @return the output of the function
*/
Eigen::VectorXd FastSigmoid(Eigen::VectorXd inputVector) {
 for(int i=0; i<inputVector.size(); i++){
  inputVector[i] = inputVector[i] / (1.0 + std::abs(inputVector[i]));
 }
 return inputVector;
}

Eigen::VectorXd SigmoidDerivative(Eigen::VectorXd inputVector) {
//dy/dx = f(x)' = f(x) * (1 - f(x))
//double result = (1.0 / (1.0 + std::exp(-input))) * (1.0 - (1.0 / (1.0 + std::exp(-input))));
//if( std::isnan(result) == true ) return 0; //protection against large negative number
 for(int i=0; i<inputVector.size(); i++){
  double result = (std::exp(-inputVector[i]))/ std::pow( (1+std::exp(-inputVector[i])), 2);
  if( std::isnan(result) == true ) inputVector[i] = 0; //protection against large negative number
  else inputVector[i] = result;
 }
 return inputVector;
}

Eigen::VectorXd Tanh(Eigen::VectorXd inputVector) {
 for(int i=0; i<inputVector.size(); i++){
  inputVector[i] = tanh(inputVector[i]);
 }
 return inputVector;
}	

Eigen::VectorXd TanhDerivative(Eigen::VectorXd inputVector) {
 for(int i=0; i<inputVector.size(); i++){
  double result = (1.0-std::tanh(inputVector[i])) * (1.0+std::tanh(inputVector[i]));
  if( std::isnan(result) == true ) inputVector[i] = 0; //protection against large negative number
  else inputVector[i] = result;
 }
 return inputVector; 
}

/**
* used in Radial Basis Neurons
* @param input value
* @return the output of the function
*/
Eigen::VectorXd RadialBasis(Eigen::VectorXd inputVector) {
 for(int i=0; i<inputVector.size(); i++){		
  inputVector[i] = exp( -std::pow(inputVector[i], 2) );
 }
 return inputVector;
}

/**
* used in Radial Basis Neurons
* @param inputVector value
* @return the output of the function
*/
Eigen::VectorXd MultiQuadratic(Eigen::VectorXd inputVector) {
 for(int i=0; i<inputVector.size(); i++){
  double t1 = 1 + std::pow(inputVector[i], 2);		
  inputVector[i] = std::sqrt(t1);
 }
 return inputVector;
}


/**
* Step funcion that returns 0 or 1
* It returns 1 for input grater than 0
* It returns 0 in all the other cases
* @param input value
* @return the output of the function
*/
Eigen::VectorXd HardLimit(Eigen::VectorXd inputVector) {
 for(int i=0; i<inputVector.size(); i++){
  if(inputVector[i] > 0) inputVector[i] = 1;
  else inputVector[i] = 0;
 }
 return inputVector;	
}



}
}


