// Que: 1
// Beginning with an empty binary tree, construct binary tree by inserting the values in the
// order given. After constructing a binary tree perform following operations on it-
// • Perform preorder recursive traversal
// • Postorder, Inorder non-recursive traversal
// • Count number of leaves, number of internal nodes.

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
    void preorder_rec(node *n);
    void postorder_ite();
    void inorder_ite();
    int countLeafNode(node *n);
    void displayLeafNode(){
        cout<<"Leaf Nodes : "<< countLeafNode(root);
        cout<<endl;
    }
    int countInternalNode(node *n);
    void displayInternalNode(){
        cout<<"Internal Nodes : "<< countInternalNode(root);
        cout<<endl;
    }
    void preorder_rec_print()
    {
        preorder_rec(root);
        cout << endl;
    }
};

void BT::insert() {
    int data;
    char choice;

    cout << "Enter Data: ";
    cin >> data;
    node *n = new node(data);

    if (root == NULL) {
        root = n;
    } else {
        node *curr = root;
        node *parent = NULL;
        while (curr != NULL) {
            parent = curr;
            cout << "Enter l->leftChild & r->rightChild: ";
            cin >> choice;
            if (choice == 'r') {
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        }
        if (choice == 'r') {
            parent->right = n;
        } else {
            parent->left = n;
        }
    }
    cout << "Data Inserted Successfully" << endl;
}


void BT::preorder_rec(node *n)
{
    if (n != NULL)
    {
        cout << n->data << " ";
        preorder_rec(n->left);
        preorder_rec(n->right);
    }
}

void BT::inorder_ite()
{
    stack<node *> st;
    node *curr = root;

    while (curr != NULL || !st.empty())
    {
        while (curr != NULL)
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

void BT::postorder_ite()
{
    stack<node *> st1, st2;
    node *curr = root;
    if (!curr)
        return;
    st1.push(curr);
    while (!st1.empty())
    {
        curr = st1.top();
        st1.pop();
        st2.push(curr);
        if (curr->left)
            st1.push(curr->left);
        if (curr->right)
            st1.push(curr->right);
    }
    while (!st2.empty())
    {
        curr = st2.top();
        st2.pop();
        cout << curr->data << " ";
    }
}

int BT::countLeafNode(node *n)
{
    if (!n)
    {
        return 0;
    }
    if (n->left == NULL && n->right == NULL)
    {
        return 1;
    }
    else
    {
        return countLeafNode(n->left) + countLeafNode(n->right);
    }
}

int BT::countInternalNode(node* n){
    if(n->left == NULL && n->right == NULL){
        return 0;
    }
    else{
        return countInternalNode(n->left)+countInternalNode(n->right)+1;
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
        cout << "2.PreOrder" << endl;
        cout << "3.InOrder" << endl;
        cout << "4.PostOrder" << endl;
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
            cout << "Pre-Order Recursive: " << endl;
            tree.preorder_rec_print();
            break;

        case 3:
            cout << "In-Order Non Recursive: " << endl;
            tree.inorder_ite();
            cout << endl;
            break;

        case 4:
            cout << "Post-Order Non Recursive: " << endl;
            tree.postorder_ite();
            cout << endl;
            break;

        case 5:
            tree.displayLeafNode();
            break;

        case 6:
            tree.displayInternalNode();
            break;

        case 7:
            cout << "Thanks......." << endl;
            break;
        }
    } while (choice != 7);
}