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

#ifndef RANDOMFUNCTIONS_H
#define RANDOMFUNCTIONS_H

namespace neuroc {

/**
 * \namespace RandomFunctions
 *
 * It contains functions for randomization
 *
 */
namespace RandomFunctions{


std::vector<double> ReturnRandomVector(unsigned int vectorSize, double minRange=-1, double maxRange=1) ;

bool PercentageProbability(const double& probability);

double ReturnUniformFloatingPointNumber( double minRange=-1, double maxRange=1);

double ReturnGaussianFloatingPointNumber(double mean, double standardDeviation);

int ReturnInteger(int minRange, int maxRange);

}
}


#endif // RANDOMFUNCTIONS_H
