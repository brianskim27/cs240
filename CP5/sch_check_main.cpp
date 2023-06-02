#include "sch_check.h"


int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "format: ./sch_check <prereqfile> <schedulefile>" << endl;
        return 1;
    }

    //call prcheck function here
    if(!pr_check(argv[1])){
        if(sch_check(argv[1], argv[2])) return 0; //all is good
    }

  return 1; //did not work
}