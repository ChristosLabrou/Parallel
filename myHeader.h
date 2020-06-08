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


};


#endif
