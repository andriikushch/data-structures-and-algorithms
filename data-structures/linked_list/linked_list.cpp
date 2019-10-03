#include <iostream>
using namespace std;

struct node
{
  node(int key) {
        this->key = key;
        this->next = nullptr;
  }
  int key;
  node * next;
};

// todo: add tail
struct linked_list
{
  node * head;

  linked_list() {
    this->head = nullptr;
  }

  void remove(int position) {
    int i = 0;

    node * current_node = this->head;
    node * prev_node;

    while (current_node != nullptr)
    {
      // remove from the beginning
      if (position == 0) {
          this->head = current_node->next;
          current_node = nullptr;

          return;
      }

      // remove from the middle
      if (i == position && current_node->next != nullptr) {
          prev_node->next = current_node->next;
          current_node = nullptr;
          return;
      }

      // remove from the end
      if (i == position && current_node->next == nullptr) {
          prev_node->next = nullptr;
          current_node = nullptr;

          return;
      }

      prev_node = current_node;
      current_node = current_node->next;

      i++;
    }

    return;
  }

  void insert(int position, node * new_item) {
    // insert to the beginning
    if (position == 0 && this->head == nullptr) {
      this->head = new_item;
      return;
    } else if (position == 0)
    {
      new_item->next = this->head;
      this->head = new_item;
      return;
    }

    int i = 0;

    node * current_node = this->head;
    node * prev_node;

    while (current_node != nullptr)
    {
      // insert in the middle
      if (i == position) {
          new_item->next = current_node;
          prev_node->next = new_item;

          return;
      }

      prev_node = current_node;
      current_node = current_node->next;

      i++;
    }

    // insert to the end
    if (i == position && prev_node->next == nullptr) {
      prev_node->next = new_item;
    }

    return;
  }

  int search_list(int val) {
    int i = 0;
    node * current_node = this->head;

    while (current_node != nullptr)
    {
      if (current_node->key == val) {
          return i;
      }
      current_node = current_node->next;
      i++;
    }

    return -1;    
  }

  void print() {
    node * current_node = this->head;
    cout << endl << "#######START##########" << endl;
    while (current_node != nullptr)
    {
      cout << current_node->key << endl;
      current_node = current_node->next;
    }
    cout << "########END############" << endl;
  }

};

int main() {
  node * n1 = new node(1);
  node * n2 = new node(2);
  node * n3 = new node(3);
  node * n4 = new node(4);
  node * n5 = new node(5);
  node * n6 = new node(6);
  node * n7 = new node(7);

  linked_list * ll = new linked_list();

  ll->insert(0, n1);
  ll->insert(1, n2);
  ll->insert(2, n3);
  ll->insert(0, n4);
  ll->insert(4, n5);
  ll->insert(0, n6);
  ll->insert(2, n7);
  ll->print(); // 6,4,7,1,2,3,5,

  delete n1;
  delete n2;
  delete n3;
  delete n4;
  delete n5;
  delete n6;
  delete n7;

  delete ll;

  return 0;
}
