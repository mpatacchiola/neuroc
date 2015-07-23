 
# neuroc - c++11 Artificial Neural Networks library
# Copyright (C) 2015  Massimiliano Patacchiola
# Author: Massimiliano Patacchiola
# email:  
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.



CC=g++
CFLAGS=-Wall -std=c++11 -fPIC

compile:
	@echo
	@echo "=== neuroc - C++11 Artificial Neural Networks library ==="
	@echo "===      Copyright Massimiliano Patacchiola 2015      ==="
	@echo
	mkdir -p ./bin #check if the folder exist then create it
	mkdir -p ./bin/obj
	mkdir -p ./bin/lib
	g++ $(CFLAGS) -Iinclude -c ./src/Neuron.cpp -o ./bin/obj/Neuron.o
	g++ $(CFLAGS) -Iinclude -c ./src/Layer.cpp -o ./bin/obj/Layer.o
	g++ $(CFLAGS) -Iinclude -c ./src/Network.cpp -o ./bin/obj/Network.o
	g++ $(CFLAGS) -Iinclude -c ./src/Parser.cpp -o ./bin/obj/Parser.o

	@echo
	@echo "=== Starting creation of Shared Library ==="
	g++ -fPIC -shared -Wl,-soname,libneuroc.so.1  -o ./bin/lib/libneuroc.so.1.0 ./bin/obj/Neuron.o ./bin/obj/Layer.o ./bin/obj/Network.o ./bin/obj/Parser.o

	@echo
	@echo "=== Creating the Static Library ==="
	ar rcs ./bin/lib/libneuroc.a ./bin/obj/Neuron.o ./bin/obj/Layer.o ./bin/obj/Network.o ./bin/obj/Parser.o
	@echo

install:

	@echo
	@echo "=== Copying file in the system folders ==="
	mkdir -p /usr/local/include/neuroc
	cp ./include/* /usr/local/include/neuroc
	cp ./bin/lib/libneuroc.so.1.0 /usr/local/lib

	@echo
	@echo "=== Adding Symbolic link to shared library ==="
	ln -sf /usr/local/lib/libneuroc.so.1.0 /usr/local/lib/libneuroc.so
	ln -sf /usr/local/lib/libneuroc.so.1.0 /usr/local/lib/libneuroc.so.1
	@echo

clean:
	@echo
	@echo "=== Removing files in the system folders ==="
	rm -r /usr/local/include/neuroc
	rm ./bin/lib/libneuroc.a ./bin/obj/Neuron.o ./bin/obj/Layer.o ./bin/obj/Network.o ./bin/obj/Parser.o
	rm ./bin/lib/libneuroc.so.1.0
	rm /usr/local/lib/libneuroc.so.1 
	rm /usr/local/lib/libneuroc.a  ./bin/lib/libneuroc.a
	@echo
