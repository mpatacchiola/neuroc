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

#ifndef DENSELAYER_H
#define DENSELAYER_H

#include <iostream> //printing functions
#include <functional>
#include <Eigen/Dense>


namespace neuroc{
/**
* \class DenseLayer
* \brief
*/
class DenseLayer {

public:

DenseLayer(unsigned int inputSize, unsigned int outputSize,std::function<Eigen::VectorXd(Eigen::MatrixXd, Eigen::VectorXd)>, std::function<Eigen::VectorXd(Eigen::VectorXd,Eigen::VectorXd)>, std::function<Eigen::VectorXd(Eigen::VectorXd)>, std::function<Eigen::VectorXd(Eigen::VectorXd)>);

DenseLayer(const DenseLayer &rDenseLayer);

DenseLayer operator=(const DenseLayer &rDenseLayer);

~DenseLayer();



Eigen::VectorXd Compute(Eigen::VectorXd inputVector);
Eigen::VectorXd ComputeDerivative(Eigen::VectorXd inputVector);

bool SetInputVector(Eigen::VectorXd valueVector);
Eigen::VectorXd GetInputVector();

bool SetOutputVector(Eigen::VectorXd valueVector);
Eigen::VectorXd GetOutputVector();

bool SetBiasVector(Eigen::VectorXd biasVector);
Eigen::VectorXd GetBiasVector();

bool SetErrorVector(Eigen::VectorXd errorVector);
Eigen::VectorXd GetErrorVector();

bool SetDerivativeVector(Eigen::VectorXd errorVector);
Eigen::VectorXd GetDerivativeVector();

unsigned int ReturnNumberOfNeurons();

bool SetWeightMatrix(Eigen::MatrixXd);
Eigen::MatrixXd GetWeightMatrix();

bool SetTransferFunction(std::function<Eigen::VectorXd(Eigen::VectorXd)>);
bool SetDerivativeFunction(std::function<Eigen::VectorXd(Eigen::VectorXd)>);

void Print();



private:
Eigen::MatrixXd mWeightMatrix;
Eigen::VectorXd mInputVector;
Eigen::VectorXd mOutputVector;
Eigen::VectorXd mDerivativeVector;
Eigen::VectorXd mBiasVector;
Eigen::VectorXd mErrorVector;

std::function<Eigen::VectorXd(Eigen::MatrixXd, Eigen::VectorXd)> mWeightFunction;
std::function<Eigen::VectorXd(Eigen::VectorXd)> mTransferFunction;
std::function<Eigen::VectorXd(Eigen::VectorXd)> mDerivativeFunction;
std::function<Eigen::VectorXd(Eigen::VectorXd, Eigen::VectorXd)> mJoinFunction;
};

} //namespace


#endif // DENSELAYER_H
