#include <iostream>
using namespace std;

struct node
{
  int key;
  node * next;
};

void print_list(node * begin);
int search_list(node * begin, int val);
node * insert(node * begin, int position, node * new_item);
node * remove(node * begin, int position);

int main() {
  node n1;
  n1.key = 1;
  n1.next = nullptr;

  node * head = &n1;

  node n2;
  n2.key = 2;
  n2.next = nullptr;

  node n3;
  n3.key = 3;
  n3.next = nullptr;

  n1.next = &n2;
  n2.next = &n3;

  node n4;
  n4.key = 4;
  n4.next = nullptr;

  head = insert(head, 3, &n4);
  print_list(head);

  head = remove(head, 1);
  print_list(head);


  return 0;
}

node * remove(node * current_node, int position) {
  int i = 0;

  node * head = current_node;
  node * prev_node;

  while (current_node != nullptr)
  {
    // remove from the beginning
    if (position == 0) {
        head = current_node->next;
        current_node = nullptr;

        return head;
    }

    // remove from the middle
    if (i == position && current_node->next != nullptr) {
        prev_node->next = current_node->next;
        current_node = nullptr;
        return head;
    }

     // remove from the end
    if (i == position && current_node->next == nullptr) {
        prev_node->next = nullptr;
        current_node = nullptr;

        return head;
    }

    prev_node = current_node;
    current_node = current_node->next;

    i++;
  }

  return head;
}

node * insert(node * current_node, int position, node * new_item) {
  int i = 0;

  node * head = current_node;
  node * prev_node;

  while (current_node != nullptr)
  {
    // insert to the beginning
    if (position == 0) {
        new_item->next = current_node;
        return new_item;
    }
    
    // insert in the middle
    if (i == position) {
        new_item->next = current_node;
        prev_node->next = new_item;

        return head;
    }

    prev_node = current_node;
    current_node = current_node->next;

    i++;
  }

  // insert to the end
  if (i == position && prev_node->next == nullptr) {
    prev_node->next = new_item;
  }

  return head;
}

int search_list(node * current_node, int val) {
  int i = 0;
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

void print_list(node * current_node) {
  while (current_node != nullptr)
  {
    cout << current_node->key << endl;
    current_node = current_node->next;
  }
}