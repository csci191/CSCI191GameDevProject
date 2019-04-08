#include "objects.h"
#include<textureLoader.h>

textureLoader* tl = new textureLoader();
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
}

objects::~objects()
{
    //dtor
}

void objects::drawObj()
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

void objects::objInit(char* filename)
{
    /*
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    tl->bindTexture(filename);
    */

    /* First frame in sprite sheet*/
    xmin=0;
    xmax=.1111111111;

    ymin=0;
    ymax=.25;


}

