#include "player.h"

void init_player(Player* player, char symbol, int x, int y) {
    player->symbol = symbol;
    player->x = x;
    player->y = y;
    player->health = 3;
    player->kills = 0;
}

void move_player(Player* player, int key, char maze[25][25]) {
    int new_x = player->x;
    int new_y = player->y;

    switch (key) {
        case 'w':
        case 'W':
        case 72: // Up arrow
            new_y--;
            break;
        case 's':
        case 'S':
        case 80: // Down arrow
            new_y++;
            break;
        case 'a':
        case 'A':
        case 75: // Left arrow
            new_x--;
            break;
        case 'd':
        case 'D':
        case 77: // Right arrow
            new_x++;
            break;
        case 'o':
        case 'O':
        case 'i':
        case 'I':
            // Eliminate zombie (handled in main game loop)
            return;
    }

    if (new_x >= 0 && new_x < 25 && new_y >= 0 && new_y < 25 && maze[new_y][new_x] != '#') {
        maze[player->y][player->x] = ' ';
        player->x = new_x;
        player->y = new_y;
        maze[player->y][player->x] = player->symbol;
    }
}
