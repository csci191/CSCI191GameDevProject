#ifndef ADJACENCYMATRIX_H
#define ADJACENCYMATRIX_H
#include <vector>
#include<stdio.h>
#include<stdlib.h>

/*
The Matrix is designed int the format [Rows][Columns]
[0][0] is top left [0][9] is top right in a 10X10 Matrix
*/

class AdjacencyMatrix
{
    private:
        int C = 100; //columns
        int R = 100; //rows
    public:
        AdjacencyMatrix();
        AdjacencyMatrix(int, int);

        virtual ~AdjacencyMatrix();

        void adjPush(int, int);
        void adjPop(int, int);
        void createClearMap();

        std::vector<std::vector<int> > adjMtrx;

    protected:

    private:
};

#endif
