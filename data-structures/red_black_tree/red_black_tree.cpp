#include <iostream>
#include <string.h>
using namespace std;

struct node
{
    node(int n) {
        key = n;
        color = "";
        left = NULL;
        right = NULL;
        parent = NULL;
    };

    int key;
    node * parent;
    node * left;
    node * right;
    string color;
};

struct red_black_tree {
    node * root;
    red_black_tree() {
        root = NULL;
    }

    void recursive_walk(node *n, void process(node &n)) {
        if (n == NULL) {
            return;
        } 
        recursive_walk(n->left,process);
        process(*n);
        recursive_walk(n->right,process);
    }

    void insert(node &n) {
        if (root == NULL) {
            root = &n;
            root->color = "black";

            return;
        }

        n.color = "red";

        node * tmp;
        tmp = root;
        
        while(true) {
            if( n.key > tmp->key) {
                if(tmp->right == NULL) {
                    n.parent = tmp;
                    tmp->right = &n;
                    break;
                } else {
                    tmp = tmp->right;
                    continue;
                }
            }
            else {
                if(tmp->left == NULL) {
                    n.parent = tmp;
                    tmp->left = &n;
                    break;
                } else {
                    tmp = tmp->left;
                    continue;
                }
            }
        } 


        // check parent is red and if "unkle is red"
        if (n.parent != NULL && n.parent->color == "red" && n.parent->parent != NULL) {
            // check if "unkle" is left or right child
            node * uncle;
            if (n.parent->parent->left == n.parent) {
                // "unkle" is right
                if (n.parent->parent->right != nullptr) {
                    uncle = n.parent->parent->right;
                }
            } else {
                // "unkle" is left
                if (n.parent->parent->left != nullptr) {
                    uncle = n.parent->parent->left;
                }
            }

            // if "uncle" is red and parent is red, paint them black and grandpa paint into red
            if (uncle != nullptr && uncle->color == "red") {
                uncle->color = "black";
                n.parent->color = "black";

                // check if is not a root node
                if (n.parent->parent->parent != nullptr) {
                    n.parent->parent->color = "red";
                }
            }
        }   
    }
};

int main() {

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

    // t.remove(4);


    cout << "digraph graphname {" << endl;
    t.recursive_walk(t.root, [](node &n){
        cout << "\t" 
        << n.key << " [label=\"" 
        << "parent : "<< n.parent << "\\n" 
        << n.key 
        <<  "\\nself : " << &n << "\" style=filled fontcolor=\"white\" color=\"dodgerblue\" fillcolor=\""<<n.color<<"\" ]" << endl;
        
        if (n.left != NULL) {
            cout << "\t" << n.key << "->" << n.left->key << ";" << endl;
        }
        if (n.right != NULL) {
            cout << "\t" << n.key << "->" << n.right->key << ";"<< endl;
        }
    });
    cout << "}" << endl;

    return 0;
}
