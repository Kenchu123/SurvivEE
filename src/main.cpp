#include "global.h"
#include "main.h"
#include "Obj.h"
#include "Player.h"
#include "LoadMedia.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

// background
Obj background;
// tree
Obj tree;

void init() {
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) throw SDL_GetError();
    //Set texture filtering to linear
    if (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" )) printf( "Warning: Linear texture filtering not enabled!" );
    // Create Window
    gWindow = SDL_CreateWindow( "SurvivEE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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
    loadedTexture.loadTexture();
    background.loadTexture(".grass");
    tree.loadTexture("tree");
	players[0].loadTexture( "shotGunPlayer" );
    players[1].loadTexture("machineGunPlayer");
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
        players.emplace_back(std::to_string(i));
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
    background.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
    // set player place
    players[0].setInitailPosition(SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT / 4);
    players[1].setInitailPosition(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4);

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

        // Render background
        background.render(0, 0);

        //Render update
        for (int i = players.size() - 1;i >= 0; i--) players[i].update();
        // Render tree
        tree.render(100, 100);
        //Update screen
        SDL_RenderPresent( gRenderer );
    }
    close();

}
