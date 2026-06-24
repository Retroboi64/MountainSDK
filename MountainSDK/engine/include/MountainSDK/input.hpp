#pragma once
#include <SDL3/SDL.h>

namespace Input {

    void Init();
    void BeginFrame();            
    void ProcessEvent(SDL_Event& e);

    bool KeyDown(SDL_Keycode key);     
    bool KeyPressed(SDL_Keycode key);  
    bool KeyReleased(SDL_Keycode key); 

    float MouseX();
    float MouseY();
    bool  MouseDown(int button);       
    bool  MousePressed(int button);
    bool  MouseReleased(int button);
}