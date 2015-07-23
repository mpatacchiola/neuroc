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

#ifndef NETWORK_H
#define NETWORK_H

#include "Neuron.h"
#include "Layer.h"
#include <memory>  // shared_ptr
#include <vector>
#include <iostream> //printing functions
#include <fstream> //save in XML
#include <sstream>

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
* Operator overload [] it is used to return the smart pointer reference to the Layer stored inside the Network
* It is possible to access the methods of the single Layer using the deferencing operator ->
* Example: myNet[3]->Compute();  // It calls the Compute() method of the Layer returned
* @param index the number of the element stored inside the Network
* @return it returns a const reference to the Layer
**/
const std::shared_ptr< Layer<T> >& operator[](int index)
{
 assert(index < nLayersVector.size() && "Out of range index.");
 return nLayersVector[index];
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
  std::vector<T> null_vector;
  return null_vector; //output_vector;
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
* Get a pointer to a Layer contained into the Network
*
* @param index int which identify the Layer inside the internal contaniner
* @return it returns the pointer, if there is an error or the index is out of range it returns NULL
**/
std::shared_ptr< Layer<T> > ReturnSharedPointerToLayer(unsigned int index){
try {

if ( index > (nLayersVector.size()-1) ) return NULL;
else return nLayersVector[index];

} catch(...) {
std::cerr << "Network error returning the pointer to the Layer" << std::endl;
return NULL;
}
}

/**
* Returning a vector containing smart-pointers to neurons connections
* The vector start with the first incoming connection of the first neuron of the first layer
* and it ends with the last incoming connection of the last neuron of the last layer
* If the network has Bias Units then the first connection of the neuron is the Bias incoming connection
* @return it returns a vector of smart-pointers to double or float
**/
std::vector<std::shared_ptr<T>> GetVectorOfPointersToConnections(){

 std::vector< std::shared_ptr<T> > output_vector;

 for (unsigned int i=0; i<nLayersVector.size(); i++){

  std::vector<std::shared_ptr<T>> vector_copy(nLayersVector[i]->GetVectorOfPointersToConnections());
  unsigned int single_layer_size = vector_copy.size();
	
  for (unsigned int j=0; j<single_layer_size; j++){
   output_vector.push_back( vector_copy[j] );
  }
 }
 return output_vector;
}

/**
* Returning a vector containing neurons connections
* The vector start with the first incoming connection of the first neuron of the first layer
* and it ends with the last incoming connection of the last neuron of the last layer
* If the network has Bias Units then the first connection of the neuron is the Bias incoming connection
* @return it returns a vector of double or float
**/
std::vector<T> GetVectorOfConnections(){

 std::vector<T> output_vector;

 for (unsigned int i=0; i<nLayersVector.size(); i++){

  std::vector<T> vector_copy(nLayersVector[i]->GetVectorOfConnections());
  unsigned int single_layer_size = vector_copy.size();
	
  for (unsigned int j=0; j<single_layer_size; j++){
   output_vector.push_back( vector_copy[j] );
  }
 }
 return output_vector;
}

/**
* It permits to set the vector of the incoming connections to the neuron
*
* @param connectionsVector a vector of shared pointer to floating point numbers
**/
bool SetVectorOfPointersToConnections(std::vector<std::shared_ptr<T>>& connectionsVector){
 if(ReturnNumberOfConnections() != connectionsVector.size()) return false;

 unsigned int previous_layer_connections = 0;
 for (unsigned int i = 0; i < nLayersVector.size(); i++){
  unsigned int layer_connections = previous_layer_connections + nLayersVector[i]->ReturnNumberOfIncomingConnections();
  std::vector<std::shared_ptr<T>> temp_vector;
  
  for(unsigned int j=previous_layer_connections; j < layer_connections; j++){
   temp_vector.push_back(connectionsVector[j]);
  }

  previous_layer_connections += layer_connections;
  nLayersVector[i]->SetVectorOfPointersToConnections(temp_vector);
 }
 return true;
}

/**
* It permits to set the vector of the incoming connections to the neuron
*
* @param connectionsVector a vector of shared pointer to floating point numbers
**/
bool SetVectorOfConnections(std::vector<T>& connectionsVector){
 if(ReturnNumberOfConnections() != connectionsVector.size()) return false;

 unsigned int previous_layer_connections = 0;
 for (unsigned int i = 0; i < nLayersVector.size(); i++){
  unsigned int layer_connections = previous_layer_connections + nLayersVector[i]->ReturnNumberOfIncomingConnections();
  std::vector<T> temp_vector;
  
  for(unsigned int j=previous_layer_connections; j < layer_connections; j++){
   temp_vector.push_back(connectionsVector[j]);
  }

  previous_layer_connections += layer_connections;
  nLayersVector[i]->SetVectorOfConnections(temp_vector);
 }
 return true;
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

inline double GetMark(){
 return mark;
}

inline void SetMark(double value){
 mark = value;
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
* Get the total number of the connections.
*
* @return unisgned int which represents the number of connections
*/
unsigned int ReturnNumberOfConnections() {
 unsigned int total_number = 0;

 for (unsigned int i = 0; i < nLayersVector.size(); i++) {
  total_number += nLayersVector[i]->ReturnNumberOfIncomingConnections();
 }

 return total_number;
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
  file_stream << "<id>" << this <<"</id>" <<  '\n';
  file_stream << "<mark>" << mark <<"</mark>" <<  '\n';
  file_stream << "<neurons_number>" << ReturnNumberOfNeurons() <<"</neurons_number>" <<  '\n';
  file_stream << "<connections_number>" << ReturnNumberOfConnections() <<"</connections_number>" << std::endl;
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

/**
* It saves the network as an XML file
* @param path complete path, included the file name
* @return it returns true in case of succes otherwise it returns false
**/
std::string ReturnStringXML(){

  std::ostringstream string_stream; 

  string_stream << "<network>" <<  '\n';
  string_stream << "<id>" << this <<"</id>" <<  '\n';
  string_stream << "<mark>" << mark <<"</mark>" <<  '\n';
  string_stream << "<neurons_number>" << ReturnNumberOfNeurons() <<"</neurons_number>" <<  '\n';
  string_stream << "<connections_number>" << ReturnNumberOfConnections() <<"</connections_number>" << std::endl;
  //file_stream.close();

  for (unsigned int i = 0; i < nLayersVector.size(); i++) {
   string_stream << nLayersVector[i]->ReturnStringXML(); 
  }

 string_stream << "</network>" << std::endl;
 return string_stream.str();
}



private:
//std::vector< Layer<T> > nLayersVector;
std::vector< std::shared_ptr<Layer<T>> > nLayersVector;
double mark = 0;




bool IsFileEmpty(std::string filePath){
int length;
ifstream filestr;

filestr.open(filePath, ios::binary); // open your file
filestr.seekg(0, ios::end); // put the "cursor" at the end of the file
length = filestr.tellg(); // find the position of the cursor
filestr.close(); // close your file

if ( length == 0 )return true;
else return false;
}


};


#endif // NETWORK_H
