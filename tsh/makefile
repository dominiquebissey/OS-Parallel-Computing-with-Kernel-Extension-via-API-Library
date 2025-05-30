SYS_LINK=-L/usr/lib
INCS = -I../include
OBJS = ../obj 
FLAGS = -g 
cc = gcc

all : tsh tshtest launch copy 

tsh : tsh.c 
	$(cc) $(EXTRA) $(INCS) $(FLAGS) -o tsh tsh.c -L$(OBJS) -lsng

tshtest : tshtest.c 
	$(cc) $(EXTRA) $(INCS) $(FLAGS) -o tshtest tshtest.c -L$(OBJS) -lsng

launch : launch.c
	$(cc) $(EXTRA) $(INCS) $(FLAGS) -o launch launch.c -L$(OBJS) -lsng

copy: tsh tshtest launch
	cp tsh ../bin
	cp tshtest ../bin
	cp launch ../bin
