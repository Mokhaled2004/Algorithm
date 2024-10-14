// GROUP:   2
// ID:      20225056
// Assign:  01
// Assign:  ArrayHeap
// UVA:     10954
// Name:    Mohamed Khaled Abdelhakim Bayoumi

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;


template <class Value>
struct Array
{

    int  n, sz;
	Value* arr;

    void Initialize() {
        n = 0;
        sz = 1;
        arr = new Value[sz];
    }

    void Destroy() {
        delete[] arr;
        n = 0; 
        sz = 0;
    }

    void AddLast(Value v) {
        if (n == sz) {
            sz = sz *2;
            Value *newarr = new Value[sz];

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


template<class Elem>
struct Heap
{
	Array<Elem> a;
	bool (*IsBefore)(Elem&, Elem&);

    void Initialize(bool (*_IsBefore)(Elem&, Elem&)) {
        a.Initialize();
        IsBefore = _IsBefore;
    }

    void Destroy() {
        a.Destroy();
    }

    int Child(int i) {
        return 2*i + 1;
    }

    int Parent(int i) {
        return (i-1)/2;
    }

    void MoveUp(int ind) {
         while (ind > 0 && IsBefore(a[ind], a[Parent(ind)])) {
            swap(a[ind], a[Parent(ind)]);
            ind = Parent(ind);          
        }
    }

    void MoveDown(int ind) {
        int size = a.n;
        int leftChild = Child(ind);
        int rightChild = leftChild + 1; 

        int smallest = ind;

        
        if (leftChild < size && IsBefore(a[leftChild], a[smallest])) {
            smallest = leftChild;
        }

        
        if (rightChild < size && IsBefore(a[rightChild], a[smallest])) {
            smallest = rightChild;
        }

        
        if (smallest != ind) {
            swap(a[ind], a[smallest]);
            MoveDown(smallest); 
        }

    }

    void Add(Elem e) {
        a.AddLast(e);
        MoveUp(a.n - 1);
    }

    Elem GetFirst() {
        if (a.n != 0) {
            return a[0];
        }
        else {
            cout << "Heap is empty" << endl;
            return -1;
        }
    }

    Elem RetrieveFirst() {
        if (a.n != 0) {
            Elem firstelem = a[0];
            a[0] = a[a.n - 1];
            a.RemoveLast();
            MoveDown(0);
            return firstelem;
        }
        else {
            cout << "Heap is empty" << endl;
            return -1;
        }
    }

};

bool IsBeforeInt(int& a, int& b)
{
	return a<b;
}


int main() {
    while (true) {
        int number;
        cin >> number;

        if (number == 0) break;  

        Heap<int> heap;
        heap.Initialize(IsBeforeInt);

        for (int i = 0; i < number; i++) {
            int num;
            cin >> num;
            heap.Add(num);
        }

        int totalCost = 0;

        while (heap.a.n > 1) {
            int first = heap.RetrieveFirst();
            int second = heap.RetrieveFirst();
            int sum = first + second;
            totalCost += sum;
            heap.Add(sum);
        }

        cout << totalCost << endl;

        heap.Destroy();
    }

    return 0;
}