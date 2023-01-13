//
// Created by zheng on 2022/8/31.
//

#include "group.h"


#ifndef CACHE_CACHE_H
#define CACHE_CACHE_H

extern char* RAM;

typedef struct Cache{
    unsigned int tag;
    unsigned int set;
    unsigned int way;
    unsigned int offset;
    int type;
    Group **groups;
} Cache;

Cache *cacheInit(unsigned int tag, unsigned int set, unsigned int way, unsigned int offset, int type);
int isCacheHit(Cache *cache, unsigned int addr);
int runCache(Cache *cache, unsigned int addr, unsigned int memData, int memRead, int memWrite, unsigned int *memDataout);
unsigned int index2addr(Cache *cache, unsigned int setIndex, unsigned int wayIndex);

#endif //CACHE_CACHE_H
