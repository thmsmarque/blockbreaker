#ifndef MANAGER_H
#define MANAGER_H

#include "liste.cpp"

#include "sprite.h"
#include "vector2.h"
#include "platform.h"
#include "bille.h"
#include "brique.h"

struct Menu;

class GameManager
{
public:
	GameManager(SDL_Renderer* renderer);
	~GameManager();
	void Update();
	void Start();
	void endOfGame(int raison);
	void initialisationBriques(const std::string& nomFichier);
	void variationScore(int var);
	void variationVie(int var);
	void SupprimerBrique(int index);
	void setMenu(Menu* menu);
	bool isGameInProgress();
	int getScore();
	void setScore(int newScore);
	void setVie(int newVie);

	SDL_Renderer* renderer;
	Menu* menu = nullptr;
private:
	Sprite bg;
	Platform* plateforme = nullptr;
	Liste<Brique>briques;
	Bille bille;
	int vie;
	int score;
	bool jeuEnCours = false;

};


#endif