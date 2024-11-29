// GROUP:   2
// ID:      20225056
// Assign:  08
// Assign:  ClosetsPair
// UVA:     10245
// Name:    Mohamed Khaled AbdElhakim Bayoumi

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath> // please use the built-in sqrt() function
using namespace std;

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
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i < mid)
        temp[k++] = a[i++];

    while (j < n)
        temp[k++] = a[j++];

    for (i = 0; i < n; ++i)
        a[i] = temp[i];

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

struct Point
{
    double x, y;
};

bool IsBeforeX(Point &a, Point &b)
{
    return a.x < b.x;
}

// Compare points based on their y-coordinate
bool IsBeforeY(Point &a, Point &b)
{
    return a.y < b.y;
}

double dist(Point &a, Point &b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ClosestPair(Point *p, int n)
{
    if (n <= 1)
        return 1e20;

    if (n == 2)
        return dist(p[0], p[1]);
    if (n == 3)
    {
        return min(dist(p[0], p[1]), min(dist(p[0], p[2]), dist(p[1], p[2])));
    }

    int mid = n / 2;
    double midX = p[mid].x;

    double d1 = ClosestPair(p, mid);
    double d2 = ClosestPair(p + mid, n - mid);

    double d = min(d1, d2);

    Point *strip = new Point[n];
    int stripSize = 0;
    for (int i = 0; i < n; ++i)
    {
        if (fabs(p[i].x - midX) < d)
        {
            strip[stripSize++] = p[i];
        }
    }

    MergeSort(strip, stripSize, IsBeforeY);

    for (int i = 0; i < stripSize; ++i)
    {
        for (int j = i + 1; j < stripSize && (strip[j].y - strip[i].y) < d; ++j)
        {
            d = min(d, dist(strip[i], strip[j]));
        }
    }

    delete[] strip;
    return d;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int N;

    while (true)
    {
        cin >> N;

        if (N == 0)
            break;

        Point *points = new Point[N];

        for (int i = 0; i < N; ++i)
        {
            cin >> points[i].x >> points[i].y;
        }

        MergeSort(points, N, IsBeforeX);

        double result = ClosestPair(points, N);

        if (result < 10000)
        {
            printf("%.4f\n", result);
        }
        else
        {
            printf("INFINITY\n");
        }

        delete[] points;
    }

    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////