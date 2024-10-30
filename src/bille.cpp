#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#include "bille.h"
#include "sprite.h"
#include "vector2.h"
#include "platform.h"

#include "constante.h"

#define speed 3


Bille::Bille(){

}

Bille::Bille(double xpos, double ypos,SDL_Renderer* renderer, Platform* plateforme): plateforme(plateforme)
{
	pos.Set(xpos,ypos);
	this->SetVitesse(0,3);
	sprite.setSprite(renderer,"../res/bille.bmp",hauteur_bille,largeur_bille,0);

}

Bille::~Bille()
{

}

void Bille::Update()
{

	pos.Set(pos.plus(pos,vit));
	CollisionBord();
	CollisionPlateforme();

}

void Bille::CollisionBord()
{
	int circleradius = hauteur_bille/2; //Rayon de la bille 

	//test de collision avec le bord droite
	if(circleradius+pos.getx()+sprite.GetRectCenter().x >= LENGTH_SCREEN)
	{
		this->SetVitesse(vit.getx() * -1,vit.gety());
	}
	//test de collision avec le bord gauche
	if(pos.getx()<=0)
	{
		this->SetVitesse(vit.getx() * -1,vit.gety());
	}
	//test de collision avec le bord haut
	if(pos.gety() <= 0)
	{
		this->SetVitesse(vit.getx(),vit.gety()* -1);
	}

}

void Bille::CollisionPlateforme()
{
	
		double cx  = pos.getx() + this->circleradius;//centre x
		double cy  = pos.gety() + this->circleradius;//centre y
		double testX = cx; 
		double testY = cy;

		double rx = this->plateforme->pos.getx();//x du coin supérieur gauche de la plateforme
		double ry = this->plateforme->pos.gety();//y du coin supérieur gauche de la plateforme


		if (cx < rx)         testX = rx;        // bord gauche
		else if (cx > rx+this->plateforme->largeur) testX = rx+rx+this->plateforme->largeur;     // bord droit

		if (cy < ry) 
		{
			       testY = ry;     
		}   // bord haut
		else if (cy > ry+rx+this->plateforme->hauteur) testY = ry+this->plateforme->hauteur;     // bord bas

		double distX = cx-testX;
		double distY = cy-testY;
		double distance = (distX*distX) + (distY*distY) ;

		if (distance <= this->circleradius * this->circleradius  && (cy <= ry && cy >= ry-this->plateforme->hauteur))//S'il y'a collision
		{
			double x = rx+this->plateforme->largeur/2 - cx;
			Vector2 nouvTraj;
			nouvTraj.Set(x/-20,vit.gety()*-1);
	    	this->SetVitesse(nouvTraj.getx(),nouvTraj.gety());
		}

}


//Set totale de la vitesse de la bille 
void Bille::SetVitesse(double vitX,double vitY)
{
	vit.Set(vitX,vitY);
	vit.Normalized();
	this->SetVitesse(speed);
}

//Multiplication des composants de la vitesse par un facteur
void Bille::SetVitesse(double mult)
{
	vit.time(mult);
}

int Bille::getX() {
    return this->pos.getx();
}

int Bille::getY() {
    return this->pos.getx();
}
