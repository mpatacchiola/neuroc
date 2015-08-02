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
 * 
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

	/**
	* Copy constructor
	*
	* @param rNeuron reference to an existing Neuron
	*/
	Neuron(const Neuron<T> &rNeuron)
	{
		mConnectionsVector = rNeuron.mConnectionsVector;
		mValue = rNeuron.mValue;
		mError = rNeuron.mError;
		mBias = rNeuron.mBias;
		WeightFunction = rNeuron.WeightFunction;
		JoinFunction = rNeuron.JoinFunction;
		TransferFunction = rNeuron.TransferFunction;
	}


	/**
	* It creates an object of type Neuron
	*
	* @param biasWeight it is the value of the weight of the bias neuron
	*/
 	Neuron(const std::vector<T>& connectionsVector, std::function<T(std::vector<T>, std::vector<T>)> weightFunction, std::function<T(T, T)> joinFunction, std::function<T(T)> transferFunction, T biasWeight=0)
   	{
		// test it on: http://webcompiler.cloudapp.net/
		// probably it needs #include <type_traits> to use the function is_floating_point		
		static_assert(std::is_floating_point<T>::value,
		              "Neuron class Neuron can only be instantiated with floating point types"); // Compiler error when the class is instantiated with something different from double or float
		mBias = biasWeight;
		WeightFunction = weightFunction;
		JoinFunction = joinFunction;
		TransferFunction = transferFunction;

		mConnectionsVector.reserve(connectionsVector.size()); //ATTENTION: it is necessary to initialise the connectionVector here
		mConnectionsVector = connectionsVector;
    	}

	/**
	* Overload of the assignment operator
	*
	* @param rNeuron reference to an existing Neuron
	*/
	Neuron<T> operator=(const Neuron<T> &rNeuron)
	{
    		
    		if (this == &rNeuron) return *this;  // check for self-assignment 

		mConnectionsVector = rNeuron.mConnectionsVector;
		mValue = rNeuron.mValue;
		mError = rNeuron.mError;
		mBias = rNeuron.mBias;
		WeightFunction = rNeuron.WeightFunction;
		JoinFunction = rNeuron.JoinFunction;
		TransferFunction = rNeuron.TransferFunction;

		return *this;
	}

    /**
    * Operator overload [] it is used to return the connection weight stored inside the neuron
    * @param index the number of the element stored inside the layer
    * @return it returns a reference to the weight
    **/
    const T& operator[](const unsigned int index) const {
        if (index >= mConnectionsVector.size()) throw std::domain_error("Error: Out of Range index.");
        return mConnectionsVector[index];
    }

    /**
     * It gives the size of the connections container
     *
     * @return it returns the number of connection of the neuron
    */
    const unsigned int Size() const{
	return mConnectionsVector.size();
    }


    /**
     * It gives the value of the Neuron after one computation
     * after that the internal value of the neuron is changed
     *
     * @return it returns the value of the neuron after the computation
    */
    T Compute(std::vector<T> inputVector) {

	//1- Applying Weight Function
	T weight_function_output = WeightFunction(inputVector, mConnectionsVector);
	#ifdef DEBUG 
	std::cout << "weight_function_output: " << weight_function_output << std::endl;
	#endif

	//2- Applying the Join Function
	T join_function_output = JoinFunction(weight_function_output, mBias);
	#ifdef DEBUG 
	std::cout << "join_function_output: " << join_function_output << std::endl;
	#endif

	//3- Applying the Transfer Function
	T neuron_output = TransferFunction(join_function_output);
	#ifdef DEBUG 
	std::cout << "neuron_output: " << neuron_output << std::endl;
	#endif

	//4- Returning the result
	mValue = neuron_output;
	return neuron_output;
    }

    /**
    * Randomize all the connection of the neuron using a Init Function.
    * The function to use must take a value as input and return a value as output.
    * The returned value will be assigned to the weight.
    *
    * @param initFunction this function is used for modifying all the weights of the neuron
    */
    void RandomizeConnectionVector(std::function<T(T)> initFunction) {

	for(auto it=mConnectionsVector.begin(); it!=mConnectionsVector.end(); it++){
	*it = initFunction(*it);
	}

	mBias = initFunction(mBias);
    }


    /**
    * Returning a vector containing the values of the neuron connections
    * The vector start with the first incoming connection and it ends with the last incoming connection
    * If the Neuron has a Bias Unit then the first connection of the neuron is the Bias incoming connection
    * @return it returns a vector of values
    **/
    const std::vector<T>& GetConnectionVector() const {
	return mConnectionsVector;
    }

    /**
    * It permits to set the vector of the incoming connections to the neuron
    *
    * @param connectionsVector a vector of floating point numbers
    **/
    bool SetConnectionVector(const std::vector<T>& connectionVector) {
	mConnectionsVector.clear;
	mConnectionsVector = connectionVector;
    }


    /**
    * Print on terminal informations about the neuron.
    *
    */
    void Print() {
        std::cout << "Value ..... " << mValue << '\n';
        std::cout << "Error ..... " << mError << '\n';
        std::cout << "Bias ..... " << mBias << '\n';
        std::cout << "Connections ..... " << mConnectionsVector.size() << '\n';

        for (unsigned i = 0; i < mConnectionsVector.size(); i++) {
           std::cout << "Connection[" << i << "] ..... " << mConnectionsVector[i] << '\n';
        }

        std::cout << std::endl;
    }


    /**
    * Set the value of the neuron
    *
    * @param value the value to set, it is used for input neurons
    */
    void SetValue(T value) {
        mValue = value; //it set the current value
    }

    /**
    * Get the value of the neuron
    *
    * @return it returns the current value of the neuron
    **/
    const T GetValue() const {
        return mValue;
    }

    /**
    * Set the value of the neuron
    *
    * @param value the value to set, it is used for input neurons
    */
    void SetError(T value) {
        mError = value;
    }

    /**
    * Get the value of the neuron
    *
    * @return it returns the current value of the neuron
    **/
    const T GetError() const {
        return mError;
    }

    /**
    * Set the value of the bias
    *
    * @param value the value to set
    */
    void SetBias(T value) {
        mBias = value; //it set the current value
    }

    /**
    * Get the value of the Bias Connection
    *
    * @return it returns the current value of the Bias Connection
    **/
    const T GetBias() const{
        return mBias;
    }



private:


    T mValue = 0;  //value obtained after the computation 
    T mError = 0;  //error obtained after the error backpropagation 
    T mBias = 0;   //value of the bias connection

    std::vector<T> mConnectionsVector;  //container of the connections values

    std::function<T(std::vector<T>, std::vector<T>)> WeightFunction;
    std::function<T(T, T)> JoinFunction;
    std::function<T(T)> TransferFunction;


};  // Class Neuron




#endif // NEURON_H
