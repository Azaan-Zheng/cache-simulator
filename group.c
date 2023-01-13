//
// Created by zheng on 2022/8/31.
//

#include "group.h"

Group *groupInit(unsigned int way, unsigned int offset){
    Group *g = (Group *) malloc(sizeof (Group));
    int size = (int)(1 << way);
    if(way + offset >= WORD_LENGTH){
        return NULL;
    }
    g->way = way;
    g->offset = offset;
    g->blocks = (Block **) malloc(size * sizeof(Block *));
    g->counters = (unsigned int *) malloc(size * sizeof(int));
    if(g->blocks == NULL || g->counters == NULL){
        return NULL;
    }
    for(int i = 0;i < size;i++){
        g->blocks[i] = blockInit(g->offset);
    }
    memset(g->counters, 0, size * sizeof(int));
    return g;
}

int isGroupHit(Group *g, unsigned int tagIndex){
    int waySize = (1 << g->way);
    for(int i = 0; i < waySize; i++){
        if(g->blocks[i]->valid && g->blocks[i]->tagIndex == tagIndex){
            return i;
        }
    }
    return MISS;
}