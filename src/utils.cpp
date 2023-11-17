#include "utils.h"

bool intersects(const SDL_Rect& rect1, const SDL_Rect& rect2) {
    if (rect1.x + rect1.w <= rect2.x || // rect1 is to the left of rect2
        rect1.x >= rect2.x + rect2.w || // rect1 is to the right of rect2
        rect1.y + rect1.h <= rect2.y || // rect1 is above rect2
        rect1.y >= rect2.y + rect2.h) { // rect1 is below rect2
        return false;
    }

    // If none of the non-intersection conditions are met, the rectangles intersect
    return true;
}