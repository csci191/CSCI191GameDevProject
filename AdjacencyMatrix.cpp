#include "AdjacencyMatrix.h"
#include <cmath>
//irrKlang for sounds

//Default values are based on the project this class was designed for
AdjacencyMatrix::AdjacencyMatrix()
{
	C = 100;
	R = 100;
	adjMtrx = new int *[R];
	for (int i = 0; i < R; i++){
		adjMtrx[i] = new int[C];
	}

	for(int i = 0; i < R; i++){
		for (int j = 0; j < C; j++){
			adjMtrx[i][j] = 0;
		}
	}
	createClearMap();
}

AdjacencyMatrix::AdjacencyMatrix(int columns, int rows)
{
	C = columns;
	R = rows;
	adjMtrx = new int *[R];
	for (int i = 0; i < R; i++){
		adjMtrx[i] = new int[C];
	}

	for(int i = 0; i < R; i++){
		for (int j = 0; j < C; j++){
			adjMtrx[i][j] = 0;
		}
	}
}

AdjacencyMatrix::~AdjacencyMatrix()
{
	for (int i = 0; i < R; i++){
		delete [] adjMtrx[i];
	}
	delete [] adjMtrx;
}

AdjacencyMatrix::adjPush(int h, int v)
{
	if ( (h >= 0 && h < R) && (v >= 0 && h < C) ){
		adjMtrx[h][v] = 1;
	}
}

AdjacencyMatrix::adjPop(int h, int v)
{
	if ( (h >= 0 && h < R) && (v >= 0 && h < C) ){
		adjMtrx[h][v] = 0;
	}
}

AdjacencyMatrix::createClearMap()
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
