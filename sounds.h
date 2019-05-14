#ifndef SOUNDS_H
#define SOUNDS_H

#include<iostream>
#include<string.h>
using namespace std;

#include <SNDS/irrKlang.h>

#include <stdlib.h>
#include <iostream>

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll
using namespace irrklang;


using namespace std;

class sounds
{
    public:
        sounds();
        virtual ~sounds();
        void playMusic(int);
        void playSound(ISoundSource* );
        void pauseSound(char *);
        void stopAllSounds();
        void MasterVolume(float);
        int initSounds();

        ISound* music[3];
        ISoundSource* sfx[5];
        void setMusic(char*, bool, int);
        void setSFX(char*, int);
        void setMusicVolume(float, int);
        void setSFXVolume(float,int);
        void pauseMusic(int);
    protected:

    private:
};



#endif // SOUNDS_H
