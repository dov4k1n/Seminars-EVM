 #include <iostream>
using namespace std;

struct ListNode{
    int value;
    ListNode* next;
};

ListNode* Process(ListNode* Head){
    if (Head->next == nullptr){
        return Head;
    }
    ListNode* Now = Head;
    Head = Now->next;
    Now->next = nullptr;
    while (Head->next != nullptr){
        ListNode* New = Head->next;
        Head->next = Now;
        Now = Head;
        Head = New;
    }
    Head->next = Now;
    return Head;
}

void Print(ListNode* Head){
    while (Head->next != nullptr){
        cout << Head->value << endl;
        ListNode* tmp = Head->next;
        Head = tmp;
    }
    cout << Head->value << endl;
}

void Delete(ListNode* Head){
    while (Head->next != nullptr){
        ListNode* tmp = Head->next;
        delete Head;
        Head = tmp;
    }
    delete Head;
}

int main(){
    int size;
    cin >> size;
    ListNode* Head = new ListNode;
    cin >> Head->value;
    ListNode* Now = Head;
    for (int i = 0; i < size - 1; i++){
        ListNode* New = new ListNode;
        cin >> New->value;
        Now->next = New;
        Now = New;
    }
    Print(Head);
    cout << "/////////" << endl;
    Head = Process(Head);
    Print(Head);
    Delete(Head);
    return 0;
}