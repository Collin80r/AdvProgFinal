#include <iostream>
#include <cmath>
#include <SDL3/SDL.h>

using namespace std;

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

int WinMain() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_DisplayID * displayID = SDL_GetDisplays(nullptr);
    const SDL_DisplayMode* display = SDL_GetDesktopDisplayMode(displayID[0]);
    if (display == nullptr) {
        std::cerr << "SDL_GetDisplay Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    SDL_Window* win = SDL_CreateWindow("SDL3 Image", display->w*.8, display->h*.8, 0);
    if (win == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* ren = SDL_CreateRenderer(win, NULL);
    if (ren == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Surface* image = SDL_LoadPNG("DVD_logo.png");
    if (image == nullptr) {
        std::cerr << "SDL_LoadPNG Error: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_FRect rect{};
    rect.x = 0;
    rect.y = 0;
    rect.w = image->w/4;
    rect.h = image->h/4;

    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, image);
    SDL_DestroySurface(image);

    if (tex == nullptr) {
        std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Event e;
    bool quit = false;

    float angle = 3.14/180*120;
    int xSign{1};
    int ySign{1};
    float velocity = 2;
    int windowWidth{0};
    int windowHeight{0};
    SDL_GetWindowSize(win, &windowWidth, &windowHeight);
    rect.x = (windowWidth - rect.w)/2;
    rect.y = (windowHeight - rect.h)/2;
    int safeWidth = windowWidth - rect.w;
    int safeHeight = windowHeight - rect.h;
    
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }
        float dx = cos(angle)*velocity;
        float dy = sin(angle)*velocity;
        rect.x += dx*xSign;
        rect.y += dy*ySign;
        if (rect.x > safeWidth) {
            rect.x = (safeWidth - (rect.x-safeWidth));
            xSign *= -1;
            SDL_SetTextureColorMod(tex,rand()%256,rand()%256,rand()%256);
        }
        if (rect.x < 0) {
            rect.x *= -1;
            xSign *= -1;
            SDL_SetTextureColorMod(tex,rand()%256,rand()%256,rand()%256);
        }
        if (rect.y > safeHeight) {
            rect.y = (safeHeight - (rect.y-safeHeight));
            ySign *= -1;
            SDL_SetTextureColorMod(tex,rand()%256,rand()%256,rand()%256);
        }
        if (rect.y < 0) {
            rect.y *= -1;
            ySign *= -1;
            SDL_SetTextureColorMod(tex,rand()%256,rand()%256,rand()%256);
        }

        SDL_RenderClear(ren);
        SDL_RenderTexture(ren, tex, NULL, &rect);
        SDL_RenderPresent(ren);
        SDL_Delay(1000/120);
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}