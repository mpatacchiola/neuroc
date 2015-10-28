#include<JointFunctions.h>


namespace neuroc{

namespace JointFunctions{

/**
* It sums the result of the wheight Function with the Bias value
*
* @return it returns the sum
**/
double Sum(double weightFunctionOutput, double biasWeight){
 return weightFunctionOutput + biasWeight;
}


/**
* It multiply the result of the wheight Function with the Bias value
*
* @return it returns the result of the multiplication
**/
double Multiplication(double weightFunctionOutput, double biasWeight){
 return weightFunctionOutput * biasWeight;
}


}
}
