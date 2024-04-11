#include <iostream>
#include <limits>

struct ListNode {
  int value;
  ListNode* next;
};

void clear_dublicates(ListNode* head) {
  ListNode *current = head, *next;

  if (current == nullptr) {
    return;
  }
  
  while (current->next != nullptr) {
    if (current->value == current->next->value) {
      next = current->next->next;
      delete current->next;
      current->next = next;
    } else {
      current = current->next;
    }
  }
}

void clear_equal(ListNode* head) {
  ListNode *current = head, *next, *previous;
  int flag = 0;

  if (current == nullptr) {
    return;
  }
  
  while (current->next != nullptr) {
    if (current->value == current->next->value) {
      next = current->next->next;
      delete current->next;
      current->next = next;
      flag = 1;
    } else {
      if (!flag)
        previous = current;
      current = current->next;
      if (flag) {
        flag = 0;
        delete previous->next;
        previous->next = current;
      }
    }
  }
}

void delete_list(ListNode* head) {
  ListNode *tmp = head, *body;
  while (tmp != nullptr) {
    body = tmp->next;
    delete tmp;
    tmp = body;
  } 
}

ListNode* read_list() {
  int input;
  ListNode *head = nullptr, *body, *tmp;
  while (std::cin >> input) {
    body = new ListNode;
    body->value = input;
    body->next = nullptr;

    if (head == nullptr) {
      head = body;
    } else {
      tmp = head;
      while (tmp->next != nullptr) {
        if (input < tmp->value) {
          std::cout << "error: list is not sorted correctly" << std::endl;
          delete_list(head);
          return nullptr;
        }
        tmp = tmp->next;
      }
      tmp->next = body;
    }
  }
  std::cin.clear(); // сбросить состояние fail в cin
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // очистить буфер ввода
  return head;
}

void print_list(ListNode* head) {
  ListNode* tmp = head;
  while (tmp != nullptr) {
    std::cout << tmp->value << " ";
    tmp = tmp->next;
  }
  std::cout << std::endl;
}

int main() {
  ListNode* head = read_list();

  if (head != nullptr) {
    std::cout << "inputed list: ";
    print_list(head);
  }

  
  std::cout << "print 1 to clear dublicates, print 0 to clear equal elements" << std::endl;
  int choice = -1;
  std::cin >> choice;

  if (choice == 1) {
    clear_dublicates(head);
    if (head != nullptr) {
      std::cout << "list cleared from dublicates: ";
      print_list(head);
    }
  } else if (choice == 0) {
    clear_equal(head);
    if (head != nullptr) {
      std::cout << "list cleared from equal elements: ";
      print_list(head);
    }
  }

  delete_list(head);
  
  return 0;
}