#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "maze.h"
#include "player.h"
#include "zombie.h"

#define MAZE_SIZE 25
#define GAME_TIME 120 // 2 minutes in seconds

char maze[MAZE_SIZE][MAZE_SIZE];
Player player1, player2;
Zombie zombies[10]; // We'll have 10 zombies
int num_zombies = 10;
int game_mode; // 1 for single player, 2 for multiplayer
time_t start_time;

void initialize_game() {
    srand((unsigned int)time(NULL));
    generate_maze(maze);
    init_player(&player1, 'X', 0, 0);
    if (game_mode == 2) {
        init_player(&player2, 'Y', 0, 1);
    }
    for (int i = 0; i < num_zombies; i++) {
        init_zombie(&zombies[i]);
    }
    start_time = time(NULL);
}

void print_game_state() {
    system("cls"); // Clear the console
    print_maze(maze);
    printf("Player 1 (X) - Health: %d, Kills: %d\n", player1.health, player1.kills);
    if (game_mode == 2) {
        printf("Player 2 (Y) - Health: %d, Kills: %d\n", player2.health, player2.kills);
    }
    int time_left = GAME_TIME - (int)(time(NULL) - start_time);
    printf("Time left: %d seconds\n", time_left);
}

int check_game_over() {
    if (player1.health <= 0 || (game_mode == 2 && player2.health <= 0)) {
        printf("Game Over! You ran out of health.\n");
        return 1;
    }
    if (time(NULL) - start_time >= GAME_TIME) {
        printf("Game Over! Time's up.\n");
        return 1;
    }
    if (maze[player1.y][player1.x] == 'E' || (game_mode == 2 && maze[player2.y][player2.x] == 'E')) {
        printf("Congratulations! You reached the end point.\n");
        return 1;
    }
    return 0;
}

void update_game_state() {
    move_zombies(zombies, num_zombies, maze);
    check_player_zombie_collision(&player1, zombies, num_zombies);
    if (game_mode == 2) {
        check_player_zombie_collision(&player2, zombies, num_zombies);
    }
}

void setup_console() {
    // Set console output to UTF-8
    SetConsoleOutputCP(CP_UTF8);
    // Enable ANSI escape sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

int main() {
    setup_console();

    printf("Welcome to Zombie Apocalypse Maze!\n");
    printf("1. Single Player\n2. Multiplayer\nEnter your choice: ");
    scanf("%d", &game_mode);

    initialize_game();

    while (!check_game_over()) {
        print_game_state();
        if (_kbhit()) {
            int key = _getch();
            if (game_mode == 1 || (game_mode == 2 && key != 224)) { // Player 1 input
                move_player(&player1, key, maze);
            } else if (game_mode == 2 && key == 224) { // Player 2 input (arrow keys)
                key = _getch(); // Get the actual arrow key
                move_player(&player2, key, maze);
            }
        }
        update_game_state();
        Sleep(100); // Small delay to control game speed
    }

    printf("Final Scores:\n");
    printf("Player 1 (X) - Kills: %d\n", player1.kills);
    if (game_mode == 2) {
        printf("Player 2 (Y) - Kills: %d\n", player2.kills);
    }

    return 0;
}
