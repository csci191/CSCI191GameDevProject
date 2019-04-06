#ifndef MAPLOADER_H
#define MAPLOADER_H

#include<GL/gl.h>
#include<TextureLoader.h>

class MapLoader
{
	public:
		MapLoader();
		MapLoader(float,float,float,float, float); //constructor to initialize tex coord to cutom values
		virtual ~MapLoader();

		TextureLoader *bgTexture = new TextureLoader();

		void drawBG(float, float);	//Function to draw square with background texture
		void mapMovement(std::string direction); //Changes coordinates to move to different zones

		float xMax, xMin, yMax, yMin; //Texture coordinates
		float moveIncrement; //Float to determine how much the map will move by in the mapMove func
		float xD, yD;
	protected:
	private:
};
#endif
