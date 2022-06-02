#include <vector>
#include "Border.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Animation.h"
#include "Image.h"
#include "Label.h"
#include "Parent.h"
#include "Grid.h"

class UI {
public:
    UI();
    ~UI();

    void init(const char* title, int xPos, int yPos, int width, int height, uint FLAG);
    bool isRunning();
    void quit();

protected:
    virtual void initElements();
    void renderUI();
    bool animate();

    std::vector<Widget*> UIElements;
    std::vector<Animation*> UIAnimations;
    std::vector<Widget*> UIChildren;

    void setRenderer(SDL_Renderer* renderer);

    SDL_Renderer* renderer;
    SDL_Point winSize = {0, 0};
    SDL_Point winPos = {0, 0};
    SDL_Window* window;
    SDL_Surface* surface;
    bool run = false;

    void addChild(Parent* parentWidget, Widget* childWidget);
    void addElement(Widget* element);
    void addAnimation(Animation* anim);
};
