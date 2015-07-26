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

#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <memory>  // shared_ptr
#include <cmath>  //  "exp" function
#include <math.h>  //  "isnan" function
#include <string>
#include <random>
#include <iostream>  // printing functions
#include <fstream> //save in XML
#include <sstream>

/**
 * Copyright 2015 Massimiliano Patacchiola
 *
 * \class Neuron
 *
 * \brief This is the lowest class and it represents the Neuron object
 *
 * \author Massimiliano Patacchiola
 *
 * \version 1.0
 *
 * \date 2015
 *
 * Contact:
 *
 */
template<typename T>
class Neuron {
public:
    enum activationFunction {SIGMOID, TANH};

    Neuron() {
        // test it on: http://webcompiler.cloudapp.net/
        // probably it needs #include <type_traits> to use the function is_floating_point
        // Compiler error when the class is instantiated with something different from double or float
        static_assert(std::is_floating_point<T>::value,
                      "Neuron class Neuron can only be instantiated with floating point types");
    }

    ~Neuron() {
        // dtor
        // NOTHING TO DO HERE
        // THE NEURON IS DESTROYED AUTOMATICALLY
        // WHEN THE LAST SMART POINTER GOES OUT OF SCOPE
    }


    /**
     * Sum of the incoming connections times the incoming neuron value,
     * after that the internal value of the neuron is changed
     *
     * @return it returns the value of the neuron after the computation
    */
    T Compute() {
        mValuePrevious = mValue;
        mValue = 0;  // value reset

        for (unsigned int i = 0; i < mIncomingVector.size(); i++) {
            if(auto sp_Neuron_Reference = mIncomingVector[i].wpNeuronReference.lock()) { //this neuron still exist, calculate
                mValue += (*mIncomingVector[i].spWeight) * (sp_Neuron_Reference->mValue);
            } else { //Oops, that Neuron has already been destroyed
                mIncomingVector[i].wpNeuronReference.reset();
                mIncomingVector.erase(mIncomingVector.begin() + i); //delete the position of the destroyed neuron
            }
        }

        if (functionToUse == SIGMOID) {
            return mValue = Sigmoid(mValue);  // Sigmoid Function
        } else if (functionToUse == TANH) {
            return mValue = tanh(mValue);  // tanh Function
        } else {
            return 0;
        }
    }

    /**
     * Sum of the incoming connections times the incoming neuron value,
     * after that the internal value of the neuron is changed
     *
     * @param functionToUse activation function to use for computating
     * @return it returns the value of the neuron after the computation
    */
    T Compute(activationFunction functionToUse) {
        mValuePrevious = mValue;
        mValue = 0;  // value reset

        for (unsigned int i = 0; i < mIncomingVector.size(); i++) {
            if(auto sp_Neuron_Reference = mIncomingVector[i].wpNeuronReference.lock()) { //this neuron still exist, calculate
                mValue += (*mIncomingVector[i].spWeight) * (sp_Neuron_Reference->mValue);
            } else { //Oops, that Neuron has already been destroyed
                mIncomingVector[i].wpNeuronReference.reset();
                mIncomingVector.erase(mIncomingVector.begin() + i); //delete the position of the destroyed neuron
            }
        }

        switch (functionToUse) {
        case SIGMOID:
            return mValue = ( 1 / (1 + exp(-mValue)) );  // Sigmoid Function
            break;

        case TANH:
            return mValue = tanh(mValue);  // Hyberbolic Tangent Function
            break;

        default:
            return mValue = ( 1 / (1 + exp(-mValue)) );  // Sigmoid Function
            break;
        }
    }


    /**
    * Set the activation function used for the computation.
    * The default activation function is SIGMOID.
    * @param functionToUse this is the function to use, it is possible to choose these values: SIGMOID, TANH
    * @return it returns true if everything is all right, otherwise false.
    */
    inline bool SetActivationFunction(activationFunction functionToUse) {
        functionToUse = functionToUse;
        return true;
    }

    /**
    * Get the activation function used for computation.
    *
    * @return it returns the activation function used: SIGMOID, TANH
    **/
    inline activationFunction GetActivationFunction() {
        return functionToUse;
    }


    /**
    * Randomize all the incoming connection to the neuron.
    * It is possible to specify a minimum and maximum range for the random generator.
    *
    * @param minRange the minimum range for the random generator
    * @param maxRange the maximum range for the random generator
    * @return bool it returns true if everything is all right, otherwise false.
    */
    bool RandomizeIncomingConnections(T minRange, T maxRange) {
        try {
            if (minRange >= maxRange) {
                std::cerr << "Neuron, the minimum value is grater than the maximum value the connections" << std::endl;
                return false;
            }

            if (mIncomingVector.empty() == true) {
//std::cerr << "Neuron, there are not incoming connections" << std::endl;
                return false;
            }

            std::random_device randomDevice;
            std::mt19937 generator(randomDevice());
            std::uniform_real_distribution<> distribution(minRange, maxRange);  // Generate a random weight

            for (unsigned int i = 0; i < mIncomingVector.size(); i++)
                *mIncomingVector[i].spWeight = distribution(generator);

            return true;
        } catch(...) {
            std::cerr << "Neuron error randomizing the connections" << std::endl;
            return false;
        }
    }

    /**
    * Set the value of an Incoming Connection.
    *
    * @param index unsiged int which identify the connection into the vector
    * @param value value to write
    * @return bool it returns true if it is all right, otherwise false
    */
    bool SetConnectionValue(unsigned int connectionIndex, T value) {
        if(connectionIndex >= mIncomingVector.size()) return false;
        *mIncomingVector[connectionIndex].spWeight=value;
        return true;
    }

    /**
    * Get the value of an Incoming Connection.
    *
    * @param index unsiged int which identify the connection into the vector
    * @param value value to write
    * @return bool it returns true if it is all right, otherwise false
    */
    T GetConnectionValue(unsigned int connectionIndex) {
        if(connectionIndex >= mIncomingVector.size()) return NULL;
        return *mIncomingVector[connectionIndex].spWeight;
    }

    /**
    * Set the value of an Incoming Connection.
    *
    * @param spNeuron shared_ptr which identify the incoming neuron associated with the connection
    * @param value value to write
    * @return bool it returns true if it is all right, otherwise false
    */
    bool SetConnectionFromNeuron(std::shared_ptr< Neuron<T> > spNeuron, T value) {
        for (unsigned int i=0; i < mIncomingVector.size(); i++)
            if(mIncomingVector[i].wpNeuronReference ==  spNeuron) {
                *mIncomingVector[i].spWeight=value;
                return true;
            }

        return false;
    }

    /**
    * Get the value of an Incoming Connection.
    *
    * @param spNeuron shared_ptr which identify the incoming neuron associated with the connection
    * @return it returns the value of the connection
    */
    T GetConnectionFromNeuron(std::shared_ptr< Neuron<T> > spNeuron) {
        for (unsigned int i = 0; i < mIncomingVector.size(); i++)
            if(mIncomingVector[i].wpNeuronReference.lock() ==  spNeuron) {
                return mIncomingVector[i].spWeight;
            }
        return 0;
    }

    /**
    * Returning a vector containing smart-pointers to neuron connections
    * The vector start with the first incoming connection and it ends with the last incoming connection
    * If the Neuron has a Bias Unit then the first connection of the neuron is the Bias incoming connection
    * @return it returns a vector of smart-pointers to double or float
    **/
    std::vector<std::shared_ptr<T>> GetVectorOfPointersToConnections() {
        std::vector<std::shared_ptr<T>> output_vector;

        for (unsigned int i = 0; i < mIncomingVector.size(); i++) {
            std::shared_ptr<T> sp_connection_value = mIncomingVector[i].spWeight;
            output_vector.push_back(sp_connection_value);
        }
        return output_vector;
    }

    /**
    * Returning a vector containing the values of the neuron connections
    * The vector start with the first incoming connection and it ends with the last incoming connection
    * If the Neuron has a Bias Unit then the first connection of the neuron is the Bias incoming connection
    * @return it returns a vector of values
    **/
    std::vector<T> GetVectorOfConnections() {
        std::vector<T> output_vector;

        for (unsigned int i = 0; i < mIncomingVector.size(); i++) {
            output_vector.push_back(*mIncomingVector[i].spWeight);
        }
        return output_vector;
    }

    /**
    * It permits to set the vector of the incoming connections to the neuron
    *
    * @param connectionsVector a vector of shared pointer to floating point numbers
    **/
    bool SetVectorOfPointersToConnections(std::vector<std::shared_ptr<T>>& connectionsVector) {
        if(connectionsVector.size() != mIncomingVector.size()) return false;

        for (unsigned int i = 0; i < mIncomingVector.size(); i++) {
            mIncomingVector[i].spWeight = connectionsVector[i];
        }
        return true;
    }

    /**
    * It permits to set the vector of the incoming connections to the neuron
    *
    * @param connectionsVector a vector of shared pointer to floating point numbers
    **/
    bool SetVectorOfConnections(std::vector<T>& connectionsVector) {
        if(connectionsVector.size() != mIncomingVector.size()) return false;

        for (unsigned int i = 0; i < mIncomingVector.size(); i++) {
            mIncomingVector[i].spWeight = std::make_shared<T>(connectionsVector[i]);
        }
        return true;
    }


    /**
    * Print on terminal informations about the neuron.
    *
    */
    void Print() {
        std::cout << "value ..... " << mValue << std::endl;
        std::cout << "error ..... " << mError << std::endl;
        std::cout << "number of incoming connections ..... " << mIncomingVector.size() << std::endl;

        for (unsigned i = 0; i < mIncomingVector.size(); i++) {
            std::cout << "incoming neuron[" << i << "] ..... " << mIncomingVector[i].wpNeuronReference.lock()->mValue << std::endl;
            std::cout << "incoming connection[" << i << "] ..... " << *mIncomingVector[i].spWeight << std::endl;
        }

        std::cout << std::endl;
    }

    /**
    * Print on terminal informations about the neuron.
    *
    * @param tag string which can help to identify the neuron
    */
    void Print(std::string tag, bool printConnections) {
        std::cout << "tag ..... " << tag << std::endl;
        std::cout << "value ..... " << mValue << std::endl;
        std::cout << "error ..... " << mError << std::endl;
        std::cout << "number of incoming connections ..... " << mIncomingVector.size() << std::endl;

        if (printConnections == true) {
            for (unsigned i = 0; i < mIncomingVector.size(); i++) {
                std::cout << "incoming neuron[" << i << "] ..... " << mIncomingVector[i].wpNeuronReference.lock()->mValue << std::endl;
                std::cout << "incoming connection[" << i << "] ..... " << *mIncomingVector[i].spWeight << std::endl;
            }
        }
        std::cout << std::endl;
    }

    /**
    * Set the value of the neuron
    *
    * @param value the value to set, it is used for input neurons
    */
    inline void SetNeuronValue(T value) {
        mValuePrevious = mValue; //it saves the previous value
        mValue = value; //it set the current value
    }

    /**
    * Get the value of the neuron
    *
    * @return it returns the current value of the neuron
    **/
    inline T GetNeuronValue() {
        return mValue;
    }

    /**
    * Set the value of the neuron
    *
    * @param value the value to set, it is used for input neurons
    */
    inline void SetNeuronError(T value) {
        mError = value;
    }

    /**
    * Get the value of the neuron
    *
    * @return it returns the current value of the neuron
    **/
    inline T GetNeuronError() {
        return mError;
    }


    /**
    * Add a connection from the neuron specified.
    * If the specified neuron is not present return false
    *
    * @param neuronToConnect pointer to the Neuron to add
    * @return true if the operation succeeded, false otherwise
    */
    bool AddConnectionFromNeuron(std::shared_ptr< Neuron<T> > spNeuron) {

        if(spNeuron == false) {
            std::cerr << "Neuron error the spNeuron pointer is empty" << std::endl;
            return false;
        }

        for (unsigned i = 0; i < mIncomingVector.size(); i++) {
            if (mIncomingVector[i].wpNeuronReference.lock() == spNeuron) {
                std::cerr << "Neuron error there is already a connection between these neurons." << std::endl;
                return false;
            }
        }

// Add a random weight value
        std::random_device rand_dev;
        std::mt19937 rand_gen(rand_dev());
        std::uniform_real_distribution<> rand_dist(-0.1, 0.1);  // Generate a random weight

        T connection_value = rand_dist(rand_gen);     // declare a constant  to new T
        std::shared_ptr<T> sp_connection_value = std::make_shared<T>(connection_value);

        mConnectionStruct temp_connection;
        temp_connection.wpNeuronReference = spNeuron;
        temp_connection.spWeight = sp_connection_value;
        mIncomingVector.push_back(temp_connection);

        return true;
    }


    /**
    * Remove an incoming connection from the neuron specified.
    * If the specified neuron is not present return false
    *
    * @param neuronToRemove pointer to the Neuron to remove
    * @return true if the operation succeeded, false otherwise
    */
    bool RemoveConnectionFromNeuron(std::shared_ptr< Neuron<T> > spNeuron, std::shared_ptr< Neuron<T> > spThisNeuron) {
        try {
            for (unsigned i = 0; i < mIncomingVector.size(); i++) {
                if (mIncomingVector[i].wpNeuronReference == spNeuron) {
// Remove the connection internally
                    mIncomingVector.erase(mIncomingVector.begin(), mIncomingVector.begin()+i);
                    return true;
                }
            }

            return false;
        } catch(...) {
            std::cerr << "Neuron error removing incoming connection" << std::endl;
            return false;
        }
    }

    /**
    * Get the total number of the incoming connections.
    *
    * @return unisgned int which represents the number of connections
    */
    unsigned int ReturnNumberOfIncomingConnections() {
        return mIncomingVector.size();
    }

    /**
    * It saves the layer as an XML file
    * @param path complete path, included the file name
    * @return it returns true in case of succes otherwise it returns false
    **/
    bool SaveAsXML(std::string path) {
        std::ofstream file_stream(path, std::fstream::app);
        std::ostringstream oss;
        if(!file_stream) {
            std::cerr<<"Cannot open the output file."<< std::endl;
            return false;
        }

        file_stream << "<neuron>" << std::endl;
        file_stream << "<id>" << this <<"</id>" << '\n';
        if(functionToUse == SIGMOID) file_stream << "    "  << "<activation_function>" << "SIGMOID" <<"</activation_function>" << '\n';
        if(functionToUse == TANH) file_stream << "    "  << "<activation_function>" << "TANH" <<"</activation_function>" << '\n';
        file_stream << "<value>" << mValue <<"</value>" << '\n';
        file_stream << "<previous_value>" << mValuePrevious <<"</previous_value>" << '\n';
        file_stream << "<error>" << mError <<"</error>" << '\n';
        file_stream << "<previous_error>" << mErrorPrevious <<"</previous_error>" << '\n';
        file_stream << "<connections_number>" << mIncomingVector.size() <<"</connections_number>" << '\n';
        file_stream  << "<connections_vector>";

        for (unsigned i = 0; i < mIncomingVector.size(); i++) {
            file_stream << *mIncomingVector[i].spWeight << ";";
        }
        file_stream<<"</connections_vector>" << '\n';

        file_stream << "<references_vector>";
        for (unsigned i = 0; i < mIncomingVector.size(); i++) {
            file_stream << mIncomingVector[i].wpNeuronReference.lock() << ";";
        }
        file_stream << "</references_vector>" << '\n';

        file_stream << "</neuron>" << std::endl;

        file_stream.close();

        return true;
    }

    /**
    * It saves the layer as an XML file
    * @param path complete path, included the file name
    * @return it returns true in case of succes otherwise it returns false
    **/
    std::string ReturnStringXML() {

        std::ostringstream string_stream;

        string_stream << "<neuron>" << std::endl;
        string_stream << "<id>" << this <<"</id>" << '\n';
        if(functionToUse == SIGMOID) string_stream << "<activation_function>" << "SIGMOID" <<"</activation_function>" << '\n';
        if(functionToUse == TANH) string_stream << "<activation_function>" << "TANH" <<"</activation_function>" << '\n';
        string_stream << "<value>" << mValue <<"</value>" << '\n';
        string_stream << "<previous_value>" << mValuePrevious <<"</previous_value>" << '\n';
        string_stream << "<error>" << mError <<"</error>" << '\n';
        string_stream << "<previous_error>" << mErrorPrevious <<"</previous_error>" << '\n';
        string_stream << "<connections_number>" << mIncomingVector.size() <<"</connections_number>" << '\n';
        string_stream << "<connections_vector>";

        for (unsigned i = 0; i < mIncomingVector.size(); i++) {
            string_stream << *mIncomingVector[i].spWeight << ";";
        }
        string_stream <<"</connections_vector>" << '\n';

        string_stream << "<references_vector>";
        for (unsigned i = 0; i < mIncomingVector.size(); i++) {
            string_stream << mIncomingVector[i].wpNeuronReference.lock() << ";";
        }
        string_stream << "</references_vector>" << '\n';

        string_stream << "</neuron>" << std::endl;


        return string_stream.str();
    }

private:
    /** This struct contain two std::shared_ptr, one to the neuron and another to the weight */
    struct mConnectionStruct {
        std::weak_ptr< Neuron<T> > wpNeuronReference;
        std::shared_ptr< T > spWeight;
    };

    T mValue = 0;  /**< value obtained after the computation */
    T mValuePrevious = 0;  /**< value obtained after the computation at n-1 */
    T mError = 0;  /**< error obtained after the error backpropagation */
    T mErrorPrevious = 0; /**< error obtained after the error backpropagation at n-1 */
    activationFunction functionToUse = SIGMOID;
    std::vector<mConnectionStruct> mIncomingVector;

    inline T Sigmoid(T input) {
        T result =  ( 1 / (1 + exp(-input)) );
        if( isnan(result) ) return 0; //protection against large negative number
        return result;
    }

    inline T SigmoidDerivative(T input) {
        return (1 / (1 + exp(-input))) * (1 - (1 / (1 + exp(-input))));
    }
    inline T TanhDerivative(T input) {
        return (1-tanh(input)) * (1+tanh(input));
    }
};  // Class Neuron




#endif // NEURON_H
