#pragma once

namespace Config
{
    // Window
    constexpr char BACKGROUND_TEXTURE[] = "cobblestone_bg.png";
    constexpr char MENU_BACKGROUND_TEXTURE[] = "mainMenu_bg.png";

    constexpr unsigned WINDOW_WIDTH = 768;
    constexpr unsigned WINDOW_HEIGHT = 576;
    constexpr unsigned FPS_LIMIT = 60;

    // Player
    constexpr float PLAYER_SPEED = 180.f;
    constexpr float PLAYER_GRAVITY = 1500.f;
    constexpr float PLAYER_JUMP = -500.f;

    // Player sprite
    constexpr int SPRITE_FRAME_SIZE = 32;
    constexpr int SPRITE_ANIMATION_FRAMES[] = {0, 1, 2, 1};
    constexpr int SPRITE_IDLE_FRAME = 2;
    constexpr float SPRITE_ANIMATION_STEP = 0.12f;
    constexpr float SPRITE_VISUAL_SCALE = 1.30f;

    // Player hitbox
    constexpr float PLAYER_HITBOX = 50.f;
    constexpr float PLAYER_HITBOX_WIDTH_SCALE = 0.6f;
    constexpr float PLAYER_HITBOX_HEIGHT_SCALE = 0.9f;

    // Platform
    constexpr float PLATFORM_SPEED = 60.f;
    constexpr float PLATFORM_MOVE_RANGE = 50.f;

    // Tile
    constexpr float TILE_SIZE = 32.f;

    // Levels
    constexpr unsigned LEVEL_COUNT = 6;

    // Delta time
    constexpr float MAX_DT = 0.05f;
    
    // Time of door opening
    constexpr float DOOR_TIMER = 2.f;

    // Door
    constexpr float DOOR_SCALE = 2.f;

    // Button
    constexpr float BUTTON_SCALE = 2.f;

}