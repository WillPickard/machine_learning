In this folder I am trying to implement linear regression with some different machine learning techniques.

In linear_regression.cpp I tried to use structs to encapsulate different things. 
It did not go well. It made it way too complicated. But from spending 
so much time trying to debug, I was able to better understand
the concepts that I was trying to implement. 

In linear_regression_vector_only.cpp I just use c++11 vectors instead of
all of the structs in linear_regression.cpp. This made it much easier. 
The main method in this file, reads from a file, extracts the inputs
and the outputs, and uses gradientDescent() to minimize the standard
error of the hypothesis result compared to the actual output. 

The input file is defined as a const string at the top of linear_regression_vector_only.cpp.
A valid file has the following format:

	x1 x2 x3 ... xn y0
	x1 x2 x3 ... xn y1
	...	... ... ... ym

	Where the x variables are the input variables which produce the y variable.
	n is the number of input variables and m is the number of training examples.
	The values of these variables must be numbers. The datatype in the linearRegression
	algorithm is double.

gradientDescent() manipulates a vector of "theta" values to form a linear equation which models
the equation.

After gradientDescent() returns, a vector of theta values of size n. If n = 3, then the theta vector represents
coeffecients for a linear equation of the form:

	(t0 * x0) + (t1 * x1) +  (t2 * x2) + (t3 * x3)

	x0 is always 1.
	
The user is then prompted to enter n variables when are then used in the hypothesis (equation above) to produce a prediction.

Will Pickard