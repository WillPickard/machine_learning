all: linear_regression_vector_only.cpp
	g++ -o main linear_regression_vector_only.cpp

generator: generate_training_file.cpp
	g++ -o gen generate_training_file.cpp

run: all
	./main

run_gen: generator
	./gen