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
	void* ins = NULL;
	TMHConfig* config = createTMHConfig("/home/tomasz/workspace/TMH_Tests/ss/test.ss");

	setAllowInterrupt(config,false);
	setCheckConfig(config,false);
	setGraphOrder(config,NONE);
	setGraphStruct(config,ADJACENCY_LIST);

	setAlgorithm(config,BFM);
	ins = createTMHAlgorithmInstance(config,
			"/home/tomasz/workspace/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	setAlgorithm(config,BFP);
	ins = createTMHAlgorithmInstance(config,
			"/home/tomasz/workspace/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	setAlgorithm(config,DKQ);
	ins = createTMHAlgorithmInstance(config,
			"/home/tomasz/workspace/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	setAlgorithm(config,DKB);
	ins = createTMHAlgorithmInstance(config,
			"/home/tomasz/workspace/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	setAlgorithm(config,DKM);
	ins = createTMHAlgorithmInstance(config,
			"/home/tomasz/workspace/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	setAlgorithm(config,DKA);
	ins = createTMHAlgorithmInstance(config,
			"/home/tomasz/workspace/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	setAlgorithm(config,DKD);
	ins = createTMHAlgorithmInstance(config,
			"/home/tomasz/workspace/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	/*setAlgorithm(config,DKF);
	ins = createTMHAlgorithmInstance(config,
			"/home/tomasz/workspace/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);*/

	/*setAlgorithm(config,DKH);
	ins = createTMHAlgorithmInstance(config,
			"/home/tomasz/workspace/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	setAlgorithm(config,DKR);
	ins = createTMHAlgorithmInstance(config,
			"/home/tomasz/workspace/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);*/

	setAlgorithm(config,PAP);
	ins = createTMHAlgorithmInstance(config,
			"/home/tomasz/workspace/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	setAlgorithm(config,TQQ);
	ins = createTMHAlgorithmInstance(config,
			"/home/tomasz/workspace/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,true);

	/*setAlgorithm(config,THR);
	ins = createTMHAlgorithmInstance(config,
			"/home/tomasz/workspace/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	setAlgorithm(config,GR1);
	ins = createTMHAlgorithmInstance(config,
			"/home/tomasz/workspace/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	setAlgorithm(config,GR2);
	ins = createTMHAlgorithmInstance(config,
			"/home/tomasz/workspace/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);*/



	destroyTMHConfigInstance(config);
}
