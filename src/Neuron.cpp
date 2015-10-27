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

#include "Neuron.h"

namespace neuroc{

/**
* Copy constructor
*
* @param rNeuron reference to an existing Neuron
*/
Neuron::Neuron(const Neuron &rNeuron)
{
mConnectionsVector = rNeuron.mConnectionsVector;
mValue = rNeuron.mValue;
mError = rNeuron.mError;
mBias = rNeuron.mBias;
WeightFunction = rNeuron.WeightFunction;
JoinFunction = rNeuron.JoinFunction;
TransferFunction = rNeuron.TransferFunction;
}


/**
* It creates an object of type Neuron
*
* @param biasWeight it is the value of the weight of the bias neuron
*/
Neuron::Neuron(const std::vector<double>& connectionsVector, std::function<double(std::vector<double>, std::vector<double>)> weightFunction, std::function<double(double, double)> joinFunction, std::function<double(double)> transferFunction,  std::function<double(double)> derivativeFunction, double biasWeight)
{
mBias = biasWeight;
WeightFunction = weightFunction;
JoinFunction = joinFunction;
TransferFunction = transferFunction;
DerivativeFunction = derivativeFunction;

mConnectionsVector.reserve(connectionsVector.size()); //ATTENTION: it is necessary to initialise the connectionVector here
mConnectionsVector = connectionsVector;
}

/**
* Overload of the assignment operator
*
* @param rNeuron reference to an existing Neuron
*/
Neuron Neuron::operator=(const Neuron &rNeuron)
{

if (this == &rNeuron) return *this;  // check for self-assignment 

mConnectionsVector = rNeuron.mConnectionsVector;
mValue = rNeuron.mValue;
mDerivative = rNeuron.mDerivative;
mError = rNeuron.mError;
mBias = rNeuron.mBias;
WeightFunction = rNeuron.WeightFunction;
JoinFunction = rNeuron.JoinFunction;
TransferFunction = rNeuron.TransferFunction;
DerivativeFunction = rNeuron.DerivativeFunction;
return *this;
}

/**
* Operator overload [] it is used to return the connection weight stored inside the neuron
* @param index the number of the element stored inside the layer
* @return it returns a reference to the weight
**/
const double& Neuron::operator[](const unsigned int index) const {
if (index >= mConnectionsVector.size()) throw std::domain_error("Error: Out of Range index.");
return mConnectionsVector[index];
}

/**
* It gives the size of the connections container
*
* @return it returns the number of connection of the neuron
*/
unsigned int Neuron::Size(){
return mConnectionsVector.size();
}


/**
* It gives the value of the Neuron after one computation
* after that the internal value of the neuron is changed
*
* @return it returns the value of the neuron after the computation
*/
double Neuron::Compute(std::vector<double> inputVector) {

//1- Applying Weight Function
double weight_function_output = WeightFunction(inputVector, mConnectionsVector);
#ifdef DEBUG 
std::cout << "weight_function_output: " << weight_function_output << std::endl;
#endif

//2- Applying the Join Function
double join_function_output = JoinFunction(weight_function_output, mBias);
#ifdef DEBUG 
std::cout << "join_function_output: " << join_function_output << std::endl;
#endif

//3- Applying the Transfer Function
double neuron_output = TransferFunction(join_function_output);
#ifdef DEBUG 
std::cout << "neuron_output: " << neuron_output << std::endl;
#endif

//4- Returning the result
mValue = neuron_output;
return neuron_output;
}

/**
* Return the value of the neuron but instead using the Transfer Function
* it uses the Derivative function specified in the creation step.
*
* @return it returns the value of the computation
**/
double Neuron::ComputeDerivative(std::vector<double> inputVector){

//1- Applying Weight Function
double weight_function_output = WeightFunction(inputVector, mConnectionsVector);
#ifdef DEBUG 
std::cout << "weight_function_output: " << weight_function_output << std::endl;
#endif

//2- Applying the Join Function
double join_function_output = JoinFunction(weight_function_output, mBias);
#ifdef DEBUG 
std::cout << "join_function_output: " << join_function_output << std::endl;
#endif

//3- Applying the Derivative Function
double derivative_output = DerivativeFunction(join_function_output);
#ifdef DEBUG 
std::cout << "derivative_output: " << derivative_output << std::endl;
#endif

//4- Returning the result
 mDerivative = derivative_output;
 return derivative_output;
}

/**
* Randomize all the connection of the neuron using a Init Function.
* The function to use must take a value as input and return a value as output.
* The returned value will be assigned to the weight.
*
* @param initFunction this function is used for modifying all the weights of the neuron
*/
void Neuron::RandomizeConnectionVector(std::function<double(double)> initFunction) {

for(auto it=mConnectionsVector.begin(); it!=mConnectionsVector.end(); it++){
*it = initFunction(*it);
}

mBias = initFunction(mBias);
}


/**
* Returning a vector containing the values of the neuron connections
* The vector start with the first incoming connection and it ends with the last incoming connection
* If the Neuron has a Bias Unit then the first connection of the neuron is the Bias incoming connection
* @return it returns a vector of values
**/
std::vector<double> Neuron::GetConnectionVector() const {
return mConnectionsVector;
}

/**
* It permits to set the vector of the incoming connections to the neuron
*
* @param connectionsVector a vector of floating point numbers
**/
void Neuron::SetConnectionVector(const std::vector<double>& connectionVector) {
mConnectionsVector.clear();
mConnectionsVector = connectionVector;
}


/**
* Set the value of the neuron
*
* @param value the value to set, it is used for input neurons
*/
void Neuron::SetValue(double value) {
mValue = value; //it set the current value
}

/**
* Get the value of the neuron
*
* @return it returns the current value of the neuron
**/
double Neuron::GetValue() {
return mValue;
}

/**
* Set the value of the neuron
*
* @param value the value to set, it is used for input neurons
*/
void Neuron::SetDerivative(double value) {
mDerivative = value; //it set the current value
}

/**
* Get the value of the neuron
*
* @return it returns the current value of the neuron
**/
double Neuron::GetDerivative() {
return mDerivative;
}

/**
* Set the value of the neuron
*
* @param value the value to set, it is used for input neurons
*/
void Neuron::SetError(double value) {
mError = value;
}

/**
* Get the value of the neuron
*
* @return it returns the current value of the neuron
**/
double Neuron::GetError(){
return mError;
}

/**
* Set the value of the bias
*
* @param value the value to set
*/
void Neuron::SetBias(double value) {
mBias = value; //it set the current value
}

/**
* Get the value of the Bias Connection
*
* @return it returns the current value of the Bias Connection
**/
double Neuron::GetBias(){
return mBias;
}


/**
* Print on terminal informations about the neuron.
*
*/
void Neuron::Print() {
std::cout << "Value ..... " << mValue << '\n';
std::cout << "Error ..... " << mError << '\n';
std::cout << "Bias ..... " << mBias << '\n';
std::cout << "Connections ..... " << mConnectionsVector.size() << '\n';

for (unsigned i = 0; i < mConnectionsVector.size(); i++) {
std::cout << "Connection[" << i << "] ..... " << mConnectionsVector[i] << '\n';
}

std::cout << std::endl;
}

}



