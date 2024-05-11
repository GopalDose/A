#include <iostream>
#include <vector>
using namespace std;

class node
{
    string key;
    string value;
    node *next;

public:
    node()
    {
        next = NULL;
    }
    node(string k, string v)
    {
        key = k;
        value = v;
        next = NULL;
    }

    friend class HashTable;
};

class HashTable
{
    static const int TABLE_SIZE = 10;
    vector<node *> hashTable;

public:
    HashTable()
    {
        hashTable = vector<node *>(TABLE_SIZE, nullptr);
    }

    ~HashTable()
    {
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            node *temp = hashTable[i];
            while (temp != nullptr)
            {
                node *prev = temp;
                temp = temp->next;
                delete prev;
            }
        }
    }

    int hash(const string &key)
    {
        int k = key[0];
        return ((3 * k) + 5) % TABLE_SIZE;
    }

    void insert();
    void find(const string &key);
    void print();
    void deleteNode(string key);
};

void HashTable::insert()
{
    string key, value;
    cout << "Enter Key: ";
    cin >> key;
    cout << "Enter its Value: ";
    cin >> value;

    node *temp = new node(key, value);
    int index = hash(key);
    if (hashTable[index] == nullptr)
    {
        hashTable[index] = temp;
    }
    else
    {
        node *current = hashTable[index];
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = temp;
    }
    cout << "Inserted successfully!!!" << endl;
}

void HashTable::find(const string &key)
{
    int index = hash(key);
    node *temp = hashTable[index];
    int c = 1;
    while (temp != nullptr && temp->key != key)
    {
        c++;
        temp = temp->next;
    }

    if (temp != nullptr)
    {
        cout << "Found after " << c << " comparison(s)!!!" << endl;
        cout << "The Data is found and the value is: " << temp->value << endl;
    }
    else
    {
        cout << "The Data not found" << endl;
    }
}

void HashTable::print()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        cout << "[" << i << "] :";
        node *temp = hashTable[i];
        while (temp != nullptr)
        {
            cout << " (" << temp->key << "," << temp->value << ")";
            temp = temp->next;
        }
        cout << endl;
    }
}

void HashTable::deleteNode(string key)
{
    int index = hash(key);

    node *temp = hashTable[index];
    node *prev = nullptr;

    while (temp != nullptr && temp->key != key)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp != nullptr)
    {
        if (prev == nullptr)
        {
            hashTable[index] = temp->next;
        }
        else
        {
            prev->next = temp->next;
        }

        delete temp;
        cout << "Node with key '" << key << "' deleted successfully!!!" << endl;
    }
    else
    {
        cout << "Node with key '" << key << "' not found" << endl;
    }
}

int main()
{
    HashTable ht;
    int choice = 0;
    do
    {
        cout << "======== MENU ========" << endl;
        cout << "1. Insert Data" << endl;
        cout << "2. Find Data" << endl;
        cout << "3. Print Data" << endl;
        cout << "4. Delete Data" << endl;
        cout << "7. Exit" << endl;
        cout << "=====================" << endl;

        cout << "Enter Your choice : ";
        cin >> choice;

        string key;
        switch (choice)
        {
        case 1:
            ht.insert();
            break;
        case 2:
            cout << "Enter Key to find: ";
            cin >> key;
            ht.find(key);
            break;
        case 3:
            ht.print();
            break;
        case 4:
            cout << "Enter Key to Delete: ";
            cin >> key;
            ht.deleteNode(key);
            break;
        default:
            break;
        }
    } while (choice != 7);

    return 0;
}
