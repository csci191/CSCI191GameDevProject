#ifndef GLSCENE_H
#define GLSCENE_H
#include<windows.h>
#include<GL/glut.h>
#include<string.h>

class GLScene
{
    glutGet();
    public:
        GLScene(); //constructor
        virtual ~GLScene();

        GLint initGL();//fixed size of int, cross platform
        GLint drawScene();
        GLvoid resizeGLScene(GLsizei, GLsizei);

        bool pause = false;
        bool startMenu = true;
        bool mainMenu = false;
        bool exitGame = false;

        int winMsg(HWND,UINT,WPARAM,LPARAM);
        float screenWidth, screenHeight;
        void updateUI(bool, int);
        void UI();

    protected:

    private:
};

#endif // GLSCENE_H
