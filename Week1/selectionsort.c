#include <stdio.h>
int main()
{
    printf("Enter the size: ");
    int n;
    scanf("%d", &n);
    int arr[n], temp, max;
    printf("Enter the elements: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    for(int i = 0; i < n-1; i++)
    {
        max = n-i-1;
        for(int j = 0; j < n-i-1; j++)
        {
            if(arr[j] > arr[max])
                max = j;
        }
        if (max == n-i-1)
            continue;
        temp = arr[n-i-1];
        arr[n-i-1] = arr[max];
        arr[max] = temp;
    }
    printf("The sorted array is: ");
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
}
