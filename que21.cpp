#include <iostream>

using namespace std;

class MaxHeap
{

    int *heap;
    int capacity;
    int size;

    int parent(int i)
    {
        return (i / 2);
    }
    int leftChild(int i)
    {
        return 2 * i + 1;
    }
    int rightChild(int i)
    {
        return 2 * i + 2;
    }

    void swap(int &a, int &b)
    {
        int temp = a;
        a = b;
        b = temp;
    }

    void maxHeapify(int i)
    {
        int left = leftChild(i);
        int right = rightChild(i);
        int largest = i;

        if (left < size && heap[left] > heap[largest])
        {
            largest = left;
        }

        if (right < size && heap[right] > heap[largest])
        {
            largest = right;
        }
        if (largest != i)
        {
            swap(heap[i], heap[largest]);
            maxHeapify(largest);
        }
    }

public:
    MaxHeap(int capacity)
    {
        this->capacity = capacity;
        heap = new int[capacity];
        size = 0;
    }

    void insert(int num)
    {
        if (size == capacity)
        {
            return;
        }
        size++;

        int currentIndex = size - 1;
        heap[currentIndex] = num;

        while (currentIndex > 0 && heap[currentIndex] > heap[parent(currentIndex)])
        {
            swap(heap[currentIndex], heap[parent(currentIndex)]);
            currentIndex = parent(currentIndex);
        }
    }

    int extractMax()
    {
        if (size == 0)
            return 0;

        int num = heap[0];
        heap[0] = heap[size - 1];
        size--;
        maxHeapify(0);

        return num;
    }
};

void heapSort(int arr[], int n)
{
    MaxHeap maxHeap(n);

    for (int i = 0; i < n; i++)
    {
        maxHeap.insert(arr[i]);
    }

    for (int i = n - 1; i >= 0; i--)
    {
        arr[i] = maxHeap.extractMax();
    }
}

int main()
{

    int ch;
    int entries;

    cout << "Enter No. of entrie: ";
    cin >> entries;
    bool flag = true;

    int Data[entries];
    int num;

    while (flag)
    {

        cout << "\n===== Heap Sort =====" << endl;
        cout << "1. Add Data" << endl;
        cout << "2. Sort Data" << endl;
        cout << "3 Print Max Data" << endl;
        cout << "----------------------" << endl;
        cout << "\n Enter Your choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
        {

            for (int i = 0; i < entries; i++)
            {
                cout << "Enter Data : ";
                cin >> num;
                Data[i] = num;
            }
            cout << "Data Added!" << endl;
            break;
        }
        case 2:
        {
            cout << "Sorted Data: " << endl;
            heapSort(Data, entries);
            for (int i = 0; i < entries; i++)
            {
                cout << i + 1 << ". " << Data[i] << endl;
            }
            break;
        }
        case 3:
        {
            cout << "Max Data ";
            cout << Data[entries - 1] << endl;
            break;
        }
        case 4:
        {
            cout << "Exiting... Thank You" << endl;
            flag = false;
            break;
        }
        default:
        {
            cout << "Invalid Input" << endl;
            break;
        }
        }
    }

    return 0;
}