#include <stdio.h> 
#include <stdlib.h> 

typedef struct {
	int* p_data;
	int p_priority;
}item_t;

typedef struct Node{
	item_t* item;
	Node* next;//demek ki neymiþ typedef struct yapacaksan onun içinde ayný sturct'ý kullanmayacaksýn þayet öyle yaparsan compiler hata verir ve geri döner her yere struct Node* yazarsýn Teþekkürler Türkiye
}Node;

// Function to Create A New Node 
void push(Node** r_head , item_t *r_item)
{
	Node* newnode = (Node*)(malloc(sizeof(Node)));//allocate space for newnode
	newnode->next = NULL;//next null
	*(newnode->item->p_data) = *(r_item->p_data);//newnode's item's p_data's pointed value equals r_item's p_data's pointed value
	newnode->item->p_priority = r_item->p_priority;
	
	if (r_head == NULL) {//if list is empty make head pointer the new node
		*r_head = newnode;
		return;
	}
	Node* temp; temp = *r_head;
	while (((newnode->item->p_priority) < (temp->next->item->p_priority))||temp->next!=NULL) 
		temp = temp->next;
	//with this loop we make sure that temp now points to a node
	//whose next pointer points to a node which has a priority equal to or smaller than the newnode
	//
	newnode->next = temp->next;//newnode points to smaller or equal priority node
	temp->next = newnode;//higher priority node is made to point to newnode by accessing through temp, the next ptr
}

void pop(Node** r_head) {
	
	if (r_head = NULL) {//nothing to pop
		printf("List is empty.\n");
		return;
		Node* temp;
		temp = *r_head; *r_head = (*r_head)->next; free(temp);//highest priority is always at the beginning of the queue
	}
}

void print(Node**r_head){
	Node* temp;
	temp = *r_head;
	if (temp == NULL) {
		printf("List is empty.\n");
		return;
	}
	while (temp->next != NULL) {
		printf("Priority:%d Data:%d", temp->item->p_priority, *(temp->item->p_data));
		temp = temp->next;
	}
}


int main()
{
	Node* head = NULL;
	item_t item1; *(item1.p_data) = 15; item1.p_priority = 1;
	item_t item2; *(item2.p_data) = -15; item2.p_priority = 0;
	item_t item3; *(item3.p_data) = 12; item3.p_priority = 1;
	item_t item4; *(item4.p_data) = -28; item4.p_priority = 0;
	item_t item5; *(item5.p_data) = 5; item5.p_priority = 1;
	item_t item6; *(item6.p_data) = 155; item6.p_priority = 2;
	item_t item7; *(item7.p_data) = 286; item7.p_priority = 2;
	item_t item8; *(item8.p_data) = 375; item8.p_priority = 2;
	item_t item9; *(item9.p_data) = 3; item9.p_priority = 1;
	item_t item10; *(item10.p_data) = -45; item10.p_priority = 0;
	item_t item11; *(item11.p_data) = -83; item11.p_priority = 0;
	item_t item12; *(item12.p_data) = -157; item12.p_priority = 0;
	push(&head, &item1);
	push(&head, &item2);
	push(&head, &item3);
	push(&head, &item4);
	push(&head, &item5);
	push(&head, &item6);
	push(&head, &item7);
	push(&head, &item8);
	push(&head, &item9);
	push(&head, &item10);
	push(&head, &item11);
	push(&head, &item12);
	printf(&head);



}
