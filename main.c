#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Room
{
    int xPosition;
    int yPosition;
    int height;
    int width;
    //
    //Monster ** monsters;
    //Item ** items;

} Room;



typedef struct Player // Player struct. Position and HP
{
    int xPosition;
    int yPosition;
    int health;
    //Room * room;
} Player;

int playerMove(int y, int x, Player * user);




int checkPosition(int newY, int newX, Player * user);
int screenSetUp();
int drawRoom(Room * room);
Room ** mapSetUp();
Player * playerSetup();

/*Room Functions */
Room * createRoom(int x, int y, int height, int width); //Create a room

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

Room ** mapSetUp() // function for creating the map
{
    Room ** rooms;
    rooms = malloc(sizeof(Room)* 6);

    rooms[0] = createRoom(13, 13, 6, 8);
    drawRoom(rooms[0]);

    rooms[1] = createRoom(40, 2, 6, 8);
    drawRoom(rooms[1]);

    rooms[2] = createRoom(40, 10, 6, 12);
    drawRoom(rooms[2]);

    return rooms;
}

Room * createRoom(int x, int y, int height, int width)
{
    Room * newRoom;
    newRoom = malloc(sizeof(Room));

    newRoom->xPosition = x;
    newRoom->yPosition = y;
    newRoom->height = height;
    newRoom->width = width;

    return newRoom;
}

int drawRoom(Room * room)
{
    int x;
    int y;

    /*Draw top and Bottom*/
    for (x = room->xPosition; x < room->xPosition + room->width; x++)
    {
        mvprintw(room->yPosition, x, "-");
        mvprintw(room->yPosition + room->height - 1, x, "-"); // Goes down height positions and print horizontally
    }

    /*Draw floors and the side walls */
    for(y = room->yPosition + 1; y < room->yPosition + room->height - 1; y++) // y is initialized to 1 below itself, and then it draws until it has reached its height
    {
        //draw side walls
        mvprintw(y, room->xPosition, "|");
        mvprintw(y, room->xPosition + room->width - 1, "|");

        //Draw Floors
        //Start 1 right from x, print . until the next wall which is xpos + width - 1
        for (x = room->xPosition + 1; x < room->xPosition + room->width - 1; x++)
        {
            mvprintw(y, x, ".");
        }

    }

    return 0;
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