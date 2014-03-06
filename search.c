#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct node{
	char *x;
	struct node *next;
};

struct node *head = NULL;
struct node *curr = NULL;

struct node* create_list(){
	printf("Creating list with headnode as %s\n","test");
	struct node *ptr = (struct node*) malloc(sizeof (struct node));
	if(NULL == ptr){
		printf("Ah, no good node was not created");	
	};
	ptr->x = "test"; 
	ptr->next = NULL;

	head = curr = ptr;
	return ptr;
}

struct node* add_to_list(char *val){
	if (NULL == head){
		return(create_list());
	} 
	struct node *ptr = (struct node*)malloc(sizeof(struct node));
	if (NULL == ptr){
		printf("Node creation failed");
		return NULL;
	}
	ptr->x = val;
	ptr->next = NULL;

	curr->next = ptr;
	curr = ptr;
	printf("Added %s\n to list", ptr->x);
	return ptr; 
};

struct node* search_in_list(char *val, struct node **prev){
	struct node *ptr = head;
	struct node *temp = NULL;
	bool found = false;

	printf("Searching for %s\n",val);
	while(ptr != NULL){
		if(ptr->x == val){
			found = true;
			break;
		} else {
			temp = ptr;
			ptr = ptr->next; 
		}
	}
	if(true == found){
		if(prev)
			*prev = temp;
		return ptr;
	} else {
		return NULL;
	}
};

int main(){
	struct node *ptr = NULL;
	create_list();
	add_to_list("Ohlala");
	add_to_list("Something Something");
	ptr = search_in_list("Ohlala", NULL);
	printf("Found %s\n",ptr->x);
}






























//----------------------------------------
// int search(struct node **root){
// 	while(root != NULL){
// 		if(root->x == "More testing"){
// 			printf("%s\n", temp->x);	
// 			break;
// 		} else {
// 			root = root->next;
// 		}
// 	}

// 	return 0;
// }

// int main(){
// 	// Setting up linked list
// 	struct node *root;
// 	//Pointer to the place in the list
// 	struct node *conductor;


// 	//Intializing first entries...I think
// 	root = malloc(sizeof(struct node));
// 	root->next = 0;
// 	root -> x = "test";

// 	//Pointing the conductor to the beginning
// 	conductor = root;
// 	if(conductor != 0){
// 		while (conductor->next != 0){
// 			conductor = conductor->next;
// 		}
// 	}
	
// 	//Adding an entry to the list
// 	conductor->next = malloc(sizeof(struct node));
// 	conductor = conductor->next;
// 	if (conductor == 0){
// 		// Check the amount memory
// 		printf("Out of memory");
// 		return 0;
// 	}
// 	conductor->next =0;
// 	conductor->x = "More testing";
// 	search(&root);

// 	//Traversing the list
// 	return 0;
// }

