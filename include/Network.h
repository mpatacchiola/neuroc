#ifndef NETWORK_H
#define NETWORK_H

#include "Neuron.h"
#include "Layer.h"
#include <memory>  // shared_ptr
#include <vector>
#include <iostream> //printing functions
#include <fstream> //save in XML

using namespace std;

/**
* \class Network
*
* \brief This is the higest class and it permits to create Networks without declaring neurons or layers
*
* \author Massimiliano Patacchiola
*
* \version 1.0
*
* \date 2015
*
* \todo LoadFromXML
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
* @param list of integers representing the layers.
* ex: {10, 5, 3, 1} Four Layers of Neurons
* @param HasBias boolean that specified if the Hidden and Output Layers must have a Bias Unit
*/
Network(std::initializer_list<int> list)
{

  //Creating the Layers and pushing them inside the container
  for ( auto it=list.begin(); it!=list.end(); ++it){
    std::shared_ptr< Layer<T> > sp_temp_layer = std::make_shared< Layer<T> >(*it);
    nLayersVector.push_back(sp_temp_layer);
  }

  //Reverse Cycle to connect the Layers
  for (unsigned int i = nLayersVector.size()-1; i > 0; i--){
    nLayersVector[i]->AddConnectionFromLayer(nLayersVector[i-1]);
  }

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

sp_output_layer->AddConnectionFromLayer(sp_input_layer);

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
 //std::vector<T> output_vector;
 try {

  //1- Set the values of the input layer
  nLayersVector[0]->SetLayerValue(InputVector);

  //2- Compute all the hidden Layer
  for (unsigned int i = 1; i < nLayersVector.size(); i++){
    nLayersVector[i]->Compute();
  }

  //3- Return the result of the Output Layer
  return nLayersVector[nLayersVector.size()-1]->GetLayerValue();

 } catch(...) {
  std::cerr << "Layer error computing internal neurons" << std::endl;
  return NULL; //output_vector;
 }

}

/**
* Add a Bias Unit in the hidden and output Layers of the network
*
* @return it returns true or false
**/
bool AddBiasNeuron(){
try{
 //It starts from 1 because the first Layer doesn't have Bias Input
 for (unsigned int i=1; i<nLayersVector.size(); i++){
  nLayersVector[i]->AddBiasNeuron();
 }
 return true;

 } catch(...) {
  std::cerr << "error adding Bias neuron to the Layer" << std::endl;
  return false;
 }
}

/**
* It returns the number of layer contained inside the Newtork
*
* @return it returns the number of Layers
**/
inline int ReturnNumberOfLayers(){
 return nLayersVector.size();
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
* Returning a vector containing smart-pointers to neurons connections
* The vector start with the first incoming connection of the first neuron of the first layer
* and it ends with the last incoming connection of the last neuron of the last layer
* @return it returns a vector of smart-pointers to double or float
**/
std::vector<std::shared_ptr<T>> ReturnConnectionsVector(){

 std::vector< std::shared_ptr<T> > output_vector;

 for (unsigned int i=0; i<nLayersVector.size(); i++){

  std::vector<std::shared_ptr<T>> vector_copy(nLayersVector[i]->ReturnConnectionsVector());
  unsigned int single_layer_size = vector_copy.size();
	
  for (unsigned int j=0; j<single_layer_size; j++){
   //output_vector.push_back( vector_copy[i]->ReturnConnectionsVector()[j] );
   output_vector.push_back( vector_copy[j] );
  }
 }
 return output_vector;
}

/**
* It returns the number of neuron contained inside the Network
*
* @return it returns the number of neurons
**/
inline unsigned int ReturnNumberOfNeurons(){
 unsigned int total_number = 0;
   for (unsigned int i = 0; i < nLayersVector.size(); i++) {
   total_number += nLayersVector[i]->ReturnNumberOfNeurons();
  }
 return total_number;
}

/**
* Print information about all the neurons contained inside the Layer
*
**/
void Print(){
 try{

  for (unsigned int i = 0; i < nLayersVector.size(); i++) {
   std::cout << "NETWORK Layer[" << i << "]" << std::endl;
   nLayersVector[i]->Print();
  }

 }catch(...){
 std::cerr << "Layer error printing informations" << std::endl;
 }
}

/**
* It saves the network as an XML file
* @param path complete path, included the file name
* @return it returns true in case of succes otherwise it returns false
**/
bool SaveAsXML(std::string path){
 std::ofstream file_stream(path, std::fstream::app); 

 if(!file_stream) {
  std::cerr<<"Cannot open the output file."<<std::endl;
  return false;
 }

  file_stream << "<network>" <<  '\n';
  file_stream << "<neurons_number>" << ReturnNumberOfNeurons() <<"</neurons_number>" << std::endl;
  file_stream.close();

  for (unsigned int i = 0; i < nLayersVector.size(); i++) {
   nLayersVector[i]->SaveAsXML(path); 
  }

 std::ofstream file_stream_close(path, std::fstream::app); 

 if(!file_stream_close) {
  std::cerr<<"Cannot open the output file."<< '\n';
  return false;
 }

 file_stream_close << "</network>" << std::endl;
 file_stream_close.close();
 return true;
}



private:
//std::vector< Layer<T> > nLayersVector;
std::vector< std::shared_ptr<Layer<T>> > nLayersVector;


};


#endif // NETWORK_H
