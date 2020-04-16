/*
What is finished: 
    The primary mechanics are done for the game, particularly from a user end with the pig.
    There will be no new features with the pig (besides the cheat) for normal gameplay.
    Features that will not likely need updates from a mechanics standpoint are coins, flight, score keeping, and most pig movement.
    Some rudimentary sprite art is also finished.
Still needs work:
    I need to add more interest in the form of gameplay, like different sized clouds, horizontally moving clouds as stated in M01,
    better "randomization", etc.
    Requirements that need to be met are sound, animation, backgrounds, and the cheat. These will mostly likely come with the next 
    milestone. 
    There are a few issues here and there that I would like to address as well for bug free gameplay.
    (I also need to cleanup my code)
Known Bugs:
    The lose screen is sometimes reached too quickly on disappearing clouds. I believe its happening accurately with falling,
     but it is too quick to tell.
    If a cloud disappears and you move to the cloud below for safety, you can't reach the next cloud and are stuck... Hopefully, 
    adding more clouds will help alleviate this. I plan to add another "layer" or two of cloud types so that I can maintain proper 
    distances while scrolling.  
    A potential bug comes in keeping the score because it will eventually max out.
    The pig can't jump while the screen scrolls. Originally this was intentional, but now I can't break it. I have another
     implementation of the game that uses the gravity Marie presented and no vOff scrolling just cloud movement to avoid this issue, 
     but it has its own set of bugs (pig shifts down slightly with cloud as it lands).
        I'm going to keep developing both versions of the game and see which ends up the least buggy.
How to play:
    Navigate the splash screen using the L R buttons (a and s on the keyboard) and press start. Use the left and right arrow keys to 
    move horizontally, and the up arrow key to jump. Keep moving up and landing on clouds while collecting coins. If you land on
    wings, you will fly for short period of time, and the flight slow down until you stop. If you lose, press start to navigate back
    through the screens. 
*/





#include <stdlib.h>
#include "myLib.h"
#include "game.h"
#include "splash1.h"
#include "splash2.h"
#include "instructions.h"
#include "gameBg.h"
#include "spriteSheet.h"
#include "pauseBg.h"
#include "loseBg.h"

// Prototypes
void initialize();

// State Prototypes
void goToStart();
void start();
void goToGame();
void game();
void goToPause();
void pause();
void goToLose();
void lose();
void goToInstruct();
void instruct();

// States
enum {START, GAME, PAUSE, LOSE, INSTRUCT};
int state;


// Button Variables
unsigned short buttons;
unsigned short oldButtons;

// Variables
int seed;
int time;
int winner;
int loser;
int startScreen;

int main() {

    initialize();

    while(1) {

        // Update button variables
        oldButtons = buttons;
        buttons = BUTTONS;
                
        // State Machine
        switch(state)
        {
            case START:
                start();
                break;
            case GAME:
                game();
                break;
            case PAUSE:
                pause();
                break;
            case LOSE:
                lose();
                break;
            case INSTRUCT:
                instruct();
                break;
        }

    }
}


// Sets up GBA
void initialize() {
    
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(28) | BG_4BPP | BG_SIZE_SMALL;
    REG_DISPCTL = MODE0 | BG0_ENABLE | SPRITE_ENABLE;

    goToStart();
}

//go to start state
void goToStart() {

    DMANow(3, splash1Pal, PALETTE, 256);
    DMANow(3, splash1Tiles, &CHARBLOCK[0], splash1TilesLen / 2);
    DMANow(3, splash1Map, &SCREENBLOCK[28], 1024 * 4);
    hideSprites();
    DMANow(3, shadowOAM, OAM, 512);
    startScreen = 0;
    state = START;

    // Begin the seed randomization
    seed = 0;
}
// Start state
void start() {

    seed++;

    // State transitions
    //switch between backgrounds to select next state
    if (BUTTON_PRESSED(BUTTON_L)) {
        DMANow(3, splash1Pal, PALETTE, 256);
        DMANow(3, splash1Tiles, &CHARBLOCK[0], splash1TilesLen / 2);
        DMANow(3, splash1Map, &SCREENBLOCK[28], 1024 * 4);
        startScreen = 0;
        REG_BG0VOFF = 0;
    }
    if (BUTTON_PRESSED(BUTTON_R)) {
        DMANow(3, splash2Pal, PALETTE, 256);
        DMANow(3, splash2Tiles, &CHARBLOCK[0], splash2TilesLen / 2);
        DMANow(3, splash2Map, &SCREENBLOCK[28], 1024 * 4);
        startScreen = 1;
    }
    if (!startScreen && BUTTON_PRESSED(BUTTON_START)) {
        goToInstruct();
    }
    if (startScreen && BUTTON_PRESSED(BUTTON_START)) {
        // Seed the random generator
        srand(seed);
        goToGame();
        initGame();
    }
}

//go to instruction screen
void goToInstruct(){
    DMANow(3, instructionsPal, PALETTE, 256);
    DMANow(3, instructionsTiles, &CHARBLOCK[0], instructionsTilesLen / 2);
    DMANow(3, instructionsMap, &SCREENBLOCK[28], 1024 * 4);
    REG_BG0VOFF = 0;
    state = INSTRUCT;
}

//instruction state
void instruct() {
    seed++;
    if (BUTTON_PRESSED(BUTTON_START)) {
        goToStart();
    }
}

// Sets up the game state
void goToGame() {
    loser = 0;
    winner = 0;

    DMANow(3, gameBgPal, PALETTE, 256);
    DMANow(3, gameBgTiles, &CHARBLOCK[0], gameBgTilesLen / 2);
    DMANow(3, gameBgMap, &SCREENBLOCK[28], 1024 * 4);

    DMANow(3, spriteSheetPal, SPRITEPALETTE, 256);
    DMANow(3, spriteSheetTiles, &CHARBLOCK[4], spriteSheetTilesLen / 2);
    hideSprites();

    state = GAME;
}

// Game state
void game() {

    updateGame();
    drawGame();

    // State transitions
    if (BUTTON_PRESSED(BUTTON_START)) {
        hideSprites();
        goToPause();
    } else if (loser) {
        goToLose();
    }  
}

// Sets up the pause state
void goToPause() {
    hideSprites();
    DMANow(3, shadowOAM, OAM, 512);
    DMANow(3, pauseBgPal, PALETTE, 256);
    DMANow(3,pauseBgTiles, &CHARBLOCK[0], pauseBgTilesLen / 2);
    DMANow(3, pauseBgMap, &SCREENBLOCK[28], 1024 * 4);
    REG_BG0VOFF = 0;
    state = PAUSE;
}

// Pause state
void pause() {
    // State transitions
    if (BUTTON_PRESSED(BUTTON_START))
        goToGame();
}

// Sets up the lose state
void goToLose() {

    DMANow(3, loseBgPal, PALETTE, 256);
    DMANow(3,loseBgTiles, &CHARBLOCK[0], loseBgTilesLen / 2);
    DMANow(3, loseBgMap, &SCREENBLOCK[28], 1024 * 4);
    hideSprites();
    DMANow(3, shadowOAM, OAM, 512);
    REG_BG0VOFF = 0;


    state = LOSE;
}

//Lose state
void lose() {

    // State transitions
    if (BUTTON_PRESSED(BUTTON_START))
        goToStart();
}
