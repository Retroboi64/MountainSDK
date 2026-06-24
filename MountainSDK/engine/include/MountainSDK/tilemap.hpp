#pragma once
#include <vector>
#include <string>
#include <cstdint>

namespace Tilemap {

    struct Tile {
        int  tilesetID = -1;  
        int  tileX = 0;   
        int  tileY = 0;   
        bool solid = false;
        bool visible = true;
    };

    struct Layer {
        std::string          name;
        int                  width = 0;
        int                  height = 0;
        std::vector<Tile>    tiles;

        Tile& Get(int x, int y) { return tiles[y * width + x]; }
        const Tile& Get(int x, int y) const { return tiles[y * width + x]; }
    };

    struct Map {
        std::string        name;
        int                tileWidth = 16;
        int                tileHeight = 16;
        std::vector<Layer> layers;

        Layer& AddLayer(const std::string& name, int w, int h);
        void   Save(const std::string& path) const;
        bool   Load(const std::string& path);
    };

} 