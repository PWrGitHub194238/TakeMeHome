//============================================================================
// Name        : Tempcpp.cpp
// Author      : Tomasz Strzałka
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C<<<<, Ansi-style
//============================================================================

#include <stdio.h>		/* sprintf */
#include <stdlib.h>     /* srand, rand */
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>

#include <random>

std::knuth_b rand_engine;  // replace knuth_b with one of the engines listed below

bool random_bool_with_prob( double prob )  // probability between 0.0 and 1.0
{
    std::bernoulli_distribution d(prob);
    return d(rand_engine);
}
using namespace std;


const string COMMENT_FLAG = "c";
const string PROBLEM_DEFFINITION_FLAG = "p";
const string ARC_FLAG = "p";

const string SP_PROBLEM = "sp";
const string NEWLINE = "\n";

int main() {
	srand (time(NULL));

	int N,M;
	double p;

	ofstream writer,writer2;
	writer2.open("log");
	for ( N = 100; N <= 8000; N += 100 ) {
	char fName [50];

	for (int i = 0; i <=5; i+=1 ) {
		p = 2.0 - i*0.2;
		M = pow(N,p);
		double pr = M/pow(N,2.0);
		sprintf (fName, "N_%d_p_%.2f_M_%d.gr", N, p, M);

		writer.open (fName);
		writer2 << "\"/home/s194238/TMH/TMH_Tests/gr/Test1/" << fName << "\",\n";

		writer << PROBLEM_DEFFINITION_FLAG << " "
							<< SP_PROBLEM << " "
							<< N << " "
							<< M << " "
							<< NEWLINE;

		writer << COMMENT_FLAG << " graph contains "
							<< N << " nodes and "
							<< M << " arcs"
							<< NEWLINE;

		writer << COMMENT_FLAG << " Dence: V^(" << p << ") " << NEWLINE;

		writer << COMMENT_FLAG << NEWLINE;
		for (  int i = 1; i <= N; i+=1 ) {
			for (  int j = 1; j <= N; j+=1 ) {
				if (random_bool_with_prob(pr) == true ) {
					writer << "a " << i << " " << j << " " << (rand() % 1000 + 1) << NEWLINE;
				}
			}
		}
		writer.close();
		}
	}
	writer2.close();

	return 0;
}
