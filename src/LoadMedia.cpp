#include "LoadMedia.h"

LoadedTexture loadedTexture;

LoadedTexture::LoadedTexture() {
    _loadedTextures.clear();
    std::string names[20] = {"Player", "GunPlayer", "machineGunPlayer", "shotGunPlayer",
                    "tree", "house1", "grass", "rock"
                    };
    for (int i = 0;i < 8; i++) _toLoadFileName.push_back(names[i]);
}

LoadedTexture::~LoadedTexture() {
    _loadedTextures.clear();
}

SDL_Texture* LoadedTexture::_loadTextureFromFile(std::string name) {
    try {
        SDL_Texture* newTexture = NULL;
        std::string s = "./media/";
        s += name;
        s += ".png";
        // std::cout << s << std::endl;
        SDL_Surface* loadedSurface = IMG_Load(s.c_str());
        if (loadedSurface == NULL) throw IMG_GetError();
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if (newTexture == NULL) throw SDL_GetError();
        SDL_FreeSurface( loadedSurface );
        return newTexture;
    }
    catch (const char* s) {
        std::cout << s << std::endl;
    }
}

void LoadedTexture::loadTexture() {
    // bulletTexture["gunBullet"] = loadTextureFromFile("gunBullet");
    for (auto name: _toLoadFileName) {
        // std::cout << "Loading: " << name << "\n";
        _loadedTextures[name] = _loadTextureFromFile(name);
    }

}

SDL_Texture* LoadedTexture::getTexture(std::string name) {
    // std::cout << "GetTexture: " << name << std::endl;
    return _loadedTextures.find(name)->second;
}
