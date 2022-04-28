#include "App.h"


SDL_Color bgColor = {40, 27, 23, 255};
SDL_Rect bnn = {100, 100, 70, 40};

const char* accessable_literals = "qwertyuiopasdfghjklzxcvbnm_() ,.\"':[]1234567890-?QWERTYUIOPASDFGHJKLZXCVBNM";

bool accessable(char c) {
    for (unsigned short i = 0; i < 75; i++) {
        if (c == accessable_literals[i])
            return true;
    }
    return false;
}

void SetRenderDrawColor(SDL_Renderer* renderer, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

App::App(const char* title, int xPos, int yPos, int width, int height, uint FLAG) {
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        printf("Video initialised\n");

        if (TTF_Init() == 0) printf("fonts initialised\n");

        window = SDL_CreateWindow(title, xPos, yPos, width, height, FLAG);
        if (window) printf("Window created\n");

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        SetRenderDrawColor(renderer, bgColor);
        if (renderer) printf("Renderer created\n");
        surface = SDL_GetWindowSurface(window);

        run = true;

        initUI(renderer);

        SDL_StartTextInput();
    }
}

void App::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            run = false;
            break;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_RESIZED
                  || event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED
                  || event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED
                  || event.window.event == SDL_WINDOWEVENT_EXPOSED
                  || event.window.event == SDL_WINDOWEVENT_RESTORED)
            {
                SDL_GetWindowSize(window, &bgPl->geometry.w, &sidebar->geometry.h);
                render();
            };
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&mouseX, &mouseY);
            for (auto *btn : buttons) {
                if (btn->isMouseOn(mouseX, mouseY)) {
                    neededRender = true;
                }
            }
            for (auto *btn : tBtnTags) {
                if (btn->isMouseOn(mouseX, mouseY)) {
                    neededRender = true;
                }
            }
            if (neededRender) {
                render();
                neededRender = false;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    SDL_GetMouseState(&mouseX, &mouseY);

                    // BUTTONS
                    for (auto *btn : buttons) {
                        if (btn->isPressed(mouseX, mouseY)) {
                            neededRender = true;
                        }
                    }

                    for (auto *btn : tBtnTags) {
                        if (btn->isPressed(mouseX, mouseY)) {
                            neededRender = true;
                        }
                    }

                    // EDIT BOXES
                    for (auto ebox : eboxes) {
                        if (ebox->isMouseOn(mouseX, mouseY)) {
                            if (ebox->edit()) neededRender = true;
                        } else if (!ebox->isMouseOn(mouseX, mouseY) && ebox->state == Editing) {
                            if (ebox->complete()) neededRender = true;
                        }

                    // OTHER
                    }
                    if (neededRender) {
                        render();
                        neededRender = false;
                    }
                    break;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            for (auto *btn : buttons) {
                btn->lostPressedFocus(mouseX, mouseY);
                neededRender = true;
            }
            for (auto *btn : tBtnTags) {
                btn->lostPressedFocus(mouseX, mouseY);
                neededRender = true;
            }

            if (neededRender) {
                render();
                neededRender = false;
            }
            break;
        case SDL_KEYDOWN:
            for (unsigned int i = 0; i < eboxes.size(); i++) {
                if (eboxes[i]->state == Editing) {
                    if (event.key.keysym.sym == SDLK_BACKSPACE && eboxes[i]->text.text.length() > 0) {
                            eboxes[i]->text.text.pop_back();
                            eboxes[i]->text.setText(eboxes[i]->text.text.c_str());

                            if (eboxes[i] == input && isMakingTags == false) {
                                if (!input_Width->isAnimating() && input_Width->isRequeresReverse() && eboxes[i]->text.textWidth < eboxes[i]->plate.geometry.w * 0.85 - 70) {
                                    input_Width->reverse();
                                    input_Width->play();
                                    tTip_Width->reverse();
                                    tTip_Width->play();
                                }

                                if (eboxes[i]->text.text.length() == 0) {
                                    tTip_Height->setRange(0, 300);
                                    tTip_Height->reverse();
                                    tTip_Height->play();
                                } else {
                                    printf("backspace and request below\n");
                                    makeTags();
                                }

                            }
                            eboxes[i]->bindText();

                            render();
                    }
                    else if (event.key.keysym.sym == SDLK_c && SDL_GetModState() &KMOD_CTRL) {
                        SDL_SetClipboardText(eboxes[i]->text.text.c_str());
                    }
                    else if (event.key.keysym.sym == SDLK_v && SDL_GetModState() &KMOD_CTRL) {
                        if (strlen(SDL_GetClipboardText()) < 35) {
                            if (accessable(*SDL_GetClipboardText())) {
                                eboxes[i]->text.setText(SDL_GetClipboardText());
                                if (eboxes[i] == input && eboxes[i]->text.textWidth > eboxes[i]->plate.geometry.w * 0.9) {
                                        input_Width->play();
                                        tTip_Width->play();
                                    }
                                eboxes[i]->bindText();
                                render();
                            }
                        }
                    }
                }
            }
            break;
        case SDL_TEXTINPUT:
            for (unsigned int i = 0; i < eboxes.size(); i++) {
                if (eboxes[i]->state == Editing) {
                    if( !( SDL_GetModState() & KMOD_CTRL && ( event.text.text[ 0 ] == 'c' || event.text.text[ 0 ] == 'C' || event.text.text[ 0 ] == 'v' || event.text.text[ 0 ] == 'V' ) ) && eboxes[i]->text.text.length() < 51)
                    {
                        if (accessable(*event.text.text)) {
                            if (eboxes[i] == input) {
                                if (eboxes[i]->text.textWidth > eboxes[i]->plate.geometry.w * 0.9) {
                                    if (!input_Width->isReversed()) {
                                        input_Width->reverse();
                                        tTip_Width->reverse();
                                    }
                                    input_Width->play();
                                    tTip_Width->play();
                                } else if (input_Width->isRequeresReverse() && eboxes[i]->text.textWidth < eboxes[i]->plate.geometry.w * 0.8 - 70) {
                                    input_Width->reverse();
                                    input_Width->play();
                                    tTip_Width->reverse();
                                    tTip_Width->play();
                                }
                            }

                            if (eboxes[i]->text.textWidth < eboxes[i]->plate.geometry.w * 0.95) {
                                eboxes[i]->text.setText((eboxes[i]->text.text + *event.text.text).c_str());
                                eboxes[i]->bindText();


                                if (eboxes[i]->text.text.length() != 0 && isMakingTags == false) {
                                    makeTags();
                                }

                                render();
                            }
                        }
                    }
                }
            }
            break;
        default:
            break;
        }
}

void App::update() {
}

void App::render() {
    SDL_RenderClear(renderer);

    renderUI();

    SDL_RenderPresent(renderer);
}

void App::clean() {
    SDL_StopTextInput();
    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    printf("App cleaned\n");
}

bool App::isRunning() { return run; }

void App::makeTags() {
    isMakingTags = true;
    try {
        if (parser.request("tag", input->text.text) == false) return;
        tBtnTags.clear();

        for (int i = 0; i < parser.tag.size(); i++) {
            tBtnTags.push_back(new Button(renderer, parser.tag(i).c_str(), {tTip->geometry.x, tTip->geometry.y + i * 20, tTip->geometry.w, 19}, {33, 20, 17, 255}));
            tBtnTags[i]->text.geometry.w = 400;
            tBtnTags[i]->text.offset_margin.left = 3;
            tBtnTags[i]->text.setColor(parser.tag.typeColor(i));
            tBtnTags[i]->setAdvColors({39, 26, 23, 255}, {30, 17, 14, 255});
            tBtnTags[i]->bindText(false);
            tBtnTags[i]->text.setFont("helv-light.ttf", 14);
            if (tBtnTags[i]->text.textWidth > tTip->geometry.w) {
                tBtnTags[i]->text.offset_margin.top = 3;
                tBtnTags[i]->text.setFont("helv-light.ttf", 10);
            }
        }

        if (tTip_Height->isAnimating() == false) {
            if (tTip->geometry.h > parser.tag.size() * 20) {
                tTip_Height->setRange(parser.tag.size() * 20, tTip->geometry.h);
                tTip_Height->setIncRange(true);
                tTip_Height->reverse();
            } else {
                tTip_Height->setRange(0, parser.tag.size() * 20);
                if (!tTip_Height->isRequeresReverse()) tTip_Height->reverse();
                }
            }
        tTip_Height->play();
    } catch (std::exception *e) {
        printf("error in making tags: %s\n", e->what());
    }
    isMakingTags = false;
}

void App::makeArts() {

}
