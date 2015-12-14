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
#include <chrono>

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
}


/**
* Class constructor. It permits to create directly a multiple hidden layer network
*
* @param list of layers.
* ex: {myFirstHiddenLayer, mySecondHiddenLayer, myOutputLayer} Three Layers of Neurons
*
*/
Network::Network(std::initializer_list<DenseLayer> layersList) {
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
return *this;
}

/**
* Operator overload [] it is used to return the smart pointer reference to the Layer stored inside the Network
* It is possible to access the methods of the single Layer using the deferencing operator ->
* Example: myNet[3]->Compute();  // It calls the Compute() method of the Layer returned
* @param index the number of the element stored inside the Network
* @return it returns a const reference to the Layer
**/
DenseLayer& Network::operator[]( unsigned int index){
if (index >= mLayersVector.size()) throw std::domain_error("Error: Out of Range index.");
return mLayersVector[index];
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
Eigen::VectorXd Network::Compute(Eigen::VectorXd InputVector) {

Eigen::VectorXd void_vector;

if(mLayersVector.size()==0){
std::cerr << "Neuroc Error: Network Computation is not possible if the network is empty" << std::endl;
return void_vector;
}
if(InputVector.size()==0){
std::cerr << "Neuroc Error: Network Computation is not possible if the input vector is empty" << std::endl;
return void_vector;
}

//Compute all the Layers
for (unsigned int i=0; i<mLayersVector.size(); i++ ) {
 InputVector = mLayersVector[i].Compute(InputVector);
}

//Return the result of the Output Layer
return mLayersVector[mLayersVector.size()-1].GetOutputVector();
}

/**
* Compute all the neurons of the layer and return a vector containing the values of these neurons
*
* @return it returns the vector containing the double, in case of problems it returns an empty vector and print an error
**/
Eigen::VectorXd Network::ComputeDerivative(Eigen::VectorXd InputVector) {

Eigen::VectorXd void_vector;

if(mLayersVector.size()==0){
std::cerr << "Neuroc Error: Network Computation is not possible if the network is empty" << std::endl;
return void_vector;
}
if(InputVector.size()==0){
std::cerr << "Neuroc Error: Network Computation is not possible if the input vector is empty" << std::endl;
return void_vector;
}

//Compute all the Layers
for (unsigned int i=0; i<mLayersVector.size(); i++ ) {
 InputVector = mLayersVector[i].ComputeDerivative(InputVector);
}

//Return the result of the Output Layer
return mLayersVector[mLayersVector.size()-1].GetDerivativeVector();
}

/**
* It computes the Mean Squared Error of the network given an input dataset and a target dataset
*
* @return it returns the Mean Squared Error
**/
double Network::ComputeMeanSquaredError(neuroc::Dataset inputDataset, neuroc::Dataset targetDataset){
 double MSE = 0; //Mean Squared Error
 double dataset_size = inputDataset.ReturnNumberOfElements();
 double target_size = targetDataset.ReturnNumberOfElements();

 if(dataset_size != target_size){
  std::cerr << "Error: The input dataset and the target dataset have different dimensions." << std::endl;
  return 0;
 }

 for(unsigned int i=0; i<dataset_size; i++){
  Eigen::VectorXd output_evector = Compute(inputDataset.GetData(i));
  //This difference is the distance between the output vector and the target
  Eigen::VectorXd distance_evector = targetDataset.GetData(i) - output_evector;
  //Adding to the performance counter the norm of the distance vector
  MSE += distance_evector.squaredNorm(); 
 }

 MSE = MSE / dataset_size;
 return MSE;
}

/**
* It test the network printing the output vector and the target vector
*
* @return it returns the Mean Squared Error
**/
double Network::Test(neuroc::Dataset inputDataset, neuroc::Dataset targetDataset){

 double MSE = 0; //Mean Squared Error
 double dataset_size = inputDataset.ReturnNumberOfElements();
 double target_size = targetDataset.ReturnNumberOfElements();

//Defining the chrono variables
 std::chrono::time_point<std::chrono::system_clock> start, end;
 start = std::chrono::system_clock::now();

 if(dataset_size != target_size){
  std::cerr << "Error: The input dataset and the target dataset have different dimensions." << std::endl;
  return MSE;
 }

 for(unsigned int i=0; i<dataset_size; i++){
  std::cout << "=====================" << std::endl;
  std::cout << "TRIAL: " << i+1 << std::endl;
  Eigen::VectorXd output_evector = Compute(inputDataset.GetData(i));
  std::cout << "Target Vector: " << std::endl;
  std::cout << targetDataset.GetData(i) << std::endl;
  std::cout << "Output Vector: " << std::endl;
  std::cout << output_evector << std::endl;
  //This difference is the distance between the output vector and the target
  Eigen::VectorXd distance_evector = targetDataset.GetData(i) - output_evector;
  //Adding to the performance counter the norm of the distance vector
  MSE += distance_evector.squaredNorm(); 
 }

 MSE = MSE / dataset_size;
 end = std::chrono::system_clock::now();
 std::chrono::duration<double> elapsed_seconds = end-start;
 std::cout << "=====================" << std::endl;
 std::cout << "SIZE: " << dataset_size << std::endl;
 std::cout << "MSE: " << MSE << std::endl;
 std::cout << "TIME: "   << elapsed_seconds.count() << "s" << std::endl;
 std::cout << "=====================" << std::endl;
 return MSE;
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
* Print information about all the neurons contained inside the Layer
*
**/
void Network::Print() {
for (unsigned int i = 0; i < mLayersVector.size(); i++) {
std::cout << "Layer[" << i << "]" << std::endl;
mLayersVector[i].Print();
std::cout  << std::endl;
}
}


} //namespace



