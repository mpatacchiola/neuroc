/*
 * neuroc - c++11 Artificial Neural Networks library
 * Copyright (C) 2015  Massimiliano Patacchiola
 * Author: Massimiliano Patacchiola
 * email:
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
*/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <math.h>  //  "isnan" function
#include <stdlib.h>     /* abs */
#include <vector>
#include <cmath>  //  "exp" function
#include <numeric> //  inner_product
#include <random>
#include <iostream>
#include <functional>

/**
 * Copyright 2015 Massimiliano Patacchiola
 *
 *
 * \brief This is and header wich contains different useful functions
 *
 * This header contains useful functions. 
 * The functions are assigned to different namespaces.
 * You are free to extend this header adding your own functions. 
 *
 * \author Massimiliano Patacchiola
 *
 * \version 1.0
 *
 * \date 2015
 *
 * Contact:
 *
 */


/**
 * \namespace InitFunctions
 *
 * It contains functions for weights initialization
 * All the functions of this namespace must take a single value and return a single value
 */
namespace InitFunctions{

	/**
	* Return the same value given as input
	* It is useful when it is not necessary to change
	* the connections vector of the neuron
	* @return the same value given as input
	*/
	template<typename T>
	T Linear(T inputValue) {
	 return inputValue;
	}

	/**
	* Return a uniform generated number in the range -0.1/+0.1
	*
	* @return a uniform random value
	*/
	template<typename T>
	T SmallValue(T inputValue) {
	 T min_value = -0.1;
	 T max_value = 0.1;
	 srand (time(NULL));
	 std::random_device generator_device;
	 std::mt19937_64 gen(generator_device());
	 std::uniform_real_distribution<> unifrom_distribution(min_value,  max_value);
	 return unifrom_distribution(gen);
	}

	/**
	* Return a uniform generated number in the range -0.1/+0.1
	*
	* @return a uniform random value
	*/
	template<typename T>
	T Unit(T inputValue) {
	 T min_value = -1.0;
	 T max_value = 1.0;
	 srand (time(NULL));
	 std::random_device generator_device;
	 std::mt19937_64 gen(generator_device());
	 std::uniform_real_distribution<> unifrom_distribution(min_value,  max_value);
	 return unifrom_distribution(gen);
	}

	/**
	* Return a mutate number with a 2% probability.
	* The mutate number is picked from a gaussian distribution
	* with mean equal to the input value and standard deviation of 1.
	* @return a gaussian random value
	*/
	template<typename T>
	T GaussianMutation(T inputValue) {
	    T probability = 2.0; //default probability of mutation is 2% 
	    T standardDeviation = 1.0; //default standard deviation is 1.0
	    srand (time(NULL));
	    std::random_device generator_device;
	    std::mt19937_64 gen(generator_device());
	    std::uniform_real_distribution<T> distribution_device(0.0,100.0);
	    T number_extracted =  distribution_device(gen);

	    if (number_extracted <= probability) {
	 	std::normal_distribution<T> normal(inputValue, standardDeviation);
	 	return normal(generator_device); //yes mutation
	    }else{
		return inputValue; //no mutation
	    }
	}

	/**
	* Return a mutate number with a 2% probability.
	* The mutate number is picked from a gaussian distribution
	* with mean equal to the input value and standard deviation of 1.
	* @return a gaussian random value
	*/
	double BinaryMutation(double inputValue) {
	    double probability = 2.0; //default probability of mutation is 2% 
	    srand (time(NULL));
	    std::random_device generator_device;
	    std::mt19937_64 gen(generator_device());
	    std::uniform_real_distribution<double> distribution_device(0.0,100.0);
	    double number_extracted =  distribution_device(gen);

	  double RangeMAX = 10.0;
	  double integer_weight = 0;
	

		//---FASE 1: conversione nel range -128/127
		if (inputValue >0) integer_weight = ((RangeMAX-inputValue) *256) /(RangeMAX*2);
		else integer_weight = (((RangeMAX-inputValue) *256) /(RangeMAX*2))-1;


		//FASE 2: Ricavo il byte corrispettivo
		int b[8];
		int val = (int)integer_weight;

		for(int Contatore = 0; Contatore<8; Contatore++){
		    b[Contatore]= val % 2;
		    val = val /2;
		}

		//FASE 3: muto il byte agendo sui singoli bit
		for(int ContaBit =0; ContaBit<8;ContaBit++){
			number_extracted =  distribution_device(gen);
		   if (number_extracted <= probability){
		       if (b[ContaBit] ==0) b[ContaBit]=1;
		       else b[ContaBit]=0;
		   }
		}

		//FASE 4: ritrasformo il Byte nel Range 255
		integer_weight =0;
		integer_weight+=b[0]*1;
		integer_weight+=b[1]*2;
		integer_weight+=b[2]*4;
		integer_weight+=b[3]*8;
		integer_weight+=b[4]*16;
		integer_weight+=b[5]*32;
		integer_weight+=b[6]*64;
		integer_weight+=b[7]*128; 

	       //FASE 5: trasformo il numero dal range 255 al Double
		if (integer_weight<0) integer_weight+=256;

		inputValue= (integer_weight + 1)/256;
		inputValue=RangeMAX -(inputValue*(RangeMAX*2));
		return inputValue;
	}



}


/**
 * \namespace WeightFunctions
 *
 * It contains functions used by the neuron in the first computational step
 * All the functions of this namespace must take two vectors and return a single value
 */
namespace WeightFunctions{


	template<typename T>
	T DotProduct(std::vector<T> firstVector, std::vector<T> secondVector){
		if(firstVector.size() != secondVector.size()) throw std::domain_error("Error: DotProduct requires equal length vectors");
		
		//return std::inner_product(firstVector.begin(), firstVector.end(), secondVector.begin(), 0);
		T accumulator = 0;
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


	template<typename T>
	T EuclideanDistance(const std::vector<T>& firstVector, const std::vector<T>& secondVector){
    		if (firstVector.size() != secondVector.size()) throw std::domain_error("Error: EuclideanDistance requires equal length vectors");

		T square_counter = 0;
		for(unsigned int i=0; i<firstVector.size(); i++){
			square_counter += std::pow( (firstVector[i] - secondVector[i]), 2 );
		}

		return std::sqrt(square_counter);
	}

	//template<typename T>
	//T NegativeDistance(const std::vector<T> firstVector&, const std::vector<T> secondVector&){
	//	return 0;
	//}

	template<typename T>
	T AbsoluteDistance(const std::vector<T>& firstVector, const std::vector<T>& secondVector){
    	  if (firstVector.size() != secondVector.size()) throw std::domain_error("Error: AbsoluteDistance requires equal length vectors");

		T counter = 0;
		for(unsigned int i=0; i<firstVector.size(); i++){
		  counter = counter + std::abs( secondVector[i]-firstVector[i] );
		  //std::cout << i << " : " << firstVector[i] << " ; " << secondVector[i] << std::endl;
		}

		return counter;
	}

}


/**
 * \namespace JoinFunctions
 *
 * It contains functions used by the neuron in the second computational step
 * All the functions of this namespace must take a two values and return a single value
 */
namespace JoinFunctions{

	template<typename T>
	T Sum(T weightFunctionOutput, T biasWeight){
		return weightFunctionOutput + biasWeight;
	}

	template<typename T>
	T Multiplication(T weightFunctionOutput, T biasWeight){
		return weightFunctionOutput * biasWeight;
	}

}

/**
 * \namespace TransferFunctions
 *
 * It contains functions used by the neuron in the third computational step
 * All the functions of this namespace must take a single value and return a single value
 */
namespace TransferFunctions{


	/**
	 * It returns the same value given as input
	 * @param input value
	 * @return the output of the function
	*/
	template<typename T>
	T Linear(T input) {
	 return input;
	}	

	template<typename T>
	T PositiveLinear(T input) {
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
	template<typename T>
	T SaturatedLinear(T input) {
         if(input > 1) return 1;
	 else if (input < -1) return -1;
	 else return input;	
	}

	template<typename T>
	T Sigmoid(T input) {
	T result =  ( 1.0 / (1.0 + std::exp(-input)) );
	if( std::isnan(result) == true ) return 0; //protection against large negative number
	 return result;
	}

	template<typename T>
	T FastSigmoid(T input) {
	 return input / (1.0 + std::abs(input));
	}

	template<typename T>
	T SigmoidDerivative(T input) {
	 return (1.0 / (1.0 + std::exp(-input))) * (1.0 - (1.0 / (1.0 + std::exp(-input))));
	}

	template<typename T>
	T Tanh(T input) {
	 return tanh(input);
	}	

	template<typename T>
	T TanhDerivative(T input) {
	 return (1.0-std::tanh(input)) * (1.0+std::tanh(input));
	}

	/**
	 * used in Radial Basis Neurons
	 * @param input value
	 * @return the output of the function
	*/
	template<typename T>
	T RadialBasis(T input) {		
	 return exp( -std::pow(input, 2) );
	}

	/**
	 * used in Radial Basis Neurons
	 * @param input value
	 * @return the output of the function
	*/
	template<typename T>
	T MultiQuadratic(T input) {
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
	template<typename T>
	T HardLimit(T input) {
         if(input > 0) return 1;
	 else return 0;	
	}



}




/**
 * \namespace RandomFunctions
 *
 * It contains functions for randomization
 *
 */
namespace RandomFunctions{

	template<typename T>
	std::vector<T>& ReturnRandomVector(unsigned int vectorSize, T minRange=0.1, T maxRange=0.1) {
		std::vector<T> output_vector;	
		output_vector.reserve(vectorSize);
		for(unsigned int i=0; i<vectorSize; i++){
			output_vector.push_back(ReturnFloatingPoint(minRange, maxRange));
		}
		return output_vector;

	}	


	template<typename T>
	T RandomizeVector(std::vector<T>* vectorToRandomize, T minRange=-1, T maxRange=1) {

	}

	/**
	 * Return true if a percentage probability is reached
	 * Ex. ReturnPercentageProbability(2.5); // It returns true if a random generated value
	 * in the range 0-100 is smaller or equal to 2.5
	 * @param probability expressed as a % value.
	 * @return It returns true if the probability is reached, otherwise it returns false
	*/
	bool PercentageProbability(const double& probability) {
	    srand (time(NULL));
	    std::random_device generator_device;
	    std::mt19937_64 gen(generator_device());
	    std::uniform_real_distribution<double> distribution_device(0.0,100.0);
	    double number_extracted =  distribution_device(gen);

	    if (number_extracted <= probability) return true;
	    else return false;
	}

	/**
	* Return a random generated floating point number.
	* It is used a uniform distribution.
	* @param minRange
	* @param maxRange
	* @return It returns the generated number
	*/
	template<typename T>
	T ReturnUniformFloatingPointNumber( T minRange=-1, T maxRange=1){
	 srand (time(NULL));
	 std::random_device generator_device;
	 std::mt19937_64 gen(generator_device());
	 std::uniform_real_distribution<> unifrom_distribution(minRange,  maxRange);
	 return unifrom_distribution(gen);
	}

	/**
	* Return a random generated floating point number.
	* It is used a gaussian distribution.
	* @param mean this is the mean to use for the distribution
	* @param standardDeviation this is the standard deviation to use for the distribution
	* @return It returns the generated number
	*/
	template<typename T>
	T ReturnGaussianFloatingPointNumber(T mean, T standardDeviation){
	 srand (time(NULL));
	 std::random_device generator_device;
	 std::mt19937_64 gen(generator_device());
	 std::normal_distribution<T> normal(mean, standardDeviation);
	 return normal(generator_device);
	}

	/**
	 * Return a random generated integer.
	 * It is used a uniform distribution.
	 * @param minRange it is the minimum value to use for selecting the integer
	 * @param maxRange it is the maximum value to use for selecting the integer
	 * @return It returns the selected integer
	*/
	int ReturnInteger(int minRange, int maxRange) {
	    srand (time(NULL));
	    std::random_device generator_device;
	    std::mt19937_64 gen(generator_device());
	    std::uniform_int_distribution<int> distribution_device(minRange, maxRange);
	    return distribution_device(gen);
	}

}














#endif // FUNCTIONS_H
