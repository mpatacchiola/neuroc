#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <memory>  // shared_ptr
#include <cmath>  //  "exp" function
#include <string>
#include <random>
#include <iostream>  // printing functions

/**
 * Copyright 2015 <Massimiliano Patacchiola>
 *
 * \class Neuron
 *
 * \brief
 *
 * \author Massimiliano Patacchiola
 *
 * \version 0
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
   if (mIsBias== true) return mValue = 1;  // return always 1 if the neuros is a Bias Neuron
   mValuePrevious = mValue;
   mValue = 0;  // value reset

   for (unsigned int i = 0; i < mIncomingVector.size(); i++)
   mValue += (*mIncomingVector[i].spWeight) * (mIncomingVector[i].spNeuronReference->mValue);

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
   if (mIsBias == true) return mValue = 1;  // return always 1 if the neuros is a Bias Neuron

   mValuePrevious = mValue;
   mValue = 0;  // value reset

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
* Calculate error for this neuron. Use this function when the neuron is not an output neuron.
* The function must be used from the output layer to the input layer.
* @return it returns the calculated error, it returns zero in case of problem
*/
T ComputeError() {
try {
mErrorPrevious = mError;
mError = 0;

for (unsigned int i = 0; i < mOutgoingVector.size(); i++) mError = (mOutgoingVector[i].spNeuronReference->mError) * (*mOutgoingVector[i].spWeight);

if (functionToUse == SIGMOID) {
return mError = mValue * (1-mValue) * mError;  // Sigmoid Function
} else if (functionToUse == TANH) {
return mError = TanhDerivative(mValue) * mError;  // tanh Function
} else {
return 0;
}
}catch(...) {
std::cerr << "Neuron error computing the error" << std::endl;
return 0;
}
}

/**
* This function can be used to find the output error for output neurons.
* The function must be used from the output layer to the input layer.
* @param targetOutput the desired target output, this is the formula used:
* error = derivative(output) * (targetOutput - output)
* @return it returns the calculated error.
*/
T ComputeError(T targetOutput) {
mErrorPrevious = mError;

if (functionToUse == SIGMOID) {
mError = mValue * (1-mValue) * (targetOutput - mValue);  // Sigmoid Function
} else if (functionToUse == TANH) {
mError = TanhDerivative(mValue) * (targetOutput - mValue);  // tanh Function
} else {
return 0;
}
return mError;
}

/**
* Set the activation function used for the computation.
* The default activation function is SIGMOID.
* @param functionToUse this is the function to use, it is possible to choose these values: SIGMOID, TANH, BIAS
* @return it returns true if everything is all right, otherwise false.
*/
inline bool SetActivationFunction(activationFunction functionToUse) {
functionToUse = functionToUse;
return true;
}

/**
* Get the activation function used for computation.
*
* @return it returns the activation function used: SIGMOID, TANH, BIAS
**/
inline activationFunction GetActivationFunction() {
return functionToUse;
}

/**
* Update the incoming connection to the neuron.
* It has not effects if the neurons does not have incoming connections.
* There is not a precise order for calling this function in a network,
* it is only necessary to use it after the Error calculation.
*
* @param eta Real[0,1], this is the learning rate to use, the value is an index of the size of the changes during the training
* @return it returns true if everything is all right, otherwise false.
*/
bool UpdateIncomingConnections(T eta) {
try {
for (unsigned int i = 0; i < mIncomingVector.size(); i++) {
// it finds the delta for every connection: learningRate * error * neuronValue
T delta = eta * mError * mIncomingVector[i].spNeuronReference->mValue;
// Update the connections vector:  connection + delta
*mIncomingVector[i].spWeight = (*mIncomingVector[i].spWeight) + delta;
}

return true;
}catch(...) {
std::cerr << "Neuron error updating the connections" << std::endl;
return false;
}
}

/**
* Update the incoming connection to the neuron. It has not effects if the neuron does not have incoming connections.
* There is not a precise order for calling this function in a network, it is only necessary to use it after the Error calculation.
*
* @param eta Real[0,1] typical 0.3; this is the learning rate to use, the value is an index of the size of the changes during the training
* @param momentum Real[0,1] typical 0.9; this is the momentum, a value which prevent the system fro converging to a local minimum.
* @return it returns true if everything is all right, otherwise false.
*/
bool UpdateIncomingConnections(T eta, T momentum) {
try {
for (unsigned int i = 0; i < mIncomingVector.size(); i++) {
// to use momentum it is necessary to calculate delta at a previous time step
T deltaPrevious = eta * mErrorPrevious * mIncomingVector[i].spNeuronReference->mValuePrevious;
// it finds the delta for every connection: learningRate * error * neuronValue
T delta = eta * mError * mIncomingVector[i].spNeuronReference->mValue;
// Update the connections vector:  connection + delta
*mIncomingVector[i].spWeight = (*mIncomingVector[i].spWeight) + delta * momentum * deltaPrevious;
}

return true;
}catch(...) {
std::cerr << "Neuron error updating the connections" << std::endl;
return false;
}
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
std::cerr << "Neuron, there are not incoming connections" << std::endl;
return false;
}

std::random_device randomDevice;
std::mt19937 generator(randomDevice());
std::uniform_real_distribution<> distribution(minRange, maxRange);  // Generate a random weight

for (unsigned int i = 0; i < mIncomingVector.size(); i++)
*mIncomingVector[i].spWeight = distribution(generator);

return true;
}catch(...) {
std::cerr << "Neuron error randomizing the connections" << std::endl;
return false;
}
}

/**
* Randomize all the outgoing connections to the neuron.
* It is possible to specify a minimum and maximum range for the random generator.
*
* @param minRange the minimum range for the random generator
* @param maxRange the maximum range for the random generator
* @return bool it returns true if everything is all right, otherwise false.
*/
bool RandomizeOutgoingConnections(T minRange, T maxRange) {
try {
if (minRange >= maxRange) {
std::cerr << "Neuron the minimum value is grater than the maximum value the connections" << std::endl;
return false;
}

if (mOutgoingVector.empty() == true) {
std::cerr << "Neuron, there are not outgoing connections" << std::endl;
return false;
}

std::random_device rand_dev;
std::mt19937 rand_gen(rand_dev());
std::uniform_real_distribution<> rand_dist(minRange, maxRange);  // Generate a random weight


for (unsigned int i = 0; i < mOutgoingVector.size(); i++) {
*mOutgoingVector[i].spWeight = rand_dist(rand_gen);
}

return true;
}catch(...) {
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
bool SetConnectionFromNeuron(std::shared_ptr< Neuron<T> > spNeuron, T value) {
for (unsigned int i=0; i < mIncomingVector.size(); i++)
if(mIncomingVector[i].spNeuronReference ==  spNeuron) {*mIncomingVector[i].spWeight=value; return true;}

return false;
}

/**
* Get the value of an Incoming Connection.
*
* @param index unsiged int which identify the connection into the vector
* @return it returns the value of the connection
*/
T GetConnectionFromNeuron(std::shared_ptr< Neuron<T> > spNeuron) {
for (unsigned int i = 0; i < mIncomingVector.size(); i++)
if(mIncomingVector[i].spNeuronReference ==  spNeuron) {return *mIncomingVector[i].spWeight;}

return 0;
}

/**
* Set the value of an Outgoing Connection.
*
* @param index unsiged int which identify the connection into the vector
* @param value value to write
* @return it returns true if it is all right, otherwise false
*/
bool SetConnectionToNeuron(std::shared_ptr< Neuron<T> > spNeuron, T value) {
for (unsigned int i = 0; i < mOutgoingVector.size(); i++)
if(mOutgoingVector[i].spNeuronReference ==  spNeuron) {*mOutgoingVector[i].spWeight=value; return true;}

return false;
}

/**
* Get the value of an Outgoing Connection.
*
* @param index unsiged int which identify the connection into the vector
* @return it returns the value of the connection
*/
T GetConnectionToNeuron(std::shared_ptr< Neuron<T> > spNeuron) {
for (unsigned int i = 0; i < mOutgoingVector.size(); i++)
if(mOutgoingVector[i].spNeuronReference ==  spNeuron) {return *mOutgoingVector[i].spWeight;}

return 0;
}


/**
* Print on terminal informations about the neuron.
*
*/
void Print() {
std::cout << "value ..... " << mValue << std::endl;
std::cout << "error ..... " << mError << std::endl;
std::cout << "number of incoming connections ..... " << mIncomingVector.size() << std::endl;
std::cout << "number of outgoing connections ..... " << mOutgoingVector.size() << std::endl;

for (unsigned i = 0; i < mIncomingVector.size(); i++) {
std::cout << "incoming neuron[" << i << "] ..... " << mIncomingVector[i].spNeuronReference->mValue << std::endl;
std::cout << "incoming connection[" << i << "] ..... " << *mIncomingVector[i].spWeight << std::endl;
}

for (unsigned i = 0; i < mOutgoingVector.size(); i++) {
std::cout << "outgoing neuron[" << i << "] ..... " << mOutgoingVector[i].spNeuronReference->mValue << std::endl;
std::cout << "outgoing connection[" << i << "] ..... " << (*mOutgoingVector[i].spWeight) << std::endl;
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
std::cout << "number of outgoing connections ..... " << mOutgoingVector.size() << std::endl;

if (printConnections == true) {
for (unsigned i = 0; i < mIncomingVector.size(); i++) {
std::cout << "incoming neuron[" << i << "] ..... " << mIncomingVector[i].spNeuronReference->mValue << std::endl;
std::cout << "incoming connection[" << i << "] ..... " << *mIncomingVector[i].spWeight << std::endl;
}

for (unsigned i = 0; i < mOutgoingVector.size(); i++) {
std::cout << "outgoing neuron[" << i << "] ..... " << mOutgoingVector[i].spNeuronReference->mValue << std::endl;
std::cout << "outgoing connection[" << i << "] ..... " << (*mOutgoingVector[i].spWeight) << std::endl;
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
mValue = value;
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
* Add a connection to the neuron specified.
* If the specified neuron is not present return false
*
* @param neuronToConnect pointer to the Neuron to add
* @return true if the operation succeeded, false otherwise
*/
bool AddConnectionToNeuron(std::shared_ptr< Neuron<T> > spThisNeuron, std::shared_ptr< Neuron<T> > spNeuron) {
try {
if(spThisNeuron.get() != this) {
std::cerr << "Neuron error the spThisNeuron pointer is not a pointer to this neuron" << std::endl;
return false;
}

if(spThisNeuron == nullptr) {
std::cerr << "Neuron error the spThisNeuron pointer is empty" << std::endl;
return false;
}

if(spNeuron == nullptr) {
std::cerr << "Neuron error the spNeuron pointer is empty" << std::endl;
return false;
}

if(spNeuron == spThisNeuron) {
std::cerr << "Neuron error the spNeuron pointer is equal to the spThisNeuron pointer." << std::endl;
return false;
}

for (unsigned i = 0; i < mOutgoingVector.size(); i++) {
if (mOutgoingVector[i].spNeuronReference == spNeuron) {
std::cerr << "Neuron error there is already a connection between these neurons." << std::endl;
return false;
}
}

// Add a random weight value
std::random_device rand_dev;
std::mt19937 rand_gen(rand_dev());
std::uniform_real_distribution<> rand_dist(-0.1, 0.1);  // Generate a random weight

T connection_value = rand_dist(rand_gen);     //  declare a constant  to new T
std::shared_ptr<T> sp_connection_value = std::make_shared<T> (connection_value);

mConnectionStruct temp_connection;
temp_connection.spNeuronReference = spNeuron;
temp_connection.spWeight = sp_connection_value;
mOutgoingVector.push_back(temp_connection);

mConnectionStruct temp_connection_other;
temp_connection_other.spNeuronReference = spThisNeuron;
temp_connection_other.spWeight = sp_connection_value;
spNeuron->mIncomingVector.push_back(temp_connection_other);

return true;
}catch(...) {
std::cerr << "Neuron error removing creating connection" << std::endl;
return false;
}
}

/**
* Add a connection from the neuron specified.
* If the specified neuron is not present return false
*
* @param neuronToConnect pointer to the Neuron to add
* @return true if the operation succeeded, false otherwise
*/
bool AddConnectionFromNeuron(std::shared_ptr< Neuron<T> > spNeuron, std::shared_ptr< Neuron<T> > spThisNeuron) {
if(spThisNeuron.get() != this) {
std::cerr << "Neuron error the spThisNeuron pointer is not a pointer to this neuron" << std::endl;
return false;
}

if(spThisNeuron == false) {
std::cerr << "Neuron error the spThisNeuron pointer is empty" << std::endl;
return false;
}

if(spNeuron == false) {
std::cerr << "Neuron error the spNeuron pointer is empty" << std::endl;
return false;
}

if(spNeuron == spThisNeuron) {
std::cerr << "Neuron error the spNeuron pointer is equal to the spThisNeuron pointer." << std::endl;
return false;
}


for (unsigned i = 0; i < mIncomingVector.size(); i++) {
if (mIncomingVector[i].spNeuronReference == spNeuron) {
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
temp_connection.spNeuronReference = spNeuron;
temp_connection.spWeight = sp_connection_value;
mIncomingVector.push_back(temp_connection);

mConnectionStruct temp_connection_other;
temp_connection_other.spNeuronReference = spThisNeuron;
temp_connection_other.spWeight = sp_connection_value;
spNeuron->mOutgoingVector.push_back(temp_connection_other);

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
if (mIncomingVector[i].spNeuronReference == spNeuron) {
// 1- Remove the connection in the other neuron
spNeuron->RemoveConnectionToNeuron(spThisNeuron);
// 2-Remove the connection internally
mIncomingVector.erase(mIncomingVector.begin(), mIncomingVector.begin()+i);
return true;
}
}

return false;
}catch(...) {
std::cerr << "Neuron error removing incoming connection" << std::endl;
return false;
}
}


/**
* Remove an outgoing connection to the neuron specified.
* If the specified neuron is not present return false
*
* @param neuronToRemove pointer to the Neuron to remove
* @return true if the operation succeeded, false otherwise
*/
bool RemoveConnectionToNeuron(std::shared_ptr< Neuron<T> > spThisNeuron, std::shared_ptr< Neuron<T> > spNeuron) {
try {
for (unsigned i = 0; i < mOutgoingVector.size(); i++) {
if (mOutgoingVector[i].spNeuronReference == spNeuron) {
// 1- Remove the connection in the other neuron
spNeuron->RemoveConnectionFromNeuron(spThisNeuron);
// 2-Remove the connection internally
mOutgoingVector.erase(mOutgoingVector.begin(), mOutgoingVector.begin()+i);
return true;
}
}

return false;
}catch(...) {
std::cerr << "Neuron error removing outgoing connection" << std::endl;
return false;
}
}

/**
* Get the total number of the incoming connections.
*
* @return unisgned int which represents the number of connections
*/
unsigned int GetNumberOfIncomingConnections() {
return mIncomingVector.size();
}


/**
* Get the total number of the outgoing connections.
*
* @return unisgned int which represents the number of connections
**/
unsigned int GetNumberOfOutgoingConnections() {
return mOutgoingVector.size();
}


/**
* Set the current neuron as a Bias Neuron.
* A Bias neuron is used to shift the activation function on the x axis during the training.
*
* @param isBias this is a boolean value true: the neuron is set as a Bias neuron; false: the neuron is not a Bias Neuron
*/
inline void SetAsBiasNeuron(bool isBiasNeuron) {
mIsBias = isBiasNeuron;
}


/**
 * Return a value which indicate if the current neuron is a Bias Neuron.
 * A Bias neuron is used to shift the activation function on the x axis during the training.
 *
 * @return boolean true: the neuron is set as a Bias neuron; false: the neuron is not a Bias Neuron
 */
inline bool IsBiasNeuron() {
return mIsBias;
}

 private:
/** This struct contain two std::shared_ptr, one to the neuron and another to the weight */
struct mConnectionStruct{
std::shared_ptr< Neuron<T> > spNeuronReference;
std::shared_ptr< T > spWeight;
};

T mValue = 0;  /**< value obtained after the computation */
T mValuePrevious = 0;  /**< value obtained after the computation at n-1 */
T mError = 0;  /**< error obtained after the error backpropagation */
T mErrorPrevious = 0; /**< error obtained after the error backpropagation at n-1 */
bool mIsBias = false;
activationFunction functionToUse = SIGMOID;
std::vector<mConnectionStruct> mOutgoingVector;
std::vector<mConnectionStruct> mIncomingVector;

inline T Sigmoid(T input) { return ( 1 / (1 + exp(-input)) ); }
inline T SigmoidDerivative(T input) { return (1 / (1 + exp(-input))) * (1 - (1 / (1 + exp(-input)))); }
inline T TanhDerivative(T input) { return (1-tanh(input)) * (1+tanh(input)); }
};  // Class Neuron




#endif // NEURON_H
