Implementing logistic regression or classification

This is very similar to my implementation of linear regression, in fact few changes needed to be made

This biggest difference was the hypothesis.
	In logistic regression the hypothesis is a probability that a given input can be classified in a binary choice
	In other words, the output of the hypothesis is a probability in [0, 1] that the input can be classified as a 1.
	For example, the test.txt file has two columns. In the first column is some number, in the second is a 1 or 0.
	The second column represents the classification. Here it is whether the value in the first column is less than 100.
	1 means that it is less than 100, 0 means it is greater than 100.


Like in the linear regression implementation, I went ahead and defined the problem with the partial derivative of the gradient descent function calculated.

The actual implementation of logistic gradient descent would be like:
	theta.j = theta.j - (alpha * partial_derivative_with_respect_to(J(theta)))
		where J(theta) = (-1/m)(sum( y_i * log(1/h(x_i) + (1 - y_i * (1 - log(h(x_i))))))) 
	for all j

However, when you compute the partial derivative, you get the same representation of gradient descent for logistic regression as you do linear regression

