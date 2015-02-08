all: logistic_regression.cpp
	g++ -o main logistic_regression.cpp

generator: generate_training_file.cpp
	g++ -o gen generate_training_file.cpp

run: all
	./main

run_gen: generator
	./gen