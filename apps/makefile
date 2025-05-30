SYS_LINK=-L/usr/lib
INCS = -I../include
OBJS = ../obj 
FLAGS = -g 
cc = gcc

all : tsPingPong

tsPingPong : tsPingPong.c 
	$(cc) $(EXTRA) $(INCS) $(FLAGS) -o tsPingPong tsPingPong.c -L$(OBJS) -lsng
