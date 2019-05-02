#include "AdjacencyMatrix.h"
#include <cmath>
//irrKlang for sounds

//Default values are based on the project this class was designed for
AdjacencyMatrix::AdjacencyMatrix()
{
    int l = 0;
    for (int i = 0; i < R; i++){
        std::vector<int> v;
        for(int j = 0; j < C; j++){
            v.push_back(0);
        }
        adjMtrx.push_back(v);
    }
	createClearMap();
}


AdjacencyMatrix::~AdjacencyMatrix()
{

}

void AdjacencyMatrix::adjPush(int h, int v)
{
	if ( (h >= 0 && h < R) && (v >= 0 && v < C) ){
		adjMtrx[h][v] = 1;
	}
}

void AdjacencyMatrix::adjPop(int h, int v)
{
	if ( (h >= 0 && h < R) && (v >= 0 && v < C) ){
		adjMtrx[h][v] = 0;
	}
}

void AdjacencyMatrix::createClearMap()
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
		    adjPush(i, i+10);
		    adjPush(i+10, i);
	}
}
