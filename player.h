#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    char symbol;
    int x, y;
    int health;
    int kills;
} Player;

void init_player(Player* player, char symbol, int x, int y);
void move_player(Player* player, int key, char maze[25][25]);

#endif
