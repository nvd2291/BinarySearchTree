/*
 * BinarySearchTree.h
 * Course: CS 15
 * Modified by: Naveed Naeem
 * UTLN: nnaeem01
 * Date: 7/13/2023
 *
 * Interface of the Binary Search Tree class.
 * Behaves like a standard BST except that it handles multiplicity
 * If you insert twice a number and then remove it once, then it will
 * still be in the data structure
 */

#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_


class BinarySearchTree {
public:
        // constructor
        BinarySearchTree();

        // destructor
        ~BinarySearchTree();

        // copy constructor
        BinarySearchTree(const BinarySearchTree &source);

        // assignment overload copy constructort
        BinarySearchTree &operator=(const BinarySearchTree &source);

        // find_min() returns the minimum value in the tree
        // returns INT_MAX if the tree is empty
        int find_min() const;

        // find_max() returns the maximum value in the tree
        // returns INT_MIN if tree is empty
        int find_max() const;

        // contains() returns true if the value is in the tree,
        // false if it is not in the tree
        bool contains(int value) const;

        // insert() inserts the value into the Binary Search Tree.
        // If the value is already in the tree, the node's count
        // is incremented by 1
        void insert(int value);

        // remove() does a full removal from the tree (NOT lazy removal)
        // If a node's count is greater than one, the count is
        // decremented, and the node is not removed.
        // Nodes with a count of 0 must be fully removed using the
        // following algorithm (discussed in class): if the node has no
        // children, simply remove it.  If the node has one child,
        // "bypass" the node to the child from the parent.  If the node
        // has two children, first find the minimum node of the
        // right child, replace the node's data with the value and
        // count of right's minimum, and then recursively delete
        // right's minimum.
        bool remove(int value);

        // returns the maximum distance from the root to it's farthest
        // leaf.  Note:  An empty tree has a height of -1, a tree with
        // just a root has a height of 0, and a tree with a root and
        // one or two children has a height of 1, etc.
        int tree_height() const;

        // returns the total number of nodes (NOT including duplicates)
        // i.e., if a tree contains 3, 4, 4, the number of nodes would
        // only be two, because the fours are contained in one node.
        int node_count() const;

        // return the sum of all the node values (including duplicates)
        // For the previous example, the count_total() would be
        // 3 + 4 + 4 = 11
        int count_total() const;

        // print the tree (written for you)
        void print_tree() const;

private:
        // Binary Search Tree Node:
        // - data is the value
        // - count is the number of times the data has been inserted
        //   into the tree (minus removals)
        //
        struct Node 
        {
            int   data;
            int   count;
            Node *left;
            Node *right;

            //Create an empty Node
            Node()
            {
                this->count = 0;
                this->data = 0;
                this->left = nullptr;
                this->right = nullptr;
            }

            // Copy
            Node(const Node *inputNode)
            {
                this->data = inputNode->data;
                this->count = inputNode->count;
                this->left = nullptr;
                this->right = nullptr;
            }

            // New node and assign value
            Node(const int value)
            {
                this->count = 0;
                this->data = value;
                this->left = nullptr;
                this->right = nullptr;
            }
        };
        // the root of the tree (starts as NULL)
        Node *root;

        // the following nine functions are private helper functions
        // for the public functions. We do not want to expose the
        // internals of the tree publicly, so we pass the root (and
        // other information in some cases) to the functions below
        // from the public functions.

        Node *find_min(Node *node) const;
        Node *find_max(Node *node) const;
        bool  contains(Node *node, int value) const;
        void  insert(Node *node, Node *parent, int value);

        // Students will implement one of the following remove functions
        bool  remove(Node *node, Node *parent, int value);
        // bool  remove(Node *node, Node **ptr_to_ptr_to_me, int value);

        int   tree_height(Node *node) const;
        int   node_count(Node *node) const;
        int   count_total(Node *node) const;
        Node *pre_order_copy(Node *node) const;

        // used by the destructor to delete nodes recursively
        void post_order_delete(Node *node);
        
        // find_parent (written for you) is necessary for removing
        // the right_min of a node when removing a node that has
        // two children
        Node *find_parent(Node *node, Node *child) const;

        // Pretty print
        void print_tree(Node *node, char *const currPos,
                        const char *const fullLine,
                        const char *const branch) const;

        // Takes in a pointer to a node and returns true if it is a leaf node,
        // otherwise it returns false
        bool isLeaf(Node *node)
        {
            if (node->left == nullptr and node->right == nullptr)
            {
                return true;
            }
            return false;
        }

        // Takes in the a node, the node's parent node, and the successor node
        // and reassign's the parent's left or right child node's depending on
        // which child node == nullptr. This should only be used on parent
        // node's where at least one child == nullptr. If parent is nullptr
        // then we know that the node is the root node.
        bool reassignParentNode(Node* node, Node* parent, Node* successorNode)
        {
            if (node == nullptr or successorNode == nullptr) return false;

            if (parent != nullptr)
            {
                if (parent->left == node)
                {
                    parent->left = successorNode;
                }
                else
                {
                    parent->right = successorNode;
                }
            }
            else
            {
                root = successorNode;
            }

            delete node;
            return true;
        }

        // Take in the parent node and the value to insert. Allocate a new Node
        // on the heap with the value provided as an input. Then determine if
        // the new node should be assigned as the root node. If not, check the
        // value of the parent node and determine whether the new node should
        // be assigned as the left or right child node or to call the private
        // insert function to recursive further down the tree.
        void insertNewNode(Node* parent, int value)
        {
            Node *newNode = new Node(value);
            newNode->count = 1;

            if (parent == nullptr)
            {
                root = newNode;
            }
            else if (value < parent->data)
            {
                if (parent->left == nullptr)
                {
                    parent->left = newNode;
                }
                else
                {
                    insert(newNode, parent->left, value);
                }
            }
            else 
            {
                if (parent->right == nullptr)
                {
                    parent->right = newNode;
                }
                else
                {
                    insert(newNode, parent->right, value);
                }
            }
        }

        // handles removing a node if it's a leaf node
        void removeLeafNode(Node* node, Node *parent)
        {
            if (not isLeaf(node)) return;

            if (parent != nullptr)
            {
                if (parent->left == node)
                {
                    parent->left = nullptr;
                }
                else
                {
                    parent->right = nullptr;
                }
            }
            else 
            {
                root = nullptr;
            }
            delete node;
        }
};

#endif /* BINARYSEARCHTREE_H_ */
