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

//初始化，决定是大堆还是小堆
void HeapInit(Heap* heap,Compare cmp);

//销毁堆
void HeapDestroy(Heap* heap);

//向堆中插入元素
void HeapInsert(Heap* heap ,HeapType value);

//取堆顶元素
int HeapRoot(Heap* heap,HeapType* value);

//删除堆顶元素
void HeapErase(Heap* heap);

//给一个数组，将数组构建成堆，这个堆通过heap来表示
void HeapCreate(Heap* heap,HeapType arry[],size_t size);

//实现堆排序
void HeapSort(HeapType arry[],size_t size);
