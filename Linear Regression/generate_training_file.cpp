#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;

const char * filename = "f10.txt";//"isRed.txt"; //sums.txt"; //powers.txt";

const int MAX = 1000000;

int main(int argc, const char * argv[])
{
	ofstream file (filename);

	/** powers.txt
	for(int i = 0; i < MAX; i++)
	{
		file << i << " " << pow(i, 2) << endl;
	}	
	**/

	/** sums.txt **
	for(int i = 0; i < MAX; i++)
	{
		file << i << " " << i << " " << (i + i) << endl;
	}
	/***/

	/** isRed.txt **
	srand(time(NULL));
	for(int i = 0; i < MAX; i++)
	{
		int isRed = rand() % 2;
		int r, g, b;
		if(isRed == 1)
		{
			r = rand() % 56 + 200;
			g = rand() % 150;
			b = rand() % 150;
			file << r << " " << g << " " << b << " " << "1" << endl;
		}
		else
		{
			r = rand() % 56;
			g = rand() % 200 + 55;
			b = rand() % 200 + 55;
			file << r << " " << g << " " << b << " " << "0" << endl;
		}
	}
	/**/

	/** f10.txt **/
	int local;
	int now;
	for(int i = 0; i < MAX; i++)
	{	
		local = 0;
		now = i;
		for(i; i < now + 10; i++)
		{
			file << i << " ";
			local += i;
		}
		file << local << endl;
	}
	/***/
	file.close();	
}