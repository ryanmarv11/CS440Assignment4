FLAGS = -std=c++11 -Wall -Wextra -pedantic -g -fpermissive

all: make_array

.PHONY: make_array

make_array: Array.hpp test_Array.cpp
	g++ test_Array.cpp -o array $(FLAGS)

clean:
	rm -rf  *.o array
