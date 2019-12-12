#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "dfs_stack.h"

// This file is for stack operations

void stack_init(Stack *s) {
    s->size = 0;
}

target *top(Stack *s) {
    if (s->size == 0) {
        fprintf(stderr, "\n---------------------------------------------------------\n");
		fprintf(stderr, "\nWrong! Stack is empty.\n");
		fprintf(stderr, "\n---------------------------------------------------------\n");
        return NULL;
    }
    target *top_target = &s->stk[s->size - 1];
    return top_target;
}

void push(Stack *s, target *target_block) {
    if (s->size < MAX_TARGETS)
        s->stk[s->size++] = *target_block;
    else{
        fprintf(stderr, "\n---------------------------------------------------------\n");
		fprintf(stderr, "\nWrong! Stack is full.\n");
		fprintf(stderr, "\n---------------------------------------------------------\n");

    }
}

void pop(Stack *s) {
    if (s->size == 0){
        fprintf(stderr, "\n---------------------------------------------------------\n");
		fprintf(stderr, "\nWrong! Stack is empty.\n");
		fprintf(stderr, "\n---------------------------------------------------------\n");
    }
        
    else
        s->size--;
}

//In main function, using TargetNanme find the target
target *find_target(Stack *s, char * TargetName){
    if (s->size == 0){
        fprintf(stderr, "\n---------------------------------------------------------\n");
		fprintf(stderr, "\nWrong! Target doesn't exist in this Makefile.\n");
        fprintf(stderr, "\nMake sure the order is correct or type right!.\n");
		fprintf(stderr, "\n---------------------------------------------------------\n");
    }       
  
    int size = s->size;    
    for (int i = 0;i < size; i++){        
        target *temp = &s->stk[i];
        if (strcmp(temp->name, TargetName) == 0){
            return temp;
        }
    }
    fprintf(stderr, "\n---------------------------------------------------------\n");
	fprintf(stderr, "\nWrong! Target doesn't exist in this Makefile.\n");
    fprintf(stderr, "\nMake sure the order is correct or type right!.\n");
	fprintf(stderr, "\n---------------------------------------------------------\n");
    exit(EXIT_FAILURE); 
}

// Print all the recipes from the stack
void print_all_recipe(Stack *s) {    
    if (s->size == 0)       
    fprintf(stderr, "Error: stack empty\n");    
    int size = s->size;    
    for (int i = 0;i < size; i++){        
        target *temp = &s->stk[i];        
        for (int j = 0; j < temp->recipe_count; j++){            
            printf("%s\n", temp->recipe[j]);        
        }    
    }
}

Stack *create_stack_byTarget(Stack *s, target *tar) {
    if (s->size == 0)
        fprintf(stderr, "Error: old stack is empty\n");
    Stack old_stack = *s;
    // Create a new stack
    Stack *new_stack = malloc(sizeof(Stack));
    stack_init(new_stack);
    // Find the target in the old stack and push to the new stack
    target *old_top = top(&old_stack);
    while (old_stack.size != 0) {
        if (strcmp(old_top->name, tar->name) == 0) {
            push(new_stack, old_top);
            pop(&old_stack);
            break;
        }
        pop(&old_stack);
        old_top = top(&old_stack);
    }
    // Push dependent targets to the new stack
    while (old_stack.size != 0) {
        old_top = top(&old_stack);
        for (int i = 0;i < new_stack->size; i++) {
            target temp = new_stack->stk[i];
            for(int j = 0; j < temp.dep_count; j++) {
                if(strcmp(old_top->name, temp.depend[j]) == 0) {
                    push(new_stack, old_top);
                    break;
                }
            }
        }
        pop(&old_stack);
    }
    return new_stack;
}

// print the recipes when run with target option
void print_stack_byTarget(Stack *s, target *tar) {
    if (s->size == 0)
    fprintf(stderr, "Error: new stack is empty\n");
    Stack new_stack = *s;
    while (new_stack.size != 0) {
        target *temp = top(&new_stack);
        for(int i = 0; i < temp->recipe_count; i++) {
            printf("%s\n", temp->recipe[i]);
        }
        pop(&new_stack);
    }
}

int run_recipe_fromStack(Stack *s) {

    return 0;
}

// Topological Sort

Stack *topological_sort(target *targetlist, int *count) {
    Stack *stack = malloc(sizeof(Stack));
    stack_init(stack);
    int target_count = *count + 1;
    int *visited = calloc(target_count,sizeof(int));
    for (int i = 0; i < target_count; i++) {
        if (!visited[i])
            topological_sort_visit(targetlist, &target_count, TARGET_INDEX_OF(targetlist, i), &i, visited, stack);
    }
    free(visited);
    return stack;
}

void topological_sort_visit(target *targetlist, int *count, target *vertex, int *index, int *visited, Stack *stack) {
    int curr = *index;
    visited[curr] = 1;
    int len = *count;
    target *next_vertex;
    for(int i = 0; i < vertex->dep_count; i++) {
        char *next_vertex_name = vertex->depend[i];
        int next_index = 256;
        for(int j = 0; j < len; j++) {
            char *tname = TARGET_INDEX_OF(targetlist, j)->name;
            if (strcmp(next_vertex_name, tname) == 0) {
                next_index = j;
                next_vertex = TARGET_INDEX_OF(targetlist, j);
                break;
            }
        }
        if (next_index < 256) {
            if (!visited[next_index])
                topological_sort_visit(targetlist, &len, next_vertex, &next_index, visited, stack);
        }
    }
    push(stack, vertex);
}