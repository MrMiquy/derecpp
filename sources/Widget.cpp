#include "../headers/Widget.h"

Widget::Widget() {
}

Widget::~Widget() {
}

void Widget::setRenderer(SDL_Renderer* _renderer) {
    renderer = _renderer;
}

void Widget::bindHoverFunction(std::function<void()> function) {
    hoverFunc = function;
}

void Widget::bindPressedFunction(std::function<void()> function) {
    pressedFunc = function;
}

void Widget::render() {
}

SDL_Rect Widget::getGeometry() {
    return geometry;
}

SDL_Rect* Widget::geometryReference() {
    return &geometry;
}

int* Widget::xReference() {
    return &geometry.x;
}

int* Widget::yReference() {
    return &geometry.y;
}

int* Widget::widthReference() {
    return &geometry.w;
}

int* Widget::heightReference() {
    return &geometry.h;
}

void Widget::setGeometry(SDL_Rect _geometry) {
    geometry = _geometry;
}

void Widget::setMouseState(MouseState state) {
    ms = state;
}

bool Widget::isEnable() {
    return enable;
}

void Widget::setEnable(bool isEnable) {
    enable = isEnable;
}

void Widget::invertEnable() {
    enable = !enable;
}

Colorize::Colorize() {
}

Colorize::~Colorize() {
}

void Colorize::setColor(SDL_Color _color) {
    color = _color;
}

void Colorize::setHoverColor(SDL_Color _color) {
    hoverColor = _color;
}

void Colorize::setPressedColor(SDL_Color _color) {
    pressedColor = _color;
}

SDL_Color Colorize::getColor() {
    return color;
}

SDL_Color Colorize::getHoverColor() {
    return hoverColor;
}

SDL_Color Colorize::getPressedColor() {
    return pressedColor;
}

void Colorize::setAlpha(Uint8 value) {
    color.a = value;
}

void Colorize::setHoverAlpha(Uint8 value) {
    hoverColor.a = value;
}

void Colorize::setPressedAlpha(Uint8 value) {
    pressedColor.a = value;
}

Uint8 Colorize::getAlpha() {
    return color.a;
}

Uint8 Colorize::getHoverAlpha() {
    return hoverColor.a;
}

Uint8 Colorize::getPressedAlpha() {
    return pressedColor.a;
}

MouseState Widget::getMouseState() {
    return ms;
}

bool Widget::collisse(int _x, int _y) {
    if ( _x > geometry.x && _x < geometry.x + geometry.w && _y > geometry.y && _y < geometry.y + geometry.h ) {
        return true;
    }
    return false;
}

bool Widget::hover(int _x, int _y) {
    if (collisse(_x, _y)) {
        if (ms == mouseNone) {
            ms = mouseHover;
            if (hoverFunc != nullptr) hoverFunc();
            return true;
        }
    } else if (ms == mouseHover) {
        ms = mouseNone;
        return true;
    }
    return false;
}

bool Widget::pressed(int _x, int _y) {
    if (collisse(_x, _y) && ms != mousePressed) {
        ms = mousePressed;
        if (pressedFunc != nullptr)
            pressedFunc();
        return true;
    }

    return false;
}

void Widget::addX(int value) {
    geometry.x += value;
}

void Widget::addY(int value) {
    geometry.y += value;
}

void Widget::addW(int value) {
    geometry.w += value;
}

void Widget::addH(int value) {
    geometry.h += value;
}

void Widget::addNormalized(int value) {
    geometry.x += value;
    geometry.y += value;
    geometry.w += value;
    geometry.h += value;
}
