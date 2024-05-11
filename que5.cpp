#include <iostream>
#include <stack>
using namespace std;

class node
{
    int data;
    node *left;
    node *right;

public:
    node()
    {
        left = right = NULL;
    }
    node(int val)
    {
        data = val;
        left = right = NULL;
    }

    friend class BST;
};

class BST
{
    node *root;

public:
    BST()
    {
        root = NULL;
    }

    void insert();
    void inorder_ite();
    void deleteNode(int key);
    node *minValueNode(node *nd);
    void search(int key);
};

void BST::insert()
{
    int val;
    cout << "Insert Integer Data: ";
    cin >> val;
    node *newNode = new node(val);

    if (root == NULL)
    {
        root = newNode;
    }
    else
    {
        node *curr = root;
        node *parent = NULL;

        while (curr != NULL)
        {
            parent = curr;
            if (curr->data < newNode->data)
            {
                curr = curr->right;
            }
            else
            {
                curr = curr->left;
            }
        }
        if (parent->data < newNode->data)
        {
            parent->right = newNode;
        }
        else
        {
            parent->left = newNode;
        }
    }
    cout << "Data Inserted Successfully" << endl;
}

void BST::inorder_ite()
{
    stack<node *> st;
    node *curr = root;

    if (!curr)
    {
        cout << "No Data" << endl;
    }
    else
    {
        while (curr || !st.empty())
        {
            while (curr)
            {
                st.push(curr);
                curr = curr->left;
            }

            curr = st.top();
            st.pop();

            cout << curr->data << " ";

            curr = curr->right;
        }
    }
}

void BST::deleteNode(int key)
{
    node *parent = NULL;
    node *curr = root;
    while (curr != NULL && curr->data != key)
    {
        parent = curr;
        if (key < curr->data)
            curr = curr->left;
        else
            curr = curr->right;
    }

    if (curr == NULL)
    {
        cout << "Node with key " << key << " not found in the tree." << endl;
        return;
    }

    // Case 1: Node to be deleted has no children (leaf node)
    if (curr->left == NULL && curr->right == NULL)
    {
        if (parent == NULL)
            root = NULL;
        else if (parent->left == curr)
            parent->left = NULL;
        else
            parent->right = NULL;
        delete curr;
    }
    else if (curr->left == NULL)
    {
        if (parent == NULL)
            root = curr->right;
        else if (parent->left == curr)
            parent->left = curr->right;
        else
            parent->right = curr->right;
        delete curr;
    }
    else if (curr->right == NULL)
    {
        if (parent == NULL)
            root = curr->left;
        else if (parent->left == curr)
            parent->left = curr->left;
        else
            parent->right = curr->left;
        delete curr;
    }
    else
    {
        node *successor = minValueNode(curr->right);
        int temp = successor->data;
        deleteNode(successor->data);
        curr->data = temp;
    }
}

node *BST::minValueNode(node *nd)
{
    node *current = nd;
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

void BST::search(int key)
{
    node *curr = root;
    int comparisions = 0;
    while (curr != NULL && curr->data != key)
    {
        if (key < curr->data)
            curr = curr->left;
        else
            curr = curr->right;
        comparisions++;
    }

    if (curr == NULL)
    {
        cout << "Node with key " << key << " not found in the tree." << endl;
        return;
    }
    else
    {
        cout << "Node with key " << key << " found in the tree." << endl;
        cout << "Comparisions required are: " << comparisions+1 << endl;
        return;
    }
}

int main()
{
    BST tree;

    int choice = 0;
    do
    {
        cout << endl
             << "======= MENU =======" << endl;
        cout << "1.Insert" << endl;
        cout << "2.InOrder Iterative" << endl;
        cout << "3.Delete" << endl;
        cout << "4.Search Key" << endl;
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
            cout << "Ascending Order: ";
            tree.inorder_ite();
            break;
        case 3:
            int key;
            cout << "Enter the key to be deleted: ";
            cin >> key;
            tree.deleteNode(key);
            break;
        case 4:
            int searchkey;
            cout << "Enter the key to be search: ";
            cin >> searchkey;
            tree.search(searchkey);
            break;
        default:
            break;
        }
    } while (choice != 7);

    return 0;
}
