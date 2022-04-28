#include "UI.h"
#include <math.h>

UI::UI() {

}

UI::~UI() {

}

void UI::renderUI() {

    for (unsigned int i = 0; i < plates.size(); i++) {
        plates[i]->render();
    }

    for (unsigned int i = 0; i < buttons.size(); i++) {
        buttons[i]->render();
    }

    for (unsigned int i = 0; i < arts.size(); i++) {
        arts[i]->render();
    }

    for (unsigned int i = 0; i < textes.size(); i++) {
        textes[i]->render();
    }

    for (unsigned int i = 0; i < eboxes.size(); i++) {
        eboxes[i]->render();
    }

    art->geometry.y = 80;
    for (int i = 0; i < 6; ++i) {
        art->geometry.x = i * 100 + sidebar->geometry.x + 205;
        art->render();
    }

    art->geometry.y = 213;
    for (int i = 0; i < 4; ++i) {
        art->geometry.x = i * 100 + sidebar->geometry.x + 205;
        art->render();
    }

    tTip->render();
    for (Button *btn : tBtnTags) {
        if (btn->geometry.y + btn->geometry.h > tTip->geometry.y + tTip->geometry.h) {
            btn->setEnable(false);
        } else {
            btn->setEnable(true);
        }
        if (btn->getEnable()) btn->render();
    }
}

void UI::addToHandler(Button* btn) {
    buttons.emplace_back(btn);
}

void UI::addArt(ArtClass* art) {
    arts.emplace_back(art);
}

void UI::addPlate(Plate* pl) {
    plates.emplace_back(pl);
}

void UI::addText(Text* txt) {
    textes.emplace_back(txt);
}

void UI::addInput(EditBox* ebox) {
    eboxes.emplace_back(ebox);
    ebox->bindText();
}

void UI::addIntAnim(intAnimation* anim) {
    intAnims.emplace_back(anim);
}

bool UI::animation() {
    bool state = false;
    for (unsigned int i = 0; i < eboxes.size(); i++) {
        if (eboxes[i]->renderLine(frame)) state = true;
    }

    for (unsigned int i = 0; i < intAnims.size(); i++) {
        if (intAnims[i]->animate(frame)) state = true;
    }

    return state;
}



void UI::hideTBtn() {

}

void UI::inputBinding() {
    if (input_Width->isAnimating()) {
        input->bindText();
    }
}

void UI::bHideSidebar() {
    sidebar_xPos->reverse();
    bHide->text.setText(sidebar_xPos->isReversed() ? ">" : "<");
    sidebar_xPos->play();
}
