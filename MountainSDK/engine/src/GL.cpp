#include "MountainSDK/GL.hpp"
#include <iostream>

namespace GL {

    SDL_GLContext _context = nullptr;

    bool Init(SDL_Window* window) {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        _context = SDL_GL_CreateContext(window);
        if (!_context) {
            std::cout << "GL context failed: " << SDL_GetError() << "\n";
            return false;
        }
        SDL_GL_MakeCurrent(window, _context);
        SDL_GL_SetSwapInterval(1);
        return true;
    }

    void CleanUp() {
        if (_context) SDL_GL_DestroyContext(_context);
    }

}