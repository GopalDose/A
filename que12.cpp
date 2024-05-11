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

    node* getRoot(){
        return root;
    }

    void insert();
    void preorder();
    void inorderTraversal();
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

void TBST::inorderTraversal()
{
    node *curr = root;

    while (curr->lbit == 1)
    {
        curr = curr->left;
    }

    while (curr != header)
    {
        curr->print();

        if (curr->rbit == 1)
        {
            curr = curr->right;
            while (curr->lbit == 1)
            {
                curr = curr->left;
            }
        }
        else
        {
            curr = curr->right;
        }
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
        cout << "3.InOrder Traversal" << endl;
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
            cout << "The PreOrder Traversal: "<<endl;
            tree.preorder();
            break;
        case 3:
            cout << "The InOrder Traversal: "<<endl;
            tree.inorderTraversal();
            break;
        case 7:
            cout << "Thanks......." << endl;
            break;
        default:
            break;
        }
    } while (choice != 7);

    return 0;
}
