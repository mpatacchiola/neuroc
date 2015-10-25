
#include <math.h>  //  "isnan" function
#include <stdlib.h>     /* abs */
#include <vector>
#include <cmath>  //  "exp" function
#include <numeric> //  inner_product
#include <random>
#include <iostream>
#include <functional>
#include<InitFunctions.h>


namespace neuroc{

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
double Linear(double inputValue) {
return inputValue;
}

/**
* Return a uniform generated number in the range -0.1/+0.1
*
* @return a uniform random value
*/
double SmallValue(double inputValue) {
double min_value = -0.1;
double max_value = 0.1;
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
double Unit(double inputValue) {
double min_value = -1.0;
double max_value = 1.0;
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
double GaussianMutation(double inputValue) {
double probability = 2.0; //default probability of mutation is 2% 
double standardDeviation = 1.0; //default standard deviation is 1.0
srand (time(NULL));
std::random_device generator_device;
std::mt19937_64 gen(generator_device());
std::uniform_real_distribution<double>  distribution_device(0.0,100.0);
double number_extracted =  distribution_device(gen);

if (number_extracted <= probability) {
std::normal_distribution<double> normal(inputValue, standardDeviation);
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



} //namespace

} //namespace
