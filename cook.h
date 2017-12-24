#ifndef COOK_H
#define COOK_H

struct cookStruct
{
    int id;
    int rank; // 1-3
    int proficiency; // 1-4
};

typedef struct cookStruct Cook;

Cook * newCook(int id, int rank, int proficiency);

#endif