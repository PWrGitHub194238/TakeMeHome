/*
 ============================================================================
 Name        : TMH_Examples.c
 Author      : Tomasz Strzałka
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <TMH_API.h>
#include <TMHConfig.h>
#include <TMHLogger.h>

#include <TMHGraph.h>

#include <DKQs.h>

void loopTest( int i, int j );
void test( int j );
void makeTest();

int main(void) {
	//enableLog(ALL,false);
	disableLog();
	//enableSaveLog("templog",true);
	loopTest(1,1);
	return EXIT_SUCCESS;
}

void loopTest( int i, int j ) {
	double s,e;
	void* ins;
	TMHConfig* config;

	for ( ; i > 0 ; i -= 1 ) {

		/*s = clock();
		config = createTMHConfig("/home/tomasz/workspace/TMH_Tests/ss/test.ss");

		setAllowInterrupt(config,false);
		setCheckConfig(config,false);
		setGraphOrder(config,NONE);
		setGraphStruct(config,ADJACENCY_LIST);

		setAlgorithm(config,BFM);

		ins = createTMHAlgorithmInstance(config,
				"/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.NY.gr");

		onlyAlgorithm(config->algorithm,ins);
		destroyTMHAlgorithmInstancje(config->algorithm,ins,false);
		destroyTMHConfigInstance(config);
		e = clock();

		printf("%f\n",e-s);*/


		loadTest("/home/tomasz/workspace/TMH_Tests/gr/testTMH1.gr",THR);

		loadTest("/home/tomasz/workspace/TMH_Tests/gr/testTMH1.gr",THR);

		loadTest("/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.NY.gr",THR);

		loadTest("/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.BAY.gr",THR);

		loadTest("/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.COL.gr",THR);

		loadTest("/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.FLA.gr",THR);

		loadTest("/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.NW.gr",THR);

		loadTest("/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.NE.gr",THR);

		loadTest("/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.CAL.gr",THR);

		loadTest("/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.LKS.gr",THR);

		loadTest("/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.E.gr",THR);

		loadTest("/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.W.gr",THR);

		loadTest("/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.CTR.gr",THR);

		loadTest("/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.USA.gr",THR);
	}
}

void loadTest( char* path, const AlgorithmAbbreviation alg ) {
	void* ins;
	double s1,s2,s3,e1,e2,e3;

	TMHConfig* config = createTMHConfig("/home/tomasz/workspace/TMH_Tests/ss/test.ss");
	TMHNodeData* param = NULL;/* malloc(sizeof(TMHNodeData));
	*param = 8;*/
	setAllowInterrupt(config,false,param);
	setCheckConfig(config,false);
	setGraphOrder(config,NONE);
	setGraphStruct(config,ADJACENCY_LIST);

	setAlgorithm(config,alg);

	s1 = clock();

	ins = createTMHAlgorithmInstance(config,path);

	e1 = clock();

	/*printf("%s:\nNodes\t:\t%u\nArcs\t:\t%u",path,((TMH_BFM*)ins)->graphData->numberOfNodes,((TMH_BFM*)ins)->graphData->numberOfArcs);
*/
	printf("%s %f ",path,e1-s1);

	s2 = clock();

	onlyAlgorithm(config->algorithm,ins);

	e2 = clock();

	s3 = clock();

	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	e3 = clock();

	destroyTMHConfigInstance(config);

	printf("%f ",e2-s2);
	printf("%f\n",e3-s3);

	if ( param != NULL ) {
		free(param);
	}
}

void test( int j ) {
	for ( ; j > 0 ; j -= 1 ) {
		makeTest();
	}
}

void onlyAlgorithm( AlgorithmAbbreviation algorithm, void* instance ) {
	runTMHAlgorithm(algorithm,instance);
}

void makeTest() {
	void* ins = NULL;
	TMHConfig* config = createTMHConfig("/home/tomasz/workspace/TMH_Tests/ss/test.ss");

	TMHNodeData* param = NULL; // malloc(sizeof(TMHNodeData));
//	*param = 2;
	setAllowInterrupt(config,false,param);
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

	setAlgorithm(config,DKQs);
	ins = createTMHAlgorithmInstance(config,
			"/home/tomasz/workspace/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	setAlgorithm(config,DKQd);
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

	setAlgorithm(config,DKF);
	ins = createTMHAlgorithmInstance(config,
			"/home/tomasz/workspace/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	setAlgorithm(config,DKH);
	ins = createTMHAlgorithmInstance(config,
			"/home/tomasz/workspace/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	setAlgorithm(config,DKR);
	ins = createTMHAlgorithmInstance(config,
			"/home/tomasz/workspace/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

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

	setAlgorithm(config,THR);
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
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	destroyTMHConfigInstance(config);
}
