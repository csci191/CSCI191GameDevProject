#include "Player.h"
#include<textureLoader.h>
#include<Timer.h>
#include<GL/gl.h>
using namespace std;

textureLoader* t= new textureLoader();
Timer* tt = new Timer();

Player::Player()
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

    position.x = -.1;
    position.y = -.1;
    position.z = -1;

    speed = 2;
}

Player::~Player()
{
    //dtor
}

void Player::drawPlayer()
{

    t->binder();
    //glScaled(.1,.1,1.0);
    glPushMatrix();
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
    glPopMatrix();
}

void Player::playerInit(char* filename)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    t->bindTexture(filename);

    /* First frame in sprite sheet*/
    xmin=0;
    xmax=.1111111111;

    ymin=0;
    ymax=.25;
}

void Player::playActions(string action)
{
    if(action == "up")
    {
        ymin=0;
        ymax=.25;
        playerAnimation();
        position.y += .1/100 * speed; // moves player up
    }

    if(action == "down")
    {
        ymin = .50;
        ymax = .75;
        playerAnimation();
        position.y -= .1/100* speed; // moves player down
    }

    if(action == "left")
    {
        ymin=.25;
        ymax=.5; //.5
        playerAnimation();
        position.x -= .1/100* speed; // moves player left
    }

    if(action == "right")
    {
        ymin = .75;
        ymax = 1;
        playerAnimation();
        position.x += .1/100 * speed; // moves player right
    }
}

void Player::playerAnimation() // plays animation
{
    if(tt->getTickets() > 100)
    {
        xmin +=.1111111111;
        xmax +=.1111111111;
        if(xmax >=1)
        {
            xmax = .2222222222;
            xmin = .1111111111;
        }
        tt->reset();
    }
}

