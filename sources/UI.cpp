#include "../headers/UI.h"

void UI::initElements() {
}

void UI::init(const char* title, int xPos, int yPos, int width, int height, uint FLAG) {
        window = SDL_CreateWindow(title, xPos, yPos, width, height, FLAG);
        initElements();

        setRenderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        surface = SDL_GetWindowSurface(window);
        run = true;
}

UI::UI() {
}

UI::~UI() {
}

void UI::setRenderer(SDL_Renderer* _renderer) {
    renderer = _renderer;

    for (Widget* widget : UIElements ) {
        widget->setRenderer(_renderer);
    }
    for (Widget* widget : UIChildren ) {
        widget->setRenderer(_renderer);
    }
}

void UI::renderUI() {
    for (Widget* widget : UIElements) {
        widget->render();
    }
}

bool UI::animate() {
    bool neededRender = false;

    for (Animation* anim : UIAnimations) {
        if (anim->animate()) neededRender = true;
    }
    return neededRender;
}

void UI::addElement(Widget* element) {
    UIElements.push_back(element);
}

void UI::addAnimation(Animation* animation) {
    UIAnimations.push_back(animation);
}

void UI::addChild(Parent* parent, Widget* child) {
    parent->addChild(child);
    UIChildren.push_back(child);
}

bool UI::isRunning() { return run; }

void UI::quit() { run = false; }
