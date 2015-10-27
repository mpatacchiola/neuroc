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

#ifndef LAYER_H
#define LAYER_H

#include "Neuron.h"
#include <iostream> //printing functions
#include <memory>  // shared_ptr
#include <cassert>
#include <fstream> //save in XML
#include <sstream>

namespace neuroc{
/**
* \class Layer
* \brief This class is the middle level of the neural network library. It is a container for neurons. It allows the use of different floating points.
*/
class Layer {

public:


Layer(const Layer &rLayer);

Layer(Neuron neuronPrototype, unsigned int dimension);

Layer(std::initializer_list<Neuron> neuronList);

Layer operator=(const Layer &rLayer);

~Layer();

Neuron& operator[](unsigned int index);


const unsigned int Size() const;

std::vector<double> Compute(std::vector<double> inputVector);
std::vector<double> ComputeDerivative(std::vector<double> inputVector);

void RandomizeConnectionMatrix(std::function<double(double)> initFunction);

bool SetValueVector(std::vector<double> valueVector);
std::vector<double> GetValueVector();

std::vector<double> GetDerivativeVector();

bool SetBiasVector(std::vector<double> biasVector);
std::vector<double> GetBiasVector();

bool SetErrorVector(std::vector<double> errorVector);
std::vector<double> GetErrorVector();

unsigned int ReturnNumberOfNeurons();

bool SetConnectionMatrix(std::vector< std::vector<double> >);
std::vector< std::vector<double> > GetConnectionMatrix();

void Print();



private:
    std::vector<Neuron> mNeuronsVector; /**< vector which contains the neurons of the layer */


};

} //namespace


#endif // LAYER_H
