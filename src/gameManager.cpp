#include <vector>
#include <ctime>
#include <fstream>

#include "menu.h"
#include "sprite.h"
#include "vector2.h"
#include "platform.h"
#include "bille.h"
#include "constante.h"



#include "gameManager.h"


struct BriqueData {
    int posX;
    int posY;
    int health;
};

#define max(a,b)(a>=b?a:b)


GameManager::GameManager(SDL_Renderer* renderer) : renderer(renderer)
{
}

GameManager::~GameManager()
{
	delete plateforme;
	plateforme = nullptr;
	bille.~Bille();
    while(!briques.estVide())
    {
        briques.remove(0);
    }
}

std::vector<BriqueData> lireConfigurationBriques(const std::string& nomFichier) {
    std::vector<BriqueData> donneesBriques;
    std::ifstream fichier(nomFichier);

    if (fichier.is_open()) {
        int posX, posY, health;
        while (fichier >> posX >> posY >> health) {
            BriqueData briqueData = {posX, posY, health};
            donneesBriques.push_back(briqueData);
        }
        fichier.close();
    }

    return donneesBriques;
}


void GameManager::initialisationBriques(const std::string& nomFichier) {
    std::vector<BriqueData> donneesBriques = lireConfigurationBriques(nomFichier);

    for (const auto& briqueData : donneesBriques) {
        briques.add(Brique(briqueData.posX, briqueData.posY, briqueData.health, renderer));
    }
}

void GameManager::setMenu(Menu* menu)
{
    this->menu = menu;
}

void GameManager::setVie(int newVie)
{
    this->vie = newVie;
}

void GameManager::Start()
{
	plateforme = new Platform((LENGTH_SCREEN/2)-hauteur_platform/2,posHauteur_plateforme,renderer);
	bille = Bille(LENGTH_SCREEN/2, posHauteur_plateforme-100,renderer,plateforme);
	initialisationBriques("../res/config_briques.txt");
	this->jeuEnCours = true;	
}



void GameManager::Update() {
    if (this->jeuEnCours == true) {
		if(briques.estVide())
			{
				this->endOfGame(0);
			}
		bg.displayText(renderer,{0,0,LENGTH_SCREEN,HEIGHT_SCREEN});


        plateforme->Update();
        SDL_Rect dstPlateforme = plateforme->sprite.getRectPos(plateforme->pos.getx(), plateforme->pos.gety());
        plateforme->sprite.displayText(renderer, dstPlateforme);

        SDL_Rect dstBille = bille.sprite.getRectPos(bille.pos.getx(), bille.pos.gety());
        bille.sprite.displayText(renderer, dstBille);
        bille.Update();

        // on ajoute une liste pour stocker les briques éliminées
        Liste<Brique*> briquesEliminees;
        for (int i = 0; i< briques.size(); i++){
            Brique* briquePtr = briques.index(i);
            if (briquePtr) {
                Brique& brique = *briquePtr;
                brique.Afficher(renderer);

                if (brique.CollisionBille(bille)) {
                    double billeX = bille.pos.getx();
                    double billeY = bille.pos.gety();
                    double billeRayon = hauteur_bille/2;
                    bille.SetVitesse(bille.vit.x, bille.vit.y*-1);
					variationScore(20);
                    menu->updateScore(getScore());
                    brique.setHealth(-1);
                    if(brique.GetHealth() <= 0)
                    {
                        brique.Eliminer();
                        briquesEliminees.add(briquePtr);  // on ajoute la brique éliminée à la nouvelle liste des briques eliminees
                        briques.remove(i);
                    }
                }
            }
        }

        if(bille.pos.gety()+hauteur_bille >= HEIGHT_SCREEN)
	    {
		    variationVie(-1);
            bille.pos.Set(LENGTH_SCREEN/2,HEIGHT_SCREEN/2);
	        bille.SetVitesse(0,3);
	    }
			
        }

}

int GameManager::getScore()
{
    return this->score;
}

void GameManager::setScore(int newScore)
{
    this->score = newScore;
}


void GameManager::endOfGame(int raison)
{
	if(raison == 0)
	{
		this->jeuEnCours = false;
        menu->MontrerMenu();
	}
}

void GameManager::variationVie(int var)
{
	if(this->jeuEnCours){this->vie = max(0,this->vie + var);
		if(vie <= 0) endOfGame(0);}
}

void GameManager::variationScore(int var)
{
	if(this->jeuEnCours == true)this->score = this->score + var;
}

bool GameManager::isGameInProgress() {
    std::cout << this->jeuEnCours << std::endl;
    return this->jeuEnCours;
}
