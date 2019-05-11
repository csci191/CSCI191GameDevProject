#include "Inputs.h"

Inputs::Inputs()
{
    //ctor
    double prev_mouse_X=0;
    double prev_mouse_Y=0;

    bool mouse_Translate=0;
    bool mouse_Rotate=0;
}
Inputs::~Inputs()
{
    //dtor
}


/*
void Inputs::keyEn(Parallax* plx, float speed)
{
    switch(wParam){
        case VK_UP:
            plx->scroll("up",speed);
            break;
        case VK_DOWN:
            plx->scroll("down",speed);
            break;
    }
}
*/

void Inputs::playerAction(Player* pl, MapLoader* MP)
{
    switch(wParam)
    {

    case VK_LEFT:
        //if(pl->actionTrigger=="Right"){
        //  float temp= pl->xmax;
        // pl->xmax=pl->xmin;
        // pl->xmin=temp;
        //}
        pl->playActions("left");

        //Block of code that detects collision with the map and reverts movements
        MP->checkMapCollision( pl,"left");
        MP->checkMapMovement(pl, "left");
        //*************************************************************************

        break;
    case VK_RIGHT:

        //if(pl->actionTrigger=="Left"){
        //   float temp= pl->xmax;
        // pl->xmax=pl->xmin;
        // pl->xmin=temp;
        //}
        pl->playActions("right");

        //Block of code that detects collision with the map and reverts movements
        MP->checkMapCollision(pl, "right");
        MP->checkMapMovement(pl, "right");
        //******************************************************************************
        break;
    case VK_UP:
        pl->playActions("up");

        //Block of code that detects collision with the map and reverts movements
        MP->checkMapCollision(pl, "up");
        MP->checkMapMovement(pl, "up");
        //************************************************************************

        break;
    case VK_DOWN:
        pl->playActions("down");

        //Block of code that detects collision with the map and reverts moveme nts
        MP->checkMapCollision(pl, "down");
        MP->checkMapMovement(pl, "down");
        //**********************************************************************
        break;

    }
}

void Inputs::Menu(GLScene* g, float arrow)
{
    switch(wParam)
    {
    case VK_SPACE:
        if(arrow >-6 && g->mainMenu==true)
        {
            g->mainMenu=false;
        }
        if(arrow <-6 && g->mainMenu==true)
        {
            g->exitGame=true;
        }
        if(g->startMenu)
        {
            g->startMenu = false;
            g->mainMenu = true;
        }
        break;
    case VK_ESCAPE:
        if(!g->pause && !g->startMenu && !g->mainMenu)
        {
            g->pause=true;
        }
        else
        {
            g->pause=false;
        }
        break;
    case 'Q':
        if(g->pause)
        {
            g->pause=false;
            g->mainMenu = true;
        }
        break;
    }
}

float Inputs::keyArrow(float y)
{
    switch(wParam)
    {
    case VK_UP:
        return -.2;
        break;
    case VK_DOWN:
        return -6.4;
        break;
    }
    return y;
}

void Inputs::keyArroe2(objects* ob,bool menu)
{
    switch(wParam)
    {
    case VK_UP:
        if(menu)
            ob->position.y = -.2;
        else
            ob->position.y = 7;
        break;
    case VK_DOWN:
        if(menu)
            ob->position.y = -6.4;
        else
            ob->position.y = 3;
        break;
    case VK_RIGHT:
        if((ob->position.y==7 || ob->position.y==3))
            ob->position.x = 2;
        break;
    case VK_LEFT:
        if((ob->position.y==7 || ob->position.y==3))
            ob->position.x = -2;
        break;
    }
}
