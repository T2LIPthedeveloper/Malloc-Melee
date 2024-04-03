#include <stdio.h>
#include <stdlib.h>

#include "./player.h"
#include "./items.h"
#include "./combat.h"
#include "./monster.h"
#include "./utilities.h"

int run_combat(struct Monster *monster, struct Player *player) {
    int player_turn = 1;

    while (player->health > 0 && monster->health > 0) {
        if (player_turn) {
            printPlayerAttack(player, monster);
            printMonsterDefense(monster);
            int damage = player->attack - monster->defence;
            if (damage < 0) {
                damage = 0;
            }
            monster->health -= damage;
            printHealth(player, monster);
            player_turn = 0;
        } else {
            printMonsterAttack(monster, player);
            printPlayerDefense(player);
            int damage = monster->attack - player->defence;
            if (damage < 0) {
                damage = 0;
            }
            player->health -= damage;
            printHealth(player, monster);
            player_turn = 1;
        }
    }

    if (player->health <= 0) {
        printf("%s has been defeated!\n", player->name);
        return 0;
    } else {
        printf("%s has been defeated!\n", monster->name);
        return 1;
    }
}

void printPlayerAttack(struct Player *player, struct Monster *monster) {
    printf("%s attacks %s for %d damage!\n", player->name, monster->name, player->attack);
}

void printMonsterDefense(struct Monster *monster) {
    printf("%s defends against the attack!\n", monster->name);
}

void printMonsterAttack(struct Monster *monster, struct Player *player) {
    printf("%s attacks %s for %d damage!\n", monster->name, player->name, monster->attack);
}

void printPlayerDefense(struct Player *player) {
    printf("%s defends against the attack!\n", player->name);
}

void printHealth(struct Player *player, struct Monster *monster) {
    printf("%s's health: %d\n", player->name, player->health);
    printf("%s's health: %d\n", monster->name, monster->health);
}

