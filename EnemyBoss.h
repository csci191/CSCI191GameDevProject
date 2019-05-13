#ifndef ENEMYBOSS_H
#define ENEMYBOSS_H

#include <GL/gl.h>
#include <TextureLoader.h>
#include <Timer.h>
#include <Player.h>
#include <iostream>
#include <string>

using namespace std;

typedef struct
{
    float x,y,z;
}vecBoss;

class EnemyBoss
{
    public:
        EnemyBoss();
        virtual ~EnemyBoss();

        vec verticies[4];
        vec position; // the boss x,y,z position

        void drawBoss();
        void bossInit(char* );
        void bossAppear(int);
        void bossSpawn();
        void bossActions();
        void bossAnimation(float, float);

        float xMin, yMin, xMax, yMax;
        float xPos, yPos;
        float tempMin, tempMax;
        int speed;
        int currentPosition;
        int prevPosition;
        int actionBoss = 0;
        int placementBoss = 0;
        std::string actionTrigger;

        float xMove, yMove;
        bool appear = false;

        TextureLoader* bossTex = new TextureLoader();
        Timer* bossTimer = new Timer();
        Timer* bossTimerAppear = new Timer();
        Timer* bossSpawner = new Timer();

    protected:

    private:
};

#endif // ENEMYBOSS_H
