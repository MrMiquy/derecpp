#ifndef __UI__
#include "ArtClass.h"
#include "Animation.h"
#include <vector>
#include "UI-objects.h"

class UI : public UIObjects {
public:
    int frame = 0;
    //Markup
    void initUI(SDL_Renderer* renderer);

    UI();
    ~UI();

    //Logic
    void addToHandler(Button* btn);
    void addArt(ArtClass* art);
    void addPlate(Plate* pl);
    void addText(Text* txt);
    void addInput(EditBox* ebox);
    void addIntAnim(intAnimation* anim);

    void renderUI();
    bool animation();

    // BUTTONS METHODS
    void bHideSidebar();

    // ANIMATION METHODS
    void inputBinding();
    void hideTBtn();

    std::vector<Button*> buttons;
    std::vector<Plate*> plates;
    std::vector<Text*> textes;
    std::vector<ArtClass*> arts;
    std::vector<EditBox*> eboxes;
    std::vector<intAnimation*> intAnims;

private:
    SDL_Renderer* renderer;
};

#define __UI__
#endif
