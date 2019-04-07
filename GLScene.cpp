#include "GLScene.h"
#include <MapLoader.h>
#include <Player.h>
#include <Inputs.h>

MapLoader *Map1 = new MapLoader(0.0244, 0.0435,0.1463,0.2609,0.2174,0.1219); //yMin, xMin, yMax, xMax, xInc,yInc
Player *Ply = new Player();
Inputs *keyB = new Inputs();
float tempx, tempy;

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

    Map1->mapInit("images/Maps/Map1.png");
    Ply->playerInit("images/pix.png");
}

GLint GLScene::drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix

    glScaled(3.33,3.33,1.0);

    glPushMatrix();
    Map1->drawBG(screenWidth, screenHeight);
    glPushMatrix();

    glPushMatrix();
    Ply->drawPlayer();
    glPopMatrix();

    if (Ply->position.x >= 1.3 || Ply->position.x<=-1.7)
    {
        if(Ply->position.x >= 1.3){
            Ply->position.x = -1.5;
            Map1->mapMovement("right");
        }else{
            Ply->position.x = 1.1;
            Map1->mapMovement("left");
        }
    }
    if(Ply->position.y >= 0.76 || Ply->position.y <= -0.9)
    {
        if(Ply->position.y > 0.76){
            Ply->position.y = -0.8;
            Map1->mapMovement("up");
        }else{
            Ply->position.y = 0.7;
            Map1->mapMovement("down");
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
            keyB->playerAction(Ply);
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
