#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "player.h"

typedef struct {
    int x, y;
} Zombie;

void init_zombie(Zombie* zombie);
void move_zombies(Zombie zombies[], int num_zombies, char maze[25][25]);
void check_player_zombie_collision(Player* player, Zombie zombies[], int num_zombies);

#endif
