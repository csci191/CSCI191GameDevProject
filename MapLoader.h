#ifndef MAPLOADER_H
#define MAPLOADER_H

#include<GL/gl.h>
#include<TextureLoader.h>
#include<Player.h>
#include<MapFrames.h>

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

		float xMax, xMin, yMax, yMin; //Texture coordinates
		float moveIncrementX, moveIncrementY; //Float to determine how much the map will move by in the mapMove func
		float xD, yD;

		MapFrames *mp = new MapFrames();
	protected:
	private:
};
#endif
