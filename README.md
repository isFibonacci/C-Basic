# shell
---
### 1. Purpose of 'mymake' Program ###
'mymake' is an executable generated from a C program. As we know, makefile are made up of targets, dependencies and recipes. The purpose of 'mymake' is to print out recipes or dependency relationship of targets and execute recipes in correct order from the given makefile and target(optional).

---

### 2. How to Compile the Program ###
'mymake' can be compiled by a given Makefile inside the root directory.
User can compile the program by ’make':
```
    $ make
```
Then an executable named 'mymake' will be generated. To remove the executable, user can simply type in 'make clean'.

---

### 3. What exactly the program does ###
There are three ways to execute the program via
- $ ./mymake filename [target]
- $ ./mymake [-p] filename
- $ ./mymake [-r] filename

1. Running $ ./mymake filename [target]

    First, user will need to provide a Makefile name and a target(optional).
    'mymake' will parse the makefile and build a dependency graph for the (optional) provided target. Then the recipes that need to be executed will be printed out and executed for the said target. If no target is specified as a command line argument, the first target in the makefile is chosem.

2. Running $ ./mymake [-p] filename

    '-p' means printing out all the information for each of the target in the Makefile.
    First, user will need to enter the '-p' flag and a Makefile name.
    'mymake' will read the contents of the makefile. Then it will print the target name, the dependency count and recipe count for each of the target in the Makefile. In addition, the dependencies and recipes for each of the target will also be printed out.

3. Running $ ./mymake [-r] filename

    '-r' means printing out the order of recipes.
    First, user will need to enter the '-r' flag and a Makefile name.
    'mymake' will pick all targets and look for recipes by the order of dependency graph in the given file.
    It will print all the recipes in the order of execution.
---

### 4. Additional Assumptions ###
-   Path clarification:
    The first argument of 'mymake' can directly take the name of makefile in the same directory as 'mymake' without clarifying path. 
    However, if users want to run makefile in other diretories, they have to add the path of the makefile by themseleves.
    For example, if someone want to run the Makefile5 in the 'test' diretory which is in the same directory as 'mymake',
    one should input './test/Makefile5' as the first argument.
    More specifically, one can type '$ ./mymake ./test/Makefile5' to run Makefile5.

    We use two loops. In the first loop, let's say if there are three lines recipes, we fork three times. And then if pid == 0, that means it is a child process, we check how many recipes in this line use some attributes in the target struct; Let's say there are two recipes: mkdir myproject, pwd; we fork two times and then exec paralle; We have to wait until these two process is finished and then continue next line as anthoer process. We wait until all the process finished and then exit. More detail is in fork_parallel.c
    
