#include <iostream>
#include "zany.h"
#include "Thing.h"
#include "ZLL.h"
using namespace std;

template <typename T>
void reportZany(const T &param) {
	cout << param << " is ";
	if(!isZany(param)) {
		cout << "not ";
	}
	cout << "zany" << endl;
}

int main() {
	int three = 3;
	int four = 4;
	reportZany(three);
	reportZany(four);
	
	string three_str = "three";
	string four_str = "Four";
	reportZany(three_str);
	reportZany(four_str);

	Thing one_thing("Eggplant", "purple");
	Thing two_thing("Strawberry", "red");
	reportZany(one_thing);
	reportZany(two_thing);

	ZLL<int> zll1;
	ZLL<string> zll2;
	ZLL<Thing> zll3;

	zll1.back(3);
	zll2.back("Four");
	zll3.back(one_thing);
}
