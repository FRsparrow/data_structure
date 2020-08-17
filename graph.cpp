#include <iostream>
#include "myheaders/graph.h"

using namespace std;

void visit(int nn)
{
    if (nn < 0)
    {
        cout << endl;
    }
    else
    {
        cout << nn << " ";
    }
}

int main()
{
    const int node_number = 6, edge_number = 10;
    Graph* graph = new Graph(node_number, edge_number, true);

    // 最小生成树图
    graph->add_edge(0, 1, 6);
    graph->add_edge(0, 2, 1);
    graph->add_edge(0, 3, 5);
    graph->add_edge(1, 2, 5);
    graph->add_edge(1, 4, 3);
    graph->add_edge(2, 3, 5);
    graph->add_edge(2, 4, 6);
    graph->add_edge(2, 5, 4);
    graph->add_edge(3, 5, 2);
    graph->add_edge(4, 5, 6);

    /*
    (2)——————5————————
     |               |
     3  ————8——————  |
     | /            \|
    (0)——1——(1)——4——(4)
      \             /
       2   1————————
        \ /
        (3)
    */
    // 无向图
    // graph->add_edge(0, 1, 1);
    // graph->add_edge(0, 2, 3);
    // graph->add_edge(0, 3, 2);
    // graph->add_edge(0, 4, 8);
    // graph->add_edge(1, 4, 4);
    // graph->add_edge(2, 3, 7);
    // graph->add_edge(2, 4, 5);
    // graph->add_edge(3, 4, 1);

    // 有向图
    // graph->add_edge(0, 1, 6);
    // graph->add_edge(0, 2, 5);
    // graph->add_edge(0, 3, 5);
    // graph->add_edge(1, 4, -1);
    // graph->add_edge(2, 1, -2);
    // graph->add_edge(2, 4, 1);
    // graph->add_edge(3, 2, -2);
    // graph->add_edge(3, 5, -1);
    // graph->add_edge(4, 6, 3);
    // graph->add_edge(5, 6, 3);

    // 拓扑排序图1
    // graph->add_edge(0, 1);
    // graph->add_edge(0, 3);
    // graph->add_edge(1, 5);
    // graph->add_edge(2, 1);
    // graph->add_edge(2, 5);
    // graph->add_edge(4, 0);
    // graph->add_edge(4, 1);
    // graph->add_edge(4, 5);

    // 拓扑排序图2
    // graph->add_edge(0, 2);
    // graph->add_edge(0, 7);
    // graph->add_edge(1, 2);
    // graph->add_edge(1, 3);
    // graph->add_edge(1, 4);
    // graph->add_edge(2, 3);
    // graph->add_edge(3, 5);
    // graph->add_edge(3, 6);
    // graph->add_edge(4, 5);
    // graph->add_edge(7, 8);
    // graph->add_edge(8, 6);

    // 关键路径图
    // graph->add_edge(0, 1, 8);
    // graph->add_edge(0, 2, 12);
    // graph->add_edge(1, 3, 14);
    // graph->add_edge(2, 3, 10);
    // graph->add_edge(2, 5, 28);
    // graph->add_edge(3, 4, 6);
    // graph->add_edge(3, 5, 8);
    // graph->add_edge(4, 6, 18);
    // graph->add_edge(5, 6, 6);
    // graph->add_edge(6, 7, 12);

    // 最小生成树
    auto mst = new Graph(node_number, node_number-1);
    graph->prim(*mst);
    mst->show(visit);

    // int d[node_number], path[node_number];
    // for (int i = 0; i < node_number; i++)
    // {
    //     graph->dijkstra(i, d, path);
    //     for (int j = 0; j < node_number; j++)
    //     {
    //         // if (d[j] >= INF)
    //         // {
    //         //     cout << i << " can't get to " << j << endl;
    //         //     continue;
    //         // }
    //         // cout << i << " to " << j << ": " << d[j] << ",path:";
    //         cout << d[j] << "(";
    //         int n = j;
    //         while (d[j] < INF && n != i)
    //         {
    //             cout << n << "<-";
    //             n = path[n];
    //         }
    //         cout << i << ")\t";
    //         // cout << d[j] << "\t";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    
    // // 使用floyd算法
    // int **a = new int*[node_number], **path2 = new int*[node_number];
    // for (int i = 0; i < node_number; i++)
    // {
    //     a[i] = new int[node_number];
    //     path2[i] = new int[node_number];
    // }
    // graph->floyd(a, path2);
    // for (int i = 0; i < node_number; i++)
    // {
    //     for (int j = 0; j < node_number; j++)
    //     {
    //         cout << a[i][j] << "(";
    //         int n = j;
    //         while (a[i][j] < INF && n != i)
    //         {
    //             cout << n << "<-";
    //             n = path2[i][n];
    //         }
    //         cout << i << ")\t";
    //     }
    //     cout << endl;
    // }
    
    // 拓扑排序
    // int seq[node_number];
    // bool exist_circle = !graph->topological_sort(seq);
    // if (exist_circle)
    // {
    //     cout << "it's an undirected graph or there exists a circle in the directed graph";
    // }
    // else
    // {
    //     cout << seq[0];
    //     for (int i = 1; i < node_number; i++)
    //     {
    //         cout << "->" << seq[i];
    //     }
    // }
    // cout << endl;
    
    // 关键路径
    // int cp[20];
    // for (int i = 0; i < 20; i++)
    // {
    //     cp[i] = -1;
    // }
    // graph->critical_path(cp);
    // for (int i = 0; cp[i] != -1; i++)
    // {
    //     cout << cp[i] << " ";
    // }
    

    system("pause");
    return 0;
}