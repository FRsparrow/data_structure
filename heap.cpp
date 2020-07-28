#include <iostream>
#include "myheaders/heap.h"

using namespace std;

template<class E>
void visit(E e)
{
    cout << e << " ";
}

int main()
{
    int a[] = {9,8,7,6,5,4,3,2,1};
    auto heap = new Heap<int>(9, a);
    heap->show(visit);
    cout << endl;

    system("pause");
    return 0;
}