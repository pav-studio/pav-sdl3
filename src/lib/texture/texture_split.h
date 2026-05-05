#include <vector>
#include "texture_region.h"

std::vector<std::vector<TextureRegion>> split(TextureRegion& parent,
                                              int tileW, int tileH) {
    std::vector<std::vector<TextureRegion>> grid;

    int cols = parent.src.w / tileW;
    int rows = parent.src.h / tileH;

    for (int y = 0; y < rows; y++) {
        std::vector<TextureRegion> row;

        for (int x = 0; x < cols; x++) {
            row.emplace_back(
                parent.texture,
                parent.src.x + x * tileW,
                parent.src.y + y * tileH,
                tileW,
                tileH
            );
        }

        grid.push_back(row);
    }

    return grid;
}