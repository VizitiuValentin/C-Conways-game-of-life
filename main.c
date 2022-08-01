#include "GOL_header.h"

int main()
{
    int linii, coloane;
    int i,j;

    srand( time(0) );
    system("cls");
    /*
    printf("How big do you want the \"WORLD\" to be? (35 x 160 recommended)\nLinii: ");
    scanf("%d", &linii);
    printf("Coloane: ");
    scanf("%d", &coloane);
    */

    linii = 35;
    coloane = 160;
//========================================================================

    char choise;
    printf("Do you want to put the cells manually or do you want a random amount of cells to be scattered of the board?\n\n");
    printf( GREEN "A. MANUAL\n" YELLOW  "B. AUTOMATIC\n" RESET "========================\n> ");
    for(;;)
    {
         scanf("%c", &choise);
         choise = toupper(choise);
         if (choise == 'B' || choise == 'A') break;
         printf("Invalid option. Please type the letter next tot the choice's name and press ENTER.\n");
         system("cls");
    }



    printf("Use WASD to move around and press SPACE to place a mob.\n"
           "Just walk into a mob to delete it\nPress ENTER when done!\n"
           "PLEASE have 16 font size and full screen on a 1366x768 display\n");

    printf("3...");
    getch();
    printf("2...");
    getch();
    printf("1...");
    getch();

    char world[linii][coloane];

// Fills the world with random amount of mobs =====================================================================
if (choise == 'B')
    for (i=j=0; i < linii; )
    {
        if (rand() % 10 < 2) world[i][j] = ENTITY;
        else world[i][j] = ' ';
        j++;
        if (j == coloane)
        {
            world[i][coloane-1] = '\0';
            j = 0;
            i++;
        }
    }


// Fills the world with spaces ====================================================================================
if (choise == 'A')
    for (i=j=0; i < linii; )
    {
        world[i][j] = ' ';
        j++;
        if (j == coloane)
        {
            world[i][coloane-1] = '\0';
            j = 0;
            i++;
        }
    }

    char move, flag = 0;

    struct player player;
    player.x = linii/2;
    player.y = coloane/2;

    world[player.x][player.y] = GOD;


    while (1)
    {
        printWorld(linii, coloane, world);
        fflush(stdin);
        move = toupper(getch());

// Mob placing ====================================================================================
        switch(move)
        {

        case 'W':
            world[player.x][player.y] = ' ';
            player.x--;
            world[player.x][player.y] = GOD;
            break;
        case 'S':
            world[player.x][player.y] = ' ';
            player.x++;
            world[player.x][player.y] = GOD;
            break;
        case 'A':
            world[player.x][player.y] = ' ';
            player.y--;
            world[player.x][player.y] = GOD;
            break;
        case 'D':
            world[player.x][player.y] = ' ';
            player.y++;
            world[player.x][player.y] = GOD;
            break;
        case ' ':
            world[player.x][player.y] = ENTITY;
            player.y++;
            world[player.x][player.y] = GOD;
            break;
        case 13:
            flag = 1;
            default: break;
        }
        if (flag == 1)
        {
            world[player.x][player.y] = ' ';
            break;
        }
    }
// Actual game running;
/*
1 - Any live cell with fewer than two live neighbours dies, as if by underpopulation.
2 - Any live cell with two or three live neighbours lives on to the next generation.
3 - Any live cell with more than three live neighbours dies, as if by overpopulation.
4 - Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
*/
//=================================================================================
int neighbour_count;
char copy_world[linii][coloane];
int generation = 0;

for (;;){
    // Copies the array
    for (i=j=0; i < linii; )
    {
        copy_world[i][j] = world[i][j];
        j++;
        if (j == coloane)
        {
            copy_world[i][coloane-1] = '\0';
            j = 0;
            i++;
        }
    }
    printWorld(linii, coloane, world);
    printf("Generation number: %d", generation);
    generation++;
    // delay(0.2);
//=================================================================================
    // Calculates the number of cells around each cell, one by one
        for (i=j=0; i < linii; )
    {
        // Checks all 8 titles around the one we are looking at now, if it has a mob on it, we add aneighbour
        neighbour_count = 0;
        if (copy_world[i-1][j] == ENTITY) neighbour_count++;
        if (copy_world[i+1][j] == ENTITY) neighbour_count++;
        if (copy_world[i][j+1] == ENTITY) neighbour_count++;
        if (copy_world[i][j-1] == ENTITY) neighbour_count++;

        if (copy_world[i-1][j+1] == ENTITY) neighbour_count++;
        if (copy_world[i+1][j-1] == ENTITY) neighbour_count++;
        if (copy_world[i+1][j+1] == ENTITY) neighbour_count++;
        if (copy_world[i-1][j-1] == ENTITY) neighbour_count++;

        if (neighbour_count < 2) world[i][j] = ' '; // Dies because of underpopulation
        else if (neighbour_count == 3)  world[i][j] = ENTITY; // Becomes alive
        else if (neighbour_count > 3) world[i][j] = ' '; // Dies because of overpopulation


        j++;
        if (j == coloane-1)
        {
            j = 0;
            i++;
        }

    } // CALCULATION LOOP END
} // GAMEPLAY FOR LOOP END


} // END MAIN
//=================================================================================


void printWorld (int linii, int coloane, char world[][coloane])
{
    system("cls");
    int i,j;

    for (i = 0; i < coloane+1; i++) printf("%c", BORDER);
    printf("\n");

    for (i=0; i < linii; i++)
    {
        printf("%c", BORDER);
        printf("%s", world[i]);
        printf("%c\n", BORDER);
    }
    for (i = 0; i < coloane+1; i++) printf("%c", BORDER);
    printf("\n");
}

void delay(double number_of_seconds)
{
    // Converting time into milli_seconds
    double milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}
