#include "../headers/Label.h"

Label::Label() {
}

Label::~Label() {
}

void Label::setText(std::string _text) {
    text = _text;
}

void Label::addMargin(SDL_Rect m) {
    margin.x += m.x;
    margin.y += m.y;
    margin.w += m.w;
    margin.h += m.h;
}

void Label::setFont(std::string fontname, int fontsize) {

}

std::string Label::getText() {
    return text;
}

Dock Label::getDock() {
    return dock;
}

SDL_Rect Label::getMargin() {
    return margin;
}
