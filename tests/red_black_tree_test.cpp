#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "../data-structures/red_black_tree/red_black_tree.cpp"

TEST_CASE( "red black tree should have a proper shape", "[red black tree]" ) {
    

    SECTION( "resizing bigger changes size and capacity" ) {
        // prepare the tree
        node n1 = node(1);
        node n2 = node(2);
        node n3 = node(3);
        node n4 = node(4);
        node n5 = node(5);
        node n6 = node(6);
        node n7 = node(7);
        node n8 = node(8);

        red_black_tree t = red_black_tree();
        t.insert(n2);
        t.insert(n1);
        t.insert(n7);
        t.insert(n4);
        t.insert(n8);
        t.insert(n3);
        t.insert(n6);
        t.insert(n5);

        // EXPECTATION:
        

        //todo: add expecation on links between nodes
        t.print();
        REQUIRE(t.root->key == 4);
        REQUIRE(t.root->color == BLACK);

        REQUIRE(t.root->left->key == 2);
        REQUIRE(t.root->left->color == RED);
        REQUIRE(t.root->left->parent == t.root);

        REQUIRE(t.root->left->left->key == 1);
        REQUIRE(t.root->left->left->color == BLACK);
        REQUIRE(t.root->left->left->parent == t.root->left);

        REQUIRE(t.root->left->right->key == 3);
        REQUIRE(t.root->left->right->color == BLACK);
        REQUIRE(t.root->left->right->parent == t.root->left);

        REQUIRE(t.root->right->key == 7);
        REQUIRE(t.root->right->color == RED);
        REQUIRE(t.root->right->parent == t.root);

        REQUIRE(t.root->right->right->key == 8);
        REQUIRE(t.root->right->right->color == BLACK);
        REQUIRE(t.root->right->right->parent == t.root->right->parent);

        REQUIRE(t.root->right->left->key == 6);
        REQUIRE(t.root->right->left->color == BLACK);
        REQUIRE(t.root->right->left->parent == t.root->right->parent);
        
        REQUIRE(t.root->right->left->left->key == 5);
        REQUIRE(t.root->right->left->left->color == RED);
        REQUIRE(t.root->right->left->left->parent == t.root->right->left);
    }
}