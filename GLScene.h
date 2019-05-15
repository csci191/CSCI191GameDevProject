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
        bool mainGame = false;
        bool exitGame = false;
        bool credit = false;

        int winMsg(HWND,UINT,WPARAM,LPARAM);
        float screenWidth, screenHeight;
        void updateUI(bool, bool, int);
        void UI(bool expand = NULL, bool red = NULL);
        void SoundUpdate();

    protected:

    private:
};

#endif // GLSCENE_H
