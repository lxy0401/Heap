#pragma once
#include <stddef.h>
#define HeapMaxSize 1024
typedef char HeapType;
//若a和b满足比较关系，返回1，否则返回0
//所谓的比较关系指的是，对于小堆来说，a<b
//对于大堆来说，a>b
typedef int(*Compare)(HeapType a,HeapType b);
typedef struct Heap
{
    HeapType data[HeapMaxSize];
    size_t size;
    Compare cmp;
}Heap;

