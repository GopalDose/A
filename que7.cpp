#include <iostream>
#include <stack>
using namespace std;

class node
{
    string key;
    string meaning;
    node *left;
    node *right;

public:
    node()
    {
        left = right = NULL;
    }

    node(string keyword, string mean)
    {
        key = keyword;
        meaning = mean;
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
    void update(string key, string meaning);
    node *minVal(node *n);
    void deleteNode(string key);
    void displayAscending();
    void displayDescending();
};

void BST::insert()
{
    string key, meaning;

    cout << "Enter the Keyword: ";
    cin >> key;
    cout << "Enter the Meaning: ";
    cin >> meaning;

    node *newNode = new node(key, meaning);

    if (!root)
    {
        root = newNode;
    }
    else
    {
        node *curr = root;
        node *parent = NULL;

        while (curr)
        {
            parent = curr;
            if (curr->key < newNode->key)
                curr = curr->right;
            else
                curr = curr->left;
        }

        if (parent->key < newNode->key)
            parent->right = newNode;
        else
            parent->left = newNode;
    }

    cout << "Data Inserted Successfully" << endl;
}

void BST::update(string key, string meaning)
{
    node *curr = root;

    while (curr && curr->key != key)
    {
        if (curr->key < key)
        {
            curr = curr->right;
        }
        else
        {
            curr = curr->left;
        }
    }

    if (curr)
    {
        curr->meaning = meaning;
        cout << "The data is Updated" << endl;
    }
    else
    {
        cout << "The Key Not Found" << endl;
    }
}

node *BST::minVal(node *n)
{
    node *curr = n;
    while (curr && curr->left != NULL)
        curr = curr->left;

    return curr;
}

void BST::deleteNode(string key)
{
    node *parent = NULL;
    node *curr = root;

    while (curr && curr->key != key)
    {
        parent = curr;
        if (curr->key < key)
            curr = curr->right;
        else
            curr = curr->left;
    }

    if (!curr)
    {
        cout << "Node with key " << key << " not found in the tree." << endl;
        return;
    }

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
        node *successor = minVal(curr->right);
        string temp = successor->key;
        deleteNode(successor->key);
        curr->key = temp;
    }
}

void BST::displayAscending()
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

        cout << curr->key << " : " << curr->meaning << endl;
        curr = curr->right;
    }
}

void BST::displayDescending()
{
    stack<node *> st;
    node *curr = root;

    while (curr || !st.empty())
    {
        while (curr)
        {
            st.push(curr);
            curr = curr->right;
        }

        curr = st.top();
        st.pop();

        cout << curr->key << " : " << curr->meaning << endl;
        curr = curr->left;
    }
}

int main()
{
    BST tree;

    string key, meaning;

    int choice = 0;
    do
    {
        cout << endl
             << "======= MENU =======" << endl;
        cout << "1.Insert" << endl;
        cout << "2.Update" << endl;
        cout << "3.Delete Node" << endl;
        cout << "4.Display Ascending" << endl;
        cout << "5.Display Descending" << endl;
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
            cout << "Enter The Key to Update: ";
            cin >> key;
            cout << "Enter The updated meaning: ";
            cin >> meaning;
            tree.update(key, meaning);
            break;
        case 3:
            cout << "Enter the Key to delete: ";
            cin >> key;
            tree.deleteNode(key);
            break;
        case 4:
            cout << "Ascending Order: ";
            tree.displayAscending();
            break;
        case 5:
            cout << "Descending Order: ";
            tree.displayDescending();
            break;
        default:
            break;
        }
    } while (choice != 7);

    return 0;
}
