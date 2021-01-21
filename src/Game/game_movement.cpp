#include "game_movement.h"

#include <cmath>

/*
 * SDL_Point *p - point that will be transformed
 * Vector2D *v - normalized vector to take an x and y direction
 * float initSpeed - base speed
 * float accelearation- rate of acceleration defaults to 0
 * float time- duration of transfor defaults to 60Hz
 * 
 * return new speed
 * 
*/
float Game::Move(SDL_Point *p, Vector2D *v, float initSpeed, float accelearation, float time)
{
    float speed = initSpeed + accelearation * time;
    float displacement = initSpeed + accelearation * time;

    if (std::abs(v->x) + std::abs(v->y) == 2)
    {
        displacement = std::sqrt((speed * speed) / 2.0);
    }

    p->x += v->x * displacement;
    p->y += v->y * displacement;

    return speed;
}