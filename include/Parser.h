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

    inline bool SetPath(std::string filePath) {
        mFilePath=filePath;
        return true;
    }

    inline std::string GetPath() {
        return mFilePath;
    }


    bool AddNote(std::string note, std::string title = "") {

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

   }

    template<typename T>
    bool SaveNetwork(const Network<T>& rNetwork) {

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
	file_stream << "<user_value>" << rNetwork.GetUserValue() <<"</user_value>" << '\n';	
	for(unsigned int lay=0; lay<rNetwork.Size(); lay++){

		file_stream << "<layer>" << '\n';
		for(unsigned int neu=0; neu<rNetwork[lay].Size(); neu++){
			file_stream << "<neuron>" << '\n';
			file_stream << "<value>" << rNetwork[lay][neu].GetValue() <<"</value>" << '\n';
			file_stream << "<error>" << rNetwork[lay][neu].GetError() <<"</error>" << '\n';
			file_stream << "<bias>" << rNetwork[lay][neu].GetBias() <<"</bias>" << '\n';
		
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

    template<typename T>
    bool SaveLayer(const Layer<T>& rLayer) {

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
		for(unsigned int neu=0; neu<rLayer.Size(); neu++){
			file_stream << "<neuron>" << '\n';
			file_stream << "<value>" << rLayer[neu].GetValue() <<"</value>" << '\n';
			file_stream << "<error>" << rLayer[neu].GetError() <<"</error>" << '\n';
			file_stream << "<bias>" << rLayer[neu].GetBias() <<"</bias>" << '\n';
		
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

    template<typename T>
    bool SaveNeuron(const Neuron<T>& rNeuron) {

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
        
	file_stream << "<connections>";
	for(unsigned int con=0; con<rNeuron.Size(); con++){
	 file_stream << rNeuron[con] << ";";
	}
	file_stream <<"</connections>" << '\n';
	file_stream << "</neuron>" << '\n';

        file_stream.close();
        return true;
    }

    template<typename T>
    bool FillNeuron(Neuron<T>* pNeuron) {

    }

    template<typename T>
    bool SaveDataset(Dataset<T>& rDataset) {

        if(mInitialised == false) {
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
    bool SaveDatasetAsCSV(Dataset<T>& rDataset, std::string filePath) {

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


