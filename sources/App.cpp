#include "../headers/App.h"

SDL_Color cBackground = {40, 27, 23, 255};
SDL_Rect backgroundGeometry = {0, 0, 0, 0};

const char* accessable_literals = "qwertyuiopasdfghjklzxcvbnm_() ,.\"':[]1234567890-?QWERTYUIOPASDFGHJKLZXCVBNM";

bool accessable(char c) {
    for (unsigned short i = 0; i < 75; i++) {
        if (c == accessable_literals[i])
            return true;
    }
    return false;
}

App::App() {
}

void App::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
            mouse = true;
            mouseChanged = true;
            break;
        case SDL_MOUSEBUTTONUP:
            mouse = false;
            mouseChanged = true;
            break;
        case SDL_MOUSEWHEEL:
            if (event.wheel.y > 0) {
                mouseUp = true;
            } else if (event.wheel.y < 0) {
                mouseDown = true;
            }
            break;

        case SDL_QUIT:
            run = false;
            break;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_RESIZED || event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
                SDL_GetWindowPosition(window, &winPos.x, &winPos.y);
                SDL_GetWindowSize(window,  &winSize.x,  &winSize.y);
                backgroundGeometry = {0, 0, winSize.x, winSize.y};

                for (Widget* widget : UIElements) {
                    widget->winResize();
                }
                neededRender = true;
            } else if (     event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED
                  || event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED
                  || event.window.event == SDL_WINDOWEVENT_EXPOSED
                  || event.window.event == SDL_WINDOWEVENT_RESTORED)
            {
                neededRender = true;
            }
            break;
        default:
            break;
        }
}

void App::update() {
    SDL_GetMouseState(&mouseX, &mouseY);
    if (mouseChanged) {
        if (mouse) {
            for (Widget* widget : concat(UIChildren, UIElements)) {
                if (widget->pressed(mouseX, mouseY)) {
                    lastPressedWidget = widget;
                    neededRender = true;
                    break;
                }
            }
        } else {
            for (Widget* widget : concat(UIChildren, UIElements)) {
                if (!widget->pressed(mouseX, mouseY, false)) {
                    if (widget->collisse(mouseX, mouseY)) {
                        widget->setMouseState(mouseHover);
                    } else {
                        widget->setMouseState(mouseNone);
                    }
                    lastPressedWidget = NULL;
                    neededRender = true;
                }
            }
        }
        mouseChanged = false;
    } if (animate()) {
        neededRender = true;
    } if (mouse && lastPressedWidget != NULL && lastPressedWidget->isDraggable()) {
        lastPressedWidget->setGeometry({mouseX - lastPressedWidget->getGeometry().w / 2, mouseY - lastPressedWidget->getGeometry().h / 2, lastPressedWidget->getGeometry().w, lastPressedWidget->getGeometry().h});
        neededRender = true;
    }
    if (mouseUp) {
        for (Widget* widget : UIElements) {
            if (widget->collisse(mouseX, mouseY)) {
                widget->scrollUp();
            }
        }
    } else if (mouseDown) {
        for (Widget* widget : UIElements) {
            if (widget->collisse(mouseX, mouseY)) {
                widget->scrollDown();
            }
        }
    }
    mouseUp = mouseDown = false;
    if (skipFrame < 2) {
        skipFrame++;
        return;
    }
    skipFrame = 0;

    if (mouseX != mouseXo && mouseY != mouseYo) {
        mouseXo = mouseX;
        mouseYo = mouseY;
        for (Widget* widget : concat(UIChildren, UIElements)) {
            if (widget->hover(mouseX, mouseY)) {
                neededRender = true;
                break;
            }
        }
    }

    if (neededRender) {
        neededRender = false;
        render();
    }
}

void App::render() {
    SDL_RenderClear(renderer);

    // FILL BACKGROUND WITH COLOR
    SDL_SetRenderDrawColor(renderer, cBackground.r, cBackground.g, cBackground.b, cBackground.a);
    SDL_RenderFillRect(renderer, &backgroundGeometry);
    // --------------------------
    renderUI();

    SDL_RenderPresent(renderer);
}

App::~App() {
    //SDL_StopTextInput();
    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    printf("App cleaned\n");
}

void App::cycle() {
    frameStart = SDL_GetTicks();

    handleEvents();
    update();

    frameTime = SDL_GetTicks() - frameStart;

    if (frameDelay > frameTime)
        SDL_Delay(frameDelay - frameTime);
}

SDL_Point App::getWindowSize() {
    return winSize;
}

SDL_Point App::getWindowPos() {
    return winPos;
}
