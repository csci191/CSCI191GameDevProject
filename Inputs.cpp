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

void Inputs::playerAction(Player* pl)
{
     switch(wParam){

        case VK_LEFT:
            //if(pl->actionTrigger=="Right"){
              //  float temp= pl->xmax;
               // pl->xmax=pl->xmin;
               // pl->xmin=temp;
            //}
            pl->playActions("left");

            break;
        case VK_RIGHT:

           //if(pl->actionTrigger=="Left"){
             //   float temp= pl->xmax;
               // pl->xmax=pl->xmin;
               // pl->xmin=temp;
            //}
            pl->playActions("right");
            break;
        case VK_UP:
             //if(pl->actionTrigger=="Down"){
               // float temp= pl->ymax;
               // pl->ymax=pl->ymin;
                //pl->ymin=temp;
            //}
            pl->playActions("up");
            break;
        case VK_DOWN:
             //if(pl->actionTrigger=="Up"){
               // float temp= pl->ymax;
                //pl->ymax=pl->ymin;
                //pl->ymin=temp;
            //}
            pl->playActions("down");
            break;


        }
}

 void Inputs::Menu(GLScene* g, float arrow)
{
    switch(wParam)
    {
        case VK_SPACE:
            if(arrow >-6 && g->mainMenu==true){g->mainMenu=false;}
            if(arrow <-6 && g->mainMenu==true){g->exitGame=true;}
            if(g->startMenu){g->startMenu = false; g->mainMenu = true;}
            break;
        case VK_ESCAPE:
            if(!g->pause && !g->startMenu && !g->mainMenu){g->pause=true;}
            else{g->pause=false;}
            break;
        case 'Q':
            if(g->pause){g->pause=false; g->mainMenu = true;}
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

