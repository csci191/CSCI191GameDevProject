#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include<iostream>
#include<SOIL.h>
#include<gl/gl.h>

class TextureLoader
{
    public:
        TextureLoader();
        virtual ~TextureLoader();

        void loadTexture(char *);
        void binder();

        unsigned char* image;
        int width, height;

        GLuint tex;
    protected:

    private:
};

#endif // TEXTURELOADER_H
