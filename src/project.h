#ifndef _PROJECT__H_
#define _PROJECT__H_
#include <stdio.h>

/* structure to maintain meetings in a calendar */
typedef struct
{
    char *description;
    int month;
    int day;
    int hour;
} Meeting;

void addMeeting(char *str, Meeting **calendar, int *size);
void deleteMeeting(char *str, Meeting *calendar, int *size);
void printTo(Meeting *calendar, FILE *stream, int *size);
void loadCalendar(Meeting *calendar, char *filename, int *size);
void quit(Meeting *calendar);

#endif //! _PROJECT__H_
