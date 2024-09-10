#include <stdio.h>
int main()
{
    printf("Enter the size: ");
    int n;
    scanf("%d", &n);
    int arr[n], search, first = 0, last = n-1, found = 0;
    printf("Enter the ascending elements: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    printf("Enter element to search: ");
    scanf("%d", &search);
    while(first <= last)
    {
        int mid = (first+last)/2;
        if(arr[mid] == search)
        {
            printf("Found at index %d\n", mid);
            found = 1;
            break;
        }
        else if(search < arr[mid])
            last = mid-1;
        else
            first = mid+1;
    }
    if (found == 0)
        printf("Element not found");
}
