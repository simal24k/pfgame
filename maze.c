#include "maze.h"
#include <stdio.h>
#include <stdlib.h>

void generate_maze(char maze[MAZE_SIZE][MAZE_SIZE]) {
    // Initialize maze with walls
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            maze[i][j] = '#';
        }
    }

    // Create some random paths
    for (int i = 0; i < MAZE_SIZE * MAZE_SIZE / 3; i++) {
        int x = rand() % MAZE_SIZE;
        int y = rand() % MAZE_SIZE;
        maze[y][x] = ' ';
    }

    // Set start and end points
    maze[0][0] = 'S';
    maze[MAZE_SIZE-1][MAZE_SIZE-1] = 'E';
}

void print_maze(char maze[MAZE_SIZE][MAZE_SIZE]) {
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            // Add a space after each character for better visibility
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
}
