#include <iostream>   // gets cin, cout, cerr
#include <fstream>    // gets file functions of open and close

#include "intervalTree.h"

//******************************************************************************

using namespace std;

//******************************************************************************
void doWork(iAVL theTree, int key[5], int val[5]) {
    // for (int i = 0; i < 5; i++) {
    //     theTree.insert(key[i], val[i]);
    // }

    theTree.insert(2,6);
    theTree.insert(1,7);
    theTree.insert(4,8);
    theTree.insert(5,9);
    theTree.insert(3,10);

   theTree.printIt();

}

//******************************************************************************
int main() {
    bool rc = false;
    iAVL theTree;

    int key[] = {1, 2, 3, 4, 5};
    int val[] = {10, 9, 7, 6, 5};
    
    doWork(theTree, key, val);
    return 0;
}