CUR_DIR = $(shell pwd)
TST_DIR = $(CUR_DIR)/test
CC = gcc
CFLAGS = -Wall -std=c99 
DBFLAG = -g
SRC = ${CUR_DIR}/src/main.c 
DEP = ${CUR_DIR}/src/graph.h ${CUR_DIR}/src/dfs_stack.h
OBJ = ${CUR_DIR}/main.o

.PHONY : clean all

all: main 

${OBJ}: ${SRC} ${DEP}
	$(CC) $(CFLAGS) $(DBFLAG) -c $< -o $@ 

main: ${OBJ} 
	$(CC) $(CFLAGS) $(DBFLAG) $(OBJ) -o mymake 

test-main: main test1 test2 test3 test4 test5 test6

test1: 
	@printf "===Testing mymake===\n"
	@printf "\nTest 1a: Normal case - print the content\n"	
	./mymake -p ${TST_DIR}/Makefile1
	@printf "\n"
	@printf "\nTest 1b: Normal case - pick target\n"	
	./mymake ${TST_DIR}/Makefile1
	@printf "\n"
	@printf "\nTest 1c: Normal case - valid target\n"	
	./mymake ${TST_DIR}/Makefile1 clean
	@printf "\n"
	@printf "\nTest 1d: Failure case - target doesn't exist\n"	
	./mymake ${TST_DIR}/Makefile1 clean1
	@printf "\n"
	@printf "\nTest 1e: Normal case - print recipes\n"	
	./mymake -r ${TST_DIR}/Makefile1 
	@printf "\n"

test2: 
	@printf "\nTest 2a: Normal case\n"	
	./mymake -p ${TST_DIR}/Makefile2
	@printf "\n"
	@printf "\nTest 2b: Normal case\n"	
	./mymake ${TST_DIR}/Makefile2 clean
	@printf "\n"
	@printf "\nTest 2c: Normal case - print recipes\n"	
	./mymake -r ${TST_DIR}/Makefile2 
	@printf "\n"
	@printf "\nTest 2d: Failure case - target doesn't exist\n"
	./mymake ${TST_DIR}/Makefile2 thunder
	@printf "\n"
	@printf "\nTest 2e: Failure case - file doesn't exist\n"
	./mymake thunder ${TST_DIR}/Makefile2 
	@printf "\n"
	@printf "\nTest 2f: Failure case - incorrect arg order\n"
	./mymake ${TST_DIR}/Makefile2 -p 
	@printf "\n"

test3: 
	@printf "\nTest 3a: Failure case - incorrect order\n"	
	./mymake ${TST_DIR}/Makefile3 -p 
	@printf "\n"
	@printf "\nTest 3b: Failure case - too many args\n"	
	./mymake ${TST_DIR}/Makefile3 -p myprog.c
	@printf "\n"
	@printf "\nTest 3c: Normal case\n"	
	./mymake -p ${TST_DIR}/Makefile3 
	@printf "\n"
	@printf "\nTest 3d: Normal case\n"	
	./mymake ${TST_DIR}/Makefile3 myprog.c
	@printf "\n"
	@printf "\nTest 3e: Normal case - execute rar\n"	
	./mymake ${TST_DIR}/Makefile3 rar
	@printf "\n"
	@printf "\nTest 3f: Normal case: execute rar\n"	
	./mymake ${TST_DIR}/Makefile3 
	@printf "\n"
	@printf "\nTest 3g: Normal case - print recipes\n"	
	./mymake -r ${TST_DIR}/Makefile3 
	@printf "\n"

test4:
	@printf "\nTest 4a: Failure case - incorrect order\n"	
	./mymake ${TST_DIR}/Makefile4 -p
	@printf "\n"
	@printf "\nTest 4b: Failure case - multiple args\n"	
	./mymake ${TST_DIR}/Makefile4 -p renderer.o
	@printf "\n"
	@printf "\nTest 4c: Failure case - target doesn't exist\n"	
	./mymake ${TST_DIR}/Makefile4 random
	@printf "\n"
	@printf "\nTest 4d: Failure case - Multiple arguments\n"	
	./mymake -p ${TST_DIR}/Makefile4 -p
	@printf "\n"
	@printf "\nTest 4e: Normal case - tokenize contents of file\n"	
	./mymake -p ${TST_DIR}/Makefile4 
	@printf "\n"
	@printf "\nTest 4f: Normal case\n"	
	./mymake ${TST_DIR}/Makefile4 test.o
	@printf "\n"
	@printf "\nTest 4g: Normal case - execute renderer.o\n"	
	./mymake ${TST_DIR}/Makefile4 renderer.o
	@printf "\n"

test5: 
	@printf "\nTest 5a: Failure case - file doesn't exist\n"	
	./mymake ${TST_DIR}/Makefilex
	@printf "\n"
	@printf "\nTest 5b: Failure case - file doesn't exist\n"
	./mymake -p d
	@printf "\n"

test6:
	@printf "\nTest 6: Failure case - Multiple arguments\n"
	./mymake -p -r ${TST_DIR}/Makefile1
	@printf "\n"

clean:
	rm -f mymake *.o
