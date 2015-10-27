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

#include "BackpropagationLearning.h"

namespace neuroc{

/**
* Class constructor.
*
**/
BackpropagationLearning::BackpropagationLearning(){

}

/**
* Class destructor.
*
**/
BackpropagationLearning::~BackpropagationLearning(){

}

/**
* Start the learning algorithm for the specified number of cycles.
*
* @return it returns the trained version of the network
**/
Network BackpropagationLearning::StartLearning(Network net, Dataset& inputDataset, Dataset& targetDataset, unsigned int cycles, bool print){

 mNet = net;
 
 //Check if the two dataset have the same size
 if(inputDataset.ReturnNumberOfData() != targetDataset.ReturnNumberOfData()){
  std::cerr << "Neuroc Eccor: BackpropagationLearning the input dataset and the target dataset have different size" << std::endl;
  return mNet;
 }

 int tot_layers = mNet.ReturnNumberOfLayers();
 tot_layers = tot_layers - 1; //zero based index

 //Main Cycle, for all data in dataset
 for(unsigned int i_set=0; i_set<inputDataset.ReturnNumberOfData(); i_set++){

  //Iteration through all the layers of the network
  for(int i_layer=tot_layers; i_layer>-1; i_layer--){
   
   //This is the case for the OUTPUT layer
   if(i_layer==tot_layers){


   //If the layer is HIDDEN
   } else {



   }


  }//layer cycle
  

 }//main cycle

 return mNet;
}


} //namespace



