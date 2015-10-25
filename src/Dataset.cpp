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

#include"Dataset.h"
#include <iterator>

namespace neuroc{

/**
* Class constructor.
*
* @param datasetDimension the dimension of the dataset
*/
Dataset::Dataset(unsigned int datasetDimension) {
mDataVector.reserve(datasetDimension);
}

Dataset::Dataset() {
}

Dataset::~Dataset() {
mDataVector.clear();
}




/**
* It permits to push back in the Dataset a new set of data
*
* @param dataToPush the vector of values to push inside the Dataset
**/
bool Dataset::PushBackData(std::vector<double> dataToPush) {
mDataVector.push_back(dataToPush);
return true;
}

/**
* It splits the dataset in two parts, mantaining in the current object
* only the first part, and returning as a dataset the second part.
*
* @param index the point where apply the split.
**/
Dataset Dataset::Split(unsigned int index){
 Dataset dataset_to_return;
 if(mDataVector.size()==0){
  std::cerr << "Error: Dataset empty." << std::endl;
  return dataset_to_return;
 }

 int size_to_give = mDataVector[0].size() - index;

 if(size_to_give<=0){
  std::cerr << "Error: Dataset cannot be split, the index is outside the range." << std::endl;
  return dataset_to_return;
 }

 for(auto it=mDataVector.begin(); it!=mDataVector.end(); ++it){
  auto it_split = std::next(it->begin(), index);
  std::vector<double> vector_to_give;
  vector_to_give.reserve(size_to_give);
  for(;it_split!=it->end(); ++it_split){
   vector_to_give.push_back(*it_split); //it assigns the element to a new vector
  }
  it->erase(it_split, it->end()); //erase the element in the vector
  dataset_to_return.PushBackData(vector_to_give);
 }

 return dataset_to_return;
}



/**
* It permits to extract a vector of data
*
* @param index of the input vector to return
**/
std::vector<double> Dataset::GetData(unsigned int index) {
if(index > mDataVector.size()){
std::cerr << "Error: Dataset out of range." << std::endl;
std::vector<double> void_vector;
return void_vector;
}
return mDataVector[index];
}

/**
* It permits to set a vector of data
*
* @param index of the input vector to set
**/
bool Dataset::SetData(unsigned int index, std::vector<double> data) {
try {
mDataVector[index] = data;
return true;
} catch(...) {
std::cerr << "Error: out of Range error." << '\n';
return false;
}
}

/**
* It permits to extract a vector of data
*
* @param index of the input vector to return
**/
unsigned int Dataset::ReturnNumberOfData() {
return mDataVector.size();
}


/**
* It prints the data stored inside the Dataset
*
* @param index of the data vector to print
**/
void Dataset::PrintData(unsigned int index){
std::vector<double> temp_vector;
temp_vector = mDataVector[index];
std::cout << "INPUT: ";
for(unsigned int i=0; i<temp_vector.size(); i++){
std::cout << temp_vector[i] << "; ";
}
std::cout << std::endl;
}

/**
* It returns a string of data organized in Comma
* Separated Values.
*
**/
std::string Dataset::ReturnStringCSV() {
std::ostringstream string_stream;
string_stream << mDataVector.size() <<   '\n';
string_stream << '\n';

for(unsigned int i=0; i<mDataVector.size(); i++) {

std::vector<double> temp_vector_input(mDataVector[i]);

for(unsigned int j=0; j<temp_vector_input.size(); j++) {
string_stream << temp_vector_input[j] << ",";
}

string_stream << '\n';
}


return string_stream.str();
}


} //namespace

