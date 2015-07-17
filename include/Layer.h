#ifndef LAYER_H
#define LAYER_H

#include "Neuron.h"
#include <iostream> //printing functions
#include <memory>  // shared_ptr
#include <cassert>
#include <fstream> //save in XML


/**
* Copyright 2015 Massimiliano Patacchiola
*
* \class Layer
*
* \brief This class is the middle level of the neural network library. It is a container for neurons. It allows the use of different floating points.
*
* \author Massimiliano Patacchiola
*
* \version 1.0
*
* \date 2015
*
* \todo RemoveBiasNeuron
* \todo AppendLayer(Layer<T> layerToAppend)
*
* Contact:
*
*/
template<typename T>
class Layer {

 public:
  Layer() {
	  static_assert(std::is_floating_point<T>::value,"Layer error class Layer can only be instantiated with floating point types");
  }

Layer(unsigned int numberOfNeurons) {
//ctor
nNeuronsVector.reserve(numberOfNeurons);  // allocate space for this specific number of Neuron

for (unsigned int i=0; i<numberOfNeurons; i++){
//std::shared_ptr< Neuron<T> > sp_neuron (new Neuron<T>());
std::shared_ptr< Neuron<T> > sp_neuron = std::make_shared< Neuron<T> >();
nNeuronsVector.push_back(sp_neuron);  // ATTENTION: this is slower
//nNeuronsVector[i] = sp_neuron;  // ATTENTION: this should be faster
}
}

Layer(unsigned int numberOfNeurons, bool HasBias) {
//ctor
nNeuronsVector.reserve(numberOfNeurons);  // allocate space for this specific number of Neuron

for (unsigned int i=0; i<numberOfNeurons; i++){
//std::shared_ptr< Neuron<T> > sp_neuron (new Neuron<T>());
std::shared_ptr< Neuron<T> > sp_neuron = std::make_shared< Neuron<T> >();
nNeuronsVector.push_back(sp_neuron);  // ATTENTION: this is slower
//nNeuronsVector[i] = sp_neuron;  // ATTENTION: this should be faster
}

if(HasBias == true){
 std::shared_ptr<Neuron<T>> sp_temp_neuron (new Neuron<T>());
 spBiasNeuron = sp_temp_neuron;
 T neuron_value = 1;
 spBiasNeuron->SetNeuronValue(neuron_value);

 for (unsigned int i=0; i<nNeuronsVector.size(); i++){
  nNeuronsVector[i]->AddConnectionFromNeuron(spBiasNeuron);
 }

}

}

~Layer()
{
//dtor
//  NOTHING TO DO HERE, THE VECTOR CONTAINER IS AUTOMATICALLY DESTROYED
}

/**
* Operator overload [] it is used to return the smart pointer reference to the neuron stored inside the layer
* It is possible to access the methods of the single neuron using the deferencing operator ->
* Example: input_layer->Compute();  // It calls the Compute() method of the neuron returned
* @param index the number of the element stored inside the layer
* @return it returns a const reference to the neuron
**/
const std::shared_ptr< Neuron<T> >& operator[](unsigned int index)
{
 assert(index < nNeuronsVector.size() && "Out of range index.");
 return nNeuronsVector[index];
}

/**
* Compute all the neurons of the layer and return a vector containing the values of these neurons
*
* @return it returns the vector containing the double, in case of problems it returns an empty vector and print an error
**/
inline bool IsEmpty() {
 return nNeuronsVector.empty();
}

/**
* Compute all the neurons of the layer and return a vector containing the values of these neurons
*
* @return it returns the vector containing the double, in case of problems it returns an empty vector and print an error
**/
std::vector<T> Compute() {
 std::vector<T> output_vector;
 try {
  for (unsigned int i = 0; i < nNeuronsVector.size(); i++) output_vector.push_back(nNeuronsVector[i]->Compute());

  return output_vector;

 } catch(...) {
  std::cerr << "Layer error computing internal neurons" << std::endl;
  return output_vector;
 }

}

/**
* Get the values of all the neurons inside the layer
*
* @param inputValues vector of doubles of the same size of the layer. Every double is given as input to the neurons inside the layer.
* @return it returns true if it is all right, otherwise false
**/
std::vector<T> GetLayerValue(){

 std::vector<T> outputVector(nNeuronsVector.size() + 1);
 try {
  for(unsigned int i = 0; i < nNeuronsVector.size(); i++)
  outputVector.push_back(nNeuronsVector[i]->GetNeuronValue());

  return outputVector;

 } catch(...) {
  std::cerr << "Layer error setting the value of the neurons" << std::endl;
  return outputVector;
 }
}

/**
* Set the values of all the neurons inside the layer
*
* @param inputValues vector of doubles of the same size of the layer. Every double is given as input to the neurons inside the layer.
* @return it returns true if it is all right, otherwise false
**/
bool SetLayerValue(std::vector<T> inputValues){
try {

if(inputValues.size() != nNeuronsVector.size()) return false;

for(unsigned int i = 0; i < nNeuronsVector.size(); i++)
nNeuronsVector[i]->SetNeuronValue(inputValues[i]);

return true;

} catch(...) {
std::cerr << "Layer error setting the value of the neurons" << std::endl;
return false;
}
}

/**
* Set the value of a specific neuron inside the layer
*
* @param index unsigned int, the index value of the neuron
* @param neuronValue double, it is the value to assign to the neuron
* @return bool it returns true if it is all right, otherwise false
**/
bool SetNeuronValue(unsigned int index, T neuronValue){

if(index > nNeuronsVector.size()-1) {
std::cerr << "Layer the index value is out of range. " <<  std::endl;
return false;
}

nNeuronsVector[index]->SetNeuronValue(neuronValue) ;

return true;
}

/**
* Set the values of all the Error associated with the neurons inside the layer
*
* @param value vector of the same size of the layer.
* @return it returns true if it is all right, otherwise false
**/
bool SetLayerError(std::vector<T> value){
try {

if(value.size() != nNeuronsVector.size()) return false;

for(unsigned int i = 0; i < value.size(); i++)
nNeuronsVector[i]->SetNeuronError(value[i]);

return true;

} catch(...) {
std::cerr << "Layer error setting the value of the neurons" << std::endl;
return false;
}
}

/**
* Set the Error value of a specific neuron inside the layer
*
* @param index unsigned int, the index value of the neuron
* @param neuronError double, it is the value to assign to the neuron
* @return bool it returns true if it is all right, otherwise false
**/
bool SetNeuronError(unsigned int index, T neuronError){

if(index > nNeuronsVector.size()-1) {
std::cerr << "Layer the index value is out of range. " <<  std::endl;
return false;
}

nNeuronsVector[index]->SetNeuronError(neuronError) ;

return true;
}

/**
* Add a Bias Neuron to the Layer
*
* @return it returns true if it is all right, otherwise false
**/
bool AddBiasNeuron(){
try{
 std::shared_ptr<Neuron<T>> sp_temp_neuron (new Neuron<T>());
 spBiasNeuron = sp_temp_neuron;
 T neuron_value = 1;
 spBiasNeuron->SetNeuronValue(neuron_value);

 for (unsigned int i=0; i<nNeuronsVector.size(); i++){
  nNeuronsVector[i]->AddConnectionFromNeuron(spBiasNeuron);
 }

 return true;

 } catch(...) {
  std::cerr << "error adding Bias neuron to the Layer" << std::endl;
  return false;
 }
}

/**
* Add connections between the neurons of the second layer and the neurons of the first layer
*
* @param layerToConnect pointer to the layer to connect
* @return it returns true if it is all right, otherwise false
**/
bool AddConnectionFromLayer(std::shared_ptr< Layer<T> > spLayerToConnect) {
try {

for(unsigned int i=0; i<nNeuronsVector.size(); i++) {
for(unsigned int j=0; j<spLayerToConnect->nNeuronsVector.size(); j++) {
nNeuronsVector[i]->AddConnectionFromNeuron( spLayerToConnect->nNeuronsVector[j] );
}
}

return true;

} catch(...) {
std::cerr << "Layer error adding connection between layers" << std::endl;
return false;
}
}


/**
* Add connections from the neuron to the layer
*
* @param neuronToConnect pointer to the neuron to connect
* @return bool it returns true if it is all right, otherwise false
**/
bool AddConnectionFromNeuron(std::shared_ptr< Neuron<T> > spNeuron){
try {

for (unsigned int i=0; i<nNeuronsVector.size(); i++)
nNeuronsVector[i]->AddConnectionFromNeuron(spNeuron);

return true;

} catch(...) {
std::cerr << "Layer error adding connection with neuron" << std::endl;
return false;
}
}

/**
* Push back a new neuron in the internal container of the layer
*
* @param neuronToPush pointer to the new neuron to add
* @return it returns true if it is all right, otherwise false
**/
bool PushBackNeuron(std::shared_ptr< Neuron<T> > spNeuron){
try {

nNeuronsVector.push_back(spNeuron);
return true;

} catch(...) {
std::cerr << "Layer error pushing back the pointer to the neuron" << std::endl;
return false;
}
}


/**
* Remove a new neuron in the internal container of the layer
*
* @param neuronToRemove pointer to the neuron to remove
* @return it returns true if it is all right, otherwise false
**/
bool RemoveNeuron(std::shared_ptr< Neuron<T> > spNeuron){
try {

for (unsigned int i=0; i<nNeuronsVector.size(); i++) {

if (spNeuron == nNeuronsVector[i]) {
nNeuronsVector.erase(nNeuronsVector.begin() + i);
return true;
}
}

return false;

} catch(...) {
std::cerr << "Layer error returning the pointer to the neuron" << std::endl;
return false;
}

}

/**
* Get a pointer to a neuron contained into the layer
*
* @param index int which identify the neuron inside the internal contaniner
* @return it returns the pointer, if there is an error or the index is out of range it returns NULL
**/
std::shared_ptr< Neuron<T> > ReturnSharedPointerToNeuron(unsigned int index){
try {

if ( index > (nNeuronsVector.size()-1) ) return NULL;
else return nNeuronsVector[index];

} catch(...) {
std::cerr << "Layer error returning the pointer to the neuron" << std::endl;
return NULL;
}
}

/**
* It returns the number of neuron contained inside the layer
*
* @return it returns the number of neurons
**/
inline unsigned int ReturnNumberOfNeurons(){
 return nNeuronsVector.size();
}

/**
* Returning a vector containing pointers to neurons connections
*
**/
std::vector< std::shared_ptr<T> > ReturnConnectionsVector(){
 std::vector< std::shared_ptr<T> > output_vector;

 for (unsigned int i=0; i<nNeuronsVector.size(); i++){
  std::vector<std::shared_ptr<T>> vector_copy(nNeuronsVector[i]->ReturnConnectionsVector());
  unsigned int neuron_vector_size = vector_copy.size();

  for (unsigned int j=0; j<neuron_vector_size; j++){
   //output_vector.push_back( nNeuronsVector[i]->ReturnConnectionsVector()[j] );
   output_vector.push_back( vector_copy[j] );
  }
 }
 return output_vector;
}

/**
* Print information about all the neurons contained inside the Layer
*
**/
void Print(){
 try{

  for (unsigned int i = 0; i < nNeuronsVector.size(); i++) {
   std::cout << "LAYER neuron[" << i << "]" << std::endl;
   nNeuronsVector[i]->Print();
  }

 }catch(...){
 std::cerr << "Layer error printing informations" << std::endl;
 }
}

/**
* Print information about all the neurons contained inside the Layer
*
* @param tag string that can help to identify neurons after printing
* @param printConnections bool if true print the incoming/outgoing vectors values for each neuron
**/
void Print(std::string tag, bool printConnections) {
try{

for (unsigned int i = 0; i < nNeuronsVector.size(); i++) {
std::cout << "LAYER neuron[" << i << "]" << std::endl;
nNeuronsVector[i]->Print(tag, printConnections);
}

}catch(...) {
std::cerr << "Layer error printing informations" << std::endl;
}
}

/**
* It returns true if the layer has an input Bias
**/
bool HasBias(){
 if(spBiasNeuron == nullptr) return false;
 else return true;
}

/**
* It saves the layer as an XML file
* @param path complete path, included the file name
* @return it returns true in case of succes otherwise it returns false
**/
bool SaveAsXML(std::string path){
 std::ofstream file_stream(path, std::fstream::app); 

 if(!file_stream) {
  std::cerr<<"Cannot open the output file."<< std::endl;
  return false;
 }

  file_stream << "  " << "<layer>" <<  '\n';
  file_stream << "  " << "<neurons_number>" << nNeuronsVector.size() <<"</neurons_number>" <<  '\n';
  file_stream << "  " << "<has_bias>" << HasBias() <<"</has_bias>" << std::endl;
  file_stream.close();

  if(HasBias() == true) spBiasNeuron->SaveAsXML(path);

  for (unsigned int i = 0; i < nNeuronsVector.size(); i++) {
   nNeuronsVector[i]->SaveAsXML(path);
  }

 std::ofstream file_stream_close(path, std::fstream::app); 

 if(!file_stream_close) {
  std::cerr<<"Cannot open the output file."<< std::endl;
  return false;
 }
  file_stream_close << "  " << "</layer>" << std::endl;
  file_stream_close.close();
 return true;
}


private:
	std::vector< std::shared_ptr< Neuron<T> > > nNeuronsVector; /**< vector which contains the neurons of the layer */
	std::shared_ptr<Neuron<T>> spBiasNeuron;

//auto sp = std::shared_ptr<Example>(new Example(argument));
   //auto msp = std::make_shared<Example>(argument);
};


#endif // LAYER_H
