#include "heap.h"

#define MAX_NODE_NUMBER MAX_HEAP_SIZE

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

class Graph
{
private:
    void set_distance(int s, int d[], Heap<heap_node>* heap);

public:
    int node_number;
    node* nodes;

    Graph(int n);
    ~Graph();

    void add_edge(int s, int t, int cost);
    void dijkstra(int s, int d[], int path[]);
    int get_cost(int s, int t);
};

void Graph::set_distance (int s, int d[], Heap<heap_node>* heap)
{
    for (int i = 0; i < node_number; i++)
    {
        d[i] = -1;
    }
    d[s] = 0;
    heap->push(heap_node(s, 0));
    
    // edge* p = nodes[s].neighbour;
    // while (p)
    // {
    //     heap->push(heap_node(p->node, p->cost));
    //     d[p->node] = p->cost;
    //     p = p->next;
    // }
    
}

Graph::Graph(int n)
{
    if (n > MAX_NODE_NUMBER)
    {
        return;
    }
    else
    {
        node_number = n;
        nodes = new node[n];
    }
     
}

Graph::~Graph(){ delete[] nodes; }

void Graph::add_edge(int s, int t, int cost)
{
    nodes[s].add_neighbour(t, cost);
    nodes[t].add_neighbour(s, cost);
}

int Graph::get_cost(int s, int t)
{
    if (s == t)
    {
        return 0;
    }
    
    edge* p = nodes[s].neighbour;
    while (p)
    {
        if (p->node == t)
        {
            return p->cost;
        }
        p = p->next;
    }
    return -1;
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
                if(c != -1 && (d[i] == -1 || c + hn.cost < d[i]))
                {
                    d[i] = c + hn.cost;
                    path[i] = hn.node;
                    heap->push(heap_node(i, d[i]));
                }
            }
        }
    }
}