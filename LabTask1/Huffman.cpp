#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

class Node
{
public:
    char data;
    int freq;
    Node *left;
    Node *right;

    Node(char d, int f) : data(d), freq(f), left(nullptr), right(nullptr) {}
};

class MinHeap
{
private:
    int size;
    int capacity;
    Node **array;

    void heapify(int index)
    {
        int parent = (index - 1) / 2;
        if (parent >= 0 && array[parent]->freq > array[index]->freq)
        {
            swap(array[parent], array[index]);
            heapify(parent);
        }
    }

    void heapifyExtract(int index)
    {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < size && array[left]->freq < array[smallest]->freq)
        {
            smallest = left;
        }

        if (right < size && array[right]->freq < array[smallest]->freq)
        {
            smallest = right;
        }

        if (smallest != index)
        {
            swap(array[index], array[smallest]);
            heapifyExtract(smallest);
        }
    }

public:
    MinHeap(int cap) : size(0), capacity(cap)
    {
        array = new Node *[cap];
    }

    int getSize()
    {
        return size;
    }

    void insert(Node *node)
    {
        if (size == capacity)
        {
            cout << "Heap is full" << endl;
            return;
        }

        array[size] = node;
        size++;
        heapify(size - 1);
    }

    Node *extractMin()
    {
        if (size == 0)
        {
            cout << "Heap is empty" << endl;
            return nullptr;
        }

        Node *min = array[0];
        array[0] = array[size - 1];
        size--;
        heapifyExtract(0);
        return min;
    }

    bool isEmpty()
    {
        return size == 0;
    }
};

Node *buildHuffmanTree(char data[], int freq[], int size)
{
    MinHeap heap(size);
    for (int i = 0; i < size; i++)
    {
        heap.insert(new Node(data[i], freq[i]));
    }

    while (heap.getSize() > 1)
    {
        Node *left = heap.extractMin();
        Node *right = heap.extractMin();
        Node *parent = new Node('ParentName', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        heap.insert(parent);
    }

    return heap.extractMin();
}

void printCodes(Node *root, int arr[], int currentinx)
{
    if (root->left)
    {
        arr[currentinx] = 0;
        printCodes(root->left, arr, currentinx + 1);
    }

    if (root->right)
    {
        arr[currentinx] = 1;
        printCodes(root->right, arr, currentinx + 1);
    }

    if (!root->left && !root->right)
    {
        cout << root->data << "--> ";
        for (int i = 0; i < currentinx; i++)
        {
            cout << arr[i];
        }
        cout << endl;
    }
}

void huffmanCodes(char data[], int freq[], int size)
{
    Node *root = buildHuffmanTree(data, freq, size);
    int arr[100], currentinx = 0;
    printCodes(root, arr, currentinx);
}

int main()
{
    string message;
    cout << "Enter the message to encode: ";
    cin >> message;

    char data[256];
    int freq[256];
    int size = 0;

    for (int i = 0; i < message.length(); i++)
    {
        char currentChar = message[i];
        bool found = false;

        for (int j = 0; j < size; j++)
        {
            if (data[j] == currentChar)
            {
                freq[j]++;
                found = true;
                break;
            }
        }

        if (!found)
        {
            data[size] = currentChar;
            freq[size] = 1;
            size++;
        }
    }

    huffmanCodes(data, freq, size);

    return 0;
}
