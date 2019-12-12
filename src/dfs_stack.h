#ifndef __DFS_STACK_H
#define __DFS_STACK_H

//Implement a stack for DFS
typedef struct stack {
    target stk[MAX_TARGETS];
    int size;
} Stack;

void stack_init(Stack *s);

target *top(Stack *s);

void push(Stack *s, target *target_block);

void pop(Stack *s);

target *find_target(Stack *s, char * TargetName);

void print_all_recipe(Stack *s);

Stack *create_stack_byTarget(Stack *s, target *tar);

void print_stack_byTarget(Stack *s, target *tar);

int run_recipe_fromStack(Stack *s);

Stack *topological_sort(target *targetlist, int *count);

void topological_sort_visit(target *targetlist, int *count, target *vertex, int *index, int *visited, Stack *stack);

#endif
