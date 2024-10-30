#ifndef BRIQUE_H
#define BRIQUE_H

#include <SDL2/SDL.h>
#include <stdio.h>

#include "bille.h"
#include "sprite.h"
#include "vector2.h"
#include "platform.h"
#include "constante.h"


class Brique {
public:
    Brique(int x, int y, int type, SDL_Renderer* renderer);
    void Afficher(SDL_Renderer* renderer);
    bool EstEliminee() ;
    void Eliminer();
    bool CollisionBille(Bille& bille);

    
    int GetHealth() ;
    void setHealth(int var);
    int getX() ;
    int getY() ;
    int getLargeur() ;
    int getHauteur() ;
    int getValue();
    bool operator!=(const Brique& other) const {
        // Comparaison basée sur l'attribut valeur
        return valeur != other.valeur;
    }

private:
    int x;
    int y;
    int health;
    bool eliminee;
    int resistance;
    Animation sprite;
    int valeur;
};

#endif
