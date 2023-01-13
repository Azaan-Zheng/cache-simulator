//
// Created by zheng on 2022/8/31.
//

#include "cache.h"
#include "strategy.h"

Cache *cacheInit(unsigned int tag, unsigned int set, unsigned int way, unsigned int offset, int type){
    Cache *c = (Cache *) malloc(sizeof (Cache));
    int size = (int)(1 << set);
    c->tag = tag;
    c->set = set;
    c->way = way;
    c->offset = offset;
    c->type = type;
    if(offset + set + way >= WORD_LENGTH){
        return NULL;
    }
    c->groups = (Group **) malloc(size * sizeof(Group *));
    if(c->groups == NULL){
        return NULL;
    }
    for(int i = 0;i < size;i++){
        c->groups[i] = groupInit(way, offset);
        if(c->groups[i] == NULL){
            return NULL;
        }
    }
    return c;
}

int isCacheHit(Cache *cache, unsigned int addr){
    unsigned int setIndex = decoder(addr, cache->offset,
                           cache->offset + cache->set - 1);
    unsigned int tag = decoder(addr, cache->offset + cache->set,
                               cache->offset + cache->set + cache->tag - 1);
    return isGroupHit(cache->groups[setIndex], tag);
}

int runCache(Cache *cache, unsigned int addr, unsigned int memData,
             int memRead, int memWrite, unsigned int *memDataout){
    unsigned int offsetIndex = decoder(addr, 0, cache->offset - 1);
    unsigned int setIndex = decoder(addr, cache->offset,
                                       cache->offset + cache->set - 1);
    unsigned int tagIndex = decoder(addr, cache->offset + cache->set,
                               cache->offset + cache->set + cache->tag - 1);

    if(!cache->groups || !cache->groups[setIndex]){
        return ERROR;
    }
    Group *group = cache->groups[setIndex];
    int hitIndex = isGroupHit(group, tagIndex);
    int refreshIndex = strategy(cache->groups[setIndex], cache->type, memRead, memWrite, hitIndex);
    if(hitIndex >= 0) {
        Block *block = group->blocks[hitIndex];
        if(memRead){
            if(readWord(block->block, offsetIndex, memDataout) != SUCCESS){
                return ERROR;
            }
        }
        if(memWrite){
            if(writeWord(block->block, offsetIndex, memData) != SUCCESS){
                return ERROR;
            }
        }
    } else {
        if(memRead){
            Block *block = group->blocks[refreshIndex];
            if(block->valid){
                unsigned int addrWrite = index2addr(cache, setIndex, refreshIndex);
                if(writeBlock(RAM, addrWrite, block->block, cache->offset) != SUCCESS){
                    return ERROR;
                }
            }
            if(readBlock(RAM, addr, block->block, cache->offset) != SUCCESS){
                return ERROR;
            }
            blockRefresh(block, tagIndex);
            if(readWord(block->block, offsetIndex, memDataout) != SUCCESS){
                return ERROR;
            }
        }
        if(memWrite){
            if(writeWord(RAM, addr, memData) != SUCCESS){
                return ERROR;
            }
        }
    }
    return SUCCESS;
}

unsigned int index2addr(Cache *cache, unsigned int setIndex, unsigned int wayIndex){
    if(setIndex >= 0 && setIndex < (1 << cache->set) && wayIndex >= 0 && wayIndex < (1 << cache->way)){
        if(cache->groups && cache->groups[setIndex]){
            Group *group = cache->groups[setIndex];
            if(group->blocks && group->blocks[wayIndex]){
                Block *block = group->blocks[wayIndex];
                return (unsigned int)(((block->tagIndex << cache->set) | setIndex) << cache->offset);
            }
        }
    }
    return ERROR;
}