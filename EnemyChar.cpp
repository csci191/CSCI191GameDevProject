#include "EnemyChar.h"

EnemyChar::EnemyChar()
{
    //ctor

     //  Bottom Left Corner
    verticies[0].x = 0.0;
    verticies[0].y = 0.0;
    verticies[0].z = -1.0;

    //  Bottom Right Corner
    verticies[1].x = 1.0;
    verticies[1].y = 0.0;
    verticies[1].z = -1.0;

    //  Top Right Corner
    verticies[2].x = 1.0;
    verticies[2].y = 1.0;
    verticies[2].z = -1.0;

    //  Top Left Corner
    verticies[3].x = 0.0;
    verticies[3].y = 1.0;
    verticies[3].z = -1.0;

    xMin = 0.0;
    xMax = 0.0;

    yMin = 0.0;
    yMax = 0.0;

    xPos = -0.5;
    yPos = -0.5;
    zPos = -1.0;

    xSize = 0.2;
    ySize = 0.2;

    eMax = 11;
    eMin = 0;

    actionTrigger = 0;

    position.x = 0.3;
    position.y = 0.3;
    position.z = -1.0;

    speed = 2;
}

EnemyChar::~EnemyChar()
{
    //dtor
}

void EnemyChar::drawEnemyChar()
{
    TEnmChar->binder();
    glPushMatrix();

    glScaled(xSize, ySize, 1.0);
    //glScaled(1.0/(float)(gridSize), (1.0)/(float)(gridSize), 1.0);

    glBegin(GL_QUADS);
        glTexCoord2f(xMin, yMax);
        glVertex3f(verticies[0].x, verticies[0].y, verticies[0].z);

        glTexCoord2f(xMax, yMax);
        glVertex3f(verticies[1].x, verticies[1].y, verticies[1].z);

        glTexCoord2f(xMax, yMin);
        glVertex3f(verticies[2].x, verticies[2].y, verticies[2].z);

        glTexCoord2f(xMin, yMin);
        glVertex3f(verticies[3].x, verticies[3].y, verticies[3].z);
    glEnd();

    glPopMatrix();
}

void EnemyChar::enemycharInit(char*fileName)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    TEnmChar->loadTexture(fileName);
    TimeEnmChar->start();

    //  Sprite Sheet Grid
    xMin = 0.0;
    xMax = 0.11111111111111;

    yMin = 0.50;
    yMax = 0.75;
}

void EnemyChar::enemycharActions()
{
    switch(actionTrigger)
    {
    case 0:
        {//stand still facing down
            xMin = 0.0;
            xMax = 0.1111111111111;

            yMin = 0.5;
            yMax = 0.75;
        }
        break;

    case 1: //stand still facing up
        {
            xMin = 0.0;
            xMax = 0.11111111111111;

            yMin = 0.0;
            yMax = 0.25;
        }
        break;

    case 2: //stand still facing right
        {
            xMin = 0.0;
            xMax = 0.11111111111111;

            yMin = 0.75;
            yMax = 1.0;
        }
        break;

    case 3: //stand still facing left
        {
            xMin = 0.0;
            xMax = 0.11111111111111;

            yMin = 0.25;
            yMax = 0.50;
        }
        break;

    case 4: //go facing down
        {
            xMin = 0.0;
            xMax = 0.1111111111111;

            yMin = 0.5;
            yMax = 0.75;
            enemycharMove(1);
            position.y -= 0.1 / 100 * speed;
        }
        break;

    case 5: //go facing up
        {
            xMin = 0.0;
            xMax = 0.11111111111111;

            yMin = 0.0;
            yMax = 0.25;
            enemycharMove(1);
            position.y += 0.1 / 100 * speed;
        }
        break;

    case 6: //go facing right
        {
            xMin = 0.0;
            xMax = 0.11111111111111;

            yMin = 0.75;
            yMax = 1.0;
            enemycharMove(1);
            position.x += 0.1 / 100 * speed;
        }
        break;

    case 7: //go facing left
        {
            xMin = 0.0;
            xMax = 0.11111111111111;

            yMin = 0.25;
            yMax = 0.50;
            enemycharMove(1);
            position.x -= 0.1 / 100 * speed;
        }
        break;

    case 8: //go facing down 5x
        {
            xMin = 0.0;
            xMax = 0.1111111111111;

            yMin = 0.5;
            yMax = 0.75;
            enemycharMove(5);
            position.y -= 0.2 / 100 * speed;
        }
        break;

    case 9: //go facing up 5x
        {
            xMin = 0.0;
            xMax = 0.11111111111111;

            yMin = 0.0;
            yMax = 0.25;
            enemycharMove(5);
            position.y += 0.2 / 100 * speed;
        }
        break;

    case 10: //go facing right 5x
        {
            xMin = 0.0;
            xMax = 0.11111111111111;

            yMin = 0.75;
            yMax = 1.0;
            enemycharMove(5);
            position.x += 0.2 / 100 * speed;
        }
        break;

    case 11: //go facing left 5x
        {
            xMin = 0.0;
            xMax = 0.11111111111111;

            yMin = 0.25;
            yMax = 0.50;
            enemycharMove(5);
            position.x -= 0.2 / 100 * speed;
        }
        break;

    }
}

void EnemyChar::enemycharMove(int moves)
{
    if(TimeEnmChar->getTicks()>40)
        {
            for(int i = 0; i < moves; i++)
            {
                xMin += (0.11111111111111);
                xMax += (0.11111111111111);
                if(xMax >= 1)
                {
                    xMax = 0.22222222222222;
                    xMin = 0.11111111111111;
                }
            }
            TimeEnmChar->reset();
        }
}

/*
void EnemyChar::collision(Player* Ply)
{
    if(position.x = Ply->position.x)
    {

    }

    if(position.y = Ply->position.y)
    {

    }
}
*/
