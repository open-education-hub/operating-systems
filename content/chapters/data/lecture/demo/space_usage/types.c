#include <stdio.h>

// naive version
typedef struct Creature
{
    int isCat;
    int isDog;
    int isHuman;
    int isWhale;
    int hasArms;
    int hasLegs;
    int hasTail;
    int sex;

    /* potentially other traits */

}Creature;

// better but not best
typedef struct BetterCreature
{
    char isCat;
    char isDog;
    char isHuman;
    char isWhale;
    char hasArms;
    char hasLegs;
    char hasTail;
    char hasColdBlood;
}BetterCreature;

// best
typedef struct BestCreature
{
    // each bit signifies a traits
    char traits;
}BestCreature;

#define isCat(p) (p & 1)
#define isDog(p) (p & 2)
#define isHuman(p) (p & 4)
#define isWhale(p) (p & 8)
#define hasArms(p) (p & 16)
#define hasLegs(p) (p & 32)
#define hasTail(p) (p & 64)
#define hasColdblood(p) (p & 128)

typedef struct BitfieldCreature
{
    char isCat : 1;
    char isDog : 1;
    char isHuman : 1;
    char isWhale : 1;
    char hasArms : 1;
    char hasLegs : 1;
    char hasTail : 1;
    char hasColdBlood : 1;

}BitfieldCreature;

void main()
{
    printf("Size of Creature: %lu\n", sizeof(Creature));
    printf("Size of BetterCreature: %lu\n", sizeof(BetterCreature));
    printf("Size of BestCreature: %lu\n", sizeof(BestCreature));
    printf("Size of BitfieldCreature: %lu\n", sizeof(BitfieldCreature));
}
