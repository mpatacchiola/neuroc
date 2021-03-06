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


/* 
 *
 * In this example I will use an handwritten digits dataset to
 * learn a feedforward neural network to recognize the digits.
 * The structure of the network derives from the structure
 * of the dataset. Each line of the dataset is a 17-dimensional
 * vector, where the integers in the range 0-15 represent the pixel 
 * intensity (from 0 to 100) of a 4x4 matrix. The last number
 * of the line represent the coded digit. The corresponding 
 * network has 16 input nodes (one for each pixel), and 1 output 
 * node (representing the recognized digit).
 *
 * The dataset is included in the examples folder, and it is
 * uncompressed during the installation. The references to
 * the dataset are reported below. The executable find the
 * dataset only if you run it having as current directory
 * of your terminal the /examples/build/exec directory.
 *
 * Link to the dataset:
 * https://archive.ics.uci.edu/ml/datasets/Pen-Based+Recognition+of+Handwritten+Digits
 *
 * Dataset Source:
 *
 * E. Alpaydin, Fevzi. Alimoglu 
 * Department of Computer Engineering 
 * Bogazici University, 80815 Istanbul Turkey 
 * alpaydin '@' boun.edu.tr
 * 
 *
*/

#include <iostream>
//#include<vector>
//#include<neuroc/Neuron.h>
//#include<neuroc/Layer.h>
//#include<neuroc/Network.h>
//#include<neuroc/Dataset.h>
//#include<neuroc/InitFunctions.h>
//#include<neuroc/WeightFunctions.h>
//#include<neuroc/JointFunctions.h>
//#include<neuroc/TransferFunctions.h>
//#include<neuroc/BackpropagationLearning.h>
//#include<neuroc/InitFunctions.h>

#include <iostream>
#include<neuroc/DenseLayer.h>
#include<neuroc/Network.h>
#include<neuroc/BackpropagationLearning.h>
#include<neuroc/Dataset.h>
#include<neuroc/WeightFunctions.h>
#include<neuroc/JoinFunctions.h>
#include<neuroc/TransferFunctions.h>
#include<Eigen/Dense>

int main()
{

 //Loading the dataset from CSV file
 neuroc::Dataset myInputDataset;
 myInputDataset.LoadFromCSV("./pendigits.tes");

 //The last digit of the dataset is the
 //desired output. To create the target
 //dataset I split the previous dataset
 //cutting off the last number.
 neuroc::Dataset myTargetDataset = myInputDataset.Split(16);

 //The two dataset are normalized in 
 //the range 0-1
 myInputDataset.DivideBy(100);
 myTargetDataset.DivideBy(10);

 neuroc::DenseLayer my_layer(16, 10, neuroc::WeightFunctions::DotProduct, neuroc::JoinFunctions::Sum, neuroc::TransferFunctions::Sigmoid, neuroc::TransferFunctions::SigmoidDerivative);
 neuroc::DenseLayer my_output_layer(10, 1, neuroc::WeightFunctions::DotProduct, neuroc::JoinFunctions::Sum, neuroc::TransferFunctions::Sigmoid, neuroc::TransferFunctions::SigmoidDerivative);

 neuroc::Network myNetwork({my_layer, my_output_layer});

 //Creating the backpropagation learning
 //object for teaching the network.
 neuroc::BackpropagationLearning myBack;
 myBack.SetLearningRate(0.35);

 //Starting the learning
 myBack.StartOnlineLearning(&myNetwork, myInputDataset, myTargetDataset, 500, true);

 //Loading the test dataset from file
 neuroc::Dataset myTestInputDataset;
 myTestInputDataset.LoadFromCSV("./pendigits.tra");
 neuroc::Dataset myTestTargetDataset = myTestInputDataset.Split(16);
 myTestInputDataset.DivideBy(100);
 myTestTargetDataset.DivideBy(10);

 //Starting the test using the last
 //dataset created.
 myNetwork.Test(myTestInputDataset, myTestTargetDataset );
}





