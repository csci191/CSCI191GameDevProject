#ifndef MAPLOADER_H
#define MAPLOADER_H

#include<GL/gl.h>
#include<TextureLoader.h>
#include<Player.h>
#include<MapFrames.h>
#include<EnemyChar.h>
#include <vector>

class MapLoader
{
	public:
		MapLoader();
		MapLoader(float,float,float,float, float, float); //constructor to initialize tex coord to cutom values
		virtual ~MapLoader();

		TextureLoader *bgTexture = new TextureLoader();

		void drawBG(float, float);	//Function to draw square with background texture
		void mapMovement(std::string direction); //Changes coordinates to move to different zones
		void mapInit(char *, char *);
		int objectPosition(float, float); //Function that returns which cell player is in
		void checkMapMovement(Player *, std::string);
		void checkMapCollision(Player *, std::string);
        std::vector<float> objectPositioner(int);

		float xMax, xMin, yMax, yMin; //Texture coordinates
		float moveIncrementX, moveIncrementY; //Float to determine how much the map will move by in the mapMove func
		float xD, yD;

		MapFrames *mp = new MapFrames();
		char *mapFile;

		int frameNumbers[6][6];
	protected:
	private:
};
#endif
