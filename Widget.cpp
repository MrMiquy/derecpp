#include "Widget.h"

const char* gFontFile = "helv-light.ttf";

Button::Button(SDL_Renderer* _renderer, const char* _text, SDL_Rect _geometry, SDL_Color _color, bool useAutoColoring, bool textMargin) {
    state = Default;
    geometry = _geometry;
    defColor = color = _color;

    text.renderer = renderer = _renderer;
    text.text = _text;
    bindText(isBindText);

    Uint8 highlight = 10;
    Uint8 darklight = 15;

    if (useAutoColoring) {
        mouseOverColor = {Uint8(defColor.r + highlight), Uint8(defColor.g + highlight), Uint8(defColor.b + highlight), defColor.a};
        pressColor = {Uint8(defColor.r - darklight), Uint8(defColor.g - darklight), Uint8(defColor.b - darklight), defColor.a};
    }
}

void Button::bindSignal(std::function<void()> func) {
    pressedPtr = func;
}

Plate::Plate(SDL_Renderer* _renderer, SDL_Rect _geometry, SDL_Color _color) {
    renderer = _renderer;
    geometry = _geometry;
    color = _color;
}

Plate::Plate() {

}

void Plate::addChild(Widget* child) {
    children.emplace_back(child);
}

void Plate::render() {
    if (getEnable()) {
        SDL_Color tempColor;
        SDL_GetRenderDrawColor(renderer, &tempColor.r, &tempColor.g, &tempColor.b, &tempColor.a);

        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &geometry);
        SDL_SetRenderDrawColor(renderer, tempColor.r, tempColor.g, tempColor.b, tempColor.a);

        for (unsigned int i = 0; i < children.size(); i++) {
            children[i]->geometry = geometry;
            children[i]->render();
        }
    }
}

EditBox::EditBox(SDL_Renderer* _renderer, SDL_Rect _geometry, SDL_Color _background, SDL_Color _foreground) {
    plate.renderer = hint.renderer = text.renderer = _renderer;
    plate.geometry = _geometry;
    completeFgColor = text.color = _foreground;
    completeBgColor = plate.color = _background;

    editFgColor.r = completeFgColor.r;
    editFgColor.g = completeFgColor.g;
    editFgColor.b = completeFgColor.b;

    editBgColor.r = completeBgColor.r + 10;
    editBgColor.g = completeBgColor.g + 10;
    editBgColor.b = completeBgColor.b + 10;

    bindText();
}

void EditBox::bindText() {
    hint.renderingGeometry.x = hint.geometry.x = text.renderingGeometry.x = text.geometry.x = plate.geometry.x;
    hint.renderingGeometry.y = hint.geometry.y = text.renderingGeometry.y = text.geometry.y = plate.geometry.y;

    if (isBindText) {
        hint.renderingGeometry.w = hint.geometry.w = text.renderingGeometry.w = text.geometry.w = plate.geometry.w;
        hint.renderingGeometry.h = hint.geometry.h = text.geometry.h = plate.geometry.h;
        text.setFont(gFontFile, plate.geometry.h / 1.5);
        hint.setFont(gFontFile, plate.geometry.h / 1.5);
    } else {
        hint.renderingGeometry.w = text.renderingGeometry.w = plate.geometry.w;
        hint.geometry.w = text.geometry.w = text.textWidth;
        text.setFont(gFontFile, 16);
        hint.setFont(gFontFile, 16);
    }

    hint.setAlpha(44);
    hint.updateDock();
    text.updateDock();
}

void EditBox::render() {
    plate.render();

    if (text.text.length() > 0) {
        text.render();
    } else {
        hint.render();
    }

    if (isRenderLine && state == Editing) {
        SDL_Color tempColor;
        line_offset = text.renderingGeometry.x + text.renderingGeometry.w + text.margin.left - text.margin.right;
        SDL_GetRenderDrawColor(plate.renderer, &tempColor.r, &tempColor.g, &tempColor.b, &tempColor.a);
        SDL_SetRenderDrawColor(plate.renderer, text.color.r, text.color.g, text.color.b, text.color.a);
        SDL_RenderDrawLine(plate.renderer, line_offset, text.renderingGeometry.y + 3 + text.margin.top, line_offset, text.renderingGeometry.y + text.renderingGeometry.h - 3 - text.margin.bottom);
        SDL_SetRenderDrawColor(plate.renderer, tempColor.r, tempColor.g, tempColor.b, tempColor.a);
    }
}

bool EditBox::isMouseOn(int x, int y) {
    if ( (x > plate.geometry.x && x < plate.geometry.x + plate.geometry.w) && (y > plate.geometry.y && y < plate.geometry.y + plate.geometry.h))
        return true;
    return false;
}

bool EditBox::edit() {
    if (state == Completed) {
        state = Editing;
        plate.color = editBgColor;
        text.color = editFgColor;
        hint.setAlpha(66);
        text.setAlpha(255);
        return true;
    }
    return false;
}

bool EditBox::complete() {
    if (state == Editing) {
        state = Completed;
        plate.color = completeBgColor;
        text.color = completeFgColor;
        hint.setAlpha(44);
        text.setAlpha(100);
        return true;
    }
    return false;
}

void EditBox::setEditColor(SDL_Color bg, SDL_Color fr) {
    editBgColor = bg;
    editFgColor = fr;
}

void EditBox::setCompleteColor(SDL_Color bg, SDL_Color fr) {
    completeBgColor = bg;
    completeFgColor = fr;
}

void Button::setAdvColors(SDL_Color _mouseOverColor, SDL_Color _pressColor) {
    mouseOverColor = _mouseOverColor;
    pressColor = _pressColor;

    render();
}

void Button::setGeometry(SDL_Rect _geometry) {
    geometry = _geometry;

    bindText(isBindText);
}

bool Button::isMouseOn(int x, int y) {
    if ( (x > geometry.x && x < geometry.x + geometry.w) && (y > geometry.y && y < geometry.y + geometry.h) ) {
        if (state == Default) {
            color = mouseOverColor;
            state = MouseOver;
            text.setAlpha(255);
            return true;
        }
    } else if (state == MouseOver) {
        color = defColor;
        state = Default;
        text.setAlpha(100);
        return true;
    }
    return false;
}

bool Button::isPressed(int x, int y) {
    if ((x > geometry.x && x < geometry.x + geometry.w) && (y > geometry.y && y < geometry.y + geometry.h)) {
        color = pressColor;
        state = Pressed;
        text.setAlpha(100);
        return true;
    }
    return false;
}

void Button::lostPressedFocus(int x, int y) {
    if ( (x > geometry.x && x < geometry.x + geometry.w) && (y > geometry.y && y < geometry.y + geometry.h)) {
        color = mouseOverColor;
        state = MouseOver;
        text.setAlpha(255);
        if (pressedPtr != nullptr) pressedPtr();
    } else {
        color = defColor;
        state = Default;
        text.setAlpha(100);
    }
}

void Button::render() {
    if (getEnable()) {
        Plate::render();
        text.render();
    }
}

void Button::bindText(bool isBinded) {
    text.renderingGeometry.x = text.geometry.x = geometry.x;
    text.renderingGeometry.y = text.geometry.y = geometry.y;

    isBindText = isBinded;
    if (isBinded) {
        text.renderingGeometry.w = text.geometry.w = geometry.w;
        text.geometry.h = geometry.h;
        text.setFont(gFontFile, geometry.h / 1.25);
    } else {
        text.renderingGeometry.w = geometry.w;
        text.setFont(gFontFile, 16);
    }
}

Text::Text() {
    renderingGeometry = geometry = {0, 0, 0, 0};
}

Text::Text(SDL_Renderer* _renderer, std::string _text, const char* fontname, int size, SDL_Rect _geometry) {
    renderer = _renderer;
    geometry = renderingGeometry = _geometry;
    setFont(fontname, size);
    setText(_text.c_str());

    setFont(gFontFile, size);
}

void Text::updateDock() {
    margin.left = margin.top = margin.right = margin.bottom = 0;
    setDock(dock, 0, true);
}

void Text::setMargin(int _left, int _top, int _right, int _bottom) {
    margin.left += _left -= _right;
    margin.top += _top -= _bottom;
    setTexture();
}

void Text::setDock(Dock _dock, int marginDock, bool forcibly) {
    if (dock != NoneDock && !forcibly) return;
    dock = _dock;

    switch (_dock) {
        case NoneDock:
            break;

        case Top:
            setMargin(geometry.w / 2 - textWidth / 2);
            offset_margin.top += marginDock;
            break;

        case Left:
            setMargin(0, geometry.h / 2 - geometry.y - textHeight / 2);
            offset_margin.left += marginDock;
            break;

        case Bottom:
            setMargin(geometry.w / 2 - textWidth / 2, geometry.h - geometry.y - textHeight);
            offset_margin.top -= marginDock;
            break;

        case Right:
            setMargin(geometry.w - textWidth, geometry.h / 2 - geometry.y - textHeight / 2);
            offset_margin.left -= marginDock;
            break;

        case Center:
            setMargin(geometry.w / 2 - textWidth / 2, geometry.h / 2 - textHeight / 2);
            break;

        case TopLeft:
            offset_margin.top += marginDock;
            offset_margin.left += marginDock;
            break;

        case TopRight:
            setMargin(geometry.w - textWidth);
            offset_margin.left -= marginDock;
            offset_margin.top += marginDock;
            break;

        case BottomRight:
            setMargin(geometry.w - textWidth, geometry.h - geometry.y - textHeight);
            offset_margin.top -= marginDock;
            offset_margin.left -= marginDock;
            break;

        case BottomLeft:
            setMargin(0, geometry.h - geometry.y - textHeight);
            offset_margin.top -= marginDock;
            offset_margin.left += marginDock;
            break;
    }
}

void Text::setFont(const char* ttf_filename, int fontSize) {
    font = TTF_OpenFont(ttf_filename, fontSize);
    TTF_SizeText(font, text.c_str(), &textWidth, &textHeight);

    if (textWidth < geometry.w) renderingGeometry.w = textWidth;
    renderingGeometry.h = textHeight;

    setTexture();
}

void Text::setAlpha(Uint8 _alpha) {
    alpha = _alpha;
    setTexture();
}

void Text::setText(const char* _text) {
    text = _text;
    setTexture();
}

void Text::setTexture() {
    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text.c_str(), color);
    texture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(texture, alpha);
}

void Widget::invertEnable() {
    setEnable(!isEnable);
}

void Text::render() {
    renderingGeometry.x = geometry.x;
    renderingGeometry.y = geometry.y;
    updateDock();

    renderingGeometry.x += margin.left + offset_margin.left;
    renderingGeometry.y += margin.top + offset_margin.top;

    if (text == "Title:") printf("x: %d \ty: %d \t\tw: %d \th:%d\n", geometry.x, geometry.y, geometry.w, geometry.h);
    if (text == "Title:") printf("x: %d \ty: %d \t\tw: %d \th:%d\n", renderingGeometry.x, renderingGeometry.y, renderingGeometry.w, renderingGeometry.h);

    SDL_RenderCopy(renderer, texture, NULL, &renderingGeometry);

    renderingGeometry.x -= margin.left - offset_margin.left;
    renderingGeometry.y -= margin.top - offset_margin.top;
}

void Text::setColor(SDL_Color _color) {
    color = _color;
}

Plate::~Plate() {
    delete this;
}

Text::~Text() {
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    delete this;
}

Button::~Button() {
    SDL_DestroyTexture(text.texture);
    TTF_CloseFont(text.font);
    delete this;
}

bool EditBox::renderLine(int frame) {
    if (state == Editing) {
        if (frame / 2 % 24 == 0) {
            isRenderLine = true;
            return true;
        } else if (frame / 2 % 12 == 0) {
            isRenderLine = false;
            return true;
        }
    }

    return false;
}
