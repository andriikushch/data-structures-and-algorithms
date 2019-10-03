#include <iostream>
using namespace std;

struct node {
    node(int key) {
        this->key = key;
        this->prev = nullptr;
    }

    int key;
    node * prev;
};

struct stack {
    node * top;
    
    stack(){
      this->top = nullptr;
    } 

    void push(node * n) {
        if (this->top != nullptr) {
            n->prev = this->top;
        }
        
        this->top = n;
    }

    node * pop() {
        if (this->top == nullptr) {
            return nullptr;
        }

        node * result = this->top;
        this->top = this->top->prev;

        return result;
    }

    void print() {
        node * current_node = this->top;
        cout << endl << "#######START##########" << endl;
        while(current_node != nullptr) {
            cout << current_node->key << endl;
            current_node = current_node->prev;
        }
        cout << "########END############" << endl;
    }
};

int main() {
  stack * s = new stack();
  
  node * n1 = new node(1);
  node * n2 = new node(2);
  

  s->push(n1);
  s->push(n2);
  s->print();

  s->pop();
  s->print();

  delete s;
  delete n1;
  delete n2;

  return 0;
}