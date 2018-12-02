default_target: all

# The main all target
all: 
	g++ -std=gnu++11 -c -O3 main.cc
	g++ -std=gnu++11 -O3 main.o -o graph
