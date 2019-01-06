#ifndef MAIN_H
#define MAIN_H

void init();
void loadMedia();
void close();
void menu(SDL_Event&);
void playing(SDL_Event&);
void gameLoad(SDL_Event&);
void pause(SDL_Event&);
void gameover(SDL_Event&);
void generate();
bool checkPlace(int, int, int dis = 100);

struct Vec {
    int x, y;
};

#endif