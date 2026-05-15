#include "SoundManager.hpp"
#include <string>
#include <iostream>

SoundManager::SoundManager()
{
    if (gemBuffer.loadFromFile(std::string(GAME_ASSET_DIR) + "/sounds/gem_sound.wav"))
    {
        gemSound.setBuffer(gemBuffer);
        gemSound.setVolume(30.f); 
    }
    if (winBuffer.loadFromFile(std::string(GAME_ASSET_DIR) + "/sounds/win_sound.wav")){
        winSound.setBuffer(winBuffer);
        winSound.setVolume(20.f); 
    }

    playMenuMusic();
}

void SoundManager::playMenuMusic()
{
    music.stop();
    if (music.openFromFile(std::string(GAME_ASSET_DIR) + "/sounds/menu_music.wav"))
    {
        music.setLoop(true);
        music.setVolume(20.f);
        music.play();
    }
}

void SoundManager::playGameMusic()
{
    music.stop();
    if (music.openFromFile(std::string(GAME_ASSET_DIR) + "/sounds/background_music.ogg"))
    {
        music.setLoop(true);
        music.setVolume(20.f);
        music.play();
    }
}

void SoundManager::playDeathMusic()
{
    music.stop();
    if (music.openFromFile(std::string(GAME_ASSET_DIR) + "/sounds/lose_music.wav"))
    {   
        music.setLoop(false);
        music.setVolume(20.f);
        music.play();
    }
}

void SoundManager::stopAllSounds()
{
    music.stop();
    gemSound.stop();
    winSound.stop();
}

void SoundManager::stopMusic()                  { music.stop(); }
void SoundManager::setMusicVolume(float volume) { music.setVolume(volume); }

void SoundManager::playGemCollect()             { gemSound.play(); }
void SoundManager::playWin()                    { winSound.play(); }