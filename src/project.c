#include "project.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *str = (char *)malloc(1000 * sizeof(char));

    int quit = 0;
    while (!quit)
    {
        fgets(str, 1000, stdin); // read input
        if (!*str)
        {
            printf("Issue reading command.\n");
        }
        char command;
        int scanned = sscanf(str, "%s", &command);
        if (scanned != 1)
        {
            printf("Issue parsing command.");
        }
        switch (command)
        {
        case 'A': // add meeting to database
            printf("add!\n");
            break;
        case 'D': // delete meeting from database
            printf("delete!\n");
            break;
        case 'L': // print calendar
            printf("print!\n");
            break;
        case 'W': // save calendar to file
            printf("save!\n");
            break;
        case 'O': // load meetings from file
            printf("load!\n");
            break;
        case 'Q': // quit program
            quit = 1;
            free(str);
            printf("quit!\n");
            break;
        default: // unknown command
            printf("Invalid command %s\n", str);
            break;
        }
    }
    printf("successful run\n");
    return 0;
}
