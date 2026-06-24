#pragma once
#include <SDL3/SDL.h>
#include <iostream>

namespace Window {
    extern SDL_Window* _window;
    extern SDL_Event   _event;
    extern bool        _running;

    void Init();
    void Update();
    void CleanUp();
    SDL_Window* GetWindow();
}