#ifndef LOADMEDIA_H
#define LOADMEDIA_H

#include "global.h"
// #include "main.h"

class LoadedTexture {
    private:
        SDL_Texture* _loadTextureFromFile(std::string);
        std::vector<std::string> _toLoadFileName;
        std::map<std::string, SDL_Texture*> _loadedTextures;
    public:
        LoadedTexture();
        ~LoadedTexture();
        void loadTexture();
        SDL_Texture* getTexture(std::string);
};

extern LoadedTexture loadedTexture;

#endif