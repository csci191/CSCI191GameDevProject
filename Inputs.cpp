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


void Inputs::playerAction(player* pl)
{
     switch(wParam){

        case VK_LEFT:
            if(pl->actionTrigger=="Right"){
                float temp= pl->xMax;
                pl->xMax=ply->xMin;
                pl->xMin=temp;
            }
            pl->actionTrigger= "Left";

            break;
        case VK_RIGHT:

           if(pl->actionTrigger=="Left"){
                float temp= pl->xMax;
                pl->xMax=pl->xMin;
                pl->xMin=temp;
            }
            pl->actionTrigger="Right";
            break;
        case VK_UP:
             if(pl->actionTrigger=="Down"){
                float temp= pl->yMax;
                pl->yMax=pl->yMin;
                pl->yMin=temp;
            }
            pl->actionTrigger="Up";
            break;
        case VK_DOWN:
             if(pl->actionTrigger=="Up"){
                float temp= pl->yMax;
                pl->yMax=pl->yMin;
                pl->yMin=temp;
            }
            pl->actionTrigger="Down";
            break;

        
        }
}


