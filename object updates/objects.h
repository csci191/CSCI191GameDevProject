#ifndef OBJECTS_H
#define OBJECTS_H
#include<GL/gl.h>
#include<iostream>
#include<string.h>
#include<PLAYER.H>
using namespace std;

typedef struct
{
    float x,y,z;
}three;

class objects
{
    public:
        objects();
        virtual ~objects();
        void drawObj();
        void objInit();
        void moveObj(string, objects*, Player* p = NULL);

        GLuint objectTex;

        three verticies[4];
        three position;
        string objDir;
        float xmin, ymin, xmax, ymax;
        float startPos, endPos;
        float maxDistanceX, maxDistanceY;

        float xsize, ysize;
        bool show;
        bool moving;
    protected:

    private:
};

#endif // OBJECTS_H
