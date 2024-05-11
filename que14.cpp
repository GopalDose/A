#include <iostream>
using namespace std;
#define size 10

class TelephonrDir
{
    long hashTable[size];

public:
    TelephonrDir()
    {
        for (int i = 0; i < size; i++)
        {
            hashTable[i] = -1;
        }
    }

    int hash(int key)
    {
        return key % size;
    }

    void insertWithoutReplacement()
    {
        int num;
        cout << "Enter a Number: ";
        cin >> num;

        int index = hash(num);
        int original = index;
        while (hashTable[index] != -1)
        {
            index++;
            index %= size;
            if (index == original)
            {
                cout << "The Table is Full" << endl;
                return;
            }
        }

        hashTable[index] = num;
        cout << "The Data inserted Successfully" << endl;
    }

    void insertWithReplacement()
    {
        int num;
        cout << "Enter a Number: ";
        cin >> num;

        int index = hash(num);
        if (hashTable[index] != -1)
        {
            int hash2 = hash(hashTable[index]);

            if (hash2 == index)
            {
                int original = index;
                while (hashTable[index] != -1)
                {
                    index++;
                    index %= size;
                    if (index == original)
                    {
                        cout << "The Table is Full" << endl;
                        return;
                    }
                }

                hashTable[index] = num;
                cout << "The Data inserted Successfully" << endl;
            }
            else
            {
                int val = hashTable[index];
                hashTable[index] = num;
                int original = hash2;
                while (hashTable[hash2] != -1)
                {
                    hash2++;
                    hash2 %= size;
                    if (hash2 == original)
                    {
                        cout << "The Table is Full" << endl;
                        return;
                    }
                }

                hashTable[hash2] = val;
                cout << "The Data inserted Successfully" << endl;
            }
        }
        else
        {
            hashTable[index] = num;
        }
    }

    void print()
    {
        for (int i = 0; i < size; i++)
        {
            cout << "[" << i << "] ->" << hashTable[i] << endl;
        }
    }

    void search()
    {
        int val;
        cout << "Enter the number to search:";
        cin >> val;

        int index = hash(val);
        if (hashTable[index] == -1)
        {
            cout << "Data not found" << endl;
            return;
        }
        else
        {
            int original = index;
            while (hashTable[index] != val)
            {
                index++;
                if (original == index)
                {
                    cout << "Data not found" << endl;
                    return;
                }
            }
            cout << "The Key is Found at: " << index << endl;
            return;
        }
    }
};

int main()
{
    TelephonrDir td;
    int choice;

    do
    {
        cout << "========== MENU ==========" << endl;
        cout << "1. Insert Without Replacement" << endl;
        cout << "2. Insert With Replacement" << endl;
        cout << "3. Print" << endl;
        cout << "4. Search" << endl;
        cout << "7. Exit" << endl;
        cout << "==========================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            td.insertWithoutReplacement();
            break;
        case 2:
            td.insertWithReplacement();
            break;
        case 3:
            td.print();
            break;
        case 4:
            td.search();
            break;
        case 7:
            cout << "Exit......" << endl;
        default:
            break;
        }
    } while (choice != 7);
}