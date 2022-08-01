#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>

#define ENTITY 'O'
#define GOD 219
#define BORDER 178

// Colors for printf
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m" // Resets the color to normal

void printWorld (int linii, int coloane, char world[][coloane]);
void delay(double number_of_seconds);

struct player
{
    int x;
    int y;
};
