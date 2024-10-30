#ifndef SPRITE_H
#define SPRITE_H


#include <SDL2/SDL.h>
#include <stdio.h>
#include <chrono>

/*
*   Ce component gère l'affichage d'un sprite
*/
class Sprite{
public:
	Sprite(SDL_Renderer* renderer, const char *pathfile, int w, int l, int format);//format = 0 si .bmp ou =1 si .png
	Sprite();
	~Sprite();//Destructeur
	void setSprite(SDL_Renderer* renderer, const char *pathfile, int w, int l,int format);
    SDL_Rect getRect();
    SDL_Rect getRectPos(int x, int y);
    SDL_Texture* getTexture();
    void displayText(SDL_Renderer* renderer, SDL_Rect dst);
	void displayText(SDL_Renderer* renderer, SDL_Rect dst, SDL_Rect src);//Nouveau displayText, plus de liberté, surtout pour les animations
    SDL_Point GetRectCenter();

	int width;
	int length;
private:
	SDL_Texture* texture = NULL;
};


struct Animation : public Sprite {
    Animation(SDL_Renderer *renderer, const char* pathfile, const int width,const int height, const int format, const int nbFrame) :
        Sprite(renderer, pathfile, width,height,format),nbFrame(nbFrame) {}


    void chooseFrame(int index)
	{
		if(index <= nbFrame && index >= 0)
		{
			actualFrame = index;
		}
	}
	void nextFrame()
	{
		actualFrame++;
		if(actualFrame > nbFrame) actualFrame = 0;
	}

	void previousFrame()
	{
		actualFrame--;
		if(actualFrame ==-1) actualFrame = nbFrame -1;
	}
    SDL_Rect rect() const {
        return { actualFrame*width, 0, width, length };
    }

	bool enfOfAnim()
	{
		return actualFrame == nbFrame-1;
	}

	int actualFrameInt()
	{
		return actualFrame;
	}

	int nbFrame = 1;
	int actualFrame = 0;
};

#endif