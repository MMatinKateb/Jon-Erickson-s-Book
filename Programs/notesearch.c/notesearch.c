#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "hacking.h"

#define FILENAME "/var/notes"

int print_notes(int, int, char *);
int find_user_note(int, int);
int search_note(char *, char *);
void fatal(char *);

int main(int argc, char *argv[]) {
    int userid, printing = 1, fd;   // File descriptor
    char searchstring[100];

    if (argc > 1)                       // If there is an arg,
        strcpy(searchstring, argv[1]);  // that is the search string;
    else                                // Otherwise,
        searchstring[0] = 0;            // search string is empty
    
    userid = getuid();
    fd = open(FILENAME, O_RDONLY);      // Open file for read-only access
    if (fd == -1)
        fatal("in main() while opening file for reading");

    while(printing)
        printing = print_notes(fd, userid, searchstring);
    printf("-------[ end of note data ]-------\n");
    close(fd);
}

// A function to print the notes for a given uid that match
// an optional search string;
// returns 0 at end of file, 1 if there are still more notes.
int print_notes(int fd, int uid, char *searchstring) {
    int note_length;
    char byte = 0, note_buffer[100];
    
    note_length = find_user_note(fd, uid);
    if (note_length == -1)  // If end of file reached,
        return 0;           // return 0.

    read(fd, note_buffer, note_length); // Read note data.
    note_buffer[note_length] = 0;       // Terminate the string

    if (search_note(note_buffer, searchstring))     // If search string found
        printf(note_buffer);                        // print the note.
    return 1;
}

// A function to find the next note for a given userID;
// returns -1 if the end of the file is reached;
// otherwise, it returns the length of the found note.
int find_user_note(int fd, int user_id) {
    int note_uid = -1;
    unsigned char byte;
    int length;

    while(note_uid != user_id)
}