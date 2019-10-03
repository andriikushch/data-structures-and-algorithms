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

    void recursive_walk(node *n, void process(node n)) {
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

        node * current;
        current = root;
        
        while(true) {
            if( n.key > current->key) {
                if(current->right == NULL) {
                    current->right = &n;
                    break;
                } else {
                    node * tmp = current;

                    current = current->right;
                    current->parent = tmp;
                    continue;
                }
            }
            else {
                if(current->left == NULL) {
                    current->left = &n;
                    break;
                } else {
                    node * tmp = current;

                    current = current->left;
                    current->parent = tmp;
                    continue;
                }
            }
        }    
    }

    void remove(int val) {
        node * parent;

        node * current;
        current = root;
        

        while(true) {
            if (current->key == val) {
                // no child casse
                if (current->right == NULL && current->left == NULL) {
                    if (parent->left == current) {
                        parent->left = NULL;
                    } else {
                        parent->right = NULL;
                    }
                    
                    // delete
                    *current = NULL;
                    break;
                } else 
                // one child case
                if((current->right != NULL) != (current->left != NULL)) {
                    if (parent->left == current) {
                        parent->left = current->left != NULL ? current->left : current->right;
                        
                        // delete
                        *current = NULL;
                        break;

                    } else {
                        parent->right = current->right != NULL ? current->right : current->left;
                        
                        // delete
                        *current = NULL;
                        break;
                    }
                } else 
                // two child case
                {
                    //find in the right smallest
                    node * smallest;
                    node * parrent_of_the_smallest;

                    parrent_of_the_smallest = current;
                    smallest = current->right;
                    
                    while (true)
                    {
                        if(smallest->left != NULL) {
                            parrent_of_the_smallest = smallest;
                            smallest = smallest->left;
                        } else {
                            break;
                        }
                    }
                    
                    smallest->left = current->left;
                    smallest->right = current->right;

                    if (parent->left == current) {
                        parent->left = smallest;
                    } else {
                        parent->right = smallest;
                    }
                
                    if (parrent_of_the_smallest->left == smallest) {
                        parrent_of_the_smallest->left = NULL;
                    } else {
                        parrent_of_the_smallest->right = NULL;
                    }

                    // delete
                    *current = NULL;

                    break;
                }
            }
            

            // iteration
            if(val < current->key) {
                if(current->left != NULL) {
                    parent = current;
                    current = current->left;
                    continue;
                } 
            }
            else {
                if(current->right != NULL) {
                    parent = current;
                    current = current->right;
                    continue;
                }
            }

            break;
        }    
    };
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
    t.recursive_walk(t.root, [](node n){
        cout << "\t" << n.key << " [label=\""<< n.key <<"\" style=filled fontcolor=\"white\" color=\"dodgerblue\" fillcolor=\""<<n.color<<"\" ]" << endl;
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
