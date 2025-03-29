#include "project.h"
#include <stdio.h>
#include <stdlib.h>

void addMeeting()
{
    printf("add!\n");
}

void deleteMeeting()
{
    printf("delete!\n");
}

void printCalendar()
{
    printf("print!\n");
}

void saveCalendar()
{
    printf("save!\n");
}

void loadCalendar()
{
    printf("load!\n");
}

void quit()
{
    printf("quit!\n");
}

int main(void)
{
    char *str = (char *)malloc(1000 * sizeof(char));

    int quitLoop = 0;
    while (!quitLoop)
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
            addMeeting();
            break;
        case 'D': // delete meeting from database
            deleteMeeting();
            break;
        case 'L': // print calendar
            printCalendar();
            break;
        case 'W': // save calendar to file
            saveCalendar();
            break;
        case 'O': // load meetings from file
            loadCalendar();
            break;
        case 'Q': // quit program
            quitLoop = 1;
            free(str);
            quit();
            break;
        default: // unknown command
            printf("Invalid command %s\n", str);
            break;
        }
    }
    printf("successful run\n");
    return 0;
}
