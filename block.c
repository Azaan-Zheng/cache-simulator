//
// Created by zheng on 2022/8/31.
//

#include "block.h"

Block* blockInit(unsigned int offset){
    Block *b = (Block *) malloc(sizeof (Block));
    b->offset = offset;
    b->tagIndex = 0;
    b->valid = 0;
    b->block = (char *)malloc(1 << offset);
    if(b->block != NULL){
        memset(b->block, 0, (1 << offset));
        return b;
    }
    free(b);
    return NULL;
}

int blockRefresh(Block *b, unsigned int tag){
    b->tagIndex = tag;
    b->valid = 1;
    return SUCCESS;
}



