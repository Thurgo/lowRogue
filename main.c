#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct Position
{
    int x;
    int y;
    //TODO Tiles tiletype
} Position;



typedef struct Room
{
    Position position;
    int height;
    int width;

    //Doors
    Position ** doors;



    //Monster ** monsters;
    //Item ** items;

} Room;



typedef struct Player // Player struct. Position and HP
{
    Position position;
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
    printw("lowRogue\n"); //Print to console
    noecho(); // Dont repeat back what user types. Cannot play game without this on
    refresh(); //I think  that this wipes the screen!
    srand(time(NULL));
    return 1;
}

Room ** mapSetUp() // function for creating the map
{
    Room ** rooms;
    rooms = malloc(sizeof(Room)* 6);

    rooms[0] = createRoom(13, 13, 6, 8); //Create and draw rooms
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

    newRoom->position.x = x;
    newRoom->position.y = y;
    newRoom->height = height;
    newRoom->width = width;

    //doors
 //random #

    newRoom->doors = malloc(sizeof(Position) * 4); //Memory for 4 doors
    //TOP DOOR
    newRoom->doors[0] = malloc(sizeof(Position));
    newRoom->doors[0]->x = rand() % (width - 2) + newRoom->position.x + 1; // Subtract 1 from width SO that you never hit the wall and have a door in a corner. also add 1 to the x so the same thing doesnt happen on the other side
    newRoom->doors[0]->y = newRoom->position.y;
    //BOTTOM DOOR
    newRoom->doors[1] = malloc(sizeof(Position));
    newRoom->doors[1]->x = rand() % (width - 2) + newRoom->position.x + 1;
    newRoom->doors[1]->y = newRoom->position.y + newRoom->height - 1;
    //LEFT DOOR
    newRoom->doors[2] = malloc(sizeof(Position));
    newRoom->doors[2]->y = rand() % (height - 2) + newRoom->position.y + 1;
    newRoom->doors[2]->x = newRoom->position.x;
    //RIGHT DOOR
    newRoom->doors[3] = malloc(sizeof(Position));
    newRoom->doors[3]->y = rand() % (height - 2) + newRoom->position.y + 1;
    newRoom->doors[3]->x = newRoom->position.x + width - 1;

    return newRoom;
}

//Ill be honest I have no clue how I got this to work but it makes sense except for the last part.
int drawRoom(Room * room)
{
    int x;
    int y;

    /*Draw top and Bottom*/
    for (x = room->position.x; x < room->position.x + room->width; x++)
    {
        mvprintw(room->position.y, x, "-");
        mvprintw(room->position.y + room->height - 1, x, "-"); // Goes down height positions and print horizontally
    }

    /*Draw floors and the side walls */
    for(y = room->position.y + 1; y < room->position.y + room->height - 1; y++) // y is initialized to 1 below itself, and then it draws until it has reached its height
    {
        //draw side walls
        mvprintw(y, room->position.x, "|");
        mvprintw(y, room->position.x + room->width - 1, "|");

        //Draw Floors
        //Start 1 right from x, print . until the next wall which is xpos + width - 1
        for (x = room->position.x + 1; x < room->position.x + room->width - 1; x++)
        {
            mvprintw(y, x, ".");
        }

    }
    //Draw doors
    mvprintw(room->doors[0]->y, room->doors[0]->x, "+");
    mvprintw(room->doors[1]->y, room->doors[1]->x, "+");
    mvprintw(room->doors[2]->y, room->doors[2]->x, "+");
    mvprintw(room->doors[3]->y, room->doors[3]->x, "+");

    return 0;
}

Player * playerSetup()
{
    Player * newPlayer; //Create new Player named newPlayer
    newPlayer = malloc(sizeof(Player)); // Create the memory for newPlayer pointer

    //init player loc/hp
    newPlayer->health = 20;
    newPlayer->position.x = 41;
    newPlayer->position.y = 11;
    //initial player spawn
    playerMove(11, 41, newPlayer);

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
            newY = user->position.y - 1;
            newX = user->position.x;
            break;
        //move down
        case 's':
        case 'S':
            newY = user->position.y + 1;
            newX = user->position.x;
            break;
        //move left
        case 'a':
        case 'A':
            newY = user->position.y;
            newX = user->position.x - 1;
            break;
        //move right
        case 'd':
        case 'D':
            newY = user->position.y;
            newX = user->position.x + 1;
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

        default: // If it is not a ., move the cursor back
            move(user->position.y, user->position.x);
            break;

    }

}


int playerMove(int y, int x, Player * user)
{
    mvprintw(user->position.y, user->position.x, "."); //Print a '.' where the user currently is

    user->position.x = x; //Set new position for user
    user->position.y = y;

    mvprintw(user->position.y, user->position.x, "@"); // Set users pic
    move(user->position.y, user->position.x); //Move cursor to current users position
}