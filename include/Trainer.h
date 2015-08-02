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

#ifndef TRAINER_H
#define TRAINER_H

#include<memory>
#include<random>
#include <algorithm>    // std::sort
#include <functional>   // std::greater

#include"Network.h"
#include"Dataset.h"
#include"Parser.h"
//#include"Functions.h"

/**
* \class Trainer
*
* \brief This class permits to train a single network or group of networks.
*
* Specifing a Network and a Dataset it is possible to train the network using a specific train algorithm.
*
*
*
* \author Massimiliano Patacchiola
*
* \version 1.0
*
* \date 2015
*
* \todo TWEANN (Topology & Weight Evolving Artificial Neural Network)
*
* Contact:
*
*/
template<typename T>
class Trainer {

public:

    enum Algorithm {BACK_PROP, GA_SUPERVISED};

    Trainer(Network<T> networkToTrain, Dataset<T> dataset) {
        spNetwork = std::make_shared<Network<T>>(networkToTrain);
        spDataset = std::make_shared<Dataset<T>>(dataset);

    }

    ~Trainer() {

    }

/**
 * It tests the network using the Dataset.
 *
 * @return It returns a value that represents the network performance
*/
void TestNetwork(Network<T>& networkToTest, Dataset<T>& rDataset){

for(unsigned int i=0; i<rDataset.ReturnNumberOfInputs(); i++){

rDataset.PrintInput(i);
rDataset.PrintTarget(i);

networkToTest.Compute(rDataset.GetInput(i));
networkToTest.PrintOutputs();

}


}



/**
 * Return true if a percentage probability is reached
 * Ex. ReturnPercentageProbability(2.5); // It returns true if a random generated value
 * in the range 0-100 is smaller or equal to 2.5
 * @param probability expressed as a % value.
 * @return It returns true if the probability is reached, otherwise it returns false
*/
    bool BackPropagationTraining(unsigned int epoch, double learningRate, double momentum) {
        return true;
    }


private:
    std::shared_ptr<Network<T>> spNetwork;
    std::shared_ptr<Dataset<T>> spDataset;




};


#endif // TRAINER_H
