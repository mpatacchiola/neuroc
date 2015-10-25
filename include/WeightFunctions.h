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

#ifndef WEIGHTFUNCTIONS_H
#define WEIGHTFUNCTIONS_H


/**
 *
 * \brief This is and header wich contains different useful functions
 *
 * This header contains useful functions. 
 * The functions are assigned to different namespaces.
 * You are free to extend this header adding your own functions. 
 *
*/

namespace neuroc{

/**
 * \namespace WeightFunctions
 *
 * It contains functions used by the neuron in the first computational step
 * All the functions of this namespace must take two vectors and return a single value
 */
namespace WeightFunctions{

double DotProduct(std::vector<double> firstVector, std::vector<double> secondVector);
double EuclideanDistance(const std::vector<double>& firstVector, const std::vector<double>& secondVector);
double AbsoluteDistance(const std::vector<double>& firstVector, const std::vector<double>& secondVector);

} //namespace

} //namespace

#endif // WEIGHTFUNCTIONS_H
