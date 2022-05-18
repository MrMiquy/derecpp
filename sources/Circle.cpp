#include "../headers/Circle.h"

Circle::Circle() {
}

Circle::~Circle() {
}

void Circle::setGeometry(SDL_Rect _geometry) {
    x = geometry.x = _geometry.x;
    y = geometry.y = _geometry.y;
    geometry.w = _geometry.w;
    geometry.h = _geometry.h;
}

void Circle::render() {
    x += geometry.w / 2;
    y += geometry.h / 2;

    if (ms == mouseNone) {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    } else if (ms == mouseHover) {
        SDL_SetRenderDrawColor(renderer, hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a);
    } else if (ms == mousePressed) {
        SDL_SetRenderDrawColor(renderer, pressedColor.r, pressedColor.g, pressedColor.b, pressedColor.a);
    }

    if (fill) {
        int32_t r = radius;
        radius *= (radius / 4);
        diameter = radius * 2;
        for (int w = 0; w < diameter; w++) {
            for (int h = 0; h < diameter; h++) {
                int dX = radius - w;
                int dY = radius - h;

                if ( (dX*dX + dY*dY) <= radius ) {
                    SDL_RenderDrawPoint(renderer, x + dX - 1, y + dY - 3);
                }
            }
        }
        radius = r;
        diameter = radius * 2;
    } else {
        int32_t oX = (radius - 1);
        int32_t oY = 0;
        int32_t tX = 1;
        int32_t tY = 1;
        int32_t error = (tX - diameter);

        while (oX >= oY) {
            SDL_RenderDrawPoint(renderer, x + oX, y - oY);
            SDL_RenderDrawPoint(renderer, x + oX, y + oY);
            SDL_RenderDrawPoint(renderer, x - oX, y - oY);
            SDL_RenderDrawPoint(renderer, x - oX, y + oY);
            SDL_RenderDrawPoint(renderer, x + oY, y - oX);
            SDL_RenderDrawPoint(renderer, x + oY, y + oX);
            SDL_RenderDrawPoint(renderer, x - oY, y - oX);
            SDL_RenderDrawPoint(renderer, x - oY, y + oX);

            if (error <= 0) {
                ++oY;
                error += tY;
                tY += 2;
            }

            if (error > 0) {
                --oX;
                tX += 2;
                error += tX - diameter;
            }
        }
    }
    x -= geometry.w / 2;
    y -= geometry.h / 2;
}

void Circle::setCentre(int32_t centreX, int32_t centreY) {
    x = geometry.x = centreX;
    y = geometry.y = centreY;
}

void Circle::setRadius(int32_t R) {
    radius = geometry.w = geometry.h = R;
    diameter = radius * 2;
}

int32_t Circle::getX() {
    return x;
}

int32_t Circle::getY() {
    return y;
}

int32_t Circle::getRadius() {
    return radius;
}

int32_t Circle::getDiameter() {
    return diameter;
}

void Circle::setFill(bool value) {
    fill = value;
}

bool Circle::isFill() {
    return fill;
}
