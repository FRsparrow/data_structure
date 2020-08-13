class disjoint_set
{
private:
    int type_number;
    int number;
    int *a;     // i的前驱是a[i]
public:
    disjoint_set(int n);
    ~disjoint_set();

    int find(int x);
    void _union(int x, int y);
};

disjoint_set::disjoint_set(int n)
{
    type_number = number = n;
    a = new int[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = i;
    }
}

disjoint_set::~disjoint_set(){ delete[] a; }

int disjoint_set::find(int x)
{
    int root = x, temp;
    while (a[root] != root)
    {
        root = a[root];
    }
    while (root != a[x])
    {
        temp = a[x];
        a[x] = root;
        x = temp;
    }
    return root;
}

void disjoint_set::_union(int x, int y)
{
    int x_root = find(x);
    int y_root = find(y);
    if (x_root != y_root)
    {
        a[y_root] = x_root;
        type_number--;
    }
}
