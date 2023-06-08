#include <iostream>
#include <windows.h>
    /*The code includes two standard C++ libraries:
        iostream and windows.h.iostream is used for input / output operations
        windows.h is used for Windows - specific functions and types.*/
struct Player{
    int level;
    int health;
};

struct Game {
    Player *player; 
};
    /*Two structs are defined: Player and Game. The Player struct represents a player in the game 
        and has two integer variables: level and health. The Game struct represents the game itself 
        and contains a pointer to a Player object.*/

Game *pGame;

        //A global variable pGame of type Game* (pointer to Game) is declared.

        //this is the entry point of the program 
int main()
{
    pGame = new Game;
    pGame->player = new Player;
    pGame->player->level = 1;
    pGame->player->health = 100;

    INPUT_RECORD event;
    HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
    DWORD count; // required by ReadConsoleInput, we can ignore it

    //the first use of iostream
    std::cout << "welcome to stef's quest" << std::endl;
    std::cout << "Player is level 1 and has 100 health." << std::endl << std::endl;
    /*The notation std::cout is used to access the cout object,
        which is part of the std namespace in C++.*/

    while (true)
    {
        // handle user input
        if (WaitForSingleObject(hStdIn, 0) == WAIT_OBJECT_0)
        {
            ReadConsoleInput(hStdIn, &event, 1, &count);
            //WindowsAPI function call is used to read input events from the console input buffer 

            //check key event
            if (event.EventType == KEY_EVENT && !event.Event.KeyEvent.bKeyDown)
                /*The condition event.EventType == KEY_EVENT checks if the EventType member of the event structure is equal to KEY_EVENT.
                    This condition verifies if the input event is a keyboard event.
                    The second part of the condition !event.Event.KeyEvent.bKeyDown checks if the bKeyDown member of the KeyEvent structure within the event structure is false.
                    This condition verifies if the key event is a key release rather than a key press.*/
            {
                // switch statement that evaluates the value of event.Event.KeyEvent.wVirtualKeyCode
                switch (event.Event.KeyEvent.wVirtualKeyCode) {
                    //If the value of wVirtualKeyCode is equal to VK_SPACE, which represents the spacebar key, the code within this case block will be executed.
                case VK_SPACE:
                    pGame->player->health--;
                    //decrements the player's health by 1. It accesses the health member of the player object within the Game struct using the pGame pointer.

                    std::cout << "After taking 1 damager remaining health is: " << pGame->player->health << std::endl;

                    break;
                    //ensures that the program does not continue executing the code for other case labels in the switch statement.
                case VK_ESCAPE:
                    return 0;
                    // this code exits the main() function and terminates the program by returning 0.
                }
            }


            // update simulation

            // render graphics
        }
    }
}