
#include "catch2/catch_all.hpp"
#include "solution.h"

using namespace std;

void clean(Node*& n) {
    if (n == nullptr) return;
    clean(n->left);
    clean(n->right);
    delete n;
}

TEST_CASE("Validate isContains") {

    Node* test = new Node(100);
    test->left = new Node(50);
    test->right = new Node(140);
    test->left->left = new Node(25);

    CHECK(isContains(test, 140) == true);
    CHECK(isContains(test, 25) == true);
    CHECK(isContains(test, 0) == false);
    CHECK(isContains(test,  150) == false);
    clean(test);
}

TEST_CASE("Validate getMin") {

    Node* test = new Node(100);
    test->left = new Node(50);
    test->right = new Node(140);
    test->left->left = new Node(25);

    CHECK(getMin(test)->key == 25);
    test->left->left->left = new Node(5);
    CHECK(getMin(test)->key == 5);

    clean(test);
}

TEST_CASE("Validate getMax") {

    Node* test = new Node(100);
    test->left = new Node(50);
    test->right = new Node(140);
    test->left->left = new Node(25);
    CHECK(getMax(test)->key == 140);
    test->right->right = new Node(180);
    CHECK(getMax(test)->key == 180);

    clean(test);
}

TEST_CASE("Validate LCA") {

    Node* test = new Node(100);
    test = insert(test, 150);
    test = insert(test, 50);
    test = insert(test, 15);
    test = insert(test, 12);
    test = insert(test, 200);

    CHECK(LCA(test, 50, 200) == 100);
    CHECK(LCA(test, 15, 12) == 15);
    CHECK(LCA(test, 15, 120) == -1);

    clean(test);
}
TEST_CASE("Validate insert") {

    Node* test = new Node(100);
    test->left = new Node(50);
    test->right = new Node(140);
    test->left->left = new Node(25);
    test = insert(test, 150);


    CHECK(test->right->right->key == 150);
    test = insert(test, 75);
    CHECK(test->left->right->key == 75);

    clean(test);
}

TEST_CASE("Validate remove") {

    Node* test = new Node(100);
    test->left = new Node(50);
    test->right = new Node(140);
    test->left->left = new Node(25);
    test = remove(test, 25);

    CHECK(test->left->left == nullptr);
    test = remove(test, 100);

    CHECK(test->key == 140);
    CHECK(test->right == nullptr);


    clean(test);
}

//============================================

TEST_CASE("Validate level()") {

    Node* test = new Node(1);
    test = insert(test, 2);
    test = insert(test, -2);
    test->left->right = new Node(-1);
    test->left->left = new Node(-3);
    test->right->right = new Node(3);
    test->right->left = new Node(0);

    int toBeFound = 0;
    CHECK(level(test, toBeFound, 1) == 3);
    toBeFound = -2;
    CHECK(level(test, toBeFound, 1) == 2);
    toBeFound = 1;
    CHECK(level(test, toBeFound, 1) == 1);

    clean(test);
}

TEST_CASE("Validate areSiblings()") {

    Node* test = new Node(1);
    test = insert(test, 2);
    test = insert(test, -2);
    test->left->right = new Node(-1);
    test->left->left = new Node(-3);
    test->right->right = new Node(3);
    test->right->left = new Node(0);

    int a = 0;
    int b = 2;
    CHECK_FALSE(areSiblings(test, a, b));
    a = -2;
    CHECK(areSiblings(test, a, b));
    a = -1;
    b = 0;
    CHECK_FALSE(areSiblings(test, a, b));

    clean(test);

}

TEST_CASE("Validate areCousins()") {

    Node* test = new Node(1);
    test = insert(test, 2);
    test = insert(test, -2);
    test->left->right = new Node(-1);
    test->left->left = new Node(-3);
    test->right->right = new Node(3);
    test->right->left = new Node(0);

    int a = 0;
    int b = 2;
    CHECK_FALSE(areCousins(test, a, b));
    a = -2;
    CHECK_FALSE(areCousins(test, a, b));
    a = -1;
    b = 0;
    CHECK(areCousins(test, a, b));

    clean(test);

}


TEST_CASE("Validate section()") {

    Node* father = new Node(1);
    father = insert(father, 2);
    father = insert(father, -2);
    father->left->right = new Node(-1);
    father->left->left = new Node(-3);
    father->right->right = new Node(3);
    father->right->left = new Node(0);

    Node* mother = new Node(3);
    mother->left = new Node(0);
    mother->left->left = new Node(-1);
    mother->left->left->left = new Node(-3);
    mother = insert(mother, 30);

    Node* child = section(mother, father);

    CHECK(isContains(child, -3));
    CHECK(isContains(child, -1));
    CHECK(isContains(child, 0));
    CHECK(isContains(child, 3));
    CHECK_FALSE(isContains(child, 1));
    CHECK_FALSE(isContains(child, 2));
    CHECK_FALSE(isContains(child, -2));
    CHECK_FALSE(isContains(child, 30));

    clean(father);
    clean(mother);

}

