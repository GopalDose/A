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
        lbit = rbit = 0;
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
        root = header = NULL;
    }

    node* getRoot(){
		return root;
	}
    void insert();
    void inorderTraversal();
    bool search(int key, node *&curr, node *& parent);
    void deleteNode(node *&parent, node *&curr);
};

void TBST::insert()
{
    int key;
    cout << "Enter Data : ";
    cin >> key;

    node *newNode = new node(key);

    if (root == NULL)
    {
        header = new node(-99);
        header->right = header;

        root = newNode;

        header->left = root;
        header->lbit = 1;
        root->left = header;
        root->right = header;
    }
    else
    {
        node *parent = root;
        while (true)
        {
            if (parent->data == newNode->data)
            {
                cout << "Node " << key << " already exists" << endl;
                delete newNode;
                newNode = NULL;
                return;
            }

            else if (parent->data > newNode->data)
            {
                if (parent->lbit == 1)
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
                if (parent->rbit == 1)
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

bool TBST::search(int key, node *&curr, node *&parent){
    while(curr!=header){
        if(curr->data == key){
            return true;
        }
        else{
            parent = curr;
            if(key < curr->data){
                if(curr->lbit){
                    curr = curr->left;
                }
                else{
                    return false;
                }
            }
            else{
                if(curr->rbit){
                    curr = curr->right;
                }
                else{
                    return false;
                }
            }
        }
    }
    return false;
}

void TBST::deleteNode(node *&parent, node *&curr){
    if(curr->lbit && curr->rbit){
        node *temp = curr->right;
        parent = curr;
        while(temp->lbit){
            parent = temp;
            temp = temp->left;
        }
        curr->data = temp->data;
        curr = temp;
    }

    if (curr->lbit == 0 && curr->rbit == 0){
		if (parent->left == curr){
			parent->left = curr->left;
			parent->lbit = 0;
		}
		else{
			parent->right = curr->right;
			parent->rbit = 0;
		}
		delete curr;
	}
    
    if(curr->lbit == 1 && curr->rbit == 0){
        node *temp = curr->left;

        if(parent->left == curr){
            parent->left = temp;
        }
        else{
            parent->right = temp;
        }

        while(temp->rbit == 1){
            temp = temp->right;
        }
        temp->right = curr->right;
        delete curr;
    }

    if (curr->lbit == 0 && curr->rbit == 1){
		node *temp = curr->right;
		if (parent->left == curr){
			parent->left = temp;
		}
		else{
			parent->right = temp;
		}
		while (temp->lbit == 1){
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
        cout << "2.InOrder Traversal" << endl;
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
            tree.inorderTraversal();
            break;
        case 3: 
		{
            int temp;
			cout << "Enter node to delete = ";
			cin >> temp;
			node *parent = NULL;
			node *current = tree.getRoot();
			if (tree.search(temp, current, parent)) {
				tree.deleteNode(parent, current);
				cout << temp << " deleted." << endl;
			}
			else{
				cout << temp << " not found." << endl;
			}
			break;
		}
        default:
            break;
        }
    } while (choice != 7);

    return 0;
}
