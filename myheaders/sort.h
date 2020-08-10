#include "heap.h"

// 插入排序
template<class E>
void straight_insertion_sort(E *start, E *end, int gap=1);
template<class E>
void binary_insertion_sort(E *start, E *end);
template<class E>
void shell_sort(E *start, E *end);

// 交换排序
template<class E>
void bubble_sort(E *start, E *end);
template<class E>
void quick_sort(E *start, E *end);

// 选择排序
template<class E>
void straight_selection_sort(E *start, E *end);
template<class E>
void tournament_sort(E *start, E *end);
template<class E>
void heap_sort(E *start, E *end);

// 其他
template<class E>
void merge_sort(E *start, E *end);


template<class E>
void straight_insertion_sort(E *start, E *end, int gap)
{
    E *p = start + gap, *q;
    E temp;
    while (p < end)
    {
        q = p;
        temp = *p;
        while (q > start && temp < *(q-gap))
        {
            *q = *(q-gap);
            q = q - gap;
        }
        *q = temp;
        p += gap;;
    }
}

template<class E>
void binary_insertion_sort(E *start, E *end)
{
    E *p = start + 1, *left, *right, *mid, *q, temp;
    while (p != end)
    {
        temp = *p;
        left = start;
        right = p - 1;
        while (left <= right)
        {
            mid = left + (right - left) / 2;
            if (temp < *mid)
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
        for (q = p; q > left; q--)
        {
            *q = *(q-1);
        }
        *q = temp;
        ++p;
    }
    
}

template<class E>
void shell_sort(E *start, E *end)
{
    int gap = (end - start) / 3 + 1;
    while (true)
    {
        for (int base = 0; base < gap; base++)
        {
            straight_insertion_sort(start+base, end, gap);
        }
        if (gap == 1)
        {
            break;
        }
        gap = gap / 3 + 1;
    }
}

template<class E>
void bubble_sort(E *start, E *end)
{
    E temp;
    bool finished;
    for (E* i = end-1; i > start; i--)
    {
        finished = true;
        for (E* p = start; p < i; p++)
        {
            if (*p > *(p+1))
            {
                temp = *p;
                *p = *(p+1);
                *(p+1) = temp;
                finished = false;
            }
        }
        if (finished)
        {
            break;
        }
    }
}

template<class E>
void quick_sort(E *start, E *end)
{
    if (start >= end-1)
    {
        return;
    }
    
    E pivot = *start;
    E *low = start, *high = end-1;
    while (low < high)
    {
        while (*high > pivot && low < high)
        {
            --high;
        }
        *low = *high;
        while (*low <= pivot && low < high)
        {
            ++low;
        }
        *high = *low;
    }
    *low = pivot;
    quick_sort(start, low);
    quick_sort(low+1, end);
}

template<class E>
void straight_selection_sort(E *start, E *end)
{
    E min, *minptr;
    for (E* p = start; p < end; p++)
    {
        min = *p;
        minptr = p;
        for (E* q = p+1; q < end; q++)
        {
            if (min > *q)
            {
                min = *q;
                minptr = q;
            }
        }
        *minptr = *p;
        *p = min;
    }
}

template<class E>
void tournament_sort(E *start, E *end)
{
    // to do
}

template<class E>
void heap_sort(E *start, E *end)
{
    Heap<E>* heap = new Heap<E>(end-start, start, true);
    heap->sort();
}

template<class E>
void merge(E* source, E* target,int block_size, int len)
{
    int j,k,jmax,kmax,base;
    // 对每两个块(0和1，2和3...)进行合并,j,k分别指向前后块的当前比较元素，小者填入temp
    for (int i = 0; i < len; i += 2*block_size)
    {
        j = i;
        k = i + block_size;
        jmax = k < len ? k : len;
        kmax = k + block_size < len ? k + block_size : len;
        base = i + block_size;  // i+(j-i)+[k-(i+block_size)]=j+k-i-block_size才是当前元素在temp中对应元素的下标
        while (j < jmax && k < kmax)
        {
            if (source[j] <= source[k])
            {
                target[j+k-base] = source[j];
                ++j;
            }
            else
            {
                target[j+k-base] = source[k];
                ++k;
            }
        }
        if (j == jmax)  // 前一块先放完
        {
            while (k < kmax)    // 后一块存在则将剩余元素移入temp（k>=kmax表示后一块不存在）
            {
                target[j+k-base] = source[k];
                ++k;
            }
        }
        else    // 后一块先放完
        {
            base = k > kmax ? 0 : base - k; // 后一块不存在则直接将前一块依次填入temp，即base为0
            while (j < jmax)
            {
                target[j-base] = source[j];
                ++j;
            }
        }
    }
}

template<class E>
void merge_sort(E *start, E *end)
{
    bool flag = true;
    int len = end - start;
    E *temp = new E[len];
    for (int block_size = 1; block_size < len; block_size *= 2)
    {
        if (flag)
        {
            merge(start, temp, block_size, len);
        }
        else
        {
            merge(temp, start, block_size, len);
        }
        flag = !flag;
    }
    if (!flag)
    {
        for (int i = 0; i < len; i++)
        {
            start[i] = temp[i];
        }
    }
    
    delete[] temp;
}

int get_bit_number(unsigned int *start, unsigned int *end)
{
    int len = end - start, count = 1;
    unsigned int max = start[0];
    for (int i = 1; i < len; i++)
    {
        max = max < start[i] ? start[i] : max;
    }
    while (max /= 10)
    {
        ++count;
    }

    return count;
}
