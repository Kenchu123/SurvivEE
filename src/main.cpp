#include "global.h"
#include "main.h"
#include "Player.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

// players;
std::vector<Player> players;

void init() {
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) throw SDL_GetError();
    //Set texture filtering to linear
    if (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" )) printf( "Warning: Linear texture filtering not enabled!" );
    // Create Window
    gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if (gWindow == NULL) throw SDL_GetError();
    // Create vsynced renderer for window
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if (gRenderer == NULL) throw SDL_GetError();
    // Initialize renderer color
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init( imgFlags ) & imgFlags)) throw IMG_GetError();
}

void loadMedia() {
    // Load testObject
	players[0].loadFromFile( "./media/shotGunPlayer.png" );
    players[1].loadFromFile("./media/machineGunPlayer.png");
}

void close() {
	//Free loaded images
	for (int i = 0;i < players.size(); i++) players[i].free();
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[]) {
    for (int i = 0;i < 2; i++) {
        Player tmp(std::to_string(i));
        players.push_back(tmp);
    }
    try {
        init();
        loadMedia();
    }
    catch (const char* message) {
        printf("Error: %s\n", message);
    }
    //Event handler
    SDL_Event e;
    // resize
    players[0].setInitailPosition(SCREEN_WIDTH / 4, SCREEN_HEIGHT * 3 / 4);
    players[1].setInitailPosition(SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT / 4);
    //While application is running
    bool quit = false;
    while(!quit) {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 ) {
            //User requests quit
            if(e.type == SDL_QUIT) { quit = true; break; }
            players[0].handleKeyInput(e);
        }

        //Clear screen
        SDL_SetRenderDrawColor( gRenderer, 182, 196, 182, 0 );
        SDL_RenderClear( gRenderer );

        //Render update
        for (int i = 0;i < players.size(); i++) players[i].update();
        //Update screen
        SDL_RenderPresent( gRenderer );
    }
    close();

}
