#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SONGS 100
#define MAX_NAME_LEN 50

typedef struct {
    int user_id;
    char song_name[MAX_NAME_LEN];
} Song;

typedef struct {
    Song queue[MAX_SONGS];
    int front;
    int rear;
    int size;
} RoundRobinScheduler;

// Initialize the scheduler
void initialize_scheduler(RoundRobinScheduler *scheduler) {
    scheduler->front = 0;
    scheduler->rear = -1;
    scheduler->size = 0;
}

// Add a song to the scheduler
void add_song(RoundRobinScheduler *scheduler, int user_id, const char *song_name) {
    if (scheduler->size == MAX_SONGS) {
        printf("Error: Queue is full!\n");
        return;
    }
    scheduler->rear = (scheduler->rear + 1) % MAX_SONGS;
    scheduler->queue[scheduler->rear].user_id = user_id;
    strncpy(scheduler->queue[scheduler->rear].song_name, song_name, MAX_NAME_LEN - 1);
    scheduler->queue[scheduler->rear].song_name[MAX_NAME_LEN - 1] = '\0';
    scheduler->size++;
}

// Get the next song in the scheduler
Song get_next_song(RoundRobinScheduler *scheduler) {
    if (scheduler->size == 0) {
        printf("Error: Queue is empty!\n");
        Song empty_song = {0, ""};
        return empty_song;
    }
    Song next_song = scheduler->queue[scheduler->front];
    scheduler->front = (scheduler->front + 1) % MAX_SONGS;
    scheduler->size--;
    return next_song;
}

// Remove songs by a specific user
void remove_user_songs(RoundRobinScheduler *scheduler, int user_id) {
    int count = scheduler->size;
    int temp_front = scheduler->front;
    RoundRobinScheduler temp;
    initialize_scheduler(&temp);

    for (int i = 0; i < count; i++) {
        Song current_song = scheduler->queue[temp_front];
        temp_front = (temp_front + 1) % MAX_SONGS;
        if (current_song.user_id != user_id) {
            add_song(&temp, current_song.user_id, current_song.song_name);
        }
    }

    *scheduler = temp;
}

// Print the current queue
void print_queue(RoundRobinScheduler *scheduler) {
    int temp_front = scheduler->front;
    printf("Current Queue:\n");
    for (int i = 0; i < scheduler->size; i++) {
        Song current_song = scheduler->queue[temp_front];
        printf("User %d: %s\n", current_song.user_id, current_song.song_name);
        temp_front = (temp_front + 1) % MAX_SONGS;
    }
}