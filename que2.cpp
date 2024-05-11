// Que: 2
// Beginning with an empty binary tree, construct binary tree by inserting the values in the
// order given. After constructing a binary tree perform following operations on it-
// • Perform  post order recursive traversal
// • Inorder, Preorder non-recursive traversal
// • Find the height of tree

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
    void postorder_rec(node *n);
    void preorder_ite();
    void inorder_ite();
    int height(node *n);
    void displayHeight(){
        cout<<"Height: "<< height(root)<<endl;
    }
    void postorder_rec_print()
    {
        postorder_rec(root);
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


void BT::postorder_rec(node *n)
{
    if (n != NULL)
    {
        postorder_rec(n->left);
        postorder_rec(n->right);
        cout << n->data << " ";
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

void BT::preorder_ite()
{
    node *curr = root;
    stack<node*> st;
    while (curr || !st.empty())
    {
        if (curr)
        {
            cout << curr->data << " ";
            st.push(curr);
            curr = curr->left;
        }
        else
        {
            curr = st.top();
            st.pop();
            curr = curr->right;
        }
    }
}

int BT::height(node *n){
    if(!n){
        return 0;
    }

    int l = 0;
    int r = 0;

    l = height(n->left);
    r = height(n->right);
    if(l>r){
        return l+1;
    }
    else{
        return r+1;
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
        cout << "2.PostOrder" << endl;
        cout << "3.InOrder" << endl;
        cout << "4.PreOrder" << endl;
        cout << "5.Height of Tree" << endl;
        cout << "6.Exit" << endl;
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
            tree.postorder_rec_print();
            break;

        case 3:
            cout << "In-Order Non Recursive: " << endl;
            tree.inorder_ite();
            cout << endl;
            break;

        case 4:
            cout << "Post-Order Non Recursive: " << endl;
            tree.preorder_ite();
            cout << endl;
            break;

        case 5:
            tree.displayHeight();
            break;

        case 6:
            cout << "Thanks......." << endl;
            break;
        }
    } while (choice != 6);
}