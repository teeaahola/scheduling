#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// helper function for input validation in addMeeting and deleteMeeting
// used to check whether a given string contains a number
int isNumber(char *str)
{
    char *ptr = str;
    if (*str == '-')
    {
        ptr++;
    }
    while (*ptr)
    {
        if (!isdigit(*ptr))
        {
            return 0;
        }
        ptr++;
    }
    return 1;
}

void addMeeting(char *str, Meeting **calendar, int fromFile)
{
    // allocate memory for the event description and time
    // since the input string can be up to 1000 characters long and we do not know how
    // long the individual components are, each component is allocated 1000 (+ terminating
    // null character) bytes initially
    char *desc = (char *)malloc(1001);
    char *dayStr = (char *)malloc(1001);
    char *monthStr = (char *)malloc(1001);
    char *hourStr = (char *)malloc(1001);
    if (!desc || !dayStr || !monthStr || !hourStr)
    {
        printf("Memory allocation failed.");
        return;
    }
    // extract data from input string
    int scanned;
    if (fromFile)
    {
        scanned = sscanf(str, "%s %[^.].%s at %s\n", desc, dayStr, monthStr, hourStr);
    }
    else
    {
        scanned = sscanf(str, "%s %s %s %s", desc, monthStr, dayStr, hourStr);
    }
    // validate number of scanned values
    if (scanned != 4)
    {
        if (fromFile)
        {
            printf("Each event should have a description, day, month and time.\n");
        }
        else
        {
            printf("A should be followed by exactly 4 arguments.\n");
        }
        free(desc);
        free(dayStr);
        free(monthStr);
        free(hourStr);
        return;
    }
    // validate that the given date and time are numbers
    if (!isNumber(dayStr) || !isNumber(monthStr) || !isNumber(hourStr))
    {
        printf("Date-time parts must be numeric.");
        free(desc);
        free(dayStr);
        free(monthStr);
        free(hourStr);
        return;
    }
    // convert date and time to integers
    int day = atoi(dayStr);
    int month = atoi(monthStr);
    int hour = atoi(hourStr);
    free(dayStr);
    free(monthStr);
    free(hourStr);
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
    Meeting *new = (Meeting *)malloc(sizeof(Meeting));
    if (!new)
    {
        printf("Memory allocation failed.");
        free(desc);
        return;
    }
    new->description = (char *)malloc(strlen(desc) + 1);
    if (!new->description)
    {
        printf("Memory allocation failed.");
        free(desc);
        return;
    }
    strcpy(new->description, desc);
    free(desc);
    new->month = month;
    new->day = day;
    new->hour = hour;
    // check if the new meeting should be the first one in the database
    if (!((*calendar)) || (new->month < (*calendar)->month) || ((new->month == (*calendar)->month) && (new->day < (*calendar)->day || ((new->day == (*calendar)->day &&new->hour < (*calendar)->hour)))))
    {
        new->next = *calendar;
        *calendar = new;
    }
    else
    // add the meeting to the database in order
    {
        curr = *calendar;
        while (curr->next && !((new->month < curr->next->month) || ((new->month == curr->next->month) && (new->day < curr->next->day || ((new->day == curr->next->day &&new->hour < curr->next->hour))))))
        {
            curr = curr->next;
        }
        new->next = curr->next;
        curr->next = new;
    }
    if (fromFile)
    {
        return;
    }
    printf("SUCCESS\n");
}

void deleteMeeting(char *str, Meeting **calendar)
{
    // extract the time of the meeting to be deleted and validate arguments
    // since the input string can be up to 1000 characters long and we do not know how
    // long the individual components are, each component is allocated 1000 (+ terminating
    // null character) bytes initially
    char *dayStr = (char *)malloc(1001);
    char *monthStr = (char *)malloc(1001);
    char *hourStr = (char *)malloc(1001);
    int scanned = sscanf(str, "%s %s %s", monthStr, dayStr, hourStr);
    if (scanned != 3)
    {
        printf("D should be followed by exactly 3 arguments.\n");
        free(dayStr);
        free(monthStr);
        free(hourStr);
        return;
    }
    // validate that the given date and time are numbers
    if (!isNumber(dayStr) || !isNumber(monthStr) || !isNumber(hourStr))
    {
        printf("Date-time parts must be numeric.");
        free(dayStr);
        free(monthStr);
        free(hourStr);
        return;
    }
    // convert date and time to integers
    int day = atoi(dayStr);
    int month = atoi(monthStr);
    int hour = atoi(hourStr);
    free(dayStr);
    free(monthStr);
    free(hourStr);
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
        printf("Calendar is empty.\n");
        return;
    }
    // delete given meeting
    if ((*calendar)->month == month && (*calendar)->day == day && (*calendar)->hour == hour)
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
            printf("The time slot %02d.%02d at %02d is not in the calendar.\n", day, month, hour);
            return;
        }
        Meeting *temp = curr->next;
        curr->next = curr->next->next;
        free(temp->description);
        free(temp);
    }
    printf("SUCCESS\n");
}

void printTo(Meeting *calendar, FILE *stream)
{
    Meeting *curr = calendar;
    while (curr)
    {
        // print each calendar entry to stream
        fprintf(stream, "%s %02d.%02d at %02d\n", curr->description, curr->day, curr->month, curr->hour);
        curr = curr->next;
    }
    printf("SUCCESS\n");
}

void saveFile(Meeting **calendar, char *filename)
{
    // strip newline character from given filename
    filename[strcspn(filename, "\n")] = 0;
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf("Error opening file %s for writing.\n", filename);
        free(filename);
        return;
    }
    // print calendar to file
    printTo(*calendar, file);
    if (ferror(file))
    {
        printf("Error handling file %s.", filename);
        fclose(file);
        return;
    }
    fclose(file);
}

void loadCalendar(Meeting **calendar, char *filename)
{
    // strip newline character from given filename
    filename[strcspn(filename, "\n")] = 0;
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Cannot open file %s for reading.\n", filename);
        return;
    }
    // clear current calendar
    quit(calendar);
    // assume the input string is at most 1000 characters long
    char *str = (char *)malloc(1000 * sizeof(char));
    while (fgets(str, 1000, file))
    {
        // add the new meeting to the calendar
        addMeeting(str, calendar, 1);
    }
    free(str);
    if (ferror(file))
    {
        printf("Error handling file %s.", filename);
        fclose(file);
        return;
    }
    fclose(file);
    printf("SUCCESS\n");
}

void quit(Meeting **calendar)
{
    Meeting *curr = *calendar;
    while (curr)
    {
        Meeting *temp = curr;
        curr = curr->next;
        free(temp->description);
        free(temp);
    }
    *calendar = NULL;
    // the quit function does not print out "SUCCESS" so that it can be called from loadCalendar
    // instead it is printed out in the main function
}

int main(void)
{
    // initialise linked list to store database
    Meeting *calendar = NULL;
    // assume the input string is at most 1000 characters long
    char *str = (char *)malloc(1000 * sizeof(char));
    char command;
    int quitLoop = 0;
    while (!quitLoop)
    {
        // read input
        fgets(str, 1000, stdin);
        if (!*str)
        {
            printf("Issue reading command.\n");
        }
        // chech whether given command follow guidelines
        int scanned = sscanf(str, "%c", &command);
        if (scanned != 1)
        {
            printf("Issue parsing command.");
        }
        if (!isspace(str[1]))
        {
            printf("Invalid command %s", str);
            continue;
        }
        // execute command
        switch (command)
        {
        case 'A': // add meeting to database
            addMeeting(str + 2, &calendar, 0);
            break;
        case 'D': // delete meeting from database
            deleteMeeting(str + 2, &calendar);
            break;
        case 'L': // print calendar
            printTo(calendar, stdout);
            break;
        case 'W': // save calendar to file
            saveFile(&calendar, str + 2);
            break;
        case 'O': // load calendar from file
            loadCalendar(&calendar, str + 2);
            break;
        case 'Q': // quit program
            quitLoop = 1;
            free(str);
            quit(&calendar);
            printf("SUCCESS\n");
            break;
        default: // unknown command
            printf("Invalid command %s", str);
            break;
        }
    }
    return 0;
}
