#include <iostream>   // gets cin, cout, cerr
#include <fstream>    // gets file functions of open and close

#include "intervalTree.h"

//******************************************************************************

using namespace std;

//******************************************************************************
void doWork(keyAVL theTree, int key[5], int val[5]) {
    // for (int i = 0; i < 5; i++) {
    //     theTree.insert(key[i], val[i]);
    // }

    theTree.insert(2,1);
    theTree.insert(1,1);
    theTree.insert(4,1);
    theTree.insert(5,1);
    theTree.insert(3,1);



    // theTree.printIt();

}

//******************************************************************************
int main() {
    bool rc = false;
    keyAVL theTree;

    int key[] = {1, 2, 3, 4, 5};
    int val[] = {10, 9, 7, 6, 5};
    
    doWork(theTree, key, val);
    return 0;
}