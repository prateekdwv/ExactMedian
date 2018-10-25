#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>

// Structure having two fields item and its index in the given array.
struct node{
      int item;
      int index;
      
};

void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}

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
 int partition(struct node a[], int l, int r, int *numComp){
    int piv = a[l].item;

    int i = l;
    int j = r+1;
    struct node temp;

    while(1)
    {
        do
        {
            i = i + 1;

            if(i > r)
                return i-1;

            // Counting comparisions    
            (*numComp)++;
        } while (a[i].item < piv);
        
        
        do
        {
            j = j -1;

            if(j < 0)
                return j+1;

            // Counting comparisions    
            (*numComp)++;
        } while (a[j].item > piv);
        
        // This comparison do not counts
        // In analysis we consider comparison between two elemtnts
        // This is index comparions
        if(i>=j)
        {
            return j;
        }
    
        temp = a[j];
        a[j] = a[i];
        a[i] = temp;

        if(i+1 == j)
        {
            return i;
        }

        //i++;
        //j--;        
    }

    return i-1;
}


//Quick sort procedure
void quick_sort(struct node a[], int l, int r, int *numComp)
{
    struct node temp;
    if(l<r)
    {   int pivot = rand()%(r-l+1);
        temp = a[pivot];
        a[pivot] = a[0];
        a[0] = temp;

        int k=partition(a,l,r, numComp);

        //swapping the 'pivot element node' with the element at its final position.
        temp = a[k];
        a[k] = a[l];
        a[l] = temp;

        quick_sort(a,l,k, numComp);
        quick_sort(a,k+1,r, numComp);
    }
}

// Function that partition the array around two elements u and v
void multiPartition(struct node arr[], int len, int *u, int *v, int *numComp)
{
    // Bring the v ahead in array, to avoid messing up with other elements
    swap(&arr[0], &arr[*v]);

    // Bring u ahead so that we can all partition
    swap(&arr[1], &arr[*u]);
    
    // Partition the array excluding the first element which has v
    //int indexU = mPartition(&arr[1],len-1, numComp) + 1;
    int indexU = partition(arr, 1, len-1, numComp);

    // Take v to the second half of the partition
    swap(&arr[0], &arr[indexU]);

    // Take u to its place
    swap(&arr[1], &arr[indexU-1]);

    // Partition the remaining array
    //int indexV = mPartition(&arr[indexU], len-indexU, numComp) + indexU;
    int indexV = partition(arr, indexU, len-1, numComp);

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

    int indexU = len-1;
    int indexV = 0;
    int middleIndex = len/2;
    int sampleSize = 0;

    int *randSampleIndex;
    struct node *arr;
    struct node *randomSampleArray;

    //do
    //{
        // Create a array of structure to work on. This is for the sake of reusability of code
        arr = (struct node *)malloc(len*sizeof(struct node));
        
        for(int  i = 0; i < len; i++)
        {
            arr[i].item = inArray[i];
            arr[i].index = i;
        }
        
        // Random Sample S
            sampleSize = floor(pow((double)len, 3.0/4.0));

            // Generate random permutation of indice
            randSampleIndex = randPermGen(sampleSize, len);

            // Random sample, with its index in original array
            randomSampleArray = (struct node *)malloc(sampleSize*sizeof(struct node));

            for(int i=0; i<sampleSize; i++)
            {
                randomSampleArray[i].item = arr[randSampleIndex[i]].item;
                randomSampleArray[i].index = randSampleIndex[i];
            }

        // Sort random sample
            quick_sort(randomSampleArray, 0, sampleSize-1, numComp);

        // Pick two elements u and v from random sample
            int rank = (sampleSize/2);
            int smallOrder = (pow(len,1.0/4.0));

            int rankU = rank - smallOrder;
            int rankV = rank + smallOrder;


            // Insure indices don't cross their line
            if(rankU >= 0 )
                indexU = randomSampleArray[rankU].index;
            else
                indexU = 0;

            if(rankV < sampleSize)
                indexV = randomSampleArray[rankV].index;
            else
                indexV = 0;


        // Multipartition across u and v
            multiPartition(arr, len, &indexU, &indexV, numComp);
            
    //}while(indexU >= middleIndex || indexV <= middleIndex);

    // Sort Elements between u and v
        quick_sort(arr, indexU+1, indexV-1, numComp);

    printf("IndexU: %d IndexV: %d\n", indexU, indexV);
    
    // Median is at index n/2
    int medianIndex = len/2;
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

    int per = 0;

    for(size_t i=1; i<100; i++)
    {
        int len = 101;

        // Keep the range of element sufficiently large from len
        // Code breaks for weird reason when it is less
        int *arr1 = randPermGen(len, 10000);
        //int arr1[] = {10,9,8,7,6,5,4,3,2,1,0};
        
        int numComp = 0;
        
        int *arr2 = (int *)malloc(len*sizeof(int));
        int *arr3 = (int *)malloc(len*sizeof(int));
        
        for(int i=0; i<len; i++)
        {
            arr2[i] = arr1[i];

            arr3[i] = arr1[i];
        }
        
        int median = exactMedian(arr2, len, &numComp);

        sort_ints(arr3, len);    

        int medianIndex = len/2;
        printf("%d is supposed to be %d    Comparision: %d\n", median, arr3[medianIndex], numComp);

        if(median == arr3[medianIndex])
        {
            per++;
        }
        
        //free(arr1);
        free(arr2);
        free(arr3);

        waitFor(1);
    }

    printf("%d\n", per);

    return 0;
}
