#include <iostream>
#include <fstream>

#include "intervalTree.h"

using namespace std;

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
node::node(int key, int value, int matchLen) {
    // constructor for key tree nodes
    this->key = key;
    left = right = NULL;
    height = 1;
}

//******************************************************************************
node::node(int key) {
    // constructor for value tree nodes
    this->key = key;
    left = right = NULL;
    height = 1;
}

//******************************************************************************
value::value(int value, int matchLen) {
    // constructor that causes the object value to be initialized
    valueNode = new node(value);
    this->matchLen = matchLen;
}

//******************************************************************************
keyAVL::keyAVL() {
    //constructor that causes the object tree to be initialized
    root = NULL;
    treeCount = 0;
}

//******************************************************************************
keyAVL::~keyAVL() {
    //deconstructor that deletes all the nodes
    //in preparation for the tree to be destroyed
    clear(root);
}

//******************************************************************************
int keyAVL::findMin(node *p) const {
    //returns the minimum value in the subtree
    int rc = p->key;

    if (p->left) {
        rc = findMin(p->left);
    }

    return rc;
}

//******************************************************************************
int keyAVL::findMax(node *p) const {
    //returns the minimum value in the subtree
    int rc = p->key;

    //returns the minimum value in the subtree
    //whose node is pointed to by pointer
    if (p->right) {
        rc = findMin(p->right);
    }

    return rc;
}

//******************************************************************************
bool keyAVL::insert(node *&p, int key, int value, int matchLen) {
    // *** insert() is currently an unmodified version of the usual AVL insertion
    bool rc = false;

    if (p) {
        // if pointer exists
        if (key < p->key) {
            // if key is less than pointer's key, travel left
            rc = insert(p->left, key);
        } 
        else if (key > p->key) {
            // if key is more than pointer's key, travel right
            rc = insert(p->right, key);
        }
    } else {
        // otherwise, we are at a leaf and we will insert the new node here
        p = new node(key);
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
void keyAVL::printIt(node *p, int &index) const {
    // print entries from left to right with their indexes and height
    if (p) {
        printIt(p->left, index);
        cout << "At " << index++ << " the key is " << p->key;
        cout << ": height = " << p->height << endl;
        printIt(p->right, index);
    }
}

//******************************************************************************
void keyAVL::clear(node *p) {
    // clear all nodes from right to left
    if (p) {
        clear(p->left);
        clear(p->right);
        delete p;
    }
}

//******************************************************************************
void keyAVL::rotateLeft(node *&p1) {
    // rotation to balance right-heavy imbalance

    // rotate left around p1
    node *p2 = p1->right;
    p1->right = p2->left;
    p2->left = p1;

    // recalculate height since positions have been changed
    p1->h = calcHeight(p1);
    p2->h = calcHeight(p2);
    p1 = p2;
}

//******************************************************************************
void keyAVL::rotateRight(node *&p1) {
    // rotation to balance left-heavy imbalance

    // rotate right around p1
    node *p2 = p1->left;
    p1->left = p2->right;
    p2->right = p1;

    // recalculate height since positions have been changed
    p1->h = calcHeight(p1);
    p2->h = calcHeight(p2);
    p1 = p2;
}

//******************************************************************************
void keyAVL::bal(node *&p1) {
    // balance given pointer

    if (p1) {
        int diff = height(p1->left) - height(p1->right);

        if (diff == 2) {
            // left-heavy, therefore rotate right
            diff = height(p1->left->left) - height(p1->left->right);
            if (diff < 0) {
                // left-right-heavy, therefore rotate left then rotate right
                rotateLeft(p1->left);
            }
            rotateRight(p1);
        } else if (diff == -2) {
            // right-heavy, therefore rotate left
            if (height(p1->right->left) > height(p1->right->right)) {
                // right-left-heavy, therefore rotate right then rotate left
                rotateRight(p1->right);
            }
            rotateLeft(p1);
        }
        // recalculate p's height
        p1->h = calcHeight(p1);
    }

}

//******************************************************************************
int keyAVL::height(node *p) const {
    // returns the height of p; return 0 if p is NULL
    int rc = 0;

    if (p) {
        rc = p->height;
    }

    return rc;
}

//******************************************************************************
int keyAVL::calcHeight(node *p) const {
    // adds 1 to the max between its left and right children's height
    return max(height(p->left), height(p->right)) + 1;
}

//******************************************************************************
bool keyAVL::insert(int key, int value, int matchLen) {
    // returns in true if key/value pair is inserted
    // otherwise, results in false
    return insert(root, key, value, matchLen);
}

//******************************************************************************
void keyAVL::printIt() const {
    // prints the tree's keys in ascending order with their index number
    int index = 0;
    printIt(root, index);
}

//******************************************************************************
int keyAVL::count() const {
    // returns the number of nodes in the tree
    return treeCount;
}

//******************************************************************************
void keyAVL::clear() {
    // removes all nodes from the tree, making the tree empty
    clear(root);
    root = NULL;
    treeCount = 0;
}