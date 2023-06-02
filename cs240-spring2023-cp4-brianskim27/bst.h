#ifndef BST_H
#define BST_H
#include<vector>
using namespace std;

class BST {
    private:
        struct Node;
        Node *root;
        int comparisons;

        Node *insertHelper(Node *node, int val);
        Node *findHelper(Node *node, int val);
        Node *findMin(Node *node);
        Node *removeHelper(Node *node, int val);
        float avgDepthHelper(Node *node);
        int heightHelper(Node *node);

    public:
        BST();
        void insert(int val);
        bool find(int val);
        void remove(int val);
        void insertVector(BST &bst, vector<int> vals);
        void removeVector(BST &bst, vector<int> vals);
        void shuffle(vector<int> &vector, int S);
        void shake(vector<int> &vector, int S, int R);
        float avgDepth();
        int height();
        void reset();
        void getCount();
};

#endif