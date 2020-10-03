#include<stdlib.h>
#include<stdio.h>
#include<stack>

using namespace std;


int min(int x, int y)
{ return (x<y)? x :y; }

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;


    int L[n1], R[n2];


    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];


    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }


    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }


    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int n)
{
   for (int arr_len=1; arr_len<=n-1; arr_len = 2*arr_len)
   {

       for (int left_start=0; left_start<n-1; left_start += 2*arr_len)
       {

           int mid = left_start + arr_len - 1;

           int right_end = min(left_start + 2*arr_len - 1, n-1);


           merge(arr, left_start, mid, right_end);
       }
   }
}

void printArr(int A[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}


void swap ( int* a, int* b )
{
    int t = *a;
    *a = *b;
    *b = t;
}


int partition (int arr[], int l, int r)
{
    int pivot = arr[r];
    int i = (l - 1);

    for (int j = l; j <= r- 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap (&arr[i], &arr[j]);
        }
    }
    swap (&arr[i + 1], &arr[r]);
    return (i + 1);
}


void quickSortIterative (int arr[], int l, int r)
{

    stack <int> aux_stack;


    aux_stack.push(l);
    aux_stack.push(r);


    while ( !aux_stack.empty() )
    {

        r = aux_stack.top();
        aux_stack.pop();
        l = aux_stack.top();
        aux_stack.pop();


        int p = partition( arr, l, r );


        if ( p-1 > l )
        {
            aux_stack.push(l);
            aux_stack.push(p - 1);
        }

        if ( p+1 < r )
        {
            aux_stack.push(p + 1);
            aux_stack.push(r);
        }
    }
}


int main()
{
    printf("Enter a Choice:\n1.Iterative Merge Sort\n2.Iterative Quick Sort\n");
    int choiceSort;
    scanf("%d",&choiceSort );
    int n;
    printf("Enter the size of array: ");
    scanf("%d",&n );
    int arr[n];
    printf("Enter the elements:\n");
    for (int k=0;k<n;k++)
    {
      scanf("%d",&arr[k] );
    }
    switch (choiceSort) {
      case 1:
      {
        mergeSort(arr, n);
      }
      case 2:
      {
          quickSortIterative( arr, 0, n - 1 );
      }
    }

    printArr( arr, n );
    return 0;
}
