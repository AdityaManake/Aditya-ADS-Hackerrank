#include<stdio.h>
int main()
{
    int n, i, k, l ,m,h;
    printf("Enter the number of array elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter array elements in sorted order:\n");
    for (i = 0; i < n; i++)
    {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
    printf("Enter the element to be searched: ");
    scanf("%d", &k);
    l=0;
    h=n-1;
    while(l<=h)
    {
        m=(l+h)/2;
        if(arr[m]==k)
        {
            printf("Element %d found at index %d\n",k,m);
            return 0;
        }
        else if(arr[m]<k)
        {
            l=m+1;
        }
        else
        {
            h=m-1;
        }
    }
    if(l>h)
    {
        printf("Element %d not found\n",k);
    }
    
    return 0;
}