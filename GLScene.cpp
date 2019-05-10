#include "GLScene.h"
#include <MapLoader.h>
#include <Player.h>
#include <Inputs.h>
#include <TextureLoader.h>
#include <Parallax.h>
#include <objects.h>
#include <EnemyChar.h>
#include<ANIMATOR.H>


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

/*PLAYER HUD*/
textureLoader HealthTex[2];
objects PlayerHealth[3];
textureLoader ManaTex[2];
objects PlayerMana[6];
textureLoader* attackTex = new textureLoader();
Animator* attackAnim = new Animator();
objects* plyAnim = new objects();

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
    HealthTex[0].loadTexture("images/FULLHEALTH.png");
    HealthTex[1].loadTexture("images/NOHEALTH.png");
    PlayerHealth[0].objectTex = HealthTex[1].tex;
    PlayerHealth[1].objectTex = HealthTex[1].tex;
    PlayerHealth[2].objectTex = HealthTex[1].tex;

    ManaTex[0].loadTexture("images/MANAFULL.png");
    ManaTex[1].loadTexture("images/MANAEMPTY.png");
    PlayerMana[0].objectTex = ManaTex[1].tex;
    PlayerMana[1].objectTex = ManaTex[1].tex;
    PlayerMana[2].objectTex = ManaTex[1].tex;
    PlayerMana[3].objectTex = ManaTex[1].tex;
    PlayerMana[4].objectTex = ManaTex[1].tex;
    PlayerMana[5].objectTex = ManaTex[1].tex;

    attackTex->loadTexture("images/attack.png");
    attackAnim->tex = attackTex->tex;	

    Ply->currentPosition = Map1->objectPosition(Ply->position.x, Ply->position.y);
    Ply->prevPosition = Ply->currentPosition;
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

    glScaled(3.33,3.33,1.0);
    glPushMatrix();
    Map1->drawBG(screenWidth, screenHeight);
    glPushMatrix();

    updateUI();	    
	    
    glPushMatrix();
    glScaled(3.33,3.33,1.0);
    Ply->drawPlayer();
    glPopMatrix();

    /* ATTACKS */
    glPushMatrix();
    glScaled(.5,.5,1.0);
    glTranslated(.1,.1,-2);
    attackAnim->animDraw();
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
	    
    glScaled(3.33,3.33,1.0);
    EChar->drawEnemy();	    
    if(!pause){	 
    EChar->enemyActions();
    EChar->xPos += EChar->xMove;
    EChar->yPos += EChar->yMove;
    glPopMatrix(); }


    }
}

void GLScene::updateUI()
{
    std::cout << Ply->health << std::endl;
    /* DISPLAY HEALTH */
    for(int a=0; a<3; a++)
    {
        glPushMatrix();
        glScaled(.05,.05,1.0);
        glTranslated(-15+a,7,-1);
        PlayerHealth[a].drawObj();
        //std::cout << PlayerHealth[a].objectTex << std::endl;
        glPopMatrix();
    }

    /* UPDATE HEALTH */
    for(int b=0; b<Ply->health;b++)
    {
        std::cout << PlayerHealth[b].objectTex << " " << HealthTex[0].tex<<std::endl;
        PlayerHealth[b].objectTex = HealthTex[0].tex;
    }

    /* DISPLAY MANA */
    for(int i=0;i<6; i++)
    {
        glPushMatrix();
        glScaled(.05,.05,1.0);
        glTranslated(-15+i,6,-1);
        PlayerMana[i].drawObj();
        glPopMatrix();
    }

    /* UPDATE MANA */
    for(int j=0; j<Ply->mana; j++)
    {
        PlayerMana[j].objectTex = ManaTex[0].tex;
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
                if(!pause){keyB ->playerAction(Ply, Map1);}
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
