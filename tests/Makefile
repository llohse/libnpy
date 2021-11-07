.PHONY: all clean

all: test data/f8.npy
	./test

test: test.cpp ../include/npy.hpp
	g++ -o test -Wall -Wpedantic -Wextra -std=c++11 -I../include test.cpp

data/%.npy: createnpy.py
	mkdir -p data
	python3 createnpy.py

clean:
	rm test
	rm -r data
