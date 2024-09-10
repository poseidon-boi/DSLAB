#include <stdio.h>
int main()
{
    printf("Enter the size: ");
    int n;
    scanf("%d", &n);
    int arr[n], search, found = 0;
    printf("Enter the elements: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    printf("Enter element to search: ");
    scanf("%d", &search);
    for(int i = 0; i < n; i++)
    {
        if(arr[i] == search)
        {
            printf("Found at index %d\n", i);
            found = 1;
        }
    }
    if(found == 0)
        printf("Element not found");
}
