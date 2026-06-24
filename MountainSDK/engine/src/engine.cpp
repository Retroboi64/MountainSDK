#include "MountainSDK/engine.hpp"
#include "MountainSDK/window.hpp"
#include "MountainSDK/GL.hpp"
#include "MountainSDK/audio.hpp"
#include "MountainSDK/input.hpp"

#include <SDL3/SDL.h>

namespace Engine {

    static float   s_dt = 0.0f;
    static bool    s_running = true;

    float GetDeltaTime() { return s_dt; }
    bool  IsRunning() { return s_running; }
    void  Quit() { s_running = false; }

    void Run(Mountain::Game* game) {
        Window::Init();
        GL::Init(Window::GetWindow());
        Audio::Init();
        Input::Init();

        game->OnInit();

        Uint64 last = SDL_GetTicks();

        while (s_running) {
            Uint64 now = SDL_GetTicks();
            s_dt = (now - last) / 1000.0f;
            last = now;

            SDL_Event e;
            Input::BeginFrame();
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_EVENT_QUIT ||
                    e.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
                    s_running = false;
                Input::ProcessEvent(e);
            }

            game->OnUpdate(s_dt);
            game->OnRender();

            SDL_GL_SwapWindow(Window::GetWindow());
        }

        game->OnCleanUp();
        Audio::CleanUp();
        GL::CleanUp();
        Window::CleanUp();
    }

} 