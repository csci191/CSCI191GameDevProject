#include "EnemyBoss.h"

EnemyBoss::EnemyBoss()
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

    xMin=0;
    yMin=0;
    xMax=0.5;
    yMax=0.33333333333;

    position.x = -0.1;
    position.y = -0.6;
    position.z = 0.02;

    xMove = 0.0;
    yMove = 0.001;

    speed = 5;
}

EnemyBoss::~EnemyBoss()
{
    //dtor
}

void EnemyBoss::drawBoss()
{
    bossTex->binder();
    glScaled(1.0, 1.0, 1.0);
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

void EnemyBoss::bossInit(char* fileName, char* nameFile)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    bossTex->loadTexture(fileName);
    bossSpawner->start();
    bossTimerAppear->start();
    bossSound->start();

    /* First frame in sprite sheet*/
    xMin = 0.0;
    xMax = 0.25;

    yMin = 0;
    yMax = 0.3333333333333;
}


void EnemyBoss::bossSpawn()
{
    appear = true;
    bossActions(bossSND);
    if((bossTimerAppear->getTicks() > 6000) && (bossTimerAppear->getTicks() < 6050))
    {
        actionBoss = 20;
        bossAppear(0);
        //cout << "spawning case 0" << endl;
    }
    else if((bossTimerAppear->getTicks() > 11000) && (bossTimerAppear->getTicks() < 11050))
    {
        actionBoss = 20;
        bossAppear(1);
        //cout << "spawning case 1" << endl;
    }
    else if((bossTimerAppear->getTicks() > 16000) && (bossTimerAppear->getTicks() < 16050))
    {
        actionBoss = 20;
        bossAppear(2);
        //cout << "spawning case 2" << endl;
    }
    else if((bossTimerAppear->getTicks() > 21000) && (bossTimerAppear->getTicks() < 21050))
    {
        actionBoss = 20;
        bossAppear(3);
        //cout << "spawning case 3" << endl;
    }
    else if(bossTimerAppear -> getTicks() > 26000)
    {
        actionBoss = 20;
        bossAppear(4);
        bossTimerAppear -> reset();
    }
}

void EnemyBoss::bossAppear(int placementBoss)
{
    if(appear)
    {
        switch(placementBoss)
        {
        case 0:
            {
                bossAnimation(-1.2, -0.6); //Bottom left corner
                //cout << "Doing case 1 appear." << endl;
                bossActions(bossSND);
            }
            break;

        case 1:
            {
                bossAnimation(0.8, -0.6); //Bottom right corner
                //cout << "Doing case 2 appear." << endl;
                bossActions(bossSND);
            }
            break;

        case 2:
            {
                bossAnimation(0.8, 0.35); //top right corner
                //cout << "Doing case 3 appear." << endl;
                bossSND->pauseSound("snds/OOT_Ganondorf_Heheh.wav");
                bossActions(bossSND);
            }
            break;

        case 3:
            {
                bossAnimation(-1.2, 0.35); //Top left corner
                //cout << "Doing case 4 appear." << endl;
                bossActions(bossSND);
            }
            break;

        case 4:
            {
                bossAnimation(-0.1, -0.6); //Top left corner
                //cout << "Doing case 4 appear." << endl;
                bossSND->pauseSound("snds/OOT_Ganondorf_Heheh.wav");
                bossActions(bossSND);
            }
            break;
        }
    }
}

void EnemyBoss::bossActions(Sounds* SND)
{
    switch(actionBoss)
    {
        case 0: //Standing facing right
            if(bossTimer -> getTicks()>100)
            {
                yMin = 0.0;
                yMax = 0.3333333333333333333333;

                xMin += 0.25;
                xMax += 0.25;

                //xPos += 0.01;

                if(xMax <= 1.0)
                {
                    actionBoss = 0;
                }
                else
                {
                    xMin = 0.75;
                    xMax = 1.0;
                    actionBoss = 1;
                    SND->pauseSound("snds/OOT_Ganondorf_Heheh.wav");
                    teleportIn = false;
                    teleportOut = true;
                }

                bossTimer -> reset();
            }
           //cout << "doing case 0" << endl;
        break;

        case 1: //standing facing right
            if(bossTimer -> getTicks()>100)
            {
                yMin = 0.0;
                yMax = 0.3333333333333333333333;

                xMin -= 0.25;
                xMax -= 0.25;

                //xPos += 0.01;

                if(xMin > 0.0)
                {
                    actionBoss = 1;
                }
                else
                {
                    xMin = 0.0;
                    xMax = 0.25;
                    actionBoss = 2;
                }
                bossTimer -> reset();
            }
            //cout << "doing case 1" << endl;
        break;

        case 2: //Standing facing right
            if(bossTimer -> getTicks()>100)
            {
                yMin = 0.0;
                yMax = 0.3333333333333333333333;

                xMin += 0.25;
                xMax += 0.25;

                //xPos += 0.01;

                if(xMax <= 1.0)
                {
                    actionBoss = 2;
                }
                else
                {
                    xMin = 0.75;
                    xMax = 1.0;
                    actionBoss = 3;
                }

                bossTimer -> reset();
            }
           //cout << "doing case 2" << endl;
        break;

        case 3: //standing facing right
            if(bossTimer -> getTicks()>100)
            {
                yMin = 0.0;
                yMax = 0.3333333333333333333333;

                xMin -= 0.25;
                xMax -= 0.25;

                //xPos += 0.01;

                if(xMin >= 0.0)
                {
                    actionBoss = 3;
                }
                else
                {
                    xMin = 0.0;
                    xMax = 0.25;
                    actionBoss = 4;
                }
                bossTimer -> reset();
            }
            //cout << "doing case 3" << endl;
        break;

        case 4: //Standing facing right
            if(bossTimer -> getTicks()>100)
            {
                yMin = 0.0;
                yMax = 0.3333333333333333333333;

                xMin += 0.25;
                xMax += 0.25;

                //xPos += 0.01;

                if(xMax <= 1.0)
                {
                    actionBoss = 4;
                }
                else
                {
                    xMin = 0.75;
                    xMax = 1.0;
                    actionBoss = 5;
                }

                bossTimer -> reset();
            }
           //cout << "doing case 4" << endl;
        break;

        case 5: //standing facing right
            if(bossTimer -> getTicks()>100)
            {
                yMin = 0.0;
                yMax = 0.3333333333333333333333;

                xMin -= 0.25;
                xMax -= 0.25;

                //xPos += 0.01;

                if(xMin >= 0.0)
                {
                    actionBoss = 5;
                }
                else
                {
                    xMin = 0.0;
                    xMax = 0.25;
                    actionBoss = 6;
                }
                bossTimer -> reset();
            }
            //cout << "doing case 5" << endl;
        break;

        case 6: //Standing facing right
            if(bossTimer -> getTicks()>100)
            {
                yMin = 0.0;
                yMax = 0.3333333333333333333333;

                xMin += 0.25;
                xMax += 0.25;

                //xPos += 0.01;

                if(xMax <= 1.0)
                {
                    actionBoss = 6;
                }
                else
                {
                    yMin = 0.3333333333333333333333;
                    yMax = 0.6666666666666666666666;
                    xMin = 0.0;
                    xMax = 0.25;

                    SND->pauseSound("snds/LA_Genie_Disappear.wav");
                    teleportIn = true;
                    teleportOut = false;

                    actionBoss = 7;
                }

                bossTimer -> reset();
            }
           //cout << "doing case 6" << endl;
        break;

        case 7: //standing facing right
            if(bossTimer -> getTicks()>100)
            {
                yMin = 0.3333333333333333333333;
                yMax = 0.6666666666666666666666;

                xMin += 0.25;
                xMax += 0.25;

                //xPos += 0.01;

                if(xMax <= 1.0)
                {
                    actionBoss = 7;
                }
                else
                {
                    yMin = 0.6666666666666666666666;
                    yMax = 1.0;

                    xMin = 0.0;
                    xMax = 0.25;
                    actionBoss = 8;
                }
                bossTimer -> reset();
            }
            //cout << "doing case 7" << endl;
        break;

        case 8: //melting facing right
            if(bossTimer -> getTicks()>100)
            {
                yMin = 0.6666666666666666666666;
                yMax = 1.0;

                xMin += 0.25;
                xMax += 0.25;

                if(xMax <= 1.0)
                {
                    actionBoss = 8;
                }
                else
                {
                    //yMin = 0.666666666;
                    //yMax = 1.0;

                    xMin = 0.75;
                    xMax = 1.0;
                    actionBoss = 9;
                }
                bossTimer -> reset();
            }
            //cout << "doing case 8" << endl;
        break;

        case 9: //melting facing right
            if(bossTimer -> getTicks()>100)
            {
                yMin = 0.6666666666666666666667;
                yMax = 1.0;

                xMin = 0.75;
                xMax = 1.0;

                bossTimer -> reset();
            }
            //int current = bossSpawner->getTicks();
           // cout << "doing case 9 " /*<< current*/ << endl;
        break;

        case 10: //Standing facing right
            if(bossTimer -> getTicks()>100)
            {
                yMin = 0.6666666666666666666666;
                yMax = 1.0;

                xMin -= 0.25;
                xMax -= 0.25;

                //xPos += 0.01;

                if(xMin >= 0.0)
                {
                    actionBoss = 10;
                }
                else
                {
                    yMin = 0.3333333333333333333333;
                    yMax = 0.6666666666666666666666;
                    xMin = 0.75;
                    xMax = 1.0;
                    actionBoss = 11;
                }

                bossTimer -> reset();
            }
           //cout << "teleporting case 10" << endl;
        break;

        case 11: //Standing facing right
            if(bossTimer -> getTicks()>100)
            {
                yMin = 0.3333333333333333333333;
                yMax = 0.6666666666666666666666;

                xMin -= 0.25;
                xMax -= 0.25;

                //xPos += 0.01;

                if(xMin >= 0.0)
                {
                    actionBoss = 11;
                }
                else
                {
                    yMin = 0.0;
                    yMax = 0.3333333333333333333333;
                    xMin = 0.75;
                    xMax = 1.0;
                    actionBoss = 12;
                }

                bossTimer -> reset();
            }
           //cout << "teleporting case 11" << endl;
        break;

        case 12: //Standing facing right
            if(bossTimer -> getTicks()>100)
            {
                yMin = 0.0;
                yMax = 0.3333333333333333333333;

                xMin -= 0.25;
                xMax -= 0.25;

                //xPos += 0.01;

                if(xMin >= 0.0)
                {
                    actionBoss = 12;
                }
                else
                {
                    yMin = 0.0;
                    yMax = 0.3333333333333333333333;
                    xMin = 0.0;
                    xMax = 0.25;
                    actionBoss = 13;
                }

                bossTimer -> reset();
            }
           //cout << "teleporting case 12" << endl;
        break;

        case 13: //Standing facing right
            if(bossTimer -> getTicks()>100)
            {
                yMin = 0.0;
                yMax = 0.3333333333333333333333;

                xMin += 0.25;
                xMax += 0.25;

                //xPos += 0.01;

                if(xMax <= 1.0)
                {
                    actionBoss = 13;
                }
                else
                {
                    xMin = 0.75;
                    xMax = 1.0;
                    attackPly = true;
                    SND->pauseSound("snds/LTTP_Agahnim_Charge.wav");
                    actionBoss = 14;
                }

                bossTimer -> reset();
            }
           //cout << "teleporting case 13" << endl;
        break;

        case 14: //standing facing right
            if(bossTimer -> getTicks()>100)
            {
                yMin = 0.0;
                yMax = 0.3333333333333333333333;

                xMin -= 0.25;
                xMax -= 0.25;

                //xPos += 0.01;

                if(xMin > 0.0)
                {
                    actionBoss = 14;
                }
                else
                {
                    xMin = 0.0;
                    xMax = 0.25;
                    actionBoss = 15;
                }
                bossTimer -> reset();
            }
            //cout << "teleporting case 14" << endl;
        break;

        case 15: //Standing facing right
            if((bossTimer -> getTicks()>100) && (bossSound->getTicks()>400) && (teleportOut))
            {
                yMin = 0.0;
                yMax = 0.3333333333333333333333;

                xMin += 0.25;
                xMax += 0.25;

                //xPos += 0.01;

                if(xMax <= 1.0)
                {
                    actionBoss = 15;
                }
                else
                {
                    yMin = 0.3333333333333333333333;
                    yMax = 0.6666666666666666666666;
                    xMin = 0.0;
                    xMax = 0.25;
                    SND->pauseSound("snds/LA_Genie_Appear.wav");
                    teleportIn = true;
                    teleportOut = false;

                    actionBoss = 16;
                }

                bossTimer -> reset();
            }
           //cout << "teleporting case 15" << endl;
        break;

        case 16: //standing facing right
            if(bossTimer -> getTicks()>100)
            {
                yMin = 0.3333333333333333333333;
                yMax = 0.6666666666666666666666;

                xMin += 0.25;
                xMax += 0.25;

                //xPos += 0.01;

                if(xMax <= 1.0)
                {
                    actionBoss = 16;
                }
                else
                {
                    yMin = 0.6666666666666666666666;
                    yMax = 1.0;

                    xMin = 0.0;
                    xMax = 0.25;
                    actionBoss = 17;
                    attackPly = false;
                }
                bossTimer -> reset();
            }
            //cout << "teleporting case 16" << endl;
        break;

        case 17: //melting facing right
            if(bossTimer -> getTicks()>100)
            {
                yMin = 0.6666666666666666666666;
                yMax = 1.0;

                xMin += 0.25;
                xMax += 0.25;

                if(xMax <= 1.0)
                {
                    actionBoss = 17;
                }
                else
                {
                    //yMin = 0.666666666;
                    //yMax = 1.0;

                    xMin = 0.75;
                    xMax = 1.0;
                    actionBoss = 18;
                }
                bossTimer -> reset();
            }
            //cout << "teleporting case 17" << endl;
        break;

        case 18: //melting facing right
            if(bossTimer -> getTicks()>100)
            {
                yMin = 0.6666666666666666666667;
                yMax = 1.0;

                xMin = 0.75;
                xMax = 1.0;

                bossTimer -> reset();
            }
            //cout << "teleporting case 18" << endl;
        break;

        case 20: //melting facing right
            if((bossTimer -> getTicks()>100) && (bossSound->getTicks()>400))
            {
                yMin = 0.6666666666666666666667;
                yMax = 1.0;

                xMin = 0.75;
                xMax = 1.0;

                if(teleportIn)
                {
                    SND->pauseSound("snds/LA_Genie_Appear.wav");
                    teleportIn = false;
                    teleportOut = true;
                }

                actionBoss = 10;
            }
            //cout << "doing case 20 " << endl;
        break;

        case 21: //melting facing right
            if(bossTimer -> getTicks()>100)
            {
                yMin = 0.0;
                yMax = 0.3333333333333333333333;

                xMin = 0.0;
                xMax = 0.25;

                actionBoss = 0;
            }
            //cout << "doing case 21 " << endl;
        break;
    }
}


void EnemyBoss::bossAnimation(float x, float y)
{
        position.x = x;
        position.y = y;
}
