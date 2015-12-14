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
#include <iostream> 
#include <Eigen/StdVector>
#include <Eigen/Dense>


namespace neuroc{

/**
* \class Dataset
*
* \brief This class permits to create complex datasets and use them to feed the network.
*
* This class provides a vector of vector container, usefull for storing data.
*
*
*/
class Dataset {

public:

Dataset(unsigned int datasetDimension);

Dataset();

~Dataset();

Eigen::VectorXd& operator[](unsigned int index);

bool PushBackData(Eigen::VectorXd dataToPush);

Dataset Split(unsigned int index);

void Clear();

bool DivideBy(double divisor);
bool MultiplyBy(double multiplier);

Eigen::VectorXd GetData(unsigned int index);
bool SetData(unsigned int index, Eigen::VectorXd data);

unsigned int ReturnNumberOfElements();

void PrintData(unsigned int index);
bool LoadFromCSV(std::string filePath);
bool SaveAsCSV(std::string filePath);

private:

//std::vector<std::vector<double>> mDataVector;
bool FileExist (std::string name);
std::vector<Eigen::VectorXd,Eigen::aligned_allocator<Eigen::VectorXd> > mDataVector;


};


} //namespace

#endif // DATASET_H
