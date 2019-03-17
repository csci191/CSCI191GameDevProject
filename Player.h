#ifndef PLAYER_H
#define PLAYER_H
#include<GL/gl.h>
#include<textureLoader.h>

typedef struct
{
    float x,y,z;
}vec;

class Player
{
    public:
        Player();
        virtual ~Player();
        vec verticies[4];
        vec position; // the players x,y,z position

        void drawPlayer();
        void playerInit(char* );
        void playActions(string);
        void playerAnimation();

        float xmin, ymin, xmax, ymax;
        int speed;

    protected:

    private:
};

#endif // PLAYER_H
