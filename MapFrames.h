#ifndef MAPFRAMES_H
#define MAPFRAMES_H

#include "AdjacencyMatrix.h"

class MapFrames
{
    private:
        int frameCount;
    public:
        MapFrames();

        virtual ~MapFrames();

        void initFrames(char *);

        /*Will hold the adjMtrxs of different sections of the map*/
        AdjacencyMatrix *frames;  

    protected:

    private:
};

#endif 
