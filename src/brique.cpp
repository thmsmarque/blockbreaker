#include <SDL2/SDL.h>
#include <stdio.h>
#include <cmath>

#include "brique.h"
#include "bille.h"
#include "sprite.h"
#include "vector2.h"
#include "platform.h"

#include "constante.h"


Brique::Brique(int x, int y, int health, SDL_Renderer* renderer) : x(x), y(y), health(health), eliminee(false), sprite(renderer, "../res/nuage.png", BRIQUE_LARGEUR, BRIQUE_HAUTEUR, 1,2) {
    sprite.actualFrame = health -1;
}


void Brique::Afficher(SDL_Renderer* renderer) {
    sprite.chooseFrame(resistance-1);
     if (!eliminee) {
        // Dessinez la brique sur le rendu avec les  coordonnées x, y, largeur et hauteur
        SDL_Rect dstRect = this->sprite.getRectPos(this->x,this->y);
        sprite.displayText(renderer, dstRect,sprite.rect());
     }
}

bool Brique::EstEliminee() {
    return eliminee;
}

void Brique::Eliminer() {
    eliminee = true;
}

bool Brique::CollisionBille(Bille& bille) { 

        if (!eliminee) {
        double billeX = bille.pos.getx();
        double billeY = bille.pos.gety();
        double billeRayon = hauteur_bille/2;

         if (billeX + billeRayon > x && billeX - billeRayon < x + BRIQUE_LARGEUR && billeY + billeRayon > y && billeY - billeRayon < y + BRIQUE_HAUTEUR) {
             return true;
          }
        }
          return false;
}




int Brique::GetHealth() {
    return health;
}

void Brique::setHealth(int var)
{
    this->health = this->GetHealth() + var;
    sprite.actualFrame -= 1;
}

int Brique::getX() {
    return x;
}

int Brique::getY() {
    return y;
}

int Brique::getLargeur() {
    return BRIQUE_LARGEUR;
}

int Brique::getHauteur() {
    return BRIQUE_HAUTEUR;
}

int Brique::getValue(){
    return x;
}
