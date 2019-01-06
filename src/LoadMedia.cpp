#include "LoadMedia.h"

LoadedTexture loadedTexture;
LoadedSound loadedSound;

LoadedTexture::LoadedTexture() {
    free();
    _loadedTextures.clear();
    // set all texture to load
    std::string names[50] = {
                    "DefaultPlayer", "GunPlayer", "MachineGunPlayer", "ShotGunPlayer", "AK47Player", "FireGunPlayer", "ShotMask",
                    "GunBullet", "MachineGunBullet", "ShotGunBullet", "FireGunBullet", "Bomb_origin", "Explosion",
                    "Tree", "Grass", "Rock1", "Rock2", "Rock3", "Floor", "Box", "BrickWall",
                    "StartMenu", "loadingmenu", "PauseMenu", "GameOver1", "GameOver2",
                    "start", "tutorial", "option", "continue", "restart",
                    "MachineGun", "AK47", "Bomb", "Gun", "ShotGun", "FireGun",
                    "Bandage", "BodyArmor1", "BodyArmor2", "Helmet1", "Helmet2", "LifeBox","Helmet1Up", "Helmet2Up",
                    "BloodStripBackground", "BloodStripWhite", "BloodStripRed", "GunBulletStrip", "GunBulletStripBackground"
                    };
    for (int i = 0;i < 50; i++) _toLoadFileName.push_back(names[i]);
}

LoadedTexture::~LoadedTexture() {
    free();
    _loadedTextures.clear();
}

void LoadedTexture::free() {
    for (std::map<std::string, SDL_Texture*>::iterator it = _loadedTextures.begin(); it != _loadedTextures.end(); it++) {
        SDL_DestroyTexture(it->second);
        it->second = NULL;
    }
}

// load texture from file
SDL_Texture* LoadedTexture::_loadTextureFromFile(std::string name) {
    try {
        SDL_Texture* newTexture = NULL;
        std::string prefix = "../media/images/", postfix = ".png";
        SDL_Surface* loadedSurface = IMG_Load((prefix + name + postfix).c_str());
        if (loadedSurface == NULL) throw IMG_GetError();
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if (newTexture == NULL) throw SDL_GetError();
        SDL_FreeSurface( loadedSurface );
        return newTexture;
    }
    catch (const char* s) {
        std::cout << s << std::endl;
        return NULL;
    }
}

// load all texture and store in map
void LoadedTexture::loadAllTexture() {
    for (auto name: _toLoadFileName) {
        _loadedTextures[name] = _loadTextureFromFile(name);
    }

}

// get texture from map
SDL_Texture* LoadedTexture::getTexture(std::string name) {
    return _loadedTextures[name];
}

// LoadedSound
LoadedSound::LoadedSound() {
    free();
    _loadedSound.clear();
    std::string names[20] = {
        "ButtonClicking", "DefaultGunShot", "FireGunShot", "footstep", "MachineGunShot", 
        "ShotGunShot", "FireInTheHole", "bombExplosion", "Healing", "Hurt", "PickupGun", 
        "BGM", "gameoversound", "shriek", "pickuphelmet", "pickuparmor", "pickupbomb"
    };
    for (int i = 0;i < 17; i++) _toLoadFileName.push_back(names[i]);
}

LoadedSound::~LoadedSound() {
    free();
    _loadedSound.clear();
}

void LoadedSound::loadAllSound() {
    for (auto name: _toLoadFileName) {
        _loadedSound[name] = _loadSoundFromFile(name);
    }
}


Mix_Chunk* LoadedSound::_loadSoundFromFile(std::string name) {
    std::string prefix = "../media/sound/", profix = ".wav";
    return Mix_LoadWAV((prefix + name + profix).c_str());
}


Mix_Chunk* LoadedSound::getSound(std::string name) {
    return _loadedSound[name];
}

void LoadedSound::playSound(int channel, std::string name, int times) {
    Mix_PlayChannel(channel, _loadedSound[name], times);
    return;
}

void LoadedSound::free() {
    for (std::map<std::string, Mix_Chunk*>::iterator it = _loadedSound.begin(); it != _loadedSound.end(); it++) {
        Mix_FreeChunk(it->second);
        it->second = NULL;
    }
}