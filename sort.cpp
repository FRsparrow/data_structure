#include <iostream>
#include "myheaders/sort.h"

using namespace std;

int main()
{
    const int n = 11;
    // int a[] = {5,4,8,2,0,7,9,3,1,6,6};
    // int a[] = {1,1,1,1,1,1,1,1,1,1,1};
    int a[] = {9,8,7,6,5,4,3,2,1,0,0};
    // int a[] = {0,1,2,3,4,5,6,6,7,8,9};
    merge_sort(a, a+n);

    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    

    system("pause");
    return 0;
}