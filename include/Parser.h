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

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "Network.h"
#include "Neuron.h"
#include "Layer.h"
#include "Dataset.h"


/**
* \class Parser
*
* \brief This class permits to save networks in XML files
*
* \author Massimiliano Patacchiola
*
* \version 1.0
*
* \date 2015
*
* \todo LoadFromXML
*
* Contact:
*
*/

class Parser {

public:

Parser();
~Parser();

bool InitialiseXML(std::string filePath);
bool FinaliseXML();

inline bool SetPath(std::string filePath){
mFilePath=filePath;
return true;
}

inline std::string GetPath(){ return mFilePath; }

template<typename T>
bool SaveNetwork(Network<T>& rNetwork){

 if(mInitialised == false){
  std::cerr<<"Error: the Parser was not Initialised."<<std::endl;
  return false;
 }

 std::ofstream file_stream(mFilePath, std::fstream::app); 

 if(!file_stream) {
  std::cerr<<"Error: Cannot open the output file."<<std::endl;
  return false;
 }

 file_stream << rNetwork.ReturnStringXML();

 file_stream.close();
 return true;
}

template<typename T>
bool SaveLayer(Layer<T>& rLayer){

 if(mInitialised == false){
  std::cerr<<"Error: the Parser was not Initialised."<<std::endl;
  return false;
 }

 std::ofstream file_stream(mFilePath, std::fstream::app); 

 if(!file_stream) {
  std::cerr<<"Error: Cannot open the output file."<<std::endl;
  return false;
 }

 file_stream << rLayer.ReturnStringXML();

 file_stream.close();
 return true;

}

template<typename T>
bool SaveNeuron(Neuron<T>& rNeuron){

 if(mInitialised == false){
  std::cerr<<"Error: the Parser was not Initialised."<<std::endl;
  return false;
 }

 std::ofstream file_stream(mFilePath, std::fstream::app); 

 if(!file_stream) {
  std::cerr<<"Error: Cannot open the output file."<<std::endl;
  return false;
 }

 file_stream << rNeuron.ReturnStringXML();

 file_stream.close();
 return true;
}

template<typename T>
bool SaveDataset(Dataset<T>& rDataset){

 if(mInitialised == false){
  std::cerr<<"Error: the Parser was not Initialised."<<std::endl;
  return false;
 }

 if(rDataset.CheckIntegrity() == false) {
  std::cerr<<"Error: The dataset is bad formed."<<std::endl;
  return false;
 }
 std::ofstream file_stream(mFilePath, std::fstream::app); 

 if(!file_stream) {
  std::cerr<<"Error: Cannot open the output file."<<std::endl;
  return false;
 }

 file_stream << rDataset.ReturnStringXML();

 file_stream.close();
 return true;
}

template<typename T>
bool SaveDatasetAsCSV(Dataset<T>& rDataset, std::string filePath){

 if(rDataset.CheckIntegrity() == false) {
  std::cerr<<"Error: The dataset is bad formed."<<std::endl;
  return false;
 }
 std::ofstream file_stream(filePath, std::fstream::app); 

 if(!file_stream) {
  std::cerr<<"Error: Cannot open the output file."<<std::endl;
  return false;
 }

 file_stream << rDataset.ReturnStringCSV();

 file_stream.close();
 return true;
}

bool CheckIntegrity();
unsigned int ReturnNumberOfNetworks();
unsigned int ReturnNumberOfLayers();
unsigned int ReturnNumberOfNeurons();
unsigned int ReturnNumberOfDatasets();

private:
std::string mFilePath;
bool mInitialised;

std::string GetLastLine(std::string filePath);
std::string GetFirstLine(std::string filePath);


};

#endif // PARSER_H


