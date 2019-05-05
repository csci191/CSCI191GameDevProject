#include "MapFrames.h"
#include <math.h>

MapFrames::MapFrames()
{
    for (int i = 0; i < R; i++){
        std::vector<int> v;
        for(int j = 0; j < C; j++){
            v.push_back(0);
        }
        adjMtrx.push_back(v);
    }
}

MapFrames::~MapFrames()
{

}

/*Wil read map file and define inaccessable sections adjMtrx*/
void MapFrames::initFrames(char *fileName, int searchFrame)
{
    createClearMap();

    float tempH = 0;
    float tempV = 0;
    frame = searchFrame;
    bool currentFrame = false;
    int tempFrame;

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
        	fscanf(file, "%f\n", &tempFrame);
        	if (tempFrame == frame){
                currentFrame = true;
        	}
        	else {
                currentFrame = false;
        	}
        	//frames = (AdjacencyMatrix*)malloc(sizeof(int)*13);
        }else if (strcmp( lineHeader, "p" ) == 0 && currentFrame == true){
        	fscanf(file, "%f %f\n", &tempH, &tempV);
        	adjPop((int)tempH, (int)tempV);
            adjPop((int)tempV, (int)tempH);
        }

    }
}

void MapFrames::adjPush(int h, int v)
{
    if ( (h >= 0 && h < R) && (v >= 0 && v < C) ){
		adjMtrx[h][v] = 1;
	}
}

void MapFrames::adjPop(int h, int v)
{
    if ( (h >= 0 && h < R) && (v >= 0 && v < C) ){
		adjMtrx[h][v] = 0;
	}
}

void MapFrames::createClearMap()
{
int temp = (int)sqrt(C);
	adjPush(0,1);
	adjPush(0,10);
	adjPush(1,0);
	adjPush(10,0);
	for (int i = 1; i < C; i++){
		if ( ((i + 1)%temp) != 0){
			adjPush(i, i + 1);
			adjPush(i+1, i);
		}
		if ((i+10 <= 99))
        {
		    adjPush(i, i+10);
		    adjPush(i+10, i);
        }
	}
}

bool MapFrames::checkConnection(int h, int v)
{
    if ( (adjMtrx[h][v] == 1) || (adjMtrx[v][h] == 1) ){
        return true;
    }else {
    return false;}

}

void MapFrames::printMtrx()
{
    for (int i = 0; i < R; i++){
        for (int j = 0; j < C; j++){
            std::cout <<adjMtrx[i][j] << " ";
        }
        std::cout << std::endl;
    }

}

