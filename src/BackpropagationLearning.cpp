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

#include "BackpropagationLearning.h"
#define DEBUG


namespace neuroc{

/**
* Class constructor.
*
**/
BackpropagationLearning::BackpropagationLearning(){

}

/**
* Class destructor.
*
**/
BackpropagationLearning::~BackpropagationLearning(){

}

/**
* Start the learning algorithm for the specified number of cycles.
*
* @return it returns the trained version of the network
**/
Network BackpropagationLearning::StartLearning(Network net, Dataset& inputDataset, Dataset& targetDataset, unsigned int cycles, bool print){

 mNet = net;
 
 //Check if the two dataset have the same size
 if(inputDataset.ReturnNumberOfData() != targetDataset.ReturnNumberOfData()){
  std::cerr << "Neuroc Error: BackpropagationLearning the input dataset and the target dataset have different size" << std::endl;
  return mNet;
 }

 //Main Cycle, for all data in dataset
 for(unsigned int i_set=0; i_set<inputDataset.ReturnNumberOfData(); i_set++){

  #ifdef DEBUG 
   std::cout << "Backpropagation Learning started... " << std::endl;
  #endif

  //1- Forward computation
  #ifdef DEBUG 
   std::cout << "Forward phase... " << std::endl;
  #endif
  Forward(inputDataset[i_set]);


  //2- Error backpropagation
  #ifdef DEBUG 
   std::cout << "ErrorBackpropagation phase... " << std::endl;
  #endif
  ErrorBackpropagation(targetDataset[i_set]);


  //3- Update the wheights
  #ifdef DEBUG 
   std::cout << "UpdateWheights phase... " << std::endl;
  #endif
  UpdateWheights(inputDataset[i_set]);
 

 }//main cycle

 return mNet;
}


/**
* Forward passage
*
* @param inputVector
**/
void BackpropagationLearning::Forward(std::vector<double> inputVector){
 mNet.Compute(inputVector);
 mNet.ComputeDerivative(inputVector);
}

/**
* Error Backpropagation
*
* @param inputVector
**/
void BackpropagationLearning::ErrorBackpropagation(std::vector<double> targetVector){

  int tot_layers = mNet.ReturnNumberOfLayers();
  tot_layers = tot_layers - 1; //zero based index
  std::vector<double> delta_vector;

  //Iteration through all the layers of the network
  //starting from the last one
  for(int i_layer=tot_layers; i_layer>-1; i_layer--){
   //This is the case for the OUTPUT layer
   if(i_layer==tot_layers){
    delta_vector = SubtractVectors(mNet[i_layer].GetValueVector(), targetVector);
    delta_vector = HadamardProduct(delta_vector, mNet[i_layer].GetDerivativeVector());
    mNet[i_layer].SetErrorVector(delta_vector);
   //If the layer is HIDDEN
   } else {
    std::vector<std::vector<double>> transpose_matrix = mNet[i_layer-1].GetConnectionMatrix();
    transpose_matrix = TransposeMatrix(transpose_matrix);
    delta_vector = MatrixVectorMultiplication(transpose_matrix, delta_vector);
    delta_vector = HadamardProduct(delta_vector, mNet[i_layer].GetDerivativeVector());
    mNet[i_layer].SetErrorVector(delta_vector);
   }

  }//layer cycle

}


/**
* Update the Wheights
*
**/
void BackpropagationLearning::UpdateWheights(std::vector<double> inputVector){
  int tot_layers = mNet.ReturnNumberOfLayers();
  tot_layers = tot_layers; //zero based index

 //Iteration through all the layers of the network
 //starting from the last one
 for(int i_layer=0; i_layer<tot_layers; i_layer++){
  //1-Setting the Bias value
  //This value is equal to BiasValue * ErrorValue of the neuron
    std::vector<double> bias_vector;
  bias_vector = mNet[i_layer].GetBiasVector();
  bias_vector = HadamardProduct(bias_vector, mNet[i_layer].GetErrorVector());
  mNet[i_layer].SetBiasVector(bias_vector);
  
  //2-Setting the Weight Matrix
  //if INPUT layer
  double change_rate = 0;
  if(i_layer==0){
   change_rate = DotProduct(inputVector, mNet[i_layer].GetErrorVector());
   mNet[i_layer].SetConnectionMatrix( MatrixScalarMultiplication(mNet[i_layer].GetConnectionMatrix(), change_rate) );
  //if HIDDEN layers
  }else{
   change_rate = DotProduct(mNet[i_layer-1].GetValueVector(), mNet[i_layer].GetErrorVector());
   mNet[i_layer].SetConnectionMatrix( MatrixScalarMultiplication(mNet[i_layer].GetConnectionMatrix(), change_rate) );
  }
 }
}

/**
* Transpose a matrix
*
**/
std::vector<std::vector<double>> BackpropagationLearning::TransposeMatrix( std::vector<std::vector<double>> matrix){

 std::vector<std::vector<double>> vector_to_return;
 if(matrix.size()==0) return vector_to_return; //check if empty
 unsigned int size=matrix[0].size();

 for(unsigned int i_col=0; i_col<size; i_col++){
  std::vector<double> temp_vector;
  for(auto it_row=matrix.begin(); it_row!=matrix.end(); ++it_row){
   temp_vector.push_back(it_row->at(i_col));
  }
  vector_to_return.push_back(temp_vector);
 }
 return vector_to_return;
}

/**
* Hadamard Product of two vectors
*
**/
std::vector<double> BackpropagationLearning::HadamardProduct(std::vector<double> firstVector, std::vector<double> secondVector){
 std::vector<double> vector_to_return;
 if(firstVector.size() != secondVector.size()){
  std::cerr << "Neuroc Error: Hadamard Product not allowed if vectors have different size" << std::endl;
  return vector_to_return;
 }

 for(unsigned int i=0; i<firstVector.size(); i++){
  vector_to_return.push_back(firstVector.at(i) * secondVector.at(i));
 }
 return vector_to_return;
}

/**
* Matrix Vector Product
*
**/
std::vector<double> BackpropagationLearning::MatrixVectorMultiplication(std::vector<std::vector<double>> matrix, std::vector<double> inputVector){
 std::vector<double> vector_to_return;
 if(matrix.size()==0 || inputVector.size()==0){
  std::cerr << "Neuroc Error: Matrix-Vector Product not allowed if the matrix or the vector are empty" << std::endl; 
  return vector_to_return;
 }
 unsigned int matrix_size=matrix[0].size();
 unsigned int vector_size=inputVector.size();

 if(matrix_size != vector_size){
  std::cerr << "Neuroc Error: Matrix-Vector Product not allowed if the matrix columns and the vector rows have different size" << std::endl; 
  return vector_to_return;
 }
  
 for(auto it_mat_row=matrix.begin(); it_mat_row!=matrix.end(); ++it_mat_row){
  unsigned int col_counter=0;
  double accumulator = 0;
  for(auto it_mat_col=it_mat_row->begin(); it_mat_col!=it_mat_row->end();  ++it_mat_col){
   accumulator +=  *it_mat_col * inputVector.at(col_counter);
   col_counter++;
  }
  vector_to_return.push_back(accumulator);
 }
 return vector_to_return;
}

/**
* MatrixScalarMultiplication
*
**/
std::vector<std::vector<double>> BackpropagationLearning::MatrixScalarMultiplication(std::vector<std::vector<double>> matrix, double scalar){
 for(auto it_row=matrix.begin(); it_row!=matrix.end(); ++it_row){
  for(auto it_col=it_row->begin(); it_col!=it_row->end(); ++it_col){
   *it_col = *it_col * scalar;
  }
 }
 return matrix;
}

/**
* Subtraction of two vectors
*
**/
std::vector<double> BackpropagationLearning::SubtractVectors(std::vector<double> firstVector, std::vector<double> secondVector){
 std::vector<double> vector_to_return;
 if(firstVector.size() != secondVector.size()){
  std::cerr << "Neuroc Error: Subtraction not allowed if vectors have different size. First: " << firstVector.size() << "; Second: " << secondVector.size() << std::endl;
  return vector_to_return;
 }

 for(unsigned int i=0; i<firstVector.size(); i++){
  vector_to_return.push_back(firstVector.at(i) - secondVector.at(i));
 }
 return vector_to_return;
}

/**
* DotProduct
*
**/
double BackpropagationLearning::DotProduct(std::vector<double> firstVector, std::vector<double> secondVector){
 if(firstVector.size() != secondVector.size()) throw std::domain_error("Neuroc Error: DotProduct requires equal length vectors");
 double accumulator = 0;
 for(unsigned int i=0; i<firstVector.size(); i++){
  accumulator +=firstVector[i] * secondVector[i];
 }
 return accumulator;
}


} //namespace



