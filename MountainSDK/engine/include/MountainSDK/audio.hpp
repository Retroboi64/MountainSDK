#pragma once
#include <string>

#ifdef PlaySound
#undef PlaySound
#endif

namespace Audio {

    using SoundID = int;
    using MusicID = int;

    bool Init();
    void CleanUp();

    SoundID LoadSound(const std::string& path);
    void    PlaySound(SoundID id, int loops = 0);
    void    StopSound(SoundID id);
    void    UnloadSound(SoundID id);

    MusicID LoadMusic(const std::string& path);
    void    PlayMusic(MusicID id, int loops = -1);
    void    PauseMusic();
    void    ResumeMusic();
    void    StopMusic();
    void    SetMusicVolume(float volume);
    void    SetSoundVolume(SoundID id, float volume);
    void    UnloadMusic(MusicID id);
}