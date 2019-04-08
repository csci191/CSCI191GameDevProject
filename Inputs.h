#ifndef INPUTS_H
#define INPUTS_H
#include<windows.h>
//#include<Model.h>
//#include<Parallax.h>
#include<Player.h>
#include<GLScene.h>


class Inputs
{
    public:
        Inputs();
        virtual ~Inputs();



//         void keyEn(Parallax*, float); // move parallax

        float keyArrow(float);
      void Menu(GLScene*, float);

        void playerAction(Player*);


        double prev_mouse_X;
        double prev_mouse_Y;

        bool mouse_Translate;
        bool mouse_Rotate;

        WPARAM wParam;




    protected:

    private:
};

#endif // INPUTS_H
