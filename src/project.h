#ifndef _PROJECT__H_
#define _PROJECT__H_

/* structure to maintain meetings in a calendar */
typedef struct
{
    char *description;
    int month;
    int day;
    int hour;
} Meeting;

void addMeeting(char *str, Meeting *calendar, int *size);
void deleteMeeting(char *str, Meeting *calendar, int *size);
void printCalendar(Meeting *calendar);
void saveCalendar(Meeting *calendar, char *filename);
void loadCalendar(Meeting *calendar, char *filename);
void quit(Meeting *calendar);

#endif //! _PROJECT__H_
