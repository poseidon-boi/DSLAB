#include <stdio.h>
#include <stdlib.h>

/** Deallocates memory for the matrix
 * @param arr The matrix to deallocate
 * @param rows The number of rows in the matrix
 */
void deallocate(int** arr, int rows) {
    for (int i = 0; i < rows; i++)
        free(arr[i]);
    free(arr);
}

/** Inputs values for the matrix
 * @param arr The matrix to store the elements in
 * @param rows Number of rows in the matrix
 * @param cols Number of columns in the matrix
 */
void get_elements(int** arr, int rows, int cols) {
    printf("Getting elements...\n");
    if (rows == 1) {
        for (int i = 0; i < cols; i++)
            scanf("%d", &arr[i]);
        return;
    }
    if (cols == 1) {
        for (int i = 0; i < rows; i++)
            scanf("%d", &arr[i]);
        return;
    }
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            scanf("%d", &arr[i][j]);
}

/** Displays the matrix
 * @param arr The matrix to display
 * @param rows Number of rows in the matrix
 * @param cols Number of columns in the matrix
 */
void display(int** arr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
}

/** Adds two matrices
 * @param arr1 First matrix
 * @param arr2 Second matrix
 * @param result Output matrix, memory is allocated in the function itself
 * @param rows Number of rows in each matrix
 * @param cols Number of columns in each matrix
 */
void add_matrices(int** arr1, int** arr2, int** result, int rows, int cols) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result[i][j] = arr1[i][j] + arr2[i][j];
}

/** Multiplies two matrices (checks for incompatible matrices as well)
 * @param arr1 First matrix
 * @param rows1 Number of rows in first matrix
 * @param cols1 Number of columns in first matrix
 * @param arr2 Second matrix
 * @param rows2 Number of rows in second matrix
 * @param cols2 Number of columns in second matrix
 * @param result Product of input matrices, memory is allocated in the function itself
 * @return returns -1 if invalid sizes of matrices, 0 if successfully multiplied
 */
int multiply_matrices(int** arr1, int rows1, int cols1, int** arr2, int rows2, int cols2, int** result) {
    if (cols1 != rows2)
        return -1;
    for (int i = 0; i < rows1; i++)
        for (int j = 0; j < cols2; j++) {
            int sum = 0;
            for (int k = 0; k < cols1; k++)
                sum += arr1[i][k] * arr2[k][j];
            result[i][j] = sum;
        }
    return 0;
}

/** Checks whether the entered matrix is a magic square
 * @param matrix The matrix to check
 * @param rows Number of rows in the matrix
 * @param cols Number of columns in the matrix
 * @return returns 0 if not a magic square, 1 if magic square
 */
int isMagic(int** matrix, int rows, int cols) {
    if (rows != cols)
        return 0;
    int rowsum[rows], colsum[rows], diagsum = 0, nondiagsum = 0;
    for (int i = 0; i < rows; i++) {
        rowsum[i] = 0;
        colsum[i] = 0;
        diagsum += matrix[i][i];
        nondiagsum += matrix[i][rows-i-1];
        for (int j = 0; j < rows; j++) {
            rowsum[i] += matrix[i][j];
            colsum[i] += matrix[j][i];
        }
    }
    if (diagsum != nondiagsum)
        return 0;
    for (int i = 0; i < rows; i++)
        if (rowsum[i] != diagsum || colsum[i] != diagsum)
            return 0;
    return 1;
}

int main() {
    printf("Enter choice(1. Add, 2. Multiply, 3. Check for Magic Square, 4. Exit): ");
    while (1) {
        int ch, **matrix1, **matrix2, **result;;
        scanf("%d", &ch);
        switch(ch) {
            case 1:
                int rows, cols;
                printf("Enter the dimensions of the matrix: ");
                scanf("%d %d", &rows, &cols);
                matrix1 = malloc(rows * sizeof *matrix1);
                matrix2 = malloc(rows * sizeof *matrix2);
                result = malloc(rows * sizeof *result);
                for (int i = 0; i < rows; i++) {
                    matrix1[i] = malloc(cols * sizeof *matrix1[i]);
                    matrix2[i] = malloc(cols * sizeof *matrix2[i]);
                    result[i] = malloc(cols * sizeof *result[i]);
                }
                printf("Enter elements of matrix 1:\n");
                get_elements(matrix1, rows, cols);
                printf("Enter elements of matrix 2:\n");
                get_elements(matrix2, rows, cols);
                add_matrices(matrix1, matrix2, result, rows, cols);
                printf("The sum matrix is:\n");
                display(result, rows, cols);
                deallocate(matrix1, rows);
                deallocate(matrix2, rows);
                deallocate(result, rows);
                break;
            case 2:
                int rows1, cols1, rows2, cols2;
                printf("Enter the dimensions of matrix 1: ");
                scanf("%d %d", &rows1, &cols1);
                printf("Enter the dimensions of matrix 2: ");
                scanf("%d %d", &rows2, &cols2);
                if (cols1 != rows2) {
                    printf("Cannot be multipled\n");
                    break;
                }
                matrix1 = malloc(rows1 * sizeof *matrix1);
                matrix2 = malloc(rows2 * sizeof *matrix2);
                result = malloc(rows1 * sizeof *result);
                for (int i = 0; i < rows; i++) {
                    matrix1[i] = malloc(cols1 * sizeof *matrix1[i]);
                    matrix2[i] = malloc(cols2 * sizeof *matrix2[i]);
                    result[i] = malloc(cols2 * sizeof *result[i]);
                }
                printf("Enter elements of matrix 1:\n");
                get_elements(matrix1, rows1, cols1);
                printf("Enter elements of matrix 2:\n");
                get_elements(matrix2, rows2, cols2);
                multiply_matrices(matrix1, rows1, cols1, matrix2, rows2, cols2, result);
                printf("The product matrix is:\n");
                display(result, rows1, cols2);
                deallocate(matrix1, rows1);
                deallocate(matrix2, rows2);
                deallocate(result, rows1);
                break;
            case 3:
                int size;
                printf("Enter length of square matrix: ");
                scanf("%d", &size);
                matrix1 = malloc(size * sizeof *matrix1);
                for (int i = 0; i < rows; i++)
                    matrix1[i] = malloc(size * sizeof *matrix1[i]);
                printf("Enter elements:\n");
                get_elements(matrix1, size, size);
                if (isMagic(matrix1, size, size))
                    printf("Magic square\n");
                else
                    printf("Not a magic square\n");
                deallocate(matrix1, size);
                break;
            case 4:
                printf("Thank you!");
                return 0;
            default:
                printf("Invalid choice, aborting");
                return 1;
        }
        printf("Enter choice: ");
    }
}