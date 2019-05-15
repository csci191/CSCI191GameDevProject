#include "objects.h"
#include<textureLoader.h>
#include<Timer.h>

textureLoader* tl = new textureLoader();
Timer* objTimer = new Timer();

objects::objects()
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
    moving = false;

    maxDistanceX = 5;
}

objects::~objects()
{
    //dtor
}

void objects::drawObj()
{
    if(show)
    {
        glBindTexture(GL_TEXTURE_2D, objectTex);
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
}

void objects::objInit()
{

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void objects::moveObj(string dir, objects* o, Player* p)
{

    if(p != NULL && o->show && !moving)
    {
            o->position.x = (p->position.x*10)+1.7;
            o->position.y = (p->position.y*10)+1;
    }
    moving = true;
    if(objTimer->getTickets()>1)
    {
        if(dir=="right")
        {
            o->position.x +=.5;
            if(o->position.x > 15) show = false;
        }
        else if(dir == "left")
        {
            o->position.x -=.5;
            if(o->position.x < -15) show = false;
        }
        else if(dir == "up")
        {
            o->position.y += .5;
            if(o->position.y > 15) show = false;
        }
        else if(dir == "down")
        {
            o->position.y -=.5;
            if(o->position.y < -15) show = false;
        }
        objTimer->reset();
    }

    if(!show) moving = false;
}

