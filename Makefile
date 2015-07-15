#          Copyright Massimiliano Patacchiola 2015
# 	neuroc - C++11 Neural Network Library


CC=g++
CFLAGS=-Wall -std=c++11 -fPIC

compile:
	@echo
	@echo "=== neuroc - C++11 Artificial Neural Networks library ==="
	mkdir -p ./bin #check if the folder exist then create it
	mkdir -p ./bin/obj
	mkdir -p ./bin/lib
	g++ $(CFLAGS) -Iinclude -c ./src/Neuron.cpp -o ./bin/obj/Neuron.o
	g++ $(CFLAGS) -Iinclude -c ./src/Layer.cpp -o ./bin/obj/Layer.o
	g++ $(CFLAGS) -Iinclude -c ./src/Network.cpp -o ./bin/obj/Network.o

	@echo
	@echo "=== Starting creation of Shared Library ==="
	g++ -fPIC -shared -Wl,-soname,libneuroc.so.1  -o ./bin/lib/libneuroc.so.1.0 ./bin/obj/Neuron.o ./bin/obj/Layer.o ./bin/obj/Network.o

	@echo
	@echo "=== Adding Symbolic link to shared library ==="

	@echo "=== Creating the Static Library ==="
	ar rcs ./bin/lib/libneuroc.a ./bin/obj/Neuron.o ./bin/obj/Layer.o ./bin/obj/Network.o

install:
	mkdir -p /usr/local/include/neuroc
	cp ./include/* /usr/local/include/neuroc
	cp ./bin/lib/libneuroc.so.1.0 /usr/local/lib
	ln -sf /usr/local/lib/libneuroc.so.1.0 /usr/local/lib/libneuroc.so
	ln -sf /usr/local/lib/libneuroc.so.1.0 /usr/local/lib/libneuroc.so.1

clean:
	rm -r /usr/local/include/neuroc
	rm ./bin/lib/libneuroc.a ./bin/obj/Neuron.o ./bin/obj/Layer.o ./bin/obj/Network.o
	rm ./bin/lib/libneuroc.so.1.0
	rm /usr/local/lib/libneuroc.so.1 
	rm /usr/local/lib/libneuroc.a  ./bin/lib/libneuroc.a


