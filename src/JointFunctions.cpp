#include<JointFunctions.h>


namespace neuroc{

namespace JointFunctions{

double Sum(double weightFunctionOutput, double biasWeight){
 return weightFunctionOutput + biasWeight;
}

double Multiplication(double weightFunctionOutput, double biasWeight){
 return weightFunctionOutput * biasWeight;
}


}
}
