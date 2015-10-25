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


#include <math.h>  //  "isnan" function
#include <stdlib.h>     /* abs */
#include <vector>
#include <cmath>  //  "exp" function
#include <numeric> //  inner_product
#include <random>
#include <iostream>
#include <functional>


namespace neuroc {

namespace RandomFunctions{

std::vector<double> ReturnRandomVector(unsigned int vectorSize, double minRange, double maxRange) {
 srand (time(NULL));
 std::random_device generator_device;
 std::mt19937_64 gen(generator_device());
 std::uniform_real_distribution<double> unifrom_distribution(minRange,  maxRange);

 std::vector<double> output_vector;	
 output_vector.reserve(vectorSize);
 for(unsigned int i=0; i<vectorSize; i++){
  output_vector.push_back(unifrom_distribution(gen));
 }
 return output_vector;
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
double ReturnUniformFloatingPointNumber( double minRange, double maxRange){
srand (time(NULL));
std::random_device generator_device;
std::mt19937_64 gen(generator_device());
std::uniform_real_distribution<double> unifrom_distribution(minRange,  maxRange);
return unifrom_distribution(gen);
}

/**
* Return a random generated floating point number.
* It is used a gaussian distribution.
* @param mean this is the mean to use for the distribution
* @param standardDeviation this is the standard deviation to use for the distribution
* @return It returns the generated number
*/
double ReturnGaussianFloatingPointNumber(double mean, double standardDeviation){
srand (time(NULL));
std::random_device generator_device;
std::mt19937_64 gen(generator_device());
std::normal_distribution<double> normal(mean, standardDeviation);
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
}


