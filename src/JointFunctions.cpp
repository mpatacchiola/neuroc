#include<JointFunctions.h>


namespace neuroc{

namespace JoinsFunctions{

double Sum(double weightFunctionOutput, double biasWeight){
 return weightFunctionOutput + biasWeight;
}

double Multiplication(double weightFunctionOutput, double biasWeight){
 return weightFunctionOutput * biasWeight;
}


}
}
