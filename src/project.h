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

void addMeeting();
void deleteMeeting();
void printCalendar();
void saveCalendar();
void loadCalendar();
void quit();

#endif //! _PROJECT__H_
