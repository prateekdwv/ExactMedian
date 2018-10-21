#include<stdio.h>
#include <stdlib.h>
#include <time.h>

void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int testPartition(int *arr, int len, int u, int v)
{
    for(int i=0; i < u; i++)
    {
        if(arr[i] > arr[u])
            return 0;
    }

    for(int j=u+1; j<v; j++)
    {
        if(arr[j] < arr[u] || arr[j] > arr[v])
            return 0;
    }

    for(int k=v+1; k<len; k++)
    {
        if(arr[k] < arr[v])
            return 0;
    }

    return 1;
}

int partition(int *arr, int len, int *numComp)
{
    int pivot = arr[0];

    int i = 1;
    int j = len - 1;    
    while(1){
        
        while(arr[i] <= pivot){
            i = i + 1;
            (*numComp)++;
        }
        (*numComp)++;

        while(arr[j] > pivot){
            j = j - 1;
            (*numComp)++;
        }
        (*numComp)++;

        (*numComp)++;
        if(i < j)
        {
            swap((arr+i),(arr+j));
            i++;
            j--;
        }
        else
            break;
    }
    return i-1;
}

int * randPermGen(int length)
{
	int *perm = (int *) malloc(length*sizeof(int));

	int i = 0;
	int j = 0;
	
	srand((unsigned int)time(NULL));

	for(i = 0; i < length; i++)
	{
		j = rand()%1023;

		if(j != 0)
			perm[i] = rand()%j;
	}

	return perm;
}

void multiPartition(int *arr, int len, int *u, int *v, int *numComp)
{
    swap(arr, (arr+*v));
    swap((arr+1), (arr+*u));
        
    int indexU = partition(arr+1,len-1, numComp) + 1;

    swap(arr, (arr+indexU));
    swap((arr+1), (arr+indexU-1));

    int indexV = partition((arr+indexU), len-indexU, numComp) + indexU;

    swap((arr+indexU), (arr+indexV));

    // Fix the index of u and return the partion index
    *u = indexU - 1;

    // No fix on v, just returning the partition index
    *v = indexV;
}

int main(int argc, char const *argv[])
{
    /*
    int per = 0;
    int comp = 0;
    for(int j=1; j<=1000; j++)
    {
        int numbComp = 0;
        srand((unsigned int)time(NULL));
        int *arr = randPermGen(10000);
            
        int index = partition(arr, 10000, rand()%100, &numbComp);

        per += testPartition(arr,10,index);
        comp += numbComp;
    }

    printf("%d    %d", per, comp/1000);
    */

    int arr[] = {4,5,2,7,8,3,1,9,0,6};

    /* for(int i=0; i<10; i++)
        printf("%d ",arr[i]);
    printf("\n"); */
    int per = 0;

    
    for(int i = 1; i <= 100; i++)
    {
        srand((unsigned int)time(NULL));
        int numComp = 0;
        int u = rand()%10000;
        int v = rand()%10000;

        int *arr = randPermGen(10000);

        multiPartition(arr, 10000, &u, &v, &numComp);

        per += testPartition(arr, 10000, u, v);
    }
    
    printf("%d\n", per);

    /* for(int i=0; i<10; i++)
        printf("%d ",arr[i]);
    printf("\nIndexU: %d IndexV: %d\n", u, v); */
   return 0;
}