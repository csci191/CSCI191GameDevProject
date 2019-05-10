#include "Animator.h"
#include<textureLoader.h>
#include<Timer.h>

textureLoader* animT = new textureLoader();
Timer* animTimer = new Timer();

Animator::Animator()
{
    //ctor
    verticies[0].x =  0.0;
    verticies[0].y =  0.0;
    verticies[0].z =  -0.1;

    verticies[1].x =  1.0;
    verticies[1].y =  0.0;
    verticies[1].z =  -0.1;

    verticies[2].x =  1.0;
    verticies[2].y =  1.0;
    verticies[2].z =  -0.1;

    verticies[3].x =  0.0;
    verticies[3].y =  1.0;
    verticies[3].z =  -0.1;

    xmin=0;
    ymin=0;
    xmax=1;
    ymax=1;

    show = true;
    animInit();
}

Animator::~Animator()
{
    //dtor
}

void Animator::animInit()
{
    /* First frame in sprite sheet*/
    xmin=(float)3/6;
    xmax=(float)4/6;

    ymin=0;
    ymax=(float)1/4;
}

void Animator::animDraw()
{
        if(show){
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUADS);
        glTexCoord2f(xmin,ymax);
        glVertex3f(verticies[0].x,verticies[0].y,verticies[0].z);

        glTexCoord2f(xmax,ymax);
        glVertex3f(verticies[1].x,verticies[1].y,verticies[1].z);

        glTexCoord2f(xmax,ymin);
        glVertex3f(verticies[2].x,verticies[2].y,verticies[2].z);

        glTexCoord2f(xmin,ymin);
        glVertex3f(verticies[3].x,verticies[3].y,verticies[3].z);
    glEnd();
    }
    playAnimation();
}

void Animator::playAnimation()
{
    if(animTimer->getTickets() > 10)
    {
        xmin +=(float)1/6;
        xmax +=(float)1/6;
        if(xmax >=1)
        {
            xmax = (float)2/6;
            xmin = (float)1/6;
        }
        animTimer->reset();
    }
}
