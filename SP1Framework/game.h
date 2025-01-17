#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include <string>


extern CStopWatch g_swTimer;
extern bool g_bQuitGame;

// struct to store keyboard events
// a small subset of KEY_EVENT_RECORD
struct SKeyEvent
{
    bool keyDown;
    bool keyReleased;
};

// struct to store mouse events
// a small subset of MOUSE_EVENT_RECORD
struct SMouseEvent
{
    COORD mousePosition;
    DWORD buttonState;
    DWORD eventFlags;
};

// Enumeration to store the control keys that your game will have
enum EKEYS
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
    K_SPACE,
    K_RETURN,
    K_B,
    K_COUNT,
    K_Q,
    K_A,
    K_Z,
    K_X,
    K_F,
};

// Enumeration for the different screen states
enum EGAMESTATES
{
    S_SPLASHSCREEN,
    S_GAME,
    S_GAME1,
    S_COUNT,
    S_CHOSEN,
    S_LOSE,
    S_WIN,
};

// struct for the game character
struct SGameChar
{
    COORD m_cLocation;
    bool  m_bActive;
};
struct SGameMob
{
    COORD m_cLocation;
    bool m_bActive;
};

// struct for the game weapon (Jun Ying WIP)
struct SGameWeapon
{
    COORD m_cLocation;
};

struct SGameAttack
{
    COORD m_cLocation;
};

struct SGameMap {
    COORD m_cLocation;
    bool m_bActive;
};
void init_firstmap( void );      // initialize your variables, allocate memory, etc
void init_secondmap(void);

void getInput    ( void );      // get input from player
void update      ( double dt ); // update the game and the state of the game
void render      ( void );      // renders the current state of the game to the console
void shutdown    ( void );      // do clean up, free memory

void splashScreenWait();    // waits for time to pass in splash screen
void updateGame();          // gameplay logic
void moveCharacter();       // moves the character, collision detection, physics, etc
void moveMob();
void setCharlocation();     //sets character location
void getCharlocation();     //get character location
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 
void renderSplashScreen();  // renders the splash screen
void renderGame();          // renders the game stuff
void renderLose();      // renders lost screen
void MapDesign();
void renderWin();
void renderGame1();
void renderMap();       // renders the map to the buffer first
void MapDesign2();
void renderMap2();
void renderMobs();
void renderCharacter();     // renders the character into the buffer
void renderWeapons(); // renders the weapon (Jun Ying WIP)
void renderWeapons1();
void renderWeaponAttack(); // renders the weapon attack
void renderWeapon2Attack();
void mobcollide();          //mob contact with enemyf
void updateGame1();
void pickedWeapon(); //when player picks up weapon (Reagan)
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderHeartbeat();
void render30sTimer();
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void renderInputEvents();   // renders the status of input events
void teleChar();
void renderWText();
void endgame();                   // ends the game
void mobspawn();
void playerwin();
void setdifficulty();       // allows user to set difficulty
void mobmovementspeedselector(int);
void weapon2init(); // sets initial positions for 2nd weapon attack
void endscreen();
void startscreen();
void renderstart();
void cheat(); // for testing
void endtext();
void renderendtext();






// keyboard and mouse input event managers
void keyboardHandler(const KEY_EVENT_RECORD& keyboardEvent);  // define this function for the console to call when there are keyboard events
void mouseHandler(const MOUSE_EVENT_RECORD& mouseEvent);      // define this function for the console to call when there are mouse events

void gameplayKBHandler(const KEY_EVENT_RECORD& keyboardEvent);   // handles keyboard events for gameplay 
void gameplayMouseHandler(const MOUSE_EVENT_RECORD& mouseEvent); // handles mouse events for gameplay 


#endif // _GAME_H