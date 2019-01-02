#ifndef MAIN_H
#define MAIN_H

void init();
void loadMedia();
void close();
void menu(SDL_Event&);
void playing(SDL_Event&);
void gameLoad(SDL_Event&);

struct Vec {
    int x, y;
};

#endif