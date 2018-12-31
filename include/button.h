#ifndef BUTTON_H
#define BUTTON_H

#include "global.h"
#include "Obj.h"


class Button : public Obj {
    private:
        ButtonType _buttonType;
        bool triggered;
    public:
        Button(ButtonType);
        ~Button();
        void handleEvent(SDL_Event *e);
        void setPos(int x, int y);
        bool get_triggered();
        void update();
};

#endif