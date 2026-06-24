#include "MountainSDK/game.hpp"
#include "MountainSDK/engine.hpp"
#include "MountainSDK/audio.hpp"
#include "MountainSDK/input.hpp"
#include "MountainSDK/tilemap.hpp"

class MyGame : public Mountain::Game {
    Audio::SoundID  m_jumpSfx;
    Tilemap::Map    m_map;

public:
    void OnInit() override {
        m_jumpSfx = Audio::LoadSound("assets/jump.wav");

        m_map.Load("assets/level1.map");
    }

    void OnUpdate(float dt) override {
        if (Input::KeyPressed(SDLK_SPACE))
            Audio::PlaySound(m_jumpSfx);

        if (Input::KeyPressed(SDLK_ESCAPE))
            Engine::Quit();
    }

    void OnRender() override {
        // GL draw calls here
    }

    void OnCleanUp() override {
        Audio::UnloadSound(m_jumpSfx);
        m_map.Save("assets/level1.map");
    }
};

int main() {
    MyGame game;
    Engine::Run(&game);
    return 0;
}