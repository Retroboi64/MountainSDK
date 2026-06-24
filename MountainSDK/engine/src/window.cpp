#include "MountainSDK/window.hpp"

namespace Window {
    SDL_Window* _window = nullptr;
    SDL_Event   _event = {};
    bool        _running = true;

    void Init() {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            std::cout << "SDL_Init failed: " << SDL_GetError() << "\n";
        }

        _window = SDL_CreateWindow("SDL3 Window", 800, 600, SDL_WINDOW_OPENGL);

        if (!GetWindow()) {
            std::cout << "Window failed: " << SDL_GetError() << "\n";
        }
    }

    void Update() {
        while (_running) {
            while (SDL_PollEvent(&_event)) {
                if (_event.type == SDL_EVENT_QUIT ||
                    _event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
                    _running = false;
                }
            }
        }
    }

    void CleanUp() {
        SDL_DestroyWindow(GetWindow());
        SDL_Quit();
    }

    SDL_Window* GetWindow() {
        return _window;
    }
}