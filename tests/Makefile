
test: test.cpp ../npy.hpp f8.npy
	g++ -o test -Wall -Wpedantic -std=c++11 test.cpp

%.npy: createnpy.py
	python3 createnpy.py

.PHONY: clean

clean:
	rm test *npy
