#ifndef GLOBAL_H
#define GLOBAL_H
#define PI 3.14159265
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <string>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>
#include <map>

enum GameState {
    Menu,
    Loading,
    Playing,
    Pause,
    GameOver,
    Quit
};

enum GunType {
    Default, Gun, MachineGun, ShotGun, SubMachineGun, AK47
};

enum PlayerType {
    DefaultPlayer, GunPlayer, MachineGunPlayer, ShotGunPlayer, SubMachineGunPlayer, AK47Player
};

enum ButtonType {
    Start, Tutorial, Option
};

// enum ItemType {
//     BodyArmor1, BodyArmor2, Helmet1, Helmet2, 
//     Bandage, LifeBox, 
//     Gun, ShotGun, MachineGun, SubMachineGun, AK47,
//     Default
// };

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int LEVEL_WIDTH;
extern int LEVEL_HEIGHT;
#endif