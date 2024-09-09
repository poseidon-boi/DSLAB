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
    switch(symbol)
    {
        case '+':
        case '-': return 1; break;
        case '*':
        case '/': return 3; break;
        case '^': return 6; break;
        case '(': return 9; break;
        case ')': return 0; break;
        default: return 7;
    }
}

int stack_prec(char symbol) {
    switch(symbol)
    {
        case '+':
        case '-': return 2; break;
        case '*':
        case '/': return 4; break;
        case '^': return 5; break;
        case '(': return 0; break;
        case '#': return -1; break;
        default: return 8;
    }
}

int convert(char* infix, char* postfix) {
    char* stk = malloc(sizeof(infix));
    int top = -1, j = 0;
    stk[++top] = '#';
    for (int i = 0; infix[i] != '\0'; i++) {
        char symbol = infix[i];
        while (stack_prec(stk[top]) > input_prec(symbol))
            postfix[j++] = stk[top--];
        if (stack_prec(stk[top])!=input_prec(symbol))
            stk[++top] = symbol;
        else
            top--;
    }
    postfix[j] = '\0';
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
    printf("The postfix expression is:\n%s", postfix);
    return 0;
}