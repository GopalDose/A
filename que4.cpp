#include <iostream>
#include <stack>
#include <queue>
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
    friend class BT;
};

class BT
{
    node *root;

public:
    BT()
    {
        root = NULL;
    }

    void insert();
    void inorder_itr();
    void postorder_rec(node *n);
    void displayPostOrder()
    {
        cout << "PostOrder Recursive: ";
        postorder_rec(root);
        cout << endl;
    }
    void BFS();
    int countDisplayLeaf(node *n);
    void countDisplayLeaffun()
    {
        cout << "The leaf Nodes are: ";
        int leafNode = countDisplayLeaf(root);
        cout << "The Total Leaf Nodes are: " << leafNode << endl;
    }
    int countDisplayInternal(node *n);
    void countDisplayInternalfun()
    {
        int internalNode = countDisplayInternal(root);
        cout << "The Total Internal Nodes are: " << internalNode << endl;
    }
};

void BT::insert()
{
    int data;
    char choice;

    cout << "Enter Data";
    cin >> data;
    node *newNode = new node(data);

    node *curr = root;
    if (!root)
    {
        root = newNode;
    }
    else
    {
        node *parent = NULL;
        while (curr)
        {
            parent = curr;
            cout << "Enter l -> leftChild & r -> rightChild";
            cin >> choice;
            if (choice == 'r')
            {
                curr = curr->right;
            }
            else
            {
                curr = curr->left;
            }
        }

        if (choice == 'r')
        {
            parent->right = newNode;
        }
        else
        {
            parent->left = newNode;
        }
    }
    cout<<"Data Inserted Successfully"<<endl;
}

void BT::inorder_itr()
{
    stack<node *> st;
    node *curr = root;

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

void BT::postorder_rec(node *n)
{
    if (n)
    {
        postorder_rec(n->left);
        postorder_rec(n->right);
        cout << n->data << " ";
    }
}

int BT::countDisplayLeaf(node *n)
{
    if (!n)
    {
        return 0;
    }
    else if (n->left == NULL && n->right == NULL)
    {
        cout << n->data << " ";
        return 1;
    }
    else
    {
        return countDisplayLeaf(n->left) + countDisplayLeaf(n->right);
    }
}

int BT::countDisplayInternal(node *n)
{
    if (n == NULL)
    {
        return 0;
    }
    if (n->left == NULL && n->right == NULL)
    {
        return 0;
    }
    else
    {
        cout<<n->data<<" ";
        return countDisplayInternal(n->left) + countDisplayInternal(n->right) + 1;
    }
}

void BT::BFS()
{
    if (root == nullptr)
        return;

    node *curr = root;
    queue<node *> qu;

    qu.push(root);
    while (!qu.empty())
    {
        curr = qu.front();
        qu.pop();
        cout << curr->data << " ";

        if (curr->left)
            qu.push(curr->left);
        if (curr->right)
            qu.push(curr->right);
    }
}

int main()
{
    BT tree;

    int choice = 0;
    do
    {
        cout << endl
             << "======= MENU =======" << endl;
        cout << "1.Insert" << endl;
        cout << "2.InOrder Iterative" << endl;
        cout << "3.PostOrder Recursive" << endl;
        cout << "4.BFS" << endl;
        cout << "5.Leaf Node Count" << endl;
        cout << "6.Internal Node Count" << endl;
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
            cout << "Inorder Iterative: " << endl;
            tree.inorder_itr();
            break;

        case 3:
            cout << "PostOrder Recursive: " << endl;
            tree.displayPostOrder();
            cout << endl;
            break;

        case 4:
            cout << "BFS: " << endl;
            tree.BFS();
            cout << endl;
            break;

        case 5:
            tree.countDisplayLeaffun();
            break;

        case 6:
            tree.countDisplayInternalfun();
            break;

        case 7:
            cout << "Thanks......." << endl;
            break;
        }
    } while (choice != 7);
}