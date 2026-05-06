#pragma once
#include <SDL3/SDL.h>

class Camera {
private:
    int virtualW, virtualH;

public:
    Camera(int vw, int vh)
        : virtualW(vw), virtualH(vh) {}

    void apply(SDL_Renderer* renderer) {
        SDL_SetRenderLogicalPresentation(
            renderer,
            virtualW,
            virtualH,
            SDL_LOGICAL_PRESENTATION_LETTERBOX
        );
    }

    void reset(SDL_Renderer* renderer) {
        SDL_SetRenderLogicalPresentation(
            renderer,
            0, 0,
            SDL_LOGICAL_PRESENTATION_DISABLED
        );
    }
};