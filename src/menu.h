#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include "sprite.h"
#include "bille.h"
#include "vector2.h"
#include "platform.h"
#include "gameManager.h"
#include "constante.h"

struct Menu {
    Sprite spriteBoutonJouer;
    Sprite spriteBoutonExit;
    Animation background;
    SDL_Renderer* renderer;
    GameManager* gm = nullptr;

    bool montrerMenu = true;
    bool enJeu = false;
    int score = 0;

    Menu(SDL_Renderer* renderer, GameManager* gm, Animation background) : renderer(renderer), gm(gm), background(background) {
        this->MontrerMenu();
        genererBoutonJouer();
        genererBoutonExit();
                TTF_Init();
    }

    void Update() {
        if (montrerMenu) {
            //Afficher le bg
            SDL_Rect dstBg = background.getRect();
            background.displayText(renderer,dstBg); 


            SDL_Rect dstBoutonJouer = spriteBoutonJouer.getRectPos(LENGTH_SCREEN / 2 - 394 / 2, hauteur_JOUER);
            spriteBoutonJouer.displayText(renderer, dstBoutonJouer);

            // Afficher le bouton "EXIT" seulement si le jeu n'est pas en cours
           
                SDL_Rect dstBoutonExit = spriteBoutonExit.getRectPos(LENGTH_SCREEN / 2 - 394 / 2, hauteur_EXIT);
                spriteBoutonExit.displayText(renderer, dstBoutonExit);
            
        }
    }

    void RenderScore(SDL_Renderer* renderer) {
        // Load font (you can do this in the constructor)
        TTF_Font* font = TTF_OpenFont("../res/OpenSans-Regular.ttf", 24);

        if (!font) {
            fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
            SDL_Quit();
            return;
        }

        std::string scoreText = "Score: " + std::to_string(score);
        SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText.c_str(), {255, 255, 255});  // White color

        if (!scoreSurface) {
            fprintf(stderr, "Erreur lors de la création de la surface du score : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            SDL_Quit();
            return;
        }

        SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
        SDL_FreeSurface(scoreSurface);

        if (!scoreTexture) {
            fprintf(stderr, "Erreur lors de la création de la texture du score : %s\n", SDL_GetError());
            TTF_CloseFont(font);
            SDL_Quit();
            return;
        }

        // Render the score texture
        SDL_Rect scoreRect = {scoreX, scoreY, 0, 0};
        SDL_QueryTexture(scoreTexture, NULL, NULL, &scoreRect.w, &scoreRect.h);
        SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);

        // Cleanup
        SDL_DestroyTexture(scoreTexture);
        TTF_CloseFont(font);
    }


    // Génération du bouton jouer
    void genererBoutonJouer() {
        spriteBoutonJouer.setSprite(renderer, "../res/jouer1.png", 394, 90, 1);
    }

    // Mise à jour du sprite du bouton
    void boutonJouerUpdate(int etat) {
        if (etat == 0) {
            spriteBoutonJouer.setSprite(renderer, "../res/jouer1.png", 394, 90, 1);
        } else {
            spriteBoutonJouer.setSprite(renderer, "../res/jouer2.png", 394, 90, 1);
        }
    }

    void genererBoutonExit() {
        spriteBoutonExit.setSprite(renderer, "../res/exit2.png", 394, 90, 1);
    }


    // Gère la position de la souris
    void handle_mouseMoving() {
        if (montrerMenu) {
            // Récupérer la position de la souris
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            if (mouseY > hauteur_JOUER && mouseY <= hauteur_JOUER + 90 && mouseX > 163 && mouseX <= 163 + 394) {
                this->boutonJouerUpdate(1);
            } else {
                this->boutonJouerUpdate(0);
            }
        }
    }

    // Gère le clic de la souris
    void handle_mouseClicking(bool& gameRunning) {
        if (montrerMenu) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
        
            if (mouseY > boutonJouerY && mouseY <= boutonJouerY + 90 && mouseX > boutonJouerX && mouseX <= boutonJouerX + 394) {
                this->CacherMenu();
                gm->Start();
                score = 0;
                gm->setScore(0);
                gm->setVie(3);
                enJeu = true;
            }
            
        }
    }

    // Cache le menu
    void CacherMenu() {
        while(!background.enfOfAnim())
                {
                    background.nextFrame();
                            SDL_RenderClear(renderer);
                    background.displayText(renderer,background.getRect(),background.rect());
                            SDL_RenderPresent(renderer);
                            SDL_Delay(60);
                }
        SDL_RenderClear(renderer);
        montrerMenu = false;
    }

    void MontrerMenu() {
        background.chooseFrame(background.nbFrame-1);
        SDL_RenderClear(renderer);
        while(!background.actualFrame == 0)
                {
                    background.previousFrame();
                            SDL_RenderClear(renderer);
                    background.displayText(renderer,background.getRect(),background.rect());
                            SDL_RenderPresent(renderer);
                            SDL_Delay(60);
                }
        montrerMenu = true;
        enJeu = false;
    }

    void updateScore(int newScore) {
        score = newScore;
    }

};

#endif
