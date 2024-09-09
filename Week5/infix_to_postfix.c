#include <stdio.h>
#include <stdlib.h>

void removenewline(char str[]) {
    for (int i=0; str[i] != '\0'; i++)
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
}

int input_prec(char symbol) {
    switch(symbol) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 3;
        case '^': return 6;
        case '(': return 9;
        case ')': return 0;
        default: return 7;
    }
}

int stack_prec(char symbol) {
    switch(symbol) {
        case '+':
        case '-': return 2;
        case '*':
        case '/': return 4;
        case '^': return 5;
        case '(': return 0;
        case '#': return -1;
        default: return 8;
    }
}

int convert(char* infix, char* postfix) {
    char stk[300];
    int top = -1, j = 0;
    stk[++top] = '#';
    for (int i = 0; infix[i] != '\0'; i++) {
        char symbol = infix[i];
        while (stack_prec(stk[top]) > input_prec(symbol))
            postfix[j++] = stk[top--];
        if (stack_prec(stk[top]) != input_prec(symbol))
            stk[++top] = symbol;
        else
            top--;
    }
    postfix[j] = '\0';
    if (stk[top] != '#') {
        printf("Invalid expression");
        return 1;
    }
    return 0;
}

int main() {
    printf("Enter the expression: ");
    char infix[300], postfix[300];
    int error;
    fgets(infix, 300, stdin);
    removenewline(infix);
    error = convert(infix, postfix);
    if (error)
        return 1;
    printf("The postfix expression is: %s", postfix);
    return 0;
}