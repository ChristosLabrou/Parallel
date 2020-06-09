#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <omp.h>
#include <time.h>

struct korifi
{
	int k;
	int in_degree;
	struct korifi *next;
};

void appen(struct korifi** head_ref, int new_k, int new_d) 
{ 
    struct korifi* new_korifi = (struct korifi*) malloc(sizeof(struct korifi)); 
  
    struct korifi *last = *head_ref;  
    
    new_korifi->k = new_k; 
    new_korifi->in_degree = new_d; 
    new_korifi->next = NULL; 
  
    if (*head_ref == NULL) 
    { 
       *head_ref = new_korifi; 
       return; 
    }   
       

    while (last->next != NULL) 
        last = last->next; 

    last->next = new_korifi; 
    return;     
};

void del(struct korifi **head){   
	struct korifi *temp=*head;			
	temp=temp->next;
	*head=temp;
};
	
void delete_k(struct korifi **head,int key_korifi)
{
    
    struct korifi* temp = *head, *prev; 
  
    if (temp != NULL && temp->k == key_korifi) 
    { 
        *head = temp->next;              
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
void printList_k(struct korifi *n) { 
    while (n != NULL) { 
        printf(" %d %d\n", n->k,n->in_degree); 
        n = n->next;
    } 
};
struct Node
{
	int data;
	struct Node *next;	
};


   
void append(struct Node** head_ref, int new_data) 
{ 
   
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node)); 
  
    struct Node *last = *head_ref; 
    new_node->data  = new_data; 
	new_node->next = NULL;
    if (*head_ref == NULL) 
    { 
       *head_ref = new_node; 
       return; 
    }   
       
    while (last->next != NULL) 
        last = last->next; 
   
    last->next = new_node; 
    return;     
};

void deletehead(struct Node **head){   
	struct Node *temp=*head;		
	temp=temp->next;
	*head=temp;
}
	

void printList(struct Node *n) { 
    while (n != NULL) { 
        printf(" %d ", n->data); 
        n = n->next;
    } 
};



void check_in(struct korifi *head, struct Node **S)
{
	#pragma omp task
	while(head!=NULL)
	{
		if(head->in_degree==0) append(S, head->k);
		head=head->next;	
	}
	
};

void decrease(struct korifi *head, int t)
{
	while(head!=NULL)
		{
			if(head->k==t)
				--(head->in_degree);
				
			head=head->next;	
		}
};


int main() 
{
	int i = 0;
	int tot = 0;
	double start, end;
	int nodes, trash, num_e;
	int RSIZ = 30;
	FILE *fptr=fopen("dag.txt", "r");
	fscanf(fptr,"%d %d %d", &nodes, &trash, &num_e);
	fclose(fptr);
	int LSIZ=num_e;
	char line[LSIZ][RSIZ];
	
	fptr = fopen("dag.txt", "r");
	i=0;
	while(fptr!= NULL)
	{
		fscanf(fptr, "%d %d", &line[i][0], &line[i][1]);
		i++;
		if(i==LSIZ) break;
    }
	fclose(fptr);
    tot = i;
	int matrix[tot][2]; //DO NOT REMOVE!!!!! IF IT IS REMOVED PROGRAM BREAKS!!!!!!!
	char const *temp1,*temp2;
	int e[num_e][2];
	for(i = 0; i<tot; i++)  		
	  {
	  	temp1=&line[i+1][0];
		temp2=&line[i+1][2];
	  	e[i][1]=atoi(temp2);
		e[i][0]=atoi(temp1);	
	   }
	int kor_temp[nodes][2];
	for(i=0; i<nodes; i++){
		
		kor_temp[i][0]=i;
		kor_temp[i][1]=0;
	}
	int j;
	for(i=0; i<nodes; i++)
		for(j=0; j<num_e; j++)
			if(kor_temp[i][0]==e[j][1])
				kor_temp[i][1]++;
	struct Node *S;
	struct Node *L;
	
	struct korifi *kor;
	kor=NULL;
	S=NULL;
	L=NULL;

	for(i=0; i<nodes; i++)
		appen(&kor,kor_temp[i][0],kor_temp[i][1]);

	check_in(kor,&S);
	int temp;
	start = omp_get_wtime();
	while(S!=NULL)
	{
		#pragma omp parallel
		delete_k(&kor,S->data);
		append(&L, S->data);
		
		temp=-1;
		#pragma omp parallel for
		for(i=0; i<num_e; i++)
		{
			if(e[i][0]==S->data)
			{	
				temp=e[i][1];
				#pragma omp critical
				decrease(kor,temp);
			}
		}
		
		deletehead(&S);
		while(S!=NULL)
		{
			deletehead(&S); //clear S gia na mhn emf 2h fora komvous
		}
		check_in(kor,&S);
	}
	end = omp_get_wtime();

	printf("\nTopologikh diataksi:\n");
	printList(L);
	double duration = end - start;
	printf("\n\n\tstart = %.16g\n\tend = %.16g\n\tDuration = %.16g\n",start, end, duration);
	
	//oi entoles autes itan gia exagogi dedomenon
	/*FILE *output = fopen("output_parallel.csv", "a");
	fprintf(output, "%.16g\n",duration);*/
    return 0;
}
