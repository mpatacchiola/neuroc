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


#include "Layer.h"


namespace neuroc{



/**
* Copy constructor
*
* @param rLayer reference to an existing Layer
*/
Layer::Layer(const Layer &rLayer)
{
mNeuronsVector = rLayer.mNeuronsVector;
}

/**
* It creates a new Layer containing similar neurons.
*
* @param neuronPrototype it is a prototype and will be used to create copies inside the layer.
* @param dimension the size of the layer
*
*/
Layer::Layer(Neuron neuronPrototype, unsigned int dimension) {
mNeuronsVector.reserve(dimension);
for(unsigned int i=0; i<dimension; i++){
Neuron neuron_copy = neuronPrototype;
mNeuronsVector.push_back(neuron_copy);
} 
}

/**
* It creates a new Layer.
*
* @param  neuronList a list of existing neurons
*
*/
Layer::Layer(std::initializer_list<Neuron> neuronList) {
mNeuronsVector.reserve(neuronList.size());
for(auto it=neuronList.begin(); it!=neuronList.end(); it++){
mNeuronsVector.push_back(*it);
} 
}

/**
* Overload of the assignment operator
*
* @param rLayer reference to an existing Layer
*/
Layer Layer::operator=(const Layer &rLayer)
{  		
if (this == &rLayer) return *this;  // check for self-assignment 
mNeuronsVector = rLayer.mNeuronsVector;
return *this;
}



Layer::~Layer() {
mNeuronsVector.clear();
}

/**
* Operator overload [] it is used to return the smart pointer reference to the neuron stored inside the layer
* It is possible to access the methods of the single neuron using the deferencing operator ->
* Example: input_layer->Compute();  // It calls the Compute() method of the neuron returned
* @param index the number of the element stored inside the layer
* @return it returns a const reference to the neuron
**/
Neuron& Layer::operator[](unsigned int index) {
if (index >= mNeuronsVector.size()) throw std::domain_error("Error: Out of Range index.");
return mNeuronsVector[index];
}

/**
* It gives the size of the connections container
*
* @return it returns the number of connection of the neuron
*/
const unsigned int Layer::Size() const{
return mNeuronsVector.size();
}


/**
* Compute all the neurons of the layer and return a vector containing the values of these neurons
*
* @return it returns the vector containing the double, in case of problems it returns an empty vector and print an error
**/
std::vector<double> Layer::Compute(std::vector<double> inputVector) {
std::vector<double> output_vector;
output_vector.reserve(mNeuronsVector.size());

for (unsigned int i = 0; i < mNeuronsVector.size(); i++){
output_vector.push_back(mNeuronsVector[i].Compute(inputVector));
}

return output_vector;
}


/**
* Randomize all the connections of the neurons inside the layer
* It is possible to specify a minimum and maximum range for the random generator.
*
* @param initFunction
* @return bool it returns true if everything is all right, otherwise false.
*/
void Layer::RandomizeConnectionMatrix(std::function<double(double)> initFunction) {
for(unsigned int i = 0; i < mNeuronsVector.size(); i++){
mNeuronsVector[i].RandomizeConnectionVector(initFunction);
}
}

/**
* Get the values of all the neurons inside the layer
*
* @param inputValues vector of doubles of the same size of the layer. Every double is given as input to the neurons inside the layer.
* @return it returns true if it is all right, otherwise false
**/
std::vector<double> Layer::GetValueVector(){

std::vector<double> outputVector;
outputVector.reserve(mNeuronsVector.size());

for(unsigned int i = 0; i < mNeuronsVector.size(); i++)
outputVector.push_back(mNeuronsVector[i].GetValue());

return outputVector;
}

/**
* Set the values of all the bias inside the layer
*
* @param biasVector vector of values with the same size of the layer.
* @return it returns true if it is all right, otherwise false
**/
bool Layer::SetBiasVector(std::vector<double> biasVector) {

if(biasVector.size() != mNeuronsVector.size()) return false;

for(unsigned int i = 0; i < biasVector.size(); i++)
mNeuronsVector[i].SetBias(biasVector[i]);

return true;
}

/**
* Set the values of all the neurons inside the layer
*
* @param inputValues vector of doubles of the same size of the layer. Every double is given as input to the neurons inside the layer.
* @return it returns true if it is all right, otherwise false
**/
bool Layer::SetValueVector(std::vector<double> valueVector) {

if(valueVector.size() != mNeuronsVector.size()) return false;

for(unsigned int i = 0; i < mNeuronsVector.size(); i++)
mNeuronsVector[i].SetValue(valueVector[i]);

return true;
}



/**
* Set the values of all the Error associated with the neurons inside the layer
*
* @param value vector of the same size of the layer.
* @return it returns true if it is all right, otherwise false
**/
bool Layer::SetErrorVector(std::vector<double> errorVector) {
if(errorVector.size() != mNeuronsVector.size()) return false;

for(unsigned int i = 0; i < errorVector.size(); i++)
mNeuronsVector[i].SetError(errorVector[i]);

return true;
}


/**
* It returns the number of neuron contained inside the layer
*
* @return it returns the number of neurons
**/
inline unsigned int Layer::ReturnNumberOfNeurons() {
return mNeuronsVector.size();
}


/**
* Returning a vector of vectors Matrix containing neurons connections
* The vector start with the first incoming connection of the first neuron
* and it ends with the last incoming connection of the last neuron
* If the Layer has a Bias Unit then the first connection of the neurons is the Bias incoming connection
* @return it returns a vector of double or float
**/
std::vector< std::vector<double> > Layer::GetConnectionMatrix() {

std::vector<std::vector<double>> output_vector;

//for (unsigned int i=0; i<mNeuronsVector.size(); i++) {
// std::vector<T> vector_copy(mNeuronsVector[i]->GetVectorOfConnections());
//unsigned int neuron_vector_size = vector_copy.size();

//for (unsigned int j=0; j<neuron_vector_size; j++) {
//    output_vector.push_back( vector_copy[j] );
// }
//}
return output_vector;
}




/**
* Print information about all the neurons contained inside the Layer
*
**/
void Layer::Print() {
for (unsigned int i = 0; i < mNeuronsVector.size(); i++) {
std::cout << "neuron[" << i << "]" << '\n';
mNeuronsVector[i].Print();
}
}



} //namespace

