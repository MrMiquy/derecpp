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

App::App(const char* title, int xPos, int yPos, int width, int height, uint FLAG) {
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        printf("Video initialised\n");

        if (TTF_Init() == 0) printf("fonts initialised\n");

        if (IMG_Init(0) == 0) printf("images initialised\n");

        window = SDL_CreateWindow(title, xPos, yPos, width, height, FLAG);
        if (window) printf("Window created\n");

        setRenderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
        if (renderer) printf("Renderer created\n");

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

        surface = SDL_GetWindowSurface(window);

        run = true;
        //SDL_StartTextInput();
    }
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
                SDL_GetWindowPosition(window, &winPos.x, &winPos.y);
                SDL_GetWindowSize(window, &winSize.x, &winSize.y);
                backgroundGeometry = {0, 0, winSize.x, winSize.y};
                neededRender = true;
            };
            break;
        default:
            break;
        }

    if (animate()) neededRender = true;

    if (neededRender) {
        neededRender = false;
        render();
    }
}

void App::update() {
    SDL_GetMouseState(&mouseX, &mouseY);

    if (mouseChanged) {
        if (mouse) {
            for (Widget* widget : UIElements) {
                if (widget->pressed(mouseX, mouseY)) {
                    neededRender = true;
                }
            }
        } else {
            for (Widget* widget : UIElements) {
                if (!widget->pressed(mouseX, mouseY)) {
                    if (widget->collisse(mouseX, mouseY)) {
                        widget->setMouseState(mouseHover);
                    } else {
                        widget->setMouseState(mouseNone);
                    }
                    neededRender = true;
                }
            }
        }
        mouseChanged = false;
    } else if (skipFrame < 4) {
        skipFrame++;
        return;
    }
    skipFrame = 0;

    if (mouseX != mouseXo && mouseY != mouseYo) {
        mouseXo = mouseX;
        mouseYo = mouseY;
        for (Widget* widget : UIElements) {
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

void App::clean() {
    //SDL_StopTextInput();
    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    printf("App cleaned\n");
}

SDL_Point App::getWindowSize() {
    return winSize;
}

SDL_Point App::getWindowPos() {
    return winPos;
}

bool App::isRunning() { return run; }
