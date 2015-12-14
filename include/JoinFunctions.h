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

#ifndef JOINFUNCTIONS_H
#define JOINFUNCTIONS_H

#include <Eigen/Dense>

namespace neuroc{
/**
 * \namespace JoinFunctions
 *
 * It contains functions used by the neuron in the second computational step
 * All the functions of this namespace must take two values and return a single value
 */
namespace JoinFunctions{

Eigen::VectorXd Sum(Eigen::VectorXd, Eigen::VectorXd);
Eigen::VectorXd Product(Eigen::VectorXd, Eigen::VectorXd);

}
}

#endif // JOINFUNCTIONS_H
