#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

typedef struct Node {
	int val;
	MPI_win next_win;
	Node *next;
} Node

Node *head = NULL;
Node *pos = NULL;

Node* New_List(int new_val)
{
	Node *alloc_node = (Node*)malloc(sizeof(Node));
	if(node == NULL) {
		printf("Node creation failed.\n");
		return NULL;
	}
	alloc_node->val = new_val;
	alloc_node->next = NULL;

	head = alloc_node;
	pos = alloc_node;
	return alloc_node;

Node* New_Node(Node* node, int new_val)
{
	if(head == NULL) {
		return new_list();
	}

	Node *new_node = (Node*)malloc
