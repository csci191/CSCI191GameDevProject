#include "MapLoader.h"
#include <TextureLoader.h>


MapLoader::MapLoader()
{
	xMax = 1.0;
    xMin = 0.0;
    yMax = 1.0;
    yMin = 0.0;
    moveIncrementX = 0.001;
    moveIncrementY = 0.001;
    xD = xMax - xMin;
    yD = yMax - yMin;
}

MapLoader::MapLoader(float yMinCoor,float xMinCoor,float  yMaxCoor, float xMaxCoor,float xinc, float yinc)
{
	xMax = xMaxCoor;
    xMin = xMinCoor;
    yMax = yMaxCoor;
    yMin = yMinCoor;
    moveIncrementX = xinc;
    moveIncrementY = yinc;
    xD = xMax - xMin;
    yD = yMax - yMin;
}

MapLoader::~MapLoader()
{
	//Destructor
}

void MapLoader::drawBG(float width, float height)
{
	bgTexture->binder();
    glBegin(GL_POLYGON);
        glTexCoord2f(xMin,yMax);
        glVertex3f(-width/height, -1,-8.0f);

        glTexCoord2f(xMax,yMax);
        glVertex3f(width/height,-1,-8.0f);

        glTexCoord2f(xMax,yMin);
        glVertex3f(width/height,1,-8.0f);

        glTexCoord2f(xMin,yMin);
        glVertex3f(-width/height,1,-8.0f);

    glEnd();
}


void MapLoader::mapMovement(std::string direction)
{
	if (direction == "right" && xMax < 1.000){
		xMax += moveIncrementX;
		xMin += moveIncrementX;
		if (xMax > 1.000)     //If the map attempts to move out of bounds it readjusts to align with the edge of the image.
		{
			xMax = 1.000;
			xMin = xMax - xD;
		}
	}else if(direction == "left" && xMin > 0.000){
		xMax -= moveIncrementX;
		xMin -= moveIncrementX;
		if (xMin < 0.000){
			xMin = 0.000;
			xMax = xMin + xD;
		}
	}else if (direction == "up" && yMax < 1.000){
		yMax -= moveIncrementY;
		yMin -= moveIncrementY;
		if (yMin < 0.000)
		{
			yMin = 0.000;
			yMax = yMin + yD;
		}
	}else if(direction == "down" && yMin > 0.000){
		yMax += moveIncrementY;
		yMin += moveIncrementY;
		if (yMax > 1.000){
			yMax = 1.000;
			yMin = yMax - yD;
		}
	}
}
void MapLoader::mapInit(char *FileName)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    bgTexture->loadTexture(FileName);
}
