#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

typedef struct Node {
	int val;
	MPI_Win next_win;
	struct Node *next;
} Node;

Node *head = NULL;
Node *tail = NULL;

MPI_Comm all_comm = MPI_COMM_WORLD;
MPI_Comm shmem_comm;
MPI_Win head_win;
int shmem_rank;
int shmem_size;

Node* New_List(int new_val)
{
	Node *alloc_node = NULL;
	MPI_Aint node_size = 0;
	int node_disp = sizeof(Node);

	if(shmem_rank == 0) {
		node_size = sizeof(Node);
	}
	MPI_Win_allocate_shared(node_size, node_disp, MPI_INFO_NULL, shmem_comm,
			&alloc_node, &head_win);
	MPI_Win_shared_query(head_win, 0, &node_size, &node_disp, &alloc_node);
	if(alloc_node == NULL) {
		printf("Node creation failed.\n");
		return NULL;
	}
	MPI_Win_fence(0, head_win);
	if(shmem_rank == 0) {
		alloc_node->val = new_val;
		alloc_node->next = NULL;
	}
	MPI_Win_fence(0, head_win);

	head = alloc_node;
	tail = alloc_node;
	return alloc_node;
}

Node* New_Node(Node* node, int new_val)
{
	Node *new_node = NULL;
	MPI_Aint node_size = 0;
	int node_disp = sizeof(Node);
	MPI_Win new_win;

	if(head == NULL) {
		return New_List(new_val);
	} else if(node == NULL) {
		return NULL;
	}

	if(shmem_rank == 0) {
		node_size = sizeof(Node);
	}
	MPI_Win_allocate_shared(node_size, node_disp, MPI_INFO_NULL, shmem_comm,
			&new_node, &new_win);
	MPI_Win_shared_query(new_win, 0, &node_size, &node_disp, &new_node);
	if(new_node == NULL) {
		printf("Node creation failed.\n");
		return NULL;
	}
	MPI_Win_fence(0, new_win);
	if(shmem_rank == 0) {
		new_node->val = new_val;
		new_node->next_win = node->next_win;
		new_node->next = node->next;
		node->next_win = new_win;
		node->next = new_node;
	}
	MPI_Win_fence(0, new_win);

	if(new_node->next == NULL) tail = new_node;
	return new_node;
}

void Clean_List()
{
	MPI_Win temp_win;
	Node *temp_next = NULL;

	while(head->next != NULL) {
		temp_win = head->next->next_win;
		temp_next = head->next->next;
		MPI_Win_fence(0, head->next_win);
		MPI_Win_free(&(head->next_win));
		head->next_win = temp_win;
		head->next = temp_next;
	}

	MPI_Win_fence(0, head_win);
	MPI_Win_free(&head_win);
	head = NULL;

	return;
}

int main(int argc, char *argv[])
{
	int i = 0;
	Node *pos = NULL;

	MPI_Init(&argc, &argv);
	MPI_Comm_split_type(all_comm, MPI_COMM_TYPE_SHARED, 0, MPI_INFO_NULL,
			&shmem_comm);
	MPI_Comm_rank(shmem_comm, &shmem_rank);
	MPI_Comm_size(shmem_comm, &shmem_size);

	for(i = 0; i < shmem_size; i++) {
		pos = New_Node(pos, i);
	}

	Clean_List();

	return 0;
}
