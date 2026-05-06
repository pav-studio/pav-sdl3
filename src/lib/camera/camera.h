#pragma once

#include <glad/glad.h>

class Camera {

private:

    int virtualW;
    int virtualH;

public:

    Camera(int vw, int vh)
        : virtualW(vw),
          virtualH(vh) {
    }

    void apply(
        int windowW,
        int windowH
    ) {

        float targetAspect =
            (float)virtualW / virtualH;

        float windowAspect =
            (float)windowW / windowH;

        int viewportX = 0;
        int viewportY = 0;

        int viewportW = windowW;
        int viewportH = windowH;

        if (windowAspect > targetAspect) {

            viewportW =
                (int)(windowH * targetAspect);

            viewportX =
                (windowW - viewportW) / 2;

        } else {

            viewportH =
                (int)(windowW / targetAspect);

            viewportY =
                (windowH - viewportH) / 2;
        }

        glViewport(
            viewportX,
            viewportY,
            viewportW,
            viewportH
        );
    }

    void reset(
        int windowW,
        int windowH
    ) {

        glViewport(
            0,
            0,
            windowW,
            windowH
        );
    }
};