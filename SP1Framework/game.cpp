// This is the main file for the game logic and function
//im pushing this for shuan cuz he sucks and messed up 
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


//for spawning at random positions
#include <cstdlib>
#include <ctime>

using namespace std;
double  g_dElapsedTime;
double  g_dDeltaTime;
double g_dHeartBeat;
double g_d30Timer;




double g_dElapsedTime_2;



float movepace; // how many frames of movement for the mob
float movetimer; // how fast the mob moves each interval
SKeyEvent g_skKeyEvent[K_COUNT];
SMouseEvent g_mouseEvent;

// Game specific variables here

//game character (Reagan)
SGameChar g_sChar;
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

    //if mob is attacked (Reagan)
    bool mob_attacked = false; // dummy mob will remove later
    bool mob1_attacked = false;
    bool mob2_attacked = false;
    bool mob3_attacked = false;
    bool mob4_attacked = false;


    //if mob is attacked in second map (Reagan)
    bool mob_attacked_2 = false; // dummy mob will remove later
    bool mob1_attacked_2 = false;
    bool mob2_attacked_2 = false;
    bool mob3_attacked_2 = false;
    bool mob4_attacked_2= false;

    bool char_exists = true;
    
    bool cleared = false;
    bool pt1cleared = false;
    bool start_time = false;

    // check for most recent key input
    std::string recentmoveinput;
//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------

void setmobmoveinterval(int interval)
{
    movetimer = interval;
}

void mobmovementspeedselector(int speeddifficulty)
{
    movepace = speeddifficulty;
}

void updateweaponattackpositions() // function to constantly update 1st weapon's attack positions
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
    case S_SPLASHSCREEN: gameplayKBHandler(keyboardEvent);//handle anything for the splash screen
        break;
    case S_GAME: gameplayKBHandler(keyboardEvent); // handle gameplay keyboard event 
        break;
    case S_LOSE: gameplayKBHandler(keyboardEvent); // press enter to return to title screen
        break;
    case S_WIN: gameplayKBHandler(keyboardEvent);
        break;
    case S_GAME1: gameplayKBHandler(keyboardEvent);
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
    case S_LOSE: //dont handle
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
    case VK_RETURN:key = K_RETURN; break; //enter key
    case 0x42: key = K_B; break;
    case 0x41: key = K_A; break;
    case 0x51: key = K_Q; break;
    case 0x5A: key = K_Z; break;
    case 0x58: key = K_X; break;
    case 0x46: key = K_F; break;

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

bool after_cutscene = false;

void update(double dt)
{
    if (start_time == true )
    {
        
        // get the delta time
        g_dElapsedTime += dt;
        g_dDeltaTime = dt;
        g_dHeartBeat = fmod(g_dElapsedTime, movetimer); //timer for mob movement (changed to movetimer so just use setmobmoveinterval instead)
        //modifies game diff 
        g_d30Timer = fmod(g_dElapsedTime, 30.0); // 30 second timer here for david (Jun Ying)
        
    }

    if (cleared == true)
    {
        // get the delta time
        g_dElapsedTime_2 += dt;

    }

    //after cutscene, the game starts (Reagan)
    if (after_cutscene == true)
    {
        mobmovementspeedselector(0.02); // the difficulty of the mob's movement speed here (Jun Ying)
        g_dHeartBeat = fmod(g_dElapsedTime, movetimer); //timer for mob movement (changed to movetimer so just use setmobmoveinterval instead)
        mobmovementspeedselector(0.02); // how many frames of the mob's movement speed here (Jun Ying)
    }

    switch (g_eGameState)
    {
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;
        case S_GAME: updateGame(); // gameplay logic when we are in the game
            break;
        case S_GAME1: updateGame();
            break;
    }
}

bool modeselected = false;
void splashScreenWait()    // waits for time to pass in splash screen
{//if mode seleceted == true g_eGamestate
    
    setdifficulty();
    startscreen();

}



void updateGame()       // gameplay logic
{

    if (after_cutscene == true)
    {
         
        mobspawn();
       
        processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
        moveCharacter();    // moves the character, collision detection, physics, etc
        
        moveMob();
        pickedWeapon(); //when player picks up weapon
    }
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
    case S_LOSE: renderLose();
        break;
    case S_WIN: renderWin();//clear map1
        break;
    case S_GAME1:renderGame1();//map 2
        break;
    }
    renderFramerate();      // renders debug information, frame rate, elapsed time, etc
    //renderHeartbeat();
    //render30sTimer();
    renderInputEvents();    // renders status of input events
    renderToScreen();    // dump the contents of the buffer to the screen, one frame worth of game
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(120); // light grey
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
    ss.str("");
    ss << ".########..##.....##.##....##";
    c.X = 1;
    c.Y = 3;
    g_Console.writeToBuffer(c, ss.str());
    ss.str("");
    ss << ".##.....##.##.....##.###...##";
    c.X = 1;
    c.Y = 4;
    g_Console.writeToBuffer(c, ss.str());
    ss.str("");
    ss << ".##.....##.##.....##.####..##";
    c.X = 1;
    c.Y = 5;
    g_Console.writeToBuffer(c, ss.str());
    ss.str("");
    ss << ".########..##.....##.##.##.##";
    c.X = 1;
    c.Y = 6;
    g_Console.writeToBuffer(c, ss.str());
    ss.str("");
    ss << ".##...##...##.....##.##..####";
    c.X = 1;
    c.Y = 7;
    g_Console.writeToBuffer(c, ss.str());
    ss.str("");
    ss << ".##....##..##.....##.##...###";
    c.X = 1;
    c.Y = 8;
    g_Console.writeToBuffer(c, ss.str());
    ss.str("");
    ss << ".##.....##..#######..##....##";
    c.X = 1;
    c.Y = 9;
    g_Console.writeToBuffer(c, ss.str());
    ss.str("");

    ss << "Select Difficulty";
    c.X = 6;
    c.Y = 19;
    g_Console.writeToBuffer(c, ss.str());
    ss.str("");
    ss << "Press 'Q' for Easy Mode";
    c.X = 6;
    c.Y = 20;
    g_Console.writeToBuffer(c, ss.str());
    ss.str("");
    ss << "Press 'A' for Normal Mode";
    c.X = 6;
    c.Y = 21;
    g_Console.writeToBuffer(c, ss.str());
    ss.str("");
    ss << "Press 'Z' for Hard Mode";
    c.X = 6;
    c.Y = 22;
    g_Console.writeToBuffer(c, ss.str());
    startscreen();
    renderstart();
    
    }
//mouse clicker
void renderWin()
{
    endtext();
}




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
    startscreen();
    cheat();
    endgame();
}
void renderLose()
{
    mobcollide();//weird ass name gonna change it LOL
    


}

void endtext()
{
    COORD c;
    std::ostringstream ss;
    ss.str("");
    ss << ".##....##..#######..##.....##....##......##.####.##....##.####";
    c.X = 2;
    c.Y = 2;
    g_Console.writeToBuffer(c, ss.str());
    ss.str("");
    ss << "..##..##..##.....##.##.....##....##..##..##..##..###...##.####";
    c.X = 2;
    c.Y = 3;
    g_Console.writeToBuffer(c, ss.str());
    ss.str("");
    ss << "...####...##.....##.##.....##....##..##..##..##..####..##.####";
    c.X = 2;
    c.Y = 3;
    g_Console.writeToBuffer(c, ss.str());
    ss.str("");
    ss << "....##....##.....##.##.....##....##..##..##..##..##.##.##..##.";
    c.X = 2;
    c.Y = 4;
    g_Console.writeToBuffer(c, ss.str());
    ss.str("");
    ss << "....##....##.....##.##.....##....##..##..##..##..##..####.....";
    c.X = 2;
    c.Y = 5;
    g_Console.writeToBuffer(c, ss.str());
    ss.str("");
    ss << "....##....##.....##.##.....##....##..##..##..##..##...###.####";
    c.X = 2;
    c.Y = 6;
    g_Console.writeToBuffer(c, ss.str());
    ss.str("");
    ss << "....##.....#######...#######......###..###..####.##....##.####";
    c.X = 2;
    c.Y = 7;
    g_Console.writeToBuffer(c, ss.str());
    ss.str("");
    ss << " You have escaped... for now";
    c.X = 20;
    c.Y = 15;
    g_Console.writeToBuffer(c, ss.str());
   
}

void renderGame1()
{
    MapDesign2();
    renderMap2();        // renders the map to the buffer first
    renderCharacter(); // renders the character into the buffer
    renderMobs(); //renders mob
    renderWeapons(); // render weapon
    renderWeaponAttack();
    renderWeapon2Attack();
    renderWText();
    mobcollide();
    startscreen();
    cheat();
    playerwin();
}


int mapWidth = 50;
int mapHeight = 24;
std::vector<char>mapArray;
int startX = 12;
int startY = 2;
std::vector<char>startArray;



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
    if (!maps) {
        exit(1);
    }
    std::string row;
    while (std::getline(maps, row))
    {
        std::stringstream rowStream(row);
        std::string(col);
        std::vector<std::string>rowvector;
        //mapArray.reserve(100);
        while (std::getline(rowStream, col, ',')) 
        {
            mapArray.push_back(stoi(col));
 //           mapArray[offset++] = static_cast<char>(stoi(col));
 //           rowvector.push_back(col);
        }
     //   mapArray.push_back(rowvector);
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

    WORD Colour= 0x0B;//0x0110 (cursed blue colour)
    for (int j = 0; j < mapHeight; j++) {
        for (int i = 0; i < mapWidth; i++)
        {
            c.X = i;
            c.Y = j;
            switch(mapArray[j * mapWidth + i])
            {
            case 1: 
                (mapArray[j * mapWidth + i]) = char(221);
                break;
            }
            g_Console.writeToBuffer(c, mapArray[j * mapWidth + i], Colour);
        }  
    }
} 

void startscreen()
{/*
    std::ifstream maze;
    maze.open("themaze.txt", std::ifstream::in);
    //int level=1;
    //switch (level)
    //{
    //case 1: maps = std::ifstream("MapDesign1.txt");
    //    break;

    //}
    // Opening may fail, always check.
    if (!maze) {
        exit(1);
    }
    std::string row;
    while (std::getline(maze, row))
    {
        std::stringstream rowStream(row);
        std::string(col);
        std::vector<std::string>rowvector;
        //mapArray.reserve(100);
        while (std::getline(rowStream, col, ','))
        {
            startArray.push_back(stoi(col));
            //           mapArray[offset++] = static_cast<char>(stoi(col));
            //           rowvector.push_back(col);
        }
        //   mapArray.push_back(rowvector);
    }
    maze.close();
    */
}
void MapDesign2()
{
    std::ifstream maps;
    maps.open("MapDesign2.txt", std::ifstream::in);
    // Opening may fail, always check.
    if (!maps) {
        exit(1);
    }
    std::string row;
    while (std::getline(maps, row))
    {
        std::stringstream rowStream(row);
        std::string(col);
        std::vector<std::string>rowvector;
        while (std::getline(rowStream, col, ','))
        {
            mapArray.push_back(stoi(col));
        }

    }
    maps.close();
}

void renderMap2()
{
    COORD c;
    WORD Colour = 0x0110;
    for (int j = 0; j < mapHeight; j++) {
        for (int i = 0; i < mapWidth; i++)
        {
            c.X = i;
            c.Y = j;
            switch (mapArray[j * mapWidth + i])
            {
            case 1:
                (mapArray[j * mapWidth + i]) = char(221);
                break;
            }
            g_Console.writeToBuffer(c, mapArray[j * mapWidth + i], Colour);
        }
    }
}


void init_firstmap(void)
{
    //to help with mob spawning
    srand((unsigned)time(0));

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

    g_sChar.m_cLocation.X = 1;
    g_sChar.m_cLocation.Y = 1;
    g_sChar.m_bActive = true;

    g_sMob.m_cLocation.X = rand() % 13 + 25;
    g_sMob.m_cLocation.Y = 1;
    g_sMob.m_bActive = true;

    g_sMob1.m_cLocation.X = rand() % 2 + 16;
    g_sMob1.m_cLocation.Y = 9;
    g_sMob1.m_bActive = true;

    g_sMob2.m_cLocation.X = rand () % 4 + 44;
    g_sMob2.m_cLocation.Y = rand() % 4 + 1;
    g_sMob2.m_bActive = true;
    
    g_sMob3.m_cLocation.X = rand() % 2 + 25;
    g_sMob3.m_cLocation.Y = rand() % 4 + 9;
    g_sMob3.m_bActive = true;

    g_sMob4.m_cLocation.X = rand() % 15 + 17;
    g_sMob4.m_cLocation.Y = 19;
    g_sMob4.m_bActive = true;


    //location for weapon
    g_sWeapon.m_cLocation.X = 5; // Jun Ying spawning WIP (fixed position for now)
    g_sWeapon.m_cLocation.Y = 4;

    g_sWeapon2.m_cLocation.X = 14; // Jun Ying spawning WIP (fixed position for now)
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

void renderstart()
{/*
    COORD c;

    WORD Colour = 0x0B;//0x0110 (cursed blue colour)
    for (int j = 0; j < startY; j++) {
        for (int i = 0; i < startX; i++)
        {
            c.X = i;
            c.Y = j;
          
            g_Console.writeToBuffer(c, startY[j * startX + i], Colour);
        }
    }*/
}


void moveCharacter()
{    
    
    //124
    // Updating the location of the character based on the key release
    // providing a beep sound whenver we shift the character

    if (g_skKeyEvent[K_UP].keyReleased && mapArray[(g_sChar.m_cLocation.Y - 1)* mapWidth + g_sChar.m_cLocation.X] != char(221))
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y--;       
    }
    if (g_skKeyEvent[K_LEFT].keyReleased && mapArray[g_sChar.m_cLocation.Y * mapWidth + (g_sChar.m_cLocation.X - 1)] != char(221))
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X--;        
    }
    if (g_skKeyEvent[K_DOWN].keyReleased && mapArray[(g_sChar.m_cLocation.Y + 1) * mapWidth + g_sChar.m_cLocation.X] != char(221))
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y++;        
    }
    if (g_skKeyEvent[K_RIGHT].keyReleased && mapArray[g_sChar.m_cLocation.Y * mapWidth + (g_sChar.m_cLocation.X + 1)] != char(221))
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X++;        
    }
    
}

bool easy_mode = false;
bool normal_mode = false;
bool hard_mode = false;

//hi
void moveMob()
{
    if (hard_mode == true)
    {
        normal_mode = false;
        easy_mode = false;
        //move down
        if (g_sChar.m_cLocation.Y > g_sMob.m_cLocation.Y && g_dHeartBeat <= 0.02 && mob_exists == true)//0.02 hardcoded for now, change to difficulty
        {
            g_sMob.m_cLocation.Y++;
        }
        if (g_sChar.m_cLocation.Y > g_sMob1.m_cLocation.Y && g_dHeartBeat <= 0.02 && mob1_exists == true)
        {
            g_sMob1.m_cLocation.Y++;
        }
        if (g_sChar.m_cLocation.Y > g_sMob2.m_cLocation.Y && g_dHeartBeat <= 0.02 && mob2_exists == true)
        {
            g_sMob2.m_cLocation.Y++;
        }
        if (g_sChar.m_cLocation.Y > g_sMob3.m_cLocation.Y && g_dHeartBeat <= 0.02 && mob3_exists == true)
        {
            g_sMob3.m_cLocation.Y++;
        }
        if (g_sChar.m_cLocation.Y > g_sMob4.m_cLocation.Y && g_dHeartBeat <= 0.02 && mob4_exists == true)
        {
            g_sMob4.m_cLocation.Y++;
        }
        //move up
        if (g_sChar.m_cLocation.Y < g_sMob.m_cLocation.Y && g_dHeartBeat <= 0.02 && mob_exists == true)
        {
            g_sMob.m_cLocation.Y--;
        }
        if (g_sChar.m_cLocation.Y < g_sMob1.m_cLocation.Y && g_dHeartBeat <= 0.02 && mob1_exists == true)
        {
            g_sMob1.m_cLocation.Y--;
        }
        if (g_sChar.m_cLocation.Y < g_sMob2.m_cLocation.Y && g_dHeartBeat <= 0.02 && mob2_exists == true)
        {
            g_sMob2.m_cLocation.Y--;
        }
        if (g_sChar.m_cLocation.Y < g_sMob3.m_cLocation.Y && g_dHeartBeat <= 0.02 && mob3_exists == true)
        {
            g_sMob3.m_cLocation.Y--;
        }
        if (g_sChar.m_cLocation.Y < g_sMob4.m_cLocation.Y && g_dHeartBeat <= 0.02 && mob4_exists == true)
        {
            g_sMob4.m_cLocation.Y--;
        }
        //move right
        if (g_sChar.m_cLocation.X > g_sMob.m_cLocation.X && g_dHeartBeat <= 0.02 && mob_exists == true)
        {
            g_sMob.m_cLocation.X++;
        }
        if (g_sChar.m_cLocation.X > g_sMob1.m_cLocation.X && g_dHeartBeat <= 0.02 && mob1_exists == true)
        {
            g_sMob1.m_cLocation.X++;
        }
        if (g_sChar.m_cLocation.X > g_sMob2.m_cLocation.X && g_dHeartBeat <= 0.02 && mob2_exists == true)
        {
            g_sMob2.m_cLocation.X++;
        }
        if (g_sChar.m_cLocation.X > g_sMob3.m_cLocation.X && g_dHeartBeat <= 0.02 && mob3_exists == true)
        {
            g_sMob3.m_cLocation.X++;
        }
        if (g_sChar.m_cLocation.X > g_sMob4.m_cLocation.X && g_dHeartBeat <= 0.02 && mob4_exists == true)
        {
            g_sMob4.m_cLocation.X++;
        }
        //move left
        if (g_sChar.m_cLocation.X < g_sMob.m_cLocation.X && g_dHeartBeat <= 0.02 && mob_exists == true)
        {
            g_sMob.m_cLocation.X--;
        }
        if (g_sChar.m_cLocation.X < g_sMob1.m_cLocation.X && g_dHeartBeat <= 0.02 && mob1_exists == true)
        {
            g_sMob1.m_cLocation.X--;
        }
        if (g_sChar.m_cLocation.X < g_sMob2.m_cLocation.X && g_dHeartBeat <= 0.02 && mob2_exists == true)
        {
            g_sMob2.m_cLocation.X--;
        }
        if (g_sChar.m_cLocation.X < g_sMob3.m_cLocation.X && g_dHeartBeat <= 0.02 && mob3_exists == true)
        {
            g_sMob3.m_cLocation.X--;
        }
        if (g_sChar.m_cLocation.X < g_sMob4.m_cLocation.X && g_dHeartBeat <= 0.02 && mob4_exists == true)
        {
            g_sMob4.m_cLocation.X--;
        }
    }
    else if (easy_mode == true)
    {
        normal_mode - false;
        hard_mode = false;

        //move down
        if (g_sChar.m_cLocation.Y > g_sMob.m_cLocation.Y && g_dHeartBeat <= 0.02 && mapArray[(g_sMob.m_cLocation.Y + 1) * mapWidth + g_sMob.m_cLocation.X] != char(221) && mob_exists == true)//0.02 hardcoded for now, change to difficulty
        {
            g_sMob.m_cLocation.Y++;
        }
        if (g_sChar.m_cLocation.Y > g_sMob1.m_cLocation.Y && g_dHeartBeat <= 0.02 && mapArray[(g_sMob1.m_cLocation.Y + 1) * mapWidth + g_sMob1.m_cLocation.X] != char(221) && mob1_exists == true)
        {
            g_sMob1.m_cLocation.Y++;
        }
        if (g_sChar.m_cLocation.Y > g_sMob2.m_cLocation.Y && g_dHeartBeat <= 0.02 && mapArray[(g_sMob2.m_cLocation.Y + 1) * mapWidth + g_sMob2.m_cLocation.X] != char(221) && mob2_exists == true)
        {
            g_sMob2.m_cLocation.Y++;
        }
        if (g_sChar.m_cLocation.Y > g_sMob3.m_cLocation.Y && g_dHeartBeat <= 0.02 && mapArray[(g_sMob3.m_cLocation.Y + 1) * mapWidth + g_sMob3.m_cLocation.X] != char(221) && mob3_exists == true)
        {
            g_sMob3.m_cLocation.Y++;
        }
        if (g_sChar.m_cLocation.Y > g_sMob4.m_cLocation.Y && g_dHeartBeat <= 0.02 && mapArray[(g_sMob4.m_cLocation.Y + 1) * mapWidth + g_sMob4.m_cLocation.X] != char(221) && mob4_exists == true)
        {
            g_sMob4.m_cLocation.Y++;
        }
        //move up
        if (g_sChar.m_cLocation.Y < g_sMob.m_cLocation.Y && g_dHeartBeat <= 0.02 && mapArray[(g_sMob.m_cLocation.Y - 1) * mapWidth + g_sMob.m_cLocation.X] != char(221) && mob_exists == true)
        {
            g_sMob.m_cLocation.Y--;
        }
        if (g_sChar.m_cLocation.Y < g_sMob1.m_cLocation.Y && g_dHeartBeat <= 0.02 && mapArray[(g_sMob1.m_cLocation.Y - 1) * mapWidth + g_sMob1.m_cLocation.X] != char(221) && mob1_exists == true)
        {
            g_sMob1.m_cLocation.Y--;
        }
        if (g_sChar.m_cLocation.Y < g_sMob2.m_cLocation.Y && g_dHeartBeat <= 0.02 && mapArray[(g_sMob2.m_cLocation.Y - 1) * mapWidth + g_sMob2.m_cLocation.X] != char(221) && mob2_exists == true)
        {
            g_sMob2.m_cLocation.Y--;
        }
        if (g_sChar.m_cLocation.Y < g_sMob3.m_cLocation.Y && g_dHeartBeat <= 0.02 && mapArray[(g_sMob3.m_cLocation.Y - 1) * mapWidth + g_sMob3.m_cLocation.X] != char(221) && mob3_exists == true)
        {
            g_sMob3.m_cLocation.Y--;
        }
        if (g_sChar.m_cLocation.Y < g_sMob4.m_cLocation.Y && g_dHeartBeat <= 0.02 && mapArray[(g_sMob4.m_cLocation.Y - 1) * mapWidth + g_sMob4.m_cLocation.X] != char(221) && mob4_exists == true)
        {
            g_sMob4.m_cLocation.Y--;
        }
        //move right
        if (g_sChar.m_cLocation.X > g_sMob.m_cLocation.X && g_dHeartBeat <= 0.02 && mapArray[g_sMob.m_cLocation.Y * mapWidth + (g_sMob.m_cLocation.X + 1)] != char(221) && mob_exists == true)
        {
            g_sMob.m_cLocation.X++;
        }
        if (g_sChar.m_cLocation.X > g_sMob1.m_cLocation.X && g_dHeartBeat <= 0.02 && mapArray[g_sMob1.m_cLocation.Y * mapWidth + (g_sMob1.m_cLocation.X + 1)] != char(221) && mob1_exists == true)
        {
            g_sMob1.m_cLocation.X++;
        }
        if (g_sChar.m_cLocation.X > g_sMob2.m_cLocation.X && g_dHeartBeat <= 0.02 && mapArray[g_sMob2.m_cLocation.Y * mapWidth + (g_sMob2.m_cLocation.X + 1)] != char(221) && mob2_exists == true)
        {
            g_sMob2.m_cLocation.X++;
        }
        if (g_sChar.m_cLocation.X > g_sMob3.m_cLocation.X && g_dHeartBeat <= 0.02 && mapArray[g_sMob3.m_cLocation.Y * mapWidth + (g_sMob3.m_cLocation.X + 1)] != char(221) && mob3_exists == true)
        {
            g_sMob3.m_cLocation.X++;
        }
        if (g_sChar.m_cLocation.X > g_sMob4.m_cLocation.X && g_dHeartBeat <= 0.02 && mapArray[g_sMob4.m_cLocation.Y * mapWidth + (g_sMob4.m_cLocation.X + 1)] != char(221) && mob4_exists == true)
        {
            g_sMob4.m_cLocation.X++;
        }
        //move left
        if (g_sChar.m_cLocation.X < g_sMob.m_cLocation.X && g_dHeartBeat <= 0.02 && mapArray[g_sMob.m_cLocation.Y * mapWidth + (g_sMob.m_cLocation.X - 1)] != char(221) && mob_exists == true)
        {
            g_sMob.m_cLocation.X--;
        }
        if (g_sChar.m_cLocation.X < g_sMob1.m_cLocation.X && g_dHeartBeat <= 0.02 && mapArray[g_sMob1.m_cLocation.Y * mapWidth + (g_sMob1.m_cLocation.X - 1)] != char(221) && mob1_exists == true)
        {
            g_sMob1.m_cLocation.X--;
        }
        if (g_sChar.m_cLocation.X < g_sMob2.m_cLocation.X && g_dHeartBeat <= 0.02 && mapArray[g_sMob2.m_cLocation.Y * mapWidth + (g_sMob2.m_cLocation.X - 1)] != char(221) && mob2_exists == true)
        {
            g_sMob2.m_cLocation.X--;
        }
        if (g_sChar.m_cLocation.X < g_sMob3.m_cLocation.X && g_dHeartBeat <= 0.02 && mapArray[g_sMob3.m_cLocation.Y * mapWidth + (g_sMob3.m_cLocation.X - 1)] != char(221) && mob3_exists == true)
        {
            g_sMob3.m_cLocation.X--;
        }
        if (g_sChar.m_cLocation.X < g_sMob4.m_cLocation.X && g_dHeartBeat <= 0.02 && mapArray[g_sMob4.m_cLocation.Y * mapWidth + (g_sMob4.m_cLocation.X - 1)] != char(221) && mob4_exists == true)
        {
            g_sMob4.m_cLocation.X--;
        }
    }
    else if (normal_mode == true)
    {
        hard_mode = false;
        easy_mode = false;
        //move down
        if (g_sChar.m_cLocation.Y > g_sMob.m_cLocation.Y && g_dHeartBeat <= 0.02 && mapArray[(g_sMob.m_cLocation.Y + 1) * mapWidth + g_sMob.m_cLocation.X] != char(221) && mob_exists == true)
        {
            g_sMob.m_cLocation.Y++;
        }
        if (g_sChar.m_cLocation.Y > g_sMob1.m_cLocation.Y && g_dHeartBeat <= 0.02 && mapArray[(g_sMob1.m_cLocation.Y + 1) * mapWidth + g_sMob1.m_cLocation.X] != char(221) && mob1_exists == true)
        {
            g_sMob1.m_cLocation.Y++;
        }
        if (g_sChar.m_cLocation.Y > g_sMob2.m_cLocation.Y && g_dHeartBeat <= 0.02 && mapArray[(g_sMob2.m_cLocation.Y + 1) * mapWidth + g_sMob2.m_cLocation.X] != char(221) && mob2_exists == true)
        {
            g_sMob2.m_cLocation.Y++;
        }
        if (g_sChar.m_cLocation.Y > g_sMob3.m_cLocation.Y && g_dHeartBeat <= 0.02 && mapArray[(g_sMob3.m_cLocation.Y + 1) * mapWidth + g_sMob3.m_cLocation.X] != char(221) && mob3_exists == true)
        {
            g_sMob3.m_cLocation.Y++;
        }
        if (g_sChar.m_cLocation.Y > g_sMob4.m_cLocation.Y && g_dHeartBeat <= 0.02 && mapArray[(g_sMob4.m_cLocation.Y + 1) * mapWidth + g_sMob4.m_cLocation.X] != char(221) && mob4_exists == true)
        {
            g_sMob4.m_cLocation.Y++;
        }
        //move up
        if (g_sChar.m_cLocation.Y < g_sMob.m_cLocation.Y && g_dHeartBeat <= 0.02 && mapArray[(g_sMob.m_cLocation.Y - 1) * mapWidth + g_sMob.m_cLocation.X] != char(221) && mob_exists == true)
        {
            g_sMob.m_cLocation.Y--;
        }
        if (g_sChar.m_cLocation.Y < g_sMob1.m_cLocation.Y && g_dHeartBeat <= 0.02 && mapArray[(g_sMob1.m_cLocation.Y - 1) * mapWidth + g_sMob1.m_cLocation.X] != char(221) && mob1_exists == true)
        {
            g_sMob1.m_cLocation.Y--;
        }
        if (g_sChar.m_cLocation.Y < g_sMob2.m_cLocation.Y && g_dHeartBeat <= 0.02 && mapArray[(g_sMob2.m_cLocation.Y - 1) * mapWidth + g_sMob2.m_cLocation.X] != char(221) && mob2_exists == true)
        {
            g_sMob2.m_cLocation.Y--;
        }
        if (g_sChar.m_cLocation.Y < g_sMob3.m_cLocation.Y && g_dHeartBeat <= 0.02 && mapArray[(g_sMob3.m_cLocation.Y - 1) * mapWidth + g_sMob3.m_cLocation.X] != char(221) && mob3_exists == true)
        {
            g_sMob3.m_cLocation.Y--;
        }
        if (g_sChar.m_cLocation.Y < g_sMob4.m_cLocation.Y && g_dHeartBeat <= 0.02 && mapArray[(g_sMob4.m_cLocation.Y - 1) * mapWidth + g_sMob4.m_cLocation.X] != char(221) && mob4_exists == true)
        {
            g_sMob4.m_cLocation.Y--;
        }
        //move right
        if (g_sChar.m_cLocation.X > g_sMob.m_cLocation.X && g_dHeartBeat <= 0.02 && mapArray[g_sMob.m_cLocation.Y * mapWidth + (g_sMob.m_cLocation.X + 1)] != char(221) && mob_exists == true)
        {
            g_sMob.m_cLocation.X++;
        }
        if (g_sChar.m_cLocation.X > g_sMob1.m_cLocation.X && g_dHeartBeat <= 0.02 && mapArray[g_sMob1.m_cLocation.Y * mapWidth + (g_sMob1.m_cLocation.X + 1)] != char(221) && mob1_exists == true)
        {
            g_sMob1.m_cLocation.X++;
        }
        if (g_sChar.m_cLocation.X > g_sMob2.m_cLocation.X && g_dHeartBeat <= 0.02 && mapArray[g_sMob2.m_cLocation.Y * mapWidth + (g_sMob2.m_cLocation.X + 1)] != char(221) && mob2_exists == true)
        {
            g_sMob2.m_cLocation.X++;
        }
        if (g_sChar.m_cLocation.X > g_sMob3.m_cLocation.X && g_dHeartBeat <= 0.02 && mapArray[g_sMob3.m_cLocation.Y * mapWidth + (g_sMob3.m_cLocation.X + 1)] != char(221) && mob3_exists == true)
        {
            g_sMob3.m_cLocation.X++;
        }
        if (g_sChar.m_cLocation.X > g_sMob4.m_cLocation.X && g_dHeartBeat <= 0.02 && mapArray[g_sMob4.m_cLocation.Y * mapWidth + (g_sMob4.m_cLocation.X + 1)] != char(221) && mob4_exists == true)
        {
            g_sMob4.m_cLocation.X++;
        }
        //move left
        if (g_sChar.m_cLocation.X < g_sMob.m_cLocation.X && g_dHeartBeat <= 0.02 && mapArray[g_sMob.m_cLocation.Y * mapWidth + (g_sMob.m_cLocation.X - 1)] != char(221) && mob_exists == true)
        {
            g_sMob.m_cLocation.X--;
        }
        if (g_sChar.m_cLocation.X < g_sMob1.m_cLocation.X && g_dHeartBeat <= 0.02 && mapArray[g_sMob1.m_cLocation.Y * mapWidth + (g_sMob1.m_cLocation.X - 1)] != char(221) && mob1_exists == true)
        {
            g_sMob1.m_cLocation.X--;
        }
        if (g_sChar.m_cLocation.X < g_sMob2.m_cLocation.X && g_dHeartBeat <= 0.02 && mapArray[g_sMob2.m_cLocation.Y * mapWidth + (g_sMob2.m_cLocation.X - 1)] != char(221) && mob2_exists == true)
        {
            g_sMob2.m_cLocation.X--;
        }
        if (g_sChar.m_cLocation.X < g_sMob3.m_cLocation.X && g_dHeartBeat <= 0.02 && mapArray[g_sMob3.m_cLocation.Y * mapWidth + (g_sMob3.m_cLocation.X - 1)] != char(221) && mob3_exists == true)
        {
            g_sMob3.m_cLocation.X--;
        }
        if (g_sChar.m_cLocation.X < g_sMob4.m_cLocation.X && g_dHeartBeat <= 0.02 && mapArray[g_sMob4.m_cLocation.Y * mapWidth + (g_sMob4.m_cLocation.X - 1)] != char(221) && mob4_exists == true)
        {
            g_sMob4.m_cLocation.X--;
        }
    }
}
 



           



void endgame()
{
    if (g_sChar.m_cLocation.X == 49 && g_sChar.m_cLocation.Y == 11)
    {
        
        g_sChar.m_cLocation.X = 1;
        g_sChar.m_cLocation.Y = 2;
        
        cleared = true;
        
        weaponExist = true;
        hasweapon = false;
        weapon2Exist = true;
        hasweapon2 = false;
        
        g_eGameState = S_GAME1;





    }
}
void cheat()
{
    /*if (g_eGameState = S_GAME)
    {
        bool cheat = false;
        if (g_skKeyEvent[K_Q].keyReleased)
        {
            cheat = true;
            g_sChar.m_cLocation.X = 48;
            g_sChar.m_cLocation.Y = 11;
            cheat = false;


        }
    }*/
}




void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0C;
    if (g_sChar.m_bActive)
    {
        charColor = 0x0A;
    }
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)80, charColor);

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
        g_Console.writeToBuffer(g_sMob.m_cLocation, (char)233, mobColor);
    }
    
    if (mob1_exists == true)
    {
        g_Console.writeToBuffer(g_sMob1.m_cLocation, (char)233, mobColor);
    }

    if (mob2_exists == true)
    {
        g_Console.writeToBuffer(g_sMob2.m_cLocation, (char)233, mobColor); 
    }

    if (mob3_exists == true)
    {
        g_Console.writeToBuffer(g_sMob3.m_cLocation, (char)233, mobColor);
    }

    if (mob4_exists == true)
    {
        g_Console.writeToBuffer(g_sMob4.m_cLocation, (char)233, mobColor);
    }
}

//to be changed with splash screen
//easy, normal,hard, EXTREME
void setdifficulty()//completely doesnt work? its not being initalized
{
    if (g_eGameState == S_SPLASHSCREEN)
    {
        /*
        if (g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED &&
            g_mouseEvent.mousePosition.Y == 7)
        {
            //easy difficulty
            easydiff = true;
            normdiff = false;
            hardfiff = false;
            lunadiff = false;

        }
        modeselected = true;
    */

    //doesnt work switching to new plan
        getInput();

        if (g_skKeyEvent[K_Q].keyReleased)
        {
            setmobmoveinterval(2.0); // the interval for each movement here (Jun Ying)
            easy_mode = true;
            modeselected = true;
            start_time = true;
            g_eGameState = S_GAME;

        }
        else if (g_skKeyEvent[K_A].keyReleased)
        {
            setmobmoveinterval(1.5); // the interval for each movement here (Jun Ying)
            normal_mode = true;
            modeselected = true;
            start_time = true;
            g_eGameState = S_GAME;

        }
        else if (g_skKeyEvent[K_Z].keyReleased)
        {
            setmobmoveinterval(1); // the interval for each movement here (Jun Ying)
            hard_mode = true;
            modeselected = true;
            start_time = true;
            g_eGameState = S_GAME;
        }
    

    }
    
    
}
   
void renderWeapons() // Jun Ying
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
        g_sMob.m_cLocation.X = 49;
        g_sMob.m_cLocation.Y = 1;
        
        mob_attacked = true; 
        
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
        g_sMob1.m_cLocation.X = 49;
        g_sMob1.m_cLocation.Y = 1;

        if (cleared == false)
        {
            mob1_attacked = true;
        }
        else if (cleared == true)
        {
            mob1_attacked_2 = true;
        }
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
        g_sMob2.m_cLocation.X = 49;
        g_sMob2.m_cLocation.Y = 1;

        if (cleared == false)
        {
            mob2_attacked = true;
        }
        else if (cleared == true)
        {
            mob2_attacked_2 = true;
        }
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
        g_sMob3.m_cLocation.X = 49;
        g_sMob3.m_cLocation.Y = 1;

        if (cleared == false)
        {
            mob3_attacked = true;
        }
        else if (cleared == true)
        {
            mob3_attacked_2 = true;
        }
       
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
        g_sMob4.m_cLocation.X = 49;
        g_sMob4.m_cLocation.Y = 1;

        if (cleared == false)
        {
            mob4_attacked = true;
        }
        else if (cleared == true)
        {
            mob4_attacked_2 = true;
        }
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
void weapon2init()
{
    g_sSlash.m_cLocation.X = 0;
    g_sSlash.m_cLocation.Y = 0;
    g_sSlash2.m_cLocation.X = 0;
    g_sSlash2.m_cLocation.Y = 0;
    g_sSlash3.m_cLocation.X = 0;
    g_sSlash3.m_cLocation.Y = 0;
}

void weapon2attacksystem()
{
    weapon2init();
    bool canbeam = false;
    bool canbeam2 = false;
    bool canbeam3 = false;
    WORD attackColor = 10;
    if (hasweapon2 == true && weapon2Exist == false && g_skKeyEvent[K_B].keyReleased)
    {
        // sword attack
        if (recentmoveinput == "UP")// up
        {
            if (mapArray[(g_sChar.m_cLocation.Y - 1) * mapWidth + g_sChar.m_cLocation.X] != char(221))
            {
                canbeam = true;
                g_sSlash.m_cLocation.X = g_sChar.m_cLocation.X;
                g_sSlash.m_cLocation.Y = g_sChar.m_cLocation.Y - 1;
                g_Console.writeToBuffer(g_sSlash.m_cLocation, (char)219, attackColor);
            }

            if (mapArray[(g_sChar.m_cLocation.Y - 2) * mapWidth + g_sChar.m_cLocation.X] != char(221) && canbeam == true)
            {
                canbeam2 = true;
                g_sSlash2.m_cLocation.X = g_sChar.m_cLocation.X;
                g_sSlash2.m_cLocation.Y = g_sChar.m_cLocation.Y - 2;
                g_Console.writeToBuffer(g_sSlash2.m_cLocation, (char)219, attackColor);
            }

            if (mapArray[(g_sChar.m_cLocation.Y - 3) * mapWidth + g_sChar.m_cLocation.X] != char(221) && canbeam2 == true)
            {
                canbeam3 = true;
                g_sSlash3.m_cLocation.X = g_sChar.m_cLocation.X;
                g_sSlash3.m_cLocation.Y = g_sChar.m_cLocation.Y - 3;
                g_Console.writeToBuffer(g_sSlash3.m_cLocation, (char)219, attackColor);
            }

        }
        else if (recentmoveinput == "LEFT")//left
        {
            if (mapArray[g_sChar.m_cLocation.Y * mapWidth + (g_sChar.m_cLocation.X - 1)] != char(221))
            {
                canbeam = true;
                g_sSlash.m_cLocation.X = g_sChar.m_cLocation.X - 1;
                g_sSlash.m_cLocation.Y = g_sChar.m_cLocation.Y;
                g_Console.writeToBuffer(g_sSlash.m_cLocation, (char)219, attackColor);
            }

            if (mapArray[g_sChar.m_cLocation.Y * mapWidth + (g_sChar.m_cLocation.X - 2)] != char(221) && canbeam == true)
            {
                canbeam2 = true;
                g_sSlash2.m_cLocation.X = g_sChar.m_cLocation.X - 2;
                g_sSlash2.m_cLocation.Y = g_sChar.m_cLocation.Y;
                g_Console.writeToBuffer(g_sSlash2.m_cLocation, (char)219, attackColor);
            }

            if (mapArray[g_sChar.m_cLocation.Y * mapWidth + (g_sChar.m_cLocation.X - 3)] != char(221) && canbeam2 == true)
            {
                canbeam3 = true;
                g_sSlash3.m_cLocation.X = g_sChar.m_cLocation.X - 3;
                g_sSlash3.m_cLocation.Y = g_sChar.m_cLocation.Y;
                g_Console.writeToBuffer(g_sSlash3.m_cLocation, (char)219, attackColor);
            }

        }
        else if (recentmoveinput == "RIGHT")//right
        {
            if (mapArray[g_sChar.m_cLocation.Y * mapWidth + (g_sChar.m_cLocation.X + 1)] != char(221))
            {
                canbeam = true;
                g_sSlash.m_cLocation.X = g_sChar.m_cLocation.X + 1;
                g_sSlash.m_cLocation.Y = g_sChar.m_cLocation.Y;
                g_Console.writeToBuffer(g_sSlash.m_cLocation, (char)219, attackColor);
            }

            if (mapArray[g_sChar.m_cLocation.Y * mapWidth + (g_sChar.m_cLocation.X + 2)] != char(221) && canbeam == true)
            {
                canbeam2 = true;
                g_sSlash2.m_cLocation.X = g_sChar.m_cLocation.X + 2;
                g_sSlash2.m_cLocation.Y = g_sChar.m_cLocation.Y;
                g_Console.writeToBuffer(g_sSlash2.m_cLocation, (char)219, attackColor);
            }

            if (mapArray[g_sChar.m_cLocation.Y * mapWidth + (g_sChar.m_cLocation.X + 3)] != char(221) && canbeam2 == true)
            {
                g_sSlash3.m_cLocation.X = g_sChar.m_cLocation.X + 3;
                g_sSlash3.m_cLocation.Y = g_sChar.m_cLocation.Y;
                g_Console.writeToBuffer(g_sSlash3.m_cLocation, (char)219, attackColor);
            }

        }
        else if (recentmoveinput == "DOWN")//down
        {
            if (mapArray[(g_sChar.m_cLocation.Y + 1) * mapWidth + g_sChar.m_cLocation.X] != char(221))
            {
                canbeam = true;
                g_sSlash.m_cLocation.X = g_sChar.m_cLocation.X;
                g_sSlash.m_cLocation.Y = g_sChar.m_cLocation.Y + 1;
                g_Console.writeToBuffer(g_sSlash.m_cLocation, (char)219, attackColor);
            }

            if (mapArray[(g_sChar.m_cLocation.Y + 2) * mapWidth + g_sChar.m_cLocation.X] != char(221) && canbeam == true)
            {
                canbeam2 = true;
                g_sSlash2.m_cLocation.X = g_sChar.m_cLocation.X;
                g_sSlash2.m_cLocation.Y = g_sChar.m_cLocation.Y + 2;
                g_Console.writeToBuffer(g_sSlash2.m_cLocation, (char)219, attackColor);
            }

            if (mapArray[(g_sChar.m_cLocation.Y + 3) * mapWidth + g_sChar.m_cLocation.X] != char(221) && canbeam2 == true)
            {
                canbeam3 = true;
                g_sSlash3.m_cLocation.X = g_sChar.m_cLocation.X;
                g_sSlash3.m_cLocation.Y = g_sChar.m_cLocation.Y + 3;
                g_Console.writeToBuffer(g_sSlash3.m_cLocation, (char)219, attackColor);
            }

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

            if (cleared == false)
            {
                mob_attacked = true;
            }
            if (cleared == true)
            {
                mob_attacked_2 = true;
            }
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


            if (cleared == false)
            {
                mob1_attacked = true;
            }
            if (cleared == true)
            {
                mob1_attacked_2 = true;
            }
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


            if (cleared == false)
            {
                mob2_attacked = true;
            }
            if (cleared == true)
            {
                mob2_attacked_2 = true;
            }
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


            if (cleared == false)
            {
                mob3_attacked = true;
            }
            if (cleared == true)
            {
                mob3_attacked_2 = true;
            }
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


            if (cleared == false)
            {
                mob4_attacked = true;
            }
            if (cleared == true)
            {
                mob4_attacked_2 = true;
            }
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

void mobcollide()// working on loops now
{
    if (mob_exists == true||mob1_exists == true||mob2_exists == true||mob3_exists == true||mob4_exists==true)
    {
        if (g_sMob.m_cLocation.X == g_sChar.m_cLocation.X
            && g_sMob.m_cLocation.Y == g_sChar.m_cLocation.Y ||
            g_sMob1.m_cLocation.X == g_sChar.m_cLocation.X
            && g_sMob1.m_cLocation.Y == g_sChar.m_cLocation.Y ||
            g_sMob2.m_cLocation.X == g_sChar.m_cLocation.X
            && g_sMob2.m_cLocation.Y == g_sChar.m_cLocation.Y ||
            g_sMob3.m_cLocation.X == g_sChar.m_cLocation.X
            && g_sMob3.m_cLocation.Y == g_sChar.m_cLocation.Y ||
            g_sMob4.m_cLocation.X == g_sChar.m_cLocation.X
            && g_sMob4.m_cLocation.Y == g_sChar.m_cLocation.Y
            )
        {
            char_exists == false;
            if (char_exists == true)
            {
                mob1_exists = false;
                mob2_exists = false;
                mob3_exists = false;
                mob4_exists = false;
                //game over
                g_eGameState = S_LOSE;
                if (g_eGameState == S_LOSE)
                {

                    COORD c;
                    std::ostringstream ss;
                    ss << " ";
                    ss << "PRESS ENTER TO RESTART AND SPACE TO QUIT!";
                    c.X = 20;
                    c.Y = 16;
                    g_Console.writeToBuffer(c, ss.str());

                    // adding end game and restart func
                    //g_bQuitGame = true; // ends game
                    if (g_skKeyEvent[K_RETURN].keyReleased)//this is go back to game(restart)
                    {   // add in u lose
                        init_firstmap();
                        weapon2Exist = true;
                        weaponExist = true;
                        g_dElapsedTime = 0;
                        //if you die, restart everything(Reagan)
                        if (cleared == true)
                        {
                            cleared = false;
                        }

                        g_eGameState = S_GAME;
                    }
                    if (g_skKeyEvent[K_SPACE].keyReleased)//ends programme
                    {
                        g_bQuitGame = true;



                    }














                }


            }






        }
    }
}

void endscreen()
{
    std::ifstream lose;
    lose.open("youlose.txt", std::ifstream::in);
    if (!lose)
    {
        exit(1);
    }
    std::vector<std::string>row1;
    if (lose.is_open())
    {
        std::string rows;
        while (std::getline(lose, rows))
        {
            row1.push_back(rows);
        }
        lose.close();
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
void playerwin()
{
    if (g_eGameState == S_GAME1 && g_sChar.m_cLocation.X == 49 && g_sChar.m_cLocation.Y == 11)//map 2, end location
    {
        g_eGameState = S_WIN;

    }   
}
void renderWText()
{
    //text box spawn after a certain time
    if (modeselected == true)
    {
        if (g_dElapsedTime >= 1 && g_dElapsedTime < 2)
        {
            COORD c;
            std::ostringstream ss;
            ss << "Welcome to the maze!";
            c.X = 55;
            c.Y = 15;
            g_Console.writeToBuffer(c, ss.str());
        }
        if (g_dElapsedTime >= 2 && g_dElapsedTime < 3)
        {
            COORD c;
            std::ostringstream ss;
            ss << "Can u get out alive??";
            c.X = 55;
            c.Y = 15;
            g_Console.writeToBuffer(c, ss.str());
        }
        if (g_dElapsedTime >= 3)
        {
            after_cutscene = true;
        }
    }

    //if weapon is equipped
    if (hasweapon == true)
    {
        COORD c;
        std::ostringstream ss;
        ss.str("");
        ss << "             +-+";
        c.X = 50;
        c.Y = 15;
        g_Console.writeToBuffer(c, ss.str());
        ss.str("");
        ss << "=============| | READY!";
        c.X = 50;
        c.Y = 16;
        g_Console.writeToBuffer(c, ss.str());
        ss.str("");
        ss << "            `:_;'";
        c.X = 50;
        c.Y = 17;
        g_Console.writeToBuffer(c, ss.str());
    }
    if (hasweapon2 == true)
    {
        COORD c;
        std::ostringstream ss;
        ss << "*////{<>===============- READY!";
        c.X = 50;
        c.Y = 20;
        g_Console.writeToBuffer(c, ss.str());
    }
}

void renderHeartbeat()
{
    COORD c;
    // displays the mob movement interval
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << "Heartbeat:" << g_dHeartBeat;
    c.X = g_Console.getConsoleSize().X - 15;
    c.Y = 2;
    g_Console.writeToBuffer(c, ss.str());
}

void render30sTimer()
{
    COORD c;
    // displays the mob spawning
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << "30sTimer:" << g_d30Timer;
    c.X = g_Console.getConsoleSize().X - 15;
    c.Y = 3;
    g_Console.writeToBuffer(c, ss.str());
}

void renderFramerate()
{
    
        COORD c;
        // displays the framerate
        std::ostringstream ss;
        ss << std::fixed << std::setprecision(3);
        ss << "FPS:" << 1.0 / g_dDeltaTime;
        c.X = g_Console.getConsoleSize().X - 12;
        c.Y = 0;
        g_Console.writeToBuffer(c, ss.str());

        // displays the elapsed time
        ss.str("");
        ss << "Time:" << g_dElapsedTime;
        c.X = 68;
        c.Y = 1;
        g_Console.writeToBuffer(c, ss.str());
    

    
}

//after a certain time, these mobs will spawn
void mobspawn()
{ 
    if (cleared == false)
    {
        if (g_dElapsedTime > 10 && mob1_attacked == false)
        {
            mob1_exists = true;
        }
        if (g_dElapsedTime > 30 && mob2_attacked == false)
        {
            mob2_exists = true;
        }
        if (g_dElapsedTime > 50 && mob3_attacked == false)
        {
            mob3_exists = true;
        }
        if (g_dElapsedTime > 70 && mob4_attacked == false)
        {
            mob4_exists = true;
        }
    }
    //if cleared a level, the game will clear all gthosts(Reagan)
    if (cleared == true)
    {
        mob_exists = false;
        mob1_exists = false;
        mob2_exists = false;
        mob3_exists = false;
        mob4_exists = false;

        //after a certain time, the ghosts will spawn again(Reagan)
        if (g_dElapsedTime_2 > 10 && mob1_attacked_2 == false)
        {
            mob1_exists = true;
        }
        if (g_dElapsedTime_2 > 30 && mob2_attacked_2 == false)
        {
            mob2_exists = true;
        }
        if (g_dElapsedTime_2 > 50 && mob3_attacked_2 == false)
        {
            mob3_exists = true;
        }
        if (g_dElapsedTime_2 > 70 && mob4_attacked_2 == false)
        {
            mob4_exists = true;
        }
        if (g_dElapsedTime_2 > 0 && mob_attacked_2 == false)
        {
            mob_exists = true;
        }
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
        case K_Q: key = "Q";
            break;
        case K_A: key = "A";
            break;
        case K_Z: key = "Z";
            break;
        case K_RETURN:key = "ENTER";
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
       g_Console.writeToBuffer(c, ss.str(), 0x17);
       
    }



    //// mouse events    
    //ss.str("");
    //ss << "Mouse position (" << g_mouseEvent.mousePosition.X << ", " << g_mouseEvent.mousePosition.Y << ")";
    //g_Console.writeToBuffer(g_mouseEvent.mousePosition, ss.str(), 0x59);
    //ss.str("");
    //switch (g_mouseEvent.eventFlags)
    //{
    //case 0:
    //    if (g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
    //    {
    //        ss.str("Left Button Pressed");
    //        g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 1, ss.str(), 0x59);
    //    }
    //    else if (g_mouseEvent.buttonState == RIGHTMOST_BUTTON_PRESSED)
    //    {
    //        ss.str("Right Button Pressed");
    //        g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 2, ss.str(), 0x59);
    //    }
    //    else
    //    {
    //        ss.str("Some Button Pressed");
    //        g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 3, ss.str(), 0x59);
    //    }
    //    break;
    //case DOUBLE_CLICK:
    //    ss.str("Double Clicked");
    //    g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 4, ss.str(), 0x59);
    //    break;        
    //case MOUSE_WHEELED:
    //    if (g_mouseEvent.buttonState & 0xFF000000)
    //        ss.str("Mouse wheeled down");
    //    else 
    //        ss.str("Mouse wheeled up");
    //    g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 5, ss.str(), 0x59);
    //    break;
    //default:        
    //    break;
    //}
    
}



