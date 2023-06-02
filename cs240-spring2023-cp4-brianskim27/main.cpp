#include <iostream>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include <queue>
#include "bst.h"
using namespace std;

int main() {
    BST bst1, bst2, bst3;
    vector<int> values = {};

//Experiment One: 10 values
    cout << "***Experiment One: 10 values***" << endl;

    for(int i = 1; i < 11; i++) {
	    values.push_back(i);
    }

    /*
    cout << "Order of vector values: ";
    for(int val:values) {
	    cout << val << " ";
    }
    cout << endl;
    */

    bst1.shuffle(values, 10);
    bst1.shake(values, 3, 3);

    /*
    cout << "New order of vector values: ";
    for(int val:values) {
	    cout << val << " ";
    }
    cout << endl;
    */

    bst1.insertVector(bst1, values);

    bst1.reset();
    bst1.find(5);
    bst1.getCount();

    bst1.reset();
    bst1.find(53);
    bst1.getCount();

    bst1.reset();
    bst1.find(7);
    bst1.getCount();

    cout << "height: " << bst1.height() << endl;
    cout << "average depth: " << bst1.avgDepth() << endl;

    bst1.remove(7);
    cout << "Remove 7" << endl;
    bst1.find(7);

    cout << "height: " << bst1.height() << endl;
    cout << "average depth: " << bst1.avgDepth() << endl;

    bst1.insert(15);
    cout << "Inserted 15" << endl;
    bst1.insert(20);
    cout << "Inserted 20" << endl;
    bst1.insert(11);
    cout << "Inserted 11" << endl;

    cout << "height: " << bst1.height() << endl;
    cout << "average depth: " << bst1.avgDepth() << endl;
    cout << endl;
    
    //Compare with a different tree of same values
    cout << "Shuffle and shake" << endl;
    bst1.removeVector(bst1, values);
    
    cout << "Order of vector values: ";
    for(int val:values) {
	    cout << val << " ";
    }
    cout << endl;

    bst1.shuffle(values, 6);
    bst1.shake(values, 4, 4);

    /*
    cout << "New order of vector values: ";
    for(int val:values) {
	    cout << val << " ";
    }
    */

    cout << endl;
    bst1.insertVector(bst1, values);

    bst1.reset();
    bst1.find(5);
    bst1.getCount();

    bst1.reset();
    bst1.find(53);
    bst1.getCount();

    bst1.reset();
    bst1.find(7);
    bst1.getCount();

    cout << "height: " << bst1.height() << endl;
    cout << "average depth: " << bst1.avgDepth() << endl;

    bst1.remove(7);
    cout << "Removed 7" << endl;
    bst1.find(7);

    cout << "height: " << bst1.height() << endl;
    cout << "average depth: " << bst1.avgDepth() << endl;

    bst1.insert(15);
    cout << "Inserted 15" << endl;
    bst1.insert(20);
    cout << "Inserted 20" << endl;
    bst1.insert(11);
    cout << "Inserted 11" << endl;

    cout << "height: " << bst1.height() << endl;
    cout << "average depth: " << bst1.avgDepth() << endl;

    cout << endl;


//Experiment Two
    cout << "***Experiment Two: 100 values***" << endl;

    values.clear();
    for(int i = 1; i < 101; i++) {
	    values.push_back(i);
    }

    /*
    cout << "Order of vector values: ";
    for(int val:values) {
	    cout << val << " ";
    }
    cout << endl;
    */

    bst2.shuffle(values, 100);
    bst2.shake(values, 50, 50);
    
    /*
    cout << "New order of vector values: ";
    for(int val:values) {
	    cout << val << " ";
    }
    cout << endl;
    */

    bst2.insertVector(bst2, values);

    bst2.reset();
    bst2.find(2);
    bst2.getCount();

    bst2.reset();
    bst2.find(50);
    bst2.getCount();

    bst2.reset();
    bst2.find(96);
    bst2.getCount();

    cout << "height: " << bst2.height() << endl;
    cout << "average depth: " << bst2.avgDepth() << endl;

    bst2.remove(63);
    cout << "Removed 63" << endl;
    bst2.find(63);

    cout << "height: " << bst2.height() << endl;
    cout << "average depth: " << bst2.avgDepth() << endl;

    bst2.insert(150);
    cout << "Inserted 150" << endl;
    bst2.insert(125);
    cout << "Inserted 125" << endl;
    bst2.insert(136);
    cout << "Inserted 136" << endl;

    cout << "height: " << bst2.height() << endl;
    cout << "average depth: " << bst2.avgDepth() << endl;
    cout << endl;
    
    //Compare with a different tree of same values
    cout << "Shuffle and shake" << endl;
    bst2.removeVector(bst2, values);
    
    /*
    cout << "Order of vector values: ";
    for(int val:values) {
	    cout << val << " ";
    }
    cout << endl;
    */

    bst2.shuffle(values, 80);
    bst2.shake(values, 75, 60);

    /*
    cout << "New order of vector values: ";
    for(int val:values) {
	    cout << val << " ";
    }
    */

    cout << endl;
    bst2.insertVector(bst2, values);

    bst2.reset();
    bst2.find(2);
    bst2.getCount();

    bst2.reset();
    bst2.find(50);
    bst2.getCount();

    bst2.reset();
    bst2.find(96);
    bst2.getCount();

    cout << "height: " << bst2.height() << endl;
    cout << "average depth: " << bst2.avgDepth() << endl;

    bst2.remove(63);
    cout << "Removed 63" << endl;
    bst2.find(63);

    cout << "height: " << bst2.height() << endl;
    cout << "average depth: " << bst2.avgDepth() << endl;

    bst2.insert(150);
    cout << "Inserted 150" << endl;
    bst2.insert(125);
    cout << "Inserted 125" << endl;
    bst2.insert(136);
    cout << "Inserted 136" << endl;

    cout << "height: " << bst2.height() << endl;
    cout << "average depth: " << bst2.avgDepth() << endl;

    cout << endl;

    
//Experiment Three
    cout << "***Experiment Three: 1000 values***" << endl;
    for(int i = 1; i < 1001; i++) {
	    values.push_back(i);
    }
    
    /*
    cout << "Order of vector values: ";
    for(int val:values) {
	    cout << val << " ";
    }
    cout << endl;
    */

    bst2.shuffle(values, 1000);
    bst2.shake(values, 500, 500);

    /*
    cout << "New order of vector values: ";
    for(int val:values) {
	    cout << val << " ";
    }
    cout << endl;
    */

    bst3.insertVector(bst3, values);

    bst3.reset();
    bst3.find(13);
    bst3.getCount();

    bst3.reset();
    bst3.find(647);
    bst3.getCount();

    bst3.reset();
    bst3.find(961);
    bst3.getCount();

    cout << "height: " << bst3.height() << endl;
    cout << "average depth: " << bst3.avgDepth() << endl;

    bst3.remove(422);
    cout << "Removed 422" << endl;
    bst3.find(422);

    cout << "height: " << bst3.height() << endl;
    cout << "average depth: " << bst3.avgDepth() << endl;

    bst3.insert(1111);
    cout << "Inserted 1111" << endl;
    bst3.insert(1010);
    cout << "Inserted 1010" << endl;
    bst3.insert(2222);
    cout << "Inserted 2222" << endl;

    cout << "height: " << bst3.height() << endl;
    cout << "average depth: " << bst3.avgDepth() << endl;
    cout << endl;
    
    //Compare with a different tree of same values
    cout << "Shuffle and shake" << endl;
    bst3.removeVector(bst3, values);
    
    /*
    cout << "Order of vector values: ";
    for(int val:values) {
	    cout << val << " ";
    }
    cout << endl;
    */

    bst3.shuffle(values, 800);
    bst3.shake(values, 750, 600);

    /*
    cout << "New order of vector values: ";
    for(int val:values) {
	    cout << val << " ";
    }
    cout << endl;
    */

    bst3.insertVector(bst3, values);

    bst3.reset();
    bst3.find(13);
    bst3.getCount();

    bst3.reset();
    bst3.find(647);
    bst3.getCount();

    bst3.reset();
    bst3.find(961);
    bst3.getCount();

    cout << "height: " << bst3.height() << endl;
    cout << "average depth: " << bst3.avgDepth() << endl;

    bst3.remove(422);
    cout << "Removed 422" << endl;
    bst3.find(422);

    cout << "height: " << bst3.height() << endl;
    cout << "average depth: " << bst3.avgDepth() << endl;

    bst3.insert(1111);
    cout << "Inserted 1111" << endl;
    bst3.insert(1010);
    cout << "Inserted 1010" << endl;
    bst3.insert(2222);
    cout << "Inserted 2222" << endl;

    cout << "height: " << bst3.height() << endl;
    cout << "average depth: " << bst3.avgDepth() << endl;

    cout << endl;
     
    return 0;
}
