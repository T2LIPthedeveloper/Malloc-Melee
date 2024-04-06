#ifndef ITEMS_HG
#define ITEMS_HG

/* Enum of possible collectible items */
typedef enum {
    BURNT_CIGAR = (short)1,
    KEY_RING,
    MALLOC_MASK
}Collectible;

/* Represents an item that has a name, verb, and associated value */
struct ValuedItem {
    char *name;
    char *verb;
    short value;
};

#endif