//linear_regression.cpp
/************
*
*	Trying to implement logistic regression or classification, without vectorization
*	
*	Three main functions:
*		h(x) - hypothesis
*		j(x) - error function, cost function
*		linear regression - minimizing theta for j(x)
*
*
*************/
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <exception>
#include <unistd.h>

using namespace std;

const char * TRAINING_FILE = "test.txt";

const double PRECISION = 0.0000000000000001;
const double ALPHA = 0.00000118;
static int ITERS = 0;

class SetSizeException : public exception
{
	public:
		SetSizeException(){};

		virtual const char * what() const throw()
		{
			return "Invalid size";
		}

};

double multiplyVector(vector<double> a, vector<double> b);

double multiplyVector(double, vector<double>);

double h(const vector<double>, vector<double>);

double cost(const vector<double>, vector< vector<double> >, vector<double>);

void gradientDescent(double, vector<double> *, vector< vector<double> >, vector<double>);

//split a string on the delimeter
vector<string> split(char, string);

double parseDouble(string);

const string stringifyEquation(vector<double>);

int main(int argc, const char * argv[])
{
	//start by reading from the file
	//basic right now, we are reading from a file where each line represents an example
	//first column is the input and second column is the output
	
	vector<double> coefficients;
	vector< vector<double> > inputs;
	vector<double> outputs;

	ifstream file (TRAINING_FILE);

	if(!file.is_open())
	{
		cout << "could not open file" << endl;
		return 1;
	}

	string line;
	while(getline(file, line))
	{
		vector<string> s = split(' ', line);

		vector<double> lineinput; //the inner vector in the 2d vector inputs
		//the first value in each vector must be a 1
		lineinput.push_back(1.0);
		for(int i = 0; i < s.size() - 1; i++)
		{	
			double value = parseDouble(s.at(i));
			lineinput.push_back(value);
		}
		inputs.push_back(lineinput);
		outputs.push_back(parseDouble(s.at(s.size() - 1)));
	}
	file.close();
	
	//init coefficients
	for(int i = 0; i < inputs.at(0).size(); i++)
	{
		coefficients.push_back(0);
	}

	for(int i = 0; i < inputs.size(); i++)
	{
		for(int j = 0; j < inputs.at(i).size(); j++)
		{
			cout << inputs.at(i).at(j) << " ";
		}
		cout << " - " << outputs.at(i) << endl;
	}
	cout << setprecision(24) << M_E << endl;
	//return 0;
	cout << "calc gradientDescent" << endl;
	
	gradientDescent(ALPHA, &coefficients, inputs, outputs);	
	cout << "done" << endl;

	cout << "obtained equation: " << endl;
	cout << stringifyEquation(coefficients) << endl;
	cout << "total iterations: " << ITERS << endl;

	cout << "enter " << coefficients.size() - 1 << " input variables (seperated by space) for guess: " << endl;

	while(1)
	{
		getline(cin, line);
		//cout << "top while" << endl;
		vector<string> s = split(' ', line);
		vector<double> given;
		given.push_back(1.0);

		for(int i = 0; i < s.size(); i++)
		{
			given.push_back(parseDouble(s.at(i)));
		}

		double answer = h(coefficients, given);
		cout << "guess: " << answer << endl;
	}

	return 0;
}

const string stringifyEquation(vector<double> coefficients)
{
	stringstream s;
	for(int i = 0; i < coefficients.size(); i++)
	{
		if(i == 0)
			s << "(" << coefficients.at(i) << " * x" << i << ") ";
		else
			s << "+ (" << coefficients.at(i) <<  " * x"  << i << ") ";
	}

	return s.str();
}

double multiplyVector(vector<double> a, vector<double> b)
{
	double result = 0.0;

	if(a.size() != b.size())
	{
		throw new SetSizeException();
	}

	for(int i = 0; i < a.size(); i++)
	{
		result += a.at(i) * b.at(i);
	}

	return result;
}

double multiplyVector(double a, vector<double> b)
{
	double result = 0.0;
	for(int i = 0; i < b.size(); i++)
	{
		result += (a * b.at(i));
	}

	return result;
}

/****
* Hypthothesis 
*	htheta(x) = (1/1 + e ^ (-theta transpose x))
*	The result is the probability b/w [0,1] that the input is 1
******/
double h(const vector<double> coefficients, vector<double> inputs)
{
	double estimate = 0.0;
	int n = inputs.size();

	double mvr = multiplyVector(coefficients, inputs); //mvr is the result of multiplying the coefficients vector with the input vector
	double result;
	for(int i = 0; i < n; i++)
	{	
		result = (1/(1 + (pow(M_E, (-1 * mvr))))); // 1/1+ e^(theta traspose x)
	//	cout << setprecision(64) << "( " << coefficients.at(i) << " * " << inputs.at(i) << " ) + ";
		estimate += result;
	}

	//cout << " = " << estimate << endl;
	return estimate;
}

/***
* Cost function 
*	
****/
double cost(const vector<double> coefficients, vector< vector<double> > inputs, vector<double> outputs)
{

	double cost = 0.0;
	double error;
	int m = inputs.size();

	for(int i = 0; i < m; i++)
	{	
		error = ( (h(coefficients, inputs.at(i)) - outputs.at(i)) );
		//cout << "goal : " << outputs.at(i) << endl;
		//cout << "error : " << error << endl;
		cost += error;
	}
	
	//cout << "cost: " << cost << endl;
	//sleep(1);
	return cost;
}

void gradientDescent(double alpha, vector<double> * coefficients, vector< vector<double> > inputs, vector<double> outputs)
{
	double last, current, precision, error;

	//bool converged = false;
	double m = inputs.size();
	last = 0;
	current = 10;
	vector<double> update;

	double lastError, thisError = 0.0;

	for(int i = 0; i < coefficients->size(); i++)
	{
		update.push_back( coefficients->at(i) );
	}

	error = 1;
	//int iters = 0;
	//while(fabs(current - last) > PRECISION)
	while(current != last)
	{
		//cout << "current " << current << endl;
		last = current;
		current = 0.0;
		lastError = fabs(error);

		for(int j = 0; j < coefficients->size(); j++)
		{
			error = ( alpha * (1/m) * multiplyVector( cost(*coefficients, inputs, outputs), inputs.at(j)) );
			update.at(j) = update.at(j) - error;
			//cout << "\tupdate.at(" << j << ") : " << update.at(j) << endl;
		}

		//update the actual coefficients
		for(int j = 0; j < coefficients->size(); j++)
		{
			coefficients->at(j) = update.at(j);
			current += coefficients->at(j);

		}

		ITERS++;
		if(ITERS % 10000 == 0)
		{
			cout << "iteration: " << ITERS << ", error: " << setprecision(256) << error << " | error - lastError: " << (fabs(error) - lastError) << endl;
		}
		//cout << "fabs(current - last) : " << fabs(current - last) << endl;
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
		//	while(target[i] == delimeter) i++;
		}
		else
		{
			current += target[i];			
		}
	}

	result.push_back(current);

	return result;
}