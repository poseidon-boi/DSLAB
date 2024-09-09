#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Enter number of rows and columns: ");
    int rows, cols;
    scanf("%d %d", &rows, &cols);
    printf("Enter elements of first matrix:\n");
    int arr1[rows][cols], arr2[rows][cols], max[rows][cols];
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            scanf("%d", &arr1[i][j]);
    printf("Enter elements of second matrix:\n");
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) {
            scanf("%d", &arr2[i][j]);
            max[i][j] = (arr1[i][j] > arr2[i][j])? arr1[i][j] : arr2[i][j];
        }
    printf("Maximum matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%d ", max[i][j]);
        printf("\n");
    }
}