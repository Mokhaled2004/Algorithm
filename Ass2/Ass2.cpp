// GROUP:   2
// ID:      20225056
// Assign:  02
// Assign:  DisjointSets
// UVA:     10608
// Name:    Mohamed Khaled Abdelhakim bayoumi

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;


////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DisjointSets
{
	int n;
	int* parent;
	int* num_nodes;

	void Initialize(int _n) {
        n = _n;
        parent = new int[n];
        num_nodes = new int[n];

        for (int i = 0; i< n;i++) {
            parent[i] = i;
            num_nodes[i] = 1;
        }
    }

    void Destroy() {
        delete[] parent;
        delete[] num_nodes;
    }


    int Find(int i) {
        if (parent[i] == i)  {
            return i;
        } else {
            return parent[i] = Find(parent[i]);
        }
    }

    bool Union(int i, int j) {
        int iroot = Find(i);
        int jroot = Find(j);


        if (iroot == jroot) {
            return false;
        } 

        if (num_nodes[iroot]< num_nodes[jroot]) {
            parent[iroot] = jroot;
            num_nodes[jroot] += num_nodes[iroot];
        } else {
            parent[jroot] = iroot;
            num_nodes[iroot] += num_nodes[jroot];
        }

        return true;
    }
	
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int testcases;

    cin >> testcases;

    while (testcases != 0) {
        int n;
        int m;

        cin >>n >> m;

        DisjointSets ds;
        ds.Initialize(n);

            for( int i = 0; i< m;i++) {
                int a;
                int b;

                cin >> a >> b;

                ds.Union(a-1,b-1);
            }

            int largestFriendshipGroup = 0;
            for (int i = 0 ; i< n;i++) {

                int root = ds.Find(i);
                if (ds.num_nodes[root] > largestFriendshipGroup) {
                    largestFriendshipGroup = ds.num_nodes[root];
                }

            }

            cout << largestFriendshipGroup << endl;

            ds.Destroy();

            testcases--;


    }
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////