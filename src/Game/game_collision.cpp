#include "game_collision.h"

// I didnt test this yet. Think it works? I pen & paper'd it though
bool Game::LineCollidesWithRect(Game::GameLine *line, SDL_Rect *rect)
{
    int minX, maxX, minY, maxY;
    if (line->a.x <= line->b.x)
    {
        minX = line->a.x;
        maxX = line->b.x;
    }
    else
    {
        minX = line->b.x;
        maxX = line->a.x;
    }

    if (line->a.y <= line->b.y)
    {
        minY = line->a.y;
        maxY = line->b.y;
    }
    else
    {
        minY = line->b.y;
        maxY = line->a.y;
    }

    return (minX >= rect->x || maxX >= rect->x) &&
           (minX <= rect->x + rect->w || maxX <= rect->x + rect->w) &&
           (minY >= rect->y || maxY >= rect->y) &&
           (minY <= rect->y + rect->h || maxY <= rect->y + rect->h);
}
