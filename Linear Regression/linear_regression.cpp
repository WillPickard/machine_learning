//linear_regression.cpp
/************
*
*	Trying to implement linear regression without vectorization
*	
*	Three main functions:
*		h(x) - hypothesis
*		j(x) - error function, cost function
*		linear regression - minimizing theta for j(x)
*
*		h(x) = h theta (x) = theta transpose x = sum i=1:n (theta(i) * x(i) where n = number of input features
*		j(x) = (1/2)(1/m)(sum i=0:m(( h(x(i))) - y(i)) ^ 2 )) 
*		linear regression is too complicated to type out in this shitty notation
*
*************/
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

const char * TRAINING_FILE = "training_examples.txt";

class SetSizeException : public exception
{
	public:
		EqualSizeException(){};

		virtual const char * what() const throw()
		{
			return "Invalid size";
		}

};

struct TrainingExample
{
	vector<double> inputs;
	double output;
};

struct TrainingExamples
{
	vector<TrainingExample> examples;
	int size;

	TrainingExamples()
	{
		size = 0;
	}

	TrainingExamples(vector<TrainingExample> e):
		examples(e)
		{
			size = e.size();
		}

	void add(TrainingExample t)
	{
		examples.push_back(t);
		size++;
	}
};

struct Theta
{
	double value;
};

struct Thetas
{
	vector<Theta> values;
	int size;
	Thetas()
		{
			size = 0;
		}

	Thetas(vector<Theta> t):
		values(t)
		{
			size = t.size();
		}

	vector<double> getVector()
	{
		vector<double> res;
		for(int i = 0; i < values.size(); i++)
		{
			res.push_back(values.at(i).value);
		}

		return res;
	}
};

struct TrainingSet
{
	Thetas * thetas;
	TrainingExamples * examples;

	TrainingSet(Thetas * t, TrainingExamples * e):
		thetas(t),
		examples(e)
		{};
};

double transpose(vector<double>, vector<double>);

//hypothesis : return a (vector>) guess of a value from being passed avector of inputs and outputs
double h(TrainingExample *, Thetas *);

double j(TrainingSet *);

//gradient descent: return an vector of thetas whose index correspond with the theta, from being passed in a (double) alpha value, (int) number of training examples,	
// 	(double *) array of input features, and (double *) array of actual output answers
void gradientDescent(double, TrainingSet *);

//split a string on the delimeter
vector<string> split(char, string);

double parseDouble(string);


int main(int argc, const char * argv[])
{
	//start by reading from the file
	//basic right now, we are reading from a file where each line represents an example
	//first column is the input and second column is the output
	double * examples = 0;

	ifstream file (TRAINING_FILE);
	string line;

	if(!file.is_open())
	{
		cout << "could not open file" << endl;
		return 1;
	}

	//vector of training examples

	struct TrainingExamples * trainingExamples = new TrainingExamples();
	struct Thetas * thetas = new Thetas();

	cout << "extracting lines" << endl;
	while(getline(file, line))
	{
		struct TrainingExample t;
		vector<string> s = split(' ', line);

		for(int i = 0; i < s.size() - 1; i++)
		{	
			cout << "line " << i << " : " << s.at(i) << endl;
			t.inputs.push_back(parseDouble(s.at(i)));
		}

		t.output = parseDouble(s.at(s.size() - 1));

		trainingExamples->add(t);
	}
	file.close();
	cout << "done with file" << endl;
	//init the thetas to 0s, there should be 1 more theta than there are input variables
	for(int i = 0; i < trainingExamples->examples.at(0).inputs.size() + 1; i++)
	{
		Theta t;
		t.value = 0;
		thetas->values.push_back(t);
	}

	thetas->size = thetas->values.size();
	
	cout << "done setting up shit" << endl;

	TrainingSet * set = new TrainingSet(thetas, trainingExamples);
	cout << "about to calc gradientDescent" << endl;
	gradientDescent(0.01, set);

	cout << "done" << endl;
	cout << "calculated theta values: " << endl;

	thetas = set->thetas;
	for(int i = 0; i < thetas->size; i++)
	{
		cout << "\t" << i << " : " << thetas->values.at(i).value << endl;
	}

	//set.

/*
	//initialize all the thetas to 0
	vector<double> thetas;
	vector<double> inputs;
	vector<double> outputs;

	//initialize the vectors
	//thetas and inputs start with an extra
	thetas.push_back(0); //all thetas need to be 0
	inputs.push_back(1); //x0 is always 1
	for(int i = 0; i < numExamples; i++)
	{
		thetas.push_back(0);
		inputs.push_back(trainingExamples.at(i).input);
		outputs.push_back(trainingExamples.at(i).output);
	}
*/
	
	return 0;
}

double transpose(vector<double> a, vector<double> b)
{
	double result = 0;

	if(a.size() != b.size())
	{
		cout << "you fucked up" << endl;
		throw new SetSizeException();
	}

	cout << "transpose" << endl;
	int size = a.size();
	for(int i = 0; i < size; i++)
	{
		result += a.at(i) * b.at(i);
	}

	return result;
}

double h(TrainingExample * e, Thetas * t)
{
	return transpose(e->inputs, t->getVector());
}

double j(TrainingSet * set)
{
	double value = 0;
	double squaredError = 0;

	TrainingExamples * e = set->examples;
	Thetas * t = set->thetas;

	int numExamples = e->size;

	//do it for each example
	for(int i = 0; i < numExamples; i++)
	{
		TrainingExample te = e->examples.at(i); 
		squaredError = pow(h(&te, t) - te.output, 2);
		value += squaredError;
	}

	return ((1/2) * (1/numExamples) * value);
}

void gradientDescent(double alpha, TrainingSet * s)
{
	cout << "calculating gradientDescent with alpha = " << alpha << endl;
	Thetas * thetas = s->thetas;
	int numThetas = thetas->size;

	TrainingExamples * trainingExamples = s->examples;
	int m = trainingExamples->size;

	bool converged = false;
	//double prevMin = 0;
	//double currentMin = 0;
	double output, hVal, thetaValue, totalError;

	vector<double> thetaValues = thetas->getVector();

	double precision = 0.0001;

	cout << "top while" << endl;
	while(!converged)
	{
		for(int j = 0; j < numThetas; j++)
		{	
			cout << "j: " << j << " " << endl;
			totalError = 0;
			Theta theta = thetas->values.at(j);
			thetaValue = thetaValues.at(j);
			TrainingExample jExample = trainingExamples->examples.at(j);
			for(int i = 0; i < m; i++)
			{
				cout << "\ti: " << i << endl;
				TrainingExample example = trainingExamples->examples.at(i);
				output = example.output;
				hVal = h(&example, thetas);
				totalError += ((hVal - output) * jExample.inputs.at(i));
			}

			totalError = (totalError * ( (alpha) * (1/m) ));
			cout << "totalError : " << totalError << endl;
			thetaValues.at(j) = (thetaValues.at(j) - totalError);
			if(totalError < precision)
			{
				converged = true;
			}
			cout << endl;
		}
		//now update the global theta values inside thetas
		for(int j = 0; j < numThetas; j++)
		{
			thetas->values.at(j).value = thetaValues.at(j);
		}
	}
}

double parseDouble(string target)
{
	istringstream iss;
	iss.exceptions(istream::failbit | istream::badbit );

	iss.str(target);
	double dTemp = 0;

	iss >> dTemp;

	return dTemp;
}

vector<string> split(char delimeter, string target)
{
	vector<string> result;

	string current = "";
	for(int i = 0; i < target.length(); i++)
	{
		if(target[i] == delimeter)
		{
			result.push_back(current);
			current = "";
		}
		else
		{
			current += target[i];			
		}
	}

	result.push_back(current);

	return result;
}