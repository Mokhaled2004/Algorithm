// GROUP:   2
// ID:      20225056
// Assign:  04
// Assign:  CountInv
// UVA:     10810
// Name:    Mohamed Khaled AbdElhakim Bayoumi

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

long long CountInvMerge(long long *a, long long *temp, int left, int mid, int right);
long long CountInv(long long *a, long long *temp, int left, int right);

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int n;
    while (cin >> n && n != 0)
    {
        long long *a = new long long[n];
        long long *temp = new long long[n];

        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }

        long long inversionCount = CountInv(a, temp, 0, n - 1);

        cout << inversionCount << endl;

        delete[] a;
        delete[] temp;
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

long long CountInvMerge(long long *a, long long *temp, int left, int mid, int right)
{
    long long i = left;
    long long j = mid + 1;
    long long k = left;
    long long inversionCount = 0;

    while (i <= mid && j <= right)
    {
        if (a[i] <= a[j])
        {
            temp[k++] = a[i++];
        }
        else
        {
            temp[k++] = a[j++];
            inversionCount += (mid - i + 1);
        }
    }

    while (i <= mid)
    {
        temp[k++] = a[i++];
    }

    while (j <= right)
    {
        temp[k++] = a[j++];
    }

    for (i = left; i <= right; i++)
    {
        a[i] = temp[i];
    }

    return inversionCount;
}

long long CountInv(long long *a, long long *temp, int left, int right)
{
    long long inversionCount = 0;
    if (left < right)
    {
        int mid = (left + right) / 2;

        inversionCount += CountInv(a, temp, left, mid);
        inversionCount += CountInv(a, temp, mid + 1, right);
        inversionCount += CountInvMerge(a, temp, left, mid, right);
    }
    return inversionCount;
}
