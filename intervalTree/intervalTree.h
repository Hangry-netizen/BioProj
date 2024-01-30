#ifndef __INTERVALTREE_H
#define __INTERVALTREE_H

class node {
    private:
        // records the node's key
        int key;

        // records the number of values that share the same key
        int keyCount;

        // records the greatest key of subtree
        int greatestKey;

        // records the least key of subtree
        int leastKey;

        // records height of subtree
        int height;

        // records the number of nodes in subtree (number of keys in subtree)
        int subTreeNodeCount;

        // records left and right children pointers
        node *left, *right;

        // records the root of the value tree
        value *valueRoot

        // constructor for key tree nodes
        node(int key, int value, int matchLen);

        // constructor for value tree nodes
        node(int key);

        friend class value;
        friend class keyAVL;
}

class value {
    private:
        // records the value node
        node *valueNode;

        // records the length of match
        int matchLen;

        // constructor that causes value object to be initialized
        value(int value=NULL, int matchLen=NULL);        
};

class keyAVL {
    private:
        // to point to the root of the tree
        node *root;

        // records the number of entries in the tree
        int treeCount;

        // returns the minimum value in the subtree
        int findMin(node *p) const;

        // returns the maximum value in the subtree
        int findMax(node *p) const;

        // rotateLeft when p1 is a node that is right heavy imbalanced
        void rotateLeft(node *&p1);

        // rotateRight when p1 is a node that is left heavy imbalanced
        void rotateRight(node *&p1);

        // to balance given pointer
        void bal(node *&p1);

        // returns the height of p if it is real
        // otherwise 0 if it is NULL
        int height(node *p) const;

        // return the calculation of p's height
        // based on the height of its children
        // this is not a recursive call
        int calcHeight(node *p) const;

        // recursion helpers
        bool insert(node *&p, int key, int value, int matchLen);
        void printIt(node *p, int &index) const;
        void clear(node *p);

    public:
        // constructor that causes object to be initialized
        keyAVL();

        // destructor that deletes all the nodes in the BST
        // in preparation for the BST to be destroyed
        ~keyAVL();

        // inserts the key/value pair into the tree
        // returns true for success
        // returns false if the key/value pair is already in the tree
        bool insert(int key, int value, int matchLen);

        // print the height of each node and its "index"
        void printIt() const;

        // returns the number of nodes in the tree
        int count() const;

        // removes all nodes from the tree, making the tree empty
        void clear();
};

#endif