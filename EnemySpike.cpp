#include "EnemySpike.h"

EnemySpike::EnemySpike()
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
    position.z = 0.01;

    xMove = 0.02;
    yMove = 0.02;
}

EnemySpike::~EnemySpike()
{
    //dtor
}

void EnemySpike::drawEnemy()
{
    spike->binder();
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

void EnemySpike::enemyActions()
{
    switch(actionEnemy)
    {
        case 0:
            if(timeSpike -> getTicks()>80)
            {
                yMin = 0.0;
                yMax = 0.5;

                xMin += 0.5;
                xMax += 0.5;

                if(xMax <= 1.0)
                {
                    actionEnemy = 0;
                }
                else
                {
                    yMin = 0.5;
                    yMax = 1.0;

                    xMin = 0.0;
                    xMax = 0.5;

                    actionEnemy = 1;
                }
                timeSpike -> reset();
            }
        break;

        case 1:
            if(timeSpike -> getTicks()>80)
            {
                yMin = 0.5;
                yMax = 1.0;

                xMin += 0.5;
                xMax += 0.5;

                if(xMax <= 1.0)
                {
                    actionEnemy = 1;
                }
                else
                {
                    yMin = 0.5;
                    yMax = 1.0;

                    xMin = 0.5;
                    xMax = 1.0;

                    actionEnemy = 2;
                }
                timeSpike -> reset();
            }
        break;

        case 2:
            if(timeSpike -> getTicks()>80)
            {
                yMin = 0.5;
                yMax = 1.0;

                xMin -= 0.5;
                xMax -= 0.5;

                //xPos += 0.01;

                if(xMin >= 0.0)
                {
                    actionEnemy = 2;
                }
                else
                {
                    yMin = 0.0;
                    yMax = 0.5;

                    xMin = 0.5;
                    xMax = 1.0;

                    actionEnemy = 3;
                }
                timeSpike -> reset();
            }
        break;

        case 3:
            if(timeSpike -> getTicks()>80)
            {
                yMin = 0.0;
                yMax = 0.5;

                xMin -= 0.5;
                xMax -= 0.5;

                //xPos += 0.01;

                if(xMin >= 0.0)
                {
                    actionEnemy = 3;
                }
                else
                {
                    yMin = 0.0;
                    yMax = 0.5;

                    xMin = 0.0;
                    xMax = 0.5;

                    actionEnemy = 0;
                }
                timeSpike -> reset();
            }
        break;
    }

}

void EnemySpike::enemyInit(char* fileName)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    spike->loadTexture(fileName);
    timeSpike->start();

    /* First frame in sprite sheet*/
    xMin = 0.0;
    xMax = 0.5;

    yMin = 0;
    yMax = 0.5;
}
