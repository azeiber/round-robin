Project Overview: 

Our Round-Robin Song Scheduler is a program designed to simulate a music playlist scheduler using the Round-Robin algorithm. The scheduler manages songs added by users and executes them in time slices (quantum time) while accounting for the context switch.

Our Features:

1. Add songs with user-specific details.
2. Play songs using round-robin scheduling.
3. Remove all songs added by a specific user.
4. View detailed metrics including arrival, start, and completion times for all songs.

How to Use:

1. Compile the Program:
    1. gcc -o music_scheduler main.c scheduler.c
    2. ./music_scheduler
2. Follow the menu options to interact with the scheduler:
    1. Add Song: Add a song by entering a user ID and the song name. Add all songs in the beginning.
    2. Play Songs: Execute the round-robin scheduler and play all songs in the queue.
    3. Remove User's Songs: Remove all songs associated with a specific user.
    4. Print Playlist Metrics: View detailed metrics for all songs in the scheduler.
    5. Exit: Exit the program.
