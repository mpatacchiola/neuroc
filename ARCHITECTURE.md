Library Architecture
====================

A brief Introduction
--------------------

When I started to think about this library I tought that was necessary to start from a strong core. The biggest error that someone can do creating a library is to superficially build the first class.
In my case the first class is the Layer, it is the backbone of the entiere architecture. To build this class I taken inspiration from the Matlab Neural Network Toolbox, which is described in the official user manual. In my opinion starting from a well defined architecture is the right strategy to decrease the probability of errors in a near future. In the following sections I am going to introduce you the main blocks behind neuroc.


Layer
-------

The layer is an object with three functions inside:

1. Weight Function
2. join Function
3. Transfer Function

There are different type of Weight, Join and Transfer functions, creating a layer it is necessary to define which function to use. 
Every layer contains also a matrix, representing the weights (incoming connections). The output of the layer is a vector obtained from the  product of the input vector and the weight matrix. 

The Layer has a connection matrix wich is a matrix of Eigen vectors. If a layer has 4 input and 2 output, it means that it has 2 neurons and a 2x4 weight matrix. 
Once the layer is created it is possible to have the output using the fucntion **Compute()** that take as input a vector and produce as output a vector.


Network
-------

The Network class is simply a container of layers. The network can be initialised with a single line and can take a list of layers as arguments. The order of insertion is important, because the output vector of each layer is given as input vector to the next layer.




