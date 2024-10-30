#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#include "sprite.h"
#include "bille.h"
#include "vector2.h"
#include "platform.h"
#include "menu.h"
#include "gameManager.h"
#include "brique.h"

#include "constante.h"
#include "liste.cpp"

int main()
{
    const int FPS = 30;

    // Initialisation SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Initialisation SDL_image
    if (IMG_Init(IMG_INIT_JPG) != IMG_INIT_JPG) {
        fprintf(stderr, "Erreur lors de l'initialisation de SDL_image : %s\n", IMG_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_CreateWindowAndRenderer(LENGTH_SCREEN, HEIGHT_SCREEN, SDL_WINDOW_SHOWN, &window, &renderer);
    SDL_SetWindowTitle(window, "Meteor");

    SDL_Event event;

    GameManager jeu(renderer);
    Menu menuScreen(renderer, &jeu,Animation(renderer,"../res/transition.png",LENGTH_SCREEN,HEIGHT_SCREEN,1,10));
    jeu.setMenu(&menuScreen);
    bool gameRunning = true;


    // Boucle principale
    while (gameRunning) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                gameRunning = false;
            }

            if (event.type == SDL_MOUSEMOTION) {
                menuScreen.handle_mouseMoving();
            }

            if (event.type == SDL_MOUSEBUTTONUP) {
                menuScreen.handle_mouseClicking(gameRunning);
                
                
                if (mouseY > boutonExitY && mouseY <= boutonExitY + 90 && mouseX > boutonExitX && mouseX <= boutonExitX + 394) {
                    // Action pour le bouton "EXIT"
                    gameRunning = false;
                }
            }
        }

        // Effacer l'écran
        SDL_RenderClear(renderer);

        
        menuScreen.background.displayText(renderer,menuScreen.background.getRect(),menuScreen.background.rect());
        // Mettre à jour le jeu et le menu
        jeu.Update();
        menuScreen.Update();
        menuScreen.RenderScore(renderer);

        // Actualiser l'affichage
        SDL_RenderPresent(renderer);

        // Limiter le FPS
        SDL_Delay(17);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
