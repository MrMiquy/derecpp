#include <vector>
#include "Border.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Animation.h"
#include "Image.h"
#include "Label.h"
#include "Parent.h"

class UI {
public:
    UI();
    ~UI();

    void UI_Init();

protected:
    // Elements

    // Borders
    Border b;
    Animation bWidth;

    // Cirles
    Circle c;

    // Ellipses
    Ellipse e;

    // Images
    Image art;

    // Labels
    Label l;

    void renderUI();
    bool animate();

    std::vector<Widget*> UIElements;
    std::vector<Animation*> UIAnimations;
    std::vector<Widget*> UIChildren;

    void setRenderer(SDL_Renderer* renderer);
    SDL_Renderer* renderer;

private:
    void addChild(Parent* parentWidget, Widget* childWidget);
    void addElement(Widget* element);
    void addAnimation(Animation* anim);

    void buttonPressed();
    void buttonHover();
};
