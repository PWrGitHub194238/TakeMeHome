/*
 ============================================================================
 Name        : testC.c
 Author      : Tomasz Strzałka
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>

const int TESTSNO = 12;
const char* TESTPATHS[12] = {
		"TMH_Tests/gr/USA-road-d/USA-road-d.NY.gr",
		"TMH_Tests/gr/USA-road-d/USA-road-d.BAY.gr",
		"TMH_Tests/gr/USA-road-d/USA-road-d.COL.gr",
		"TMH_Tests/gr/USA-road-d/USA-road-d.FLA.gr",
		"TMH_Tests/gr/USA-road-d/USA-road-d.NW.gr",
		"TMH_Tests/gr/USA-road-d/USA-road-d.NE.gr",
		"TMH_Tests/gr/USA-road-d/USA-road-d.CAL.gr",
		"TMH_Tests/gr/USA-road-d/USA-road-d.LKS.gr",
		"TMH_Tests/gr/USA-road-d/USA-road-d.E.gr",
		"TMH_Tests/gr/USA-road-d/USA-road-d.W.gr",
		"TMH_Tests/gr/USA-road-d/USA-road-d.CTR.gr",
		"TMH_Tests/gr/USA-road-d/USA-road-d.USA.gr"
};

const char* SAVE[12] = {
		"50xUSA-road-d.NY.gr",
		"50xUSA-road-d.BAY.gr",
		"50xUSA-road-d.COL.gr",
		"50xUSA-road-d.FLA.gr",
		"50xUSA-road-d.NW.gr",
		"50xUSA-road-d.NE.gr",
		"50xUSA-road-d.CAL.gr",
		"50xUSA-road-d.LKS.gr",
		"50xUSA-road-d.E.gr",
		"50xUSA-road-d.W.gr",
		"50xUSA-road-d.CTR.gr",
		"50xUSA-road-d.USA.gr",
		"50xUSA-road-d.CTR.gr",
		"50xUSA-road-d.USA.gr"
};
static void modGraphData( FILE* const dataFile, const char* savePath, int PARAM );
static double standard_deviation(unsigned int data[], unsigned long int n);

int main(void) {
	FILE* dataFile = NULL;
	int i;
	for (i=0; i <TESTSNO; i ++ ) {
		printf("%s\n",TESTPATHS[i]);
		dataFile = fopen(TESTPATHS[i],"r");
		modGraphData(dataFile,SAVE[i],50);
	}
	return EXIT_SUCCESS;
}


static void modGraphData( FILE* const dataFile, const char* savePath, int PARAM ) {
	unsigned int numberOfNodes;
	unsigned int numberOfArcs;
	unsigned int fromNodeID,toNodeID;
	unsigned int distanceLabel;
	unsigned int maxArcCost = 0;
	unsigned int* costTab = NULL;
	FILE* saveFile = NULL;
	saveFile = fopen(savePath,"w");
	double stdD = 0.0, avg = 0.0;
	unsigned long int i = 0;
	while ( !feof(dataFile) ) {
		switch (fgetc(dataFile)) {
		case 'c':
			fscanf(dataFile, "%*[^\n]\n");
			break;
		case 'p':
			fscanf(dataFile," %*[^ ] %u %u\n",&numberOfNodes,&numberOfArcs);
			printf("%u %u\n",numberOfNodes,numberOfArcs);
			costTab = malloc(numberOfArcs*sizeof(unsigned int));
			fprintf(saveFile,"p sp %u %u\n",numberOfNodes,numberOfArcs);
			break;
		case 'a':
			fscanf(dataFile," %u %u %u\n",&fromNodeID,&toNodeID,&distanceLabel);
			fprintf(saveFile,"a %u %u %u\n",fromNodeID,toNodeID,distanceLabel*PARAM);
			maxArcCost = ( (maxArcCost < distanceLabel) ? distanceLabel : maxArcCost);
			avg += distanceLabel;
			costTab[i++] = distanceLabel;
		}
	}

	stdD = standard_deviation(costTab,numberOfArcs);
	avg = avg/numberOfArcs;
	printf("%d,\n",maxArcCost/5);
	printf("& $%d$ & $%.2f$ & $%.2f$ &  \\\\\n",maxArcCost,avg,stdD);
	free(costTab);
	fclose(dataFile);
	fclose(saveFile);
	return;
}

static double standard_deviation(unsigned int data[], unsigned long int n)
{
    float mean=0.0, sum_deviation=0.0;
    int i;
    for(i=0; i<n;++i)
    {
        mean+=data[i];
    }
    mean=mean/n;
    for(i=0; i<n;++i) {
    	sum_deviation+=(data[i]-mean)*(data[i]-mean);
    }
    return sqrt(sum_deviation/n);
}
