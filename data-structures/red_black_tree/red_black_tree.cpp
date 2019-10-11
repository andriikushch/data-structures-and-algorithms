#include <iostream>
#include <string.h>
using namespace std;

const string BLACK = "black";
const string RED = "red";

struct node
{
    node(int n) {
        key = n;
        color = "";
        left = NULL;
        right = NULL;
        parent = nullptr;
    };

    int key;
    node * parent;
    node * left;
    node * right;
    string color;

    void swapColors(node * n) {
        string tmp_color = n->color;
        n->color = color;
        color = tmp_color;
    }
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

        recursive_walk(n->left, process);
        process(*n);
        recursive_walk(n->right, process);
    }

    void rightRightCase(node * tmp) {
        // for readability
        node * parent = tmp->parent;
        node * grandpa = tmp->parent->parent;

        node * parent_left_subtree = parent->left;

        parent->left = grandpa;
        parent->parent = grandpa->parent;
        grandpa->parent = parent;

        grandpa->right = parent_left_subtree;

        // swap colors
        parent->swapColors(grandpa);

        if (parent->parent == NULL) {
            root = parent;
        }
    }

    void rightLeftCase(node * tmp) {
        // for readability
        node * parent = tmp->parent;
        node * grandpa = tmp->parent->parent;

        node * tmp_right_subtree = tmp->right;

        tmp->right = parent;
        parent->left = tmp_right_subtree;
        parent->parent = tmp;

        tmp->parent = grandpa;

        rightRightCase(parent);
    }

    void leftLeftCase(node * tmp) {
        // for readability
        node * parent = tmp->parent;
        node * grandpa = tmp->parent->parent;

        node * parent_right_subtree = parent->right;

        parent->right = grandpa;
        parent->parent = grandpa->parent;
        grandpa->parent = parent;

        grandpa->left = parent_right_subtree;

        // swap colors
        parent->swapColors(grandpa);

        if (parent->parent == NULL) {
            root = parent;
        }
    }

    void leftRightCase(node * tmp) {
        // for readability
        node * parent = tmp->parent;
        node * grandpa = tmp->parent->parent;

        node * tmp_left_subtree = tmp->left;

        tmp->left = parent;
        parent->right = tmp_left_subtree;
        parent->parent = tmp;

        tmp->parent = grandpa;

        leftLeftCase(parent);
    }

    void insert(node &n) {
        // 1. do regular b-tree insertion
        if (root == NULL) {
            root = &n;
            root->color = BLACK;

            return;
        }

        n.color = RED;

        node * tmp;
        tmp = root;

        while(true) {
            if(n.key > tmp->key) {
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

        // balace tree
        tmp = &n;

        while(true) {

            // 2.  if tmp is root, change color of tmp as BLACK
            if (tmp->parent == NULL) {
                tmp->color = BLACK;
                break;
            }

            // 3. following if color of tmp’s parent is not BLACK and x is not root.
            // check parent is red and if "unkle is red"
            if (tmp->parent != NULL && tmp->parent->color == RED && tmp->parent->parent != NULL) {
                // check if "unkle" is left or right child
                node * uncle;
                node * grandpa = tmp->parent->parent;

                if (grandpa->left == tmp->parent) {
                    // "unkle" is right
                    if (grandpa->right != NULL) {
                        uncle = grandpa->right;
                    }
                } else {
                    // "unkle" is left
                    if (grandpa->left != NULL) {
                        uncle = grandpa->left;
                    }
                }

                // if "uncle" is NULL stop
                if (uncle == NULL) {
                    break;
                }


                // if "uncle" is red and parent is red, paint them black and grandpa paint into red
                if (uncle != NULL && uncle->color == RED) {
                    // change color of parent and uncle as BLACK
                    uncle->color = BLACK;
                    tmp->parent->color = BLACK;

                    // change color of grand parent as RED
                    grandpa->color = RED;

                    // change tmp = tmp’s grandparent, repeat steps 2 and 3 for new tmp
                    tmp = grandpa;

                    continue;
                } else if (uncle != NULL && uncle->color == BLACK) {
                    // 1. left Left Case (p is left child of g and tmp is left child of p)
                    if (grandpa->left == tmp->parent && tmp == tmp->parent->left) {
                        leftLeftCase(tmp);
                    }

                    // 2. left Right Case (p is left child of g and tmp is right child of p)
                    if (grandpa->left == tmp->parent && tmp == tmp->parent->right) {
                        leftRightCase(tmp);
                    }

                    // 3. right Right Case (Mirror of case 1)
                    if (grandpa->right == tmp->parent && tmp == tmp->parent->right) {
                        rightRightCase(tmp);
                    }
                    // 4. right Left Case (Mirror of case 2)
                    if (grandpa->right == tmp->parent && tmp == tmp->parent->left) {
                        rightLeftCase(tmp);
                    }
                }
            }

            // simplify
            if (tmp->parent != NULL && tmp->parent->color == BLACK) {
                break;
            }
        }

        // simplify
        if (tmp->parent == NULL) {
            root = tmp;
        }
    }

    void remove(node * n) {
        
    }

    void print() {
        cout << "digraph graphname {" << endl;
        recursive_walk(root, [](node &n){
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
    }
};
