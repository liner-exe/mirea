#ifndef BS_TREE
#define BS_TREE

#include <iostream>
#include <iomanip>

struct Node
{
    double data;
    Node* left;
    Node* right;

    Node(double val) : data(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree
{
public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree();

    void insert(double data);
    void printInOrder();
    void printSumLeaves();
    void printAverage();
    void fillTestData();

    void printTree(Node* node, int level);
    void visualize();
private:
    Node* root;

    Node* insert(Node* node, double value);
    void inOrderTraversal(Node* node);
    double sumLeaves(Node* node);
    void calculateSumAndCount(Node* node, double& sum, int& count);
    void clear(Node* node);
};

#endif // BS_TREE