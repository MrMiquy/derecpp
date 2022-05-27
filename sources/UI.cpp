#include "../headers/UI.h"

void UI::initElements() {
    art.setImage("art.png");
    art.setPosition({160, 20});
    art.setDraggable(true);
    addChild(&b, &art);

    b.setGeometry({40, 40, 250, 250});
    b.setHoverColor({50, 50, 50, 255});
    b.setPressedColor({150, 150, 150, 255});
    b.Colorizing(false);
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

    bWidth.setDuration(500);
    bWidth.setValue(b.xReference());
    addAnimation(&bWidth);

    bColor.setDuration(500);
    bColor.setRange(b.getPressedColor(), b.getColor());
    bColor.setValue(b.colorReference());
    addAnimation(&bColor);
}

void UI::initUI(const char* title, int xPos, int yPos, int width, int height, uint FLAG) {
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        printf("Video initialised\n");

        if (TTF_Init() == 0) printf("fonts initialised\n");

        if (IMG_Init(0) == 0) printf("images initialised\n");

        window = SDL_CreateWindow(title, xPos, yPos, width, height, FLAG);
        if (window) printf("Window created\n");

        initElements();

        setRenderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
        if (renderer) printf("Renderer created\n");

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

        surface = SDL_GetWindowSurface(window);

        run = true;
    }
}

void UI::buttonPressed() {
    if (!bColor.isAnimating()) {
        bColor.setRange(bColor.getRangeTo(), bColor.getRangeFrom());
        bColor.play();
    }

    if (!bWidth.isAnimating()) {
        bWidth.setRange(b.getGeometry().x, b.getGeometry().x + 50);
        bWidth.play();
    }
}

void UI::buttonHover() {
    if (!bWidth.isAnimating() && b.getGeometry().x > -150) {
        bWidth.setRange(b.getGeometry().x, b.getGeometry().x - 50);
        bWidth.play();
    }
}

UI::UI() {
}

UI::~UI() {
    printf("quiting...\n");
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
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
