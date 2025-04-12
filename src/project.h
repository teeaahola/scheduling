#ifndef _PROJECT__H_
#define _PROJECT__H_
#include <stdio.h>

/* linked list structure to maintain meetings in a calendar */
typedef struct meeting
{
    char *description;
    int month;
    int day;
    int hour;
    struct meeting *next;
} Meeting;

// functions to manage the database
void addMeeting(char *str, Meeting **calendar, int *size);
void deleteMeeting(char *str, Meeting **calendar, int *size);
//  void printTo(Meeting *calendar, FILE *stream, int *size);
//  void saveFile(char *str, Meeting *calendar, int *size);
//  void loadCalendar(Meeting *calendar, char *filename, int *size);
void quit(Meeting *calendar);

#endif //! _PROJECT__H_
