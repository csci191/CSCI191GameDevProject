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
    int tempf = 0;
    for (int i = 0; i < 6; i ++){
        for (int j = 0; j < 6; j++){
            frameNumbers[i][j] = tempf;
            tempf++;
        }

    }

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
void MapLoader::mapInit(char *FileName, char *SecondFile)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    bgTexture->loadTexture(FileName);
    mapFile = SecondFile;
    mp->initFrames(mapFile, 0);
}
int MapLoader::objectPosition(float x, float y)
{
    float xMarkMin = -1.775;
    float xinc = 0.3145;
    float yinc = 0.17;
    float xMarkMax = xMarkMin + xinc;
    float yMarkMax = 0.8;
    float yMarkMin = yMarkMax - yinc;
    int yP = 0;
    int xP = 0;
    for (int i = 0; i < 10; i ++){
        if (x >= xMarkMin && x <= xMarkMax){
            xP = i;
        }
        if(y >= yMarkMin && y <= yMarkMax){
            yP = i*10;
        }
        xMarkMax += xinc;
        xMarkMin += xinc;
        yMarkMax -= yinc;
        yMarkMin -= yinc;
    }
    return yP + xP;
}

void MapLoader::checkMapMovement(Player* Ply, std::string direction)
{
        if (Ply->position.x >= 1.3 || Ply->position.x<=-1.7)
        {
        if(Ply->position.x >= 1.3){
            if ( (mp->frame+1) < 36 ){
                    if (mp->frameConnections[mp->frame][mp->frame+1] == 1 &&
                       (Ply->prevPosition >= mp->doorList[mp->frame][2] && Ply->prevPosition <= mp->doorList[mp->frame][3])
                        )
                    {
                        Ply->position.x = -1.65;
                        mapMovement("right");
                        mp->initFrames(mapFile, mp->frame + 1);
                        Ply->currentPosition = objectPosition(Ply->position.x, Ply->position.y);
                        Ply->prevPosition = Ply->currentPosition;

                    }else {
                    Ply->position.x = 1.29;
                    }
            }else {
                Ply->position.x = 1.29;
            }

        }else{
            if ( (mp->frame -1) >= 0){
                if (mp->frameConnections[mp->frame][mp->frame - 1] == 1 &&
                    (Ply->prevPosition >= mp->doorList[mp->frame][0] && Ply->prevPosition <= mp->doorList[mp->frame][1])
                    ){
                    Ply->position.x = 1.25;
                    mapMovement("left");
                    mp->initFrames(mapFile, mp->frame - 1);
                    Ply->currentPosition = objectPosition(Ply->position.x, Ply->position.y);
                    Ply->prevPosition = Ply->currentPosition;
                }else {
                    Ply->position.x = -1.69;
                }
            }else {
                Ply->position.x = -1.69;
            }

        }
        }
//============================================================

        if(Ply->position.y >= 0.76 || Ply->position.y <= -0.9)
        {

            if(Ply->position.y >= 0.76){
                    if ( (mp->frame - 4) >= 0 ){
                        if(mp->frameConnections[mp->frame][mp->frame - 4] == 1 &&
                           (Ply->currentPosition >= mp->doorList[mp->frame][4] && Ply->currentPosition <= mp->doorList[mp->frame][5])
                           ){
                            Ply->position.y = -0.85;
                            mapMovement("up");
                            mp->initFrames(mapFile, mp->frame - 4);
                            Ply->currentPosition = objectPosition(Ply->position.x, Ply->position.y);
                            Ply->prevPosition = Ply->currentPosition;
                        }else {
                            Ply->position.y = 0.759;
                        }
                    }else {
                        Ply->position.y = 0.759;
                    }

            }else{
                if ( (mp->frame + 4) < 36 ){
                    if ( (mp->frameConnections[mp->frame][mp->frame + 4]) == 1 &&
                        (Ply->prevPosition >= mp->doorList[mp->frame][6] && Ply->prevPosition <= mp->doorList[mp->frame][7])
                        ){
                        Ply->position.y = 0.71;
                        mapMovement("down");
                        mp->initFrames(mapFile, mp->frame + 4);
                        Ply->currentPosition = objectPosition(Ply->position.x, Ply->position.y);
                        Ply->prevPosition = Ply->currentPosition;
                    }else {
                        Ply->position.y = -0.88;
                    }
                }else {
                    Ply->position.y = -0.88;
                }

            }
        }

}

void MapLoader::checkMapCollision(Player* pl,  std::string direction)
{
    if (direction == "left"){
        pl->currentPosition = objectPosition(pl->position.x, pl->position.y);
            if ( pl->currentPosition != pl->prevPosition ){
               if( mp->checkConnection(pl->currentPosition, pl->prevPosition) ){
                    pl->prevPosition = pl->currentPosition;
               }else {
                    pl->position.x += .5/100 * pl->speed;
                    pl->currentPosition = pl->prevPosition;
               }
            }
    }else if(direction == "right"){
        pl->currentPosition = objectPosition(pl->position.x, pl->position.y) ;
            if ( pl->currentPosition != pl->prevPosition ){
               if( mp->checkConnection(pl->currentPosition, pl->prevPosition) ){
                    pl->prevPosition = pl->currentPosition;
               }else {
                    pl->position.x -= .5/100 * pl->speed;
                    pl->currentPosition = pl->prevPosition;
               }
            }
    }else if(direction == "up"){
        pl->currentPosition = objectPosition(pl->position.x, pl->position.y) ;
            if ( pl->currentPosition != pl->prevPosition ){
               if( mp->checkConnection(pl->currentPosition, pl->prevPosition) ){
                    pl->prevPosition = pl->currentPosition;
               }else {
                    pl->position.y -= .5/100 * pl->speed;
                    pl->currentPosition = pl->prevPosition;
               }
            }
    }else if(direction == "down"){
         pl->currentPosition = objectPosition(pl->position.x, pl->position.y);
            if ( pl->currentPosition != pl->prevPosition ){
               if( mp->checkConnection(pl->currentPosition, pl->prevPosition) ){
                    pl->prevPosition = pl->currentPosition;
               }else {
                    pl->position.y += .5/100 * pl->speed;
                    pl->currentPosition = pl->prevPosition;
               }
            }
    }
}

 std::vector<float> MapLoader::objectPositioner(int pos)
{
    float xMPS = -1.775;
    float xinc = 0.3145;
    float yinc = 0.17;
    float yMPS = 0.8;
    int xLoc, yLoc;

    xLoc = pos % 10;
    yLoc = (pos-xLoc)/10 ;

    float xcoord = xMPS + (xinc * xLoc);
    xcoord += 0.0125;
    float ycoord = yMPS - (yinc * yLoc);
    ycoord -= 0.06;
    std::vector<float> positions;
    positions.push_back(xcoord);
    positions.push_back(ycoord);
    return positions;

}

