#ifndef MY_HEADER
#define MY_HEADER

struct korifi
{
	int k;
	int in_degree;
	struct korifi *next;
};

void appen(struct korifi** head_ref, int new_k, int new_d)
{
	struct korifi* new_korifi = (struct korifi*)malloc(sizeof(struct korifi));
	struct korifi* last = *head_ref;
	
	new_korifi->k = new_k;
	new_korifi->in_degree = new_d;

	if (*head_ref == NULL)
	{
		*head_ref = new_korifi;
		return;
	}

	while (last->next != NULL)
	{
		last = last->next;
	}

	last->next = new_korifi;
	return;
};

void del(struct korifi **head)
{
	struct korifi *temp=*head;
	temp=temp->next;
	*head=temp;
};

void delete_k(struct korifi **head, int key_korifi)
{
	struct korifi* temp = *head, *prev;
	
	if (temp != NULL && temp->k == key_korifi)
	{
		*head = temp->
		return;
	}

	while (temp != NULL && temp->k != key_korifi)
	{
		prev = temp;
		temp = temp->next;
	}

	if (temp == NULL) return;
	
	prev->next = temp->next;

};

void printList_k(struct korifi *n)
{
	while (n != NULL)
	{
		printf("%d %d\n", n->k, n->in_degree);
		n = n->next;
	}
};

struct Node
{
	int data;
	struct Node *next;
};

void append (struct Node** head_ref, int new_data)
{
	struct Node* new_node = (struct Node*) malloc (sizeof(struct Node));
	struct Node* last = *head_ref;

	new_node->data = new_data;
	new_node->next = NULL;

	if(*head_ref == NULL)
	{
		*head_ref = new_node;
		return;
	}

	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new_node;
	return;
};

void deletehead(struct Node **head)
{
	struct Node *temp=*head;
	temp=temp->next;
	*head=temp;
};

void printList(struct Node *n)
{
	while (n != NULL) 
	{
		printf("%d", n->data);
		n = n->next;
	}
};

void check_in(struct korifi *head, struct Node **S)
{
	while(head != NULL)
	{
		if(head->in_degree==0) append(S, head->k);
		head=head->next;
	}

};


void decrease(struct korifi* head, int t)
{
	while(head != NULL)
	{
		if(head->k == t)
			--(head->in_degree);
		head = head->next;
	}
};




















































#endif
