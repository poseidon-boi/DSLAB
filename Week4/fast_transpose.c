#include <stdio.h>
#include <stdlib.h>

struct tuple {
    int row, col, val;
};

typedef struct tuple sparse;

void fast_transpose(sparse s[], sparse t[], int start[]) {
    t[0].val = s[0].val;
    t[0].row = s[0].col;
    t[0].col = s[0].row;
    for (int i = 1; i <= s[0].val; i++) {
        int col = s[i].col;
        t[start[col]].val = s[i].val;
        t[start[col]].col = s[i].row;
        t[start[col]++].row = s[i].col;
    }
}

void display(sparse s[]) {
    int size = s[0].val;
    for (int i=0; i<=size; i++)
        printf("<%d, %d, %d>\t", s[i].row, s[i].col, s[i].val);
    printf("\n");
}

int main() {
    int m, n;
    printf("Enter the dimensions: ");
    scanf("%d %d", &m, &n);
    int arr[m][n], nonzero = 0;
    printf("Enter the elements:\n");
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            scanf("%d", &arr[i][j]);
            if (arr[i][j] != 0)
                nonzero++;
        }
    if (nonzero == 0) {
        printf("No nonzero elements");
        return 0;
    }
    sparse a[nonzero+1], b[nonzero+1];
    int c = 1, freq[n], start[n];
    for (int i = 0; i < n; i++) {
        freq[i] = 0;
        start[i] = 0;
    }
    a[0].row = m;
    a[0].col = n;
    a[0].val = nonzero;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (arr[i][j] != 0) {
                a[c].row = i;
                a[c].col = j;
                a[c].val = arr[i][j];
                c++;
                freq[j]++;
            }
    start[0] = 1;
    for (int i = 1; i < n; i++)
        start[i] = start[i-1] + freq[i-1];
    printf("The tuple representation is:\n");
    display(a);
    fast_transpose(a, b, start);
    printf("After transposing:\n");
    display(b);
    return 0;
}
