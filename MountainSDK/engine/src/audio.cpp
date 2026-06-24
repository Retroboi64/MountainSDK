#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include "MountainSDK/audio.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>

#ifdef PlaySound
#undef PlaySound
#endif

namespace Audio {

    struct Sound {
        std::vector<float> pcm;
        ma_uint32          sampleRate;
        ma_uint32          channels;
    };

    static ma_engine                         s_engine;
    static std::unordered_map<SoundID, ma_sound>  s_sounds;
    static std::unordered_map<MusicID, ma_sound>  s_music;
    static SoundID s_nextSound = 0;
    static MusicID s_nextMusic = 0;

    bool Init() {
        if (ma_engine_init(nullptr, &s_engine) != MA_SUCCESS) {
            std::cout << "miniaudio engine init failed\n";
            return false;
        }
        return true;
    }

    void CleanUp() {
        for (auto& [id, s] : s_sounds) ma_sound_uninit(&s);
        for (auto& [id, s] : s_music)  ma_sound_uninit(&s);
        s_sounds.clear();
        s_music.clear();
        ma_engine_uninit(&s_engine);
    }

    SoundID LoadSound(const std::string& path) {
        SoundID id = s_nextSound++;
        ma_sound& s = s_sounds[id];
        if (ma_sound_init_from_file(&s_engine, path.c_str(),
            MA_SOUND_FLAG_DECODE | MA_SOUND_FLAG_ASYNC, nullptr, nullptr, &s) != MA_SUCCESS) {
            std::cout << "LoadSound failed: " << path << "\n";
            s_sounds.erase(id);
            return -1;
        }
        return id;
    }

    void PlaySound(SoundID id, int loops) {
        if (!s_sounds.count(id)) return;
        ma_sound_set_looping(&s_sounds[id], loops != 0);
        ma_sound_seek_to_pcm_frame(&s_sounds[id], 0);
        ma_sound_start(&s_sounds[id]);
    }

    void StopSound(SoundID id) {
        if (s_sounds.count(id)) ma_sound_stop(&s_sounds[id]);
    }

    void SetSoundVolume(SoundID id, float volume) {
        if (s_sounds.count(id)) ma_sound_set_volume(&s_sounds[id], volume);
    }

    void UnloadSound(SoundID id) {
        if (!s_sounds.count(id)) return;
        ma_sound_uninit(&s_sounds[id]);
        s_sounds.erase(id);
    }

    MusicID LoadMusic(const std::string& path) {
        MusicID id = s_nextMusic++;
        ma_sound& s = s_music[id];
        // Stream from disk instead of decoding fully into memory
        if (ma_sound_init_from_file(&s_engine, path.c_str(),
            MA_SOUND_FLAG_STREAM, nullptr, nullptr, &s) != MA_SUCCESS) {
            std::cout << "LoadMusic failed: " << path << "\n";
            s_music.erase(id);
            return -1;
        }
        return id;
    }

    void PlayMusic(MusicID id, int loops) {
        if (!s_music.count(id)) return;
        ma_sound_set_looping(&s_music[id], loops == -1 || loops > 0);
        ma_sound_start(&s_music[id]);
    }

    void PauseMusic() {
        for (auto& [id, s] : s_music) ma_sound_stop(&s);
    }
    void ResumeMusic() {
        for (auto& [id, s] : s_music) ma_sound_start(&s);
    }
    void StopMusic() {
        for (auto& [id, s] : s_music) {
            ma_sound_stop(&s);
            ma_sound_seek_to_pcm_frame(&s, 0);
        }
    }

    void SetMusicVolume(float volume) {
        for (auto& [id, s] : s_music) ma_sound_set_volume(&s, volume);
    }

    void UnloadMusic(MusicID id) {
        if (!s_music.count(id)) return;
        ma_sound_uninit(&s_music[id]);
        s_music.erase(id);
    }

} 