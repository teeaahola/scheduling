# Description

A command line based scheduling system for scheduling one-hour meetings. A
meeting is represented with the following data:

- **description** is the description of the meeting, which is a string that can
  have arbitrary length but no whitespace characters.

- **month** is the month of the meeting time, which is an integer between 1
  and 12.

- **day** is the day of month of the meeting time, which is an integer between 1
  and 31.

- **hour** is hour of the day of the meeting time, which is an integer between 0
  and 23.

For the system, each meeting time must be unique.

# Commands

## Add meeting

Adds a new meeting to the system. The command has the following format.

`A <description> <month> <day> <hour>`

where the entries are the names of the meeting data fields.

For example, a valid add meeting command is as follows.

`A Haircut 3 26 14`

would reserve a meeting for haircutting on 26.3. at 14.

If the system has another meeting at the specified time, the meeting cannot be
scheduled.

## Delete meeting

Cancels (deletes) a scheduled meeting. The command has the following format.

`D <month> <day> <hour>`

where the entries are the time fields of the meeting data.

For example, a valid delete meeting command is as follows.

`D 3 26 14`

would delete the meeting added above.

If the system does not have a scheduled meeting at the specified time, the
program prints an error message.

## Print calendar

Displays the scheduled meetings. The command has the following format.

`L`

It prints the stored meetings on a separate line as follows.

`<description> <day>.<month> at <hour>`

where the entries are the names of the meeting data fields.

For example, print calendar command output is as follows.

```
Haircut 26.03 at 14
Exam 02.11 at 08
SUCCESS
```

The database entries are printed in the order of meeting time such that the
earlier meetings will be printed first.

## Save to file

Saves the database to a text file. The command has the following format.

`W <filename>`

where **\<filename>** is the name of the text file.

It writes the stored meetings on a separate line as follows.

`<description> <day>.<month> at <hour>`

where the entries are the names of the meeting data fields.

## Load from file

Loads meetings from a text file saved using **Save to file** command. The
command has the following format.

`O <filename>`

where **\<filename>** is the name of the text file.

It assumes the stored meetings are on a separate line in the format specified
above.

If the file is valid and loaded correctly, the current schedule is replaced with
the entries loaded from the file.

## Quit program

Releases all allocated memory and exits the program. The command has the
following format.

`Q`

# Example of possible command sequence.

```
A Haircut 3 26 14
A C-lecture 3 27 12
A C-exercise 3 27 14
A Math_lecture 3 26 14
D 3 26 14
A Math_lecture 3 26 14
L
W calendar.txt
Q
```

After this, the calendar saves the first three entries since the first
“Math_lecture” isn't successful because the time is already reserved in previous
entry. After the entry is deleted with the command “D”, adding the
“Math_lecture” is successful. After these, the calendar is printed and saved to
the text file “calendar.txt”.
