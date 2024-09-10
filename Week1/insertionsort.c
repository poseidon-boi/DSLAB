#include <stdio.h>
int main()
{
    printf("Enter the size: ");
    int n;
    scanf("%d", &n);
    int arr[n], temp;
    printf("Enter the elements: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    for(int i = 1; i < n; i++)
    {
        for(int j = i; j > 0; j--)
        {
            if(arr[j] < arr[j-1])
            {
                temp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = temp;
            }
        }
    }
    printf("The sorted array is: ");
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
}
