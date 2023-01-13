//
// Created by zheng on 2022/8/31.
//
#include "defines.h"
#include "group.h"

#ifndef CACHE_STRATEGY_H
#define CACHE_STRATEGY_H

int strategy(Group *g, int type, int memRead, int memWrite, int hitIndex);
int strategyLRU(Group *g, int memRead, int memWrite, int hitIndex);
int strategyFIFO(Group *g, int memRead, int memWrite, int hitIndex);
int strategyLFU(Group *g, int memRead, int memWrite, int hitIndex);

#endif //CACHE_STRATEGY_H
