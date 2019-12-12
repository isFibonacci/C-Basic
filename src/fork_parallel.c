#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include "graph.h"
#include "fork_parallel.h"


// This file is for 1.3 fork/exec


void child_execute(char *recipe) {
    char *cmd[128];
    int j = 0;
    char *token = NULL;
    token = strtok(recipe, " ");
    while(token != NULL){
        cmd[j] = token;
        token = strtok(NULL, " ");
        j += 1;
    }
    cmd[j+1] = NULL;
    execvp(cmd[0], cmd); 

    fprintf(stderr, "\n---------------------------------------------------------\n");
    fprintf(stderr, "\nWrong! Exec fail.\n");
    fprintf(stderr, "\n---------------------------------------------------------\n");
    exit(-1);
}


int run(target *targetBlock){

    int lines = targetBlock->Lines;
    int pid;

    for (int i = 0; i <= lines; i++) {

        /* fork another process */
        pid = fork();

        if (pid<0) { 
            /* error occurred */
            fprintf(stderr, "\n---------------------------------------------------------\n");
		    fprintf(stderr, "\nWrong! Fork fail.\n");
		    fprintf(stderr, "\n---------------------------------------------------------\n");
        
            exit(-1);
        } 
        else if (pid==0){
            /*  child process   */
            int start = targetBlock->pairs[2 * i];
            int end = targetBlock->pairs[2 * i + 1];

            // recipes need to exec parallel 
            for (int j = 0; j <= end -start; j++) {
                pid_t cpid = fork();
                if (cpid == 0){
                    child_execute(targetBlock->recipe[start + j]);
                }
            }
            for (int j = 0; j <= end -start; j++) {
                wait(NULL);
            }
            exit(0);
        }
        else{ 
            /*    parent process  */
            /* parent will wait for the child to complete*/
            wait(NULL);

        }
    } 
    return 0;

    
}