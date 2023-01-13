//
// Created by zheng on 2022/8/31.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defines.h"
#include "utils.h"

#ifndef CACHE_BLOCK_H
#define CACHE_BLOCK_H

typedef struct Block{
    int valid;
    unsigned int tagIndex;
    unsigned int offset;
    char *block;
} Block;

Block *blockInit(unsigned int offset);
int blockRefresh(Block *b, unsigned int tagIndex);

#endif //CACHE_BLOCK_H
