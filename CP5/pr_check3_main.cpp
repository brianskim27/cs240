#include "pr_check3.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "format: ./pr_check prereqs.txt" << endl;
        return 1;
    }

   return(pr_check(argv[1])); 
}