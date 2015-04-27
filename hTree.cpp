#include "hTree.h"
#include <string>
#include <iostream>
using namespace std;

hTree::hTree()
{
    //ctor
}

hTree::~hTree()
{
    //dtor
}

void hTree::insertNode(hTreeN *node, hTreeN *child) {
    if (node == NULL || node->title == "") {
        node = child;
    } else if (node->title.compare(child->title) < 0) {
        if (node->rightChild == NULL) {
            node->rightChild = child;
            child->parent = node;
        } else {
            insertNode(node->rightChild, child);
        }
    } else if (node->title.compare(child->title) > 0) {
        if (node->leftChild == NULL) {
            node->leftChild = child;
            child->parent = node;
        } else {
            insertNode(node->leftChild, child);
        }
    }
}

void hTree::printTree(hTreeN *node) {
    if (node != NULL) {
        printTree(node->leftChild);

        cout << node->title << " ";

        printTree(node->rightChild);
    }
}
