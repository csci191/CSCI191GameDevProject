#ifndef GLSCENE_H
#define GLSCENE_H

#include <string.h>
#include<windows.h>
#include<GL/glut.h>
class GLScene
{
    public:
        GLScene();
        virtual ~GLScene();
        GLint initGL();
        GLint drawScene();
        GLvoid resizeGLScene(GLsizei, GLsizei);

        int winMsg(HWND, UINT, WPARAM, LPARAM);
        float screenWidth;
        float screenHeight;
        bool pause = false;
        bool startMenu = true;
        bool mainMenu = false;
        bool exitGame = false;

        WPARAM wParam;

    protected:

    private:
};

#endif // GLSCENE_H
