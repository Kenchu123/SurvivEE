#include "Obj.h"
#include "LoadMedia.h"

Obj::Obj(): _objWidth(0), _objHeight(0), _objTexture(NULL), _posX(0), _posY(0) {
	//Initialize
}

Obj::~Obj() {
	free();
}

void Obj::loadTexture(std::string name) {
    // free();
    _objTexture = loadedTexture.getTexture(name);
    SDL_QueryTexture(_objTexture, NULL, NULL, &_objWidth, &_objHeight);
}

void Obj::free() {
	//Free texture if it exists
	if (_objTexture != NULL) {
		// SDL_DestroyTexture( _objTexture );
		_objTexture = NULL;
		_objWidth = 0;
		_objHeight = 0;
	}
}

void Obj::render(int x, int y, double angle, SDL_Point* center, SDL_Rect* clip, SDL_RendererFlip flip) {
    SDL_Rect renderQuad = { x, y, _objWidth, _objHeight };
    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopyEx( gRenderer, _objTexture, clip, &renderQuad, angle, center, flip );
}

int Obj::getWidth() {
	return _objWidth;
}

int Obj::getHeight() {
	return _objHeight;
}

void Obj::resize(int w, int h) {
    _objWidth = w;
    _objHeight = h;
    return;
}