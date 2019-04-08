#ifndef PARALLAX_H
#define PARALLAX_H
#include<windows.h>
#include<iostream>
#include<GL/gl.h>

using namespace std;


class Parallax
{
    public:
        Parallax();
        virtual ~Parallax();
        void drawSquare(float, float); //drawing a square
        void parallaxInit(char*); // initialize with texture
        void scroll(bool, string, float);
        GLuint paraTex;
        //void keyEnv();
        float xmax, ymax, xmin, ymin;


    protected:

    private:
};

#endif // PARALLAX_H
