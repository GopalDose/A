#include <iostream>
using namespace std;

class node
{
    int data;
    node *left;
    node *right;

    int lbit, rbit;

public:
    node()
    {
        left = right = NULL;
    }

    node(int val)
    {
        data = val;
        left = right = NULL;
        lbit = rbit = 0;
    }

    void print()
    {
        cout << "| " << lbit << " <= " << data << " => " << rbit << " |" << endl;
    }
    friend class TBST;
};

class TBST
{
    node *root;
    node *header;

public:
    TBST()
    {
        root = NULL;
    }

    node *getRoot()
    {
        return root;
    }

    void insert();
    void preorder();
    void deleteNode(node *&parent, node *&curr);
    bool searchNode(int key, node *&curr, node *&parent);
};

void TBST::insert()
{
    int key;
    cout << "Enter Data";
    cin >> key;

    node *newNode = new node(key);

    if (root == NULL)
    {
        header = new node(-99);

        header->right = header;
        root = newNode;

        header->left = root;
        header->lbit = 1;
        root->left = root->right = header;
    }
    else
    {
        node *parent = root;
        while (true)
        {
            if (parent->data > newNode->data)
            {
                if (parent->lbit)
                {
                    parent = parent->left;
                }
                else
                {
                    newNode->left = parent->left;
                    newNode->right = parent;
                    parent->left = newNode;
                    parent->lbit = 1;
                    return;
                }
            }
            else
            {
                if (parent->rbit)
                {
                    parent = parent->right;
                }
                else
                {
                    newNode->right = parent->right;
                    newNode->left = parent;
                    parent->right = newNode;
                    parent->rbit = 1;
                    return;
                }
            }
        }
    }
}

void TBST::preorder()
{
    bool flag = 0;
    node *curr = root;

    while (curr != header)
    {
        if (flag == 0)
        {
            curr->print();
        }
        if (flag == 0 && curr->lbit == 1)
        {
            curr = curr->left;
        }
        else
        {
            flag = (curr->rbit == 1) ? (0) : 1;
            curr = curr->right;
        }
    }
}

bool TBST::searchNode(int key, node *&curr, node *&parent)
{
    while (curr != header)
    {
        if (curr->data == key)
        {
            return true;
        }
        else
        {
            parent = curr;
            if (curr->data > key)
            {
                if (curr->lbit == 1)
                {
                    curr = curr->left;
                }
                else
                    return false;
            }
            else
            {
                if (curr->rbit == 1)
                    curr = curr->right;
                else
                    return false;
            }
        }
    }
    return false;
}

void TBST::deleteNode(node *&parent, node *&curr)
{
    if (curr->lbit && curr->rbit)
    {
        node *temp = curr->right;
        parent = curr;
        while (temp->lbit)
        {
            parent = temp;
            temp = temp->left;
        }
        curr->data = temp->data;
        curr = temp;
    }

    if (curr->lbit == 0 && curr->rbit == 0)
    {
        if (parent->left == curr)
        {
            parent->left = curr->left;
            parent->lbit = 0;
        }
        else
        {
            parent->right = curr->right;
            parent->right = 0;
        }
        delete curr;
    }

    if (curr->lbit == 1 && curr->rbit == 0)
    {
        node *temp = curr->left;
        if (parent->left == curr)
        {
            parent->left = temp;
        }
        else
        {
            parent->right = temp;
        }
        while (temp->rbit == 1)
        {
            temp = temp->right;
        }
        temp->right = curr->right;
        delete curr;
    }

    if (curr->lbit == 0 && curr->rbit == 1)
    {
        node *temp = curr->right;
        if (parent->left == curr)
        {
            parent->left = temp;
        }
        else
        {
            parent->right = temp;
        }
        while (temp->lbit)
        {
            temp = temp->left;
        }
        temp->left = curr->left;
        delete curr;
    }
}

int main()
{
    TBST tree;

    string key, meaning;

    int choice = 0;
    do
    {
        cout << endl
             << "======= MENU =======" << endl;
        cout << "1.Insert" << endl;
        cout << "2.PreOrder Traversal" << endl;
        cout << "3.Delete Node" << endl;
        cout << "7.Exit" << endl;
        cout << "====================" << endl;

        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            tree.insert();
            break;
        case 2:
            cout << "The PreOrder Traversal: " << endl;
            tree.preorder();
            break;
        case 3:
        {
            int temp;
            cout << "Enter node to delete = ";
            cin >> temp;
            node *parent = NULL;
            node *current = tree.getRoot();
            if (tree.searchNode(temp, current, parent))
            {
                tree.deleteNode(parent, current);
                cout << temp << " deleted." << endl;
            }
            else
            {
                cout << temp << " not found." << endl;
            }
            break;
        }
        case 7:
            cout << "Thanks......." << endl;
            break;
        default:
            break;
        }
    } while (choice != 7);

    return 0;
}
