#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
struct Node {
    char data;
    struct Node *left, *right;
};
struct Stack {
    int top;
    struct Node* arr[100];
};
void initStack(struct Stack* s) {
    s->top = -1;
}
void push(struct Stack* s, struct Node* node) {
    s->arr[++(s->top)] = node;
}
struct Node* pop(struct Stack* s) {
    return s->arr[(s->top)--];
}
struct Node* newNode(char data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}
void infixToPostfix(char* infix, char* postfix) {
    char stack[100];
    int top = -1, k = 0;
    for (int i = 0; infix[i]; i++) {
        char c = infix[i];
        if (isalnum(c)) { 
            postfix[k++] = c;
        }
        else if (c == '(') {
            stack[++top] = c;
        }
        else if (c == ')') {
            while (top != -1 && stack[top] != '(')
                postfix[k++] = stack[top--];
            top--; '(';
        }
        else { 
            while (top != -1 && precedence(stack[top]) >= precedence(c))
                postfix[k++] = stack[top--];
            stack[++top] = c;
        }
    }
    while (top != -1) postfix[k++] = stack[top--];
    postfix[k] = '\0';
}

struct Node* constructExpressionTree(char* postfix) {
    struct Stack s;
    initStack(&s);
    for (int i = 0; postfix[i]; i++) {
        char c = postfix[i];
        if (isalnum(c)) { 
            push(&s, newNode(c));
        } else { 
            struct Node* node = newNode(c);
            struct Node* right = pop(&s);
            struct Node* left = pop(&s);
            node->left = left;
            node->right = right;
            push(&s, node);
        }
    }
    return pop(&s); 
}

void printPrefix(struct Node* root) {
    if (root == NULL) return;
    printf("%c", root->data);
    printPrefix(root->left);
    printPrefix(root->right);
}

void printPostfix(struct Node* root) {
    if (root == NULL) return;
    printPostfix(root->left);
    printPostfix(root->right);
    printf("%c", root->data);
}

int main() {
    char infix[100], postfix[100];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    struct Node* root = constructExpressionTree(postfix);

    printf("Prefix expression: ");
    printPrefix(root);
    printf("\n");

    printf("Postfix expression: ");
    printPostfix(root);
    printf("\n");

    return 0;
}

