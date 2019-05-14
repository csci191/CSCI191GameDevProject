#include "sounds.h"
#include<iostream>
#include<string.h>
using namespace std;

ISoundEngine* engine = createIrrKlangDevice();

sounds::sounds()
{
    //cto
}

sounds::~sounds()
{
    //dtor
    engine->drop(); // delete engine
}

void sounds::playMusic(int i)
{
    music[i]->setIsPaused(false);
}

void sounds::playSound(ISoundSource* i)
{
    engine->play2D(i);
}

void sounds::pauseSound(char* File)
{
    engine->play2D(File, false,false);
}

void sounds::stopAllSounds()
{
    engine->stopAllSounds();
}

void sounds::MasterVolume(float v)
{
    engine->setSoundVolume(v);
}

void sounds::setMusic(char* file, bool play, int i)
{
    music[i] = engine->play2D(file, true, !play, true);
    //setMusicVolume(1);
}

void sounds::setSFXVolume(float v, int i)
{
    if(sfx[i])
    {
        sfx[i]->setDefaultVolume(v);
    }
}

void sounds::pauseMusic(int i)
{
    music[i]->setIsPaused(true);
}


void sounds::setSFX(char* file, int i)
{
    sfx[i] = engine->addSoundSourceFromFile(file);
}

void sounds::setMusicVolume(float v, int i)
{
    if(music)
    {
        music[i]->setVolume(v);
        cout << music[i]->getVolume() << endl;
    }
}


int sounds::initSounds()
{

    if (!engine)
    {
        cout<<"Could not startup engine\n";
        return 0; // error starting up the engine
    }
    return 1;
}


