#include<JoinFunctions.h>


namespace neuroc{

namespace JoinFunctions{

/**
* It sums the result of the wheight Function with the Bias value
*
* @return it returns the sum
**/
Eigen::VectorXd Sum(Eigen::VectorXd weighedVector, Eigen::VectorXd biasVector){
 return weighedVector + biasVector;
}


/**
* It multiply the result of the wheight Function with the Bias value
*
* @return it returns the result of the multiplication
**/
Eigen::VectorXd Product(Eigen::VectorXd weighedVector, Eigen::VectorXd biasVector){
 return weighedVector.cwiseProduct(biasVector);
}


}
}
