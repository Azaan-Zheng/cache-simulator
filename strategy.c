//
// Created by zheng on 2022/8/31.
//

#include "strategy.h"

int strategy(Group *g, int type, int memRead, int memWrite, int hitIndex){
    if(type == LRU){
        return strategyLRU(g, memRead, memWrite, hitIndex);
    } else if(type == FIFO) {
        return strategyFIFO(g, memRead, memWrite, hitIndex);
    } else if(type == LFU) {
        return strategyLFU(g, memRead, memWrite, hitIndex);
    } else {
        return ERROR;
    }
}

int strategyLRU(Group *g, int memRead, int memWrite, int hitIndex){
    int blockNum = (int)(1 << g->way);
    if(hitIndex >= 0){
        if(memRead){
            for(int i = 0;i < blockNum;i++){
                g->counters[i]++;
            }
            g->counters[hitIndex] = 0;
            return READ_BLOCK;
        }
        return WRITE_BLOCK;
    } else {
        if(memRead){
            int refreshIndex = 0;
            for(int i = 1;i < blockNum;i++){
                if(g->counters[i] > g->counters[refreshIndex]){
                    refreshIndex = i;
                }
            }
            return refreshIndex;
        }
    }
    return NO_OPTION;
}

int strategyFIFO(Group *g, int memRead, int memWrite, int hitIndex){

    return NO_OPTION;
}

int strategyLFU(Group *g, int memRead, int memWrite, int hitIndex){

    return NO_OPTION;
}