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
    // Test Array
    Array<int> arr;
    arr.Initialize();

    cout << "Testing Array:" << endl;
    for (int i = 0; i < 10; i++) {
        arr.AddLast(i);
        cout << "Added " << i << ", Array size: " << arr.n << ", Capacity: " << arr.sz << endl;
    }

    cout << "Array contents: ";
    for (int i = 0; i < arr.n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Remove last element
    arr.RemoveLast();
    cout << "Removed last element, new size: " << arr.n << endl;

    // Print final array contents
    cout << "Final Array contents: ";
    for (int i = 0; i < arr.n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    arr.Destroy();

    // Test Heap
    Heap<int> heap;
    heap.Initialize(IsBeforeInt);

    cout << "\nTesting Heap:" << endl;
    for (int i = 10; i > 0; i--) {
        heap.Add(i);
        cout << "Added " << i << ", Heap first element: " << heap.GetFirst() << endl;
    }

    cout << "Heap contents after all additions (retrieve in order): ";
    while (heap.a.n > 0) {
        cout << heap.RetrieveFirst() << " ";
    }
    cout << endl;

    heap.Destroy();

    return 0;
}