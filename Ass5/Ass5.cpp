// GROUP:   2
// ID:      20225056
// Assign:  05
// Assign:  Kruskal
// UVA:     11631
// Name:    Mohamed Khaled AbdElhakim Bayoumi

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DisjointSets
{
    int n;
    int *parent;
    int *num_nodes;

    void Initialize(int _n)
    {
        n = _n;
        parent = new int[n];
        num_nodes = new int[n];

        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            num_nodes[i] = 1;
        }
    }

    void Destroy()
    {
        delete[] parent;
        delete[] num_nodes;
    }

    int Find(int i)
    {
        if (parent[i] == i)
        {
            return i;
        }
        else
        {
            return parent[i] = Find(parent[i]);
        }
    }

    bool Union(int i, int j)
    {
        int iroot = Find(i);
        int jroot = Find(j);

        if (iroot == jroot)
        {
            return false;
        }

        if (num_nodes[iroot] < num_nodes[jroot])
        {
            parent[iroot] = jroot;
            num_nodes[jroot] += num_nodes[iroot];
        }
        else
        {
            parent[jroot] = iroot;
            num_nodes[iroot] += num_nodes[jroot];
        }

        return true;
    }
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Type>
void Merge(Type *a, int n, bool (*IsBefore)(Type &a, Type &b))
{
    int mid = n / 2;
    int i = 0, j = mid, k = 0;

    Type *temp = new Type[n];

    while (i < mid && j < n)
    {
        if (IsBefore(a[i], a[j]))
        {
            temp[k++] = a[i++];
        }
        else
        {
            temp[k++] = a[j++];
        }
    }

    while (i < mid)
    {
        temp[k++] = a[i++];
    }

    while (j < n)
    {
        temp[k++] = a[j++];
    }

    for (i = 0; i < n; i++)
    {
        a[i] = temp[i];
    }

    delete[] temp;
}

template <class Type>
void MergeSort(Type *a, int n, bool (*IsBefore)(Type &a, Type &b))
{
    if (n <= 1)
        return;

    int mid = n / 2;

    MergeSort(a, mid, IsBefore);
    MergeSort(a + mid, n - mid, IsBefore);

    Merge(a, n, IsBefore);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
    int u, v;
    int w;
};

bool IsBeforeEdge(Edge &a, Edge &b)
{
    return a.w < b.w;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int m, n;

    while (true)
    {

        cin >> m >> n;

        if (m == 0 && n == 0)
        {
            break;
        }

        Edge *edges = new Edge[n];

        for (int i = 0; i < n; i++)
        {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
        }

        MergeSort(edges, n, IsBeforeEdge);

        DisjointSets ds;
        ds.Initialize(m);

        int totalWeight = 0;
        int MSTWeight = 0;

        for (int i = 0; i < n; i++)
        {
            totalWeight += edges[i].w;
        }

        for (int i = 0; i < n; i++)
        {
            if (ds.Union(edges[i].u, edges[i].v))
            {
                MSTWeight += edges[i].w;
            }
        }

        int savedWeight = totalWeight - MSTWeight;
        cout << savedWeight << endl;

        ds.Destroy();
        delete[] edges;
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////