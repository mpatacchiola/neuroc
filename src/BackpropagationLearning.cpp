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
#include <math.h>       // pow
#include <chrono> //timer

namespace neuroc{

/**
* Class constructor.
*
**/
BackpropagationLearning::BackpropagationLearning(){
 mLearningRate = 0.5;
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
Network BackpropagationLearning::StartOnlineLearning(Network net, Dataset& inputDataset, Dataset& targetDataset, unsigned int cycles, bool print){

 mNet = net;

 //Defining the chrono variables
 std::chrono::time_point<std::chrono::system_clock> start, end;
 start = std::chrono::system_clock::now();

  for(unsigned int epoch=0; epoch<cycles; epoch++){

   if(print==true){ 
    std::cout << "=====================" << std::endl;
    std::cout << "EPOCH: " << epoch << std::endl;
   }

   //Check if the two dataset have the same size
   if(inputDataset.ReturnNumberOfData() != targetDataset.ReturnNumberOfData()){
    std::cerr << "Neuroc Error: BackpropagationLearning the input dataset and the target dataset have different size" << std::endl;
    return mNet;
   }
   
   double global_error = 0;
   //Main Cycle, for all data in dataset
   for(unsigned int i_set=0; i_set<inputDataset.ReturnNumberOfData(); i_set++){

    //if(print==true) std::cout << "=== LEARNING CYCLE: " << i_set  <<  " ===" << std::endl;

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
    global_error += ErrorBackpropagation(targetDataset[i_set]);
    //if(print==true) std::cout << "ERROR: " << global_error << std::endl;

    //3- Update the wheights
    #ifdef DEBUG 
     std::cout << "UpdateWheights phase... " << std::endl;
    #endif
    UpdateWheights(inputDataset[i_set]);
 }//main cycle

 //Epoch Statistics
 if(print==true){
  std::cout << "COST: " << global_error << std::endl;
 }


 }//epoch cycle

 //Final statistics
 if(print==true){
  std::cout << "=====================" << std::endl;
  end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  std::cout << "EPOCHS: " << cycles << std::endl;
  std::cout << "LEARNING RATE: " << mLearningRate << std::endl;
  std::cout << "LAYERS: " << mNet.ReturnNumberOfLayers() << std::endl;
  std::cout << "NEURONS: " << mNet.ReturnNumberOfNeurons() << std::endl;
  std::cout << "TIME: "   << elapsed_seconds.count() << "s" << std::endl;
  std::cout << "=====================" << std::endl;
  std::cout << std::endl;
 }
 return mNet;
}

/**
* Test the network on the dataset specified.
*
* @return it returns the trained version of the network
**/
void BackpropagationLearning::StartTest(Network& net, Dataset& inputDataset, Dataset& targetDataset, bool print){
  
   //Check if the two dataset have the same size
   if(inputDataset.ReturnNumberOfData() != targetDataset.ReturnNumberOfData()){
    std::cerr << "Neuroc Error: BackpropagationLearning the input dataset and the target dataset have different size" << std::endl;
    return;
   }

    //Defining the chrono variables
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

   //Main Cycle, for all data in dataset
   double global_performance = 0;
   for(unsigned int i_set=0; i_set<inputDataset.ReturnNumberOfData(); i_set++){
    std::cout << "=====================" << std::endl;
    std::cout << "TEST: " << i_set+1 << std::endl;
    std::vector<double> input_vector = inputDataset[i_set];
    std::vector<double> output_vector = net.Compute(input_vector);
    std::vector<double> target_vector = targetDataset[i_set];
    std::vector<double> error_vector = SubtractVectors(target_vector, output_vector);
    double accumulator = 0;
    //Taking the absolute value of the delta = target-output
    for(auto it_err=error_vector.begin(); it_err!=error_vector.end(); ++it_err){
     accumulator += std::abs(*it_err);
    }
    accumulator = accumulator / error_vector.size(); //mean value
    //TODO here I suppose that the maximum delta is 1.0
    //this is not true if it is used a +1 -1 activation function
    //In that case the maximum possible delta is euqal to 2
    global_performance += (1-accumulator); 

   std::cout << "INPUT: ";
   for(auto it_in=input_vector.begin(); it_in!=input_vector.end(); ++it_in){
    if(it_in != input_vector.end()-1) std::cout << *it_in << "-";
    else std::cout << *it_in;
   }
   std::cout << std::endl;
   std::cout << "TARGET: ";
   for(auto it_tar=target_vector.begin(); it_tar!=target_vector.end(); ++it_tar){
    if(it_tar != target_vector.end()-1) std::cout << *it_tar << "-";
    else std::cout << *it_tar; 
   }
   std::cout << std::endl; 
   std::cout << "OUTPUT: ";
   for(auto it_out=output_vector.begin(); it_out!=output_vector.end(); ++it_out){
    if(it_out != output_vector.end()-1) std::cout << *it_out << "-";
    else std::cout << *it_out;  
   }
   std::cout << std::endl;  
   }

  double dataset_size = inputDataset.ReturnNumberOfData();
  global_performance = global_performance / dataset_size;
  global_performance *= 100;
  std::cout << "=====================" << std::endl;
  std::cout << "TOT DATA: " << dataset_size << std::endl;
  std::cout << "PERFORMANCE: " << global_performance << "%" << std::endl;
  end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  std::cout << "TIME: " << elapsed_seconds.count() << "s" << std::endl;
  std::cout << "=====================" << std::endl;
  std::cout << std::endl;

}

/**
* Set the learing rate
*
* @param value
**/
void BackpropagationLearning::SetLearningRate(double value){
 mLearningRate = value;
}

/**
* Get the learing rate
*
**/
double BackpropagationLearning::GetLearningRate(){
 return mLearningRate;
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
* It returns the RMSD (Root Mean Square Deviation)
* 
*
* @param inputVector
**/
double BackpropagationLearning::ErrorBackpropagation(std::vector<double> targetVector){

  int tot_layers = mNet.ReturnNumberOfLayers();
  tot_layers = tot_layers - 1; //zero based index
  std::vector<double> delta_vector;

  //Iteration through all the layers of the network
  //starting from the last one
  for(int i_layer=tot_layers; i_layer>-1; i_layer--){
   //This is the case for the OUTPUT layer
   if(i_layer==tot_layers){
    delta_vector.clear();
    //TODO the power of a vector
    delta_vector = SubtractVectors(targetVector, mNet[i_layer].GetValueVector());
    //delta_vector = PowerVector(delta_vector, 2.0);
    //delta_vector = VectorScalarMultiplication(delta_vector, 0.5);
    delta_vector = HadamardProduct(delta_vector, mNet[i_layer].GetDerivativeVector());
    mNet[i_layer].SetErrorVector(delta_vector);
   //If the layer is HIDDEN
   } else {
    //The connection matrix is taken for the layer next to the current one
    std::vector<std::vector<double>> transpose_matrix = mNet[i_layer+1].GetConnectionMatrix();
    //To allow the matrix-vector multiplication the matrix must be transpose
    transpose_matrix = TransposeMatrix(transpose_matrix);
    //Matrix-vector multiplication returns a vector with lenght equal
    //to the error-vector for the current layer
    delta_vector.clear();
    delta_vector = mNet[i_layer+1].GetErrorVector();
    delta_vector = MatrixVectorMultiplication(transpose_matrix, delta_vector);
    delta_vector = HadamardProduct(delta_vector, mNet[i_layer].GetDerivativeVector());
    mNet[i_layer].SetErrorVector(delta_vector);
   }
  }//layer cycle

  std::vector<double> error_vector = mNet[tot_layers].GetErrorVector();
  //error_vector = PowerVector(error_vector, 2.0);
  //error_vector = VectorScalarMultiplication(error_vector, 0.5);
  double accumulator = 0;
  for(auto it=error_vector.begin(); it!=error_vector.end(); ++it){
   *it = pow(*it, 2.0);
   //*it = *it / 2.0;
   accumulator += *it;
  }

 accumulator = accumulator / 2;
 return accumulator;
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
  std::vector<std::vector<double>> change_rate_matrix;
  std::vector<std::vector<double>> updated_connection_matrix;
  if(i_layer==0){
   change_rate_matrix.clear();
   change_rate_matrix = OuterProduct(inputVector, mNet[i_layer].GetErrorVector()); //DotProduct(inputVector, mNet[i_layer].GetErrorVector());
   change_rate_matrix = TransposeMatrix(change_rate_matrix);
   //add here the MatrixScalarMultiplication between change_rate_matrix and LearningRateValue
   change_rate_matrix = MatrixScalarMultiplication(change_rate_matrix, mLearningRate);
   updated_connection_matrix.clear();
   updated_connection_matrix = MatrixMatrixAddition(mNet[i_layer].GetConnectionMatrix(), change_rate_matrix);
   mNet[i_layer].SetConnectionMatrix(updated_connection_matrix);
  //if HIDDEN layers
  }else{
   change_rate_matrix.clear();
   change_rate_matrix = OuterProduct(mNet[i_layer-1].GetValueVector(), mNet[i_layer].GetErrorVector()); //DotProduct(inputVector, mNet[i_layer].GetErrorVector());
   change_rate_matrix = TransposeMatrix(change_rate_matrix);
   change_rate_matrix = MatrixScalarMultiplication(change_rate_matrix, mLearningRate);
   updated_connection_matrix.clear();
   updated_connection_matrix = MatrixMatrixAddition(mNet[i_layer].GetConnectionMatrix(), change_rate_matrix);
   mNet[i_layer].SetConnectionMatrix(updated_connection_matrix);
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
* MatrixMatrixAddition
*
**/
std::vector<std::vector<double>> BackpropagationLearning::MatrixMatrixAddition(std::vector<std::vector<double>> firstMatrix, std::vector<std::vector<double>> secondMatrix){
 std::vector<std::vector<double>> result_matrix;
 if(firstMatrix.size() != secondMatrix.size()){
  std::cerr << "Neuroc Error: Matrices Addition not allowed if matrices have different row size. First: " << firstMatrix.size() << "; Second: " << secondMatrix.size() << std::endl;
  return result_matrix;
 }
 if(firstMatrix.size()==0 || secondMatrix.size()==0){
  std::cerr << "Neuroc Error: Matrices Addition not allowed if matrices are empty. First: " << firstMatrix.size() << "; Second: " << secondMatrix.size() << std::endl;
  return result_matrix;
 }
 if(firstMatrix.at(0).size() != secondMatrix.at(0).size()){
  std::cerr << "Neuroc Error: Matrices Addition not allowed if matrices have different column size. First: " << firstMatrix.at(0).size() << "; Second: " << secondMatrix.at(0).size() << std::endl;
  return result_matrix;
 }

 unsigned int tot_row=firstMatrix.size();
 unsigned int tot_col=firstMatrix.at(0).size();
 for(unsigned int i_row=0; i_row<tot_row; i_row++){
  std::vector<double> row_vector;
  for(unsigned int i_col=0; i_col<tot_col; i_col++){
   row_vector.push_back(firstMatrix[i_row][i_col] + secondMatrix[i_row][i_col]);
  }
  result_matrix.push_back(row_vector);
 }
 return result_matrix;
}

/**
* Power of a vector
*
**/
std::vector<double> BackpropagationLearning::PowerVector(std::vector<double> firstVector, double power){
 for(auto it=firstVector.begin(); it!=firstVector.end(); ++it){
  *it = std::pow(*it, power);
 }
 return firstVector;
}

/**
* Vector Scalar Multiplication
*
**/
std::vector<double> BackpropagationLearning::VectorScalarMultiplication(std::vector<double> firstVector, double scalar){
 for(auto it=firstVector.begin(); it!=firstVector.end(); ++it){
  *it = *it * scalar;
 }
 return firstVector;
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

/**
* OuterProduct
*
**/
std::vector<std::vector<double>> BackpropagationLearning::OuterProduct(std::vector<double> firstVector, std::vector<double> secondVector){
 std::vector<std::vector<double>> matrix;
 for(auto it_first=firstVector.begin(); it_first!=firstVector.end(); ++it_first){
   std::vector<double> row_vector;
   for(auto it_second=secondVector.begin(); it_second!=secondVector.end(); ++it_second){
    row_vector.push_back( *it_first * *it_second );
   }
  matrix.push_back(row_vector);
 }
 return matrix;
}


} //namespace



