//
// Created by zheng on 2022/8/31.
//

#include <malloc.h>
#include "defines.h"

#ifndef CACHE_UTILS_H
#define CACHE_UTILS_H

unsigned int decoder(unsigned int addr, int begin, int end);
int writeWord(char *arr, int begin, unsigned int data);
int writeBlock(char *arr, int begin, char *block, unsigned int offset);
int readWord(char *arr, int begin, unsigned int *data);
int readBlock(char *arr, int begin, char *block, unsigned int offset);

#endif //CACHE_UTILS_H
