#include <stdio.h>
#include <stdlib.h>

struct node{
      int item;
      int index;
      
};

void swap (struct node* a, struct node* b)
{
    struct node temp = *a;
    *a = *b;
    *b = temp;
}

int main(int argc, char const *argv[])
{
    struct node a;
    struct node b;

    a.item = 5;
    a.index = 1;

    b.item = 7;
    b.index = 2;

    printf("a: %d %d \n b: %d %d\n", a.item, a.index, b.item, b.index);

    swap(&a,&b);

    printf("a: %d %d \n b: %d %d\n", a.item, a.index, b.item, b.index);
    
}

for(int i=0; i<indexU; i++)
    {
        if(arr2[i].item > arr2[indexU].item)
        {
            printf("Fail");
            exit(1);
        }
    }

    
    for(int i = indexU+1; i < indexV; i++)
    {
        if(arr2[i].item < arr2[indexU].item || arr2[i].item > arr2[indexV].item)
        {
            printf("Fail");
            exit(1);
        }
    }

    
    for(int i = indexV+1; i < len; i++)
    {
        if(arr2[i].item < arr2[indexV].item)
        {
            printf("Fail");
            exit(1);
        }
    }


struct node *arr = (struct node *)malloc(len*sizeof(struct node));
        int numComp = 0;
        
        for(int  i = 0; i < len; i++)
        {
            arr[i].item = arr1[i];
            arr[i].index = i;
        }

        quick_sort(arr, 0, 100, &numComp);
        sort_ints(arr1, 101);

        
        for(int i = 0; i < 100; i++)
        {
            if(arr1[i] != arr[i].item)
            {
                printf("Error\n");
                exit(1);
            }
        }
        printf("Sucess\n");


=============================

 // Partition along the median of Random Sample
        swap(&arr[0], &arr[indexU]);
        int tempIndex = partition(arr, 0, len-1, numComp);

        if(tempIndex == middleIndex)
            return arr[tempIndex].item;
        else if(tempIndex < middleIndex)
        {
            indexU = tempIndex;

            int medianGap = middleIndex - indexU;
            
        }
        else
            indexV = tempIndex;