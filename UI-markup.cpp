#include "UI.h"

const char* ff = "helv-light.ttf";
SDL_Color white = {255, 255, 255, 255};

SDL_Color color_background_plate = {30, 21, 18, 255};
SDL_Color color_sidebar_plate = {50, 34, 30, 255};
SDL_Color color_input_editbox = {43, 31, 28, 255};
SDL_Color color_tip = {33, 20, 17, 255};
SDL_Color color_button = {50, 34, 30, 255};

void hide_sidebar() {
    printf("button pressed correct\n");
}

void UI::initUI(SDL_Renderer* _renderer) {
    renderer = _renderer;

    art = new ArtClass(renderer, "art.png");

    logo = new ArtClass(renderer, "logo.png");
    logo->geometry.x = 200;
    addArt(logo);

    bgPl = new Plate(renderer, {0, 0, 1000, 75}, color_background_plate);
    addPlate(bgPl);

    sidebar = new Plate(renderer, {0, 75, 200, 800}, color_sidebar_plate);
    addPlate(sidebar);
    sidebar_xPos = new intAnimation(&sidebar->geometry.x, 0, -sidebar->geometry.w, 80);
    addIntAnim(sidebar_xPos);

    title_Tags = new Text(renderer, "Tags:", ff, 20, {50, 100, 50, 50});
    title_Tags->setDock(Top, 10);
    sidebar->addChild(title_Tags);

    input = new EditBox(renderer, {20, 55, 180, 20}, color_input_editbox, white);
    input->setEditColor({70, 50, 45, 255}, white);
    input->hint.setText("Search by tag");
    input->hint.setDock(Center);
    input->text.setText("");
    input->text.setDock(Center);
    input->text.margin.left += 3;
    addInput(input);
    input_Width = new intAnimation(&input->plate.geometry.w, input->plate.geometry.w, input->plate.geometry.w + 70, 80);
    input_Width->setFrameFunc(std::bind(&UI::inputBinding, this));
    addIntAnim(input_Width);

    bSettings = new Button(renderer, "Loli for fapping", {0, 0, 0, 0}, color_button);
    bSettings->bindText(false);
    bSettings->text.setFont(ff, 14);
    bSettings->text.setDock(Center);
    bSettings->bindSignal(hide_sidebar);
    addToHandler(bSettings);

    bHide = new Button(renderer, "<", {0, 60, 15, 15}, color_button);
    bHide->bindText(false);
    bHide->text.setFont(ff, 14);
    bHide->text.setDock(Center);
    bHide->bindSignal(std::bind(&UI::bHideSidebar, this));
    addToHandler(bHide);


    // pop-up plates and tips
    tTip = new Plate(renderer, {input->plate.geometry.x + 5, input->plate.geometry.y + input->plate.geometry.h, input->plate.geometry.w - 10, 0}, color_tip);
    tTip_Width = new intAnimation(&tTip->geometry.w, tTip->geometry.w, input->plate.geometry.w - input->plate.geometry.x + 100, 100);
    addIntAnim(tTip_Width);
    tTip_Height = new intAnimation(&tTip->geometry.h, 0, 300, 100);
    tTip_Height->reverse();
    addIntAnim(tTip_Height);
}


