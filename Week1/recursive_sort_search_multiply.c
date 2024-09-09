#include <stdio.h>
#include <stdlib.h>

/**
 * @param arr the array to search in
 * @param lo the lower limit to search
 * @param hi the upper limit to search
 * @param search the value to search for
 * @return returns the array index where the element is found, -1 if not found
 */
int binary_search(int arr[], int lo, int hi, int search) {
    if (lo > hi)
        return -1;
    int mid = lo + (hi - lo) / 2;
    if (arr[mid] == search)
        return mid;
    if (search < arr[mid])
        return binary_search(arr, lo, mid-1, search);
    // if (search > arr[mid])
    return binary_search(arr, mid+1, hi, search);
}

/**
 * @param arr the array to sort
 * @param lo the lower limit to sort from
 * @param hi the upper limit to sort until(included)
 */
void selection_sort(int arr[], int lo, int hi) {
    if (lo == hi)
        return;
    int max = arr[lo], max_pos = lo, temp;
    for (int i = lo+1; i <= hi; i++)
        if (arr[i] > max) {
            max = arr[i];
            max_pos = i;
        }
    arr[max_pos] = arr[hi];
    arr[hi] = max;
    selection_sort(arr, lo, hi-1);
}

/**
 * @return returns the product
 */
int multiply_recursive(int multiplicand, int multiplier) {
    if (multiplier == 0)
        return 0;
    return multiplicand + multiply_recursive(multiplicand, multiplier-1);
}

int main() {
    int num1, num2, size, search, position;
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);
    int product = multiply_recursive(num1, num2);
    printf("The product is %d\n", product);
    printf("Enter size of array: ");
    scanf("%d", &size);
    int arr[size];
    printf("Enter the elements: ");
    for (int i = 0; i < size; i++)
        scanf("%d", &arr[i]);
    selection_sort(arr, 0, size-1);
    printf("The sorted array is: ");
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\nEnter element to search: ");
    scanf("%d", &search);
    position = binary_search(arr, 0, size-1, search);
    if (position == -1)
        printf("Element not found");
    else
        printf("Found at position %d", (position+1));
    return 0;
}