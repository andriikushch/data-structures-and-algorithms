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
                        // move subtree from parent to grandpa
                        grandpa->left = tmp->parent->right;
                        // make grandpa child of parent
                        tmp->parent->right = grandpa;

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

                    // 2. left Right Case (p is left child of g and tmp is right child of p)
                    if (grandpa->left == tmp->parent && tmp == tmp->parent->right) {
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
                    }

                    // 3. right Right Case (Mirror of case 1)
                    if (grandpa->right == tmp->parent && tmp == tmp->parent->right) {
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
                    // 4. right Left Case (Mirror of case 2)
                    if (grandpa->right == tmp->parent && tmp == tmp->parent->left) {
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

    //t.remove(4);

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
