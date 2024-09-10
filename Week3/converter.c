#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char pop(char stk[], int *top) {
    if (*top == -1)
        return '\0';
    return stk[(*top)--];
}

 void push(char stk[], int size, int *top, char data) {
    if (*top == size-1) {
        printf("Stack overflow");
        return;
    }
    stk[++*top] = data;
}

void converter(int num, char conv[], int *top, int base) {
    while (num > 0) {
        char digit = num%base;
        if(digit == 10)
            digit = 'A';
        if(digit == 11)
            digit = 'B';
        if(digit == 12)
            digit = 'C';
        if(digit == 13)
            digit = 'D';
        if(digit == 14)
            digit = 'E';
        if(digit == 15)
            digit = 'F';
        push(conv, 64, top, digit);
        num /= base;
    }
}

void display(char conv[], int *top) {
    while(*top > -1) {
        char digit = pop(conv, top);
        if(digit < 10)
            printf("%d", digit);
        else
            printf("%c", digit);
    }
}

int main() {
    char conv[64];
    int num, base, top = -1;
    printf("Enter number and base: ");
    scanf("%d %d", &num, &base);
    converter(num, conv, &top, base);
    printf("The converted number is: ");
    display(conv, &top);
    return 0;
}

