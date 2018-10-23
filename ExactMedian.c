#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>

// Structure having two fields item and its index in the given array.
struct node{
      int item;
      int index;
      
};

void swap(struct node *i, struct node *j)
{
    struct node temp = *i;
    *i = *j;
    *j = temp;
}

// Utility function to generate a random permutation of given length
// where each element will be in the range [0,elemRange-1] and NO REPETITION
int * randPermGen(int length, int elemRange){
    // Allocating memory
	int *perm = (int *) malloc(length*sizeof(int));
	
	srand((unsigned int)time(NULL));

    int i=0;
    while(i < length)
	{
		// To enhance randomness
        int j = rand()%elemRange;
        int randNum;
        if(j != 0)
			randNum = rand()%j;
        else
            continue;

        // Check for no repeatition
        int flag = 0;
        for(int k=0; k<i; k++)
        {
            if(perm[k] == randNum)
            {
                flag = 1;
                break;
            }
        }

        if(flag)
            continue;
        else
        {       
            perm[i] = randNum;
            i++;
        }
	}

	return perm;
}

//partition procedure that will partition array around its first element.
 int partition(struct node a[], int l, int r){
     int piv=a[l].item,i=l+1,j=r;
    struct node temp;

    while(i<=j)
    {
        while(a[i].item<=piv && i<=j)
            i++;
        while(a[j].item>=piv && i<=j)
            j--;
        if(i<j)
        {
            temp = a[j];
            a[j] = a[i];
            a[i] = temp;
        }
    }
    //swapping the 'pivot element node' with the element at its final position.
    temp = a[j];
    a[j] = a[l];
    a[l] = temp;
    
    return j;
}


//Quick sort procedure
void quick_sort(struct node a[], int l, int r)
{
    if(l>r)
    return;
    int k=partition(a,l,r);
    quick_sort(a,l,k-1);
    quick_sort(a,k+1,r);
}

// Partition the array around the first element
int mPartition(struct node arr[], int len, int *numComp)
{
    // Picking pivot element
    int pivot = arr[0].item;

    // Partition indicator
    int i = 1;
    int j = len - 1;

    while(1){
        
        // Bypass the elements which are already less than pivot
        while(arr[i].item <= pivot){
            i = i + 1;
            (*numComp)++;
        }
        (*numComp)++;

        // Bypass the elements which are already greater than pivot
        while(arr[j].item > pivot){
            j = j - 1;
            (*numComp)++;
        }
        (*numComp)++;

        (*numComp)++;
        if(i < j)
        {
            // Fix inversions
            swap(&arr[i], &arr[j]);
            i++;
            j--;
        }
        else
            break;
    }
    return i-1;
}

// Function that partition the array around two elements u and v
void multiPartition(struct node arr[], int len, int *u, int *v, int *numComp)
{
    // Bring the v ahead in array, to avoid messing up with other elements
    swap(&arr[0], &arr[*v]);

    // Bring u ahead so that we can all partition
    swap(&arr[1], &arr[*u]);
    
    // Partition the array excluding the first element which has v
    int indexU = mPartition(&arr[1],len-1, numComp) + 1;

    // Take v to the second half of the partition
    swap(&arr[0], &arr[indexU]);

    // Take u to its place
    swap(&arr[1], &arr[indexU-1]);

    // Partition the remaining array
    int indexV = mPartition(&arr[indexU], len-indexU, numComp) + indexU;

    // Take v to its position
    swap(&arr[indexU], &arr[indexV]);

    // Fix the index of u and return the partion index
    *u = indexU - 1;

    // No fix on v, just returning the partition index
    *v = indexV;
}

// Function that modifies the input array with median at (len/2)th index
// in 1.5n+o(n) comparision on expectation
int exactMedian(int *inArray, int len, int *numComp)
{
    // Create a array of structure to work on. This is for the sake of reusability
    struct node *arr = (struct node *)malloc(len*sizeof(struct node));
    
    for(int  i = 0; i < len; i++)
    {
        arr[i].item = inArray[i];
        arr[i].index = i;
    }
    
    // Random Sample S
        int sampleSize = floor(pow((double)len, 3.0/4.0));

        // Generate random permutation of indice
        int *randSampleIndex = randPermGen(sampleSize, len);

        // Random sample, with its index in original array
        struct node *randomSampleArray = (struct node *)malloc(sampleSize*sizeof(struct node));

        for(int i=0; i<sampleSize; i++)
        {
            randomSampleArray[i].item = arr[randSampleIndex[i]].item;
            randomSampleArray[i].index = randSampleIndex[i];
        }

    // Sort random sample
        quick_sort(randomSampleArray, 0, sampleSize-1);

    // Pick two elements u and v from random sample
        int rank = floor(sampleSize/2);
        int smallOrder = floor(pow(len,1/2));

        int rankU = rank - smallOrder;
        int rankV = rank + smallOrder;

        int indexU;
        int indexV;

        if(rankU >= 0 )
            indexU = randomSampleArray[rankU].index;
        else
            indexU = 0;

        if(rankV < sampleSize)
            indexV = randomSampleArray[rankU].index;
        else
            indexV = 0;

    // Multipartition across u and v
        multiPartition(arr, len, &indexU, &indexV, numComp);

    // Sort Elements between u and v
        quick_sort(arr, indexU, indexV);

    printf("%d %d\n", indexU, indexV);

    
    /* for(int i = 0; i < len; i++)
    {
        printf("%d  ", arr[i].item);
    }
    printf("\n"); */
    
    // Median is at index n/2
    int medianIndex = (int)floor(len/2);
    int median = arr[medianIndex].item;

    // Free Memory
    free(arr);
    free(randomSampleArray);

    return median;
}

/* Comparison function. Receives two generic (void) pointers to the items under comparison. */
int compare_ints(const void *p, const void *q) {
    int x = *(const int *)p;
    int y = *(const int *)q;

    /* Avoid return x - y, which can cause undefined behaviour
       because of signed integer overflow. */
    if (x < y)
        return -1;  // Return -1 if you want ascending, 1 if you want descending order. 
    else if (x > y)
        return 1;   // Return 1 if you want ascending, -1 if you want descending order. 

    return 0;
}

/* Sort an array of n integers, pointed to by a. */
void sort_ints(int *a, int n) {
    qsort(a, n, sizeof *a, &compare_ints);
}
//int argc, char const *argv[]
int main()
{
    /* if(argc<=1) {
        printf("You did not feed me arguments\n");
        exit(1);
     }

    int len = argc-1;
    int *arr = (int *)malloc((len)*sizeof(int));
    int numComp = 0;
    
    for(int i = 1; i <= len; i++)
    {
        arr[i-1] = atoi(argv[i]);
    } 
    */
    int len = 10000;
    printf("Here");
    int *arr1 = randPermGen(len, 100000);
    printf("Here");

    
    struct node *arr2 = (struct node *)malloc(len*sizeof(struct node));
    int *arr3 = (int *)malloc(len*sizeof(int));
    
    for(int i=0; i<len; i++)
    {
        arr2[i].item = arr1[i];
        arr2[i].index = i;

        arr3[i] = arr1[i];
    }
    
    quick_sort(arr2, 0, len-1);
    sort_ints(arr3, len);

    for(int i=0; i<len; i++)
    {
        if(arr2[i].item != arr3[i])
        {
            printf("Fail");
            exit(1);
        }
    }

    printf("Success");
    


    //free(arr);

    return 0;
}
