#ifndef ANIMATOR_H
#define ANIMATOR_H
#include<textureLoader.h>
#include<iostream>
#include<string.h>

typedef struct
{
    float x,y,z;
}animV;

class Animator
{
    public:
        Animator();
        virtual ~Animator();

        animV verticies[4];
        animV position; // the players x,y,z position

        float xmin, ymin, xmax, ymax;

        GLuint tex;
        void animInit(float, float, float, float);
        void animDraw();
        void playAnimation();

        bool show;
        bool play = false;

    protected:

    private:
};

#endif // ANIMATOR_H
