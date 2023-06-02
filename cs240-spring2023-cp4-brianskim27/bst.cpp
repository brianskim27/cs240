#include "bst.h"
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <queue>
using namespace std;

struct BST::Node {
    int val;
    Node *left;
    Node *right;
    Node(int v) {
        val = v;
        left = NULL;
        right = NULL;
    }
};

BST::BST() {
    root = NULL;
    comparisons = 0;
}

BST::Node *BST::insertHelper(Node *node, int val) {
    if(node == NULL) {
        return new Node(val);
    }

    if(val < node->val) {
        comparisons++;
        node->left = insertHelper(node->left, val);
    }
    else if(val > node->val) {
        comparisons++;
        node->right = insertHelper(node->right, val);
    }
    
    return node;
}

BST::Node *BST::findHelper(Node *node, int val) {
    if(node == NULL) {
        return NULL;
    }

    if(val == node->val) {
        comparisons++;
        return node;
    }
    else if(val < node->val) {
        comparisons++;
        return findHelper(node->left, val);
    }
    else {
        comparisons++;
        return findHelper(node->right, val);
    }
}

BST::Node *BST::findMin(Node *node) {
    while(node->left != NULL) {
        node = node->left;
    }

    return node;
}

BST::Node *BST::removeHelper(Node *node, int val) {
    if(node == NULL) {
        return NULL;
    }

    if(val < node->val) {
        comparisons++;
        node->left = removeHelper(node->left, val);
    }
    else if(val > node->val) {
        comparisons++;
        node->right = removeHelper(node->right, val);
    }
    else {
        if(node->left == NULL && node->right == NULL) {
            delete node;
            node = NULL;
        }
        else if(node->left == NULL) {
            Node *temp = node;
            node = node->right;
            delete temp;
        }
        else if(node->right == NULL) {
            Node *temp = node;
            node = node->left;
            delete temp;
        }
        else {
            Node *temp = findMin(node->right);
            node->val = temp->val;
            node->right = removeHelper(node->right, temp->val);
        }
    }

    return node;
}

float BST::avgDepthHelper(Node* node) {
    if (node == NULL) {
        return 0.0;
    }

    int sum = 0;
    int count = 0;
    queue<pair<Node*, int>> q;
    q.push(make_pair(node, 0));
    
    while (!q.empty()) {
        pair<Node*, int> current = q.front();
        q.pop();
        Node* node = current.first;
        int depth = current.second;
        sum += depth;
        count++;

        if (node->left) {
            q.push(make_pair(node->left, depth + 1));
        }
        if (node->right) {
            q.push(make_pair(node->right, depth + 1));
        }
    }

    return (float)sum / count;
}

int BST::heightHelper(Node *node) {
    if(node == NULL) {
        return -1;
    }
    else {
        int left_height = heightHelper(node->left);
        int right_height = heightHelper(node->right);
        int height = max(left_height, right_height) + 1;
        return height;
    }
}

void BST::insert(int val) {
    root = insertHelper(root, val);
}

bool BST::find(int val) {
    Node *node = findHelper(root, val);

    if(node == NULL) {
	cout << "Find " << val << ": Not found" << endl;
        return false;
    }
    cout << "Find " << val << ": Found" << endl;
    return true;
}

void BST::remove(int val) {
    root = removeHelper(root, val); 
}

void BST::insertVector(BST &bst, vector<int> vals) {
    for(int val:vals) {
        bst.insert(val);
    }
}

void BST::removeVector(BST &bst, vector<int> vals) {
    for(int val:vals) {
        bst.remove(val);
    }
}

void BST::shuffle(vector<int> &vector, int S) {
    srand(time(NULL));

    int N = vector.size();
    for(int i = 0; i < S; i++) {
        int swap_one = rand() % N;
        int swap_two = rand() % N;
        swap(vector[swap_one], vector[swap_two]);
    }
}

void BST::shake(vector<int> &vector, int S, int R) {
    srand(time(NULL));

    int N = vector.size();
    for(int i = 0; i < S; i++) {
        int element = rand() % N;
        int distance = (rand() % R) + 1;
        int direction;
        if(distance > 0) {
            direction = 1;
        }
        else if(distance < 0) {
            direction = -1;
        }

        for(int j = 0; j < abs(distance); j++) {
            int k = element + (direction * j);
            if(k < 0 || k >= N || k == element) {
                break;
            }
            else {
                swap(vector[k], vector[k - direction]);
            }
        }
    }
}

float BST::avgDepth() {
    return avgDepthHelper(root);
}

int BST::height() {
    return heightHelper(root);
}

void BST::reset() {
    comparisons = 0;
    cout << "Comparison count has been reset" << endl;
}

void BST::getCount() {
    cout << "Number of comparisons since last call to reset(): " << comparisons << endl;
}
