#include <iostream>
using namespace std;

struct node {
    node(int key) {
        this->key = key;
        this->next = nullptr;
    }

    int key;
    node * next;
};

struct queue
 {
    node * head;
    node * tail;
    
    queue(){
      this->head = nullptr;
      this->tail = nullptr;
    } 

    void push(node &n) {

        if (this->tail == nullptr && this->head == nullptr) {
            this->tail = &n;
            this->head = &n; 

            return;
        }

        this->tail->next = &n;
        this->tail = &n;
    }

    node * pop() {
        if (this->head == nullptr && this->tail == nullptr) {
            return nullptr;
        }

        node * result = this->head;
        this->head  = this->head->next;

        return result;
    }

    void print() {
        node * current_node = this->head;
        cout << endl << "#######START##########" << endl;
        while(current_node != nullptr) {
            cout << current_node->key << endl;
            current_node = current_node->next;
        }
        cout << "########END############" << endl;
    }
};

int main() {
  queue * s = new queue();
  
  node n1 = node(1);
  node n2 = node(2);
  

  s->push(n1);
  s->push(n2);

  s->print();

  cout << endl << s->pop()->key << endl;
  s->print();


  delete s;

  return 0;
}