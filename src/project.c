#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void addMeeting(char *str, Meeting **calendar, int *size)
{
    // allocate memory for the event description based on string length
    char *space;
    space = " ";
    int len = strcspn(str, space);
    char *desc = (char *)malloc(len + 1);
    if (!desc)
    {
        printf("Memory allocation failed.");
        return;
    }
    int day, month, hour;
    int scanned = sscanf(str, "%s %d %d %d", desc, &month, &day, &hour);
    // validate number of scanned values
    if (scanned != 4)
    {
        printf("A should be followed by exactly 4 arguments.\n");
        free(desc);
        return;
    }
    //  check if date and time are acceptable
    if (month < 1 || month > 12)
    {
        printf("Month cannot be less than 1 or greater than 12.\n");
        free(desc);
        return;
    }
    if (day < 1 || day > 31)
    {
        printf("Day cannot be less than 1 or greater than 31.\n");
        free(desc);
        return;
    }
    if (hour < 0 || hour > 23)
    {
        printf("Hour cannot be negative or greater than 23.\n");
        free(desc);
        return;
    }
    // check for overlap between events
    Meeting *curr = *calendar;
    while (curr)
    {
        if (curr->month == month && curr->day == day && curr->hour == hour)
        {
            printf("Cannot add meeting to occupied time slot.\n");
            free(desc);
            return;
        }
        curr = curr->next;
    }
    // allocate memory for new meeting
    (*size)++;
    Meeting *new = (Meeting *)malloc(sizeof(Meeting));
    if (!new)
    {
        printf("Memory allocation failed.");
        free(desc);
        return;
    }
    new->description = desc;
    new->month = month;
    new->day = day;
    new->hour = hour;
    // add meeting to the database in order
    if (!((*calendar)) || (new->month < (*calendar)->month) || ((new->month == (*calendar)->month) && (new->day < (*calendar)->day || ((new->day == (*calendar)->day &&new->hour < (*calendar)->hour)))))
    {
        new->next = *calendar;
        *calendar = new;
    }
    else
    {
        // Meeting *prev = calendar;
        curr = *calendar;
        while (curr->next && !((new->month < curr->next->month) || ((new->month == curr->next->month) && (new->day < curr->next->day || ((new->day == curr->next->day &&new->hour < curr->next->hour))))))
        {
            curr = curr->next;
        }
        // add new meeting to the database
        new->next = curr->next;
        curr->next = new;
    }
    printf("SUCCESS\n");
}

void deleteMeeting(char *str, Meeting **calendar, int *size)
{
    int day, month, hour;
    int scanned = sscanf(str, "%d %d %d", &month, &day, &hour);
    if (scanned != 3)
    {
        printf("D should be followed by exactly 3 arguments.\n");
        return;
    }
    //  check if date and time are acceptable
    if (month < 1 || month > 12)
    {
        printf("Month cannot be less than 1 or greater than 12.\n");
        return;
    }
    if (day < 1 || day > 31)
    {
        printf("Day cannot be less than 1 or greater than 31.\n");
        return;
    }
    if (hour < 0 || hour > 23)
    {
        printf("Hour cannot be negative or greater than 23.\n");
        return;
    }
    // check if the calendar is empty
    if (!(*calendar))
    {
        printf("Time slot %02d.%02d at %02d is not in the calendar.\n", day, month, hour);
        (*size)--; //
        return;
    }
    // check if the deleted node is the first one
    else if ((*calendar)->month == month && (*calendar)->day == day && (*calendar)->hour == hour)
    {
        Meeting *temp = *calendar;
        *calendar = (*calendar)->next;
        free(temp->description);
        free(temp);
    }
    else
    {
        Meeting *curr = *calendar;
        while (curr->next && !(curr->next->month == month && curr->next->day == day && curr->next->hour == hour))
        {
            curr = curr->next;
        }
        if (!curr->next)
        {
            printf("Time slot %02d.%02d at %02d is not in the calendar.\n", day, month, hour);
            return;
        }
        Meeting *temp = curr->next;
        curr->next = curr->next->next;
        free(temp->description);
        free(temp);
        (*size)--;
    }
    printf("SUCCESS\n");
}

void printTo(Meeting *calendar, FILE *stream)
{
    // sort the calendar in order of meeting time
    // print each entry
    Meeting *curr = calendar;
    while (curr)
    {
        fprintf(stream, "%s %02d.%02d at %02d\n", curr->description, curr->day, curr->month, curr->hour);
        curr = curr->next;
    }
    printf("SUCCESS\n");
}

void saveFile(char *str, Meeting *calendar)
{
    char *space;
    space = " \n";
    int len = strcspn(str, space);
    char *filename = (char *)malloc(len + 1);
    if (!filename)
    {
        printf("Memory allocation failed.");
        return;
    }
    int scanned = sscanf(str, "%s\n", filename);
    if (scanned != 1)
    {
        printf("Incorrect number of arguments for 'W': expected 1 but received %d.\n", scanned);
        free(filename);
        return;
    }
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf("Error opening file %s for writing.\n", filename);
        free(filename);
        return;
    }
    printTo(calendar, file);
    fclose(file);
    free(filename);
}
/*
void loadCalendar(Meeting **calendar, char *filename, int *size)
{
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
    // calendar = (Meeting *)malloc(*size * sizeof(Meeting));
    for (int j = 0; j < *size; j++)
    {
        char *str = (char *)calloc(*size, sizeof(Meeting));
        fgets(str, 1000, file); // fix
        Meeting *curr = (Meeting *)malloc(sizeof(Meeting));
        curr->next = NULL;
        int scanned = sscanf(str, "%s %d.%d at %d\n", curr->description, &curr->day, &curr->month, &curr->hour);
    }
    fclose(file);
    // error handling
    printf("SUCCESS\n");
}*/

void quit(Meeting *calendar)
{
    Meeting *curr = calendar;
    while (curr->next)
    {
        Meeting *temp = curr;
        curr = curr->next;
        free(temp->description);
        free(temp);
    }
    if (curr)
    {
        free(curr->description);
        free(curr);
    }
    printf("SUCCESS\n");
}

int main(void)
{
    // initialise linked list to store database
    Meeting *calendar = NULL; //(Meeting *)calloc(1, sizeof(Meeting));
    // calendar->next = NULL;
    int size = 0;
    // assume the input string is at most 1000 characters long
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
            addMeeting(str + 2, &calendar, &size);
            break;
        case 'D': // delete meeting from database
            deleteMeeting(str + 2, &calendar, &size);
            break;
        case 'L': // print calendar
            printTo(calendar, stdout);
            break;
        case 'W': // save calendar to file
            saveFile(str + 2, calendar);
            break;
        case 'O': // load meetings from file
            // loadCalendar(&calendar, str + 2, &size);
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
    return 0;
}
