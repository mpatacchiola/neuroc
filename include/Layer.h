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

#ifndef LAYER_H
#define LAYER_H

#include "Neuron.h"
#include <iostream> //printing functions
#include <memory>  // shared_ptr
#include <cassert>
#include <fstream> //save in XML
#include <sstream>

/**
* Copyright 2015 Massimiliano Patacchiola
*
* \class Layer
*
* \brief This class is the middle level of the neural network library. It is a container for neurons. It allows the use of different floating points.
*
* \author Massimiliano Patacchiola
*
* \version 1.0
*
* \date 2015
*
*
* Contact:
*
*/
template<typename T>
class Layer {

public:


	/**
	* Copy constructor
	*
	* @param rLayer reference to an existing Layer
	*/
	Layer(const Layer<T> &rLayer)
	{
	mNeuronsVector = rLayer.mNeuronsVector;
	}

    /**
    * It creates a new Layer containing similar neurons.
    *
    * @param neuronPrototype it is a prototype and will be used to create copies inside the layer.
    * @param dimension the size of the layer
    *
    */
    Layer(Neuron<T> neuronPrototype, unsigned int dimension) {
        static_assert(std::is_floating_point<T>::value,"Error: the Layer class can only be instantiated with floating point types");
	
	mNeuronsVector.reserve(dimension);
	for(unsigned int i=0; i<dimension; i++){
	  Neuron<T> neuron_copy = neuronPrototype;
	  mNeuronsVector.push_back(neuron_copy);
	} 
    }

    /**
    * It creates a new Layer.
    *
    * @param  neuronList a list of existing neurons
    *
    */
    Layer(std::initializer_list<Neuron<T>> neuronList) {
        static_assert(std::is_floating_point<T>::value,"Error: the Layer class can only be instantiated with floating point types");
	mNeuronsVector.reserve(neuronList.size());
	for(auto it=neuronList.begin(); it!=neuronList.end(); it++){
	  mNeuronsVector.push_back(*it);
	} 
    }

	/**
	* Overload of the assignment operator
	*
	* @param rLayer reference to an existing Layer
	*/
	Layer<T> operator=(const Layer<T> &rLayer)
	{  		
    		if (this == &rLayer) return *this;  // check for self-assignment 
		mNeuronsVector = rLayer.mNeuronsVector;
		return *this;
	}



    ~Layer() {
	mNeuronsVector.clear();
    }

    /**
    * Operator overload [] it is used to return the smart pointer reference to the neuron stored inside the layer
    * It is possible to access the methods of the single neuron using the deferencing operator ->
    * Example: input_layer->Compute();  // It calls the Compute() method of the neuron returned
    * @param index the number of the element stored inside the layer
    * @return it returns a const reference to the neuron
    **/
    const Neuron<T>& operator[](const unsigned int index) const {
        if (index >= mNeuronsVector.size()) throw std::domain_error("Error: Out of Range index.");
        return mNeuronsVector[index];
    }

    /**
     * It gives the size of the connections container
     *
     * @return it returns the number of connection of the neuron
    */
    const unsigned int Size() const{
	return mNeuronsVector.size();
    }

    /**
    * It returns a reference to the vector that contain the neurons
    * 
    * @return a const reference to the vector
    */
    const std::vector<Neuron<T>>& ReturReferenceToNeuronsVector() const {
	return mNeuronsVector;
   }

    /**
    * Compute all the neurons of the layer and return a vector containing the values of these neurons
    *
    * @return it returns the vector containing the double, in case of problems it returns an empty vector and print an error
    **/
    std::vector<T> Compute(std::vector<T> inputVector) {
        std::vector<T> output_vector;
        output_vector.reserve(mNeuronsVector.size());

        for (unsigned int i = 0; i < mNeuronsVector.size(); i++){
	 output_vector.push_back(mNeuronsVector[i].Compute(inputVector));
	}

        return output_vector;
    }


    /**
    * Randomize all the connections of the neurons inside the layer
    * It is possible to specify a minimum and maximum range for the random generator.
    *
    * @param initFunction
    * @return bool it returns true if everything is all right, otherwise false.
    */
    void RandomizeConnectionMatrix(std::function<T(T)> initFunction) {
            for(unsigned int i = 0; i < mNeuronsVector.size(); i++){
		mNeuronsVector[i].RandomizeConnectionVector(initFunction);
		}
    }

    /**
    * Get the values of all the neurons inside the layer
    *
    * @param inputValues vector of doubles of the same size of the layer. Every double is given as input to the neurons inside the layer.
    * @return it returns true if it is all right, otherwise false
    **/
    const std::vector<T>& GetValueVector() const{

        std::vector<T> outputVector;
        outputVector.reserve(mNeuronsVector.size());

        for(unsigned int i = 0; i < mNeuronsVector.size(); i++)
            outputVector.push_back(mNeuronsVector[i].GetValue());

        return outputVector;
    }

    /**
    * Set the values of all the bias inside the layer
    *
    * @param biasVector vector of values with the same size of the layer.
    * @return it returns true if it is all right, otherwise false
    **/
    bool SetBiasVector(std::vector<T> biasVector) {

            if(biasVector.size() != mNeuronsVector.size()) return false;

            for(unsigned int i = 0; i < biasVector.size(); i++)
                mNeuronsVector[i].SetBias(biasVector[i]);

            return true;
    }

    /**
    * Set the values of all the neurons inside the layer
    *
    * @param inputValues vector of doubles of the same size of the layer. Every double is given as input to the neurons inside the layer.
    * @return it returns true if it is all right, otherwise false
    **/
    bool SetValueVector(std::vector<T> valueVector) {

            if(valueVector.size() != mNeuronsVector.size()) return false;

            for(unsigned int i = 0; i < mNeuronsVector.size(); i++)
                mNeuronsVector[i].SetValue(valueVector[i]);

            return true;
    }



    /**
    * Set the values of all the Error associated with the neurons inside the layer
    *
    * @param value vector of the same size of the layer.
    * @return it returns true if it is all right, otherwise false
    **/
    bool SetErrorVector(std::vector<T> errorVector) {
            if(errorVector.size() != mNeuronsVector.size()) return false;

            for(unsigned int i = 0; i < errorVector.size(); i++)
                mNeuronsVector[i].SetError(errorVector[i]);

            return true;
    }


    /**
    * It returns the number of neuron contained inside the layer
    *
    * @return it returns the number of neurons
    **/
    inline unsigned int ReturnNumberOfNeurons() {
        return mNeuronsVector.size();
    }


    /**
    * Returning a vector of vectors Matrix containing neurons connections
    * The vector start with the first incoming connection of the first neuron
    * and it ends with the last incoming connection of the last neuron
    * If the Layer has a Bias Unit then the first connection of the neurons is the Bias incoming connection
    * @return it returns a vector of double or float
    **/
    std::vector< std::vector<T> > GetConnectionMatrix() {

        std::vector<std::vector<T>> output_vector;

        //for (unsigned int i=0; i<mNeuronsVector.size(); i++) {
           // std::vector<T> vector_copy(mNeuronsVector[i]->GetVectorOfConnections());
           //unsigned int neuron_vector_size = vector_copy.size();

            //for (unsigned int j=0; j<neuron_vector_size; j++) {
            //    output_vector.push_back( vector_copy[j] );
           // }
        //}
        return output_vector;
    }




    /**
    * Print information about all the neurons contained inside the Layer
    *
    **/
    void Print() {
            for (unsigned int i = 0; i < mNeuronsVector.size(); i++) {
                std::cout << "neuron[" << i << "]" << '\n';
                mNeuronsVector[i].Print();
            }
    }



private:
    std::vector<Neuron<T>> mNeuronsVector; /**< vector which contains the neurons of the layer */


};


#endif // LAYER_H
