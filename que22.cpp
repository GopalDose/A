#include <iostream>
using namespace std;

class Student
{
    string name;
    int marks;

public:
    Student()
    {
        name = "";
        marks = 0;
    }

    Student(string name, int marks)
    {
        this->name = name;
        this->marks = marks;
    }
    void getData()
    {
        cout << "Enter Name of student: ";
        cin >> name;
        cout << "Enter Marks of Student: ";
        cin >> marks;
    }

    void display()
    {
        cout << "Name: " << name << " Marks: " << marks << endl;
    }

    friend class Heap;
};

class Heap
{
    Student **heap;
    int capicity;
    int size;

    int parent(int i)
    {
        return i / 2;
    }

    int left(int i)
    {
        return i * 2 + 1;
    }

    int right(int i)
    {
        return i * 2 + 2;
    }

    void swap(Student *&a, Student *&b)
    {
        Student *t = a;
        a = b;
        b = t;
    }

public:
    Heap(int cap)
    {
        capicity = cap;
        heap = new Student *[capicity];
        size = 0;
    }

    void heapfy(int i)
    {
        int l = left(i);
        int r = right(i);
        int largest = i;

        if (l < size && heap[l]->marks > heap[largest]->marks)
        {
            largest = l;
        }
        if (r < size && heap[r]->marks > heap[largest]->marks)
        {
            largest = r;
        }

        if (largest != i)
        {
            swap(heap[largest], heap[i]);
            heapfy(largest);
        }
    }

    void insert(Student *s)
    {
        if (size == capicity)
        {
            cout << "Overflow" << endl;
            return;
        }
        size++;

        int curr = size - 1;
        heap[curr] = s;

        while (curr > 0 && heap[curr]->marks > heap[parent(curr)]->marks)
        {
            swap(heap[curr], heap[parent(curr)]);
            curr = parent(curr);
        }
    }

    Student *extractMax()
    {
        if (size == 0)
        {
            return nullptr;
        }

        Student *t = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapfy(0);
        return t;
    }
};

void heapSort(Student *arr[], int n)
{
    Heap h(n);

    for (int i = 0; i < n; i++)
    {
        h.insert(arr[i]);
    }
    for (int i = n - 1; i >= 0; i--)
    {
        arr[i] = h.extractMax();
    }
}

int main()
{
    int numStudents;
    int ch;

    cout << "Enter No of Students: ";
    cin >> numStudents;

    Student *stu[numStudents];
    Student s;

    do
    {
        cout << "======== MENU ========" << endl;
        cout << "1. Add Students" << endl;
        cout << "2. Print Students" << endl;
        cout << "3. Sort Students" << endl;
        cout << "4. Max Mark Students" << endl;
        cout << "7. Exit" << endl;
        cout << "=====================" << endl;
        cout << "Enter The Choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
        {
            for (int i = 0; i < numStudents; i++)
            {
                Student *new_student = new Student();
                new_student->getData();
                stu[i] = new_student;
            }
            cout << "Students Added!" << endl;
            break;
        }
        case 2:
            for (int i = 0; i < numStudents; i++)
            {
                stu[i]->display();
            }
            break;
        case 3:
        {
            cout << "Sorted Students: " << endl;
            heapSort(stu, numStudents);
            for (int i = 0; i < numStudents; i++)
            {
                stu[i]->display();
            }
            break;
        }
        case 4:
        {
            cout << "Student with Max Marks: " << endl;
            stu[numStudents - 1]->display();
            break;
        }
        case 7:
        {
            cout << "Exiting... Thank You" << endl;
            break;
        }
        }

    } while (ch != 7);
}