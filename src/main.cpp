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
Obj background, StartMenu, loadingmenu, PauseMenu, GameOver1, GameOver2;
// camera
SDL_Rect camera = {0 , 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT};
SDL_Rect camera2 = {0, SCREEN_WIDTH, SCREEN_WIDTH / 2, SCREEN_HEIGHT};
// tree
ItemType itemName[12] = {Gun, MachineGun, AK47, Bomb, ShotGun, FireGun,
                    Bandage, BodyArmor1, BodyArmor2, Helmet1, Helmet2, LifeBox};
// button
Button* startButton;
Button* continueButton;

// generate time
Timer reGenTime;
int genTimes = 1;

int main(int argc, char* args[]) {
    try {
        init();
        loadMedia();
    }
    catch (const char* message) {
        printf("Error: %s\n", message);
    }
    srand(time(NULL));

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
            case GameOver: gameover(e); break;
            case Pause: pause(e); break;
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
        if (startButton->get_triggered() == true) { 
            gameState = Loading; 
            startButton->set_triggered(false);
            break; 
            }
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
    // Render StartMenu
    StartMenu.render(0, 0); 
    StartMenu.resize(1200, 800);
    // Render Button
    startButton->update(); 
    startButton->resize(300, 50);
    // tutorial.update(); option.update();

    //Update screen
    SDL_RenderPresent( gRenderer );
}

void gameLoad(SDL_Event& e) {
    while( SDL_PollEvent( &e ) != 0 ) {
        //User requests quit
        if (e.key.keysym.sym == SDLK_SPACE) { 
            generate();
            gameState = Playing;
            reGenTime.start();
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

bool checkPlace(int x, int y, int dis) {
    // check for not render on same place || render
    for (int i = 0; i < players.size(); i++) {
        if (sqrt(pow(players[i]->getPlayerX() - x, 2) + pow(players[i]->getPlayerY() - y, 2)) < dis) return 0;
    }
    for (int i = 0;i < obstacles.size(); i++) {
        if (sqrt(pow(obstacles[i]->getObsX() - x, 2) + pow(obstacles[i]->getObsY() - y, 2)) < dis) return 0;
    }
    return 1;
}

void generate(ItemType item) {
    std::cout << "reGenerate: " << typeToString(item) << std::endl;
    int a = rand() % 1800 + 100, b = rand() % 1800 + 100;
    while (!checkPlace(a, b)) {
        a = rand() % 1800 + 100;
        b = rand() % 1800 + 100;
    }
    Item* tmp = new Item(item, a, b);
    items.push_back(tmp);
}

void generate() {
    // generate players
    Player* player1 = new Player(std::to_string(1));
    Player2* player2 = new Player2(std::to_string(2));
    players.push_back(player1);
    players.push_back(player2);

    // set player place
    players[0]->setInitialPosition(LEVEL_WIDTH - 200, LEVEL_HEIGHT - 200);
    players[1]->setInitialPosition(50, 50);

    for (int i = 0;i < 25; i++) {
        int a = rand() % 25, b = rand() % 25;
        while (!checkPlace(b * 80, a * 80)) {
            a = rand() % 25, b = rand() % 25;
        }
        Obstacle* tmp = new Obstacle(BrickWall, b * 80, a * 80);
        tmp->resize(80, 80);
        obstacles.push_back(tmp);
    }
    // generate boxes

    // generate rocks
    for (int i = 0; i < 20; i++) {
        int a = rand() % 1800 + 100, b = rand() % 1800 + 100;
        while (!checkPlace(a, b, 70)) {
            a = rand() % 1800 + 100;
            b = rand() % 1800 + 100;
        }
        int cnt = rand() % 3;
        // "Rock1", "Rock2", "Rock3"
        Obstacle* tmp = new Obstacle((ObstacleType)(Rock1 + cnt), a, b, rand() % 360);
        int size = rand() % 20 + 80;
        tmp->resize(size, size);
        obstacles.push_back(tmp);
    }

    // generate trees
    for (int i = 0;i < 25; i++) {
        int a = rand() % 1800 + 100, b = rand() % 1800 + 100;
        while (!checkPlace(a, b)) {
            a = rand() % 1800 + 100;
            b = rand() % 1800 + 100;
        }
        Obstacle* tmp = new Obstacle(Tree, a, b, rand() % 360);
        int size = rand() % 20 + 80;
        tmp->resize(size, size);
        obstacles.push_back(tmp);
    }
    // generate item
    for (int i = 1;i < 12; i++) {
        int a = rand() % 1800 + 100, b = rand() % 1800 + 100;
        while (!checkPlace(a, b)) {
            a = rand() % 1800 + 100;
            b = rand() % 1800 + 100;
        }
        Item* tmp = new Item(itemName[i], a, b);
        items.push_back(tmp);
    }
}

void playing(SDL_Event& e) {
    Timer capTimer;
    capTimer.start();
    if (reGenTime.getTicks() > 10000 * genTimes) {
        std::cout << "testTicks:" << reGenTime.getTicks() << std::endl;
        generate((ItemType)(random() % 11 + 1));
        genTimes += 1;
    }
    //Handle events on queue
    while( SDL_PollEvent( &e ) != 0 ) {
        //User requests quit
        if(e.type == SDL_QUIT) { gameState = Quit; break; }
        else if (e.key.keysym.sym == SDLK_ESCAPE) { 
            gameState = Pause;
            break; }
        else if(players[0]->getState() == dead || players[1]->getState() == dead) {
            gameState = GameOver; 
            loadedSound.playSound(4, "gameoversound", -1);
            break; }
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
    // render bullet
    for (int i = 0;i < bullets.size(); i++) {
        bullets[i]->update();
        bullets[i]->renderL(camera);
        bullets[i]->renderR(camera2);
    }
    // render obstacle without tree
    for(int i = 0; i < obstacles.size(); i++) {
        if (obstacles[i]->_type == Tree) continue;
        obstacles[i]->renderL(camera);
        obstacles[i]->renderR(camera2);
    }
    // render player
    for (int i = 0;i < players.size(); i++) {
        players[i]->renderL(camera);
        players[i]->renderR(camera2);
    }
    // render Tree
    for(int i = 0; i < obstacles.size(); i++) {
        if (obstacles[i]->_type == Tree) {
            obstacles[i]->renderL(camera);
            obstacles[i]->renderR(camera2);
        }
    }
    // Render test item
    for (int i = 0; i < items.size(); i++) {
        // items[i]->update();
        items[i]->renderL(camera);
        items[i]->renderR(camera2);
    }

    // render Bloodstrip and windows
    for (int i = 0;i < players.size(); i++) {
        // for (int j = 0;j < 2; j++) {
        //     players[i]->BloodStrip[j].render(abs(i - 1) * SCREEN_WIDTH / 2 + 30, 30);
        // }
        players[i]->BloodStrip[0].render(abs(i - 1) * SCREEN_WIDTH / 2 + 30 * (1 - i) + 30, 30); // bloodstrip background
        players[i]->BloodStrip[1].render(abs(i - 1) * SCREEN_WIDTH / 2 + 30 * (1 - i) + 31, 29); // bloodstrip
        players[i]->GunBulletStrip[0].render(abs(i - 1) * SCREEN_WIDTH / 2 + 30 * (1 - i) + 30, 80); // gunbulletstrip background
        players[i]->GunBulletStrip[1].render(abs(i - 1) * SCREEN_WIDTH / 2 + 30 * (1 - i) + 31, 79); // gunbulletstrip

        int ind = 1;
        if (players[i]->gun != NULL) {
            players[i]->gun->render(SCREEN_WIDTH / (i + 1) - 30 * i - 80, SCREEN_HEIGHT - 70 * (ind++));
        }
        if (players[i]->helmet != NULL) {
            players[i]->helmet->render(SCREEN_WIDTH / (i + 1) - 30 * i - 80, SCREEN_HEIGHT - 70 * (ind++));
        }
        if (players[i]->bodyArmor != NULL) {
            players[i]->bodyArmor->render(SCREEN_WIDTH / (i + 1) - 30 * i - 80, SCREEN_HEIGHT - 70 * (ind++));
        }
    }

    // Test for draw Line
    SDL_Rect rect = { SCREEN_WIDTH / 2 - 30, 0, 60, SCREEN_HEIGHT};
    SDL_RenderDrawRect(gRenderer, &rect);
    SDL_RenderFillRect(gRenderer ,&rect);
    //Update screen
    SDL_RenderPresent( gRenderer );
    //Set Limited Framerate
    int frameTicks = capTimer.getTicks();
    if( frameTicks < SCREEN_TICK_PER_FRAME ) {
        //Wait remaining time
        SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
    }
}

void pause(SDL_Event& e) {
    while( SDL_PollEvent( &e ) != 0 ) {
        //User requests quit
        if (continueButton->get_triggered() == true) { 
            gameState = Playing; 
            continueButton->set_triggered(false);
            break; }
        else if (e.type == SDL_QUIT) { gameState = Quit; break; }
        continueButton->handleEvent(&e); 
    }
    //Clear screen
    SDL_SetRenderDrawColor( gRenderer, 182, 196, 182, 0 );
    SDL_RenderClear( gRenderer );

    // Render loadingmenu
    PauseMenu.render(0, 0);
    PauseMenu.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
    //Update screen
    
    // Render Button
    continueButton->update(); 
    continueButton->resize(350, 40);
    SDL_RenderPresent( gRenderer );
}

void gameover(SDL_Event& e) {
    while( SDL_PollEvent( &e ) != 0 ) {
        //User requests quit
        if (e.type == SDL_QUIT) { gameState = Quit; break; }
    }
    //Clear screen
    SDL_SetRenderDrawColor( gRenderer, 182, 196, 182, 0 );
    SDL_RenderClear( gRenderer );

    // Render loadingmenu
    if(players[0]->getState() == dead) {
        GameOver1.render(0,0);
        GameOver1.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    else {
        GameOver2.render(0,0);
        GameOver2.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    //Update screen
    SDL_RenderPresent( gRenderer );
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
    continueButton = new Button(Continue);
    background.loadTexture("Grass");
    StartMenu.loadTexture("StartMenu");
    loadingmenu.loadTexture("loadingmenu");
    PauseMenu.loadTexture("PauseMenu");
    GameOver1.loadTexture("GameOver1");
    GameOver2.loadTexture("GameOver2");
    loadedSound.playSound(4, "BGM", -1);
	// players[0].loadTexture("GunPlayer");
    // players[1].loadTexture("MachineGunPlayer");
}

void close() {
    background.free();
    StartMenu.free();
    loadingmenu.free();

	//Free loaded player
	for (int i = 0;i < players.size(); i++) players[i]->free();

    // destroy loadedTextures
    loadedTexture.free();

    // destroy loadedSound
    loadedSound.free();
    startButton = NULL;
    continueButton = NULL;
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

