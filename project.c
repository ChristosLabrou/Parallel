#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <time.h>

#define LSIZ 128
#define RSIZ 10

struct korifi
{
	int k;
	int in_degree;
	struct korifi *next;
};

void appen(struct korifi** head_ref, int new_k, int new_d){};
