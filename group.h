//
// Created by zheng on 2022/8/31.
//

#include "block.h"


#ifndef CACHE_GROUP_H
#define CACHE_GROUP_H

typedef struct Group{
    unsigned int way;
    unsigned int offset;
    Block **blocks;
    unsigned int *counters;
} Group;

Group *groupInit(unsigned int way, unsigned int offset);
int isGroupHit(Group *g, unsigned int tag);

#endif //CACHE_GROUP_H
