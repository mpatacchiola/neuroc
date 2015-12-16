# Neuroc - C++ Artificial Nerual Networks library
# Copyright (C) 2015  Massimiliano Patacchiola
# Author: Massimiliano Patacchiola
# email: 


CC=g++
CFLAGS=-Wall -std=c++11 -O3 -fexceptions -I/usr/local/include/neuroc -I/usr/include/eigen3

#to compress the files for the handwritten digit example: tar -jcvf handwritten_dataset.tar pendigits.tes pendigits.tra
#to uncompress the files: -jxvf handwritten_dataset.tar -C ./build/exec/

compile:
	@echo
	@echo "===  Neuroc - C++ Artificial Nerual Networks library  ==="
	@echo "===     Copyright Massimiliano Patacchiola 2015       ==="
	@echo "===                 GNU v2.0 license                  ==="
	@echo
	mkdir -p ./build #check if the folder exist then create it
	mkdir -p ./build/obj
	mkdir -p ./build/exec


	@echo
	@echo "=== Compiling example files ==="
	@echo
	@echo "..... XOR"
	g++ $(CFLAGS) -Iinclude -c ./xor.cpp -o ./build/obj/xor.o
	g++ -o ./build/exec/xor ./build/obj/xor.o -lneuroc
	@echo
	@echo "..... handwritten digits"
	g++ $(CFLAGS) -Iinclude -c ./handwritten_digits.cpp -o ./build/obj/handwritten_digits.o
	g++ -o ./build/exec/handwritten_digits ./build/obj/handwritten_digits.o -lneuroc
	@echo


	@echo
	@echo "=== Uncompressing the dataset ==="
	@echo
	tar -jxvf handwritten_dataset.tar -C ./build/exec/


remove:
	@echo
	@echo "=== Removing example files ==="
	@echo
	rm ./build/obj/xor.o ./build/exec/xor 
	rm ./build/obj/handwritten_digits.o ./build/exec/handwritten_digits



