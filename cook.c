#include "cook.h"
#include <stdlib.h>

Cook * newCook(int id, int rank, int proficiency)
{
    Cook * cook = malloc(sizeof(Cook));
    cook->id = id;
    cook->rank = rank;
    cook->proficiency = proficiency;

    return cook;
}