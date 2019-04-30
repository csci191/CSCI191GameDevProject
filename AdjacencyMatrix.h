#ifndef ADJACENCYMATRIX_H
#define ADJACENCYMATRIX_H
/*
The Matrix is designed int the format [Rows][Columns]
[0][0] is top left [0][9] is top right in a 10X10 Matrix
*/

class AdjacencyMatrix
{
    private:
        int C; //columns
        int R; //rows
    public:
        AdjacencyMatrix();
        AdjacencyMatrix(int, int);

        virtual ~AdjacencyMatrix();

        void adjPush(int, int);
        void adjPop(int, int);
        void createClearMap();

        int **adjMtrx;

    protected:

    private:
};

#endif 
