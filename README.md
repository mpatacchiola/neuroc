neuroc
==============

Lightweight and highly optimized C++ library for Neural Networks
--------------

Welcome in the Neuroc repository! Neuroc is a modular library based on the idea of smart blocks. The neuron class is a generic object made of different functions. The architecture is inspired by the *Matlab Neural Network Toolbox*, you can find other details about neuroc design [here](ARCHITECTURE.md). Let's look now at the main features of Neuroc:

- Essential and expandible
- Safe memory management
- Object Oriented approach
- Can use float or double
- All you can eat networks architecture
- Customizable Transfer Function, Weight Initialization 
- You can save Networks, Layers and Neurons in XML files
- Open source (GNU v.2 license)

Prerequisites
--------------

To install the library you must have *make* and g++ already installed on your system.
You can install them from a Unix system running the following commands from the terminal:

 `sudo apt-get install build-essential`

 `sudo apt-get install g++`


Installation
-------------

If you are using a Unix system you can install the library very easily:

1. Clone the repository or download it from [here](https://github.com/mpatacchiola/neuroc/archive/master.zip)
2. Extract the files from the archive and save them in a folder on your computer
3. Open the terminal inside that folder and type the following command
4. `make compile`
5. If everything is right you will find the shared and static libraries (libneuroc.so, libneuroc.a) inside the folder *bin/lib*. You have to install the library typing the following command
6. `sudo make install`
7. The installation is complete, the library files were copied inside the system folders and they are ready to be used
8. To remove the library you have to write `sudo make clean` in the terminal, it will delete all the files produced during the installation


Using the library in your own code
----------------------------------

After the installation neuroc was copied on your system, inside the folder */usr/local/lib* you can see the shared library libneuroc.so and the static library libneuroc.a. The header files were copied in */usr/local/include*, you need them in order to use the library.
The first thing to do is to include the library in your source file, you can do it adding the following includes:

> `#include<neuroc/Neuron.h>`
> 
>  `#include<neuroc/Layer.h>`
> 
>  `#include<neuroc/Network.h>`
> 
>  `#include<neuroc/Parser.h>`
> 
>  `#include<neuroc/Dataset.h>`
> 

To use the shared library it is also necessary to link it to your project. In g++ this is very easy, here is an example:

`g++ -Wall -std=c++11 -fPIC -I/usr/local/include/neuroc -L/usr/local/lib -Wl,--no-as-needed mycode.cpp -o mycode -lneuroc`

This command will compile the imaginary file mycode.cpp and will produce an executable file called mycode in your project directory.
To check if the shared library is linked to your executable, you can run the Unix command ldd.
Using g++ it is also possible to use the static version of the library:

`g++ -std=c++11 -I/usr/local/include/neuroc -L/usr/local/lib -static /home/username/mycode.cpp -o mycode -lneuroc`

In this case the library will be statically included inside your code.
To integrate neuroc in a different environment (ex Eclipse, Code::Blocks, etc) follow the istructions given by the producer on how to integrate an external shared library or a static one.


Examples
---------

Neuroc permits to create different kind of network. Every object is a container where you can push other objects or data.
The class network is a container of Layers, the class Layers is a container of Neurons and the class Dataset is a container of input/target values.

With only a single line of code it is possible to create a fully connected multilayer perceptron:

> Network<float> myNet(10, 5, 1);  //Feedforward network with: 10 input, 5 hidden, 1 output

To create a Network with more than three layers:

> Network<float> myNet({10, 5, 3, 2, 1});  //Feedforward network with: 10 input, 5 hidden, 3 hidden, 2 hidden, 1 output

It is very easy to create a Dataset and push inside it some values:

> Dataset myDataset; //Creating the XOR dataset
> 
> myDataset.PushBackInputAndTarget({0.0, 0.0}, {0.0});
> 
> myDataset.PushBackInputAndTarget({0.0, 1.0}, {1.0});
> 
> myDataset.PushBackInputAndTarget({1.0, 0.0}, {1.0});
> 
> myDataset.PushBackInputAndTarget({1.0, 1.0}, {0.0});

You can save Networks, Layers, Datasets in an XML file using the class Parser:

> Parser myParser;  //Definition of the Parser
> 
> myParser.InitialiseXML("/home/user/mynet.xml");  //It initialises the Parser, adding the prefix of the XML file
> 
> myParser.SaveNetwork(myNetwork);  //It saves the network in the XML
> 
> myParser.SaveNetwork(myDataset);  //It saves the dataset in the XML
> 
> myParser.FinaliseXML();  //It finalises and close the file


Documentation
-------------

The documentation is produced with Doxygen and the HTML output can be found inside the folder /html.
An explenation of the logic behind the architecture can be found in this specific [readme](ARCHITECTURE.md).


License
-------

*neuroc - c++11 Artificial Neural Networks library*

*Copyright (C) 2015  Massimiliano Patacchiola*

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.


