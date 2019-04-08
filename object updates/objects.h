#ifndef OBJECTS_H
#define OBJECTS_H
#include<GL/gl.h>

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
        void objInit(char*);

        GLuint objectTex;

        three verticies[4];
        three position;
        float xmin, ymin, xmax, ymax;



    protected:

    private:
};

#endif // OBJECTS_H
