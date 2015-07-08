neuroc
==============

Lightweight and highly optimized C++ library for Neural Networks
--------------

Welcome in the neuroc repository! I designed this library after reading the excellent book of Bjarne-Stroustrup *The C++ Programming Language (4th Edition)* especially the chapter 34 *Memory and Resources* where the author presents some illuminating examples of **shared_ptr** and **weak_ptr**. Starting from there I decided to create a Neural Networks library based on the idea of a safe memory management.

Prerequisites
--------------

To install the library you must have *make* and *g++* already installed on your system.
You can install them from a Unix system running the following commands from the terminal:

 `sudo apt-get install build-essential`
 `sudo apt-get install g++`


Installation
--------------

If you are using a Unix system you can install the library very easily:

1. Download the zip package clicking on "Download ZIP" on your right ->
2. Extract the files from the archive and save them in a folder on your computer
3. Open the terminal inside that folder
4. Write `make compile` on your terminal and press Enter
5. If everything is right you will find the shared and static libraries (libneuroc.so, libneuroc.a) inside the folder *bin/lib*
6. Write `sudo make install` and press Enter
7. The installation is complete, the libraries were copied inside the system folder and they are ready to be used
8. To remove the library you have to write `make clean` in the terminal, it will delete all the files produced during the installation


Using the library
--------------

After the installation neuroc was copied on your system, inside the folder */usr/local/lib* you can see the shared library libneuroc.so and the static library libneuroc.a. To use the shared library it is necessary to link it to your project. In g++ this is very easy, here is an example:

```
g++ -std=c++11 -I/usr/local/lib -lneuroc -c /home/username/mycode.cpp
```

This command will compile the imaginary file mycode.cpp and will produce an executable file called a.out in your project directory.
Using a similar command it is also possible to use the static version of the library:

```
g++ -std=c++11 -I/usr/local/lib -static -lneuroc -c /home/username/mycode.cpp
```
In this case the library will be statically included inside your code.
To integrate neuroc in a different environment (ex Eclipse, Code::Blocks, etc) follow the istructions given by the producer on how to integrate an external shared library or a static one.

