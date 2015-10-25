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

#include"Parser.h"
#include <fstream> //save in XML


namespace neuroc{

Parser::Parser(){
  mInitialised = false;
}


Parser::~Parser(){
}

/**
* It Initialise the XML file deleting all previous content and adding a the XML declaration and the root node <neuroc>
*
* @return it returns true in case of succes otherwise it returns false
**/
bool Parser::InitialiseXML(std::string filePath){
 Parser::SetPath(filePath);
 std::ofstream file_stream(mFilePath, std::fstream::trunc); 

 if(!file_stream) {
  std::cerr<<"Error: Cannot open the output file."<<std::endl;
  mInitialised = false;
  return false;
 }

 file_stream << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << '\n';
 file_stream << "<neuroc>" << std::endl;
 file_stream.close();
 mInitialised = true;
 return true;
}


/**
* It Finalises the XML file adding a terminator index
*
* @return it returns true in case of succes otherwise it returns false
**/
bool Parser::FinaliseXML(){

 if(mInitialised == false){
  std::cerr<<"Error: the Parser was not Initialised."<<std::endl;
  return false;
 }

 std::ofstream file_stream(mFilePath, std::fstream::app); 

 if(!file_stream) {
  std::cerr<<"Error: Cannot open the output file."<<std::endl;
  return false;
 }

 file_stream << "</neuroc>" <<  '\n';
 file_stream.close();
 return true;
}


bool Parser::SetPath(std::string filePath) {
mFilePath=filePath;
return true;
}

std::string Parser::GetPath() {
return mFilePath;
}


bool Parser::AddNote(std::string note, std::string title) {

if(mInitialised == false) {
std::cerr<<"Error: the Parser was not Initialised."<<std::endl;
return false;
}

std::ofstream file_stream(mFilePath, std::fstream::app);

if(!file_stream) {
std::cerr<<"Error: Cannot open the output file."<<std::endl;
return false;
}

if(title == "") file_stream << "<note>" << note << "</note>" << '\n';
else file_stream << "<note " << "title:'" << title << "'>" << note << "</note>" << '\n';

return true;
}


bool Parser::SaveNetwork(Network& rNetwork) {

if(mInitialised == false) {
std::cerr<<"Error: the Parser was not Initialised."<<std::endl;
return false;
}

std::ofstream file_stream(mFilePath, std::fstream::app);

if(!file_stream) {
std::cerr<<"Error: Cannot open the output file."<<std::endl;
return false;
}

file_stream << "<network>" << '\n';
file_stream << "<size>" << rNetwork.Size() <<"</size>" << '\n';
file_stream << "<user_value>" << rNetwork.GetUserValue() <<"</user_value>" << '\n';	
for(unsigned int lay=0; lay<rNetwork.Size(); lay++){

file_stream << "<layer>" << '\n';
file_stream << "<size>" << rNetwork[lay].Size() <<"</size>" << '\n';
for(unsigned int neu=0; neu<rNetwork[lay].Size(); neu++){
	file_stream << "<neuron>" << '\n';
	file_stream << "<value>" << rNetwork[lay][neu].GetValue() <<"</value>" << '\n';
	file_stream << "<error>" << rNetwork[lay][neu].GetError() <<"</error>" << '\n';
	file_stream << "<bias>" << rNetwork[lay][neu].GetBias() <<"</bias>" << '\n';
	file_stream << "<size>" << rNetwork[lay][neu].Size() <<"</size>" << '\n';
	file_stream << "<connections>";
	for(unsigned int con=0; con<rNetwork[lay][neu].Size(); con++){
	 file_stream << rNetwork[lay][neu][con] << ";";
	}
	file_stream <<"</connections>" << '\n';
	file_stream << "</neuron>" << '\n';
}
file_stream << "</layer>" << '\n';
}
file_stream << "</network>" << '\n';

file_stream.close();
return true;
}


bool Parser::SaveLayer( Layer& rLayer) {

if(mInitialised == false) {
std::cerr<<"Error: the Parser was not Initialised."<<std::endl;
return false;
}

std::ofstream file_stream(mFilePath, std::fstream::app);

if(!file_stream) {
std::cerr<<"Error: Cannot open the output file."<<std::endl;
return false;
}

file_stream << "<layer>" << '\n';
file_stream << "<size>" << rLayer.Size() <<"</size>" << '\n';
for(unsigned int neu=0; neu<rLayer.Size(); neu++){
	file_stream << "<neuron>" << '\n';
	file_stream << "<value>" << rLayer[neu].GetValue() <<"</value>" << '\n';
	file_stream << "<error>" << rLayer[neu].GetError() <<"</error>" << '\n';
	file_stream << "<bias>" << rLayer[neu].GetBias() <<"</bias>" << '\n';
	file_stream << "<size>" << rLayer[neu].Size() <<"</size>" << '\n';
	file_stream << "<connections>";
	for(unsigned int con=0; con<rLayer[neu].Size(); con++){
	 file_stream << rLayer[neu][con] << ";";
	}
	file_stream <<"</connections>" << '\n';
	file_stream << "</neuron>" << '\n';
}
file_stream << "</layer>" << '\n';

file_stream.close();
return true;

}


bool Parser::SaveNeuron( Neuron& rNeuron) {

if(mInitialised == false) {
std::cerr<<"Error: the XML Parser was not Initialised."<<std::endl;
return false;
}

std::ofstream file_stream(mFilePath, std::fstream::app);

if(!file_stream) {
std::cerr<<"Error: Cannot open the output file."<<std::endl;
return false;
}

file_stream << "<neuron>" << '\n';
file_stream << "<value>" << rNeuron.GetValue() <<"</value>" << '\n';
file_stream << "<error>" << rNeuron.GetError() <<"</error>" << '\n';
file_stream << "<bias>" << rNeuron.GetBias() <<"</bias>" << '\n';
file_stream << "<size>" << rNeuron.Size() <<"</size>" << '\n';
file_stream << "<connections>";
for(unsigned int con=0; con<rNeuron.Size(); con++){
file_stream << rNeuron[con] << ";";
}
file_stream <<"</connections>" << '\n';
file_stream << "</neuron>" << '\n';

file_stream.close();
return true;
}


bool Parser::FillNeuron(Neuron* pNeuron) {
return false;
}



bool Parser::SaveDatasetAsCSV(Dataset& rDataset, std::string filePath) {

std::ofstream file_stream(filePath, std::fstream::app);

if(!file_stream) {
std::cerr<<"Error: Cannot open the output file."<<std::endl;
return false;
}

file_stream << rDataset.ReturnStringCSV();

file_stream.close();
return true;
}

/**
* It Returns the number of Networks saved inside the XML file
*
* @return it returns an unsigned int representing the number of Networks
**/
unsigned int Parser::ReturnNumberOfNetworks()
{

  std::ifstream file_stream (mFilePath, std::ifstream::binary);
 if(!file_stream) {
  std::cerr<<"Error: Cannot open the output file."<<std::endl;
  return false;
 }

  std::string line;
  unsigned int counter = 0;

  while (file_stream >> std::ws && std::getline(file_stream, line)){
   if(line == "<network>") counter++;
  }

    return counter;
}

/**
* It Returns the number of Layers saved inside the XML file
*
* @return it returns an unsigned int representing the number of Layers
**/
unsigned int Parser::ReturnNumberOfLayers()
{
  std::ifstream file_stream (mFilePath, std::ifstream::binary);
 if(!file_stream) {
  std::cerr<<"Error: Cannot open the output file."<<std::endl;
  return false;
 }

  std::string line;
  unsigned int counter = 0;

  while (file_stream >> std::ws && std::getline(file_stream, line)){
   if(line == "<layer>") counter++;
  }

    return counter;
}

/**
* It Returns the number of Datasets saved inside the XML file
*
* @return it returns an unsigned int representing the number of Datasets
**/
unsigned int Parser::ReturnNumberOfDatasets()
{
  std::ifstream file_stream (mFilePath, std::ifstream::binary);
 if(!file_stream) {
  std::cerr<<"Error: Cannot open the output file."<<std::endl;
  return false;
 }

  std::string line;
  unsigned int counter = 0;

  while (file_stream >> std::ws && std::getline(file_stream, line)){
   if(line == "<dataset>") counter++;
  }

    return counter;
}

/**
* It Returns the number of Neurons saved inside the XML file
*
* @return it returns an unsigned int representing the number of Neurons
**/
unsigned int Parser::ReturnNumberOfNeurons()
{
  std::ifstream file_stream (mFilePath, std::ifstream::binary);
 if(!file_stream) {
  std::cerr<<"Error: Cannot open the output file."<<std::endl;
  return false;
 }

  std::string line;
  unsigned int counter = 0;

  while (file_stream >> std::ws && std::getline(file_stream, line)){
   if(line == "<neuron>") counter++;
  }

    return counter;
}

std::string Parser::GetLastLine(std::string filePath)
{
  std::ifstream in (filePath, std::ifstream::binary);
  if (!in) return "";

    std::string line;
    while (in >> std::ws && std::getline(in, line)); // skip empty lines

    return line;
}

std::string Parser::GetFirstLine(std::string filePath)
{
  std::ifstream in (filePath, std::ifstream::binary);
  if (!in) return "";
  
  in.seekg(0, in.beg);

  std::string line;
  std::getline(in, line);
  return line;
}


}  //namespace


