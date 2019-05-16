#include "BossFire.h"

BossFire::BossFire()
{
    //ctor
    verticies[0].x =  0.0;
    verticies[0].y =  0.0;
    verticies[0].z =  -7;

    verticies[1].x =  0.4;
    verticies[1].y =  0.0;
    verticies[1].z =  -7;

    verticies[2].x =  0.4;
    verticies[2].y =  0.4;
    verticies[2].z =  -7;

    verticies[3].x =  0.0;
    verticies[3].y =  0.4;
    verticies[3].z =  -7;

    xMin=0.0;
    yMin=0.0;
    xMax=0.5;
    yMax=0.5;

    position.x = -0.4;
    position.y = -0.4;
    position.z = 0.03;

    xMove = 0.02;
    yMove = 0.02;
}

BossFire::~BossFire()
{
    //dtor
}

void BossFire::drawFire()
{
    texFire->binder();
    glScaled(0.5, 0.5, 1.0);
    glTranslatef(position.x, position.y, position.z);
    glPushMatrix();
    glBegin(GL_QUADS);
        glTexCoord2f(xMin,yMax);
        glVertex3f(verticies[0].x, verticies[0].y, verticies[0].z);

        glTexCoord2f(xMax,yMax);
        glVertex3f(verticies[1].x, verticies[1].y, verticies[1].z);

        glTexCoord2f(xMax,yMin);
        glVertex3f(verticies[2].x, verticies[2].y, verticies[2].z);

        glTexCoord2f(xMin,yMin);
        glVertex3f(verticies[3].x, verticies[3].y, verticies[3].z);
    glEnd();
    glPopMatrix();
}

void BossFire::attackFire(Player* Ply, EnemyBoss* Boss)
{
    if(Boss->attackPly)
    {
        if((Ply != NULL) && (Boss != NULL))
        {
            position.x = Boss->position.x;
            position.y = Boss->position.y;
            tempPlayerX = Ply->position.x;
            tempPlayerY = Ply->position.y;
        }
        if((attacking))
        {
            if((position.x != tempPlayerX) && (position.y != tempPlayerY))
                position.x += 0.1;
                position.y += 0.1;
                yMin = 0.0;
                yMax = 1.0;
                xMin = 0.0;
                xMax = 0.25;
                bossAttacking = 0;
                fireActions(Boss);
                if((position.x = -15.0) || (position.x = 15.0) || (position.y = -15.0) || (position.y = 15.0))
                {
                    attacking = false;
                }
            if((position.x = Ply->position.x) && (position.y = Ply->position.y))
            {
                attacking = false;
            }
        }
    }
}


void BossFire::fireActions(EnemyBoss* Boss)
{
    if(attacking)
    {
        switch(bossAttacking)
        {
            case 0:
                if(timeFire->getTicks()>80)
                {
                    yMin = 0.0;
                    yMax = 1.0;

                    xMin += 0.2;
                    xMax += 0.2;

                    if(xMax <= 1.0)
                    {
                        bossAttacking = 0;
                    }
                    else
                    {
                        xMin = 0.8;
                        xMax = 1.0;
                        bossAttacking = 1;
                    }
                    timeFire->reset();
                }
            break;
            case 1:
                if(timeFire->getTicks()>80)
                {
                    yMin = 0.0;
                    yMax = 1.0;

                    xMin -= 0.2;
                    xMax -= 0.2;

                    if(xMin >= 0.0)
                    {
                        bossAttacking = 1;
                    }
                    else
                    {
                        xMin = 0.0;
                        xMax = 0.2;
                        bossAttacking = 0;
                    }
                    timeFire->reset();
                }
                break;
        }
    }
}

void BossFire::fireInit(char* fileName)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    texFire->loadTexture(fileName);
    timeFire->start();

    /* First frame in sprite sheet*/
    xMin = 0.0;
    xMax = 0.5;

    yMin = 0;
    yMax = 0.5;
}
