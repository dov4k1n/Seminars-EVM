#include<iostream>


struct ListNode {
ListNode* next;
int value;
};



void print(ListNode *head){
	while(head!=nullptr){
		std::cout<<head->value;
		head=head->next;
	}
}

void DelNext( ListNode* head ) {
    ListNode *curr=head, *next=NULL;
    while (curr!=NULL) {
    	next=curr->next;
    	delete curr;
    	curr=next;
    }
}

ListNode* Process(ListNode* head){
	ListNode *cur, *prev, *tmp;
	cur=head;
	prev=head;
	for(cur=head,prev=head;cur->next!=nullptr;prev=cur, cur=cur->next);
	tmp=cur;
	prev->next=cur->next;
	tmp->next=head;
	return tmp;
}


int main(){
	    ListNode *prev=NULL,  *Now, *New;
    int i, k, l, elem;
    std::cout<<"Введите число элементов списка"<<std::endl;
    std::cin>>k;
    std::cout<<"Введите элементы списка"<<std::endl;
    for (i = 0; i <  k; i++)  {
        std::cin >> elem;
        New = new ListNode;
        New->value = elem;
        New->next = nullptr;
        if (prev == nullptr) {
        	prev = New;
  		}
        else {
            Now = prev;
            while (Now->next != nullptr) {
                Now = Now->next;
            }
            Now->next = New;
        }
    }
    prev=Process( prev);
     while (prev != nullptr) {
        std::cout << prev->value << " ";
        prev = prev->next;
    }  
    DelNext(prev);
    return 0;
}