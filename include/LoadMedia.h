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
        void loadAllTexture();
        SDL_Texture* getTexture(std::string);
        void free(); // Destroy Texture
};

class LoadedSound {
    private:
        Mix_Chunk* _loadSoundFromFile(std::string);
        std::vector<std::string> _toLoadFileName;
        std::map<std::string, Mix_Chunk*> _loadedSound;
    public:
        LoadedSound();
        ~LoadedSound();
        void loadAllSound();
        Mix_Chunk* getSound(std::string);
        void playSound(int, std::string, int);
        void free();
};


extern LoadedTexture loadedTexture;
extern LoadedSound loadedSound;

#endif