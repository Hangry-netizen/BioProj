#include <iostream>
#include <fstream>

#include "intervalTree.h"

//******************************************************************************

using namespace std;

//******************************************************************************
int min(int a, int b) {
    // function to determine the minimum of two given integers
    int min = a;

    if (b < min) {
        min = b;
    }

    return min;
}

//******************************************************************************
int max(int a, int b) {
    // function to determine the maximum of two given integers
    int max = a;

    if (b > max) {
        max = b;
    }

    return max;
}

//******************************************************************************
node::node(bool primary, int key, int value) {
    // constructor for tree nodes
    this->key = key;
    
    if (primary) {
        // if node is part of the primary tree, insert value into valTree
        valTree = new iAVL();
        valTree->insert(false, valTree->root, value, -1);

    } else {
        valTree = NULL;
    }

    left = right = NULL;
    height = 1;
}


//******************************************************************************
iAVL::iAVL() {
    // constructor that causes the object tree to be initialized
    root = NULL;
    treeCount = 0;
}

//******************************************************************************
iAVL::~iAVL() {
    // deconstructor that deletes all the nodes 
    // in preparation for the tree to be destroyed
    clear(root);
}

//******************************************************************************
int iAVL::height(node *p) const {
    // returns the height of p; returns 0 if p is NULL
    int rc = 0;
    
    if (p) {
        rc = p->height;
    }

    return rc;
}

//******************************************************************************
int iAVL::leastKey(node *p) const {
    // returns the leastKey of p
    int rc = 0;
    
    if (p) {
        rc = p->leastKey;
    }

    return rc;
}

//******************************************************************************
int iAVL::greatestKey(node *p) const {
    // returns the greatestKey of p
    int rc = 0;

    if (p) {
        rc = p->greatestKey;
    }
    return rc;
}

//******************************************************************************
int iAVL::calcHeight(node *p) const {
    // returns the max between p's left and right children's height, + 1 (for p)
    return max(height(p->left), height(p->right)) + 1;
}

// //******************************************************************************
// int iAVL::calcLeastKey(node *p) const {
//     // returns the leastKey value in p's subtree
//     int rc = p->key;

//     rc = p->left ? min(rc,p->left->key) : rc;
//     rc = p->right ? min(rc,p->right->key) : rc;

//     return rc;
// }

// //******************************************************************************
// int iAVL::calcGreatestKey(node *p) const {
//     // returns the greatestKey value in p's subtree
//     int rc = p->key;

//     rc = p->left ? max(rc,p->left->key) : rc;
//     rc = p->right ? max(rc,p->right->key) : rc;

//     return rc;
// }

//******************************************************************************
void iAVL::rotateLeft(node *&p1) {
    // rotation to balance right-heavy imbalance

    // rotate left around p1
    node *p2 = p1->right;
    p1->right = p2->left;
    p2->left = p1;

    // recalculate height, greatestKey and leastKey since positions have changed
    p1->height = calcHeight(p1);
    p2->height = calcHeight(p2);
    p1 = p2;
}

//******************************************************************************
void iAVL::rotateRight(node *&p1) {
    // rotation to balance left-heavy imbalance

    // rotate right around p1
    node *p2 = p1->left;
    p1->left = p2->right;
    p2->right = p1;

    // recalculate height since positions have been changed
    p1->height = calcHeight(p1);
    p2->height = calcHeight(p2);
    p1 = p2;
}

//******************************************************************************
void iAVL::bal(node *&p) {
    // balance given pointer

    if (p) {
        int diff = height(p->left) - height(p->right);

        if (diff == 2) {
            // left-heavy, therefore rotate right
            diff = height(p->left->left) - height(p->left->right);
            if (diff < 0) {
                // left-right-heavy, therefore rotate left then rotate right
                rotateLeft(p->left);
            }
            rotateRight(p);
        } else if (diff == -2) {
            // right-heavy, therefore rotate left
            if (height(p->right->left) > height(p->right->right)) {
                // right-left-heavy, therefore rotate right then rotate left
                rotateRight(p->right);
            }
            rotateLeft(p);
        }
        // recalculate p's height
        p->height = calcHeight(p);
    }

}

//******************************************************************************
// recursion helper
bool iAVL::insert(bool primary, node *&p, int key, int value) {
    // insert given key/value pair into key and value trees
    bool rc = false;

    if (p) {
        // if pointer exists
        if (key < p->key) {
            // if key is less than pointer's key, travel left
            rc = insert(primary, p->left, key, value);
        } else if (key > p->key) {
            // if key is more than pointer's key, travel right
            rc = insert(primary, p->right, key, value);
        } else {
            // if key is the same as pointer key, return p
            if (primary) {
                rc = p->valTree->insert(false, p->valTree->root, value, -1);
            }
        }
    } else {
        // otherwise, we are at a leaf, create new node and return it
        p = new node(primary, key, value);
        treeCount++;
        rc = true;
        
        bal(p);
        p->height = calcHeight(p);
    }
    // balance p
    bal(p);

    return rc;
}

//******************************************************************************
// recursion helper
void iAVL::printIt(bool primary, node *p, int &index) const {
    // print entries from left to right with their indexes and height
    if (p) {
        if (primary) {
            printIt(primary, p->left, index);      
            cout << "At " << index++ << " the key is " << p->key;
            cout << ": height = " << p->height << endl;
            int secondaryIndex = 0;
            root->valTree->printIt(false, p->valTree->root, secondaryIndex);
            printIt(primary, p->right, index);

        } else {
            printIt(primary, p->left, index);
            cout << "    myValTree    " << endl;
            cout << "    At " << index << " the key is " << p->key;
            cout << ": height = " << p->height << endl;
            printIt(primary, p->right , index);
        }
    }
}

//******************************************************************************
// recursion helper
void iAVL::clear(node *p) {
    // clear all nodes from right to left
    if (p) {
        clear(p->left);
        clear(p->right);
        delete p;
    }
}
//******************************************************************************
bool iAVL::insert(int key, int value) {
    // returns in true if key/value pair is inserted
    // otherwise, results in false
    bool rc = false;

    rc = insert(true, root, key, value);

    return rc;
}

//******************************************************************************
void iAVL::clear() {
    // removes all nodes from the tree, making the tree empty
    clear(root);
    root = NULL;
    treeCount = 0;
}

//******************************************************************************
void iAVL::printIt() const {
    // prints the tree's keys in ascending order with their index number
    int index = 0;
    bool primary = true;
    printIt(primary, root, index);
}

//******************************************************************************
int iAVL::count() const {
    // returns the number of nodes in the tree
    return treeCount;
}