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

#include <vector>
#include <iostream>  // printing functions
#include <Network.h>
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

Network StartOnlineLearning(Network net, Dataset& inputDataset, Dataset& targetDataset, unsigned int cycles, bool print=true);
void StartTest(Network& net, Dataset& inputDataset, Dataset& targetDataset, bool print=true);

void SetLearningRate(double value);
double GetLearningRate();


private:

Network mNet;
double mLearningRate;
double learningRate;

void Forward(std::vector<double> inputVector);
double ErrorBackpropagation(std::vector<double> targetDataset);
void UpdateWheights(std::vector<double> inputVector);

std::vector<std::vector<double>> TransposeMatrix( std::vector<std::vector<double>> matrix);
std::vector<double> HadamardProduct(std::vector<double> firstVector, std::vector<double> secondVector);
std::vector<double> MatrixVectorMultiplication(std::vector<std::vector<double>> matrix, std::vector<double> inputVector);
std::vector<std::vector<double>> MatrixScalarMultiplication(std::vector<std::vector<double>> matrix, double scalar);
std::vector<std::vector<double>> MatrixMatrixAddition(std::vector<std::vector<double>> firstMatrix, std::vector<std::vector<double>> secondMatrix);
std::vector<double> PowerVector(std::vector<double> firstVector, double power);
std::vector<double> VectorScalarMultiplication(std::vector<double> firstVector, double scalar);
std::vector<double> SubtractVectors(std::vector<double> firstVector, std::vector<double> secondVector);
double DotProduct(std::vector<double> firstVector, std::vector<double> secondVector);
std::vector<std::vector<double>> OuterProduct(std::vector<double> firstVector, std::vector<double> secondVector);

};  // Class BackpropagationLearning

}//namespace


#endif // BACKPROPAGATIONLEARNING_H
