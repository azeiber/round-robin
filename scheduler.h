#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdio.h>  // Include this only if necessary for I/O functions
#include <string.h> // For string functions

#define MAX_SONGS 100
#define MAX_NAME_LEN 50

// Song structure to store song information
typedef struct {
    int user_id;                 // ID of the user who added the song
    char song_name[MAX_NAME_LEN]; // Name of the song
} Song;

// Scheduler structure to implement the round-robin queue
typedef struct {
    Song queue[MAX_SONGS];  // Array to store the song queue
    int front;              // Index of the first song in the queue
    int rear;               // Index of the last song in the queue
    int size;               // Current size of the queue
} RoundRobinScheduler;

// Function declarations
void initialize_scheduler(RoundRobinScheduler *scheduler);
void add_song(RoundRobinScheduler *scheduler, int user_id, const char *song_name);
Song get_next_song(RoundRobinScheduler *scheduler);
void remove_user_songs(RoundRobinScheduler *scheduler, int user_id);
void print_queue(RoundRobinScheduler *scheduler);

#endif // SCHEDULER_H
