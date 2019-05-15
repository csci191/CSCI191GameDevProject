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
        int checkFrame();

        std::vector<int> enemyPositions;
        int bossPos = -1;
        std::vector<std::vector<int> > adjMtrx;
        std::vector<std::vector<int> > frameConnections;
        std::vector<std::vector<int> > doorList;//Door list contains a range of numbers for determining where the doors
                                                /*are. The range is contained as
                                                leftMin leftMax, rightMin rightMax, upMin upMax, downMin downMax
                                                */
        int frame;

    protected:

    private:
};

#endif
