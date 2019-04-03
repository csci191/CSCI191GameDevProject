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


void Inputs::playerAction(player* ply)
{
     switch(wParam){

        case VK_LEFT:
            if(ply->actionTrigger=="Right"){
                float temp= ply->xMax;
                ply->xMax=ply->xMin;
                ply->xMin=temp;
            }
            ply->actionTrigger= "Left";

            break;
        case VK_RIGHT:

           if(ply->actionTrigger=="Left"){
                float temp= ply->xMax;
                ply->xMax=ply->xMin;
                ply->xMin=temp;
            }
            ply->actionTrigger="Right";
            break;
        case VK_UP:
            ply->actionTrigger="Jump";
            break;
        case VK_DOWN:
            ply->actionTrigger="Down";
            break;

        case VK_TAB:
        ply->actionTrigger = "change";
        break;

        }
}


