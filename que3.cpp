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
    void displayInorder(){
        cout<<"InOrder Recursive: ";
        inorder_rec(root);
        cout<<endl;
    }
    void inorder_rec(node *n);
    void preorder_ite();
    void postorder_ite();
    void mirrorImage(node *n);
    void displayMirror(){
        mirrorImage(root);
        cout<<"Created Mirror Image of the Tree"<<endl;
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

void BT::inorder_rec(node *n){
    if(n){
        inorder_rec(n->left);
        cout<<n->data<<" ";
        inorder_rec(n->right);
    }
}

void BT::postorder_ite(){
    stack<node*> st1, st2;
    node *curr = root;

    if(!curr)
        return;
    st1.push(curr);
    while(!st1.empty()){
        curr = st1.top();
        st1.pop();
        st2.push(curr);
        if(curr->left)
            st1.push(curr->left);
        if(curr->right)
            st1.push(curr->right);
    }

    while(!st2.empty()){
        curr = st2.top();
        st2.pop();
        cout<<curr->data <<" ";
    }
}

void BT::preorder_ite(){
    stack<node*> st;
    node* curr = root;

    while(curr || !st.empty()){
        if(curr){
            cout<< curr->data <<" ";
            st.push(curr);
            curr = curr->left;
        }
        else{
            curr = st.top();
            st.pop();
            curr = curr->right;
        }
    }
}

void BT::mirrorImage(node* n){
    if(!n)
        return;
    mirrorImage(n->left);
    mirrorImage(n->right);
    node* temp = n->left;
    n->left = n->right;
    n->right = temp;
}

int main()
{
    int choice = 0;
    BT tree;
    do{
        cout<<"======== MENU ========"<<endl;
        cout<<"1. Insert Node"<<endl;
        cout<<"2. Inorder Recursive"<<endl;
        cout<<"3. PostOrder Iterative"<<endl;
        cout<<"4. PreOrder Iterative"<<endl;
        cout<<"5. Mirror Image"<<endl;
        cout<<"6. Exit"<<endl;
        cout<<"======================"<<endl;
        cout<<"Enter Your Choice: ";
        cin>>choice;

        switch (choice)
        {
        case 1:
            tree.insert();
            break;

        case 2:
            tree.displayInorder();
            break;
        
        case 3:
            cout<<"Post Order Iterative: ";
            tree.postorder_ite();
            cout<<endl;
            break;

        case 4:
            cout<<"Pre Order Iterative: ";
            tree.preorder_ite();
            cout<<endl;
            break;

        case 5:
            tree.displayMirror();
            break;

        case 6:
            cout<<"Thanks You........"<<endl;
            break;
        }

    }while(choice != 6);
}