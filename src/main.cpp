#include "global.h"
#include "main.h"
#include "Obj.h"
#include "Player.h"
#include "Bullet.h"
#include "LoadMedia.h"
#include "Timer.h"
#include "button.h"
#include "Obstacle.h"
#include "Item.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
int SCREEN_WIDTH = 1200;
int SCREEN_HEIGHT = 800;
int LEVEL_WIDTH = 2000;
int LEVEL_HEIGHT = 2000;
int SCREEN_FPS = 60;
int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

// set Game State
GameState gameState;
// background, loadingmenu
Obj background, loadingmenu;
// camera
SDL_Rect camera = {0 , 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT};
SDL_Rect camera2 = {0, SCREEN_WIDTH, SCREEN_WIDTH /2, SCREEN_HEIGHT};
// tree
std::string itemName[12] = {"MachineGun", "AK47", "Bomb", "Gun", "ShotGun", "SubMachineGun",
                    "Bandage", "BodyArmor1", "BodyArmor2", "Helmet1", "Helmet2", "LifeBox"};
// Title
Obj Title;
// button
Button* startButton;
// obstacle
std::string ObstacleName[2] = {"Tree", "Rock"};
// test for Helmet
Item helmet1;

int main(int argc, char* args[]) {
    try {
        init();
        loadMedia();
    }
    catch (const char* message) {
        printf("Error: %s\n", message);
    }
    for (int i = 0;i < 12; i++) {
        Item* tmp = new Item(itemName[i], 200.0, i * 60);
        items.push_back(tmp);
    }
    for(int i = 0; i < 2; i++) {
        Obstacle* tmp2 = new Obstacle(ObstacleName[i], 500, 100 + i * 100);
        obstacles.push_back(tmp2);
    }
    //Event handler
    SDL_Event e;
    // initail game State
    gameState = Menu;
    while (gameState != Quit) {
        SDL_GetWindowSize(gWindow, &SCREEN_WIDTH, &SCREEN_HEIGHT);
        switch (gameState) {
            case Menu: menu(e); break;
            case Loading: gameLoad(e); break;
            case Playing: playing(e); break;
            default: 
                gameState = Quit;
                break;
        }
    }
    // close game
    close();

}

void menu(SDL_Event& e) {
    //Handle events on queue
    while( SDL_PollEvent( &e ) != 0 ) {
        //User requests quit
        if (startButton->get_triggered() == true) { gameState = Loading; break; }
        else if (e.type == SDL_QUIT) { gameState = Quit; break; }
        startButton->handleEvent(&e); 
        // tutorial.handleEvent(&e); option.handleEvent(&e);
    }
    //Clear screen
    SDL_SetRenderDrawColor( gRenderer, 182, 196, 182, 0 );
    SDL_RenderClear( gRenderer );

    // resize
    background.resize(LEVEL_WIDTH, LEVEL_HEIGHT);
    // Render background
    background.render(0, 0);

    // Render Title
    Title.render((SCREEN_WIDTH - Title.getWidth()) / 2 , SCREEN_HEIGHT / 5);

    // Render Button
    startButton->update(); 
    startButton->resize(152, 42);
    // tutorial.update(); option.update();

    //Update screen
    SDL_RenderPresent( gRenderer );
}

void gameLoad(SDL_Event& e) {
    while( SDL_PollEvent( &e ) != 0 ) {
        //User requests quit
        if (e.key.keysym.sym == SDLK_SPACE) { 
            Player* player1 = new Player(std::to_string(1));
            Player2* player2 = new Player2(std::to_string(2));
            players.push_back(player1);
            players.push_back(player2);
            // set player place
            players[0]->setInitialPosition(SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT / 4);
            players[1]->setInitialPosition(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4);
            gameState = Playing;
            break;
        }
        else if (e.type == SDL_QUIT) { gameState = Quit; break; }
    }
    //Clear screen
    SDL_SetRenderDrawColor( gRenderer, 182, 196, 182, 0 );
    SDL_RenderClear( gRenderer );

    // Render loadingmenu
    loadingmenu.render(0, 0);
    loadingmenu.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
    //Update screen
    SDL_RenderPresent( gRenderer );
}

void playing(SDL_Event& e) {
    Timer capTimer;
    capTimer.start();
    //Handle events on queue
    while( SDL_PollEvent( &e ) != 0 ) {
        //User requests quit
        if(e.type == SDL_QUIT) { gameState = Quit; break; }
        players[0]->handleKeyInput(e);
        players[1]->handleKeyInput(e);
    }

    //Clear screen
    SDL_RenderClear( gRenderer );
    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 50 );
    // Render background
    background.render(0, 0, 0.0, NULL, &camera);
    background.render(SCREEN_WIDTH / 2, 0, 0.0, NULL, &camera2);

    //Render update
    for (int i = 0;i < players.size(); i++) {
        players[i]->update();
    }

    //Center the camera over the Player
    camera.x = players[1]->getPlayerX() - SCREEN_WIDTH / 4;
    camera.y = players[1]->getPlayerY() - SCREEN_HEIGHT / 2;
    camera2.x = players[0]->getPlayerX() - SCREEN_WIDTH / 4;
    camera2.y = players[0]->getPlayerY() - SCREEN_HEIGHT / 2;
    //Keep the camera in bounds
    if( camera.x < 0 ) {camera.x = 0;}
    if( camera.y < 0 ) {camera.y = 0;}
    if( camera.x > LEVEL_WIDTH - camera.w ) {camera.x = LEVEL_WIDTH - camera.w;}
    if( camera.y > LEVEL_HEIGHT - camera.h ) {camera.y = LEVEL_HEIGHT - camera.h;}
    //Keep the camera2 in bounds
    if( camera2.x < 0 ) {camera2.x = 0;}
    if( camera2.y < 0 ) {camera2.y = 0;}
    if( camera2.x > LEVEL_WIDTH - camera2.w ) {camera2.x = LEVEL_WIDTH - camera2.w;}
    if( camera2.y > LEVEL_HEIGHT - camera2.h ) {camera2.y = LEVEL_HEIGHT - camera2.h;}

    for (int i = 0;i < players.size(); i++) {
        players[i]->renderL(camera);
        players[i]->renderR(camera2);
        helmet1.SetPosition(players[i]->getPlayerX(), players[i]->getPlayerY());
        helmet1.renderL(camera);
        helmet1.renderR(camera2);
    }

    for (int i = 0;i < bullets.size(); i++) {
        bullets[i]->update();
        bullets[i]->renderL(camera);
        bullets[i]->renderR(camera2);
    }

    // Render test item
    for (int i = 0; i < items.size(); i++) {
        // items[i]->update();
        items[i]->renderL(camera);
        items[i]->renderR(camera2);
    }
    for(int i = 0; i < obstacles.size(); i++) {
        // obstacles[i]->update();
        obstacles[i]->renderL(camera);
        obstacles[i]->renderR(camera2);
    }

    // render Bloodstrip
    for (int i = 0;i < players.size(); i++) {
        // for (int j = 0;j < 2; j++) {
        //     players[i]->BloodStrip[j].render(abs(i - 1) * SCREEN_WIDTH / 2 + 30, 30);
        // }
        players[i]->BloodStrip[0].render(abs(i - 1) * SCREEN_WIDTH / 2 + 30, 30); // strip background
        players[i]->BloodStrip[1].render(abs(i - 1) * SCREEN_WIDTH / 2 + 31, 29); // blood strip
    }

    // Test for draw Line
    SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT);
    //Update screen
    SDL_RenderPresent( gRenderer );
    int frameTicks = capTimer.getTicks();
    if( frameTicks < SCREEN_TICK_PER_FRAME ) {
        //Wait remaining timefgdwvdsdvwvavvwwvvsavdvwdvavsvwsvvwvvvwvsvwds wvvwvsvdwvvavsdvwvvdsvdsvwvsvawvvsvdvas
        SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
    }
}

void init() {
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) throw SDL_GetError();
    //Set texture filtering to linear
    if (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" )) printf( "Warning: Linear texture filtering not enabled!" );
    // Create Window
    gWindow = SDL_CreateWindow( "SurvivEE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE );
    if (gWindow == NULL) throw SDL_GetError();
    // Create vsynced renderer for window
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if (gRenderer == NULL) throw SDL_GetError();
    // Initialize renderer color
    SDL_SetRenderDrawColor( gRenderer, 182, 196, 182, 100 );
    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init( imgFlags ) & imgFlags)) throw IMG_GetError();
    // Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) throw Mix_GetError();
}

void loadMedia() {
    // Load all texture
    loadedTexture.loadAllTexture();
    // Load all sound
    loadedSound.loadAllSound();

    startButton = new Button(Start);
    background.loadTexture("Grass");
    Title.loadTexture("Title");
    loadingmenu.loadTexture("loadingmenu");
    // load helmet1
    helmet1.loadTexture("Helmet1Up");
    helmet1.resize(40, 40);
	// players[0].loadTexture("GunPlayer");
    // players[1].loadTexture("MachineGunPlayer");
}

void close() {
    background.free();
    Title.free();
    loadingmenu.free();

	//Free loaded player
	for (int i = 0;i < players.size(); i++) players[i]->free();

    // destroy loadedTextures
    loadedTexture.free();

    // destroy loadedSound
    loadedSound.free();
    startButton = NULL;
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	
	//Quit SDL subsystems
	IMG_Quit();
    Mix_Quit();
	SDL_Quit();
}

