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

#include<neuroc/Neuron.h>
#include<neuroc/Layer.h>
#include<neuroc/Network.h>
#include<neuroc/Dataset.h>
#include<neuroc/InitFunctions.h>
#include<neuroc/WeightFunctions.h>
#include<neuroc/JointFunctions.h>
#include<neuroc/TransferFunctions.h>
#include<neuroc/BackpropagationLearning.h>
#include<neuroc/InitFunctions.h>

int main()
{

 //First we must create the connection vectors
 //necessary for building the neurons. Here I
 //declare two vectors with a certain number
 //of zero inside.
 std::vector<double> connectionVector(2);
 std::vector<double> connectionVectorOutput(4);

 //I create the two neuron prototype, one for
 //the neurons in the hidden layer and the
 //other for the neuron in the output layer.
 neuroc::Neuron neuronPrototype(connectionVector, neuroc::WeightFunctions::DotProduct, neuroc::JointFunctions::Sum, neuroc::TransferFunctions::Sigmoid, neuroc::TransferFunctions::SigmoidDerivative, 0.35 );
 neuroc::Neuron neuronPrototypeOutput(connectionVectorOutput, neuroc::WeightFunctions::DotProduct, neuroc::JointFunctions::Sum, neuroc::TransferFunctions::Sigmoid, neuroc::TransferFunctions::SigmoidDerivative, 0.35 );

 //Creating the two layer, the neuron prototype
 //and the number of neurons must be specified
 //during the declaration of the object.
 neuroc::Layer HiddenLayer(neuronPrototype, 4);
 neuroc::Layer OutputLayer(neuronPrototypeOutput, 1);

 //Creating the network. It is composed of the
 //two layers created in the previous part.
 neuroc::Network myNet({HiddenLayer, OutputLayer});
 myNet.RandomizeConnectionMatrix(neuroc::InitFunctions::Unit);

 //Creating the XOR datasets. One dataset is
 //for the input values and the other for 
 //the target values.
 neuroc::Dataset myInputDataset;
 neuroc::Dataset myTargetDataset;
 myInputDataset.PushBackData({1,1});
 myTargetDataset.PushBackData({0});
 myInputDataset.PushBackData({1,0});
 myTargetDataset.PushBackData({1});
 myInputDataset.PushBackData({0,1});
 myTargetDataset.PushBackData({1});
 myInputDataset.PushBackData({0,0});
 myTargetDataset.PushBackData({0});

 //Creating the Backpropagation object and
 //setting the learing rate.
 neuroc::BackpropagationLearning myBack;
 myBack.SetLearningRate(0.5);

 //Starting Online Learing.
 myNet = myBack.StartOnlineLearning(myNet, myInputDataset, myTargetDataset, 50000, true);

 //Starting the test of the network.
 myBack.StartTest(myNet, myInputDataset, myTargetDataset, true);

 return 0;
}



