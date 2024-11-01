// GROUP:   2
// ID:      20225056
// Assign:  06
// Assign:  Prim
// UVA:     534
// Name:    Mohamed Khaled Abdelhakim Bayoumi

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
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

struct Edge
{
    int v;    // id of the adjacent node
    double w; // edge weight = distance between the two nodes
};

struct Node
{
    int x, y; // x and y coordinates of the node
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
        for (int i = 0; i < n; i++)
        {
            nodes[i].Initialize();
        }
    }

    void Destroy()
    {
        for (int i = 0; i < n; i++)
        {
            nodes[i].Destroy();
        }
        delete[] nodes;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Find the square root of "v" in "n" iterations
double Sqrt(double v, int n = 100)
{
    if (v < 0)
        return -1;
    if (v == 0)
        return 0;

    double x = v;

    for (int i = 0; i < n; i++)
    {
        x = 0.5 * (x + v / x);
    }
    return x;
}

double CalculateDistance(int x1, int y1, int x2, int y2)
{
    return Sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

double Prim(Graph &g, int startIndex, int goalIndex)
{
    const double INF = 1e9;
    double minDistance[200];
    bool visited[200] = {false};

    for (int i = 0; i < g.n; ++i)
    {
        minDistance[i] = INF;
    }
    minDistance[startIndex] = 0;

    for (int count = 0; count < g.n; ++count)
    {
        int u = -1;
        for (int i = 0; i < g.n; ++i)
        {
            if (!visited[i] && (u == -1 || minDistance[i] < minDistance[u]))
            {
                u = i;
            }
        }

        if (u == -1)
            break;

        visited[u] = true;

        for (int i = 0; i < g.nodes[u].adj.n; ++i)
        {
            Edge edge = g.nodes[u].adj[i];
            int v = edge.v;
            double weight = edge.w;

            if (!visited[v])
            {
                minDistance[v] = min(minDistance[v], max(minDistance[u], edge.w));
            }
        }
    }

    return minDistance[goalIndex];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int caseNumber = 1;

    while (true)
    {
        int n;
        cin >> n;
        if (n == 0)
            break;

        Graph g;
        g.Initialize(n);

        for (int i = 0; i < n; ++i)
        {
            cin >> g.nodes[i].x >> g.nodes[i].y;
        }

        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                double distance = CalculateDistance(g.nodes[i].x, g.nodes[i].y, g.nodes[j].x, g.nodes[j].y);
                g.nodes[i].adj.AddLast({j, distance});
                g.nodes[j].adj.AddLast({i, distance});
            }
        }

        double result = Prim(g, 0, 1);

        cout << "Scenario #" << caseNumber++ << endl;
        cout << "Frog Distance = " << fixed << setprecision(3) << result << endl;
        cout << endl;

        g.Destroy();
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
