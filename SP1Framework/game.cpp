// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>


using namespace std;
double  g_dElapsedTime;
double  g_dDeltaTime;
double g_dOldTime;
double g_dHeartBeat;
double g_d30Timer;
float movepace; // how many frames of movement for the mob
float movetimer; // how fast the mob moves each interval
SKeyEvent g_skKeyEvent[K_COUNT];
SMouseEvent g_mouseEvent;

// Game specific variables here

//game character (Reagan)
SGameChar   g_sChar;
SGameMob g_sMob;
SGameMob g_sMob1;
SGameMob g_sMob2;
SGameMob g_sMob3;
SGameMob g_sMob4;





//weapon struct (Jun Ying)
SGameWeapon g_sWeapon;
SGameWeapon g_sWeapon2;

SGameAttack g_sSmash; // g_sWeapon attack
SGameAttack g_sSmash2;
SGameAttack g_sSmash3;
SGameAttack g_sSmash4;
SGameAttack g_sSmash5;
SGameAttack g_sSmash6;
SGameAttack g_sSmash7;
SGameAttack g_sSmash8;

SGameAttack g_sSlash;
SGameAttack g_sSlash2;
SGameAttack g_sSlash3;

EGAMESTATES g_eGameState = S_SPLASHSCREEN; // initial state
SGameMap    g_sMap;
// Console object
Console g_Console(80, 25, "SP1 Framework");


//boolean to show weapon (Reagan)
    bool weaponExist = true;
    bool weapon2Exist = true;
//boolean to show whether player picked up weapon or not
    bool hasweapon = false;
    bool hasweapon2 = false;
    bool isattack = false;

    //boolean for mob existing
    bool mob_exists = true; // dummy mob will remove later
    bool mob1_exists = false;
    bool mob2_exists = false;
    bool mob3_exists = false;
    bool mob4_exists = false;
    bool char_exists = true;
    
    // check for most recent key input
    std::string recentmoveinput;
//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{

 


    // Set precision for floating point output
    g_dElapsedTime = 0.0;    

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

    g_sChar.m_cLocation.X = 1;
    g_sChar.m_cLocation.Y = 1;
    g_sChar.m_bActive = true;

    g_sMob2.m_cLocation.X = 30;
    g_sMob2.m_cLocation.Y = 30;
    g_sMob2.m_bActive = true;

    g_sMob1.m_cLocation.X = 20;
    g_sMob1.m_cLocation.Y = 20;
    g_sMob1.m_bActive = true;

    g_sMob.m_cLocation.X = 10;
    g_sMob.m_cLocation.Y = 10;
    g_sMob.m_bActive = true;

    g_sMob3.m_cLocation.X = 40;
    g_sMob3.m_cLocation.Y = 40;
    g_sMob3.m_bActive = true;

    g_sMob4.m_cLocation.X = 50;
    g_sMob4.m_cLocation.Y = 50;
    g_sMob4.m_bActive = true;


    //location for weapon
    g_sWeapon.m_cLocation.X = 5; // Jun Ying WIP (for now)
    g_sWeapon.m_cLocation.Y = 4;

    g_sWeapon2.m_cLocation.X = 14; // Jun Ying WIP (for now)
    g_sWeapon2.m_cLocation.Y = 15;

    // g_sWeapon's attack position init 
    g_sSmash.m_cLocation.X = g_sChar.m_cLocation.X + 1; // right
    g_sSmash.m_cLocation.Y = g_sChar.m_cLocation.Y;

    g_sSmash2.m_cLocation.X = g_sChar.m_cLocation.X + 1; // bottom right
    g_sSmash2.m_cLocation.Y = g_sChar.m_cLocation.Y + 1;

    g_sSmash3.m_cLocation.X = g_sChar.m_cLocation.X; // bottom
    g_sSmash3.m_cLocation.Y = g_sChar.m_cLocation.Y + 1;

    g_sSmash4.m_cLocation.X = g_sChar.m_cLocation.X - 1; // bottom left
    g_sSmash4.m_cLocation.Y = g_sChar.m_cLocation.Y + 1;

    g_sSmash5.m_cLocation.X = g_sChar.m_cLocation.X - 1; // left
    g_sSmash5.m_cLocation.Y = g_sChar.m_cLocation.Y;

    g_sSmash6.m_cLocation.X = g_sChar.m_cLocation.X - 1; // top left
    g_sSmash6.m_cLocation.Y = g_sChar.m_cLocation.Y - 1;

    g_sSmash7.m_cLocation.X = g_sChar.m_cLocation.X; // top
    g_sSmash7.m_cLocation.Y = g_sChar.m_cLocation.Y - 1;

    g_sSmash8.m_cLocation.X = g_sChar.m_cLocation.X + 1; // top right
    g_sSmash8.m_cLocation.Y = g_sChar.m_cLocation.Y - 1;

    //g_sWeapon's attack position init
    g_sSlash.m_cLocation.X = g_sChar.m_cLocation.X;
    g_sSlash.m_cLocation.Y = g_sChar.m_cLocation.Y;
    g_sSlash2.m_cLocation.X = g_sChar.m_cLocation.X;
    g_sSlash2.m_cLocation.Y = g_sChar.m_cLocation.Y;
    g_sSlash3.m_cLocation.X = g_sChar.m_cLocation.X;
    g_sSlash3.m_cLocation.Y = g_sChar.m_cLocation.Y;

    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");

    // remember to set your keyboard handler, so that your functions can be notified of input events
    g_Console.setKeyboardHandler(keyboardHandler);
    g_Console.setMouseHandler(mouseHandler);
}

void setmobmoveinterval(int interval)
{
    movetimer = interval;
}

void mobmovementspeedselector(int speeddifficulty)
{
    movepace = speeddifficulty;
}

void updateweaponattackpositions()
{
    g_sSmash.m_cLocation.X = g_sChar.m_cLocation.X + 1; // right
    g_sSmash.m_cLocation.Y = g_sChar.m_cLocation.Y;

    g_sSmash2.m_cLocation.X = g_sChar.m_cLocation.X + 1; // bottom right
    g_sSmash2.m_cLocation.Y = g_sChar.m_cLocation.Y + 1;

    g_sSmash3.m_cLocation.X = g_sChar.m_cLocation.X; // bottom
    g_sSmash3.m_cLocation.Y = g_sChar.m_cLocation.Y + 1;

    g_sSmash4.m_cLocation.X = g_sChar.m_cLocation.X - 1; // bottom left
    g_sSmash4.m_cLocation.Y = g_sChar.m_cLocation.Y + 1;

    g_sSmash5.m_cLocation.X = g_sChar.m_cLocation.X - 1; // left
    g_sSmash5.m_cLocation.Y = g_sChar.m_cLocation.Y;

    g_sSmash6.m_cLocation.X = g_sChar.m_cLocation.X - 1; // top left
    g_sSmash6.m_cLocation.Y = g_sChar.m_cLocation.Y - 1;

    g_sSmash7.m_cLocation.X = g_sChar.m_cLocation.X; // top
    g_sSmash7.m_cLocation.Y = g_sChar.m_cLocation.Y - 1;

    g_sSmash8.m_cLocation.X = g_sChar.m_cLocation.X + 1; // top right
    g_sSmash8.m_cLocation.Y = g_sChar.m_cLocation.Y - 1;
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Get all the console input events
//            This function sets up the keyboard and mouse input from the console.
//            We will need to reset all the keyboard status, because no events will be sent if no keys are pressed.
//
//            Remember to set the handlers for keyboard and mouse events.
//            The function prototype of the handler is a function that takes in a const reference to the event struct
//            and returns nothing. 
//            void pfKeyboardHandler(const KEY_EVENT_RECORD&);
//            void pfMouseHandlerconst MOUSE_EVENT_RECORD&);
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput( void )
{
    // resets all the keyboard events
    memset(g_skKeyEvent, 0, K_COUNT * sizeof(*g_skKeyEvent));
    // then call the console to detect input from user
    g_Console.readConsoleInput();    
}

//--------------------------------------------------------------
// Purpose  : This is the handler for the keyboard input. Whenever there is a keyboard event, this function will be called.
//            Ideally, you should pass the key event to a specific function to handle the event.
//            This is because in some states, some keys would be disabled. Hence, to reduce your code complexity, 
//            it would be wise to split your keyboard input handlers separately.
//            
//            The KEY_EVENT_RECORD struct has more attributes that you can use, if you are adventurous enough.
//
//            In this case, we are not handling any keyboard event in the Splashscreen state
//            
// Input    : const KEY_EVENT_RECORD& keyboardEvent - reference to a key event struct
// Output   : void
//--------------------------------------------------------------
void keyboardHandler(const KEY_EVENT_RECORD& keyboardEvent)
{    
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: // don't handle anything for the splash screen
        break;
    case S_GAME: gameplayKBHandler(keyboardEvent); // handle gameplay keyboard event 
        break;
    }
}
std::vector<std::vector<std::string>>mapvector;
//--------------------------------------------------------------
// Purpose  : This is the handler for the mouse input. Whenever there is a mouse event, this function will be called.
//            Ideally, you should pass the key event to a specific function to handle the event.
//            This is because in some states, some keys would be disabled. Hence, to reduce your code complexity, 
//            it would be wise to split your keyboard input handlers separately.
//            
//            For the mouse event, if the mouse is not moved, no event will be sent, hence you should not reset the mouse status.
//            However, if the mouse goes out of the window, you would not be able to know either. 
//
//            The MOUSE_EVENT_RECORD struct has more attributes that you can use, if you are adventurous enough.
//
//            In this case, we are not handling any mouse event in the Splashscreen state
//            
// Input    : const MOUSE_EVENT_RECORD& mouseEvent - reference to a mouse event struct
// Output   : void
//--------------------------------------------------------------
void mouseHandler(const MOUSE_EVENT_RECORD& mouseEvent)
{    
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: gameplayMouseHandler(mouseEvent);// don't handle anything for the splash screen
        break;
    case S_GAME: gameplayMouseHandler(mouseEvent); // handle gameplay mouse event
        break;
    }
}

//--------------------------------------------------------------
// Purpose  : This is the keyboard handler in the game state. Whenever there is a keyboard event in the game state, this function will be called.
//            
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : const KEY_EVENT_RECORD& keyboardEvent
// Output   : void
//--------------------------------------------------------------
void gameplayKBHandler(const KEY_EVENT_RECORD& keyboardEvent)
{
    // here, we map the key to our enums
    EKEYS key = K_COUNT;
    switch (keyboardEvent.wVirtualKeyCode)
    {
    case VK_UP: key = K_UP; break;
    case VK_DOWN: key = K_DOWN; break;
    case VK_LEFT: key = K_LEFT; break; 
    case VK_RIGHT: key = K_RIGHT; break; 
    case VK_SPACE: key = K_SPACE; break;
    case VK_ESCAPE: key = K_ESCAPE; break; 
    case 0x42: key = K_B; break;
    }
    // a key pressed event would be one with bKeyDown == true
    // a key released event would be one with bKeyDown == false
    // if no key is pressed, no event would be fired.
    // so we are tracking if a key is either pressed, or released
    if (key != K_COUNT)
    {
        g_skKeyEvent[key].keyDown = keyboardEvent.bKeyDown;
        g_skKeyEvent[key].keyReleased = !keyboardEvent.bKeyDown;
    }    
}

//--------------------------------------------------------------
// Purpose  : This is the mouse handler in the game state. Whenever there is a mouse event in the game state, this function will be called.
//            
//            If mouse clicks are detected, the corresponding bit for that mouse button will be set.
//            mouse wheel, 
//            
// Input    : const KEY_EVENT_RECORD& keyboardEvent
// Output   : void
//--------------------------------------------------------------
void gameplayMouseHandler(const MOUSE_EVENT_RECORD& mouseEvent)
{
    if (mouseEvent.dwEventFlags & MOUSE_MOVED) // update the mouse position if there are no events
    {
        g_mouseEvent.mousePosition = mouseEvent.dwMousePosition;
    }
    g_mouseEvent.buttonState = mouseEvent.dwButtonState;
    g_mouseEvent.eventFlags = mouseEvent.dwEventFlags;
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------

void update(double dt)
{
    setmobmoveinterval(2.0); // the interval for each movement here (Jun Ying)
    mobmovementspeedselector(0.02); // how many frames of the mob's movement speed here (Jun Ying)
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;
    g_dHeartBeat = fmod(g_dElapsedTime, 2.0); // 2 second timer for mob movement
    g_d30Timer = fmod(g_dElapsedTime, 30.0); // 30 second timer here for david (Jun Ying)
    mobmovementspeedselector(0.02); // the difficulty of the mob's movement speed here (Jun Ying)
    switch (g_eGameState)
    {
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;
        case S_GAME: updateGame(); // gameplay logic when we are in the game
            break;
    }
}


void splashScreenWait()    // waits for time to pass in splash screen
{//if mode seleceted == true g_eGamestate
    if (g_dElapsedTime > 3) // wait for 3 seconds to switch to game mode, else do nothing
        g_eGameState = S_GAME;
}

void updateGame()       // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.


    moveMob();

    pickedWeapon(); //when player picks up weapon

}


void processUserInput()
{
    // quits the game if player hits the escape key
    if (g_skKeyEvent[K_ESCAPE].keyReleased)
        g_bQuitGame = true;    
}

//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: renderSplashScreen();
        break;
    case S_GAME: renderGame();
        break;
    }
    renderFramerate();      // renders debug information, frame rate, elapsed time, etc
    renderHeartbeat();
    renderInputEvents();    // renders status of input events
    renderToScreen();    // dump the contents of the buffer to the screen, one frame worth of game
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(160);
}

void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}

void renderSplashScreen()  // renders the splash screen difficulties UI for the player
{
    COORD c;
    std::ostringstream ss;
    ss << "Select Difficulty";
    c.X = 18;
    c.Y = 4;
    g_Console.writeToBuffer(c, ss.str());
    ss.str("");
    ss << "Easy Mode";
    c.X = 6;
    c.Y = 7;
    g_Console.writeToBuffer(c, ss.str());
    ss.str("");
    ss << "Normal Mode";
    c.X = 8;
    c.Y = 9;
    g_Console.writeToBuffer(c, ss.str());
    ss.str("");
    ss << "Hard Mode";
    c.X = 10;
    c.Y = 11;
    g_Console.writeToBuffer(c, ss.str());
    ss.str("");
    ss << "Extreme Mode";
    c.X = 13;
    c.Y = 13;
    g_Console.writeToBuffer(c, ss.str());
    }
//mouse clicker



void renderGame()
{
    MapDesign();
    renderMap();        // renders the map to the buffer first
    renderCharacter(); // renders the character into the buffer
    renderMobs(); //renders mob
    renderWeapons(); // render weapon
    renderWeaponAttack();
    renderWeapon2Attack();
    renderWText();
    mobcollide();
    setdifficulty();
    
}

int mapWidth = 50;
int mapHeight = 24;
//std::vector<char> mapArray;

char mapArray[] = { '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
'#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#','#',' ',' ',' ',' ',' ','#',
'#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
'#',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ','#','#','#','#',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ','#',' ','#','#','#','#',' ',' ',' ',' ',' ','#',
'#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#',' ','#','#',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ','#',' ','#','#',' ',' ',' ',' ',' ',' ',' ','#',
'#',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ','#',' ','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ',' ',' ',' ',' ','#',' ','#',' ','#','#','#','#','#','#','#','#','#','#',
'#',' ','#','#','#','#','#',' ','#','#','#','#','#',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',
'#',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ',' ','#','#','#','#','#','#',' ','#',' ','#','#','#','#',' ','#',' ','#',' ',' ',' ',' ','#',' ','#',' ','#','#','#','#','#','#','#',' ','#','#',
'#',' ','#','#',' ','#','#',' ','#','#','#','#','#','#',' ','#',' ',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ',' ','#',' ','#',' ',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ',' ',' ',' ','#',' ','#',
'#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ','#',' ','#',' ','#','#','#','#',' ','#',' ','#',' ',' ',' ',' ','#',' ','#',' ',' ',' ',' ','#',' ',' ','#','#','#','#','#','#','#','#','#','#','#',
'#',' ','#',' ','#',' ','#',' ','#','#','#','#',' ','#',' ','#',' ','#',' ',' ','#',' ','#',' ','#',' ',' ',' ','#',' ',' ','#',' ',' ',' ',' ','#','#',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
'#','#','#',' ',' ',' ','#',' ','#',' ',' ','#',' ','#',' ',' ',' ',' ','#',' ','#',' ','#','#','#',' ',' ',' ','#',' ','#','#','#','#','#','#','#',' ',' ','#',' ','#','#','#','#','#','#','#','#','#',
'#',' ','#',' ','#',' ','#',' ','#','#',' ','#',' ','#',' ','#','#','#','#','#','#',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#','#',' ','#','#',' ','#',' ',' ',' ',' ',' ','#',' ','#',
'#',' ','#',' ','#',' ','#',' ',' ',' ','#','#',' ','#','#','#','#',' ',' ',' ',' ',' ','#',' ',' ',' ',' ','#','#','#','#','#','#','#',' ','#','#',' ',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ','#',
'#',' ','#',' ','#',' ','#','#','#',' ','#','#',' ',' ',' ','#','#',' ','#','#','#','#','#',' ',' ',' ',' ','#',' ',' ',' ',' ',' ','#',' ','#','#',' ','#','#',' ','#',' ',' ',' ',' ',' ','#',' ','#',
'#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#','#',' ','#','#',' ','#',' ',' ',' ','#',' ',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ','#','#',' ','#','#',' ','#',' ',' ',' ',' ',' ','#',' ','#',
'#',' ',' ','#','#',' ','#',' ','#',' ','#',' ',' ','#',' ',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ','#',' ','#','#','#','#','#',' ','#','#',' ','#','#',' ','#','#','#','#','#','#','#',' ','#',
'#',' ',' ',' ','#',' ','#',' ','#',' ','#',' ',' ','#','#',' ','#','#','#','#','#',' ','#','#','#','#','#','#',' ',' ',' ',' ',' ','#',' ','#','#',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
'#',' ',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#','#',' ','#','#','#','#',' ','#',
'#',' ',' ',' ','#','#','#','#','#','#','#',' ',' ',' ','#',' ','#','#','#','#','#',' ','#','#','#',' ','#',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ','#','#',
'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ','#',' ','#',' ',' ','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ','#','#',
'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ','#','#','#','#','#','#','#',' ','#',' ','#',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#',
'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'
}; 

void MapDesign()
{
    std::ifstream maps;
    maps.open("MapDesign1.txt", std::ifstream::in);
    //int level=1;
    //switch (level)
    //{
    //case 1: maps = std::ifstream("MapDesign1.txt");
    //    break;

    //}
    // Opening may fail, always check.
  //  if (!maps) {
    //    exit(1);
    //}
    int offset = 0;
    std::string row;
    while (std::getline(maps, row))
    {
        std::stringstream rowStream(row);
        std::string(col);
        std::vector<std::string>rowvector;
        while (std::getline(rowStream, col, ',')) 
        {
            mapArray[offset++] = static_cast<char>(stoi(col));
            //rowvector.push_back(col);
        }
        //mapvector.push_back(rowvector);
    }
    maps.close();
}
void renderMap()
{

    // Set up sample colours, and output shadings
    /*const WORD colors[] = {
        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    };
    */
    COORD c;

    WORD Colour= 3;
    for (int j = 0; j < mapHeight; j++) {
        for (int i = 0; i < mapWidth; i++)
        {
            c.X = i;
            c.Y = j;
            //switch(mapArray[j * mapWidth + i])
            //{
                //case 1: //render '#'
            //}
            g_Console.writeToBuffer(c, mapArray[j * mapWidth + i], Colour);
        }  
    }
} 



void moveCharacter()
{    
    char find_string = '#';
    //124
    // Updating the location of the character based on the key release
    // providing a beep sound whenver we shift the character

    if (g_skKeyEvent[K_UP].keyReleased && mapArray[(g_sChar.m_cLocation.Y - 1)* mapWidth + g_sChar.m_cLocation.X] != '#' )
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y--;       
    }
    if (g_skKeyEvent[K_LEFT].keyReleased && mapArray[g_sChar.m_cLocation.Y * mapWidth + (g_sChar.m_cLocation.X - 1)] != '#')
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X--;        
    }
    if (g_skKeyEvent[K_DOWN].keyReleased && mapArray[(g_sChar.m_cLocation.Y + 1) * mapWidth + g_sChar.m_cLocation.X] != '#')
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y++;        
    }
    if (g_skKeyEvent[K_RIGHT].keyReleased && mapArray[g_sChar.m_cLocation.Y * mapWidth + (g_sChar.m_cLocation.X + 1)] != '#')
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X++;        
    }
    
}

bool easy_mode = true;
bool hard_mode = false;

void moveMob()
{
    if (hard_mode == true)
    {
        easy_mode = false;
        if (g_sChar.m_cLocation.Y > g_sMob.m_cLocation.Y && g_dHeartBeat <= 0.02 && g_sMob.m_cLocation.Y + 1 <= 1)//0.02 hardcoded for now, change to difficulty
        {
            g_sMob.m_cLocation.Y++;
        }
        if (g_sChar.m_cLocation.Y < g_sMob.m_cLocation.Y && g_dHeartBeat <= 0.02 && g_sMob.m_cLocation.Y - 1 <= 50)
        {
            g_sMob.m_cLocation.Y--;
        }
        if (g_sChar.m_cLocation.X > g_sMob.m_cLocation.X && g_dHeartBeat <= 0.02 && g_sMob.m_cLocation.X + 1 <= 50)
        {
            g_sMob.m_cLocation.X++;
        }
        if (g_sChar.m_cLocation.X < g_sMob.m_cLocation.X && g_dHeartBeat <= 0.02 && g_sMob.m_cLocation.X - 1 <= 1)
        {
            g_sMob.m_cLocation.X--;
        }
    }
    if (easy_mode == true)
    {
        hard_mode = false;
        if (g_sChar.m_cLocation.Y > g_sMob.m_cLocation.Y && g_dHeartBeat <= 0.02 && mapArray[(g_sMob.m_cLocation.Y + 1) * mapWidth + g_sMob.m_cLocation.X] != '#')//0.02 hardcoded for now, change to difficulty
        {
            g_sMob.m_cLocation.Y++;
        }
        if (g_sChar.m_cLocation.Y < g_sMob.m_cLocation.Y && g_dHeartBeat <= 0.02 && mapArray[(g_sMob.m_cLocation.Y - 1) * mapWidth + g_sMob.m_cLocation.X] != '#')
        {
            g_sMob.m_cLocation.Y--;
        }
        if (g_sChar.m_cLocation.X > g_sMob.m_cLocation.X && g_dHeartBeat <= 0.02 && mapArray[g_sMob.m_cLocation.Y * mapWidth + (g_sMob.m_cLocation.X + 1)] != '#')
        {
            g_sMob.m_cLocation.X++;
        }
        if (g_sChar.m_cLocation.X < g_sMob.m_cLocation.X && g_dHeartBeat <= 0.02 && mapArray[g_sMob.m_cLocation.Y * mapWidth + (g_sMob.m_cLocation.X - 1)] != '#')
        {
            g_sMob.m_cLocation.X--;
        }
    }
}
           







void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0C;
    if (g_sChar.m_bActive)
    {
        charColor = 0x0A;
    }
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)1, charColor);

}

void renderMobs()
{
    WORD mobColor = 252;
    if (g_sMob.m_bActive)
    {
        mobColor = 0x0C;
    }
    
    if (mob_exists == true)
    {
        g_Console.writeToBuffer(g_sMob.m_cLocation, (char)1, mobColor);
    }
    
    if (mob1_exists == true)
    {
        g_Console.writeToBuffer(g_sMob1.m_cLocation, (char)1, mobColor);
    }

    if (mob2_exists == true)
    {
        g_Console.writeToBuffer(g_sMob2.m_cLocation, (char)1, mobColor);
    }

    if (mob3_exists == true)
    {
        g_Console.writeToBuffer(g_sMob3.m_cLocation, (char)1, mobColor);
    }

    if (mob4_exists == true)
    {
        g_Console.writeToBuffer(g_sMob4.m_cLocation, (char)1, mobColor);
    }
}
void setdifficulty()//to be changed with splash screen
{//easy, normal,hard, EXTREME
   
    }






void renderWeapons() // Jun Ying WIP
{
    // Colour for the weapon symbol
    WORD weaponColor = 240;
    WORD weapon2Color = 239;
    
    if (weaponExist == true)
    {
        g_Console.writeToBuffer(g_sWeapon.m_cLocation, (char)206, weaponColor);
    }
    if (weapon2Exist == true)
    {
        g_Console.writeToBuffer(g_sWeapon2.m_cLocation, (char)237, weapon2Color);
    }
}

void weaponattacksystem()
{
    WORD attackColor = 255;
    g_Console.writeToBuffer(g_sSmash.m_cLocation, (char)254, attackColor);
    g_Console.writeToBuffer(g_sSmash2.m_cLocation, (char)254, attackColor);
    g_Console.writeToBuffer(g_sSmash3.m_cLocation, (char)254, attackColor);
    g_Console.writeToBuffer(g_sSmash4.m_cLocation, (char)254, attackColor);
    g_Console.writeToBuffer(g_sSmash5.m_cLocation, (char)254, attackColor);
    g_Console.writeToBuffer(g_sSmash6.m_cLocation, (char)254, attackColor);
    g_Console.writeToBuffer(g_sSmash7.m_cLocation, (char)254, attackColor);
    g_Console.writeToBuffer(g_sSmash8.m_cLocation, (char)254, attackColor);

    if (g_sSmash.m_cLocation.X == g_sMob.m_cLocation.X &&
        g_sSmash.m_cLocation.Y == g_sMob.m_cLocation.Y ||
        g_sSmash2.m_cLocation.X == g_sMob.m_cLocation.X &&
        g_sSmash2.m_cLocation.Y == g_sMob.m_cLocation.Y ||
        g_sSmash3.m_cLocation.X == g_sMob.m_cLocation.X &&
        g_sSmash3.m_cLocation.Y == g_sMob.m_cLocation.Y ||
        g_sSmash4.m_cLocation.X == g_sMob.m_cLocation.X &&
        g_sSmash4.m_cLocation.Y == g_sMob.m_cLocation.Y ||
        g_sSmash5.m_cLocation.X == g_sMob.m_cLocation.X &&
        g_sSmash5.m_cLocation.Y == g_sMob.m_cLocation.Y ||
        g_sSmash6.m_cLocation.X == g_sMob.m_cLocation.X &&
        g_sSmash6.m_cLocation.Y == g_sMob.m_cLocation.Y ||
        g_sSmash7.m_cLocation.X == g_sMob.m_cLocation.X &&
        g_sSmash7.m_cLocation.Y == g_sMob.m_cLocation.Y ||
        g_sSmash8.m_cLocation.X == g_sMob.m_cLocation.X &&
        g_sSmash8.m_cLocation.Y == g_sMob.m_cLocation.Y
        )
    {
        mob_exists = false;
    }

    if (g_sSmash.m_cLocation.X == g_sMob1.m_cLocation.X &&
        g_sSmash.m_cLocation.Y == g_sMob1.m_cLocation.Y ||
        g_sSmash2.m_cLocation.X == g_sMob1.m_cLocation.X &&
        g_sSmash2.m_cLocation.Y == g_sMob1.m_cLocation.Y ||
        g_sSmash3.m_cLocation.X == g_sMob1.m_cLocation.X &&
        g_sSmash3.m_cLocation.Y == g_sMob1.m_cLocation.Y ||
        g_sSmash4.m_cLocation.X == g_sMob1.m_cLocation.X &&
        g_sSmash4.m_cLocation.Y == g_sMob1.m_cLocation.Y ||
        g_sSmash5.m_cLocation.X == g_sMob1.m_cLocation.X &&
        g_sSmash5.m_cLocation.Y == g_sMob1.m_cLocation.Y ||
        g_sSmash6.m_cLocation.X == g_sMob1.m_cLocation.X &&
        g_sSmash6.m_cLocation.Y == g_sMob1.m_cLocation.Y ||
        g_sSmash7.m_cLocation.X == g_sMob1.m_cLocation.X &&
        g_sSmash7.m_cLocation.Y == g_sMob1.m_cLocation.Y ||
        g_sSmash8.m_cLocation.X == g_sMob1.m_cLocation.X &&
        g_sSmash8.m_cLocation.Y == g_sMob1.m_cLocation.Y
        )
    {
        mob1_exists = false;
    }

    if (g_sSmash.m_cLocation.X == g_sMob2.m_cLocation.X &&
        g_sSmash.m_cLocation.Y == g_sMob2.m_cLocation.Y ||
        g_sSmash2.m_cLocation.X == g_sMob2.m_cLocation.X &&
        g_sSmash2.m_cLocation.Y == g_sMob2.m_cLocation.Y ||
        g_sSmash3.m_cLocation.X == g_sMob2.m_cLocation.X &&
        g_sSmash3.m_cLocation.Y == g_sMob2.m_cLocation.Y ||
        g_sSmash4.m_cLocation.X == g_sMob2.m_cLocation.X &&
        g_sSmash4.m_cLocation.Y == g_sMob2.m_cLocation.Y ||
        g_sSmash5.m_cLocation.X == g_sMob2.m_cLocation.X &&
        g_sSmash5.m_cLocation.Y == g_sMob2.m_cLocation.Y ||
        g_sSmash6.m_cLocation.X == g_sMob2.m_cLocation.X &&
        g_sSmash6.m_cLocation.Y == g_sMob2.m_cLocation.Y ||
        g_sSmash7.m_cLocation.X == g_sMob2.m_cLocation.X &&
        g_sSmash7.m_cLocation.Y == g_sMob2.m_cLocation.Y ||
        g_sSmash8.m_cLocation.X == g_sMob2.m_cLocation.X &&
        g_sSmash8.m_cLocation.Y == g_sMob2.m_cLocation.Y
        )
    {
        mob2_exists = false;
    }

    if (g_sSmash.m_cLocation.X == g_sMob3.m_cLocation.X &&
        g_sSmash.m_cLocation.Y == g_sMob3.m_cLocation.Y ||
        g_sSmash2.m_cLocation.X == g_sMob3.m_cLocation.X &&
        g_sSmash2.m_cLocation.Y == g_sMob3.m_cLocation.Y ||
        g_sSmash3.m_cLocation.X == g_sMob3.m_cLocation.X &&
        g_sSmash3.m_cLocation.Y == g_sMob3.m_cLocation.Y ||
        g_sSmash4.m_cLocation.X == g_sMob3.m_cLocation.X &&
        g_sSmash4.m_cLocation.Y == g_sMob3.m_cLocation.Y ||
        g_sSmash5.m_cLocation.X == g_sMob3.m_cLocation.X &&
        g_sSmash5.m_cLocation.Y == g_sMob3.m_cLocation.Y ||
        g_sSmash6.m_cLocation.X == g_sMob3.m_cLocation.X &&
        g_sSmash6.m_cLocation.Y == g_sMob3.m_cLocation.Y ||
        g_sSmash7.m_cLocation.X == g_sMob3.m_cLocation.X &&
        g_sSmash7.m_cLocation.Y == g_sMob3.m_cLocation.Y ||
        g_sSmash8.m_cLocation.X == g_sMob3.m_cLocation.X &&
        g_sSmash8.m_cLocation.Y == g_sMob3.m_cLocation.Y
        )
    {
        mob3_exists = false;
    }

    if (g_sSmash.m_cLocation.X == g_sMob4.m_cLocation.X &&
        g_sSmash.m_cLocation.Y == g_sMob4.m_cLocation.Y ||
        g_sSmash2.m_cLocation.X == g_sMob4.m_cLocation.X &&
        g_sSmash2.m_cLocation.Y == g_sMob4.m_cLocation.Y ||
        g_sSmash3.m_cLocation.X == g_sMob4.m_cLocation.X &&
        g_sSmash3.m_cLocation.Y == g_sMob4.m_cLocation.Y ||
        g_sSmash4.m_cLocation.X == g_sMob4.m_cLocation.X &&
        g_sSmash4.m_cLocation.Y == g_sMob4.m_cLocation.Y ||
        g_sSmash5.m_cLocation.X == g_sMob4.m_cLocation.X &&
        g_sSmash5.m_cLocation.Y == g_sMob4.m_cLocation.Y ||
        g_sSmash6.m_cLocation.X == g_sMob4.m_cLocation.X &&
        g_sSmash6.m_cLocation.Y == g_sMob4.m_cLocation.Y ||
        g_sSmash7.m_cLocation.X == g_sMob4.m_cLocation.X &&
        g_sSmash7.m_cLocation.Y == g_sMob4.m_cLocation.Y ||
        g_sSmash8.m_cLocation.X == g_sMob4.m_cLocation.X &&
        g_sSmash8.m_cLocation.Y == g_sMob4.m_cLocation.Y
        )
    {
        mob4_exists = false;
    }
}

void renderWeaponAttack()
{
    updateweaponattackpositions();
    if (isattack == false && recentmoveinput == "UP" || recentmoveinput == "LEFT" || recentmoveinput == "RIGHT" || recentmoveinput == "DOWN")
    {
        isattack = true;

        if (hasweapon == true && weaponExist == false && g_skKeyEvent[K_SPACE].keyReleased)
        {
            // the 360 aoe attack if player obtains the epic weapon and checks if there are mobs within range of weapon attack
            weaponattacksystem();

        }

        isattack = false;
        
    }


}


void weapon2attacksystem()
{
    WORD attackColor = 10;
    if (hasweapon2 == true && weapon2Exist == false && g_skKeyEvent[K_B].keyReleased)
    {
        // sword attack
        if (recentmoveinput == "UP")// up
        {

            g_sSlash.m_cLocation.X = g_sChar.m_cLocation.X;
            g_sSlash.m_cLocation.Y = g_sChar.m_cLocation.Y - 1;
            g_Console.writeToBuffer(g_sSlash.m_cLocation, (char)219, attackColor);
            g_sSlash2.m_cLocation.X = g_sChar.m_cLocation.X;
            g_sSlash2.m_cLocation.Y = g_sChar.m_cLocation.Y - 2;
            g_Console.writeToBuffer(g_sSlash2.m_cLocation, (char)219, attackColor);
            g_sSlash3.m_cLocation.X = g_sChar.m_cLocation.X;
            g_sSlash3.m_cLocation.Y = g_sChar.m_cLocation.Y - 3;
            g_Console.writeToBuffer(g_sSlash3.m_cLocation, (char)219, attackColor);

        }
        else if (recentmoveinput == "LEFT")//left
        {
            g_sSlash.m_cLocation.X = g_sChar.m_cLocation.X - 1;
            g_sSlash.m_cLocation.Y = g_sChar.m_cLocation.Y;
            g_Console.writeToBuffer(g_sSlash.m_cLocation, (char)219, attackColor);
            g_sSlash2.m_cLocation.X = g_sChar.m_cLocation.X - 2;
            g_sSlash2.m_cLocation.Y = g_sChar.m_cLocation.Y;
            g_Console.writeToBuffer(g_sSlash2.m_cLocation, (char)219, attackColor);
            g_sSlash3.m_cLocation.X = g_sChar.m_cLocation.X - 3;
            g_sSlash3.m_cLocation.Y = g_sChar.m_cLocation.Y;
            g_Console.writeToBuffer(g_sSlash3.m_cLocation, (char)219, attackColor);
        }
        else if (recentmoveinput == "RIGHT")//right
        {
            g_sSlash.m_cLocation.X = g_sChar.m_cLocation.X + 1;
            g_sSlash.m_cLocation.Y = g_sChar.m_cLocation.Y;
            g_Console.writeToBuffer(g_sSlash.m_cLocation, (char)219, attackColor);
            g_sSlash2.m_cLocation.X = g_sChar.m_cLocation.X + 2;
            g_sSlash2.m_cLocation.Y = g_sChar.m_cLocation.Y;
            g_Console.writeToBuffer(g_sSlash2.m_cLocation, (char)219, attackColor);
            g_sSlash3.m_cLocation.X = g_sChar.m_cLocation.X + 3;
            g_sSlash3.m_cLocation.Y = g_sChar.m_cLocation.Y;
            g_Console.writeToBuffer(g_sSlash3.m_cLocation, (char)219, attackColor);

        }
        else if (recentmoveinput == "DOWN")//down
        {
            g_sSlash.m_cLocation.X = g_sChar.m_cLocation.X;
            g_sSlash.m_cLocation.Y = g_sChar.m_cLocation.Y + 1;
            g_Console.writeToBuffer(g_sSlash.m_cLocation, (char)219, attackColor);
            g_sSlash2.m_cLocation.X = g_sChar.m_cLocation.X;
            g_sSlash2.m_cLocation.Y = g_sChar.m_cLocation.Y + 2;
            g_Console.writeToBuffer(g_sSlash2.m_cLocation, (char)219, attackColor);
            g_sSlash3.m_cLocation.X = g_sChar.m_cLocation.X;
            g_sSlash3.m_cLocation.Y = g_sChar.m_cLocation.Y + 3;
            g_Console.writeToBuffer(g_sSlash3.m_cLocation, (char)219, attackColor);
        }

        //if there are mobs within range of weapon attack
        if (g_sSlash.m_cLocation.X == g_sMob.m_cLocation.X &&
            g_sSlash.m_cLocation.Y == g_sMob.m_cLocation.Y ||
            g_sSlash2.m_cLocation.X == g_sMob.m_cLocation.X &&
            g_sSlash2.m_cLocation.Y == g_sMob.m_cLocation.Y ||
            g_sSlash3.m_cLocation.X == g_sMob.m_cLocation.X &&
            g_sSlash3.m_cLocation.Y == g_sMob.m_cLocation.Y
            )
        {
            mob_exists = false;
        }
        if (g_sSlash.m_cLocation.X == g_sMob1.m_cLocation.X &&
            g_sSlash.m_cLocation.Y == g_sMob1.m_cLocation.Y ||
            g_sSlash2.m_cLocation.X == g_sMob1.m_cLocation.X &&
            g_sSlash2.m_cLocation.Y == g_sMob1.m_cLocation.Y ||
            g_sSlash3.m_cLocation.X == g_sMob1.m_cLocation.X &&
            g_sSlash3.m_cLocation.Y == g_sMob1.m_cLocation.Y 
            )
        {
            mob1_exists = false;
        }
        if (g_sSlash.m_cLocation.X == g_sMob2.m_cLocation.X &&
            g_sSlash.m_cLocation.Y == g_sMob2.m_cLocation.Y ||
            g_sSlash2.m_cLocation.X == g_sMob2.m_cLocation.X &&
            g_sSlash2.m_cLocation.Y == g_sMob2.m_cLocation.Y ||
            g_sSlash3.m_cLocation.X == g_sMob2.m_cLocation.X &&
            g_sSlash3.m_cLocation.Y == g_sMob2.m_cLocation.Y 
            )
        {
            mob2_exists = false;
        }
        if (g_sSlash.m_cLocation.X == g_sMob3.m_cLocation.X &&
            g_sSlash.m_cLocation.Y == g_sMob3.m_cLocation.Y ||
            g_sSlash2.m_cLocation.X == g_sMob3.m_cLocation.X &&
            g_sSlash2.m_cLocation.Y == g_sMob3.m_cLocation.Y ||
            g_sSlash3.m_cLocation.X == g_sMob3.m_cLocation.X &&
            g_sSlash3.m_cLocation.Y == g_sMob3.m_cLocation.Y
            )
        {
            mob3_exists = false;
        }
        if (g_sSlash.m_cLocation.X == g_sMob4.m_cLocation.X &&
            g_sSlash.m_cLocation.Y == g_sMob4.m_cLocation.Y ||
            g_sSlash2.m_cLocation.X == g_sMob4.m_cLocation.X &&
            g_sSlash2.m_cLocation.Y == g_sMob4.m_cLocation.Y ||
            g_sSlash3.m_cLocation.X == g_sMob4.m_cLocation.X &&
            g_sSlash3.m_cLocation.Y == g_sMob4.m_cLocation.Y
            )
        {
            mob4_exists = false;
        }
    }
}

void renderWeapon2Attack()
{
    if (isattack == false)
    {
        isattack = true;

        weapon2attacksystem();

        isattack = false;

    }


}
void mobcollide()//david WIP dection works tho
{
    if (mob_exists == true)
    {
        if (g_sMob.m_cLocation.X == g_sChar.m_cLocation.X
            && g_sMob.m_cLocation.Y == g_sChar.m_cLocation.Y
            )
        {
            char_exists == false;


            COORD c;
            std::ostringstream ss;
            ss << "You Lose!";
            c.X = 25;
            c.Y = 15;
            g_Console.writeToBuffer(c, ss.str());
            // adding end game and restart func
            //g_bQuitGame = true; // ends game




        }
    }
}


void pickedWeapon()
{
    //conditional statement when character and weapon are in the same coordinates (Reagan)
    if (g_sWeapon.m_cLocation.X == g_sChar.m_cLocation.X &&
        g_sWeapon.m_cLocation.Y == g_sChar.m_cLocation.Y && g_skKeyEvent[K_SPACE].keyDown)
    {
        weaponExist = false;
        hasweapon = true;
        
    }
    if (g_sWeapon2.m_cLocation.X == g_sChar.m_cLocation.X &&
        g_sWeapon2.m_cLocation.Y == g_sChar.m_cLocation.Y && g_skKeyEvent[K_SPACE].keyDown)
    {
        weapon2Exist = false;
        hasweapon2 = true;

    }


}
void renderWText()
{
    if (hasweapon == true)
    {
        COORD c;
        std::ostringstream ss;
        ss << "You picked up the cross!";
        c.X = 55;
        c.Y = 23;
        g_Console.writeToBuffer(c, ss.str());
    }
    if (hasweapon2 == true)
    {
        COORD c;
        std::ostringstream ss;
        ss << "You picked up the sword!";
        c.X = 55;
        c.Y = 20;
        g_Console.writeToBuffer(c, ss.str());
    }
}

void renderHeartbeat()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << "Heartbeat:" << g_dHeartBeat;
    c.X = g_Console.getConsoleSize().X - 15;
    c.Y = 2;
    g_Console.writeToBuffer(c, ss.str());
}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss <<"FPS:"<< 1.0 / g_dDeltaTime;
    c.X = g_Console.getConsoleSize().X - 12;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());

    // displays the elapsed time
    ss.str("");
    ss <<"Time:" <<g_dElapsedTime;
    c.X = 68;
    c.Y = 1;
    g_Console.writeToBuffer(c, ss.str());
}

    void mobspawn()
    { if (g_dElapsedTime > 10)
        {
        mob1_exists = true;
        }
    if (g_dElapsedTime > 30)
    {
       // mob1_exists = true;
    }
    if (g_dElapsedTime > 50)
    {
       // mob1_exists = true;
    }
    if (g_dElapsedTime > 70)
    {
      // mob1_exists = true;
    }

    }


// this is an example of how you would use the input events
void renderInputEvents()
{
    // keyboard events
    COORD startPos = {50, 2};
    std::ostringstream ss;
    std::string key;
    for (int i = 0; i < K_COUNT; ++i)
    {
        ss.str("");
        switch (i)
        {
        case K_UP: key = "UP";
            break;
        case K_DOWN: key = "DOWN";
            break;
        case K_LEFT: key = "LEFT";
            break;
        case K_RIGHT: key = "RIGHT";
            break;
        case K_SPACE: key = "SPACE";
            break;
        case K_B: key = "B";
            break;
        default: continue;
        }
        if (g_skKeyEvent[i].keyDown)
            ss << key << " pressed";
            
        else if (g_skKeyEvent[i].keyReleased)
        {
            ss << key << " released";
            recentmoveinput = key;
        }
        else
            ss << key << " not pressed";

        COORD c = { startPos.X, startPos.Y + i };
       // g_Console.writeToBuffer(c, ss.str(), 0x17);
    }



    // mouse events    
    ss.str("");
    ss << "Mouse position (" << g_mouseEvent.mousePosition.X << ", " << g_mouseEvent.mousePosition.Y << ")";
    g_Console.writeToBuffer(g_mouseEvent.mousePosition, ss.str(), 0x59);
    ss.str("");
    switch (g_mouseEvent.eventFlags)
    {
    case 0:
        if (g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            ss.str("Left Button Pressed");
            g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 1, ss.str(), 0x59);
        }
        else if (g_mouseEvent.buttonState == RIGHTMOST_BUTTON_PRESSED)
        {
            ss.str("Right Button Pressed");
            g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 2, ss.str(), 0x59);
        }
        else
        {
            ss.str("Some Button Pressed");
            g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 3, ss.str(), 0x59);
        }
        break;
    case DOUBLE_CLICK:
        ss.str("Double Clicked");
        g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 4, ss.str(), 0x59);
        break;        
    case MOUSE_WHEELED:
        if (g_mouseEvent.buttonState & 0xFF000000)
            ss.str("Mouse wheeled down");
        else
            ss.str("Mouse wheeled up");
        g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 5, ss.str(), 0x59);
        break;
    default:        
        break;
    }
    
}



