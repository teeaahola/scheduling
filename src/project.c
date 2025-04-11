#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void addMeeting(char *str, Meeting **calendar, int *size)
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
        Meeting curr = (*calendar)[i];
        if (curr.month == month && curr.day == day && curr.hour == hour)
        {
            printf("Cannot add meeting to occupied time slot.\n");
            return;
        }
    }
    // allocate memory for new meeting and copy its information
    (*size)++;
    Meeting *temp = (Meeting *)realloc(*calendar, *size * sizeof(Meeting));
    if (!temp)
    {
        printf("Memory allocation failed.");
        return;
    }
    *calendar = temp;
    // Meeting *curr = &calendar[*size - 1];
    (*calendar)[*size - 1].description = malloc(strlen(desc) + 1);
    strcpy((*calendar)[*size - 1].description, desc);
    (*calendar)[*size - 1].month = month;
    (*calendar)[*size - 1].day = day;
    (*calendar)[*size - 1].hour = hour;
    printf("SUCCESS!\n");
}

void deleteMeeting(char *str, Meeting *calendar, int *size)
{
    printf("delete!\n");
    printf("SUCCESS!\n");
}

void printTo(Meeting *calendar, FILE *stream, int *size)
{
    // sort the calendar in order of meeting time
    // print each entry
    for (int i = 0; i < *size; i++)
    {
        Meeting curr = calendar[i];
        fprintf(stream, "%s %02d.%02d at %02d\n", curr.description, curr.day, curr.month, curr.hour);
    }
    printf("SUCCESS!\n");
}

void saveFile(char *str, Meeting *calendar, int *size)
{
    char *txt;
    txt = ".txt";
    char filename[100]; // fix implementation
    int scanned = sscanf(str, "W %s\n", filename);
    if (scanned != 1)
    {
        printf("Incorrect number of arguments for 'W': expected 1 but received %d.\n", scanned);
        return;
    }
    strcat(filename, txt);
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf("Error opening file %s for writing.\n", filename);
        return;
    }
    printTo(calendar, file, size);
    fclose(file);
}

void loadCalendar(Meeting *calendar, char *filename, int *size)
{
    // strip beginning of command
    FILE *file = fopen(filename, "r");
    // count number of lines (= number of meetings) in the file
    int i = 0;
    if (!file)
    {
        printf("Error opening file %s.", filename);
        return;
    }
    int chr;
    chr = fgetc(file);
    int prev = chr;
    while (chr)
    {
        if (chr == '\n')
        {
            i++;
        }
        if (chr == EOF)
        {
            if (prev == '\n')
            {
                break;
            }
            else
            {
                if (prev == EOF)
                {
                    break;
                }
                i++;
                break;
            }
        }
        prev = chr;
        chr = fgetc(file);
    }
    *size = i;
    rewind(file);
    calendar = (Meeting *)malloc(*size * sizeof(Meeting));
    for (int j = 0; j < *size; j++)
    {
        char *str = (char *)calloc(*size, sizeof(Meeting));
        fgets(str, 1000, file);
        Meeting curr = calendar[i];
        int scanned = sscanf(str, "%s %d.%d at %d\n", curr.description, &curr.day, &curr.month, &curr.hour);
    }
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
    int size = 0;
    char *str = (char *)malloc(1000 * sizeof(char));
    char command;
    int quitLoop = 0;
    while (!quitLoop)
    {
        fgets(str, 1000, stdin); // read input
        if (!*str)
        {
            printf("Issue reading command.\n");
        }
        int scanned = sscanf(str, "%c", &command);
        if (scanned != 1)
        {
            printf("Issue parsing command.");
        }
        if (!isspace(str[1]))
        {
            printf("Invalid command %s\n", str);
            continue;
        }
        switch (command)
        {
        case 'A': // add meeting to database
            addMeeting(str, &calendar, &size);
            break;
        case 'D': // delete meeting from database
            deleteMeeting(str, calendar, &size);
            break;
        case 'L': // print calendar
            printTo(calendar, stdout, &size);
            break;
        case 'W': // save calendar to file
            saveFile(str, calendar, &size);
            break;
        case 'O': // load meetings from file
            loadCalendar(calendar, str, &size);
            break;
        case 'Q': // quit program
            quitLoop = 1;
            free(str);
            quit(calendar);
            break;
        default: // unknown command
            printf("Invalid command %s", str);
            break;
        }
    }
    printf("successful run\n");
    return 0;
}
