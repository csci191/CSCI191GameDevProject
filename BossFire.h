#ifndef BOSSFIRE_H
#define BOSSFIRE_H

#include <GL/gl.h>
#include <TextureLoader.h>
#include <Timer.h>
#include <Player.h>
#include <iostream>
#include <string>
#include <Sounds.h>
#include <EnemyBoss.h>
#include <Player.h>

using namespace std;

typedef struct
{
    float x,y,z;
}vecFire;

class BossFire
{
    public:
        BossFire();
        virtual ~BossFire();

        void drawFire();
        void fireActions(EnemyBoss*);
        void fireInit(char*);
        void attackFire(Player*, EnemyBoss*);

        vec verticies[4];
        vec position;

        bool isFireLive = true;

        int Frames;
        int actionEnemy = 0;
        bool attacking = true;
        int bossAttacking;


        Timer *timeFire = new Timer();
        TextureLoader *texFire = new TextureLoader();

        float xMin, yMin, xMax, yMax;

        float xMove, yMove;

        float tempPlayerX, tempPlayerY;

    protected:

    private:
};

#endif // BOSSFIRE_H
