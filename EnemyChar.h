#ifndef ENEMYCHAR_H
#define ENEMYCHAR_H

#include <GL/gl.h>
#include <TextureLoader.h>
#include <Timer.h>

class EnemyChar
{
    public:
        EnemyChar();
        virtual ~EnemyChar();

        void drawEnemy();
        void placeEnemy(float, float, float);
        void enemyActions();
        void enemyInit();

        bool isEnemyLive = true;
        GLuint enemyTex;

        float xPos;
        float yPos;
        float zPos;

        float xSize;
        float ySize;
        float zSize;

        float rotateX;
        float rotateY;
        float rotateZ;

        int Frames;
        int actionEnemy = 0;

        Timer *TE = new Timer();

        float xMin;
        float xMax;
        float yMax;
        float yMin;

        float xMove, yMove;

    protected:

    private:
};

#endif // ENEMYCHAR_H
