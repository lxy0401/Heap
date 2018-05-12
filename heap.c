#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

//销毁堆
//注：此时内存不能释放，因为没有malloc
void HeapDestroy(Heap* heap)
{
    if(heap == NULL)
    {
        //非法输入
        return ;
    }
    heap->size = 0;
    heap->cmp = NULL;
    return ;
}

//向堆中插入元素
void Swap(HeapType* a,HeapType* b)
{
    HeapType tmp = *a;
    *a = *b;
    *b = tmp;
}
void AdjustUp(Heap* heap,size_t index)
{
    //index表示从哪个位置开始调整
    size_t child = index;
    size_t parent = (child - 1)/2;
    while(child > 0)
    {
        if(!heap->cmp(heap->data[parent],heap->data[child]))
        {
            Swap(&heap->data[parent],&heap->data[child]);
        }
        else
        {
            //若发现某个位置下的child，parent已满足堆的要求，就停止上浮
            //因为上面的节点已经满足堆的要求
            break;
        }
        child = parent;
        parent = (child - 1)/2;
    }
}
void HeapInsert(Heap* heap ,HeapType value)
{
    if(heap == NULL)
    {
        //非法输入
        return ;
    }
    //相当于对数组进行尾插
    if(heap->size >= HeapMaxSize)
    {
        //堆满
        return ;
    }
    heap->data[heap->size++] = value;
    //对这个堆进行上浮式调整
    //调整的起始位置为size-1，即插入的元素
    AdjustUp(heap,heap->size-1);
    return ;
}

//取堆顶元素
int HeapRoot(Heap* heap,HeapType* value)
{
    if(heap == NULL)
    {
        //非法输入
        return 0;
    }
    if(heap->size == 0)
    {
        //空堆
        return 0;
    }
    *value = heap->data[0];
    return 1;
}

//删除堆顶元素
void AdjustDown(Heap* heap,size_t index)
{
    size_t parent = index;
    size_t child = 2*index+1;//左子树
    while(child < heap->size)
    {
        //child+1表示右子树
        if(child+1 < heap->size && heap->cmp(heap->data[child+1],heap->data[child]))
        {
            //若右子树存在，且右子树比左子树更符合堆的要求
            //假设为小堆：右子树<做子树，且让child指向右子树
            child = child+1;
        }
        //child指向左右子树中更小的那个元素
        if(heap->cmp(heap->data[child],heap->data[parent]))
        {
            Swap(&heap->data[child],&heap->data[parent]);
        }
        else
        {
            break;
        }
        parent = child;
        child = 2*parent+1;
    }
}
void HeapErase(Heap* heap)
{
    if(heap == NULL)
    {
        //非法输入
        return ;
    }
    if(heap->size == 0)
    {
        //空堆
        return ;
    }
    //交换堆顶与最后一个元素
    Swap(&heap->data[0],&heap->data[heap->size-1]);
    //--size进行尾删
    --heap->size;
    //从根节点出发进行下沉
    AdjustDown(heap,0);
    return ;
}

//给一个数组，将数组构建成堆，这个堆通过heap来表示
void HeapCreate(Heap* heap,HeapType arry[],size_t size)
{
    if(heap == NULL)
    {
        return ;
    }
    //遍历arry数组，将数组元素依次插入到堆中
    size_t i = 0;
    for(;i<size;++i)
    {
        HeapInsert(heap,arry[i]);
    }
    return;
}

//实现堆排序
//升序->大堆
//降序->小堆
void HeapSort(HeapType arry[],size_t size)
{
    //把数组构建成堆
    Heap heap;
    HeapInit(&heap,Greater);
    HeapCreate(&heap,arry,size);
    //循环将堆进行删除操作
    while(heap,size>0)
    {
        HeapErase(&heap);
    }
    //循环结束后，堆排序完成了
    memcpy(arry,heap.data,size* sizeof(HeapType));
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
void HeapPrintChar(Heap* heap,const char* msg)
{
    printf("[%s]\n",msg);
    size_t i = 0;
    for(;i<heap->size;++i)
    {
        printf("[%c|%lu]",heap->data[i],i);
    }
    printf("\n");
}
void TestInit()
{
    TEST_HEAD;
    Heap heap;
    HeapInit(&heap,Greater);
    printf("size expected 0,actual %lu\n",heap.size);
    printf("cmp expected %p,actual %p\n",Greater,heap.cmp);
}

void TestInsert()
{
    TEST_HEAD;
    Heap heap;
    HeapInit(&heap,Greater);
    HeapInsert(&heap,'c');
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'a');
    HeapInsert(&heap,'e');
    HeapInsert(&heap,'f');
    HeapInsert(&heap,'d');
    HeapPrintChar(&heap,"向堆中插入六个元素");
}

void TestRoot()
{
    TEST_HEAD;
    Heap heap;
    HeapInit(&heap,Greater);
    HeapInsert(&heap,'c');
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'a');
    HeapInsert(&heap,'e');
    HeapInsert(&heap,'f');
    HeapInsert(&heap,'d');
    HeapType value;
    int ret = HeapRoot(&heap,&value);
    printf("ret expected 1,actual %d\n",ret);
    printf("value expected f,actual %c\n",value);
}

void TestErase()
{ 
    TEST_HEAD;
    Heap heap;
    HeapInit(&heap,Greater);
    HeapInsert(&heap,'c');
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'a');
    HeapInsert(&heap,'e');
    HeapInsert(&heap,'f');
    HeapInsert(&heap,'d');
    HeapErase(&heap);
    HeapPrintChar(&heap,"对堆进行一次删除操作");
}

void TestSort()
{
    TEST_HEAD;
    HeapType arry[] = {'d','e','c','a','b'};
    HeapSort(arry,sizeof(arry)/sizeof(arry[0]));
    size_t i = 0;
    for(;i<sizeof(arry)/sizeof(arry[0]);++i)
    {
        printf("%c",arry[i]);
    }
    printf("\n");
}

int main()
{
    TestInit();
    TestInsert();
    TestRoot();
    TestErase();
    TestSort();
    return 0;
}
#endif
