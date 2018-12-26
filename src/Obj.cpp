#include "Obj.h"

Obj::Obj() {
	//Initialize
	_objTexture = NULL;
	_objWidth = 0;
	_objHeight = 0;
}

Obj::~Obj() {
	free();
}

void Obj::loadFromFile(std::string path) {
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) throw IMG_GetError();
    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
    newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
    if (newTexture == NULL) throw SDL_GetError();
    _objWidth = loadedSurface->w;
    _objHeight = loadedSurface->h;
    SDL_FreeSurface( loadedSurface );
    _objTexture = newTexture;
}

void Obj::free() {
	//Free texture if it exists
	if (_objTexture != NULL) {
		SDL_DestroyTexture( _objTexture );
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