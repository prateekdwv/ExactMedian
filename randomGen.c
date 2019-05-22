#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>

int uRand(int rangeLow, int rangeHigh) {
    double myRand = rand()/(1.0 + RAND_MAX); 
    int range = rangeHigh - rangeLow + 1;
    int myRand_scaled = (myRand * range) + rangeLow;
    return myRand_scaled;
}

void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
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
        int randNum = uRand(1, elemRange-1);
        
        // Check for no repetition
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

int main(int argc, char const *argv[])
{
    int len = 50000;
    int *arr = randPermGen(len, 1000000);

    
    for(int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
