#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct Player // Player struct. Position and HP
{
    int xPosition;
    int yPosition;
    int health;
} Player;

int playerMove(int y, int x, Player * user);




int checkPosition(int newY, int newX, Player * user);
int screenSetUp();
int mapSetUp();
Player * playerSetup();

int main()
{
    //Setup
    int ch;
    Player * user; //init user
    screenSetUp(); // Starts game
    mapSetUp(); // Renders map
    user = playerSetup();
    int handleInput(int input, Player * user);


    //Main game setup
    while ((ch = getch()) != 'z') //When user enters char z end game
    {
        handleInput(ch, user);
    }


    endwin(); // Ends ncurses(screenSetUp)
    return 0;
}






int screenSetUp() //Creating ncurses game
{
    initscr(); //Start screen
    printw("Hello World!\n"); //Print to console
    noecho(); // Dont repeat back what user types. Cannot play game without this on
    refresh(); //I think  that this wipes the screen!

    return 1;
}

int mapSetUp() // function for creating the map
{
    // move cursor to x13 y13 and build a ceiling
    mvprintw(13, 13, "--------"); //y, x, "string"
    //show that this is a room with two horizontal walls with 6 spaces (4)
    mvprintw(14, 13, "|......|"); //y, x, "string"
    mvprintw(15, 13, "|......|"); //y, x, "string"
    mvprintw(16, 13, "|......|"); //y, x, "string"
    mvprintw(17, 13, "|......|"); //y, x, "string"
    //Another ceiling yo
    mvprintw(18, 13, "--------"); //y, x, "string"

    // move cursor to x13 y13 and build a ceiling
    mvprintw(2, 40, "--------"); //y, x, "string"
    //show that this is a room with two horizontal walls with 6 spaces (4)
    mvprintw(3, 40, "|......|"); //y, x, "string"
    mvprintw(4, 40, "|......|"); //y, x, "string"
    mvprintw(5, 40, "|......|"); //y, x, "string"
    mvprintw(6, 40, "|......|"); //y, x, "string"
    //Another ceiling yo
    mvprintw(7, 40, "--------"); //y, x, "string"


    // move cursor to x13 y13 and build a ceiling
    mvprintw(10, 40, "--------"); //y, x, "string"
    //show that this is a room with two horizontal walls with 6 spaces (4)
    mvprintw(11, 40, "|......|"); //y, x, "string"
    mvprintw(12, 40, "|......|"); //y, x, "string"
    mvprintw(13, 40, "|......|"); //y, x, "string"
    mvprintw(14, 40, "|......|"); //y, x, "string"
    //Another ceiling yo
    mvprintw(15, 40, "--------"); //y, x, "string"
}

Player * playerSetup()
{
    Player * newPlayer; //Create new Player named newPlayer
    newPlayer = malloc(sizeof(Player)); // Create the memory for newPlayer pointer

    //init player loc/hp
    newPlayer->health = 20;
    newPlayer->xPosition = 14;
    newPlayer->yPosition = 14;
    //initial player spawn
    playerMove(14, 14, newPlayer);

    return newPlayer;
}

int handleInput(int input, Player * user)
{
    int newY;
    int newX;
    switch (input)
    {
        //move up
        case 'w':
        case 'W':
            newY = user->yPosition - 1;
            newX = user->xPosition;
            break;
        //move down
        case 's':
        case 'S':
            newY = user->yPosition + 1;
            newX = user->xPosition;
            break;
        //move left
        case 'a':
        case 'A':
            newY = user->yPosition;
            newX = user->xPosition - 1;
            break;
        //move right
        case 'd':
        case 'D':
            newY = user->yPosition;
            newX = user->xPosition + 1;
            break;

        default:
            break;


    }
    checkPosition(newY, newX, user);

}
//Checks what is at next position
int checkPosition(int newY, int newX, Player * user)
{
    int space;
    switch (mvinch(newY, newX)) //Finds the new place to move
    {
        case '.': // If it is a ., move to it
            playerMove(newY, newX, user);
            break;

        default: // If it is not a ., c
            move(user->yPosition, user->xPosition);
            break;

    }

}

int playerMove(int y, int x, Player * user)
{
    mvprintw(user->yPosition, user->xPosition, "."); //Print a '.' where the user currently is

    user->xPosition = x; //Set new position for user
    user->yPosition = y;

    mvprintw(user->yPosition, user->xPosition, "@"); // Set users pic
    move(user->yPosition, user->xPosition); //Move cursor to current users position
}