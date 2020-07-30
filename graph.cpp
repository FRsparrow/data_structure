#include <iostream>
#include "myheaders/graph.h"

using namespace std;

int main()
{
    const int node_number = 5;
    Graph* graph = new Graph(node_number);
    graph->add_edge(0, 1, 1);
    graph->add_edge(0, 2, 3);
    graph->add_edge(0, 3, 2);
    graph->add_edge(0, 4, 8);
    graph->add_edge(1, 4, 4);
    graph->add_edge(2, 3, 7);
    graph->add_edge(2, 4, 5);
    graph->add_edge(3, 4, 1);

    int d[node_number], path[node_number];
    for (int i = 0; i < node_number; i++)
    {
        graph->dijkstra(i, d, path);
        for (int j = 0; j < node_number; j++)
        {
            cout << i << "到" << j << "路径长度为" << d[j] << "，反向路径为:";
            int n = j;
            while (n != i)
            {
                cout << n << " ";
                n = path[n];
            }
            cout << i << endl;
        }
        cout << endl;
    }
    
    system("pause");
    return 0;
}