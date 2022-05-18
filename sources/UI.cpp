#include "../headers/UI.h"

void UI::UI_Init() {
    art.setImage("art.png");
    art.setPosition({160, 20});
    art.setDraggable(true);
    addChild(&b, &art);

    b.setGeometry({40, 40, 25, 250});
    b.setHoverColor({50, 50, 50, 255});
    b.setPressedColor({150, 150, 150, 255});
    addElement(&b);
    b.bindPressedFunction(std::bind(&UI::buttonPressed, this));
    b.bindHoverFunction(std::bind(&UI::buttonHover, this));

    c.setCentre(200, 300);
    c.setRadius(25);
    c.setHoverColor({50, 50, 50, 255});
    c.setPressedColor({150, 150, 150, 255});
    c.setDraggable(true);
    addElement(&c);

    e.setGeometry({300, 100, 100, 50});
    e.setColor({20, 100, 255, 155});
    e.setHoverColor({255, 255, 255, 255});
    addElement(&e);

    l.setText("hello\nworld");
    l.setGeometry({0, 0, 220, 320});
    l.setFont("helvetic.ttf", 18);
    l.setColor({255,255,255,255});
    l.setHoverColor({200,200,200,255});
    l.setPressedColor({100,100,100,255});
    l.setDraggable(true);
    addElement(&l);

    bWidth.setRange(300, 300);
    bWidth.setDuration(100);
    bWidth.setValue(b.widthReference());
    addAnimation(&bWidth);
}

void UI::buttonPressed() {
    if (!bWidth.isAnimating()) {
        bWidth.setRange(b.getGeometry().w, b.getGeometry().w + 30);
        bWidth.play();
    }
}

void UI::buttonHover() {
    if (!bWidth.isAnimating() && b.getGeometry().w > 30) {
        bWidth.setRange(b.getGeometry().w, b.getGeometry().w - 30);
        bWidth.play();
    }
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
