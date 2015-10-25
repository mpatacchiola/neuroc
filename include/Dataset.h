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

#ifndef DATASET_H
#define DATASET_H

#include <vector>
#include <iostream> //printing functions
#include <sstream>
#include <initializer_list>

namespace neuroc{

/**
* \class Dataset
*
* \brief This class permits to create complex datasets and use them to feed the network.
*
* This class provides two containers for Input and Target datas. The Dataset can be created using the Parser directly
* from a CSV (Comma-Separeted Values) file or an XML file. During the backpropagation training it loads Input and Output values
* and use them to feed the Network.
*
*/
class Dataset {

public:

Dataset(unsigned int datasetDimension);

Dataset();

~Dataset();

bool PushBackInputAndTarget(std::initializer_list<double> inputList, std::initializer_list<double> targetList);

bool PushBackInputAndTarget(std::vector<double> inputDataToPush, std::vector<double> targetDataToPush);

bool PushBackInput(std::vector<double> dataToPush);

bool PushBackInput(std::initializer_list<double> inputList);

std::vector<double> GetInput(unsigned int index);

bool SetInput(unsigned int index, std::vector<double> data);

unsigned int ReturnNumberOfInputs();

bool PushBackTarget(std::vector<double> dataToPush) ;


bool PushBackTarget(std::initializer_list<double> targetList);

std::vector<double> GetTarget(unsigned int index);

bool SetTarget(unsigned int index, std::vector<double> data);

unsigned int ReturnNumberOfTargets();

bool CheckIntegrity();


void PrintInput(unsigned int index);

void PrintTarget(unsigned int index);

std::string ReturnStringXML();


std::string ReturnStringCSV();

private:

std::vector<std::vector<double>> nInputsVector;
std::vector<std::vector<double>> nTargetsVector;

};


} //namespace

#endif // DATASET_H
