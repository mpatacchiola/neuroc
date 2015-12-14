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

//#define DEBUG

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


double BackpropagationLearning::SingleStepOnlineLearning(Network* net, Eigen::VectorXd inputVector, Eigen::VectorXd targetVector, bool print){
 #ifdef DEBUG 
  std::cout << "Forward phase... " << std::endl;
 #endif
 Forward(net, inputVector);

 #ifdef DEBUG 
  std::cout << "ErrorBackpropagation phase... " << std::endl;
 #endif
 double squared_error = ErrorBackpropagation(net, targetVector);

 //3- Update the wheights
 #ifdef DEBUG 
  std::cout << "UpdateWheights phase... " << std::endl;
 #endif
 UpdateWheights(net);

 return squared_error;
}

/**
* Start the learning algorithm for the specified number of cycles.
*
* @return it returns the trained version of the network
**/

void BackpropagationLearning::StartOnlineLearning(Network* net, Dataset& inputDataset, Dataset& targetDataset, unsigned int cycles, bool print){
//Defining the chrono variables
 std::chrono::time_point<std::chrono::system_clock> start, end;
 start = std::chrono::system_clock::now();

  for(unsigned int epoch=0; epoch<cycles; epoch++){

   if(print==true){ 
    std::cout << "=====================" << std::endl;
    std::cout << "EPOCH: " << epoch+1 << std::endl;
   }

   //Check if the two dataset have the same size
   if(inputDataset.ReturnNumberOfElements() != targetDataset.ReturnNumberOfElements()){
    std::cerr << "Neuroc Error: BackpropagationLearning the input dataset and the target dataset have different size" << std::endl;
   }
   
   double MSE = 0; //Mean Squared Error
   double dataset_size = inputDataset.ReturnNumberOfElements();
   //Main Cycle, for all data in dataset
   for(unsigned int i_set=0; i_set<dataset_size; i_set++){

    MSE += SingleStepOnlineLearning(net, inputDataset[i_set], targetDataset[i_set], true);
   }//main cycle

   //Epoch Statistics
   if(print==true){
    std::cout << "MSE: " << MSE / dataset_size  << std::endl;
   }

 }//epoch cycle

 //Final statistics
 if(print==true){
  std::cout << "=====================" << std::endl;
  end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  std::cout << "EPOCHS: " << cycles << std::endl;
  std::cout << "LEARNING RATE: " << mLearningRate << std::endl;
  std::cout << "LAYERS: " << net->ReturnNumberOfLayers() << std::endl;
  //std::cout << "NEURONS: " << net->ReturnNumberOfNeurons() << std::endl;
  std::cout << "TIME: "   << elapsed_seconds.count() << "s" << std::endl;
  std::cout << "=====================" << std::endl;
  std::cout << std::endl;
 }

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
void BackpropagationLearning::Forward(Network* net, Eigen::VectorXd inputVector){
 net->Compute(inputVector);
 net->ComputeDerivative(inputVector);
}

/**
* Error Backpropagation
* It returns the Sqared Error
* It returns the RMSD (Root Mean Square Deviation)
* 
*
* @param inputVector
**/
double BackpropagationLearning::ErrorBackpropagation(Network* net, Eigen::VectorXd targetVector){
  int tot_layers = net->ReturnNumberOfLayers();
  tot_layers = tot_layers - 1; //zero based index
  Eigen::VectorXd delta_vector;
  Eigen::MatrixXd next_layer_connection_matrix;

  //Iteration through all the layers of the network
  //starting from the last one
  for(int i_layer=tot_layers; i_layer>-1; i_layer--){
   //This is the case for the OUTPUT layer
   if(i_layer==tot_layers){
    delta_vector = targetVector - (*net)[i_layer].GetOutputVector(); 
    delta_vector = delta_vector.cwiseProduct( (*net)[i_layer].GetDerivativeVector() ); //HadamardProduct
    (*net)[i_layer].SetErrorVector(delta_vector);
   //If the layer is HIDDEN
   } else {

    //The connection matrix is taken for the layer next to the current one
    next_layer_connection_matrix = (*net)[i_layer+1].GetWeightMatrix();
    //To allow the matrix-vector multiplication the matrix must be transpose
    
    //Matrix-vector multiplication returns a vector with lenght equal
    //to the error-vector for the current layer
    Eigen::VectorXd next_layer_error_vector = (*net)[i_layer+1].GetErrorVector();
    delta_vector = next_layer_connection_matrix.transpose() * next_layer_error_vector;
    Eigen::VectorXd current_layer_derivative_vector = (*net)[i_layer].GetDerivativeVector();
    Eigen::VectorXd current_layer_error_vector = delta_vector.cwiseProduct(current_layer_derivative_vector); //HadamardProduct
    (*net)[i_layer].SetErrorVector(current_layer_error_vector);
   }
  }//layer cycle

 //Computing the Squared-Error
 double SE = 0;
 Eigen::VectorXd distance_evector = targetVector - (*net)[tot_layers].GetOutputVector();
 SE = distance_evector.squaredNorm();
 //double accumulator = error_vector.dot(error_vector); //here we take the power of the vector
 //accumulator = accumulator / 2;
 //return accumulator;
 return SE;
}


/**
* Update the Wheights
*
**/
void BackpropagationLearning::UpdateWheights(Network* net){
  int tot_layers = net->ReturnNumberOfLayers();
  tot_layers = tot_layers; //zero based index

 //Iteration through all the layers of the network
 //starting from the last one
 for(int i_layer=0; i_layer<tot_layers; i_layer++){

  //1-Setting the Bias value
  //This value is equal to BiasValue * ErrorValue of the neuron
  Eigen::VectorXd bias_vector;
  bias_vector = (*net)[i_layer].GetBiasVector();
  bias_vector = bias_vector.cwiseProduct( (*net)[i_layer].GetErrorVector() );  //HadamardProduct
  (*net)[i_layer].SetBiasVector(bias_vector);

  //2-Setting the Weight Matrix
  //if INPUT layer
  Eigen::MatrixXd change_rate_matrix;
  Eigen::MatrixXd updated_connection_matrix;
  Eigen::VectorXd inputVector;
  inputVector = (*net)[i_layer].GetInputVector();
  change_rate_matrix = (*net)[i_layer].GetErrorVector() * inputVector.transpose();
  //add here the MatrixScalarMultiplication between change_rate_matrix and LearningRateValue
  change_rate_matrix = change_rate_matrix * mLearningRate; //MatrixScalarMultiplication(change_rate_matrix, mLearningRate);
  updated_connection_matrix = change_rate_matrix + (*net)[i_layer].GetWeightMatrix();
  (*net)[i_layer].SetWeightMatrix(updated_connection_matrix);
 }
}



} //namespace



