/*
 * Title: BinarySearchTree.cpp
 * Course: CS 15
 * Modified by: Naveed Naeem
 * UTLN: nnaeem01
 * Date: 7/13/2023
 *
 * Implementation of the Binary Search Tree class.
 * Behaves like a standard BST except that it handles multiplicity
 * If you insert a number twice  and then remove it once, then it will
 * still be in the data structure. For full function contracts see the header 
 * file BinarySearchTree.h
 */

#include <cstring>
#include <iostream>
#include <limits>

#include "BinarySearchTree.h"

using namespace std;

BinarySearchTree::BinarySearchTree()
{
    //Initialize and empty binary search tree
    root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
    // walk tree in post-order traversal and delete
    post_order_delete(root);
    root = nullptr; // not really necessary, since the tree is going
                    // away, but might want to guard against someone
                    // using a pointer after deleting
}

void BinarySearchTree::post_order_delete(Node *node)
{
    if (node == nullptr)
    {
        return;
    }

    post_order_delete(node->left);
    post_order_delete(node->right);
    delete node;
    node = nullptr;
}

// copy constructor
BinarySearchTree::BinarySearchTree(const BinarySearchTree &source) {
    // use pre-order traversal to copy the tree
    root = pre_order_copy(source.root);
}

// assignment overload
BinarySearchTree &BinarySearchTree::operator=(const BinarySearchTree &source) 
{
    // check for self-assignment
    if (this->root == source.root)
    {
        return *this;
    }

    // delete current tree if it exists
    if (this->root != nullptr)
    {
        post_order_delete(this->root);
    }

    // use pre-order traversal to copy the tree
    root = pre_order_copy(source.root);

    // return *this
    return *this;
}

BinarySearchTree::Node *BinarySearchTree::pre_order_copy(Node *node) const
{
    if (node == nullptr)
    {
        return nullptr;
    }

    Node *copyNode = new Node(node);
    copyNode->left = pre_order_copy(node->left);
    copyNode->right = pre_order_copy(node->right);
    return copyNode;
}

int BinarySearchTree::find_min() const
{
    if (root == nullptr) 
    {
        return numeric_limits<int>::max(); // INT_MAX
    }
    return find_min(root)->data;
}

BinarySearchTree::Node *BinarySearchTree::find_min(Node *node) const 
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (node->left != nullptr)
    {
        return find_min(node->left);
    }
    else
    {
        return node;
    }
}

int BinarySearchTree::find_max() const
{
    if (root == nullptr)
    {
        return numeric_limits<int>::min(); // INT_MAX
    }

    return find_max(root)->data;
}

BinarySearchTree::Node *BinarySearchTree::find_max(Node *node) const
{
    if (node == nullptr)
    {
        return nullptr;;
    }

    if (node->right != nullptr)
    {
        return find_max(node->right);
    }
    else
    {
        return node;
    }
}

bool BinarySearchTree::contains(int value) const 
{
    return contains(root, value);
}

bool BinarySearchTree::contains(Node *node, int value) const 
{
    if (node == nullptr)
    {
        return false;
    }

    if (node->data == value)
    {
        return true;
    }

    // If the value is greater than the current node call contains private
    // helper on the right side of the tree
    if (value > node->data)
    {
        return contains(node->right, value);
    }

    // If the value is less than the current node call contains private
    // helper on the left side of the tree
    if ( value < node->data)
    {
        return contains(node->left, value);
    }

    // Should never get here, but keep the compiler happy
    return false;
}

void BinarySearchTree::insert(int value) {
    insert(root, nullptr, value);
}

void BinarySearchTree::insert(Node *node, Node *parent, int value)
{
    // if the node is nullptr, create a new node
    if (node == nullptr)
    {
        insertNewNode(parent, value);
        return;
    }

    if (value < node->data)
    {
        insert(node->left, node, value);
    }
    else if (value > node->data)
    {
        insert(node->right, node, value);
    }
    else
    {
        node->count++;
    }

    return;
}

bool BinarySearchTree::remove(int value) 
{
    return remove(root, nullptr, value);
}

bool BinarySearchTree::remove(Node *node, Node *parent, int value)
{
    if (node == nullptr) return false;

    if (value < node->data)
    {
        return remove(node->left, node, value);
    }
    else if (value > node->data)
    {
        return remove(node->right, node, value);
    }
    else
    {
        node->count--;
        if (node->count > 0) return true;

        if (isLeaf(node))
        {
            removeLeafNode(node, parent);
            return true;
        }
        else if (node->left == nullptr)
        {
            return reassignParentNode(node, parent, node->right);
        }
        else if (node->right == nullptr)
        {
            return reassignParentNode(node, parent, node->left);
        }
        else
        {
            Node *minRightNode = find_min(node->right);
            node->count = minRightNode->count;
            node->data = minRightNode->data;
            return remove(node->right, node, minRightNode->data);
        }
    }
}

int BinarySearchTree::tree_height() const {
    return tree_height(root);
}

int BinarySearchTree::tree_height(Node *node) const 
{
    if (node == nullptr)
    {
        return -1;
    }

    int leftHeight = tree_height(node->left);
    int rightHeight = tree_height(node->right);

    return (max(leftHeight,rightHeight) + 1);
}

// returns the total number of nodes
int BinarySearchTree::node_count() const
{
    return node_count(root);
}

int BinarySearchTree::node_count(Node *node) const
{
    if (node == nullptr)
    {
        return 0;
    }

    int left = node_count(node->left);
    int right = node_count(node->right);

    return (1 + left + right);
}

// return the sum of all the node values (including duplicates)
int BinarySearchTree::count_total() const {
    return count_total(root);
}

// Use recursion to find and return the total value of the tree
// Total value of the tree is determine by adding up the 
// (node.count * node.data) for each node 
int BinarySearchTree::count_total(Node *node) const 
{
    if (node == nullptr) return 0;

    int leftCount = 0;
    int rightCount = 0;

    if (node->left != nullptr)
    {
        leftCount = count_total(node->left);
    }

    if (node->right != nullptr)
    {
        rightCount = count_total(node->right);
    }

    return ((node->count * node->data) + leftCount + rightCount);
}

BinarySearchTree::Node *BinarySearchTree::find_parent(Node *node,
                                                      Node *child) const {
    if (node == nullptr) return nullptr;

    // if either the left or right is equal to the child,
    // we have found the parent
    if (node->left == child or node->right == child) { return node; }

    // Use the binary search tree invariant to walk the tree
    if (child->data > node->data) {
        return find_parent(node->right, child);
    } else {
        return find_parent(node->left, child);
    }
}

// use the printPretty helper to make the tree look nice
void BinarySearchTree::print_tree() const {
    size_t      numLayers  = tree_height() + 1;
    size_t      levelWidth = 4;
    const char *rootPrefix = "-> ";

    // Need numLayers * levelWidth characters for each layer of tree.
    // Add an extra levelWidth characters at front to avoid if statement
    // 1 extra char for nul character at end
    char *start = new char[(numLayers + 1) * levelWidth + 1];

    print_tree(root, start + levelWidth, start + levelWidth, rootPrefix);
    delete[] start;
}

// Logic and Output Reference:
// https://www.techiedelight.com/c-program-print-binary-tree/
void BinarySearchTree::print_tree(Node *node, char *const currPos,
                                  const char *const fullLine,
                                  const char *const branch) const {
    if (node == nullptr) return;

    // 4 characters + 1 for nul terminator
    using TreeLevel                    = char[5];
    static const int       levelLength = sizeof(TreeLevel) - 1;
    static const TreeLevel UP = ".-- ", DOWN = "`-- ", EMPTY = "    ",
                           CONNECT = "   |";
    // Copies prev into dest and advances dest by strlen(prev)
    auto set = [](char *dest, const char *prev) {
        size_t p = strlen(prev);
        return (char *)memcpy(dest, prev, p) + p;
    };

    print_tree(node->right, set(currPos, EMPTY), fullLine, UP);

    // Clear any characters that would immediate precede the "branch"
    // Don't need to check for root (i.e start of array),fullLine is padded
    set(currPos - levelLength, EMPTY);

    // Terminate fullLine at current level
    *currPos = '\0';

    std::cerr << fullLine << branch << node->data
              << (node->count > 1 ? "*" : "") << endl;

    // Connect upper branch to parent
    if (branch == UP) set(currPos - levelLength, CONNECT);

    // Connect lower branch to parent
    print_tree(node->left, set(currPos, CONNECT), fullLine, DOWN);
}
