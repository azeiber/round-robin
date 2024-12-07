#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "scheduler.h"

int get_valid_integer(const char* prompt) //Function to get a valid integer input from the user
{
    int value; //Variable to store the validated integer
    char input[100]; //Buffer to hold the user's input

    while (1) 
    {
        printf("%s", prompt); //Displays the prompt to the user
    
        if (fgets(input, sizeof(input), stdin) == NULL) //Reads input from the user
        {
            printf("Error reading input. Please try again.\n");
            continue; //Retry if input reading fails
        }

        input[strcspn(input, "\n")] = 0; //Removes the trailing newline character

        char* endptr; //Pointer for error checking during conversion
        long parsed_value = strtol(input, &endptr, 10); //Converts input to a long integer

        if (*endptr == '\0' && parsed_value >= 0 && parsed_value <= INT_MAX) // Validate the converted value
        {
            return (int)parsed_value; //Returnss valid integer value
        } else 
        {
            printf("Invalid input. Please enter a valid number.\n");
        }
    }
}

int main() 
{   
    RRSongScheduler scheduler; //Scheduler object to manage songs

    //Prompts user to configure scheduler parameters
    int quantum_time = get_valid_integer("Enter quantum time (song play slice): ");
    int context_switch_time = get_valid_integer("Enter context switch time: ");
    
    initialize_scheduler(&scheduler, quantum_time, context_switch_time); //Initializes the scheduler with the provided parameters

    int choice, user_id; //Variables for user menu choices and user ID
    char song_name[MAX_NAME_LEN]; //Buffer for song names

    while (1)
    { 
        // Displays menu options to the user
        printf("\n--- Music Round Robin Scheduler ---\n");
        printf("1. Add Song\n");
        printf("2. Play Songs\n");
        printf("3. Remove User's Songs\n");
        printf("4. Print Playlist Metrics\n");
        printf("5. Exit\n");

        choice = get_valid_integer("Enter your choice: "); //Get a valid menu choice from the user

        switch (choice)
        { 
            case 1: //Add a new song to the scheduler
                user_id = get_valid_integer("Enter User ID: "); //Get user ID
                printf("Enter Song Name: ");
                fgets(song_name, MAX_NAME_LEN, stdin); //Get song name
                song_name[strcspn(song_name, "\n")] = 0;  //Remove trailing newline
                
                add_song(&scheduler, user_id, song_name); //Add the song
                printf("Song added successfully!\n");
                break;

            case 2: //Play all songs using round-robin scheduling
                run_song_scheduler(&scheduler);
                printf("Playlist playback completed.\n");
                break;

            case 3: //Remove all songs for a specific user
                user_id = get_valid_integer("Enter User ID to remove songs: "); //Get user ID
                remove_user_songs(&scheduler, user_id); //Remove user's songs
                printf("Songs for User %d removed.\n", user_id);
                break;

            case 4: //Print metrics for all songs in the playlist
                print_song_metrics(&scheduler);
                break;

            case 5: //Exit the program
                printf("Exiting...\n");
                return 0;

            default: //Handle invalid menu choices
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0; //Successful end of program
}