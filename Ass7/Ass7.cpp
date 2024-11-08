// GROUP:   2
// ID:      20225056
// Assign:  07
// Assign:  Dijkstra
// UVA:     10986
// Name:    Mohamed Khaled AbdElhakim Bayoumi

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits.h>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Value>
struct Array
{

    int n, sz;
    Value *arr;

    void Initialize()
    {
        n = 0;
        sz = 1;
        arr = new Value[sz];
    }

    void Destroy()
    {
        delete[] arr;
        n = 0;
        sz = 0;
    }

    void AddLast(Value v)
    {
        if (n == sz)
        {
            sz = sz * 2;
            Value *newarr = new Value[sz];

            for (int i = 0; i < n; i++)
            {
                newarr[i] = arr[i];
            }

            delete[] arr;
            arr = newarr;
        }

        arr[n++] = v;
    }

    void RemoveLast()
    {
        if (n > 0)
        {
            n--;
        }
    }

    Value &operator[](int i)
    {
        return arr[i];
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Elem>
struct Heap
{
    Array<Elem> a;
    int *pos;
    bool (*IsBefore)(Elem &, Elem &);

    void Initialize(bool (*_IsBefore)(Elem &, Elem &), int n)
    {
        a.Initialize();
        IsBefore = _IsBefore;
        pos = new int[n];
        for (int i = 0; i < n; ++i)
            pos[i] = -1;
    }

    void Destroy()
    {
        a.Destroy();
        delete[] pos;
    }

    int Child(int i)
    {
        return 2 * i + 1;
    }

    int Parent(int i)
    {
        return (i - 1) / 2;
    }

    void MoveUp(int ind)
    {
        while (ind > 0 && IsBefore(a[ind], a[Parent(ind)]))
        {
            swap(a[ind], a[Parent(ind)]);

            pos[a[ind].v] = ind;
            pos[a[Parent(ind)].v] = Parent(ind);
            ind = Parent(ind);
        }
    }

    void MoveDown(int ind)
    {
        int size = a.n;
        int leftChild = Child(ind);
        int rightChild = leftChild + 1;
        int smallest = ind;

        if (leftChild < size && IsBefore(a[leftChild], a[smallest]))
        {
            smallest = leftChild;
        }

        if (rightChild < size && IsBefore(a[rightChild], a[smallest]))
        {
            smallest = rightChild;
        }

        if (smallest != ind)
        {
            swap(a[ind], a[smallest]);

            pos[a[ind].v] = ind;
            pos[a[smallest].v] = smallest;
            MoveDown(smallest);
        }
    }

    void Add(Elem e)
    {
        a.AddLast(e);
        pos[e.v] = a.n - 1;
        MoveUp(a.n - 1);
    }

    Elem GetFirst()
    {
        if (a.n != 0)
        {
            return a[0];
        }
        else
        {
            cout << "Heap is empty" << endl;
            return Elem();
        }
    }

    Elem RetrieveFirst()
    {
        if (a.n != 0)
        {
            Elem firstElem = a[0];
            pos[firstElem.v] = -1;
            a[0] = a[a.n - 1];
            pos[a[0].v] = 0;
            a.RemoveLast();
            MoveDown(0);
            return firstElem;
        }
        else
        {
            cout << "Heap is empty" << endl;
            return Elem();
        }
    }

    void Update(Elem e)
    {
        int index = pos[e.v];
        if (index != -1)
        {
            a[index] = e;

            if (index > 0 && IsBefore(a[index], a[Parent(index)]))
            {
                MoveUp(index);
            }
            else
            {
                MoveDown(index);
            }
        }
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
    int v;
    int w;
};

struct Node
{
    Array<Edge> adj;

    void Initialize()
    {
        adj.Initialize();
    }

    void Destroy()
    {
        adj.Destroy();
    }
};

struct Graph
{
    int n;
    Node *nodes;

    void Initialize(int _n)
    {
        n = _n;
        nodes = new Node[n];
        for (int i = 0; i < n; ++i)
        {
            nodes[i].Initialize();
        }
    }

    void Destroy()
    {
        for (int i = 0; i < n; ++i)
        {
            nodes[i].Destroy();
        }
        delete[] nodes;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBefore(Edge &a, Edge &b)
{
    return a.w < b.w;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        int n, m, S, T;
        cin >> n >> m >> S >> T;

        Graph g;
        g.Initialize(n);

        for (int i = 0; i < m; ++i)
        {
            int u, v, w;
            cin >> u >> v >> w;
            g.nodes[u].adj.AddLast({v, w});
            g.nodes[v].adj.AddLast({u, w});
        }

        int INF = INT_MAX;
        int dist[n];
        bool visited[n];
        for (int i = 0; i < n; ++i)
        {
            dist[i] = INF;
            visited[i] = false;
        }

        dist[S] = 0;
        Heap<Edge> heap;
        heap.Initialize(IsBefore, n);
        heap.Add({S, 0});

        while (heap.a.n > 0)
        {
            Edge current = heap.RetrieveFirst();
            int u = current.v;

            if (visited[u])
                continue;

            visited[u] = true;

            if (u == T)
            {
                cout << "Case #" << t << ": " << dist[u] << endl;
                break;
            }

            for (int i = 0; i < g.nodes[u].adj.n; ++i)
            {
                int v = g.nodes[u].adj[i].v;
                int weight = g.nodes[u].adj[i].w;

                if (dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;
                    heap.Add({v, dist[v]});
                }
            }
        }

        if (dist[T] == INF)
        {
            cout << "Case #" << t << ": unreachable" << endl;
        }

        g.Destroy();
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////