#include "project.h"
#include <stdio.h>
#include <stdlib.h>

void addMeeting(char *str, Meeting *calendar, int *size)
{
    char desc[100]; // fix implementation
    int day, month, hour;
    int scanned = sscanf(str, "A %s %d %d %d", desc, &month, &day, &hour);
    if (scanned != 4)
    {
        printf("Incorrect number of arguments for 'A': expected 4 but received %d.\n", scanned);
        return;
    }
    //  check if date and time are acceptable
    if (month < 1 || month > 12)
    {
        printf("Month was %d but should be a value between 1 and 12\n", month);
        return;
    }
    if (day < 1 || day > 31)
    {
        printf("Day was %d but should be a value between 1 and 31\n", day);
        return;
    }
    if (hour < 0 || hour > 23)
    {
        printf("Hour was %d but should be a value between 0 and 23\n", hour);
        return;
    }
    // check for overlap between events
    for (int i = 0; i < *size; i++)
    {
        Meeting current = calendar[i];
        if (current.month == month && current.day == day && current.hour == hour)
        {
            printf("Cannot add meeting to occupied time slot.\n");
            return;
        }
        printf("iterating through loop: i = %d\n", i);
    }
    // allocate memory for new meeting and copy its information
    *size += 1;
    calendar = (Meeting *)realloc(calendar, *size);
    calendar[*size - 1].description = desc;
    calendar[*size - 1].month = month;
    calendar[*size - 1].day = day;
    calendar[*size - 1].hour = hour;
    printf("SUCCESS!\n");
}

void deleteMeeting(char *str, Meeting *calendar, int *size)
{
    printf("delete!\n");
    printf("SUCCESS!\n");
}

void printCalendar(Meeting *calendar)
{
    printf("print!\n");
    printf("SUCCESS!\n");
}

void saveCalendar(Meeting *calendar, char *filename)
{
    FILE *file = fopen(filename, "w");
    fclose(file);
    printf("save!\n");
    printf("SUCCESS!\n");
}

void loadCalendar(Meeting *calendar, char *filename)
{
    FILE *file = fopen(filename, "r");
    fclose(file);
    printf("load!\n");
    printf("SUCCESS!\n");
}

void quit(Meeting *calendar)
{
    printf("quit!\n");
    printf("SUCCESS!\n");
}

int main(void)
{
    Meeting *calendar = (Meeting *)malloc(sizeof(Meeting)); // array to store database
    int *size;
    size = 0;
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
        int scanned = sscanf(str, "%c", &command);
        if (scanned != 1)
        {
            printf("Issue parsing command.");
        }
        // fix reading input so does not accept 'Add' for 'A'
        switch (command)
        {
        case 'A': // add meeting to database
            addMeeting(str, calendar, &size);
            break;
        case 'D': // delete meeting from database
            deleteMeeting(str, calendar, &size);
            break;
        case 'L': // print calendar
            printCalendar(calendar);
            break;
        case 'W': // save calendar to file
            saveCalendar(calendar, str);
            break;
        case 'O': // load meetings from file
            loadCalendar(calendar, str);
            break;
        case 'Q': // quit program
            quitLoop = 1;
            free(str);
            quit(calendar);
            break;
        default: // unknown command
            printf("Invalid command %s\n", str);
            break;
        }
    }
    printf("successful run\n");
    return 0;
}
