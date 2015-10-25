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

namespace neuroc{

/**
* \class Parser
*
* \brief This class permits to save networks in XML files
*
*
*/

class Parser {

public:

 Parser();
 ~Parser();

 bool InitialiseXML(std::string filePath);
 bool FinaliseXML();

 bool SetPath(std::string filePath) ;
 std::string GetPath();

 bool AddNote(std::string note, std::string title = "");

 bool SaveNetwork(Network& rNetwork) ;
 bool SaveLayer( Layer& rLayer);
 bool SaveNeuron( Neuron& rNeuron) ;

 bool FillNeuron(Neuron* pNeuron);


 bool SaveDataset(Dataset& rDataset);
 bool SaveDatasetAsCSV(Dataset& rDataset, std::string filePath);

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


} //namespace

#endif // PARSER_H


