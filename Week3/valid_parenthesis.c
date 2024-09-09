#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void removenewline(char str[]) {
    for (int i=0; str[i] != '\0'; i++)
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
}

int isValid(char* s) {
    int length = strlen(s);
    char stack[length];
    int top = -1;

    for (int i = 0; i < length; i++) {
        if (s[i] != '(' && s[i] != '[' && s[i] != '{' && s[i] != ')' && s[i] != ']' && s[i] != '}')
            continue;
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            stack[++top] = s[i];
        } else {
            if (top == -1) {
                return 0;
            }
            char opening = stack[top--];
            if ((s[i] == ')' && opening != '(') ||
                (s[i] == ']' && opening != '[') ||
                (s[i] == '}' && opening != '{')) {
                return 0;
            }
        }
    }

    return top == -1;
}

int main() {
    printf("Enter the expression: ");
    char exp[200];
    fgets(exp, 200, stdin);
    removenewline(exp);
    if (isValid(exp))
        printf("Valid");
    else
        printf("Invalid");
}