#include <iostream>
using namespace std;

class node {
    string key, meaning;
    node *lc;
    node *rc;
    int height;

public:
    node(string k, string m) {
        key = k;
        meaning = m;
        lc = rc = NULL;
        height = 0;
    }

    friend class AVL;
};

class AVL {
public:
    node *root; 
    AVL() {
        root = NULL;
    }

    int node_height(node *p) {
        int hl = 0, hr = 0;
        hl = p && p->lc ? p->lc->height : 0;
        hr = p && p->rc ? p->rc->height : 0;

        return (hl > hr ? hl + 1 : hr + 1);
    }

    int BF(node *p) {
        int hl = 0, hr = 0;
        hl = p && p->lc ? p->lc->height : 0;
        hr = p && p->rc ? p->rc->height : 0;

        return (hl - hr);
    }

    node *LL(node *p) {
        node *pl = p->lc;
        p->lc = pl->rc;
        pl->rc = p;
        p->height = node_height(p);
        pl->height = node_height(pl);
        if (root == p) {
            root = pl;
        }
        return pl;
    }

    node *LR(node *p) {
        p->lc = RR(p->lc);
        return LL(p);
    }

    node *RR(node *p) {
        node *pr = p->rc;
        node *prl = pr->lc;

        pr->lc = p;
        p->rc = prl;

        p->height = node_height(p);
        pr->height = node_height(pr);

        if (root == p) {
            root = pr;
        }
        return pr;
    }

    node *RL(node *p) {
        p->rc = LL(p->rc);
        return RR(p);
    }

    node *insert(node *parent, string k, string m) {
        if (parent == NULL) {
            node *temp = new node(k, m);
            temp->height = 1;
            return temp;
        }

        if (k < parent->key) {
            parent->lc = insert(parent->lc, k, m);
        } else if (k > parent->key) {
            parent->rc = insert(parent->rc, k, m);
        } else {
            cout << "Key already exists: " << k << endl;
            return parent;
        }

        parent->height = node_height(parent);

        if (BF(parent) == 2 && BF(parent->lc) == 1) {
            return LL(parent);
        } else if (BF(parent) == 2 && BF(parent->lc) == -1) {
            return LR(parent);
        } else if (BF(parent) == -2 && BF(parent->rc) == -1) {
            return RR(parent);
        } else if (BF(parent) == -2 && BF(parent->rc) == 1) {
            return RL(parent);
        }
        return parent;
    }

    void inorder(node *t) {
        if (t != NULL) {
            inorder(t->lc);
            cout << t->key << " : " << t->meaning << " : " << BF(t) << endl;
            inorder(t->rc);
        }
    }
};

int main() {
    AVL a;
    int ch;
    string x, y;
    do {
        cout << "========== MENU ==========" << endl;
        cout << "1. INSERT" << endl;
        cout << "2. ASCENDING ORDER (INORDER)" << endl;
        cout << "3. EXIT" << endl;
        cout << "==========================" << endl;
        cout << "ENTER YOUR CHOICE" << endl;
        cin >> ch;
        switch (ch) {
        case 1: {
            string k, m;
            cout << "Enter The Key: ";
            cin >> k;
            cout << "Enter The meaning: ";
            cin >> m;
            a.root = a.insert(a.root, k, m);
            break;
        }
        case 2: {
            cout << "INORDER(ASCENDING ORDER)" << endl;
            a.inorder(a.root);
            break;
        }
        case 3: {
            return 0;
        }
        default:
            cout << "INVALID INPUT " << endl;
        }
    } while (true);

    return 0;
}
