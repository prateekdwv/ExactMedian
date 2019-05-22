#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>

//Structure having two fields item and its index in the given array.
struct node{
      long long int item;
      long long int index;
      
};

//partition procedure that will partition array around its first element.
long long int partition(struct node a[],long long int l,long long int r)
{
long long int piv=a[l].item,i=l+1,j=r;
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
void quick_sort(struct node a[],long long int l,long long int r)
{
    if(l>r)
    return;
    long long int k=partition(a,l,r);
    quick_sort(a,l,k-1);
    quick_sort(a,k+1,r);
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

//Main procedure
int main()
{
    /* long long int i,n;
    printf("No of elements in the list : ");
    scanf("%lld", &n);
    int *a = (int *)malloc(n*sizeof(int));
    struct node *arr = (struct node *)malloc(n*sizeof(struct node));
    printf("Enter elements of the list: ");
    for(i=0;i<n;i++)
        scanf("%lld", &a[i]); */

    int per = 0;
    for(int j = 1; j <= 100; j++)
    {
            
        int n = 11;
        int p[] = {5,4,2,5,8,3,1,9,0,6,5};
        struct node *arr = (struct node *)malloc(n*sizeof(struct node));
        int *a = (int *)malloc(n*sizeof(int));


        for(int i=0;i<n;i++){
            arr[i].item=p[i];
            arr[i].index=i;

            a[i] = p[i];

        }
        //quick_sort(arr,0,n-1);
        long long int index= partition(arr,0, 7);

        printf("Index: %lld \n Partitioned list is as: ", index);
        for(int i=0;i<n;i++){
            printf("%lld ",arr[i].item);
        }
        printf("\n");
        /*
        for(i=0;i<n;i++){
            printf("%lld ",arr[i].index);
        }
        printf("\n\n"); */

        sort_ints(a, n);

        int flag = 1;
        
        for(int i = 0; i < n; i++)
        {
            if(arr[i].item != a[i] || p[arr[i].index] != arr[i].item)
            {
                flag = 0;
                break;
            }
        }
        per += flag;
        printf("j = %d    Result: %d\n",j, flag);
    }

    printf("%d\n",per);
    return 0;
}

