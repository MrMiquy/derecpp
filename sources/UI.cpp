#include "../headers/UI.h"

UI::UI() {
    b.setGeometry({20, 80, 300, 50});
    b.setHoverColor({50, 50, 50, 255});
    b.setPressedColor({150, 150, 150, 255});
    addElement(&b);
    b.bindPressedFunction(std::bind(&UI::buttonPressed, this));
    b.bindHoverFunction(std::bind(&UI::buttonHover, this));

    c.setCentre(200, 300);
    c.setRadius(25);
    c.setHoverColor({50, 50, 50, 255});
    c.setPressedColor({150, 150, 150, 255});
    //c.setFill(false);
    addElement(&c);

    e.setGeometry({300, 100, 100, 50});
    e.setColor({20, 100, 255, 155});
    e.setHoverColor({255, 255, 255, 255});
    addElement(&e);

    bWidth.setRange(300, 300);
    bWidth.setDuration(400);
    bWidth.setValue(b.widthReference());
    addAnimation(&bWidth);

    art.setImage("art.png");
    art.setPosition({300, 230});
    addElement(&art);
}

void UI::buttonPressed() {
    bWidth.setRange(b.getGeometry().w, b.getGeometry().w + 30);
    bWidth.play();
}

void UI::buttonHover() {

}


UI::~UI() {
}

void UI::setRenderer(SDL_Renderer* _renderer) {
    renderer = _renderer;

    for (Widget* widget : UIElements ) {
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
