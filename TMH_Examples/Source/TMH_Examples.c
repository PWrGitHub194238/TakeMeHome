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

const int TESTSNO = 12;
const char* TESTPATHS[12] = {
		"/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.NY.gr",
		"/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.BAY.gr",
		"/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.COL.gr",
		"/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.FLA.gr",
		"/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.NW.gr",
		"/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.NE.gr",
		"/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.CAL.gr",
		"/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.LKS.gr",
		"/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.E.gr",
		"/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.W.gr",
		"/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.CTR.gr",
		"/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.USA.gr"
};

const int TESTSNO1 = 30;

const char* TESTPATHS1[30] = {
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_100_p_1.60_M_1584.gr",
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_200_p_1.60_M_4804.gr",
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_300_p_1.60_M_9191.gr",
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_400_p_1.60_M_14564.gr",
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_500_p_1.60_M_20813.gr",
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_600_p_1.60_M_27863.gr",
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_700_p_1.60_M_35657.gr",
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_800_p_1.60_M_44151.gr",
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_900_p_1.60_M_53307.gr",
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_1000_p_1.60_M_63095.gr",
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_1100_p_1.60_M_73490.gr",
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_1200_p_1.60_M_84467.gr",
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_1300_p_1.60_M_96008.gr",
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_1400_p_1.60_M_108094.gr",
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_1500_p_1.60_M_120710.gr",
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_1600_p_1.60_M_133841.gr",
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_1700_p_1.60_M_147474.gr",
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_1800_p_1.60_M_161598.gr",
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_1900_p_1.60_M_176199.gr",
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_2000_p_1.60_M_191270.gr",
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_2100_p_1.60_M_206800.gr",
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_2200_p_1.60_M_222780.gr",
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_2300_p_1.60_M_239201.gr",
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_2400_p_1.60_M_256057.gr",
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_2500_p_1.60_M_273340.gr",
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_2600_p_1.60_M_291043.gr",
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_2700_p_1.60_M_309159.gr",
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_2800_p_1.60_M_327682.gr",
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_2900_p_1.60_M_346606.gr",
		"/home/s194238/TMH/TMH_Tests/gr/Test1/N_3000_p_1.60_M_365926.gr"
};

const char* SAVEPATH = "/home/s194238/TMH/TMH_Tests/out/USATest2";

int main(void) {
	enableLog(ALL,false);
	//disableLog();
	enableSaveLog("templog",true);
	//loopTest(1,1);

	//loadTest("/home/tomasz/workspace/TMH_Tests/gr/USA-road-d/USA-road-d.NY.gr",DKD);

//	loadTest("/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.NY.gr",DDL);
//	loadTest("/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.NY.gr",DKD);
//	loadTest("/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.NY.gr",DKM);
//	loadTest("/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.NY.gr",DKX);
//	loadTest("/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.NY.gr",DKXb);
//	loadTest("/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.NY.gr",DKFb);
	//loadTest("/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.NY.gr",DKA);

	//loadTest("/home/s194238/TMH/TMH_Tests/gr/testTMH1.gr",DKQd);

	//finalTest(TESTPATHS,TESTSNO,"USATest",PAP,NULL,"PAP");
	//finalTest(TESTPATHS,TESTSNO,"USATest",DKXb,NULL,"DKXb");

	finalTest(TESTPATHS,TESTSNO,"Test1",DKA,NULL,"DKA");
	finalTest(TESTPATHS,TESTSNO,"Test1",TQQ,NULL,"TQQ");
	finalTest(TESTPATHS,TESTSNO,"Test1",DDL,NULL,"DDL");
	finalTest(TESTPATHS,TESTSNO,"Test1",DKD,NULL,"DKD");
	finalTest(TESTPATHS,TESTSNO,"Test1",DKM,NULL,"DKM");
	finalTest(TESTPATHS,TESTSNO,"Test1",DKX,NULL,"DKX");
	finalTest(TESTPATHS,TESTSNO,"Test1",DKFb,NULL,"DKFb");
	finalTest(TESTPATHS,TESTSNO,"Test1",DKR,NULL,"DKR");
	finalTest(TESTPATHS,TESTSNO,"Test1",DKR,NULL,"THR");

	return EXIT_SUCCESS;
}

void finalTest( char** paths, int noOfTests, char* testName, const AlgorithmAbbreviation alg, TMHNodeData* param, char* algName ) {
	void* ins;
	clock_t sC[REPEAT],sR[REPEAT],sD[REPEAT],eC[REPEAT],eR[REPEAT],eD[REPEAT];
	double AC,AR,AD;
	char cBuf[100],rBuf[200],dBuf[200];


	//char  pcBuf[200],prBuf[200],pdBuf[200];
	//FILE* cFile = NULL;
	FILE* rFile = NULL;
	//FILE* dFile = NULL;

	//FILE* pcFile = NULL;
	//FILE* prFile = NULL;
	//FILE* pdFile = NULL;

	int i,j;
	char* path;
	long long int numOfVE;
	TMHConfig* config = createTMHConfig("/home/s194238/TMH/TMH_Tests/ss/USATest3.ss",true);

	setCheckConfig(config,false);
	setGraphOrder(config,NONE);
	setGraphStruct(config,ADJACENCY_LIST);

	setAlgorithm(config,alg);

	//sprintf (cBuf, "%s/C_%s_%s_100Nodes",SAVEPATH,testName,algName);
	sprintf (rBuf, "%s/R_%s_%s_1.60RETEST",SAVEPATH,testName,algName);
	//sprintf (dBuf, "%s/D_%s_%s_100Nodes",SAVEPATH,testName,algName);

	for ( i = 0; i < noOfTests; i += 1) {

		setAllowInterrupt(config,false,param);


		//cFile = fopen(cBuf,"a");
		rFile = fopen(rBuf,"a");
		//dFile = fopen(dBuf,"a");
		path = paths[i];
		//sprintf (pcBuf, "%s/pC_%s_%s_%d",SAVEPATH,testName,algName,i);
		//sprintf (prBuf, "%s/pR_%s_%s_%d",SAVEPATH,testName,algName,i);
		//sprintf (pdBuf, "%s/pD_%s_%s_%d",SAVEPATH,testName,algName,i);

		numOfVE = getSumOfArcAndNodes(path);
		printf("Run\t:\t %s\nfor\t:\t%s (%d / %d)\n",algName,path,i+1,noOfTests);
		for ( j = 0; j < REPEAT; j += 1 ) {
		//	pcFile = fopen(pcBuf,"a");
		//	prFile = fopen(prBuf,"a");
		//	pdFile = fopen(pdBuf,"a");
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

		//	fprintf(pcFile, "%f\n", eC[j]-sC[j]);
		//	fprintf(prFile, "%f\n", eR[j]-sR[j]);
		//	fprintf(pdFile, "%f\n", eD[j]-sD[j]);

		//	fclose(pcFile);
		//	fclose(prFile);
		//	fclose(pdFile);

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
		AC /= CLOCKS_PER_SEC;
		AR /= CLOCKS_PER_SEC;
		AD /= CLOCKS_PER_SEC;

		//fprintf(cFile, "%lld %f\n", numOfVE, AC);
		fprintf(rFile, "%lld %f\n", numOfVE, AR);
		//fprintf(dFile, "%lld %f\n", numOfVE, AD);


		//fclose(cFile);
		fclose(rFile);
		//fclose(dFile);
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
		config = createTMHConfig("/home/s194238/TMH/TMH_Tests/ss/test.ss");

		setAllowInterrupt(config,false);
		setCheckConfig(config,false);
		setGraphOrder(config,NONE);
		setGraphStruct(config,ADJACENCY_LIST);

		setAlgorithm(config,BFM);

		ins = createTMHAlgorithmInstance(config,
				"/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.NY.gr");

		onlyAlgorithm(config->algorithm,ins);
		destroyTMHAlgorithmInstancje(config->algorithm,ins,false);
		destroyTMHConfigInstance(config);
		e = clock();

		printf("%f\n",e-s);*/


		loadTest("/home/s194238/TMH/TMH_Tests/gr/testTMH1.gr",DKXb);

		loadTest("/home/s194238/TMH/TMH_Tests/gr/testTMH1.gr",DKXb);

		loadTest("/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.NY.gr",DKXb);

		loadTest("/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.BAY.gr",DKXb);

		loadTest("/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.COL.gr",DKXb);

		loadTest("/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.FLA.gr",DKXb);

		loadTest("/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.NW.gr",DKXb);

		loadTest("/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.NE.gr",DKXb);

		loadTest("/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.CAL.gr",DKXb);

		loadTest("/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.LKS.gr",DKXb);

		loadTest("/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.E.gr",DKXb);

		loadTest("/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.W.gr",DKXb);

		loadTest("/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.CTR.gr",DKXb);

		loadTest("/home/s194238/TMH/TMH_Tests/gr/USA-road-d/USA-road-d.USA.gr",DKXb);
	}
}

void loadTest( char* path, const AlgorithmAbbreviation alg ) {
	void* ins;
	double s1,s2,s3,e1,e2,e3;

	TMHConfig* config = createTMHConfig("/home/tomasz/workspace/TMH_Tests/ss/test.ss",true);
	TMHNodeData* param = NULL; // malloc(sizeof(TMHNodeData));
	//*param = 2;
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
	TMHConfig* config = createTMHConfig("/home/s194238/TMH/TMH_Tests/ss/test.ss",false);

	TMHNodeData* param = NULL; // malloc(sizeof(TMHNodeData));
//	*param = 2;
	setAllowInterrupt(config,false,param);
	setCheckConfig(config,false);
	setGraphOrder(config,NONE);
	setGraphStruct(config,ADJACENCY_LIST);

	setAlgorithm(config,BFM);
	ins = createTMHAlgorithmInstance(config,
			"/home/s194238/TMH/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	setAlgorithm(config,BFP);
	ins = createTMHAlgorithmInstance(config,
			"/home/s194238/TMH/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	setAlgorithm(config,DKQs);
	ins = createTMHAlgorithmInstance(config,
			"/home/s194238/TMH/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	setAlgorithm(config,DKQd);
	ins = createTMHAlgorithmInstance(config,
			"/home/s194238/TMH/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	setAlgorithm(config,DKB);
	ins = createTMHAlgorithmInstance(config,
			"/home/s194238/TMH/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	setAlgorithm(config,DKM);
	ins = createTMHAlgorithmInstance(config,
			"/home/s194238/TMH/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	setAlgorithm(config,DKA);
	ins = createTMHAlgorithmInstance(config,
			"/home/s194238/TMH/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	setAlgorithm(config,DKD);
	ins = createTMHAlgorithmInstance(config,
			"/home/s194238/TMH/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	setAlgorithm(config,DKF);
	ins = createTMHAlgorithmInstance(config,
			"/home/s194238/TMH/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	setAlgorithm(config,DKH);
	ins = createTMHAlgorithmInstance(config,
			"/home/s194238/TMH/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	setAlgorithm(config,DKR);
	ins = createTMHAlgorithmInstance(config,
			"/home/s194238/TMH/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	setAlgorithm(config,PAP);
	ins = createTMHAlgorithmInstance(config,
			"/home/s194238/TMH/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	setAlgorithm(config,TQQ);
	ins = createTMHAlgorithmInstance(config,
			"/home/s194238/TMH/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,true);

	setAlgorithm(config,THR);
	ins = createTMHAlgorithmInstance(config,
			"/home/s194238/TMH/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	setAlgorithm(config,GR1);
	ins = createTMHAlgorithmInstance(config,
			"/home/s194238/TMH/TMH_Tests/gr/test.gr");
	runTMHAlgorithm(config->algorithm,ins);
	destroyTMHAlgorithmInstancje(config->algorithm,ins,false);

	setAlgorithm(config,GR2);
	ins = createTMHAlgorithmInstance(config,
			"/home/s194238/TMH/TMH_Tests/gr/test.gr");
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
