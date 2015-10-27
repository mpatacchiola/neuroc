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

#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <memory>  // shared_ptr
#include <cmath>  //  "exp" function
#include <string>
#include <random>
#include <iostream>  // printing functions
#include <fstream> //save in XML
#include <sstream>

namespace neuroc{

/**
 * \class Neuron
 * \brief This is the lowest class and it represents the Neuron object
 *
 *
 */

class Neuron {
public:

Neuron(const Neuron &rNeuron);
Neuron(const std::vector<double>& connectionsVector, std::function<double(std::vector<double>, std::vector<double>)> weightFunction, std::function<double(double, double)> joinFunction, std::function<double(double)> transferFunction, std::function<double(double)> derivativeFunction, double biasWeight=0);

Neuron operator=(const Neuron &rNeuron);
const double& operator[](const unsigned int index) const;
unsigned int Size();

double Compute(std::vector<double> inputVector);
double ComputeDerivative(std::vector<double> inputVector);

void RandomizeConnectionVector(std::function<double(double)> initFunction);

void SetConnectionVector(const std::vector<double>& connectionVector);
std::vector<double> GetConnectionVector() const;
void SetValue(double value);
double GetValue();
void SetDerivative(double value);
double GetDerivative();
void SetError(double value);
double GetError();
void SetBias(double value);
double GetBias();



void Print();

private:

double mValue = 0;  //value obtained after the computation
double mDerivative = 0;
double mError = 0;  //error obtained after the error backpropagation 
double mBias = 0;   //value of the bias connection

std::vector<double> mConnectionsVector;  //container of the connections values

std::function<double(std::vector<double>, std::vector<double>)> WeightFunction;
std::function<double(double, double)> JoinFunction;
std::function<double(double)> TransferFunction;
std::function<double(double)> DerivativeFunction;

};  // Class Neuron

}//namespace


#endif // NEURON_H
