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

#include "Network.h"


namespace neuroc{

/**
* Default constructor
*
*
*/
Network::Network()
{
}

/**
* Copy constructor
*
* @param rLayer reference to an existing Layer
*/
Network::Network(const Network &rNetwork)
{
mLayersVector = rNetwork.mLayersVector;
mUserValue = rNetwork.mUserValue;
}


/**
* Class constructor. It permits to create directly a multiple hidden layer network
*
* @param list of layers.
* ex: {myFirstHiddenLayer, mySecondHiddenLayer, myOutputLayer} Three Layers of Neurons
*
*/
Network::Network(std::initializer_list<Layer> layersList) {
mLayersVector.reserve(layersList.size());
for ( auto it=layersList.begin(); it!=layersList.end(); ++it) {
mLayersVector.push_back(*it);
}
}


Network::~Network() {
mLayersVector.clear();
}

/**
* Overload of the assignment operator
*
* @param rLayer reference to an existing Layer
*/
Network Network::operator=(const Network &rNetwork)
{  		
if (this == &rNetwork) return *this;  // check for self-assignment 
mLayersVector = rNetwork.mLayersVector;
mUserValue = rNetwork.mUserValue;
return *this;
}

/**
* Operator overload [] it is used to return the smart pointer reference to the Layer stored inside the Network
* It is possible to access the methods of the single Layer using the deferencing operator ->
* Example: myNet[3]->Compute();  // It calls the Compute() method of the Layer returned
* @param index the number of the element stored inside the Network
* @return it returns a const reference to the Layer
**/
Layer& Network::operator[]( unsigned int index){
if (index >= mLayersVector.size()) throw std::domain_error("Error: Out of Range index.");
return mLayersVector[index];
}

/**
* Operator overload < it is used to permit sorting on internal container
* @param rhs another Network to compare
**/
bool Network::operator < (const Network& rhs) const
{
return (mUserValue < rhs.mUserValue);
}

/**
* Operator overload > it is used to permit sorting on internal container
* @param rhs another Network to compare
**/
bool Network::operator > (const Network& rhs) const
{
return (mUserValue > rhs.mUserValue);
}

/**
* It gives the size of the connections container
*
* @return it returns the number of connection of the neuron
*/
unsigned int Network::Size(){
return mLayersVector.size();
}

/**
* Compute all the neurons of the layer and return a vector containing the values of these neurons
*
* @return it returns the vector containing the double, in case of problems it returns an empty vector and print an error
**/
std::vector<double> Network::Compute(const std::vector<double>& InputVector) {

std::vector<double> void_vector;

if(mLayersVector.size()==0){
std::cerr << "Neuroc Error: Network Computation is not possible if the network is empty" << std::endl;
return void_vector;
}
if(InputVector.size()==0){
std::cerr << "Neuroc Error: Network Computation is not possible if the input vector is empty" << std::endl;
return void_vector;
}
if(InputVector.size() != mLayersVector[0][0].GetConnectionVector().size()){
std::cerr << "Neuroc Error: Network Computation is not possible if the input vector size is different from the input size of the first layer" << std::endl;
return void_vector;
}

//1- Set the values of the input layer
mLayersVector[0].Compute(InputVector);



//2- Compute all the hidden Layer

for (unsigned int i=1; i<mLayersVector.size(); i++ ) {
mLayersVector[i].Compute(mLayersVector[i-1].GetValueVector());
}



//3- Return the result of the Output Layer
return mLayersVector[mLayersVector.size()-1].GetValueVector();
}

/**
* Compute all the neurons of the layer and return a vector containing the values of these neurons
*
* @return it returns the vector containing the double, in case of problems it returns an empty vector and print an error
**/
std::vector<double> Network::ComputeDerivative(const std::vector<double>& InputVector) {

//1- Set the values of the input layer
mLayersVector[0].ComputeDerivative(InputVector);

#ifdef DEBUG 
 std::cout << "Network Computation... " << std::endl;
#endif

//2- Compute all the hidden Layer

for (unsigned int i=1; i<mLayersVector.size(); i++ ) {
mLayersVector[i].ComputeDerivative(mLayersVector[i-1].GetValueVector());
}

//3- Return the result of the Output Layer
return mLayersVector[mLayersVector.size()-1].GetDerivativeVector();
}

/**
* It returns a reference to the vector that contain the neurons
* 
* @return a const reference to the vector
*/
const std::vector<Layer>& Network::ReturReferenceToLayersVector() {
return mLayersVector;
}


/**
* Randomize all the connections of the neurons inside the layer
* It is possible to specify a minimum and maximum range for the random generator.
*
* @param minRange the minimum range for the random generator
* @param maxRange the maximum range for the random generator
* @return bool it returns true if everything is all right, otherwise false.
*/
void Network::RandomizeConnectionMatrix(std::function<double(double)> initFunction) {

for (unsigned int i=0; i<mLayersVector.size(); i++) {
mLayersVector[i].RandomizeConnectionMatrix(initFunction);
}
}


/**
* It returns the number of layer contained inside the Newtork
*
* @return it returns the number of Layers
**/
int Network::ReturnNumberOfLayers() {
return mLayersVector.size();
}


/**
* It returns the number of neuron contained inside the Network
*
* @return it returns the number of neurons
**/
unsigned int Network::ReturnNumberOfNeurons() {
unsigned int total_number = 0;
for (unsigned int i = 0; i < mLayersVector.size(); i++) {
total_number += mLayersVector[i].ReturnNumberOfNeurons();
}
return total_number;
}

/**
* It returns the generic user value
*
* @return it returns the user value
**/
double Network::GetUserValue() {
return mUserValue;
}

/**
* It sets the generic user value
*
* @param value the value to set
**/
void Network::SetUserValue(double value){
mUserValue = value;
}


/**
* Print information about all the neurons contained inside the Layer
*
**/
void Network::Print() {
for (unsigned int i = 0; i < mLayersVector.size(); i++) {
std::cout << "Layer[" << i << "]" << std::endl;
mLayersVector[i].Print();
}
}


} //namespace



