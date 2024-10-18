// GROUP:   2
// ID:      20225056
// Assign:  03
// Assign:  Graphs
// UVA:     924
// Name:    Mohamed Khaled Abdelhakim Bayoumi

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////


template <class Value>
struct Array
{

    int  n, size;
	Value* arr;

    void Initialize() {
        n = 0;
        size = 1;
        arr = new Value[size];
    }

    void Destroy() {
        delete[] arr;
        n = 0; 
        size = 0;
    }

    void AddLast(Value v) {
        if (n == size) {
            size = size *2;
            Value *newarr = new Value[size];

            for (int i = 0; i < n ; i++) {
                newarr[i] = arr[i];
            }

            delete[] arr;
            arr = newarr;
        }

        arr[n++] = v;
    }


    void RemoveLast() {
        if (n > 0) {
            n--;
        }   
    }


    Value& operator[](int i) {
        return arr[i];
    }

};


////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Node
{
	Array<int> adj;

	void Initialize() {
        adj.Initialize();
    }
	void Destroy() {
        adj.Destroy();
    }
};

struct Graph
{
	int n;
	Node* nodes;

	void Initialize(int _n) {
        n =_n;
        nodes = new Node [n];
        for (int i = 0; i< n;i++) {
            nodes[i].Initialize();
        }
    }


	void Destroy() {
        for (int i = 0; i< n;i++) {
            nodes[i].Destroy();
        }
        delete[] nodes;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class Type>
struct Queue {
    int f, n, sz;  
    Type* elems;

    void Initialize(int size) {
        sz = size;  
        f = 0;
        n = 0;
        elems = new Type[sz];
    }

    void Destroy() {
        delete[] elems;
        sz = 0;
        n = 0;
        f = 0;
    }

    void Add(Type t) {
        if (n == sz) {
            sz = sz * 2;
            Type *newelems = new Type [sz];
            for (int i = 0; i < n; i++) {
                newelems[i] = elems[(f + i)%sz];
            }
            delete[] elems;
            elems = newelems;
            f = 0;
        }

        elems[(f + n)%sz] = t;
        n++;
    }

    Type Pop() {
        if (n > 0) {
            Type elementtopop = elems[f];
            f = (f + 1) % sz;
            n--;
            return elementtopop;
        }
        throw "Queue is empty";
    }

    Type Peek() {
        if (n > 0) {
            return elems[f];
        }
        throw "Queue is empty";
    }

    int Num() {
        return n;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {

    int E;
    cin >> E;

    Graph graph;
    graph.Initialize(E);

    // Read friendships
    for (int i = 0; i < E; i++) {
        int numberOfFriends;
        cin >> numberOfFriends;

        for (int j = 0; j < numberOfFriends; j++) {
            int friendIndex;
            cin >> friendIndex;
            graph.nodes[i].adj.AddLast(friendIndex);
        }
    }

    int T;
    cin >> T;

    while (T != 0) {
        int source;
        cin >> source;

        Queue<int> queue;
        queue.Initialize(2);  

        queue.Add(source);
        int day = 0;
        int maxHearersInADay = 0;  
        int firstBoomDay = -1; 

        bool heard[E] = {false};  
        heard[source] = true;  

        while (queue.Num() > 0) {
            int newHearersToday = queue.Num();  

            if (newHearersToday > maxHearersInADay) {
                maxHearersInADay = newHearersToday;
                firstBoomDay = day;
            }

            for (int i = 0; i < newHearersToday; i++) {
                int currentEmployee = queue.Pop();

                for (int j = 0; j < graph.nodes[currentEmployee].adj.n; j++) {
                    int friendIdx = graph.nodes[currentEmployee].adj[j];
                    if (!heard[friendIdx]) {
                        heard[friendIdx] = true;  
                        queue.Add(friendIdx);  
                    }
                }
            }

            day++;
        }

        

        if (maxHearersInADay == 1) {
            cout << "0" << endl;
        } else {
            cout << maxHearersInADay << " " << firstBoomDay << endl;
        }
        T--;

    }

    graph.Destroy();
    return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////