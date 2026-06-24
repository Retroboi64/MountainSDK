#pragma once
#include <SDL3/SDL.h>

namespace GL {
    extern SDL_GLContext _context;

    bool Init(SDL_Window* window);
    void CleanUp();
}