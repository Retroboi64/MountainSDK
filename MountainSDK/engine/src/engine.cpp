#include <iostream>
#include <SDL3/SDL.h>

namespace Engine {
	void Init() {
        if (!SDL_Init(SDL_INIT_VIDEO))
        {
            std::cout << "SDL_Init failed: " << SDL_GetError() << "\n";
        }

        SDL_Window* window = SDL_CreateWindow(
            "SDL3 Window",
            800,
            600,
            SDL_WINDOW_OPENGL
        );

        if (!window)
        {
            std::cout << "Window failed: " << SDL_GetError() << "\n";
        }

        SDL_Delay(2000);

        SDL_DestroyWindow(window);
        SDL_Quit();
	}
}