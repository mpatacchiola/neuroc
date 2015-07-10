#ifndef NETWORK_H
#define NETWORK_H

#include "Neuron.h"
#include "Layer.h"
#include <memory>  // shared_ptr
#include <vector>
#include <iostream> //printing functions

using namespace std;

/**
* \class Network
*
* \ingroup NeuralNetwork
*
* \brief
*
* \author Massimiliano Patacchiola
*
* \version 0
*
* \date 2015
*
* Contact:
*
*/
template<typename T>
class Network {

public:

/**
* Class constructor. It permits to create directly a multiple hidden layer network
*
* @param numberOfInputNeurons this is the number of neuron to insert into the input layer
* @param numberOfOutputNeurons this is the number of neuron to insert into the output layer
*/
template<typename... Args>
Network(unsigned int numberOfInputNeurons, Args... args,  unsigned int numberOfOutputNeurons) {

}

/**
* Class constructor. It permits to create directly a two layer
*
* @param numberOfInputNeurons this is the number of neuron to insert into the input layer
* @param numberOfOutputNeurons this is the number of neuron to insert into the output layer
*/
Network(unsigned int numberOfInputNeurons, unsigned int numberOfOutputNeurons) {
static_assert(std::is_floating_point<T>::value,"Network error class Network can only be instantiated with floating point types");

nLayersVector.reserve(2);

std::shared_ptr< Layer<T> > sp_input_layer = std::make_shared< Layer<T> >(numberOfInputNeurons);
std::shared_ptr< Layer<T> > sp_output_layer = std::make_shared< Layer<T> >(numberOfOutputNeurons);

sp_input_layer->AddConnectionToLayer(sp_output_layer);

nLayersVector.push_back(sp_input_layer);
nLayersVector.push_back(sp_output_layer);
}

/**
* Class constructor. It permits to create directly a two layer
*
* @param numberOfInputNeurons this is the number of neuron to insert into the input layer
* @param numberOfHiddenNeurons this is the number of neuron to insert into the hidden layer
* @param numberOfOutputNeurons this is the number of neuron to insert into the output layer
*/
Network(unsigned int numberOfInputNeurons, unsigned int numberOfHiddenNeurons, unsigned int numberOfOutputNeurons) {
static_assert(std::is_floating_point<T>::value,"Network error class Network can only be instantiated with floating point types");

nLayersVector.reserve(3);

std::shared_ptr< Layer<T> > sp_input_layer = std::make_shared< Layer<T> >(numberOfInputNeurons);
std::shared_ptr< Layer<T> > sp_hidden_layer = std::make_shared< Layer<T> >(numberOfHiddenNeurons);
std::shared_ptr< Layer<T> > sp_output_layer = std::make_shared< Layer<T> >(numberOfOutputNeurons);

sp_hidden_layer->AddConnectionFromLayer(sp_input_layer);
sp_output_layer->AddConnectionFromLayer(sp_hidden_layer);

nLayersVector.push_back(sp_input_layer);
nLayersVector.push_back(sp_hidden_layer);
nLayersVector.push_back(sp_output_layer);
}

~Network() {
// Nothing to do here
}

/**
* Compute all the neurons of the layer and return a vector containing the values of these neurons
*
* @return it returns the vector containing the double, in case of problems it returns an empty vector and print an error
**/
std::vector<T> Compute(std::vector<T> InputVector) {
 std::vector<T> output_vector;
 try {

  //1- Set the values of the input layer
  nLayersVector[0].SetLayerValue(InputVector);

  //2- Compute all the hidden Layer
  for (unsigned int i = 1; i < nLayersVector.size(); i++){
    nLayersVector[i]->Compute();
  }

  //3- Return the result of the Output Layer
  return nLayersVector[nLayersVector.size()-1]->GetLayerValue();

 } catch(...) {
  std::cerr << "Layer error computing internal neurons" << std::endl;
  return output_vector;
 }

}

/**
* Operator overload [] it is used to return a smart pointer to the layer stored inside the network
* It is possible to access the methods of the single layer using the deferencing operator ->
* Example: net[3]->Compute();  // It calls the Compute() method of the third layer
* @param index the number of the element stored inside the network
* @return it returns a const reference to the neuron
**/
const std::shared_ptr< Layer<T> >& operator[](unsigned int index)
{
assert(index < nLayersVector.size() && "Out of range index.");
return nLayersVector[index];
}

/**
* Returning a vector containing pointers to neurons connections
*
**/
std::vector< std::shared_ptr<T> > ReturnConnectionsVector(){

 std::vector< std::shared_ptr<T> > output_vector(nLayersVector.size() + 1);

 for (unsigned int i=0; i<nLayersVector.size(); i++){
  output_vector.insert(output_vector.end(), nLayersVector[i]->ReturnConnectionsVector().begin(), nLayersVector[i]->ReturnConnectionsVector().end() );
 }

 return output_vector;

}





private:
//std::vector< Layer<T> > nLayersVector;
std::vector< std::shared_ptr< Layer<T> > > nLayersVector;


};


#endif // NETWORK_H
