#include <iostream>

struct ListNode {
  int value;
  ListNode* next;
};

ListNode* clear_repetitions(ListNode* head) {

}

void read_list() {
  int elem, flag = 0;
  ListNode* old;

  while (std::cin >> elem) {
    ListNode* body;
    body->value = elem;
    body->next = nullptr;
    old->next = body;
    old = body;
    flag = 1;
  }
}

int main() {
  ListNode head;
}