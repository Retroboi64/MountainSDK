#include "MountainSDK/tilemap.hpp"
#include <fstream>
#include <iostream>

namespace Tilemap {

    Layer& Map::AddLayer(const std::string& layerName, int w, int h) {
        Layer& l = layers.emplace_back();
        l.name = layerName;
        l.width = w;
        l.height = h;
        l.tiles.resize(w * h);
        return l;
    }

    void Map::Save(const std::string& path) const {
        std::ofstream f(path, std::ios::binary);
        if (!f) { std::cout << "Tilemap::Save failed: " << path << "\n"; return; }

        auto writeInt = [&](int v) { f.write((char*)&v, sizeof(int)); };
        auto writeStr = [&](const std::string& s) {
            int len = (int)s.size();
            f.write((char*)&len, sizeof(int));
            f.write(s.data(), len);
            };

        writeStr(name);
        writeInt(tileWidth);
        writeInt(tileHeight);
        writeInt((int)layers.size());

        for (auto& layer : layers) {
            writeStr(layer.name);
            writeInt(layer.width);
            writeInt(layer.height);
            for (auto& t : layer.tiles) {
                writeInt(t.tilesetID);
                writeInt(t.tileX);
                writeInt(t.tileY);
                f.write((char*)&t.solid, 1);
                f.write((char*)&t.visible, 1);
            }
        }
    }

    bool Map::Load(const std::string& path) {
        std::ifstream f(path, std::ios::binary);
        if (!f) { std::cout << "Tilemap::Load failed: " << path << "\n"; return false; }

        auto readInt = [&]() { int v; f.read((char*)&v, sizeof(int)); return v; };
        auto readStr = [&]() {
            int len = readInt();
            std::string s(len, '\0');
            f.read(s.data(), len);
            return s;
            };

        name = readStr();
        tileWidth = readInt();
        tileHeight = readInt();
        int numLayers = readInt();
        layers.clear();

        for (int i = 0; i < numLayers; i++) {
            Layer& l = layers.emplace_back();
            l.name = readStr();
            l.width = readInt();
            l.height = readInt();
            l.tiles.resize(l.width * l.height);
            for (auto& t : l.tiles) {
                t.tilesetID = readInt();
                t.tileX = readInt();
                t.tileY = readInt();
                f.read((char*)&t.solid, 1);
                f.read((char*)&t.visible, 1);
            }
        }
        return true;
    }
}