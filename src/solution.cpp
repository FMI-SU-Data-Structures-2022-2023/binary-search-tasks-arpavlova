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

    if (node->key < key) { node->right = remove(node->right, key); }
    else if (node->key > key) { node->left = remove(node->left, key); }
    else
    {
        if (!node->left && !node->right) { return nullptr; }
        else if (node->left && !node->right) { return node->left; }
        else if (node->right && !node->left) { return node->right; }

        else
        {
            Node* minInRightSubtree = getMin(node->right);
            node->key = minInRightSubtree->key;

            node->right = remove(node->right, minInRightSubtree->key);
        }
    }

    return node;
}

void sectionCreator(const Node* l, const Node* r, Node* &result)
{
    if (!l || !r) { return; }
    if (l->key == r->key) { result = insert(result, r->key); }
    sectionCreator(l->left, r, result);
    sectionCreator(l->right, r, result);
    sectionCreator(l, r->right, result);
    sectionCreator(l, r->left, result);

}

Node* section(const Node* l, const Node* r) 
{
    Node* section = nullptr;
    sectionCreator(l, r, section);

    return section;
}

int level(const Node* root, int a, int lev)
{
    if (!root) { return -1; }
    if (root->key == a) { return lev; }

    int isInLeft = level(root->left, a, lev + 1);
    int isInRight = level(root->right, a, lev + 1);

    return isInLeft != -1 ? isInLeft : isInRight;

}

bool areSiblings(const Node* root, int a, int b)
{
    if (!root->left && !root->right) { return false; }
    if((root->left->key == a && root->right->key == b) 
        || (root->left->key == b && root->right->key == a))
    {return true;}
  
    return areSiblings(root->right, a, b) || areSiblings(root->left, a, b);
}

bool areCousins(const Node* root, int key1, int key2)
{
    return (level(root, key1, 1) == level(root, key2, 1) && !areSiblings(root, key1, key2));
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
