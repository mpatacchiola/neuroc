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

#ifndef BACKPROPAGATIONLEARNING_H
#define BACKPROPAGATIONLEARNING_H

#include <iostream>  // printing functions
#include <Network.h>
#include <Eigen/Dense>
#include <Dataset.h>

namespace neuroc{

/**
 * \class BackpropagationLearning
 * \brief Implementation of the Error-Backpropagation Learning algorithm
 *
 *
 */

class BackpropagationLearning {
public:

BackpropagationLearning();
~BackpropagationLearning();

double SingleStepOnlineLearning(Network* net, Eigen::VectorXd inputVector, Eigen::VectorXd targetVector, bool print=true);
void StartOnlineLearning(Network* net, Dataset& inputDataset, Dataset& targetDataset, unsigned int cycles, bool print=true);
//Network StartOnlineLearning(Network net, Dataset& inputDataset, Dataset& targetDataset, unsigned int cycles, bool print=true);
//void StartTest(Network& net, Dataset& inputDataset, Dataset& targetDataset, bool print=true);

void SetLearningRate(double value);
double GetLearningRate();


private:

//Network mNet;
double mLearningRate;
double learningRate;

void Forward(Network* net, Eigen::VectorXd );
double ErrorBackpropagation(Network* net, Eigen::VectorXd );
void UpdateWheights(Network* net);


};  // Class BackpropagationLearning

}//namespace


#endif // BACKPROPAGATIONLEARNING_H
