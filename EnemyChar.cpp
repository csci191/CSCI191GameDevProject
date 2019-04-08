#include "EnemyChar.h"

EnemyChar::EnemyChar()
{
    //ctor
    xPos = 0.1;
    yPos = 0.0;
    zPos = -1.0;

    xSize = 0.02;
    ySize = 0.02;

    rotateX = 0.0;
    rotateY = 0.0;
    rotateZ = 0.0;

    xMove = 0.0;
    yMove = 0.001;
}

EnemyChar::~EnemyChar()
{
    //dtor
}

void EnemyChar::drawEnemy()
{
    if(isEnemyLive)
    {


    glPushMatrix();

    glTranslated(xPos, yPos, zPos);
    glRotated(rotateX, 1.0, 0.0, 0.0);
    glRotated(rotateY, 0.0, 1.0, 0.0);
    glRotated(rotateZ, 0.0, 0.0, 1.0);

    glBindTexture(GL_TEXTURE_2D, enemyTex);
    glScaled(xSize, ySize, 1.0);

    glBegin(GL_QUADS);
        glTexCoord2f(xMin, yMax);
        glVertex3f(1.0, -1.0, 0.0);

        glTexCoord2f(xMax, yMax);
        glVertex3f(-1.0, -1.0, 0.0);

        glTexCoord2f(xMax, yMin);
        glVertex3f(-1.0, 1.0, 0.0);

        glTexCoord2f(xMin, yMin);
        glVertex3f(1.0, 1.0, 0.0);
    glEnd();

    glPopMatrix();
    }
}

void EnemyChar::placeEnemy(float x, float y, float z)
{
    xPos = x;
    yPos = y;
    zPos = z;
}

void EnemyChar::enemyActions()
{
     switch(actionEnemy)
    {
        case 0: //go Right
            if(TE -> getTicks()>80)
            {
                yMin = 0.75;
                yMax = 1.0;

                xMin += 0.11111111111111 / (float)Frames;
                xMax += 0.11111111111111 / (float)Frames;

                //xPos += 0.01;

                if(xMax >= 1.0)
                {
                    xMin = 0.0;
                    xMax = 0.11111111111111 / (float)Frames;
                }

                TE -> reset();
            }
        break;

        case 1: //go Left
            if(TE -> getTicks()>80)
            {

                yMin = 0.25;
                yMax = 0.5;

                xMin += 0.11111111111111 / (float)Frames;
                xMax += 0.11111111111111 / (float)Frames;

                //xPos += 0.01;

                if(xMax >= 1.0)
                {
                    xMin = 0.0;
                    xMax = 0.11111111111111 / (float)Frames;
                }

                TE -> reset();
            }

        break;

        case 2: //go Down
            if(TE -> getTicks()>80)
            {

                yMin = 0.5;
                yMax = 0.75;

                xMin += 0.11111111111111 / (float)Frames;
                xMax += 0.11111111111111 / (float)Frames;

                //xPos += 0.01;

                if(xMax >= 1.0)
                {
                    xMin = 0.0;
                    xMax = 0.11111111111111 / (float)Frames;
                }

                TE -> reset();
            }

        break;

        case 3: //go Up
            if(TE -> getTicks()>80)
            {

                yMin = 0.0;
                yMax = 0.25;

                xMin += 0.11111111111111 / (float)Frames;
                xMax += 0.11111111111111 / (float)Frames;

                //xPos += 0.01;

                if(xMax >= 1.0)
                {
                    xMin = 0.0;
                    xMax = 0.11111111111111 / (float)Frames;
                }

                TE -> reset();
            }

        break;
    }
}

void EnemyChar::enemyInit()
{
    Frames = 1;

    xMin = 0.0;
    xMax = 0.11111111111111 / (float)Frames;

    yMin = 0.0;
    yMax = 0.25 / (float)Frames;


}
