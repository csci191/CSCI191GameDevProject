#include "AdjacencyMatrix.h"
//irrKlang for sounds

//Default is values are based on the project this class was designed for
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
