#pragma once

#include <vector>

#include "texture_region.h"
#include "texture_split.h"

std::vector<TextureRegion>
extractSprites(
    TextureRegion& parent,
    int tileW,
    int tileH,
    bool byRow
) {

    auto grid = split(parent, tileW, tileH);

    if (byRow) {

        return grid[0];

    } else {

        std::vector<TextureRegion> col;

        for (int i = 0; i < grid.size(); i++) {

            col.push_back(grid[i][0]);
        }

        return col;
    }
}