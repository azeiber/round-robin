#ifndef RR_SCHEDULER_H
#define RR_SCHEDULER_H

#include <stdio.h> //Standard I/O library for printing and input
#define MAX_SONGS 100 //Maximum number of songs in the scheduler
#define MAX_NAME_LEN 50 //Maximum length for song names

typedef struct //Structure to represent a song with relevant metadata
{
    int user_id; //Unique identifier for the user who added the song
    char song_name[MAX_NAME_LEN]; //Name of the song, stored as a string
    int arrival_time;  //Time when the song was added to the scheduler
    int remaining_time; //Remaining playtime for the song
    int start_time;     //Time when the song starts playing for the first time
    int completion_time; //Time when the song finishes playing
} Song;

typedef struct //Structure to represent the round-robin song scheduler
{
    Song songs[MAX_SONGS];  //Array to store all songs in the scheduler
    int song_count;   //Current count of songs in the scheduler
    int current_time;  //Scheduler's internal clock to track time
    int quantum_time;  //Time slice for each song's turn in the scheduler
    int context_switch_time;  //Overhead time added when switching between songs
} RRSongScheduler;

void initialize_scheduler(RRSongScheduler *scheduler, int quantum, int context_switch); //Initializes the scheduler with given quantum and context switch times

void add_song(RRSongScheduler *scheduler, int user_id, const char *song_name); //Adds a new song to the scheduler for a specific user

void run_song_scheduler(RRSongScheduler *scheduler); //Runs the round-robin scheduling process to play songs

void print_song_metrics(RRSongScheduler *scheduler); //Prints metrics for all songs, including start and completion times

void remove_user_songs(RRSongScheduler *scheduler, int user_id); //Removes all songs associated with a specific user from the scheduler

#endif