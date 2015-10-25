
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

double DotProduct(std::vector<double> firstVector, std::vector<double> secondVector){
if(firstVector.size() != secondVector.size()) throw std::domain_error("Error: DotProduct requires equal length vectors");

//return std::inner_product(firstVector.begin(), firstVector.end(), secondVector.begin(), 0);
double accumulator = 0;
for(unsigned int i=0; i<firstVector.size(); i++){
accumulator +=firstVector[i] * secondVector[i];
}

return accumulator;

}

//template<typename T>
//T NormalizedDotProduct(const std::vector<T> firstVector&, const std::vector<T> secondVector&){
//	return 0;
//}

//template<typename T>
//T ScalarProduct(const std::vector<T> firstVector&, const std::vector<T> secondVector&){
//	return 0;
//}


double EuclideanDistance(const std::vector<double>& firstVector, const std::vector<double>& secondVector){
if (firstVector.size() != secondVector.size()) throw std::domain_error("Error: EuclideanDistance requires equal length vectors");

double square_counter = 0;
for(unsigned int i=0; i<firstVector.size(); i++){
square_counter += std::pow( (firstVector[i] - secondVector[i]), 2 );
}

return std::sqrt(square_counter);
}

//template<typename T>
//T NegativeDistance(const std::vector<T> firstVector&, const std::vector<T> secondVector&){
//	return 0;
//}

double AbsoluteDistance(const std::vector<double>& firstVector, const std::vector<double>& secondVector){
if (firstVector.size() != secondVector.size()) throw std::domain_error("Error: AbsoluteDistance requires equal length vectors");

double counter = 0;
for(unsigned int i=0; i<firstVector.size(); i++){
counter = counter + std::abs( secondVector[i]-firstVector[i] );
//std::cout << i << " : " << firstVector[i] << " ; " << secondVector[i] << std::endl;
}

return counter;
}

} //namespace

} //namespace
