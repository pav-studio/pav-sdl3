#include <SDL3/SDL.h>

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Rogue Pong", 800, 600, 0);

    SDL_Delay(3000);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}