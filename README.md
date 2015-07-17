neuroc
==============

Lightweight and highly optimized C++ library for Neural Networks
--------------

Welcome in the neuroc repository! I designed this library after reading the excellent book of Bjarne-Stroustrup *The C++ Programming Language (4th Edition)* especially the chapter 34 *Memory and Resources* where the author presents some illuminating examples of **shared_ptr** and **weak_ptr**. Starting from there I decided to create a Neural Networks library based on the idea of a safe memory management.

- Safe memory management using Smart Pointers
- Object Oriented approach
- Multilayer feedforward Networks
- Sparse connected Networks
- Multiple Activation Functions

Prerequisites
--------------

To install the library you must have *make* and g++ already installed on your system.
You can install them from a Unix system running the following commands from the terminal:

 `sudo apt-get install build-essential`

 `sudo apt-get install g++`


Installation
--------------

If you are using a Unix system you can install the library very easily:

1. Clone the repository or download it from [here](https://github.com/mpatacchiola/neuroc/archive/master.zip)
2. Extract the files from the archive and save them in a folder on your computer
3. Open the terminal inside that folder and type the following command
4. `make compile`
5. If everything is right you will find the shared and static libraries (libneuroc.so, libneuroc.a) inside the folder *bin/lib*. You have to install the library typing the following command
6. `sudo make install`
7. The installation is complete, the library files were copied inside the system folders and they are ready to be used
8. To remove the library you have to write `sudo make clean` in the terminal, it will delete all the files produced during the installation


Using the library
--------------

After the installation neuroc was copied on your system, inside the folder */usr/local/lib* you can see the shared library libneuroc.so and the static library libneuroc.a. The header files were copied in */usr/local/include*, you need them in order to use the library.
To use the shared library it is necessary to link it to your project. In g++ this is very easy, here is an example:

`g++ -Wall -std=c++11 -fPIC -I/usr/local/include/neuroc -L/usr/local/lib -Wl,--no-as-needed mycode.cpp -o mycode -lneuroc`

This command will compile the imaginary file mycode.cpp and will produce an executable file called mycode in your project directory.
To check if the shared library is linked to your executable, you can run the Unix command ldd.
Using g++ it is also possible to use the static version of the library:

`g++ -std=c++11 -I/usr/local/include/neuroc -L/usr/local/lib -static /home/username/mycode.cpp -o mycode -lneuroc`

In this case the library will be statically included inside your code.
To integrate neuroc in a different environment (ex Eclipse, Code::Blocks, etc) follow the istructions given by the producer on how to integrate an external shared library or a static one.


Code Examples
--------------

Neuroc permits to create diffrent kind of network. With only a single line of code it is possible to create a multilayer perceptron:

`Network<float> myNet(10, 5, 1);  //Feedforward network with: 10 input, 5 hidden, 1 output`

To create a Network with more than three layers you can write:

`Network<float> myNet({10, 5, 3, 2, 1});  //Feedforward network with: 10 input, 5 hidden, 3 hidden, 2 hidden, 1 output`

You can save the Network in an XML file:

`myNet.SaveAsXML("/home/user/mynet.xml");  //its saves the network`






