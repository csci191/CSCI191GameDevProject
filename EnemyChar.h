#ifndef ENEMYCHAR_H
#define ENEMYCHAR_H

#include <GL/gl.h>
#include <TextureLoader.h>
#include <Timer.h>
//#include <Player.h>

typedef struct
{
    float x;
    float y;
    float z;
}vecEnm;

class EnemyChar
{
    public:
        EnemyChar();
        virtual ~EnemyChar();

        void drawEnemyChar();
        void enemycharInit(char*);
        void enemycharActions();
        void enemycharMove(int);

        //void collision(Player*);

        int actionTrigger;
        vecEnm verticies[4];
        vecEnm position;
        float xMin, yMin, xMax, yMax;

        float xPos, yPos, zPos;
        float xSize, ySize;
        int eMax, eMin;
        int speed;

        TextureLoader *TEnmChar = new TextureLoader();
        Timer *TimeEnmChar = new Timer();

    protected:

    private:
};

#endif // ENEMYCHAR_H
