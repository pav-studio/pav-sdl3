#pragma once

#include <vector>

#include "texture_region.h"

std::vector<std::vector<TextureRegion>>
split(
    TextureRegion& parent,
    int tileW,
    int tileH
) {

    std::vector<std::vector<TextureRegion>> grid;

    int cols = parent.w / tileW;
    int rows = parent.h / tileH;

    for (int y = 0; y < rows; y++) {

        std::vector<TextureRegion> row;

        for (int x = 0; x < cols; x++) {

            row.emplace_back(
                parent.textureID,

                parent.x + x * tileW,
                parent.y + y * tileH,

                tileW,
                tileH,

                parent.textureWidth,
                parent.textureHeight
            );
        }

        grid.push_back(row);
    }

    return grid;
}