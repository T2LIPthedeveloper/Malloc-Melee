#ifndef ITEMS_H
#define ITEMS_H

/* types of items */
typedef enum {
    WEAPON,
    POTION,
    ARMOR,
    KEY
} ItemType;

/* UsefulItem struct under which items can be stored */
typedef struct {
    char *name; /* item name */
    short value; /* value of item */
    ItemType type; /* type of item */
} UsefulItem;

#endif