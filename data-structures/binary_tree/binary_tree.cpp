#include <iostream>
using namespace std;

struct node
{
    node(int n) {
        key = n;
        left = NULL;
        right = NULL;
    };

    int key;
    node * left;
    node * right;
};

struct binary_tree {
    node * root;
    binary_tree() {
        root = NULL;
    }

    void recursive_walk(node *n, void process(node n)) {
        if (n == NULL) {
            return;
        } else {
            process(*n);
        }

        recursive_walk(n->left,process);
        recursive_walk(n->right,process);
    }

    void insert(node &n) {
        if (root == NULL) {
            root = &n;

            return;
        }

        node * temp;
        temp = root;
        
        while(true) {
            if( n.key > temp->key) {
                if(temp->right == NULL) {
                    temp->right = &n;
                    break;
                } else {
                    temp = temp->right;
                    continue;
                }
            }
            else {
                if(temp->left == NULL) {
                    temp->left = &n;
                    break;
                } else {
                    temp = temp->left;
                    continue;
                }
            }
        }    
    }

    void remove(int val) {
        node * parent;

        node * temp;
        temp = root;
        

        while(true) {
            if (temp->key == val) {
                // no child casse
                if (temp->right == NULL && temp->left == NULL) {
                    if (parent->left == temp) {
                        parent->left = NULL;
                    } else {
                        parent->right = NULL;
                    }
                    
                    // delete
                    *temp = NULL;
                    break;
                } else 
                // one child case
                if((temp->right != NULL) != (temp->left != NULL)) {
                    if (parent->left == temp) {
                        parent->left = temp->left != NULL ? temp->left : temp->right;
                        
                        // delete
                        *temp = NULL;
                        break;

                    } else {
                        parent->right = temp->right != NULL ? temp->right : temp->left;
                        
                        // delete
                        *temp = NULL;
                        break;
                    }
                } else 
                // two child case
                {
                    //find in the right smallest
                    node * smallest;
                    node * parrent_of_the_smallest;

                    parrent_of_the_smallest = temp;
                    smallest = temp->right;
                    
                    while (true)
                    {
                        if(smallest->left != NULL) {
                            parrent_of_the_smallest = smallest;
                            smallest = smallest->left;
                        } else {
                            break;
                        }
                    }
                    
                    smallest->left = temp->left;
                    smallest->right = temp->right;

                    if (parent->left == temp) {
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
                    *temp = NULL;

                    break;
                }
            }
            

            // iteration
            if(val < temp->key) {
                if(temp->left != NULL) {
                    parent = temp;
                    temp = temp->left;
                    continue;
                } 
            }
            else {
                if(temp->right != NULL) {
                    parent = temp;
                    temp = temp->right;
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

    binary_tree t = binary_tree();
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
