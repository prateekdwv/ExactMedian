#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>

#define ll long long

// Constants. Change it on your own risk :)
    // Number of trails of experiment
    #define TRAILS 100
    // Size of array
    #define ARRSIZE 10000
    // Array Element Range
    // CATUION Keep this range more than or equal to ARRSIZE. 
    // Because random generation is without repetition
    #define ELERANGE 10000000
    // Size of Sample
    #define SAMPLESIZE(length) floor(pow((double)(length), 2.0/3.0))
    // Gap
    #define GAP(length) floor(pow((double)(length), 4.0/10.0))

// Structure having two fields item and its index in the given array.
struct node{
      ll item;
      ll index;
      
};

// Utility code to generate a uniform interger in given range
ll uRand(ll rangeLow, ll rangeHigh) {
    long double myRand = rand()/(1.0 + RAND_MAX); 
    ll range = rangeHigh - rangeLow + 1;
    ll myRand_scaled = (myRand * range) + rangeLow;
    return myRand_scaled;
}

// Utility function to add dealy
void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}

// Utility function to swao two numbers
void swap(struct node *i, struct node *j){
    struct node temp = *i;
    *i = *j;
    *j = temp;
}

ll * randPermGenRep(ll length, ll elemRange){
    // Allocating memory
	ll *perm = (ll *) malloc(length*sizeof(ll));
	
	srand((unsigned int)time(NULL));

    ll i=0;
    while(i < length)
	{
		// To enhance randomness
        ll randNum = uRand(0, elemRange-1);
        
        perm[i] = randNum;
     
        i++;        
    }

	return perm;
}

// Utility function to generate a random permutation of given length
// where each element will be in the range [0,elemRange-1] and NO REPETITION
ll * randPermGen(ll length, ll elemRange){
    // Allocating memory
	ll *perm = (ll *) malloc(length*sizeof(ll));
	
	srand((unsigned int)time(NULL));

    ll i=0;
    while(i < length)
	{
		// To enhance randomness
        ll randNum = uRand(0, elemRange-1);
        
        // Check for no repeatition
        int flag = 0;
        for(ll k=0; k<i; k++)
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

/* Comparison function. Receives two generic (void) pointers to the items under comparison. */
int compare_ints(const void *p, const void *q) {
    ll x = *(const int *)p;
    ll y = *(const int *)q;

    /* Avoid return x - y, which can cause undefined behaviour
       because of signed integer overflow. */
    if (x < y)
        return -1;  // Return -1 if you want ascending, 1 if you want descending order. 
    else if (x > y)
        return 1;   // Return 1 if you want ascending, -1 if you want descending order. 

    return 0;
}

/* Sort an array of n integers, pointed to by a. */
void sort_ints(ll *a, ll n) {
    qsort(a, n, sizeof *a, &compare_ints);
}

// Implimenation of Insertion Sort, to be used with QS
// When the array size goes down certain threshold
void insertionSort(struct node arr[], ll l, ll r, ll *numComp) { 
   ll i, j; 
   struct node key;
   for (i = l+1; i <= r; i++) 
   { 
       key = arr[i]; 
       j = i; 
  
       /* Move elements of arr[0..i-1], that are 
          greater than key, to one position ahead 
          of their current position */
       while (j > l && arr[j-1].item > key.item) 
       { 
           arr[j] = arr[j-1]; 
           j = j-1;

           (*numComp)++;
       }
       (*numComp)++;

       arr[j] = key; 
   } 
} 

//partition procedure that will partition array around its first element.
 ll partition(struct node a[], ll l, ll r, ll *numComp){
    ll piv = a[l].item;

    ll i = l;
    ll j = r+1;
    struct node temp;

    while(1)
    {
        do
        {
            i = i + 1;

            // Counting comparisions    
            (*numComp)++;
        } while (i < r && a[i].item < piv);
        
        
        do
        {
            j = j - 1;

            // Counting comparisions    
            (*numComp)++;
        } while (j > -1 && a[j].item > piv);
        
        // This comparison do not counts
        // In analysis we consider comparison between two elemtnts
        // This is index comparions
        if(i>=j)
        {
            return j;
        }

        swap(&a[j], &a[i]);

        if(i+1 == j)
        {
            return i;
        }

        //i++;
        //j--;        
    }
}

//Quick sort procedure
void quick_select(struct node a[], int k, ll l, ll r, ll *numComp){
    struct node temp;
    if(l<r)
    {   
        /*
        // Randomized QuickSort
        int pivot = rand()%(r-l);
        temp = a[l + pivot];
        a[l + pivot] = a[l];
        a[l] = temp;
        */
        
        /* if ((l-r+1) < 10) {
            return;
        } */

        // Use insertion sort if the size of array goes below threshold        
        if((r-l+1) < 10)
        {
            insertionSort(a,l,r, numComp);

            return;
        }

        // Pivot is median of (first, middle, last) element
        int mid = (l + r)/ 2;
        
        if (a[mid].item < a[l].item) {
            swap(&a[mid], &a[l]);
        }

        if(a[r].item < a[l].item) {
            swap(&a[r], &a[l]);
        }

        if(a[mid].item < a[r].item) {
            swap(&a[mid], &a[r]);
        }
        
        swap(&a[r], &a[l]);

        ll pos = partition(a, l, r, numComp);
        
        // Removing two extra comparisons
        *numComp -= 2;

        // Swapping the 'pivot element node' with the element at its final position.
        swap(&a[pos], &a[l]);

        if(k == pos)
            return;
        else if(k < pos)
            quick_select(a, k, l, pos-1, numComp);
        else
            quick_select(a, k, pos+1, r, numComp);
    }
}


//Quick sort procedure
void quick_sort(struct node a[], ll l, ll r, ll *numComp){
    struct node temp;
    if(l<r)
    {   
        /*
        // Randomized QuickSort
        int pivot = rand()%(r-l);
        temp = a[l + pivot];
        a[l + pivot] = a[l];
        a[l] = temp;
        */
        
        /* if ((l-r+1) < 10) {
            return;
        } */

        // Use insertion sort if the size of array goes below threshold        
        if((r-l+1) < 10)
        {
            insertionSort(a,l,r, numComp);

            return;
        }

        // Pivot is median of (first, middle, last) element
        int mid = (l + r)/ 2;
        
        if (a[mid].item < a[l].item) {
            swap(&a[mid], &a[l]);
        }

        if(a[r].item < a[l].item) {
            swap(&a[r], &a[l]);
        }

        if(a[mid].item < a[r].item) {
            swap(&a[mid], &a[r]);
        }
        
        swap(&a[r], &a[l]);

        ll k = partition(a,l,r, numComp);
        
        // Removing two extra comparisons
        *numComp -= 2;

        // Swapping the 'pivot element node' with the element at its final position.
        swap(&a[k], &a[l]);

        // Recursive calls
        quick_sort(a,l,k-1, numComp);
        quick_sort(a,k+1,r, numComp);
    }
}

// Function that partition the array around two elements u and v
void multiPartition(struct node arr[], ll len, ll *e, ll *u, ll *v, ll *numComp){
    ll middleIndex = len/2;
    ll indexU = 0;
    ll indexV = len-1;

    // Bring the v ahead in array, to avoid messing up with other elements
        swap(&arr[0], &arr[*v]);
            if(*u == 0)
                *u = *v;
            else if(*e == 0)
                *e = *v;

        // Bring u ahead so that we can all partition
        swap(&arr[1], &arr[*u]);
            if(*e == 1)
                *e = *u;
        
        // Bring u ahead so that we can all partition
        swap(&arr[2], &arr[*e]);

        ll tempIndex = partition(arr, 2, len-1, numComp);

        // Removing two extra comparisons
        *numComp -= 2;

        // Take v to the second half of the partition
        swap(&arr[0], &arr[tempIndex]);

        // Take e to its place
        swap(&arr[2], &arr[tempIndex-1]);
            // Fix index of e
            tempIndex = tempIndex - 1;

        // Take u to first place
        swap(&arr[0], &arr[1]);

        if(tempIndex == middleIndex)
        {
            *u = tempIndex;
            *v = tempIndex;

            return ;
        }
        else if(tempIndex < middleIndex)
        {
            // e will become u
            indexU = tempIndex;

            // Partition around v
            indexV = partition(arr, tempIndex+1, len-1, numComp);

            // Removing two extra comparisons
            *numComp -= 2;

            // Take v to its position
            swap(&arr[tempIndex+1], &arr[indexV]);

            //printf("IndexU/E: %lld IndexV: %lld\n", indexU, indexV);

        }
        else if (tempIndex > middleIndex)
        {
            // e will become v
            indexV = tempIndex;

            // Partition around u
            indexU = partition(arr, 0, tempIndex-1, numComp);

            // Removing two extra comparisons
            *numComp -= 2;

            // Take v to its position
            swap(&arr[0], &arr[indexU]);

            //printf("IndexU: %lld IndexV/E: %lld\n", indexU, indexV);
        }

        *u = indexU;
        *v = indexV;
}

// Function that modifies the input array with median at (len/2)th index
// in 1.5n+o(n) comparision on expectation
ll exactMedian(ll *inArray, ll len, ll *numComp, ll *maxComp, ll *minComp){
    ll indexU = len-1;
    ll indexV = 0;
    ll indexE = 0;
    ll middleIndex = len/2;
    ll sampleSize = 0;
    ll sampleMiddleIndex = 0;

    ll *randSampleIndex;
    struct node *arr;
    struct node *randomSampleArray;

    // Create a array of structure to work on. This is for the sake of reusability of code
    arr = (struct node *)malloc(len*sizeof(struct node));
    
    for(ll  i = 0; i < len; i++)
    {
        arr[i].item = inArray[i];
        arr[i].index = i;
    }
    
    // Random Sample S
        sampleSize = SAMPLESIZE(len);
        //sampleSize = floor(10*log2f(len));
        
        // Generate random permutation of indice
        randSampleIndex = randPermGen(sampleSize, len);

        // Random sample, with its index in original array
        randomSampleArray = (struct node *)malloc(sampleSize*sizeof(struct node));

        for(ll i=0; i<sampleSize; i++)
        {
            randomSampleArray[i].item = arr[randSampleIndex[i]].item;
            randomSampleArray[i].index = randSampleIndex[i];
        }

        sampleMiddleIndex = sampleSize / 2;
        ll smallOrder = GAP(len);

        ll rankU = sampleMiddleIndex - smallOrder;
        ll rankV = sampleMiddleIndex + smallOrder;

    // Sort random sample
        //quick_sort(randomSampleArray, 0, sampleSize-1, numComp);
        quick_select(randomSampleArray, sampleMiddleIndex,0,sampleSize-1,numComp);
        quick_select(randomSampleArray, rankU,0,sampleMiddleIndex-1,numComp);
        quick_select(randomSampleArray, rankV,sampleMiddleIndex+1,sampleSize-1,numComp);
            //insertionSort(randomSampleArray, 0, sampleSize-1, numComp);

    // Pick two elements u and v from random sample and middle element e

        // Insure indices don't cross their line
        if(rankU >= 0 )
            indexU = randomSampleArray[rankU].index;
        else
            indexU = randomSampleArray[0].index;

        if(rankV < sampleSize)
            indexV = randomSampleArray[rankV].index;
        else
            indexV = randomSampleArray[sampleSize-1].index;

        indexE = randomSampleArray[sampleMiddleIndex].index;


    // Multipartition across e and (u or v)
        multiPartition(arr, len, &indexE, &indexU, &indexV, numComp);

        if(indexU == middleIndex || indexV == middleIndex)
        {
            //printf("IndexU: %lld IndexV: %lld    k: %lld l: %lld\n", indexU, indexV, sampleSize, indexV-indexU-1);
            // Found it !!
            return arr[middleIndex].item;
        }
            
    //printf("IndexU: %lld IndexV: %lld    k: %lld l: %lld\n", indexU, indexV, sampleSize, indexV-indexU-1);
    
    // Sort Elements between u and v
        //quick_sort(arr, indexU+1, indexV-1, numComp);
        quick_select(arr, middleIndex, indexU+1, indexV-1, numComp);
    
    // Found it!!
    ll median = arr[middleIndex].item;

    // Update Comparison
    if(*maxComp < *numComp)
    {
        *maxComp = *numComp;
    }
    if(*minComp > *numComp)
    {
        *minComp = *numComp;
    }

    // Free Memory
    free(arr);
    free(randomSampleArray);

    return median;
}

//int argc, char const *argv[]
int main(){   
    int accuracy = 0;
    ll expComp = 0;
    ll maxComp = 0;
    ll minComp = 5*ARRSIZE;
    ll len;
    int trail = TRAILS;

    for(size_t i=1; i<=trail; i++)
    {
        //printf("%lud", i);
        len = ARRSIZE;

        // Keep the range of element sufficiently large from len
        // Code breaks for weird reason when it is less
        ll *arr1 = randPermGenRep(len, ELERANGE);
        //int arr1[] = {10,9,8,7,6,5,4,3,2,1,0};

        
        ll numComp = 0;
        
        ll *arr2 = (ll *)malloc(len*sizeof(ll));
        ll *arr3 = (ll *)malloc(len*sizeof(ll));
        
        for(ll i=0; i<len; i++)
        {
            arr2[i] = arr1[i];

            arr3[i] = arr1[i];
        }
        
        ll median = exactMedian(arr2, len, &numComp, &maxComp, &minComp);

        sort_ints(arr3, len);    

        ll middleIndex = len/2;

        //printf("%lld is supposed to be %lld    Comparision: %lld\n", median, arr3[middleIndex], numComp);

        if(median == arr3[middleIndex])
        {
            accuracy++;   
        }

        expComp += numComp;
        
        //free(arr1);
        free(arr2);
        free(arr3);
       
        //waitFor(1.5);
        
        for(size_t i = 0; i < 10000000; i++);
        

    }

    printf("Accuracy: %d    Avg: %f    Min: %f    Max: %f\n", accuracy, ((float)expComp/trail)/len, ((float)minComp)/len, ((float)maxComp)/len);

    return 0;
}