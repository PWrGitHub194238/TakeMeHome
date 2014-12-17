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

static long long int getSumOfArcAndNodes( char* path );


const int REPEAT = 1;

const int TESTSNO = 10;

const char* TESTPATHS[10] = {
		"/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.NY.gr",
		"/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.BAY.gr",
		"/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.COL.gr",
		"/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.FLA.gr",
		"/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.NW.gr",
		"/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.NE.gr",
		"/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.CAL.gr",
		"/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.LKS.gr",
		"/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.E.gr",
		"/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.W.gr",/*
		"/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.CTR.gr",
		"/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.USA.gr"*/
};

const char* SAVEPATH = "/home/tomasz/workspace/TMH_Tests/tests";

int main(void) {
//	enableLog(TRACE,false);
	disableLog();
//	enableSaveLog("templog",true);
	//loopTest(1,1);

	//loadTest("/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.NW.gr",DKXb);

	finalTest(TESTPATHS,TESTSNO,"USATest",DKA,NULL,"DKA");
	//finalTest(TESTPATHS,TESTSNO,"USATest",PAP,NULL,"PAP");
	//finalTest(TESTPATHS,TESTSNO,"USATest",TQQ,NULL,"TQQ");

	finalTest(TESTPATHS,TESTSNO,"USATest",DDL,NULL,"DDL");
	finalTest(TESTPATHS,TESTSNO,"USATest",DKD,NULL,"DKD");
	finalTest(TESTPATHS,TESTSNO,"USATest",DKM,NULL,"DKM");
	finalTest(TESTPATHS,TESTSNO,"USATest",DKX,NULL,"DKX");
//	finalTest(TESTPATHS,TESTSNO,"USATest",DKXb,NULL,"DKXb");
	finalTest(TESTPATHS,TESTSNO,"USATest",DKFb,NULL,"DKFb");
	finalTest(TESTPATHS,TESTSNO,"USATest",DKR,NULL,"DKR");

	return EXIT_SUCCESS;
}

void finalTest( char** paths, int noOfTests, char* testName, const AlgorithmAbbreviation alg, TMHNodeData* param, char* algName ) {
	void* ins;
	double sC[REPEAT],sR[REPEAT],sD[REPEAT],eC[REPEAT],eR[REPEAT],eD[REPEAT];
	double AC,AR,AD;
	char cBuf[100],rBuf[200],dBuf[200],pcBuf[200],prBuf[200],pdBuf[200];
	FILE* cFile = NULL;
	FILE* rFile = NULL;
	FILE* dFile = NULL;

	FILE* pcFile = NULL;
	FILE* prFile = NULL;
	FILE* pdFile = NULL;

	int i,j;
	char* path;
	long long int numOfVE;
	TMHConfig* config = createTMHConfig("/home/tomasz/workspace/TMH_Tests/ss/test.ss");
	setAllowInterrupt(config,false,param);
	setCheckConfig(config,false);
	setGraphOrder(config,NONE);
	setGraphStruct(config,ADJACENCY_LIST);

	setAlgorithm(config,alg);

	sprintf (cBuf, "%s/C_%s_%s",SAVEPATH,testName,algName);
	sprintf (rBuf, "%s/R_%s_%s",SAVEPATH,testName,algName);
	sprintf (dBuf, "%s/D_%s_%s",SAVEPATH,testName,algName);

	for ( i = 0; i < noOfTests; i += 1) {
		cFile = fopen(cBuf,"a");
		rFile = fopen(rBuf,"a");
		dFile = fopen(dBuf,"a");
		path = paths[i];
		sprintf (pcBuf, "%s/pC_%s_%s_%d",SAVEPATH,testName,algName,i);
		sprintf (prBuf, "%s/pR_%s_%s_%d",SAVEPATH,testName,algName,i);
		sprintf (pdBuf, "%s/pD_%s_%s_%d",SAVEPATH,testName,algName,i);

		numOfVE = getSumOfArcAndNodes(path);
		printf("Run\t:\t %s\nfor\t:\t%s (%d / %d)\n",algName,path,i+1,noOfTests);
		for ( j = 0; j < REPEAT; j += 1 ) {
			pcFile = fopen(pcBuf,"a");
			prFile = fopen(prBuf,"a");
			pdFile = fopen(pdBuf,"a");
			printf("Start (%d /%d)...",j+1,REPEAT);
			sC[j] = clock();
			ins = createTMHAlgorithmInstance(config,path);
			eC[j] = clock();
			sR[j] = clock();
			onlyAlgorithm(config->algorithm,ins);
			eR[j] = clock();
			sD[j] = clock();
			destroyTMHAlgorithmInstancje(config->algorithm,ins,false);
			eD[j] = clock();

			fprintf(pcFile, "%f\n", eC[j]-sC[j]);
			fprintf(prFile, "%f\n", eR[j]-sR[j]);
			fprintf(pdFile, "%f\n", eD[j]-sD[j]);

			fclose(pcFile);
			fclose(prFile);
			fclose(pdFile);

			printf("OK\n");
		}
		AC = 0;
		AR = 0;
		AD = 0;
		for ( j = 0; j < REPEAT; j += 1 ) {
			AC += (eC[j]-sC[j])/REPEAT;
			AR += (eR[j]-sR[j])/REPEAT;
			AD += (eD[j]-sD[j])/REPEAT;
		}

		fprintf(cFile, "%lld %f\n", numOfVE, AC);
		fprintf(rFile, "%lld %f\n", numOfVE, AR);
		fprintf(dFile, "%lld %f\n", numOfVE, AD);


		fclose(cFile);
		fclose(rFile);
		fclose(dFile);
		printf("Save done.\n\n");

	}
	destroyTMHConfigInstance(config);

	if ( param != NULL ) {
		free(param);
	}
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


		loadTest("/home/tomasz/workspace/TMH_Tests/gr/testTMH1.gr",DKXb);

		loadTest("/home/tomasz/workspace/TMH_Tests/gr/testTMH1.gr",DKXb);

		loadTest("/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.NY.gr",DKXb);

		loadTest("/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.BAY.gr",DKXb);

		loadTest("/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.COL.gr",DKXb);

		loadTest("/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.FLA.gr",DKXb);

		loadTest("/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.NW.gr",DKXb);

		loadTest("/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.NE.gr",DKXb);

		loadTest("/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.CAL.gr",DKXb);

		loadTest("/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.LKS.gr",DKXb);

		loadTest("/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.E.gr",DKXb);

		loadTest("/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.W.gr",DKXb);

		loadTest("/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.CTR.gr",DKXb);

		loadTest("/home/tomasz/workspace/TMH_Tests/gr/USA-road-d.USA.gr",DKXb);
	}
}

void loadTest( char* path, const AlgorithmAbbreviation alg ) {
	void* ins;
	double s1,s2,s3,e1,e2,e3;

	TMHConfig* config = createTMHConfig("/home/tomasz/workspace/TMH_Tests/ss/test.ss");
	TMHNodeData* param = malloc(sizeof(TMHNodeData));
	*param = 2;
	setAllowInterrupt(config,false,param);
	setCheckConfig(config,false);
	setGraphOrder(config,NONE);
	setGraphStruct(config,ADJACENCY_LIST);

	setAlgorithm(config,alg);

	s1 = clock();

	printf("SFSGDGDGSDFSFSF\n");
	ins = createTMHAlgorithmInstance(config,path);
	printf("SFSGDGDGSDFSFSF\n");

	e1 = clock();

	/*printf("%s:\nNodes\t:\t%u\nArcs\t:\t%u",path,((TMH_BFM*)ins)->graphData->numberOfNodes,((TMH_BFM*)ins)->graphData->numberOfArcs);
*/
	printf("%s %f ",path,e1-s1);

	s2 = clock();
	printf("A");
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


static const int C_LINE_ARGC = 0;
static const int P_LINE_ARGC = 2;
static long long int getSumOfArcAndNodes( char* path ) {
	TMHNodeIdx numberOfNodes;
	TMHNodeIdx numberOfArcs;

	FILE* dataFile = fopen(path,"r");
	while ( !feof(dataFile) ) {
		switch (fgetc(dataFile)) {
		case 'c':
			if ( fscanf(dataFile, "%*[^\n]\n") != C_LINE_ARGC ) {
				fclose(dataFile);
				return 0;
			}
			break;
		case 'p':
			if ( fscanf(dataFile," %*[^ ] %u %u\n",&numberOfNodes,&numberOfArcs) == P_LINE_ARGC ) {
				fclose(dataFile);
				return numberOfNodes + numberOfArcs;
			} else {
				fclose(dataFile);
				return 0;
			}
			break;
		}
	}
	fclose(dataFile);
	return 0;
}
