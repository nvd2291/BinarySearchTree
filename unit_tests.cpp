/*
 * Title: unit_tests.cpp
 * Course: CS 15
 * Modified by: Naveed Naeem
 * UTLN: nnaeem01
 * Date: 7/13/2023
 *
 *  CS 15 - HW3: Binary Search Trees
 *  
 *  Purpose: Contains the Unit tests for the BinarySearchTree Class.
 *  
 */

#include <iostream>
#include <cassert>
#include <math.h>
#include <limits>
#include <random>
#include "BinarySearchTree.h"

using namespace std;

// Test the BST constructor for an empty tree
void test_BST_constructor_empty()
{
    BinarySearchTree bst;
    assert(bst.node_count() == 0);
    assert(bst.find_min() == numeric_limits<int>::max());
    assert(bst.find_max() == numeric_limits<int>::min());
    assert(bst.tree_height() == - 1);
}

// Test the BST copy constructor
void test_BST_copy_constructor()
{
    BinarySearchTree bst1;
    bst1.insert(3);
    bst1.insert(6);
    bst1.insert(9);

    assert(bst1.node_count() == 3);
    assert(bst1.find_min() == 3);
    assert(bst1.find_max() == 9);

    BinarySearchTree bst2(bst1);
    assert(bst2.node_count() == 3);
    assert(bst2.find_min() == 3);
    assert(bst2.find_max() == 9);
}

// Test the BST operator overload copy constructor
void test_BST_operator_overload_copy_constructor()
{
    BinarySearchTree bst1;
    bst1.insert(6);
    bst1.insert(3);
    bst1.insert(1);

    assert(bst1.node_count() == 3);
    assert(bst1.find_min() == 1);
    assert(bst1.find_max() == 6);

    BinarySearchTree bst2 = bst1;
    assert(bst2.node_count() == 3);
    assert(bst2.find_min() == 1);
    assert(bst2.find_max() == 6);
}

// Test the BST assignement operator
void test_BST_assignment_operator()
{
    BinarySearchTree bst1;
    BinarySearchTree bst2;
    BinarySearchTree bst3;

    bst1.insert(16);
    bst1.insert(8);
    bst1.insert(32);
    bst1.insert(64);

    bst2 = bst1;
    assert(bst2.find_max() == 64);
    assert(bst2.find_min() == 8);
    assert(bst2.contains(16));
    assert(bst2.contains(32));

    for (int i = 0; i < 100; i++)
    {
        if (i % 2 != 0)
        {
            bst3.insert(i);
        }
    }

    assert(bst3.node_count() == 50);
    assert(bst3.contains(1));
    assert(bst3.contains(49));
    assert(bst3.contains(99));

    bst1 = bst3;

    for (int i = 0; i < 100; i++)
    {
        if (i % 2 != 0)
        {
            assert(bst1.contains(i));
        }
    }

    assert(bst1.node_count() == 50);
    assert(bst1.contains(1));
    assert(bst1.contains(49));
    assert(bst1.contains(99));
}

// Test the BST insert method with a single value
void test_BST_insert()
{
    BinarySearchTree bst;

    assert(bst.node_count() == 0);
    
    bst.insert(1234645);
    assert(bst.node_count() == 1);
    assert(bst.contains(1234645));

}

// Insert bunch of unique elements into the bst and verify the node count and 
// count total are correct
void test_BST_insert_multiple()
{
    BinarySearchTree bst;

    bst.insert(4);
    bst.insert(2);
    bst.insert(5);
    bst.insert(8);
    bst.insert(10);
    bst.insert(7);
    bst.insert(0);
    bst.insert(-1);
    bst.insert(1);
    bst.insert(6);
    bst.insert(3);
    bst.insert(69);
    bst.insert(42);
    bst.insert(12);
    bst.insert(18);
    bst.insert(13);

    assert(bst.node_count() == 16);
    assert(bst.count_total() == 199);
}

// Insert the same values into a binary 100 times and confirm the number of
// nodes doesn't change and that the count_total() value makes sense
void test_BST_insert_duplicates()
{
    BinarySearchTree bst;

    for (int i = 0; i < 100; i++)
    {
        bst.insert(4);
        bst.insert(2);
        bst.insert(5);
        bst.insert(8);
        bst.insert(10);
        bst.insert(7);
        bst.insert(0);
        bst.insert(-1);
        bst.insert(1);
        bst.insert(6);
        bst.insert(3);
        bst.insert(69);
        bst.insert(42);
        bst.insert(12);
        bst.insert(18);
        bst.insert(13);
    }

    assert(bst.node_count() == 16);
    assert(bst.count_total() == (199 *100));
}

// Insert very large positive numbers and their negation and confirm the min
// value is correct.
void test_BST_find_min()
{
    BinarySearchTree bst_neg;

    // Test empty tree
    assert(bst_neg.find_min() == numeric_limits<int>::max()); 

    bst_neg.insert(50);

    // Insert mutiple positive and negative numbers
    for (int i = 0; i < 256; i++)
    {
        bst_neg.insert(-i);
        bst_neg.insert(i);
    }

    assert(bst_neg.find_min() == -255);

    // Insert a very large negative number to a populated tree
    bst_neg.insert((-1 * pow(2, 31)));

    assert(bst_neg.find_min() == (-1 * pow(2, 31)));

    BinarySearchTree bst_pos;
    
    //Insert a positive number
    bst_pos.insert(1024);

    for (size_t i = 0; i < 1000; i++)
    {
        bst_pos.insert(i*i);
    }

    // Confirm the min value is 0
    assert(bst_pos.find_min() == 0);   
}

// Insert a lot of negative numbers and confirm the max is 0
// Insert a lot of large numbers and confirm the max makes sense
void test_BST_find_max()
{
    BinarySearchTree bst_neg;

    // Test empty tree
    assert(bst_neg.find_max() == numeric_limits<int>::min()); 

    bst_neg.insert(-1);

    for (int i = 0; i < 100; i++)
    {
        bst_neg.insert(-i * 1000);
    }
    assert(bst_neg.find_max() == 0);

    BinarySearchTree bst_pos;
    bst_pos.insert(32767);
    for (int i = 0; i < 1000; i++)
    {
        bst_pos.insert(i*1000);
    }
    assert(bst_pos.find_max() == 999000);
}

//insert 50000 random numbers and confirm they exist in the BST
void test_BST_contains_random_mult()
{
    BinarySearchTree bst;
    
    assert(not bst.contains(256));

    std::random_device rd;
    std::mt19937 generator(rd());
    vector<int> randomVector;
    std::uniform_real_distribution<double> distribution(0, 4096);

    for (int i = 0; i < 50000; i++)
    {
        int randomNumber = (int)distribution(generator);
        randomVector.push_back(randomNumber);
        bst.insert(randomNumber);
    }

    for (int i = 0; i < 50000; i++)
    {
        assert(bst.contains(randomVector[i]));
    }

}

// Test BST contains method on an empty tree
void test_BST_contains_empty()
{
    BinarySearchTree bst_empty;

    assert(not bst_empty.contains(-256));
    assert(not bst_empty.contains(0));
    assert(not bst_empty.contains(1034));
}

// Test BST contains on a single node tree
void test_BST_contains_single()
{
    BinarySearchTree bst_single;

    bst_single.insert(0);
    assert(bst_single.contains(0));
    assert(bst_single.node_count() == 1);
    assert(not bst_single.contains(-1));
    assert(not bst_single.contains(1));
}

// Test BST remove() on an empty tree
void test_BST_remove_empty()
{
    BinarySearchTree bst_empty;

    assert(bst_empty.count_total() == 0);
    assert(bst_empty.node_count() == 0);
    assert(bst_empty.tree_height() == -1);

    std::random_device rd;
    std::mt19937 generator(rd());
    vector<int> randomVector;
    std::uniform_real_distribution<double> distribution(0, 4096);

    for (int i = 0; i < 50000; i++)
    {
        int randomNumber = (int)distribution(generator);
        assert(not bst_empty.remove(randomNumber));
    }
}

// Test BST remove() on a single node tree
void test_BST_remove_single()
{
    BinarySearchTree bst_single;

    bst_single.insert(300);

    assert(bst_single.count_total() == 300);
    assert(bst_single.node_count() == 1);
    assert(bst_single.remove(300));

    assert(bst_single.count_total() == 0);
    assert(bst_single.node_count() == 0);
    assert(not bst_single.contains(300));

}

// Test BST remove where the node to remove is the root and the root has child
// nodes
void test_BST_remove_root_with_children()
{
    BinarySearchTree bst;

    bst.insert(11);
    bst.insert(7);
    bst.remove(11);

    assert(not bst.contains(11));
    assert(bst.node_count() == 1);
    assert(bst.tree_height() == 0);
    assert(bst.count_total() == 7);
    bst.insert(8);

    bst.remove(7);
    assert(not bst.contains(7));
    assert(bst.node_count() == 1);
    assert(bst.tree_height() == 0);
    assert(bst.count_total() == 8);
}

// Test BST remove on a tree with multiple nodes
void test_BST_remove_multiple_nodes()
{
    BinarySearchTree bst;
    int nums[10] = {9, 8, 10, 5, 3, 1, 2, 6, 11, 7};

    for (int i = 0; i < 10; i++)
    {
        bst.insert(nums[i]);
    }

    for (int i = 0; i < 10; i++)
    {
        assert(bst.contains(nums[i]));
        assert(bst.remove(nums[i]));
        assert(not bst.contains(nums[i]));

        // Make sure no other nodes got removed unintentionally
        for (int j = (i + 1); j < 10; j++)
        {
            assert(bst.contains(nums[j]));
        }
    }
}

// Test BST node_count on an empty tree
void test_BST_node_count_empty()
{
    BinarySearchTree bst;

    assert(bst.node_count() == 0);
    assert(bst.count_total() == 0);
}

// Test BST node_count on tree with only a root node
void test_BST_node_count_root()
{
    BinarySearchTree bst;
    bst.insert(42);
    assert(bst.node_count() == 1);

}

// Test BST node_count on a tree with a root, left child, right child
void test_BST_node_count_root_w_children()
{
    BinarySearchTree bst;
    bst.insert(42);
    assert(bst.node_count() == 1);
    bst.insert(12);
    assert(bst.node_count() == 2);
    bst.insert(52);
    assert(bst.node_count() == 3);
}

// Test BST node_count on a tree with multiple nodes
void test_BST_node_count_multiple()
{
    BinarySearchTree bst;

    int nums[11] = {42, 36, 12, 17, 69, 49, 64, 25, 81, 96, 77};

    for (int i = 0; i < 11; i++)
    {
        bst.insert(nums[i]);
    }

    assert(bst.node_count() == 11);
}

// Test BST count_total on an empty tree
void test_BST_count_total_empty()
{
    BinarySearchTree bst;

    assert(bst.count_total() == 0);
}

// Test BST count_total the root, whose value has been inserted multiple times
void test_BST_count_total_root()
{
    BinarySearchTree bst;
    for (int i = 0; i < 10; i++)
    {
        bst.insert(42);
        assert(bst.count_total() == (42 * (i + 1)));
    }
}

// Test BST count_total on a tree with a root, left Child, and right child
// Repeat ten times and assert that the count total is correct everytime
// the node's are inserted.
void test_BST_count_total_root_w_children()
{
    BinarySearchTree bst;
    for (int i = 0; i < 10; i++)
    {
        bst.insert(10);
        bst.insert(1);
        bst.insert(14);

        assert(bst.count_total() == (25 * (i + 1)));
    }
}

// Test BST count_total on a BST that has 50000 random values inserted and
// confirm the count_total is the expected value
void test_BST_count_total_random()
{
    BinarySearchTree bst;
    std::random_device rd;
    std::mt19937 generator(rd());
    vector<int> randomVector;
    std::uniform_real_distribution<double> distribution(0, 4096);

    for (int i = 0; i < 50000; i++)
    {
        int randomNumber = (int)distribution(generator);
        randomVector.push_back(randomNumber);
        bst.insert(randomNumber);
    }

    int randomVectorSum = 0;
    for (int i = 0; i < 50000; i++)
    {
        randomVectorSum += randomVector[i];
    }

    assert(bst.count_total() == randomVectorSum);
}

// Test BST tree_height on an empty tree
void test_BST_tree_height_empty()
{
    BinarySearchTree bst;
    assert(bst.tree_height() == -1);
}

// Test BST tree_height on an empty tree
void test_BST_tree_height_root_only()
{
    BinarySearchTree bst;
    bst.insert(42);

    assert(bst.tree_height() == 0);
}

// Test BST tree_height on root with left and right children
void test_BST_tree_height_root_w_children()
{
    BinarySearchTree bst;
    bst.insert(42);
    bst.insert(-19);
    bst.insert(52);

    assert(bst.tree_height() == 1);
}

// Test BST tree_height by inserting multiple values to the left
void test_BST_tree_height_left_multiple()
{
    BinarySearchTree bst;

    for (int i = 0; i < 26; i++)
    {
        bst.insert(-1 * i);
    }

    assert(bst.tree_height() == 25);
}

// Test BST tree_height by inserting multiple values to the right
void test_BST_tree_height_right_multiple()
{
    BinarySearchTree bst;

    for (int i = 0; i < 26; i++)
    {
        bst.insert(i);
    }

    assert(bst.tree_height() == 25);
}

// Test BST tree_height by inserting random values
void test_BST_tree_height_multiple()
{
    BinarySearchTree bst;

    bst.insert(4);
    bst.insert(2);
    bst.insert(5);
    bst.insert(8);
    bst.insert(10);
    bst.insert(7);
    bst.insert(0);
    bst.insert(-1);
    bst.insert(1);
    bst.insert(6);
    bst.insert(3);
    bst.insert(69);
    bst.insert(42);
    bst.insert(12);
    bst.insert(18);
    bst.insert(13);

    assert(bst.tree_height() == 8);
}

int main()
{
    //Test constructors and assignment operator 
    test_BST_constructor_empty();
    test_BST_copy_constructor();
    test_BST_operator_overload_copy_constructor();
    test_BST_assignment_operator();

    //Test the BST public methods
    test_BST_insert();
    test_BST_insert_multiple();
    test_BST_insert_duplicates();

    test_BST_find_min();
    test_BST_find_max();

    test_BST_contains_empty();
    test_BST_contains_single();
    test_BST_contains_random_mult();

    test_BST_node_count_empty();
    test_BST_node_count_root_w_children();
    test_BST_node_count_multiple();

    test_BST_count_total_empty();
    test_BST_count_total_root();
    test_BST_count_total_root_w_children();
    test_BST_count_total_random();

    test_BST_remove_empty();
    test_BST_remove_single();
    test_BST_remove_root_with_children();
    test_BST_remove_multiple_nodes();

    test_BST_tree_height_empty();
    test_BST_tree_height_root_only();
    test_BST_tree_height_root_w_children();
    test_BST_tree_height_left_multiple();
    test_BST_tree_height_right_multiple();
    test_BST_tree_height_multiple();
    return 0;
}