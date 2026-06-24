#pragma once

namespace Mountain {

    class Game {
    public:
        virtual ~Game() = default;

        virtual void OnInit() {}
        virtual void OnUpdate(float dt) {}
        virtual void OnRender() {}
        virtual void OnCleanUp() {}
    };

}