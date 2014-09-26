/*
 ============================================================================
 Name        : TMH_Examples.c
 Author      : Tomasz Strzałka
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#include <TMHLogger.h>
#include <TMH_API.h>

void loopTest( int i, int j );
void test( int j );
void makeTest();

int main(void) {
	enableLog(ALL,false);
	enableSaveLog("templog",true);
	loopTest(1,1);
	return EXIT_SUCCESS;
}

void loopTest( int i, int j ) {
	double s,e;
	for ( ; i > 0 ; i -= 1 ) {
		s = clock();
		test(j);
		e = clock();
		printf("%f\n",e-s);
	}
}

void test( int j ) {
	for ( ; j > 0 ; j -= 1 ) {
		makeTest();
	}
}

void makeTest() {
	void* ins = createTMHAlgorithmInstance(BFM,
			"/home/tomasz/workspace/TMH_Tests/gr/testTMH.gr",
			"/home/tomasz/workspace/TMH_Tests/ss/test.ss",false,false);
	runTMHAlgorithm(BFM,ins);
	destroyTMHBFMInstance(ins);

	ins = createTMHAlgorithmInstance(BFP,
		"/home/tomasz/workspace/TMH_Tests/gr/testTMH.gr",
		"/home/tomasz/workspace/TMH_Tests/ss/test.ss",false,false);
	runTMHAlgorithm(BFP,ins);
	destroyTMHBFPInstance(ins);

	ins = createTMHAlgorithmInstance(DKQ,
			"/home/tomasz/workspace/TMH_Tests/gr/testTMH.gr",
			"/home/tomasz/workspace/TMH_Tests/ss/test.ss",false,false);
	runTMHAlgorithm(DKQ,ins);
	destroyTMHDKQInstance(ins);

	ins = createTMHAlgorithmInstance(DKA,
			"/home/tomasz/workspace/TMH_Tests/gr/testTMH.gr",
			"/home/tomasz/workspace/TMH_Tests/ss/test.ss",false,false);
	runTMHAlgorithm(DKA,ins);
	destroyTMHDKAInstance(ins);

	ins = createTMHAlgorithmInstance(DKB,
			"/home/tomasz/workspace/TMH_Tests/gr/testTMH.gr",
			"/home/tomasz/workspace/TMH_Tests/ss/test.ss",false,false);
	runTMHAlgorithm(DKB,ins);
	destroyTMHDKBInstance(ins);

	ins = createTMHAlgorithmInstance(DKM,
			"/home/tomasz/workspace/TMH_Tests/gr/testTMH.gr",
			"/home/tomasz/workspace/TMH_Tests/ss/test.ss",false,false);
	runTMHAlgorithm(DKM,ins);
	destroyTMHDKMInstance(ins);

	ins = createTMHAlgorithmInstance(DKD,
			"/home/tomasz/workspace/TMH_Tests/gr/testTMH.gr",
			"/home/tomasz/workspace/TMH_Tests/ss/test.ss",false,false);
	runTMHAlgorithm(DKD,ins);
	destroyTMHDKDInstance(ins);

	ins = createTMHAlgorithmInstance(DKF,
			"/home/tomasz/workspace/TMH_Tests/gr/testTMH.gr",
			"/home/tomasz/workspace/TMH_Tests/ss/test.ss",false,false);
	runTMHAlgorithm(DKF,ins);
	destroyTMHDKFInstance(ins);
}
