#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

//为大堆打造的比较函数
int Greater(HeapType a,HeapType b)
{
    return a>b?1:0;
}

//为小堆打造的比较函数
int Less(HeapType a,HeapType b)
{
    return a<b?1:0;
}
//初始化，决定是大堆还是小堆
void HeapInit(Heap* heap,Compare cmp)
{
    if(heap == NULL)
    {
        //非法输入
        return ;
    }
    heap->size = 0;
    heap ->cmp = cmp;
    return ;
}


/************************
 *
 *
 *
 * 以下为测试代码
 *
 *
 ***************************/
#if 1
#include <stdio.h>
#define TEST_HEAD printf("\n===========%s================\n",__FUNCTION__);
void TestInit()
{
    TEST_HEAD;
    Heap heap;
    HeapInit(&heap,Greater);
    printf("size expected 0,actual %lu\n",heap.size);
    printf("cmp expected %p,actual %p\n",Greater,heap.cmp);
}


int main()
{
    TestInit();
    return 0;
}
#endif
