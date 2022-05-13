#include <vector>
#include "Border.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Animation.h"
#include "Image.h"

class UI {
public:
    UI();
    ~UI();

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

    void renderUI();
    bool animate();

    std::vector<Widget*> UIElements;
    std::vector<Animation*> UIAnimations;

    void setRenderer(SDL_Renderer* renderer);
    SDL_Renderer* renderer;

private:
    void addElement(Widget* element);
    void addAnimation(Animation* anim);

    void buttonPressed();
    void buttonHover();
};
