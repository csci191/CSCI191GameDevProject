#include "GLScene.h"
#include <MapLoader.h>
#include <Player.h>
#include <Inputs.h>
#include <TextureLoader.h>
#include <Parallax.h>
#include <objects.h>
#include <EnemyChar.h>

MapLoader *Map1 = new MapLoader(0.0244, 0.0435,0.1463,0.2609,0.2174,0.1219); //yMin, xMin, yMax, xMax, xInc,yInc
Player *Ply = new Player();
Inputs *keyB = new Inputs();
EnemyChar *EChar = new EnemyChar();
/*     Enemy Texture     */
TextureLoader *ETex = new TextureLoader();
float tempx, tempy;

/* START MENU'S TEXTURE AND OBJECTS */
objects* StartObjects = new objects();           // STARTMENU MAIN LOGO OBJECT
objects* StartObjects1 = new objects();          // STARTMENU CONTROL OJBECT
Parallax* StartPara = new Parallax();            // STARTMENU PARALLAX
TextureLoader* StartLogo = new TextureLoader();
TextureLoader* StartBG = new TextureLoader();
TextureLoader* StartPress = new TextureLoader();

/* MAIN MENU'S TEXTURE AND OBJECTS */
objects MMObjects[3];
Parallax* MMPara = new Parallax();
TextureLoader* MMStart = new TextureLoader();
TextureLoader* MMOption = new TextureLoader();
TextureLoader* MMQuit = new TextureLoader();
TextureLoader* MMBG = new TextureLoader();

/* MAIN GAME'S TEXTURE AND OBJECTS */
TextureLoader* RQTex = new TextureLoader();    // TEXTURE FOR OPTION WINDOW
objects* RQ = new objects();                   // OBJECT FOR OPTION WINDOW
Parallax* GamePara = new Parallax();           // PARALLAX FOR GAME

/* ARROW CURSOR */
objects* arrow = new objects();            // ARROW OBJECT
TextureLoader* AT = new TextureLoader();   // ARROW TEXTURE

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
    Map1->mapInit("images/Maps/Map1.png");
    RQTex->loadTexture("images/RQ.png");
    GamePara->paraTex = Map1->bgTexture->tex;              // LOAD PARLLAX
    RQ->objectTex = RQTex->tex;

    Ply->playerInit("images/pix.png");             // INITIALIZE TEXTURE FOR PLAYER
    ETex->loadTexture("images/enemy.png");                  //Enemy texture
    EChar->enemyTex = ETex->tex;

    AT->loadTexture("images/arrow.png");
    arrow->objectTex = AT->tex;
    arrow->position.y = -.2;
    EChar->enemyInit();
}

GLint GLScene::drawScene()
{
    if(startMenu) // RENDERS STARTMENU
    {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();


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
    }

    else if(!mainMenu && !startMenu) // RENDERS MAIN GAME
    {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        if(pause) // POPUP WINDOW FOR QUITTING
        {
            glPushMatrix();
            glScaled(.2,.2,1);
            glTranslated(0,0,-1);
            RQ->drawObj();
            glPopMatrix();
        }

    glScaled(3.33,3.33,1.0);

    glPushMatrix();
    Map1->drawBG(screenWidth, screenHeight);
    glPushMatrix();

    glPushMatrix();
    Ply->drawPlayer();
    glPopMatrix();

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
    }else if (EChar->yPos > 0.1)
    {
            EChar->yMove = -0.001;
            EChar->actionEnemy = 2;
    }else if (EChar->yPos < -0.1)
    {
        EChar->yMove = 0.001;
        EChar->actionEnemy = 3;
    }

    EChar->drawEnemy();
    EChar->enemyActions();
    EChar->xPos += EChar->xMove;
    EChar->yPos += EChar->yMove;
    glPopMatrix();

    if (Ply->position.x >= 1.3 || Ply->position.x<=-1.7)
    {
        if(Ply->position.x >= 1.3){
            Ply->position.x = -1.5;
            Map1->mapMovement("right");
            EChar->isEnemyLive = false;
        }else{
            Ply->position.x = 1.1;
            Map1->mapMovement("left");
            EChar->isEnemyLive = false;
        }
    }
    if(Ply->position.y >= 0.76 || Ply->position.y <= -0.9)
    {
        if(Ply->position.y > 0.76){
            Ply->position.y = -0.8;
            Map1->mapMovement("up");
            EChar->isEnemyLive = false;
        }else{
            Ply->position.y = 0.7;
            Map1->mapMovement("down");
            EChar->isEnemyLive = false;
        }
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
                //KbMs ->keyPressed(mdl);
                if(!pause){keyB ->playerAction(Ply);}
            }
            if(mainMenu)
            {
                arrow->position.y = keyB->keyArrow(arrow->position.y);
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
