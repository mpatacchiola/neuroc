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

#include "DenseLayer.h"
#include "Dataset.h"
#include <iostream> //printing functions
#include <Eigen/Dense>

using namespace std;


namespace neuroc{

/**
* \class Network
* \brief This is the higest class and it permits to create Networks without declaring neurons or layers
*
*/
class Network {

public:


Network();

Network(const Network &rNetwork);

Network(std::initializer_list<DenseLayer> layersList);

~Network();

Network operator=(const Network &rNetwork);

DenseLayer& operator[](unsigned int index);


unsigned int Size();

Eigen::VectorXd Compute(Eigen::VectorXd InputVector);
Eigen::VectorXd ComputeDerivative(Eigen::VectorXd InputVector);
double ComputeMeanSquaredError(neuroc::Dataset, neuroc::Dataset);

double Test(neuroc::Dataset, neuroc::Dataset);

int ReturnNumberOfLayers();

unsigned int ReturnNumberOfNeurons();

void Print();



private:
 std::vector<DenseLayer> mLayersVector;


};

} //namespace


#endif // NETWORK_H
