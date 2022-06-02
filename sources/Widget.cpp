#include "../headers/Widget.h"

Widget::Widget() {
}

Widget::~Widget() {
}

void Widget::setDockGeometry(SDL_Rect dGeometry) {
    dockGeometry = dGeometry;

    if (dock != NoneDock) updateDock();
}

void Widget::setDock(Dock d, int m) {
    dock = d;
    updateDock();

    if (m != 0) {
        switch (dock) {
            case TopLeftDock:
                geometry.x += m;
                margin.x += m;
                geometry.y += m;
                margin.y += m;
                break;
            case TopDock:
                geometry.y += m;
                margin.y += m;
                break;
            case TopRightDock:
                geometry.x -= m;
                margin.x -= m;
                geometry.y += m;
                margin.y += m;
                break;

            default:
                break;
        }
    }
}

void Widget::updateDock() {
    switch (dock) {
        case NoneDock:
            break;
        case TopLeftDock:
            geometry.x = dockGeometry.x;
            geometry.y = dockGeometry.y;
            break;
        case TopDock:
            geometry.x = dockGeometry.w / 2 - geometry.w / 2 + dockGeometry.x;
            geometry.y = dockGeometry.y;
            break;
        case TopRightDock:
            geometry.x = dockGeometry.w - geometry.w;
            geometry.y = dockGeometry.y;
            break;

        default:
            break;
    }
    geometry.x += padding.x + margin.x;
    geometry.y += padding.y + margin.y;
    geometry.w -= padding.w - padding.x;
    geometry.h -= padding.h - padding.y;
}

void Widget::setMargin(SDL_Rect _margin) {
    geometry.x -= margin.x;
    geometry.y -= margin.y;

    margin.x = _margin.x - _margin.w;
    margin.y = _margin.y - _margin.h;

    geometry.x += margin.x;
    geometry.y += margin.y;
}

SDL_Point Widget::getMargin() {
    return margin;
}

void Widget::setPadding(SDL_Rect _padding) {
    geometry.x -= padding.x;
    geometry.y -= padding.y;
    geometry.w += padding.w - padding.x;
    geometry.h += padding.h - padding.y;

    padding = _padding;

    geometry.x += padding.x;
    geometry.y += padding.y;
    geometry.w -= padding.w - padding.x;
    geometry.h -= padding.h - padding.y;
}

SDL_Rect Widget::getPadding() {
    return padding;
}

void Widget::proportionalSizeW(float width) {
    geometry.w = width / geometry.w * geometry.w;
    geometry.h = width / geometry.w * geometry.h;
}

void Widget::proportionalSizeH(float height) {
    geometry.w = height / geometry.h * geometry.w;
    geometry.h = height / geometry.h * geometry.h;
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

void Widget::bindUnhoverFunction(std::function<void()> function) {
    unhoverFunc = function;
}

void Widget::bindUnpressedFunction(std::function<void()> function) {
    unpressedFunc = function;
}

void Widget::bindScrollUpFunction(std::function<void()> function) {
    scrollUpFunc = function;
}

void Widget::bindScrollDownFunction(std::function<void()> function) {
    scrollDownFunc = function;
}

void Widget::bindWinResizeFunction(std::function<void()> function) {
    winResizeFunc = function;
}

void Widget::render() {
    updateDock();
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
    if (geometry.x == 0 || geometry.y == 0 || geometry.w == 0 || geometry.h == 0) nativeGeometry = _geometry;
    geometry = _geometry;
}

void Widget::setPos(SDL_Point pos) {
    geometry.x = pos.x;
    geometry.y = pos.y;
}

void Widget::setSize(SDL_Point size) {
    geometry.w = size.x;
    geometry.h = size.y;
}

void Widget::setNativeGeometry(SDL_Rect _nativeGeometry) {
    nativeGeometry = _nativeGeometry;
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

void Widget::setDraggable(bool value) {
    drag = value;
}

bool Widget::isDraggable() {
    return drag;
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

SDL_Color Colorize::getColorByState(MouseState ms) {
    switch (ms) {
        case mouseNone:
            return color;
        case mouseHover:
            return hoverColor;
        case mousePressed:
            return pressedColor;
        default:
            return color;
    }
}

SDL_Color* Colorize::colorReference() {
    return &color;
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
    if (unhoverFunc != nullptr) unhoverFunc();
    return false;
}

bool Widget::pressed(int _x, int _y, bool press) {
    if (collisse(_x, _y) && ms != mousePressed && press) {
        ms = mousePressed;
        if (pressedFunc != nullptr) pressedFunc();
        return true;
    }

    if (unpressedFunc != nullptr) unpressedFunc();
    return false;
}

void Widget::scrollUp() {
    if (scrollUpFunc != nullptr) scrollUpFunc();
}

void Widget::scrollDown() {
    if (scrollDownFunc != nullptr) scrollDownFunc();
}

void Widget::winResize() {
    if (winResizeFunc != nullptr) winResizeFunc();
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
