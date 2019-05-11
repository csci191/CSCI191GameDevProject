#include "GLScene.h"
#include <MapLoader.h>
#include <Player.h>
#include <Inputs.h>
#include <textureLoader.h>
#include <Parallax.h>
#include <objects.h>
#include <EnemyChar.h>
#include<ANIMATOR.H>

#include<iostream>
#include<string.h>
using namespace std;

MapLoader *Map1 = new MapLoader(0.0244, 0.0435,0.1463,0.2609,0.2174,0.1219); //yMin, xMin, yMax, xMax, xInc,yInc
Player *Ply = new Player();
Inputs *keyB = new Inputs();
EnemyChar *EChar = new EnemyChar();

/*     Enemy Texture     */
textureLoader *ETex = new textureLoader();
float tempx, tempy;

/* START MENU'S TEXTURE AND OBJECTS */
objects* StartObjects = new objects();           // STARTMENU MAIN LOGO OBJECT
objects* StartObjects1 = new objects();          // STARTMENU CONTROL OJBECT
Parallax* StartPara = new Parallax();            // STARTMENU PARALLAX
textureLoader* StartLogo = new textureLoader();
textureLoader* StartBG = new textureLoader();
textureLoader* StartPress = new textureLoader();

/* MAIN MENU'S TEXTURE AND OBJECTS */
objects MMObjects[3];
Parallax* MMPara = new Parallax();
textureLoader* MMStart = new textureLoader();
textureLoader* MMOption = new textureLoader();
textureLoader* MMQuit = new textureLoader();
textureLoader* MMBG = new textureLoader();

/* MAIN GAME'S TEXTURE AND OBJECTS */
textureLoader* RQTex = new textureLoader();    // TEXTURE FOR OPTION WINDOW
objects* RQ = new objects();                   // OBJECT FOR OPTION WINDOW
Parallax* GamePara = new Parallax();           // PARALLAX FOR GAME

/* ARROW CURSOR */
objects* arrow = new objects();            // ARROW OBJECT
textureLoader* AT = new textureLoader();   // ARROW TEXTURE

/*PLAYER HUD*/
textureLoader* HealthTex = new textureLoader();                     // health texture
Animator PlayerHealth[3];
textureLoader* ManaTex = new textureLoader();
Animator PlayerMana[6];

/* ATTACK */
textureLoader* attackTex = new textureLoader();
Animator* attackAnim = new Animator();

/* FIREBALL */
textureLoader* fireballTex = new textureLoader();
objects* fireball = new objects();

GLScene::GLScene()
{
    //ctor
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
}

GLScene::~GLScene()
{
    //dtor
}
GLint GLScene::initGL()
{
    glShadeModel(GL_SMOOTH);        //For good transitions and animations
    glClearColor(1.0f,0.0f,0.0f,0.0f);   //Set background color
    glClearDepth(1.0f);             //decide what is at the front and back
    glEnable(GL_DEPTH_TEST);        //for the depth calculations

    glEnable(GL_COLOR_MATERIAL);
    //GLLight Light(GL_LIGHT0);

    /* INITIALIZE FOR START MENU */
    StartLogo->loadTexture("images/Game.png");         // STORE LOGO TEXTURE
    StartPress->loadTexture("images/PressSpace.png");
    StartBG->loadTexture("images/StartMenu.png");      // STORE PARALLAX TEXTURE
    StartObjects->objectTex = StartLogo->tex;         // INITIALIZE LOGO TEXTURE
    StartObjects1->objectTex = StartPress->tex;
    StartPara->paraTex = StartBG->tex;                // INITIALIZE PARALLAX TEXTURE

    /* INITIALIZE FOR Main Menu */
    MMStart->loadTexture("images/MMStart.png");
    MMQuit->loadTexture("images/MMQuit.png");
    MMBG->loadTexture("images/MainMenu.png");
    MMObjects[0].objectTex = MMStart->tex;
    MMObjects[1].objectTex = MMQuit->tex;
    MMPara->paraTex = MMBG->tex;

    /* INITIALIZE FOR GAME */
    Map1->mapInit("images/Maps/Map1.png", "mapData/Map1.txt");
    RQTex->loadTexture("images/inventory.png");
    GamePara->paraTex = Map1->bgTexture->tex;              // LOAD PARLLAX
    RQ->objectTex = RQTex->tex;

    Ply->playerInit("images/pix.png");             // INITIALIZE TEXTURE FOR PLAYER
    ETex->loadTexture("images/enemy.png");                  //Enemy texture
    EChar->enemyTex = ETex->tex;

    AT->loadTexture("images/arrow.png");
    arrow->objectTex = AT->tex;
    arrow->position.y = -.2;
    EChar->enemyInit();

    /*PLAYER HUD*/
    /* HEALTH */
    HealthTex[0].loadTexture("images/health.png");
    for(int i=0; i<3; i++)
    {
        PlayerHealth[i].tex = HealthTex->tex;
        PlayerHealth[i].xmin = 0.0;
        PlayerHealth[i].xmax = 0.5;
        PlayerHealth[i].show = true;
        PlayerHealth[i].animInit((float)PlayerHealth[i].xmin, (float)PlayerHealth[i].xmax, 0, 1);
    }

    /* MANA */
    ManaTex->loadTexture("images/mana.png");
    for(int j=0; j<6; j++)
    {
        PlayerMana[j].tex = ManaTex->tex;
        PlayerMana[j].xmin = 0.5;
        PlayerMana[j].xmax = 1.0;
        PlayerMana[j].show = true;
        PlayerMana[j].animInit((float)PlayerMana[j].xmin, (float)PlayerMana[j].xmax, 0, 1);
    }

    /* ATTACK */
    attackAnim->animInit((float)3/6, (float)4/6, (float)1/4, (float)2/4);
    attackTex->loadTexture("images/attack.png");
    attackAnim->tex = attackTex->tex;

    /* FIREBALL */
    fireballTex->loadTexture("images/fireball.png");
    fireball->objectTex = fireballTex->tex;
    fireball->show = false;

    Ply->currentPosition = Map1->objectPosition(Ply->position.x, Ply->position.y);
    Ply->prevPosition = Ply->currentPosition;
}

GLint GLScene::drawScene()
{
    if(startMenu) // RENDERS STARTMENU
    {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        /* BACKGROUND */
        glPushMatrix();
        StartPara->drawSquare(screenWidth,screenHeight);
        glPopMatrix();

        glPushMatrix();
        glScaled(.5,.25,1);
        glTranslated(-.5,-1.7,-1);
        StartObjects1->drawObj();
        glPopMatrix();

        glPushMatrix();
        glScaled(1,.5,1);
        glTranslated(-.5,-.15,-1);
        StartObjects->drawObj();
        glPopMatrix();
    }
    else if(mainMenu) // RENDERS MAINMENU
    {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        glPushMatrix();
        MMPara->drawSquare(screenWidth,screenHeight);
        glPopMatrix();

        if(arrow->position.y > 1)
        {
            arrow->position.y = -.2;
            arrow->position.x = -6.4;
        }

        /* ARROW CURSOR */
        glPushMatrix();
        glScaled(.05,.05,1);
        glTranslated(2.5,arrow->position.y,-1);
        arrow->drawObj();
        glPopMatrix();

        glPushMatrix();
        glScaled(.3,.3,1);
        glTranslated(-.5,-.5,-1);
        MMObjects[0].drawObj();
        glPopMatrix();

        glPushMatrix();
        glScaled(.3,.3,1);
        glTranslated(-.5,-1.5,-1);
        MMObjects[1].drawObj();
        glPopMatrix();

        /* RESETS HEALTH AND MANA */
        Ply->health = 3;
        Ply->mana = 6;

        for(int i=0; i<3; i++)
        {
            PlayerHealth[i].tex = HealthTex->tex;
            PlayerHealth[i].xmin = 0.0;
            PlayerHealth[i].xmax = 0.5;
            PlayerHealth[i].show = true;
            PlayerHealth[i].animInit((float)PlayerHealth[i].xmin, (float)PlayerHealth[i].xmax, 0, 1);
        }

        for(int j=0; j<6; j++)
        {
            PlayerMana[j].tex = ManaTex->tex;
            PlayerMana[j].xmin = 0.5;
            PlayerMana[j].xmax = 1.0;
            PlayerMana[j].show = true;
            PlayerMana[j].animInit((float)PlayerMana[j].xmin, (float)PlayerMana[j].xmax, 0, 1);
        }
    }

    else if(!mainMenu && !startMenu) // RENDERS MAIN GAME
    {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        std::cout << Ply->mana << std::endl;

        /* DRAWS BAGGROUND */
        glPushMatrix();
        glScaled(3.33,3.33,1.0);
        Map1->drawBG(screenWidth, screenHeight);
        glPopMatrix();

        /* DRAWS HUD*/
        updateUI(true, Ply->health);
        updateUI(false, Ply->mana);
        UI();

        /* DRAWS PLAYER */
        glPushMatrix();
        glScaled(3.33,3.33,1.0);
        Ply->drawPlayer();
        glPopMatrix();

        /* DRAWS ATTACKS */
        if(attackAnim->show)
        {
            glPushMatrix();
            glScaled(1,1,1.0);
            attackAnim->position.x = Ply->position.x -.3;                     // SETS POSITION TO WHERE PLAYERS X POSITION IS
            attackAnim->position.y = Ply->position.y -.3;                     // SETS POSITION TO WHERE PLAYERS Y POSITION IS
            glTranslated(attackAnim->position.x, attackAnim->position.y,-2);
            attackAnim->animDraw();                                           // DRAWS THE ATTACK
            attackAnim->play = true;
            attackAnim->playAnimation();                                      // PLAYS THE ATTACK ANIMATION
            glPopMatrix();
        }

        /* DRAWS FIREBALL */
        if(fireball->show)
        {
            glPushMatrix();
            glScaled(.1,.1,1);
            if(!pause)
                fireball->moveObj(fireball->objDir);

            glTranslated(fireball->position.x, fireball->position.y,-2);
            fireball->drawObj();
            glPopMatrix();
        }


        glPushMatrix();
        if(EChar->xPos < -0.1)
        {
            EChar->xMove = 0.001;
            EChar->actionEnemy = 1;
        }
        else if (EChar->xPos > 0.1)
        {
            EChar->xMove = -0.001;
            EChar->actionEnemy = 0;
        }
        else if (EChar->yPos > 0.1)
        {
            EChar->yMove = -0.001;
            EChar->actionEnemy = 2;
        }
        else if (EChar->yPos < -0.1)
        {
            EChar->yMove = 0.001;
            EChar->actionEnemy = 3;
        }

        if(pause) // POPUP WINDOW FOR QUITTING
        {
            if(arrow->position.y < 1)
            {
                arrow->position.y = 7;
                arrow->position.x = -2;
            }

            glPushMatrix();
            glScaled(.05,.05,1);
            glTranslated(arrow->position.x,arrow->position.y,-1);
            arrow->drawObj();
            glPopMatrix();

            glPushMatrix();
            glScaled(.5,.5,1);
            glTranslated(-.5,0,-1);
            RQ->drawObj();
            glPopMatrix();
            glEnd();
        }

        glPushMatrix();
        glScaled(3.33,3.33,1.0);
        EChar->drawEnemy();
        if(!pause)
        {
            EChar->enemyActions();
            EChar->xPos += EChar->xMove;
            EChar->yPos += EChar->yMove;
            glPopMatrix();
        }
    }
}

void GLScene::UI()
{
    /* DISPLAY HEALTH */
    for(int a=0; a<3; a++)
    {
        glPushMatrix();
        glScaled(.05,.05,1.0);
        glTranslated(-15+a,7,-1);
        PlayerHealth[a].animDraw();
        glPopMatrix();
    }

    /* DISPLAY MANA */
    for(int i=0; i<6; i++)
    {
        glPushMatrix();
        glScaled(.05,.05,1.0);
        glTranslated(-15+i,6,-1);
        PlayerMana[i].animDraw();
        glPopMatrix();
    }
}

void GLScene::updateUI(bool red, int point)
{
    /* UPDATES HEALTH UI */
    if(red)
    {
        for(int i=0; i<3-point; i++)
        {
            PlayerHealth[i].xmin = 0.5;
            PlayerHealth[i].xmax = 1.0;
            PlayerHealth[i].animInit((float)PlayerHealth[i].xmin, (float)PlayerHealth[i].xmax, 0, 1);
        }
    }
    /* UPDATES MANA UI */
    else
    {
        for(int j=0; j<6-point; j++)
        {
            PlayerMana[j].tex = ManaTex->tex;
            PlayerMana[j].xmin = 0.0;
            PlayerMana[j].xmax = 0.5;
            PlayerMana[j].animInit((float)PlayerMana[j].xmin, (float)PlayerMana[j].xmax, 0, 1);
        }
    }

}

GLvoid GLScene::resizeGLScene(GLsizei width, GLsizei height)
{
    GLfloat aspectRatio = (GLfloat)width/(GLfloat)height;
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspectRatio, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);

}

int GLScene::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)									// Check For Windows Messages
    {

    case WM_KEYDOWN:
        keyB->wParam = wParam;
        if(!mainMenu && !startMenu)
        {
            if(!pause)
            {
                keyB ->playerAction(Ply, Map1);

                /* THIS HAS TO BE HERE TO WORK, IDK WHY */
                switch(wParam)
                {
                case 'Z':
                    /* UP ATTACK */
                    if(Ply->ymin==0)
                    {
                        attackAnim->animInit((float)3/6, (float)4/6, (float)0/4, (float)1/4);
                    }
                    /* LEFT ATTACK */
                    else if(Ply->ymin==.25)
                    {
                        attackAnim->animInit((float)3/6, (float)4/6, (float)1/4, (float)2/4);
                    }
                    /* DOWN ATTACK */
                    else if(Ply->ymin==.5)
                    {
                        attackAnim->animInit((float)3/6, (float)4/6, (float)2/4, (float)3/4);
                    }
                    /* RIGHT ATTACK */
                    else if(Ply->ymin==.75)
                    {
                        attackAnim->animInit((float)3/6, (float)4/6, (float)3/4, (float)4/4);
                    }

                    if(!attackAnim->show)
                        attackAnim->show = true;
                    break;
                case 'X':
                    if(Ply->mana>0)
                    {
                        Ply->mana -=1;
                        updateUI(false, Ply->mana);

                        fireball->position.x = 0;
                        fireball->position.y = 0;
                        if(Ply->ymin ==0)
                        {
                            fireball->objDir = "up";
                        }
                        else if(Ply->ymin == .25)
                        {
                            fireball->objDir = "left";
                            fireball->xmax = -1;
                        }
                        else if(Ply->ymin == .5)
                        {
                            fireball->objDir = "down";
                        }
                        else if(Ply->ymin == .75)
                        {
                            fireball->objDir = "right";
                            fireball->xmax = 1;
                        }
                        if(Ply->mana >0)
                            fireball->show = true;
                    }
                    break;
                }
            }
        }
        if(mainMenu || pause)
        {
            //arrow->position.y = keyB->keyArrow(arrow->position.y);
            keyB->keyArroe2(arrow, mainMenu);
        }
        keyB->Menu(this,arrow->position.y);
        break;

    case WM_KEYUP:								// Has A Key Been Released?
    {
        keyB->wParam = wParam;
        //Ply->actionTrigger = "stand";
        //KbMs->keyUP();

        break;								// Jump Back
    }

    case WM_LBUTTONDOWN:
    {
        //KbMs->wParam = wParam;
        //KbMs->mouseEventDown(MdlTpt, LOWORD(lParam),HIWORD(lParam));
        break;								// Jump Back
    }

    case WM_RBUTTONDOWN:
    {
        //KbMs->wParam = wParam;
        //KbMs->mouseEventDown(MdlTpt, LOWORD(lParam),HIWORD(lParam));
        break;								// Jump Back
    }

    case WM_MBUTTONDOWN:
    {
        //KbMs->wParam = wParam;
        //KbMs->mouseEventDown(MdlTpt, LOWORD(lParam),HIWORD(lParam));
        break;								// Jump Back
    }

    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
    {
        //KbMs->mouseEventUp();
        break;								// Jump Back
    }

    case WM_MOUSEMOVE:
    {
        //KbMs->mouseEventMove(MdlTpt, LOWORD(lParam),HIWORD(lParam));
        break;								// Jump Back
    }

    case WM_MOUSEWHEEL:
    {
        //KbMs->mouseWheel(MdlTpt, (double)GET_WHEEL_DELTA_WPARAM(wParam));
        break;								// Jump Back
    }

    }
}
