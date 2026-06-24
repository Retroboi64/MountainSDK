#pragma once
#include "MountainSDK/game.hpp"

namespace Engine {
    void Run(Mountain::Game* game);

    float   GetDeltaTime();
    bool    IsRunning();
    void    Quit();
}