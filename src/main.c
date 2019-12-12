
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "graph.h"
#include "dfs_stack.h"
#include "file_funcs.h"
#include "fork_parallel.h"
#include "dfs_funcs.c"
#include "file_funcs.c"
#include "fork_parallel.c"



// argv[0] is the program name， argv[1] is parameter like filename 
//Validate the input arguments, bullet proof the program
int main(int argc, char *argv[]) {

	// pointer to array of target
	target *targetListPtr;
	int target_count = 0;

	// run like $ ./mymake -p Makefile4
	if((argc == 3) && strncmp(argv[1], "-p", 2) == 0){

		if(check_file(argv[2]) == -1) {
			exit(EXIT_FAILURE);
		}

		// Process file to an array of targets and print recipes and dependencies
		targetListPtr = process_file_to_target(argv[2], &target_count);
		print_targets_detail(targetListPtr, &target_count);

		free_target_string(targetListPtr, &target_count);
		free(targetListPtr);
	}

	// run like $ ./mymake [-r] filename
	else if(((argc == 3) && strncmp(argv[1], "-r", 2) == 0)){

		if(check_file(argv[2]) == -1) {
			exit(EXIT_FAILURE);
		}

		// Process file to an array of targets and sort them into a stack
		targetListPtr = process_file_to_target(argv[2], &target_count);
		Stack *target_stack = topological_sort(targetListPtr, &target_count);
		print_all_recipe(target_stack);

		free(target_stack);
		free_target_string(targetListPtr, &target_count);
		free(targetListPtr);
	}

	//$ ./mymake filename [target] 
	//If the optional arguments are provided, they must be in fixed positions.
	else if (argc == 3) {

		if(check_file(argv[1]) == -1) {
			exit(EXIT_FAILURE);
		}

		// Process file to an array of all targets and sort them into a stack
		targetListPtr = process_file_to_target(argv[1], &target_count);
		Stack *target_stack = topological_sort(targetListPtr, &target_count);

		// Put targets that need to run recipes into a new stack by the specific target
		target *target_found = find_target(target_stack, argv[2]);
		Stack* final_stack = create_stack_byTarget(target_stack, target_found);
		print_stack_byTarget(final_stack, target_found);

		//take one targetBlock.dep to fork and exec each time
		while(final_stack->size != 0){
			target *temp = top(final_stack);
			pop(final_stack);
			run(temp);
		}
		
		free(target_stack);
		free(final_stack);
		free_target_string(targetListPtr, &target_count);
		free(targetListPtr);
	}

	//run like $ ./mymake filename
	else if (argc == 2){

		if(check_file(argv[1]) == -1) {
			exit(EXIT_FAILURE);
		}

		// Process file to an array of all targets and sort them into a stack
		targetListPtr = process_file_to_target(argv[1], &target_count);
		Stack *target_stack = topological_sort(targetListPtr, &target_count);

		// Push targets into a new stack by the order of running dependencies
		target *first_target = find_target(target_stack, targetListPtr->name);
		Stack* final_stack = create_stack_byTarget(target_stack, first_target);
		print_stack_byTarget(final_stack, first_target);
		
		while(final_stack->size != 0){
			target *temp = top(final_stack);
			pop(final_stack);
			run(temp);
		}

		free(target_stack);
		free(final_stack);
		free_target_string(targetListPtr, &target_count);
		free(targetListPtr);
	}

	else if (argc > 3){
		
		fprintf(stderr, "\n---------------------------------------------------------\n");
		fprintf(stderr, "\nWrong! Can only take upto two command line arguments.\n");
		fprintf(stderr, "\n---------------------------------------------------------\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
