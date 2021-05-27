FLAGS = -std=c++11 -Wall -Wextra -pedantic -g -fpermissive

all: make_array make_web

.PHONY: make_array make_web

make_array: Array.hpp test_Array.cpp
	g++ test_Array.cpp -o array $(FLAGS)
make_web: Array.hpp web_page_test.cpp
	g++ web_page_test.cpp -o web $(FLAGS)

clean:
	rm -rf  *.o array web