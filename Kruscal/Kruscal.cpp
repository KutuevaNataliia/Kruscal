#include <iostream>
#include <fstream>
#include <cstdlib>

struct Edge {
    int weight;
    char start;
    char finish;
};

int comp(const int* i, const int* j)
{
    return *i - *j;
}

void init(int n, int* parent)
{
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
    }
}
int getRep(int i, int* parent)
{
    if (parent[i] != i)
    {
        parent[i] = getRep(parent[i], parent);
    }
    return parent[i];
}

void link(int u, int v, int* parent)
{
    int tu = getRep(u, parent);
    int tv = getRep(v, parent);
    if (tu == tv)
        return;
    if (std::rand() % 2)
    {
        parent[u] = v;
    }
    else {
        parent[v] = u;
    }
}

int kruscal(Edge* edges, int n, int m)
{
    int cost = 0;
    int* parent = new int[n];
    init(n, parent);
    for (int i = 0; i < m; i++)
    {
        int u = getRep(edges[i].start - 'a', parent);
        int v = getRep(edges[i].finish - 'a', parent);
        if (u != v)
        {
            std::cout << edges[i].start << ' ' << edges[i].finish << std::endl;
            cost += edges[i].weight;
            link(u, v, parent);
        }
    }
    return cost;
}

int main()
{
    int n, m;
    std::ifstream input("test1.txt");
    if (!input)
    {
        exit(1);
    }
    input >> n >> m;
    Edge* edges = new Edge[m];
    for (int i = 0; i < m; i++)
    {
        input >> edges[i].start >> edges[i].finish >> edges[i].weight;
    }
    input.close();

    std::qsort(edges, m, sizeof * edges, (int(*) (const void*, const void*)) comp);

    int cost = kruscal(edges, n, m);
    std::cout << "Cost = " << cost << std::endl;
}