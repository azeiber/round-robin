#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scheduler.h"


void initialize_scheduler(RRSongScheduler *scheduler, int quantum, int context_switch) //Function to initialize the round-robin song scheduler
{
    scheduler->song_count = 0; //Initializes the number of songs to 0
    scheduler->current_time = 0; //Initializes the current time to 0
    scheduler->quantum_time = quantum; //Sets the quantum time for the scheduler
    scheduler->context_switch_time = context_switch; //Sets the context switch time
}


void add_song(RRSongScheduler *scheduler, int user_id, const char *song_name) //Function to add a song to the scheduler 
{
    if (scheduler->song_count >= MAX_SONGS) //Checks if the scheduler has reached its maximum capacity
    {
        printf("Cannot add more songs. Playlist is full.\n");
        return; //Exit if playlist is full
    }
    Song *song = &scheduler->songs[scheduler->song_count]; //Adds song details to the next available slot in the scheduler
    song->user_id = user_id; //Sets the user ID for the song
    strncpy(song->song_name, song_name, MAX_NAME_LEN - 1); //Copies the song name with bounds checking
    song->song_name[MAX_NAME_LEN - 1] = '\0'; //Ensures the string is null-terminated
    song->arrival_time = scheduler->current_time; //Records the arrival time
    song->remaining_time = 3; //Sets default duration (assume each song plays for 3 time units)
    song->start_time = -1; //Initializes start time as not yet started
    song->completion_time = -1; //Initializes completion time as not completed

    scheduler->song_count++; //Increments the song count
}

void run_song_scheduler(RRSongScheduler *scheduler) //Function to run the round-robin scheduling algorithm for songs
{
    int completed_songs = 0; //Tracks the number of completed songs
    int current_song_index = 0; //Index of the song currently being processed

    while (completed_songs < scheduler->song_count) //Loops until all songs are completed
    {
        Song *current_song = &scheduler->songs[current_song_index];

        if (current_song->remaining_time <= 0) //Skips songs that have already been played
        {
            current_song_index = (current_song_index + 1) % scheduler->song_count; //Moves to the next song
            continue; //Continues to the next iteration
        }

       if (current_song->start_time == -1) //Marks the start time if this is the first play of the song
        {
            current_song->start_time = scheduler->current_time;
        }

        int play_time = (current_song->remaining_time < scheduler->quantum_time) ? current_song->remaining_time : scheduler->quantum_time;

        printf("Now playing: User %d - %s (Time: %d)\n",current_song->user_id, current_song->song_name, scheduler->current_time);  //Simulates playing the song and display its details

        current_song->remaining_time -= play_time; //Decreases the remaining time
        scheduler->current_time += play_time; //Updates the current time

       
        scheduler->current_time += scheduler->context_switch_time; //Account for context switch overhead

        if (current_song->remaining_time <= 0) //If the song has finished, record the completion time and update completed count
        {
            current_song->completion_time = scheduler->current_time;
            completed_songs++;
        }

        current_song_index = (current_song_index + 1) % scheduler->song_count; //Move to the next song in a circular queue manner
    }

}

void print_song_metrics(RRSongScheduler *scheduler) //Function to display metrics for all songs in the scheduler
{
    printf("\nPlaylist Metrics:\n");
    printf("--------------------------------------------------------\n");
    printf("User\tSong\t\tArrival\tStart\tComplete\n");
    
    for (int i = 0; i < scheduler->song_count; i++) //Iterates through all songs and display their details
    {
        Song *s = &scheduler->songs[i];
        printf("%d\t%-15s\t%d\t%d\t%d\n", s->user_id, s->song_name, s->arrival_time, s->start_time, s->completion_time);
    }
}

void remove_user_songs(RRSongScheduler *scheduler, int user_id) //Function to remove all songs by a specific user
{
    RRSongScheduler temp; //Temporary scheduler to store remaining songs
    initialize_scheduler(&temp, scheduler->quantum_time, scheduler->context_switch_time); //Initializes temporary scheduler

    for (int i = 0; i < scheduler->song_count; i++) //Copies songs not matching the given user ID to the temporary scheduler
    {
        if (scheduler->songs[i].user_id != user_id) 
        {
            add_song(&temp, scheduler->songs[i].user_id, scheduler->songs[i].song_name);
        }
    }

    *scheduler = temp; //Replacess the original scheduler with the filtered one
}

