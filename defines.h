//
// Created by zheng on 2022/8/31.
//

#ifndef CACHE_DEFINES_H
#define CACHE_DEFINES_H

//system structure
#define WORD_LENGTH 32

//strategy
#define LRU 0x11
#define FIFO 0x12
#define LFU 0x13

// return valid
#define SUCCESS 1
#define ERROR -1
#define MISS -2
#define READ_BLOCK -3
#define WRITE_BLOCK -4
#define NO_OPTION -5


#endif //CACHE_DEFINES_H
