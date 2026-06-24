#include "MountainSDK/input.hpp"
#include <unordered_map>

namespace Input {

    static std::unordered_map<SDL_Keycode, bool> s_current, s_prev;
    static std::unordered_map<int, bool>         s_mbCurrent, s_mbPrev;
    static float s_mouseX = 0, s_mouseY = 0;

    void Init() {}

    void BeginFrame() {
        s_prev = s_current;
        s_mbPrev = s_mbCurrent;
    }

    void ProcessEvent(SDL_Event& e) {
        if (e.type == SDL_EVENT_KEY_DOWN)
            s_current[e.key.key] = true;
        else if (e.type == SDL_EVENT_KEY_UP)
            s_current[e.key.key] = false;
        else if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
            s_mbCurrent[e.button.button] = true;
        else if (e.type == SDL_EVENT_MOUSE_BUTTON_UP)
            s_mbCurrent[e.button.button] = false;
        else if (e.type == SDL_EVENT_MOUSE_MOTION) {
            s_mouseX = e.motion.x;
            s_mouseY = e.motion.y;
        }
    }

    bool KeyDown(SDL_Keycode key) { return s_current.count(key) && s_current[key]; }
    bool KeyPressed(SDL_Keycode key) { return KeyDown(key) && !(s_prev.count(key) && s_prev[key]); }
    bool KeyReleased(SDL_Keycode key) { return !KeyDown(key) && (s_prev.count(key) && s_prev[key]); }

    float MouseX() { return s_mouseX; }
    float MouseY() { return s_mouseY; }
    bool  MouseDown(int b) { return s_mbCurrent.count(b) && s_mbCurrent[b]; }
    bool  MousePressed(int b) { return MouseDown(b) && !(s_mbPrev.count(b) && s_mbPrev[b]); }
    bool  MouseReleased(int b) { return !MouseDown(b) && (s_mbPrev.count(b) && s_mbPrev[b]); }

} 