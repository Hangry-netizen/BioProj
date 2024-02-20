#ifndef __INTERVALTREE_H
#define __INTERVALTREE_H

class value;

//******************************************************************************
class node {
    private:
        // records the node's key
        int key;

        // records the least key of subtree
        int leastKey;

        // records the greatest key of subtree
        int greatestKey;

        // records height of subtree
        int height;

        // records the number of nodes in subtree (number of keys in subtree)
        int subTreeNodeCount;

        // records left and right children pointers
        node *left, *right;

        // records the root of the value tree
        iAVL *valTree;

        // constructor for nodes
        node(bool primary, int key, int value);

        friend class iAVL;
};

//******************************************************************************
class iAVL {
    private:
        // points to the root of the tree
        node *root;

        // records the number of entries in the tree
        int treeCount;

        // returns the height of p; returns 0 if p is NULL
        int height(node *p) const;

        // returns the leastKey of p; returns 0 if p is NULL
        int leastKey(node *p) const;

        // returns the greatestKey of p; returns 0 if p is NULL
        int greatestKey(node *p) const;

        // returns the calculation of p's height based on its children's
        int calcHeight(node *p) const;

        // returns the leastKey value in p's subtree
        int calcLeastKey(node *p) const;

        // returns the greatestKey value in p's subtree
        int calcGreatestKey(node *p) const;

        // rotateLeft when p1 is a node that is right heavy imbalanced
        void rotateLeft(node *&p1);

        // rotateRight when p1 is a node that is left heavy imbalanced
        void rotateRight(node *&p1);

        // to balance given pointer
        void bal(node *&p);

        // recursion helpers
        bool insert(bool primary, node *&p, int key, int value);
        void printIt(node *p, int &index) const;
        void clear(node *p);

    public:
        // constructor that causes the tree object to be initialized
        iAVL(bool primary = false);

        // destructor that deletes all the nodes in the tree object
        ~iAVL();

        // returns true if key/value pair is inserted into the tree
        // returns false if the key/value pair is already in the tree
        bool insert(int key, int value);

        // removes all nodes from the tree, making the tree empty
        void clear();

        // prints the height of each node and its "index"
        void printIt() const;

        // returns the number of nodes in the tree
        int count() const;
};

#endif