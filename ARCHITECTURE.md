Library Architecture
====================

A brief Introduction
--------------------

When I started to think about this library I tought that was necessary to start from a strong core. The biggest error that someone can do creating a library is to superficially build the first class.
In my case the first class is the Neuron one, it is the backbone of the entiere architecture. To build this class I taken inspiration from the Matlab Neural Network Toolbox, which is described in the official user manual. In my opinion starting from a well defined architecture is the right strategy to decrease the probability of errors in a near future. In the following sections I am going to introduce you the main blocks behind neuroc.

Neuron
-------

The Neuron is an object with three functions inside:

1. Weight Function
2. joint Function
3. Transfer Function

There are different type of Weight, Joint and Transfer functions, creating a neuron it is necessary to define which function to use. 
Every neuron contains also a connection vector, representing the weights (incoming connections). The output of the neuron is a single value obtained from the dot product of the input vector and the connection vector. 

Example: A neuron with 4 input will have a connection vector with 4 elements, each one of this values is a weight

Once the neuron is created it is possible to compute the output using the fucntion **Compute()** that take as input a vector and produce as output a single value.
This function is a sequence of operations, the following list is an example of operations taken from a standard neuron:

1- Neuron-input = input_vector
2- Weight Function output = input_vector · connection_vector
3- Join Function output = weight_function_output + bias
4- Transfer Function output = TransferFunction(join_function_output)
5- Neuron-output = transfer_function_output

Layer
-------

The Layer is a container of neurons. It has a connection matrix wich is a matrix of neurons vectors. If a Layers has 4 Neurons it has a connection matrix containing 4 connection vectors. Creating a layer it is necessary to specify a connection matrix and each one of the three functions necessary for a single neuron to work (see Neuron section). It is also possible to define a layer inserting a list of already existing neurons. The connection matrix object will define the number of input and output of the layer.

> 
> Layer<float> myLayer();
> 

In this example a Layer of 2 Neurons is created, it can be connected with another layer of 4 neurons as input.
Once the layer is created it is possible to have the output using the fucntion **Compute()** that take as input a vector or a list and produce as output a vector.
This function is a sequence of operations that are identical to the ones seen in the Neuron section above. In this case there is only one difference, the connection is a real matrix, composed of the connection vectors of the neurons inside the layer. The Weight Function will be a dot product of a input_vector and a connection matrix:

- Weight Function output = input_vector * connection_matrix


Network
-------

The Network class is simply a container of layers. The network can be initialised with a single line and can take a list of layers as arguments. The order of insertion is important, because the output vector of each layer is given as input vector to the next layer.




