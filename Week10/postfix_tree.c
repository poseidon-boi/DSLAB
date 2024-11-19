#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

/** Creates an expression tree from a postfix expression (Max size: 999)
 * @param postfix The string containing the postfix expression
 * @return NULL if the expression is invalid, root node of the expression tree
 *         otherwise
 */
node* create_expression_tree(char* postfix);

/** Evaluates the given expression tree
 * @param error Stores the error value. Set to 1 if the expression tree is
 *              invalid or evaluation fails for reasons such as division by 0.
 *              Set to 0 if successfully evaluated.
 * @param root The root node of the expression tree
 * @return The evaluated result
 */
int evaluate_expression_tree(node* root, int* error);

/** Pushes newnode onto the stack and updates top
 * @return 0 if successfully pushed, 1 if failed because of stack overflow
 */
int push(node** stack, node* newnode, int* top);

/** Pops a node from the stack and updates top
 * @return The popped node, NULL if the stack is empty
 */
node* pop(node** stack, int* top);

/** Prints the tree horizontally using character values */
void print_tree_char(node* root, int curdepth);

/** Removes the newline character from the end of the fgets string */
void removenewline(char* str);

int main() {
    printf("Enter postfix expression: ");
    char postfix[1000];
    if (!fgets(postfix, 1000, stdin)) {
        fprintf(stderr, "Failed to read expression\n");
        return EXIT_FAILURE;
    }
    node* expression_tree = create_expression_tree(postfix);
    if (!expression_tree) {
        // fprintf(stderr, "Failed to create expression tree\n");
        return EXIT_FAILURE;
    }
    print_tree_char(expression_tree, 0);
    int result = 0, error = 0;
    result = evaluate_expression_tree(expression_tree, &error);
    if (error) {
        fprintf(stderr, "Error evaluating expression\n");
        return EXIT_FAILURE;
    }
    printf("Result is %d\n", result);
    return EXIT_SUCCESS;
}

int push(node** stack, node* newnode, int *top) {
    if (*top >= 999)
        return 1;
    stack[++*top] = newnode;
    return 0;
}

node* pop(node** stack, int* top) {
    if (*top == -1)
        return NULL;
    return stack[(*top)--];
}

node* create_expression_tree(char* postfix) {
    if (!postfix)
        return NULL;
    int len;
    for (len = 0; postfix[len] != '\0' && len < 1000; len++);
    if (!len || len == 1000) {
        fprintf(stderr, "Invalid length of expression\n");
        return NULL;
    }
    node** stack = malloc(sizeof(*stack) * 1000);
    int top = -1;
    for (int i = 0; i < len; i++) {
        if (postfix[i] >= '0' && postfix[i] <= '9') {
            node* temp = malloc(sizeof(*temp));
            temp -> data = postfix[i];
            temp -> left = temp -> right = NULL;
            int error = push(stack, temp, &top);
            if (error) {
                fprintf(stderr, "Stack overflow\n");
                return NULL;
            }
        }
        if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' ||
            postfix[i] == '/') {

            node* tempright = pop(stack, &top), *templeft = pop(stack, &top);
            if (!tempright || !templeft) {
                fprintf(stderr, "Operand not found\n");
                return NULL;
            }
            node* temp = malloc(sizeof(*temp));
            temp -> data = postfix[i];
            temp -> left = templeft;
            temp -> right = tempright;
            int error = push(stack, temp, &top);
            if (error) {
                fprintf(stderr, "Stack overflow\n");
                return NULL;
            }
        }
    }
    if (top != 0) {
        fprintf(stderr, "Error: Top value is %d after evaluation\n", top);
        return NULL;
    }
    return stack[0];
}

int evaluate_expression_tree(node* root, int* error) {
    if (!root) {
        *error = 1;
        return 0;
    }
    if (root -> data >= '0' && root -> data <= '9') {
        if (root -> left || root -> right) {
            *error = 1;
            return 0;
        }
        return root -> data - '0';
    }
    switch (root -> data) {
    case '+':
        return evaluate_expression_tree(root -> left, error) + 
               evaluate_expression_tree(root -> right, error);
    case '-':
        return (evaluate_expression_tree(root -> left, error) - 
               evaluate_expression_tree(root -> right, error));
    case '*':
        return (evaluate_expression_tree(root -> left, error) * 
               evaluate_expression_tree(root -> right, error));
    case '/':
        if (evaluate_expression_tree(root -> right, error) == 0) {
            *error = 1;
            return 0;
        }
        return (evaluate_expression_tree(root -> left, error) / 
               evaluate_expression_tree(root -> right, error));
    default:
        *error = 1;
        return 0;
    }
}

void print_tree_char(node* root, int curdepth) {
    if (!root)
        return;
    print_tree_char(root -> right, curdepth + 1);
    for (int i = 0; i < curdepth; i++)
        printf("\t");
    printf("%c\n", root -> data);
    print_tree_char(root -> left, curdepth + 1);
}

void removenewline(char* str) {
    for (int i=0; str[i] != '\0'; i++)
        if (str[i] == '\n' || str[i] == '\r') {
            str[i] = '\0';
            break;
        }
}