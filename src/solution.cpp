#include "solution.h"

bool isContains(Node* node, int key) 
{
    if (!node) { return false; }
    if (node->key < key) { return isContains(node->right, key); }
    if (node->key > key) { return isContains(node->left, key); }
    if (node->key == key) { return true; }
}

bool isContains(const Node* node, int key)
{
    if (!node) { return false; }
    if (node->key < key) { return isContains(node->right, key); }
    if (node->key > key) { return isContains(node->left, key); }
    if (node->key == key) { return true; }
}

Node* insert(Node* node, int value) 
{
    if (!node)  { return new Node(value); }

    if (value >= node->key) {  node->right = insert(node->right, value); }
    else if (value < node->key) {  node->left = insert(node->left, value);}

    return node;
}

Node* getMax(Node* node)
{
    if (!node) { return nullptr; }
    if (!node->right) { return node; }
    return getMax(node->right);
}

Node* getMin(Node* node) 
{
    if (!node) { return nullptr; }
    if (!node->left) { return node; }
    return getMin(node->left);
}

Node* remove(Node* node, int key) 
{
    if (!node) { return nullptr; }

}

Node* section(const Node* l, const Node* r) {
    return nullptr;
}

bool areCousins(const Node*, int key1, int key2) {
    return false;
}


bool lcaFinder(const Node* root, int& lca, int x, int y)
{
    if (!root) { return false; }
    if (root->key == x || root->key == y) { lca = root->key; return true; }

    bool areInTheLeftSubtree = lcaFinder(root->left, lca, x, y);
    bool areInTheRightSubtree = lcaFinder(root->right, lca, x, y);


    if (areInTheLeftSubtree && areInTheRightSubtree) { lca = root->key; }

    return areInTheLeftSubtree || areInTheRightSubtree;
}

int LCA(const Node* root, int key1, int key2) 
{
    int lca = -1;
    if (isContains(root, key1) && isContains(root, key2))
    {
        lcaFinder(root, lca, key1, key2);
    }

    return lca;
}
