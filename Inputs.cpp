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

void Inputs::Menu(GLScene* g, float arrowX, float arrowY, Player* p)
{
    switch(wParam)
    {
    case VK_SPACE:
        if(!g->credit)
        {
            if(arrowY >-2.7 && g->mainMenu==true)
            {
                g->mainMenu=false;
            }
            if(arrowY <-6 && g->mainMenu==true)
            {
                g->exitGame=true;
            }
            if(arrowY < -2.7 && arrowY >-3 && g->mainMenu ==true)
            {
                g->credit = true;
            }
        }
        if(g->startMenu)
        {
            g->startMenu = false;
            g->mainMenu = true;
        }
        if(g->pause)
        {
            if(arrowX==-2 && arrowY==7 && p->healthPotion!=0)
            {
                if(p->health != p->maxHealth)
                {
                    p->healthPotion -=1;
                    p->health += 1;
                    g->updateUI(true, true, p->health);
                }
            }
            if(arrowX==-2 && arrowY==3)
            {
                if(p->mana != p->maxMana && p->manaPotion!=0)
                {
                    p->manaPotion -=1;
                    p->mana += 1;
                    g->updateUI(false, true, p->mana);
                }
            }
            if(arrowX==2 && arrowY==3)
            {
                if(p->maxMana < 12)
                {
                    p->maxMana += 3;
                    g->UI(true, false);
                }
            }
            if(arrowX==2 && arrowY==7)
            {
                if(p->maxHealth < 12)
                {
                    p->maxHealth += 1;
                    g->UI(true, true);
                }
            }
        }

        break;
    case VK_ESCAPE:
        if(g->credit)
        {
            if(g->credit)
                g->credit = false;
        }
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
            if(ob->position.y <=-6.4)
            {
                ob->position.y = -2.7;
            }
            else
            {
                ob->position.y = -.2;
            }
        else
            ob->position.y = 7;
        break;
    case VK_DOWN:
        if(menu)
            if(ob->position.y < -.2 && ob->position.y > -.3)
            {
                ob->position.y = -2.7;
            }
            else
            {
                ob->position.y = -6.4;
            }
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
