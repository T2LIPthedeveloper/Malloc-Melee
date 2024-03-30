#ifndef MONSTER_H
#define MONSTER_H

struct Monster {
    char * name;
    short max_health;
    short health;
    short attack;
    short defence;
    char* attack_messages[3]; /* Descriptions of the monster's attacks */
    int attack_type_count;
    char* defense_messages[3]; /* Descriptions of the monster's defenses */
    int defense_type_count;
    char* death_message; /* Message displayed when the monster dies */
    char* victory_message; /* Message displayed when the player defeats the monster */
    char* defeat_message; /* Message displayed when the monster defeats the player */
};

#endif
