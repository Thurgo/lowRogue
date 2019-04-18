#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct Player // Player struct. Position and HP
{
    int xPosition;
    int yPosition;
    int health;
} Player;






int screenSetUp();
int mapSetUp();
Player * playerSetup();

int main()
{
    int ch;
    Player * user;
    screenSetUp(); // Starts game
    mapSetUp();

    user = playerSetup();

    while ((ch = getch()) != 'z')
    {

    }


    endwin(); // Ends ncurses(screenSetUp)
    return 0;
}






int screenSetUp() //Creating ncurses game
{
    initscr(); //Start screen
    printw("Hello World!\n"); //Print to console
    noecho(); // Dont repeat back what user types
    refresh(); //I think  that this wipes the screen!

    return 0;
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
    Player * newPlayer;
    newPlayer = malloc(sizeof(Player));

    //
    newPlayer->xPosition = 14;
    newPlayer->yPosition = 14;
    newPlayer->health = 20;

    //
    mvprintw(newPlayer->yPosition, newPlayer->xPosition, "@");
    move(newPlayer->yPosition, newPlayer->xPosition);

    return newPlayer;
}