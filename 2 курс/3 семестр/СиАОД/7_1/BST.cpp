#include "BST.h"

// Private


Node* BinarySearchTree::insert(Node* node, double value)
{
    if (node == nullptr) return new Node(value);

    if (value < node->data)
    {
        node->left = insert(node->left, value);
    }
    else if (value > node->data)
    {
        node->right = insert(node->right, value);
    }

    return node;
}

void BinarySearchTree::inOrderTraversal(Node* node)
{
    if (node == nullptr) return;

    inOrderTraversal(node->left);
    std::cout << node->data << " ";
    inOrderTraversal(node->right);
}

double BinarySearchTree::sumLeaves(Node* node)
{
    if (node == nullptr) return 0.0;

    if (node->left == nullptr && node->right == nullptr)
    {
        return node->data;
    }

    return sumLeaves(node->left) + sumLeaves(node->right);
}

void BinarySearchTree::calculateSumAndCount(Node* node, double& sum, int& count)
{
    if (node == nullptr) return;

    sum += node->data;
    count++;

    calculateSumAndCount(node->left, sum, count);
    calculateSumAndCount(node->right, sum, count);
}

void BinarySearchTree::clear(Node *node)
{
    if (node == nullptr) return;

    clear(node->left);
    clear(node->right);

    delete node;
}

// Public

BinarySearchTree::~BinarySearchTree()
{
    clear(root);
}

void BinarySearchTree::insert(double data)
{
    root = insert(root, data);
}

void BinarySearchTree::printInOrder()
{
    std::cout << "Симметричный обход: ";
    inOrderTraversal(root);
    std::cout << std::endl;
}

void BinarySearchTree::printSumLeaves()
{
    double sum = sumLeaves(root);
    std::cout << "Сумма значений листьев: " << sum << std::endl;
}

void BinarySearchTree::printAverage()
{
    if (root == nullptr)
    {
        std::cout << "Дерево пустое." << std::endl;
    }

    double totalSum = 0.0;
    int totalCount = 0.0;

    calculateSumAndCount(root, totalSum, totalCount);

    if (totalCount > 0)
    {
        double average = totalSum / totalCount;
        std::cout << "Сумма всех узлов: " << totalSum << std::endl;
        std::cout << "Количество узлов: " << totalCount << std::endl;
        std::cout << "Среднее арифметическое: " << average << std::endl;
    }
}

void BinarySearchTree::fillTestData()
{
    double testValues[] = { 10.5, 5.2, 15.8, 2.1, 7.4, 12.3, 18.9, 6.0,
        8.5, 11.1
    };

    for (double value : testValues)
    {
        insert(value);
    }

    std::cout << "Тестовые данные (10 элем.) добавлены." << std::endl;
}

void BinarySearchTree::printTree(Node* node, int level)
{
    if (node == nullptr) return;

    printTree(node->right, level + 1);

    std::string indent(level * 4, ' ');

    std::cout << indent << std::setprecision(4) << node->data << std::endl;

    printTree(node->left, level + 1);
}

void BinarySearchTree::visualize()
{
    printTree(root, 0);
}
