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
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

namespace neuroc{

/**
* Class constructor.
*
*/
Dataset::Dataset() {
}

/**
* Class constructor.
*
* @param datasetDimension the dimension of the dataset
*/
Dataset::Dataset(unsigned int datasetDimension) {
 mDataVector.reserve(datasetDimension);
}

/**
* Class destructor.
*
*/
Dataset::~Dataset() {
 mDataVector.clear();
}

/**
* It divides all the value by the divisor specified.
*
* @param divisor
**/
bool Dataset::DivideBy(double divisor){
 if(divisor == 0) return false;
 for(auto it_set=mDataVector.begin(); it_set!=mDataVector.end(); ++it_set) {
  for(auto it_data=it_set->begin(); it_data!=it_set->end(); ++it_data) {
   *it_data /= divisor;
  }
 }
 return true;
}

/**
* Operator overload [] it is used to return the reference to the
* vector stored inside the dataset at a certain position.
* @param index the number of the element stored inside the layer
* @return it returns a reference to the vector
**/
std::vector<double>& Dataset::operator[](unsigned int index) {
 if (index >= mDataVector.size()) throw std::domain_error("Error: Out of Range index.");
 return mDataVector[index];
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
  auto it_start_split = std::next(it->begin(), index);
  std::vector<double> vector_to_give;
  vector_to_give.reserve(size_to_give);
  for(auto it_split=it_start_split; it_split!=it->end(); ++it_split){
   vector_to_give.push_back(*it_split); //it assigns the element to a new vector
  }
  it->erase(it_start_split, it->end()); //erase the element in the vector
  dataset_to_return.PushBackData(vector_to_give);
 }

 return dataset_to_return;
}

/**
* It deletes all the elements inside the dataset.
*
**/
void Dataset::Clear(){
 mDataVector.clear();
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
 if(index > mDataVector.size()){
  std::cerr << "Error: Dataset out of range." << std::endl;
  return;
 }
 for(auto it_data=mDataVector[index].begin(); it_data!=mDataVector[index].end(); ++it_data) {
  if(it_data!=mDataVector[index].end() - 1) std::cout << *it_data << ",";
  else std::cout << *it_data;
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
 for(unsigned int i=0; i<mDataVector.size(); i++) {
  std::vector<double> temp_vector_input(mDataVector[i]);
  for(unsigned int j=0; j<temp_vector_input.size(); j++) {
   string_stream << temp_vector_input[j] << ",";
  }
  string_stream << '\n';
 }

 return string_stream.str();
}


/**
* It loads data from a Comma Separated Value file.
* The Data are appended in the current dataset.
*
* @param filePath the path to the file to load
**/
bool Dataset::LoadFromCSV(std::string filePath){
 if(FileExist(filePath) == false){
  std::cerr<<"Error: Cannot find the input file."<<std::endl;
  return false;
 }
 std::ifstream train_file(filePath);
 std::string token;

 while(std::getline(train_file, token)) {
  //remove white space
  token.erase(std::remove_if(token.begin(), token.end(), isspace), token.end());
  std::vector<double> data_vector;
  std::stringstream ss(token);
  unsigned int i;
  //push the values into the temp vector
  while(ss >> i){
   data_vector.push_back(i);
   if(ss.peek()== ',') ss.ignore();
  }
  //push the temp vector inside the dataset
  mDataVector.push_back(data_vector);
 }
 train_file.close();
 return true;
}

/**
* It saves the dataset as CSV file
*
* @param filePath the path to the file to load
**/
bool Dataset::SaveAsCSV(std::string filePath) {
 std::ofstream file_stream(filePath, std::fstream::app);
 if(!file_stream) {
  std::cerr<<"Error: Cannot open the output file."<<std::endl;
  return false;
 }
 for(auto it_set=mDataVector.begin(); it_set!=mDataVector.end(); ++it_set) {
  for(auto it_data=it_set->begin(); it_data!=it_set->end(); ++it_data) {
  if(it_data!=it_set->end() - 1) file_stream << *it_data << ",";
  else file_stream << *it_data;
  }
  file_stream << '\n';
 }
 file_stream.close();
 return true;
}

/**
* It checks if the file exist.
*
**/
bool Dataset::FileExist (std::string name) {
 if (FILE *file = fopen(name.c_str(), "r")) {
  fclose(file);
  return true;
 } else {
  return false;
 }   
}


} //namespace

