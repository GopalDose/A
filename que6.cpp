#include <iostream>
#include <stack>
using namespace std;

class node{
    int data;
    node *left;
    node *right;

    public:
    node(){
        left = right = NULL;
    }

    node(int val){
        data = val;
        left = right = NULL;
    }
    friend class BST;
};

class BST{
    node* root;

    public:
    BST(){
        root = NULL;
    }

    void insert();
    void descending_order();
    void minVal();
    void maxVal();
};

void BST::insert()
{
    int val;
    cout << "Insert Integer Data";
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

void BST::descending_order(){
    stack<node*> st;
    node* curr = root;

    while(curr || !st.empty()){
        while(curr){
            st.push(curr);
            curr = curr->right;
        }

        curr = st.top();
        st.pop();

        cout<<curr->data<<" ";
        curr = curr->left;
    }
}

void BST::minVal(){
    if(!root){
        cout<<"No Data"<<endl;
    }
    else{
        int val;
        node* curr = root;
        while(curr->left){
            curr = curr->left;
        }

        if(curr){
            val = curr->data;
            cout<<"The Minimum Value is: "<<val;
        }
    }
}

void BST::maxVal(){
    if(!root){
        cout<<"No Data"<<endl;
    }
    else{
        int val;
        node* curr = root;
        while(curr->right){
            curr = curr->right;
        }

        if(curr){
            val = curr->data;
            cout<<"The Maximum Value is: "<<val;
        }
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
        cout << "2.Descending Order" << endl;
        cout << "3.MinValue" << endl;
        cout << "4.MaxValue" << endl;
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
            cout << "Descending Order: ";
            tree.descending_order();
            break;
        case 3:
            tree.minVal();
            break;
        case 4:
            tree.maxVal();
            break;
        default:
            break;
        }
    } while (choice != 7);

    return 0;
}
