#define MAX_HEAP_SIZE 100

template<class E>
class Heap
{
private:
    int heap_size;
    E* elements;

    void shift_up(int pos);
    void shift_down(int pos, int end);
public:
    Heap();
    Heap(int heap_size, E e[]);
    ~Heap();

    bool push(const E& e);
    bool pop(E& e);
    E& top();
    void show(void(*visit)(E e));
};

template<class E>
Heap<E>::Heap()
{
    elements = new E[MAX_HEAP_SIZE];
    heap_size = 0;
}

/*
�����ѣ������һ�����׽�㵽��һ�����׽�㣬ÿ�����׽�����ν����³�
*/
template<class E>
Heap<E>::Heap(int heap_size, E e[])
{
    elements = new E[MAX_HEAP_SIZE];
    this->heap_size = heap_size;
    for (int i = 0; i < heap_size; i++)
    {
        elements[i] = e[i];
    }
    int pos = heap_size / 2 - 1;
    while (pos >= 0)
    {
        shift_down(pos--, heap_size-1);
    }
}

template<class E>
Heap<E>::~Heap()
{
    delete[] elements;
}

/*
pos���Ľ��͸��׽��Ƚϴ�С�����ȸ��׽��С���򽻻����ظ����裬�������
*/
template<class E>
void Heap<E>::shift_up(int pos)
{
    E temp = elements[pos];
    while (pos > 0 && elements[(pos-1)>>2] > temp)
    {
        elements[pos] = elements[(pos-1)>>2];
        pos = (pos-1) >> 2;
    }
    elements[pos] = temp;
}

/*
pos���Ľ��ͽ�С�ĺ��ӽ��Ƚϴ�С�����ȸú��ӽ��С���򽻻����ظ����裬�������
*/
template<class E>
void Heap<E>::shift_down(int pos, int end)
{
    E temp = elements[pos];
    int child;
    while ((child = 2 * pos + 1) <= end)
    {
        // ѡ�����Һ���С���Ǹ�
        if (child < end && elements[child] > elements[child+1])
        {
            child++;
        }
        if (temp > elements[child])
        {
            elements[pos] = elements[child];
            pos = child;
        }
        else
        {
            break;
        }
    }
    elements[pos] = temp;
}

/*
�ڶ�ĩβ�����Ԫ�أ�Ȼ�����Ԫ�ؽ����ϸ�
*/
template<class E>
bool Heap<E>::push(const E& e)
{
    if (heap_size >= MAX_HEAP_SIZE)
    {
        return false;
    }
    elements[heap_size] = e;
    shift_up(heap_size++);

    return true;
}

/*
����βԪ�ظ������ף�Ȼ���³�
*/
template<class E>
bool Heap<E>::pop(E& e)
{
    if (heap_size == 0)
    {
        return false;
    }
    e = elements[0];
    elements[0] = elements[--heap_size];
    shift_down(0, heap_size-1);

    return true;
}

template<class E>
E& Heap<E>::top()
{
    return elements[0];
}

template<class E>
void Heap<E>::show(void(*visit)(E e))
{
    for (int i = 0; i < heap_size; i++)
    {
        visit(elements[i]);
    }
}