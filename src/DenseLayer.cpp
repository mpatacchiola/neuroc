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


#include "DenseLayer.h"


namespace neuroc{



DenseLayer::DenseLayer(unsigned int inputSize, unsigned int outputSize, std::function<Eigen::VectorXd(Eigen::MatrixXd, Eigen::VectorXd)> weightFunction, std::function<Eigen::VectorXd(Eigen::VectorXd,Eigen::VectorXd)> joinFunction, std::function<Eigen::VectorXd(Eigen::VectorXd)> transferFunction, std::function<Eigen::VectorXd(Eigen::VectorXd)> derivativeFunction){

 std::srand((unsigned int) time(0));

 //Defining all the vectors
 mInputVector = Eigen::VectorXd::Zero(inputSize);
 mOutputVector = Eigen::VectorXd::Zero(outputSize);
 mErrorVector = Eigen::VectorXd::Zero(outputSize);
 mBiasVector = Eigen::VectorXd::Random(outputSize);

 //Eigen create a random matrix of input x output dimension
 //The value of the weights are randomized between -1 and +1
 std::srand((unsigned int) time(0));
 //mWeightMatrix = Eigen::MatrixXd::Random(inputSize,outputSize);
 mWeightMatrix = Eigen::MatrixXd::Random(outputSize,inputSize);

 //Assigning the activation function to he layer
 //The default function is the linear one.
 //A different function can be specified using the apposite method.
 mWeightFunction = weightFunction;
 mJoinFunction = joinFunction;
 mTransferFunction =  transferFunction;
 mDerivativeFunction =  derivativeFunction;
}

/**
* Copy constructor
*
* @param rDenseLayer reference to an existing DenseLayer
*/
DenseLayer::DenseLayer(const DenseLayer &rDenseLayer)
{
 mInputVector = rDenseLayer.mInputVector;
 mOutputVector = rDenseLayer.mOutputVector;
 mDerivativeVector = rDenseLayer.mDerivativeVector;
 mErrorVector = rDenseLayer.mErrorVector;
 mBiasVector = rDenseLayer.mBiasVector;
 mWeightMatrix = rDenseLayer.mWeightMatrix;
 mWeightFunction = rDenseLayer.mWeightFunction;
 mJoinFunction = rDenseLayer.mJoinFunction;
 mTransferFunction = rDenseLayer.mTransferFunction;
 mDerivativeFunction = rDenseLayer.mDerivativeFunction;
}



/**
* Overload of the assignment operator
*
* @param rDenseLayer reference to an existing DenseLayer
*/
DenseLayer DenseLayer::operator=(const DenseLayer &rDenseLayer)
{  		
if (this == &rDenseLayer) return *this;  // check for self-assignment 
 mInputVector = rDenseLayer.mInputVector;
 mOutputVector = rDenseLayer.mOutputVector;
 mDerivativeVector = rDenseLayer.mDerivativeVector;
 mErrorVector = rDenseLayer.mErrorVector;
 mBiasVector = rDenseLayer.mBiasVector;
 mWeightMatrix = rDenseLayer.mWeightMatrix;
 mWeightFunction = rDenseLayer.mWeightFunction;
 mJoinFunction = rDenseLayer.mJoinFunction;
 mTransferFunction = rDenseLayer.mTransferFunction;
 mDerivativeFunction = rDenseLayer.mDerivativeFunction;
return *this;
}



DenseLayer::~DenseLayer() {
}



/**
* Compute all the neurons of the DenseLayer and return a vector containing the values of these neurons
*
* @return it returns the vector containing the double, in case of problems it returns an empty vector and print an error
**/
Eigen::VectorXd DenseLayer::Compute(Eigen::VectorXd inputVector) {

 mInputVector = inputVector;
 mOutputVector = mWeightFunction(mWeightMatrix, mInputVector);  //mOutputVector = mWeightMatrix * mInputVector;
 mOutputVector = mJoinFunction(mOutputVector, mBiasVector);  //mOutputVector = mOutputVector + mBiasVector;
 mOutputVector = mTransferFunction(mOutputVector);

 return mOutputVector;
}

Eigen::VectorXd DenseLayer::ComputeDerivative(Eigen::VectorXd inputVector) {

 mDerivativeVector = mWeightFunction(mWeightMatrix, inputVector); //mDerivativeVector = mWeightMatrix * mInputVector;
 mDerivativeVector = mJoinFunction(mDerivativeVector, mBiasVector); //mDerivativeVector = mDerivativeVector + mBiasVector;
 mDerivativeVector = mDerivativeFunction(mDerivativeVector);

 return mDerivativeVector;
}

/**
* Get the values of all the neurons inside the DenseLayer
*
* @return it returns true if it is all right, otherwise false
**/
Eigen::VectorXd DenseLayer::GetInputVector(){
return mInputVector;
}

/**
* Set the values of all the neurons inside the DenseLayer
*
* @param inputValues vector of doubles of the same size of the DenseLayer. Every double is given as input to the neurons inside the DenseLayer.
* @return it returns true if it is all right, otherwise false
**/
bool DenseLayer::SetInputVector(Eigen::VectorXd inputVector) {
 mInputVector = inputVector;
 return true;
}

/**
* Get the values of all the neurons inside the DenseLayer
*
* @return it returns true if it is all right, otherwise false
**/
Eigen::VectorXd DenseLayer::GetOutputVector(){
return mOutputVector;
}

/**
* Set the values of all the neurons inside the DenseLayer
*
* @param inputValues vector of doubles of the same size of the DenseLayer. Every double is given as input to the neurons inside the DenseLayer.
* @return it returns true if it is all right, otherwise false
**/
bool DenseLayer::SetOutputVector(Eigen::VectorXd outputVector) {
 mOutputVector = outputVector;
 return true;
}


/**
* Set the values of all the bias inside the DenseLayer
*
* @param biasVector vector of values with the same size of the DenseLayer.
* @return it returns true if it is all right, otherwise false
**/
bool DenseLayer::SetBiasVector(Eigen::VectorXd biasVector) {
 mBiasVector = biasVector;
 return true;
}

/**
* Get the values of all the bias inside the DenseLayer
*
* @return it returns a vector with the bias values
**/
Eigen::VectorXd DenseLayer::GetBiasVector(){
 return mBiasVector;
}

/**
* Set the values of all the Error associated with the neurons inside the DenseLayer
*
* @param value vector of the same size of the DenseLayer.
* @return it returns true if it is all right, otherwise false
**/
bool DenseLayer::SetErrorVector(Eigen::VectorXd errorVector) {
 mErrorVector = errorVector;
 return true;
}

Eigen::VectorXd DenseLayer::GetErrorVector(){
 return mErrorVector;
}

/**
* Set the values of all the Derivative vector associated with the neurons inside the DenseLayer
*
* @param value vector of the same size of the DenseLayer.
* @return it returns true if it is all right, otherwise false
**/
bool DenseLayer::SetDerivativeVector(Eigen::VectorXd errorVector) {
 mDerivativeVector = errorVector;
 return true;
}

Eigen::VectorXd DenseLayer::GetDerivativeVector(){
 return mDerivativeVector;
}


/**
* It returns the number of neuron contained inside the DenseLayer
*
* @return it returns the number of neurons
**/
unsigned int DenseLayer::ReturnNumberOfNeurons() {
 return 0;
}

/**
* It sets the connection vector for each neuron inside the DenseLayer.
*
* @return it returns true if everything is correct
**/
bool DenseLayer::SetWeightMatrix(Eigen::MatrixXd weightMatrix){
 mWeightMatrix = weightMatrix;
 return true;
}

/**
* Returning a vector of vectors Matrix containing neurons connections
* The vector start with the first incoming connection of the first neuron
* and it ends with the last incoming connection of the last neuron
* If the DenseLayer has a Bias Unit then the first connection of the neurons is the Bias incoming connection
* @return it returns a vector of double or float
**/
Eigen::MatrixXd DenseLayer::GetWeightMatrix() {
 return mWeightMatrix;
}

/**
* It sets the transfer function for the layer.
*
* @return it returns true if everything is correct
**/
bool DenseLayer::SetTransferFunction(std::function<Eigen::VectorXd(Eigen::VectorXd)> transferFunction){
 mTransferFunction = transferFunction;
 return true;
}


//TODO
bool DenseLayer::SetDerivativeFunction(std::function<Eigen::VectorXd(Eigen::VectorXd)> derivativeFunction){
 return false;
}




/**
* Print information about all the neurons contained inside the DenseLayer
*
**/
void DenseLayer::Print() {
std::cout << "Input Size ..... " << mWeightMatrix.cols() << std::endl;
std::cout << "Input Vector: " << std::endl << mInputVector << std::endl;
std::cout << std::endl;
std::cout << "Output Size ..... " << mWeightMatrix.rows() << std::endl;
std::cout << "Output Vector: " << std::endl << mOutputVector << std::endl;
std::cout << std::endl;
std::cout << "Bias Size ..... " << mBiasVector.size() << std::endl;
std::cout << "Bias Vector: " << std::endl << mBiasVector << std::endl;
std::cout << std::endl;
std::cout << "Weight Matrix: " << std::endl << mWeightMatrix << std::endl;
}



} //namespace

