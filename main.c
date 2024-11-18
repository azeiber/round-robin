int main() 
{   
    #include <stdio.h>
    #include "scheduler.h"
    
    //#include <stdlib.h>
    #include <string.h>

    RoundRobinScheduler scheduler;
    initialize_scheduler(&scheduler);

    int choice, user_id;
    char song_name[MAX_NAME_LEN];
    while (1) {
        printf("\n1. Add Song\n2. Play Next Song\n3. Remove User Songs\n4. Print Queue\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter User ID: ");
                scanf("%d", &user_id);
                printf("Enter Song Name: ");
                scanf(" %[^\n]s", song_name);  // Read a string with spaces
                add_song(&scheduler, user_id, song_name);
                break;
            case 2: {
                Song next_song = get_next_song(&scheduler);
                if (next_song.user_id != 0) {
                    printf("Now playing: User %d - %s\n", next_song.user_id, next_song.song_name);
                }
                break;
            }
            case 3:
                printf("Enter User ID to remove all songs: ");
                scanf("%d", &user_id);
                remove_user_songs(&scheduler, user_id);
                break;
            case 4:
                print_queue(&scheduler);
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}