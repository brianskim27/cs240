#include <iostream>
#include <stdlib.h>
#include "Course.h"
#include "Roster.h"

using namespace std;

int main(int argc, char *argv[]) {
   Course one;
   Course *two = new Course("CS 240", "-B1", 100, "Dracula");
   one.show();
   two->show();
   delete(two);
}
