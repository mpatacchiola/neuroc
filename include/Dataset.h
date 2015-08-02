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

/**
* \class Dataset
*
* \brief This class permits to create complex datasets and use them to feed the network.
*
* This class provides two containers for Input and Target datas. The Dataset can be created using the Parser directly
* from a CSV (Comma-Separeted Values) file or an XML file. During the backpropagation training it loads Input and Output values
* and use them to feed the Network.
*
* \author Massimiliano Patacchiola
*
* \version 1.0
*
* \date 2015
*
* \todo
*
* Contact:
*
*/
template<typename T>
class Dataset {

public:

    /**
    * Class constructor. It permits to create directly a multiple hidden layer network
    *
    * @param datasetDimension the dimension of the dataset
    */
    Dataset(unsigned int datasetDimension) {
        nInputsVector.reserve(datasetDimension);
        nTargetsVector.reserve(datasetDimension);
    }

    Dataset() {
    }

    ~Dataset() {
        nInputsVector.clear();
        nTargetsVector.clear();
    }

    /**
    * It permits to push back directly list of values without use a vector
    * ex: myDataset.PushBackInputAndTarget({0.4, 0.3, 0.2}, {0.01, 0.02});
    *
    * @param inputList the list of values to push in the input container
    * @param targetList the list of values to push in the target container
    **/
    bool PushBackInputAndTarget(std::initializer_list<T> inputList, std::initializer_list<T> targetList) {
        PushBackInput( inputList);
        PushBackTarget(targetList);
        return true;
    }

    /**
    * It permits to push back in the Dataset a new set of Input values
    *
    * @param dataToPush the vector of values to push inside the Dataset
    **/
    bool PushBackInputAndTarget(std::vector<T> inputDataToPush, std::vector<T> targetDataToPush) {
        nInputsVector.push_back(inputDataToPush);
        nTargetsVector.push_back(targetDataToPush);
        return true;
    }

    /**
    * It permits to push back in the Dataset a new set of Input values
    *
    * @param dataToPush the vector of values to push inside the Dataset
    **/
    bool PushBackInput(std::vector<T> dataToPush) {
        nInputsVector.push_back(dataToPush);
        return true;
    }

    /**
    * It permits to push back in the Dataset a new set of Input values
    *
    * @param dataToPush the vector of values to push inside the Dataset
    **/
    bool PushBackInput(std::initializer_list<T> inputList) {
        std::vector<T> temp_vector;

        for ( auto it=inputList.begin(); it!=inputList.end(); ++it) {
            temp_vector.push_back(*it);
        }

        nInputsVector.push_back(temp_vector);
        return true;
    }


    /**
    * It permits to extract a vector of inputs
    *
    * @param index of the input vector to return
    **/
    std::vector<T> GetInput(unsigned int index) {
        return nInputsVector[index];
    }

    /**
    * It permits to set a vector of input
    *
    * @param index of the input vector to set
    **/
    bool SetInput(unsigned int index, std::vector<T> data) {
        try {
            nInputsVector[index] = data;
            return true;
        } catch(...) {
            std::cerr << "Error: out of Range error." << '\n';
            return false;
        }
    }

    /**
    * It permits to extract a vector of inputs
    *
    * @param index of the input vector to return
    **/
    unsigned int ReturnNumberOfInputs() {
        return nInputsVector.size();
    }

    /**
    * It permits to push back in the Dataset a new set of Target values
    *
    * @param dataToPush the vector of values to push inside the Dataset
    **/
    bool PushBackTarget(std::vector<T> dataToPush) {
        nTargetsVector.push_back(dataToPush);
        return true;
    }

    /**
    * It permits to push back in the Dataset a new set of Target values
    *
    * @param dataToPush the vector of values to push inside the Dataset
    **/
    bool PushBackTarget(std::initializer_list<T> targetList) {
        std::vector<T> temp_vector;

        for ( auto it=targetList.begin(); it!=targetList.end(); ++it) {
            temp_vector.push_back(*it);
        }

        nTargetsVector.push_back(temp_vector);
        return true;
    }

    /**
    * It permits to extract a vector of targets
    *
    * @param index of the target vector to return
    **/
    std::vector<T> GetTarget(unsigned int index) {
        return nTargetsVector[index];
    }

    /**
    * It permits to set a vector of targets
    *
    * @param index of the target vector to set
    **/
    bool SetTarget(unsigned int index, T data) {
        try {
            nTargetsVector[index] = data;
            return true;
        } catch(...) {
            std::cerr << "Error: out of Range error." << '\n';
            return false;
        }
    }

    /**
    * It returns the number of targets inside the Dataset
    *
    * @return it returns an unsigned integer representing the number of targets
    **/
    unsigned int ReturnNumberOfTargets() {
        return nTargetsVector.size();
    }

    /**
    * It checks if there is the same number of input and target values
    *
    * @return it returns true if everything is all right, otherwise it returns false
    **/
    bool CheckIntegrity() {

        if(nInputsVector.empty()==true || nTargetsVector.empty()==true) return false;
        if(nInputsVector.size() != nTargetsVector.size()) return false;

        unsigned int input_size = nInputsVector[0].size();
        unsigned int target_size = nTargetsVector[0].size();

        for(unsigned int i=0; i<nInputsVector.size(); i++) {
            if (nInputsVector[i].size() != input_size) return false;
            if (nTargetsVector[i].size() != target_size) return false;
        }

        return true;
    }


void PrintInput(unsigned int index){
std::vector<T> temp_vector;
temp_vector = nInputsVector[index];
std::cout << "INPUT: ";
for(unsigned int i=0; i<temp_vector.size(); i++){
std::cout << temp_vector[i] << "; ";
}
std::cout << std::endl;
}

void PrintTarget(unsigned int index){
std::vector<T> temp_vector;
temp_vector = nTargetsVector[index];
std::cout << "TARGET: ";
for(unsigned int i=0; i<temp_vector.size(); i++){
std::cout << temp_vector[i] << "; ";
}
std::cout << std::endl;
}



    std::string ReturnStringXML() {
        std::ostringstream string_stream;
        string_stream << "<dataset>" << '\n';
        string_stream << "<id>" << this << "</id>"<<  '\n';
        string_stream << "<size>" << nInputsVector.size() << "</size>"<<  '\n';

        for(unsigned int i=0; i<nInputsVector.size(); i++) {

            std::vector<T> temp_vector_input(nInputsVector[i]);
            std::vector<T> temp_vector_target(nTargetsVector[i]);

            string_stream << "<input_values>";
            for(unsigned int j=0; j<temp_vector_input.size(); j++) {
                string_stream << temp_vector_input[j] << ";";
            }
            string_stream << "</input_values>" <<  '\n';

            string_stream << "<target_values>";
            for(unsigned int j=0; j<temp_vector_target.size(); j++) {
                string_stream << temp_vector_target[j] << ";";
            }
            string_stream << "</target_values>" <<  '\n';
        }
        string_stream << "</dataset>" << '\n';

        return string_stream.str();
    }


    std::string ReturnStringCSV() {
        std::ostringstream string_stream;
        string_stream << nInputsVector.size() << "," << nTargetsVector.size() <<   '\n';
        string_stream << '\n';

        for(unsigned int i=0; i<nInputsVector.size(); i++) {

            std::vector<T> temp_vector_input(nInputsVector[i]);
            std::vector<T> temp_vector_target(nTargetsVector[i]);

            for(unsigned int j=0; j<temp_vector_input.size(); j++) {
                string_stream << temp_vector_input[j] << ",";
            }

            for(unsigned int j=0; j<temp_vector_target.size(); j++) {
                string_stream << temp_vector_target[j] << ",";
            }

            string_stream << '\n';
        }


        return string_stream.str();
    }

private:

    std::vector<std::vector<T>> nInputsVector;
    std::vector<std::vector<T>> nTargetsVector;



};


#endif // DATASET_H
