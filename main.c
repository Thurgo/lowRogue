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

    //
    newPlayer->xPosition = 14;
    newPlayer->yPosition = 14;
    newPlayer->health = 20;

    //
    mvprintw(newPlayer->yPosition, newPlayer->xPosition, "@"); // Print @ at players location
    move(newPlayer->yPosition, newPlayer->xPosition); //Moves the cursor to players location

    return newPlayer;
}

int handleInput(int input, Player * user)
{
    switch (input)
    {
        //move up
        case 'w':
        case 'W':
            playerMove(user->yPosition - 1, user->xPosition, user);
            break;
        //move down
        case 's':
        case 'S':
            playerMove(user->yPosition + 1, user->xPosition, user);
            break;
        //move left
        case 'a':
        case 'A':
            playerMove(user->yPosition, user->xPosition - 1, user);
            break;
        //move right
        case 'd':
        case 'D':
            playerMove(user->yPosition, user->xPosition + 1, user);
            break;

        default:
            break;


    }
}

int playerMove(int y, int x, Player * user)
{
    mvprintw(user->yPosition, user->xPosition, ".");

    user->xPosition = x;
    user->yPosition = y;

    mvprintw(user->yPosition, user->xPosition, "@");
    move(user->yPosition, user->xPosition);
}