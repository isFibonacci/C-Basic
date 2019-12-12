#ifndef __GRAPH_H
#define __GRAPH_H

#define LINE_SIZE 128
#define MAX_LINES 128
#define MAX_DEP 8
//Account for extra credit
#define MAX_RECIPES_PT 8
#define MAX_TARGETS 128
#define MAX_PARM 32

typedef struct target_block {
	char *name;
	char *depend[MAX_DEP];
	char *recipe[MAX_RECIPES_PT];
	int ReicpesLines;
	unsigned char dep_count;
	unsigned char recipe_count;
	unsigned char visited;
	
	// number of lines of recipes
	int Lines;
	// index of recipe array to identify which recipes should to be exec paralle
	int pairs[MAX_DEP*2];
	// Used in deal with file to identify which recipes should to be exec paralle
	int LastIndex;
	
} target;

char lines[MAX_LINES][LINE_SIZE];

// get the element of the array at index x
#define TARGET_INDEX_OF(ptr, x) (ptr + x)

#endif
