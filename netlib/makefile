INCL = -I../include
FLAGS = -c -g
EXTRA = 
cc = gcc

all :	netlib.o tshlib.o wall_clock.o archive ranl move

wall_clock.o : wall_clock.c
	$(cc) $(EXTRA) $(INCL) $(FLAGS) wall_clock.c $(TAIL)
netlib.o : netlib.c $(TAIL)
	$(cc) $(EXTRA)  $(INCL) $(FLAGS)  netlib.c $(TAIL)
tshlib.o : tshlib.c $(TAIL)
	$(cc) $(EXTRA)  $(INCL) $(FLAGS)  tshlib.c $(TAIL)
archive : 
	ar rcv libb.a *.o
ranl:
move :
	mv libb.a ../obj/libsng.a
	/bin/rm -f *.o
