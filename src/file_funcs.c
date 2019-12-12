#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "graph.h"
#include "file_funcs.h"

//This file is for read file and deal with target, dep, recipes
int check_file(char *fname)
{
	FILE* fp = fopen(fname, "r");
	if (!fp) {
		fprintf(stderr, "\n---------------------------------------------------------\n");
		fprintf(stderr, "\nWrong! Cannot open the file, it doesn't exist.\n");
		fprintf(stderr, "\nMake sure the order is correct or type right!.\n");
		fprintf(stderr, "\n---------------------------------------------------------\n");
		return -1;
	}
	fclose(fp);
	return 0;
}

//Parse the input makefile to determine targets, dependencies, and recipes
target *process_file_to_target(char *fname, int *count) {
	FILE* fp = fopen(fname, "r");
	char line[LINE_SIZE];
	int i = 0;
	// malloc memory space for array of target
	target *targetList = NULL;
	targetList = calloc(LINE_SIZE, sizeof(target));
	if (targetList == NULL) {
		fprintf(stderr, "Malloc failed!\n");
		return NULL;
	}
	int index = -1;
	
	//Read the contents and store in lines, and deal the data when reading line
	while (fgets(line, LINE_SIZE, fp)){ 
		strncpy(lines[i], line, strlen(line));
		//  empty line start as '\n'
		if (lines[i][0] == '\n'){
		//compelete a targetBlock, save in list, index + 1
			continue;
		}

		//recipes, start after '\t', use the targetBlock in the targetList
		else if (lines[i][0] == '\t'){
			//Recieps Lines 
			TARGET_INDEX_OF(targetList, index)->Lines += 1;

			int start = TARGET_INDEX_OF(targetList, index)->LastIndex;

			// recipe_count for the next line
			int j = TARGET_INDEX_OF(targetList, index)->recipe_count;
			char *token = NULL;
			int after = 0;

			while(after == 0 || token != NULL){
				//deal the first character '\t'
				if(after != 1){
					
					//first may have \t
					token = strtok(lines[i], "\t,\n");
					// TARGET_INDEX_OF(targetList, index)->recipe[j] = token;
					TARGET_INDEX_OF(targetList, index)->recipe[j] = malloc(strlen(token) + 1);
					strcpy(TARGET_INDEX_OF(targetList, index)->recipe[j], token);		
								
					// '\t' should not count in recipe count
					if(token == NULL || *token == '\n')
						break;

					TARGET_INDEX_OF(targetList, index)->recipe_count += 1;
					TARGET_INDEX_OF(targetList, index)->pairs[start] = j;

					j += 1;
					after = 1; 
				}
				// ", " deal delemiter
				token = strtok(NULL, ",\n");
				if(token == NULL || *token == '\n'){
				//there is not ","
					break;
				}
				//deal recipe, delete blank 
				//if it can get into here, there is at least one ","
				//the index must be on

				token += 1; 
				TARGET_INDEX_OF(targetList, index)->recipe[j] = malloc(strlen(token) + 1);
				strcpy(TARGET_INDEX_OF(targetList, index)->recipe[j], token);
				TARGET_INDEX_OF(targetList, index)->recipe_count += 1;
				j += 1;
 
			}

			start += 1;
			TARGET_INDEX_OF(targetList, index)->pairs[start] = j-1;
			start += 1;
			TARGET_INDEX_OF(targetList, index)->LastIndex = start;
			
		}
		// target line, create a target block
		else{
			// new targetBlock, otherwise it will call the last target
			index += 1;
			target targetBlock;
			
			char* token = NULL;
			int after = 0;
			int j = 0;

			while(after == 0 || token!= NULL ){
				// dael target 
				if( after != 1){
					token = strtok(lines[i], " :");

					// create and compress it into list immediately
					targetBlock.name = token;
					// TARGET_INDEX_OF(targetList, index)->name = targetBlock.name;
					TARGET_INDEX_OF(targetList, index)->name = malloc(strlen(targetBlock.name) + 1);
					strcpy(TARGET_INDEX_OF(targetList, index)->name, targetBlock.name);
					
					//declare the lines of recipes 
					TARGET_INDEX_OF(targetList, index)->Lines = -1;
					TARGET_INDEX_OF(targetList, index)->LastIndex = 0;
					after = 1;
				}
				token = strtok(NULL, " :\n");
				if (token == NULL || *token == '\n')
					break;
				
				//deal depend
				TARGET_INDEX_OF(targetList, index)->depend[j] = malloc(strlen(token) + 1);
				strcpy(TARGET_INDEX_OF(targetList, index)->depend[j], token);
				TARGET_INDEX_OF(targetList, index)->dep_count +=1;
				j += 1;
			}

		}
	//after read this line
	i += 1;
	}

	*count = index;
	fclose(fp);
	return targetList;
}


int print_targets_detail(target *list_ptr, int *count) {
	if (list_ptr == NULL) {
		fprintf(stderr, "Target does not exist!\n");
		return -1;
	}
	target *temp = list_ptr;
	// get the pointer to the target by name
	for (int i = 0; i < *count + 1; i++) {
		printf("target \'%s\' has %d dependencies and %d recipe\n", temp->name, temp->dep_count, temp->recipe_count);
		for(int j = 0; j < temp->dep_count; j++) {
			printf("Dependency %d is %s\n", j, temp->depend[j]);
		}
		for(int k = 0; k < temp->recipe_count; k++) {
			printf("Recipe %d is %s\n", k, temp->recipe[k]);
		}
		temp = TARGET_INDEX_OF(list_ptr, i+1);
		printf("\n");
	}
	return 1;
}

// free all the string blocks malloc by targets
void free_target_string(target *tar, int *count) {
	for(int i = 0; i < *count + 1; i++) {
		// free all the target names
		free(TARGET_INDEX_OF(tar, i)->name);
		// free all the dependency names
		for(int j = 0; j < TARGET_INDEX_OF(tar, i)->dep_count; j++) {	
			free(TARGET_INDEX_OF(tar, i)->depend[j]);	
		}
		// free all the recipes
		for(int k = 0; k < TARGET_INDEX_OF(tar, i)->recipe_count; k++) {	
			free(TARGET_INDEX_OF(tar, i)->recipe[k]);	
		}	
	}
}
