#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct {
	int* p_data;
	int p_priority;
}item_t;

typedef struct {
	int size, index;
	item_t* item[1000];
}queue_t;

/*struct Node{
	item_t* item;
	struct Node* next;
};

void addIntNode(struct Node** head, int data, int priority,int *count) {
	if ((*count) > 100) {
		printf("\nQueue has reached the maximum element limit of 100 elements.\n");
		return;
	}
	struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
	item_t* newitem = (item_t*)malloc(sizeof(item_t));
	int* new_data = malloc(sizeof(int));

	*new_data = data;

	(*newitem).p_priority = priority;
	(*newitem).p_data = new_data;//!!!Somehow p_data does not get typecast into int, so I use int*workaround
	(*newitem).workaround = (*newitem).p_data;

	(*newnode).next = NULL;
	(*newnode).item = newitem;

	if ((*head) == NULL) {
		*head = newnode;
	}

	else {
		newnode->next = *head;//head points to current first entry, newnode's next equals head
		*head = newnode;//head points to newnode
	}

}


void printList(struct Node** head, int const* count) {
	if ((*head) == NULL) {
		printf("List is empty.\n");
		return;
	}
	struct Node* temp;
	temp = *head;
	for (int i = 1; i <= *count; i++) {
		printf("%d\n", *(temp->item->workaround));
		temp = temp->next;
	}
}*/

void init_qu(queue_t* queue1,int size) {
	queue1->size = size;
	queue1->index = 0;

}

int queue_add(queue_t* p_queue, item_t* p_item) {
	if (p_queue->index == p_queue->size) {
		printf("Queue is full.\n");
		return 1;
	}

	p_queue->item[p_queue->index] = p_item;
	p_queue->index++;
	return 0;
}

void printQ(queue_t* p_queue) {
	if (p_queue->index == 0) {
		printf("Queue is empty.\n");
		return;
	}
	int temp_index = p_queue->index;
	while (temp_index >= 0) {
		printf("Priority:%d  Data:%d\n", p_queue->item[temp_index]->p_priority, *(p_queue->item[temp_index]->p_data));
		temp_index--;
	}
}


int main() {
	queue_t queue1;
	init_qu(&queue1, 100);

	item_t item1;
	item1.p_data = (int*)malloc(sizeof(int));
	*item1.p_data = 15;
	item1.p_priority = 0;

	if (queue_add(&queue1, &item1) == 0)
		printf("Item has correctly been queued.\n");
	
	item_t item2;
	item2.p_data = (int*)malloc(sizeof(int));
	*item2.p_data = 15;
	item2.p_priority = 0;
	if (queue_add(&queue1, &item2) == 0)
		printf("Item has correctly been queued.\n");

	item_t item3;
	item3.p_data = (int*)malloc(sizeof(int));
	*item3.p_data = 15;
	item3.p_priority = 0;
	if (queue_add(&queue1, &item3) == 0)
		printf("Item has correctly been queued.\n");

	item_t item4;
	item4.p_data = (int*)malloc(sizeof(int));
	*item4.p_data = 15;
	item4.p_priority = 0;
	if (queue_add(&queue1, &item4) == 0)
		printf("Item has correctly been queued.\n");

	printQ(&queue1);



}