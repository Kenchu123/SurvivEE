#ifndef OBJ_H
#define OBJ_H
#include "global.h"
#include "LoadMedia.h"
// Object that have texture and can be seen on the window
class Obj {
    protected:
        std::string _type;
        double _posX, _posY; // texture position
        SDL_Texture *_objTexture;
        int _objWidth, _objHeight;
    public:
        Obj();
        ~Obj();
        void loadTexture(std::string);
        void free();
        void render(int x, int y, double angle = 0.0, SDL_Point* center = NULL, SDL_Rect* clip = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

        int getWidth();
        int getHeight();
        virtual void resize(int w, int h);
};
#endif