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

    void connectOnTheLeftSide(node * n) {
        left = n;
        if (left) {
            n->parent = this;
        }
    }

    void connectOnTheRightSide(node * n) {
        right = n;
        if (right) {
            n->parent = this;
        }
    }

    bool isRightChild(node * n) {
        return right == n;
    }

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

    void rightRightCase(node * tmp , node * grandpa) {
        // move subtree from parent to grandpa
        grandpa->right = tmp->parent->left;
        // make grandpa child of parent
        tmp->parent->left = grandpa;

        // make grandpa parent parent of parent
        tmp->parent->parent = grandpa->parent;
        // make parent parent of grand pa
        grandpa->parent = tmp->parent;

        // swap colors
        string parent_color = tmp->parent->color;
        tmp->parent->color = grandpa->color;
        grandpa->color = parent_color;

        // todo: change tmp?
        tmp = tmp->parent;
    }

    void rightLeftCase(node * tmp, node * grandpa) {
        string tmp_parent_color = tmp->parent->color;
        // rotate
        grandpa->right = tmp;
        node * t = tmp->right;
        tmp->right = tmp->parent;

        tmp->parent->parent = tmp;
        tmp->parent->left = t;
        tmp->parent = grandpa;

        // turn
        tmp->parent->right = tmp->left;
        tmp->left = tmp->parent;
        tmp->parent = tmp->parent->parent;

        // swap colors
        tmp->left->color = tmp->color;
        tmp->color = tmp_parent_color;
    }

    void leftLeftCase(node * tmp , node * grandpa) {
        // for readability
        node * parent = tmp->parent;

        // how grandpa attached to it's parent
        int side = 0; // -1 left, 0 no parent, 1 right

        // move subtree from parent to grandpa
        grandpa->connectOnTheLeftSide(parent->right);

        // store grandpa parent
        node * grandpa_parent = grandpa->parent;
        if (grandpa_parent) {
            if (grandpa_parent->isRightChild(parent)) {
                side = 1;
            } else {
                side = -1;
            }
        }

        // make grandpa child of parent
        parent->connectOnTheRightSide(grandpa);

        // restore link to previous grandpa parent
        if (side == 1) {
            grandpa_parent->connectOnTheRightSide(parent);
        } else if (side == -1) {
            grandpa_parent->connectOnTheLeftSide(parent);
        } else {
            parent->parent = NULL;
        }

        // swap colors
        parent->swapColors(grandpa);
    }

    void leftRightCase(node * tmp , node * grandpa) {
        string tmp_parent_color = tmp->parent->color;

        // rotate
        grandpa->left = tmp;
        node * t = tmp->left;
        tmp->left = tmp->parent;

        tmp->parent->parent = tmp;
        tmp->parent->right = t;
        tmp->parent = grandpa;

        // turn
        tmp->parent->left = tmp->right;
        tmp->right = tmp->parent;
        tmp->parent = tmp->parent->parent;

        // swap colors
        tmp->right->color = tmp->color;
        tmp->color = tmp_parent_color;
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
                        leftLeftCase(tmp, grandpa);
                    }

                    // 2. left Right Case (p is left child of g and tmp is right child of p)
                    if (grandpa->left == tmp->parent && tmp == tmp->parent->right) {
                        leftRightCase(tmp, grandpa);
                    }

                    // 3. right Right Case (Mirror of case 1)
                    if (grandpa->right == tmp->parent && tmp == tmp->parent->right) {
                        rightRightCase(tmp, grandpa);
                    }
                    // 4. right Left Case (Mirror of case 2)
                    if (grandpa->right == tmp->parent && tmp == tmp->parent->left) {
                        rightLeftCase(tmp, grandpa);
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
