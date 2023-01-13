//
// Created by zheng on 2022/8/31.
//
#include "utils.h"

unsigned int decoder(unsigned int addr, int begin, int end){
    if(0 <= begin && begin <= end && end < WORD_LENGTH){
        return ((addr >> begin) & ((1 << (end + 1 - begin)) - 1));
    }
    return addr;
}

int writeWord(char *arr, int begin, unsigned int data){
    if(begin >= 0 && begin + 4 <= _msize(arr)){
        arr[begin] = (char) data;
        arr[begin + 1] = (char) (data >> 8);
        arr[begin + 2] = (char) (data >> 16);
        arr[begin + 3] = (char) (data >> 24);
        return SUCCESS;
    }
    return ERROR;
}

int writeBlock(char *arr, int begin, char *block, unsigned int offset){
    int len = 1 << offset;
    if(begin >= 0 && begin + len <= _msize(arr)){
        for(int i = 0;i < len;i++){
            arr[i] = block[i];
        }
        return SUCCESS;
    }
    return ERROR;
}

int readWord(char *arr, int begin, unsigned int *data){
    unsigned int t = 0;
    if(begin >= 0 && begin + 4 <= _msize(arr)){
        for(int i = 3; i >= 0; i--){
            t = (t << 8) | ((unsigned int)(arr[begin + i]));
        }
        *data = t;
        return SUCCESS;
    }
    return ERROR;
}

int readBlock(char *arr, int begin, char *block, unsigned int offset){
    int len = 1 << offset;
    if(begin >= 0 && begin + len <= _msize(arr)){
        for(int i = 0;i < len;i++){
            block[i] = arr[i];
        }
        return SUCCESS;
    }
    return ERROR;
}