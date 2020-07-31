#include "heap.h"

#define MAX_NODE_NUMBER MAX_HEAP_SIZE   // 最大结点数
#define INF 100    // 无穷权值

// 堆优化dijkstra的堆元素类型
struct heap_node
{
    int node;
    int cost;

    heap_node(){}
    heap_node(int n, int c): node(n), cost(c){}

    bool operator < (struct heap_node hn)
    {
        return cost < hn.cost;
    }

    bool operator > (struct heap_node hn)
    {
        return cost > hn.cost;
    }
};

// 边
class edge
{
public:
    int node;
    int cost;
    edge* next;

    edge(int n, int c);
    ~edge();
};

edge::edge(int n, int c): node(n), cost(c), next(nullptr){}

edge::~edge(){ delete next;}

// 结点
class node
{
public:
    edge* neighbour;
    edge* last_neighbour;

    node();
    ~node();
    
    void add_neighbour(int t, int cost);
};

node::node(): neighbour(nullptr), last_neighbour(nullptr){}

node::~node(){ delete neighbour; }

void node::add_neighbour(int t, int cost)
{
    if (!last_neighbour)
    {
        neighbour = last_neighbour = new edge(t, cost);
    }
    else
    {
        last_neighbour->next = new edge(t, cost);
        last_neighbour = last_neighbour->next;
    }
}

// 图
class Graph
{
private:
    int node_number;
    node* sources;  // 正邻接表
    node* targets;  // 逆邻接表,若为无向图则等于sources

    bool undirected;    // true为无向图，false为有向图
    void set_distance(int s, int d[], Heap<heap_node>* heap);
    void get_indegree(int count[], int& top);

public:

    Graph(int n, bool undirected);
    ~Graph();

    void add_edge(int s, int t, int cost);
    void dijkstra(int s, int d[], int path[]);
    void bellman_ford(int s, int d[], int path[]);
    void floyd(int** a, int** path);
    void critical_path(int* cp);
    bool topological_sort(int seq[]);   // 有环或为无向图返回false，否则返回true
    int get_cost(int s, int t);
};

void Graph::set_distance (int s, int d[], Heap<heap_node>* heap)
{
    for (int i = 0; i < node_number; i++)
    {
        d[i] = INF;
    }
    d[s] = 0;
    heap->push(heap_node(s, 0));
    
    // edge* p = sources[s].neighbour;
    // while (p)
    // {
    //     heap->push(heap_node(p->node, p->cost));
    //     d[p->node] = p->cost;
    //     p = p->next;
    // }
    
}

void Graph::get_indegree(int count[], int& top)
{
    for (int i = 0; i < node_number; i++)
    {
        count[i] = 0;
        edge* p = targets[i].neighbour;
        while (p)
        {
            ++count[i];
            p = p->next;
        }
        if (!count[i])  // 入度为0，进栈
        {
            count[i] = top;
            top = i;
        }
    }
}

Graph::Graph(int n, bool type=true)
{
    if (n > MAX_NODE_NUMBER)
    {
        return;
    }
    else
    {
        undirected = type;
        node_number = n;
        sources = new node[n];

        if (!type)   // 有向图建立逆邻接表
        {
            targets = new node[n];
        }
        else
        {
            targets = sources;
        }
    }
     
}

Graph::~Graph()
{
    delete[] sources;
    if (!undirected)
    {
        delete[] targets;
    }
}

void Graph::add_edge(int s, int t, int cost=1)
{
    sources[s].add_neighbour(t, cost);
    // 无向图则每条边有两个方向
    if (undirected)
    {
        sources[t].add_neighbour(s, cost);
    }
    else
    {
        targets[t].add_neighbour(s, cost);
    }
    
}

int Graph::get_cost(int s, int t)
{
    if (s == t)
    {
        return 0;
    }
    
    edge* p = sources[s].neighbour;
    while (p)
    {
        if (p->node == t)
        {
            return p->cost;
        }
        p = p->next;
    }
    return INF;
}

void Graph::dijkstra(int s, int d[], int path[])
{
    auto heap = new Heap<heap_node>();
    bool computed[node_number];
    
    for (int i = 0; i < node_number; i++)
    {
        computed[i] = false;
        path[i] = -1;
    }
    path[s] = s;
    // computed[s] = true;
    set_distance(s, d, heap);
    
    int count = node_number;
    while (count--)
    {
        struct heap_node hn;
        do
        {
            heap->pop(hn);
        } while (computed[hn.node]);

        d[hn.node] = hn.cost;
        computed[hn.node] = true;
        
        // 更新
        for (int i = 0; i < node_number; i++)
        {
            if (!computed[i])
            {
                int c = get_cost(hn.node, i);
                if(c != INF && (d[i] == INF || c + hn.cost < d[i]))
                {
                    d[i] = c + hn.cost;
                    path[i] = hn.node;
                    heap->push(heap_node(i, d[i]));
                }
            }
        }
    }

    delete heap;
}

void Graph::bellman_ford(int s, int d[], int path[])
{
    for (int i = 0; i < node_number; i++)
    {
        d[i] = INF;
        path[i] = -1;
    }
    d[s] = 0;
    edge* p = sources[s].neighbour;
    // 源点s的所有邻居初始化的distance值初始化
    while (p)
    {
        d[p->node] = p->cost;
        path[p->node] = s;
        p = p->next;
    }
    
    for (int i = 1; i < node_number-1; i++)
    {
        for (int j = 0; j < node_number; j++)
        {
            // if (s != j)
            // {
            //     for (int k = 0; k < node_number; k++)
            //     {
            //         int c = get_cost(k, j);
            //         if (c < INF && d[k] < INF && d[j] > d[k] + c)
            //         {
            //             d[j] = d[k] + c;
            //             path[j] = k;
            //         }
            //     }
            // }

            edge* p = targets[j].neighbour;
            // 遍历指向j的每条边
            while (p)
            {
                if (d[p->node] < INF && d[j] > d[p->node] + p->cost)
                {
                    d[j] = d[p->node] + p->cost;
                    path[j] = p->node;
                }
                p = p->next;
            }
            
        }
    }
}

void Graph::floyd(int** a, int** path)
{
    for (int i = 0; i < node_number; i++)
    {
        for (int j = 0; j < node_number; j++)
        {
            a[i][j] = INF;
            path[i][j] = -1;
        }
        a[i][i] = 0;
        path[i][i] = i;
        // 初始化邻接矩阵
        edge* p = sources[i].neighbour;
        while (p)
        {
            path[i][p->node] = i;
            a[i][p->node] = p->cost;
            p = p->next;
        }
    }
    
    // i到j的路径中间顶点的序号<=k
    for (int k = 0; k < node_number; k++)
    {
        for (int i = 0; i < node_number; i++)
        {
            for (int j = 0; j < node_number; j++)
            {
                if (a[i][k] < INF && a[k][j] < INF && (a[i][j] == INF || a[i][k] + a[k][j] < a[i][j]))
                {
                    // i = k && j != k，故a[i][j]的改变不影响本次k中其他i，j的计算，因为其若改变，是根据a[i][k]和a[k][j]计算的
                    a[i][j] = a[i][k] + a[k][j];
                    // i到j路经k(i->...->k->...->j)，从而i到j的路上j前面的顶点就是k到j的路上j前面的顶点
                    path[i][j] = path[k][j];
                }
            }
        }
    }
}

// 假设各结点标号顺序即为拓扑顺序
void Graph::critical_path(int* cp)
{
    int index = 0;
    int *ve = new int[node_number], *vl = new int[node_number];
    for (int i = 0; i < node_number; i++)
    {
        ve[i] = 0;
    }
    
    // 计算ve: 每个点可能的最早开始时间; ve[j] = max{ve[i]+dur(i,j)}, i遍历所有指向j的结点
    for (int i = 1; i < node_number; i++)
    {
        edge* p = targets[i].neighbour;
        while (p)
        {
            if (ve[i] < ve[p->node] + p->cost)
            {
                ve[i] = ve[p->node] + p->cost;
            }
            p = p->next;
        }
    }
    
    // 计算vl: 每个点最迟开始时间; vl[j] = min{vl[k]-dur(j,k)}, k遍历所有j指向的结点
    for (int i = 0; i < node_number; i++)
    {
        vl[i] = ve[node_number-1];
    }
    for (int i = node_number-2; i >= 0; i--)
    {
        edge* p = sources[i].neighbour;
        while (p)
        {
            if (vl[i] > vl[p->node] - p->cost)
            {
                vl[i] = vl[p->node] - p->cost;
            }
            p = p->next;
        }
    }
    
    for (int i = 0; i < node_number; i++)
    {
        edge* p = sources[i].neighbour;
        while (p)
        {
            if (ve[i] == vl[p->node] - p->cost)
            {
                cp[index++] = i;
                cp[index++] = p->node;
            }
            p = p->next;
        }
        
    }
    
    delete[] ve;
    delete[] vl;
}

bool Graph::topological_sort(int seq[])
{
    if (undirected)
    {
        return false;
    }
    
    int* count = new int[node_number];
    int top = -1, index = 0;
    // 统计入度并初始化栈，所有入度为0的入栈
    // 其中栈为链栈，每个栈元素count值为其在栈中下方元素的下标，top为栈顶元素下标
    get_indegree(count, top);
    while (top != -1)   // 栈不空
    {
        // 出栈
        seq[index] = top;
        top = count[top];

        edge* p = sources[seq[index]].neighbour;
        // 删去以栈顶结点为源点的所有边
        while (p)
        {
            if ((--count[p->node]) == 0)    // 入度变为0则进栈
            {
                count[p->node] = top;
                top = p->node;
            }
            p = p->next;
        }
        
        ++index;
    }
    
    delete[] count;

    // 有环
    if (index < node_number)
    {
        return false;
    }
    return true;
}