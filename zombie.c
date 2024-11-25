#include "zombie.h"
#include <stdlib.h>

void init_zombie(Zombie* zombie) {
    do {
        zombie->x = rand() % 25;
        zombie->y = rand() % 25;
    } while (zombie->x == 0 && zombie->y == 0); // Ensure zombie is not at start point
}

void move_zombies(Zombie zombies[], int num_zombies, char maze[25][25]) {
    for (int i = 0; i < num_zombies; i++) {
        int direction = rand() % 4;
        int new_x = zombies[i].x;
        int new_y = zombies[i].y;

        switch (direction) {
            case 0: new_y--; break; // Up
            case 1: new_y++; break; // Down
            case 2: new_x--; break; // Left
            case 3: new_x++; break; // Right
        }

        if (new_x >= 0 && new_x < 25 && new_y >= 0 && new_y < 25 && maze[new_y][new_x] == ' ') {
            maze[zombies[i].y][zombies[i].x] = ' ';
            zombies[i].x = new_x;
            zombies[i].y = new_y;
            maze[zombies[i].y][zombies[i].x] = 'Z';
        }
    }
}

void check_player_zombie_collision(Player* player, Zombie zombies[], int num_zombies) {
    for (int i = 0; i < num_zombies; i++) {
        if (abs(player->x - zombies[i].x) <= 1 && abs(player->y - zombies[i].y) <= 1) {
            printf("Warning: Zombie approaching!\n");
            return;
        }
    }
}