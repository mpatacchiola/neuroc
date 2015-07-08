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

sp_input_layer->AddConnectionToLayer(sp_hidden_layer);
sp_hidden_layer->AddConnectionToLayer(sp_output_layer);

nLayersVector.push_back(sp_input_layer);
nLayersVector.push_back(sp_hidden_layer);
nLayersVector.push_back(sp_output_layer);
}

~Network() {
// Nothing to do here
}

/**
* Operator overload [] it is used to return a smart pointer to the layer stored inside the network
* It is possible to access the methods of the single layer using the deferencing operator ->
* Example: net->Compute();  // It calls the Compute() method of the layer returned
* @param index the number of the element stored inside the network
* @return it returns a const reference to the neuron
**/
const std::shared_ptr< Layer<T> >& operator[](unsigned int index)
{
assert(index < nLayersVector.size() && "Out of range index.");
return nLayersVector[index];
}

private:
//std::vector< Layer<T> > nLayersVector;
std::vector< std::shared_ptr< Layer<T> > > nLayersVector;

};


#endif // NETWORK_H
