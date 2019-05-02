#include "MapFrames.h"
#include<stdlib.h>
#include<fstream>
#include <stdio.h>
#include <string.h>

MapFrames::MapFrames()
{
	frameCount = 0;
}

MapFrames::~MapFrames()
{

}

/*Wil read map file and define inaccessable sections adjMtrx*/
void MapFrames::initFrames(char *fileName)
{
    float tempH = 0;
    float tempV = 0;
    float currentF = 0;
	//File reading the C way
	FILE * file = fopen(fileName, "r");
    if(file == NULL){
        printf("File could not be opened!\n");
        return;
    }
    //Loop for file reading
    while(1){
    	char lineHeader[128]; //Temp value assuming lines will not exceed 128 char length
        //Read first word of the line
        int res = fscanf(file, "%s", lineHeader);

    	if(res == EOF)
            break; //breaks if the end of file is reached
        		   //else we move into the parser

        if ( strcmp( lineHeader, "i" ) == 0){
        	fscanf(file, "%f\n", &frameCount);
        	frames = new AdjacencyMatrix[(int)frameCount];
        }else if (strcmp( lineHeader, "p" ) == 0){
        	fscanf(file, "%f %f\n", &tempH, &tempV);
        	frames[(int)currentF].adjPop((int)tempH, (int)tempV);
            frames[(int)currentF].adjPop((int)tempV, (int)tempH);
        }else if(strcmp( lineHeader, "v" ) == 0){
        	fscanf(file, "%f\n", currentF);
        }

    }
}
