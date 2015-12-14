
#include <math.h>  //  "isnan" function
#include <stdlib.h>     /* abs */
#include <vector>
#include <cmath>  //  "exp" function
#include <numeric> //  inner_product
#include <random>
#include <iostream>
#include <functional>
#include<WeightFunctions.h>


/**
 *
 * \brief This is and header wich contains different useful functions
 *
 * This header contains useful functions. 
 * The functions are assigned to different namespaces.
 * You are free to extend this header adding your own functions. 
 *
*/

namespace neuroc{

namespace WeightFunctions{

/**
* The weight vectors associated with each neuron of the layer are
* combined with the input vector producing a vector as output
*
* @param weightMatrix
* @param inputVector
* @return 
**/
Eigen::VectorXd DotProduct(Eigen::MatrixXd weightMatrix, Eigen::VectorXd inputVector){
 if(weightMatrix.cols() != inputVector.size()) throw std::domain_error("Error: DotProduct requires equal length vectors");
 return weightMatrix * inputVector;
}


//TODO
Eigen::VectorXd EuclideanDistance(Eigen::MatrixXd weightMatrix, Eigen::VectorXd inputVector){
 return inputVector;
}


//TODO
Eigen::VectorXd AbsoluteDistance(Eigen::MatrixXd weightMatrix, Eigen::VectorXd inputVector){
 return inputVector;
}

} //namespace

} //namespace
