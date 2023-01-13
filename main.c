#include <stdio.h>
#include "cache.h"



Cache *cache = NULL;
char *RAM = NULL;
unsigned tag = 5;
unsigned way = 2;
unsigned set = 4;
unsigned offset = 8;


int main() {
    cache = cacheInit(tag, set, way, offset,LRU);
    RAM = (char *) malloc(1 << (tag + set + offset));
    memset(RAM,0,(1 << (tag + set + offset)));


    unsigned int addr = 0;
    unsigned int memData = 0xffffffff;
    int memRead = 1;
    int memWrite = 0;
    unsigned int out = 0;
    int isHit = 0;

    int hitCount = 0;
    int allCount = 0;
    float hitRate = 0.0;

    for(int i = 0;i < 10;i++){
        for(int j = 0;j <= 4351;j++){
            addr = (unsigned int)(j << 2);
            isHit = isCacheHit(cache, addr);
            runCache(cache,addr,memData,memRead,memWrite,&out);

            allCount++;
            if(isHit >= 0){
                hitCount++;
            }
        }
    }
    hitRate = hitCount * 100.0 / allCount;
    printf("hitCount: %d  allCount: %d  hitRate: %.2f%%\n",hitCount, allCount, hitRate);

//    printf("addr: %x  isHit: %d  memRead: %d  memWrite: %d  memData: %x  out: %x\n",addr, isHit, memRead, memWrite, memData, out);

    return 0;
}
