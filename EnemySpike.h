#ifndef ENEMYSPIKE_H
#define ENEMYSPIKE_H

#include <GL/gl.h>
#include <TextureLoader.h>
#include <Timer.h>
#include <Player.h>
#include <iostream>
#include <string>
#include <Sounds.h>

using namespace std;

typedef struct
{
    float x,y,z;
}vecSpike;

class EnemySpike
{
    public:
        EnemySpike();
        virtual ~EnemySpike();

        void drawEnemy();
        void enemyActions();
        void enemyInit(char*);

        vec verticies[4];
        vec position;

        bool isEnemyLive = true;

        int Frames;
        int actionEnemy = 0;

        Timer *timeSpike = new Timer();
        TextureLoader *spike = new TextureLoader();

        float xMin, yMin, xMax, yMax;

        float xMove, yMove;

    protected:

    private:
};

#endif // ENEMYSPIKE_H
