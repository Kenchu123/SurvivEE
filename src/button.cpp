#include "button.h"
#include "LoadMedia.h"
#include "Utility.h"
#include "Obj.h"

Button::Button(ButtonType _type): Obj() {
    //Initialize
    _buttonType = _type;
    loadTexture(typeToString(_buttonType));
};

Button::~Button() {
    free();
}

void Button::setPos(int x, int y) {
    _posX = x;
    _posY = y;
}

void Button::handleEvent(SDL_Event *e) {
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is outside of the button
		if( x < _posX || x > _posX + _objWidth || y < _posY || y > _posY + _objHeight){ inside = false; }

		//Mouse is inside button
		if( inside && e->type == SDL_MOUSEBUTTONDOWN) { 
            loadedSound.playSound("medium");
            triggered = true; 
            }
	}
}

bool Button::get_triggered() {
    return triggered;
}

void Button::update() {
    switch(_buttonType) {
        case Start: setPos((SCREEN_WIDTH - getWidth())/ 2, SCREEN_HEIGHT * 2 / 3); break;
        case Tutorial: setPos((SCREEN_WIDTH - getWidth())/ 2, SCREEN_HEIGHT * 7 / 10); break;
        case Option: setPos((SCREEN_WIDTH - getWidth())/ 2, SCREEN_HEIGHT * 8 / 10); break;
        default: setPos(0, 0);
    }
    render(_posX, _posY);
}