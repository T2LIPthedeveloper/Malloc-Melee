#ifndef ITEMS_HG
#define ITEMS_HG

/* Enum of possible collectible items */
typedef enum {
    WEBRUNE = (short)1,
    KEYRING,
    OLDENBLING
}Collectible;

/* Represents an item that has a name, verb, and associated value */
struct ValuedItem {
    char *name;
    char *verb;
    short value;
};

#endif