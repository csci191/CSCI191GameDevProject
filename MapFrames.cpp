#include "MapFrames.h"

MapFrames::MapFrames()
{
	frameCount = 0;
}

MapFrames::~MapFrames()
{

}

/*Wil read map file and define each map sections adjMtrx*/
MapFrames::initFrames(char *fileName)
{
	//File reading the C way
	FILE * file = fopen(fileName, "r");
    if(file == NULL){
        printf("File could not be opened!\n");
        return;
    }
    int tempH, tempV;
    //Loop for file reading
    while(1){
    	char lineHeader[128]; //Temp value assuming lines will not exceed 128 char length
        //Read first word of the line
        int res = fscanf(file, "%s", lineHeader);

    	if(res == EOF)
            break; //breaks if the end of file is reached
        		   //else we move into the parser

        if ( strcmp( lineHeader, "i" ) == 0){
        	fscanf(file, "%d\n", frameCount);
        	frames = new AdjacencyMatrix[frameCount]
        }else if (strcmp( lineHeader, "p") == 0){
        	fscanf(file, "%d %d\n", tempH, tempV);
        	frames->adjPush(tempH, tempV);
        }

    }
}
