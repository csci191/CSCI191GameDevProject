#ifndef MAPFRAMES_H
#define MAPFRAMES_H

#include<stdlib.h>
#include<fstream>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>

class MapFrames
{
    private:
        int frame;
        int R = 100;
        int C = 100;
    public:
        MapFrames();

        virtual ~MapFrames();

        void initFrames(char *, int);

        void adjPush(int, int);
        void adjPop(int, int);
        void createClearMap();
        bool checkConnection(int, int);
        void printMtrx();

        std::vector<std::vector<int> > adjMtrx;

    protected:

    private:
};

#endif
