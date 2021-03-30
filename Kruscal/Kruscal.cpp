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

void init(int n, int* parent, int* w)
{
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
        w[i] = 1;
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

void link(int u, int v, int* parent, int* w)
{
    int tu = getRep(u, parent);
    int tv = getRep(v, parent);
    if (tu == tv)
        return;
    if (std::rand() % 2)
    {
        parent[u] = v;
        w[v] += w[u];
    }
    else {
        parent[v] = u;
        w[u] += w[v];
    }
}

int kruscal(Edge* edges, int n, int m)
{
    int cost = 0;
    int* parent = new int[n];
    int* w = new int[n];
    init(n, parent, w);
    for (int i = 0; i < m; i++)
    {
        int u = getRep(edges[i].start - 'a', parent);
        int v = getRep(edges[i].finish - 'a', parent);
        if (u != v)
        {
            std::cout << edges[i].start << ' ' << edges[i].finish << std::endl;
            cost += edges[i].weight;
            link(u, v, parent, w);
        }
    }
    return cost;
}

int main()
{
    int n, m;
    std::ifstream input("test2.txt");
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

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"
