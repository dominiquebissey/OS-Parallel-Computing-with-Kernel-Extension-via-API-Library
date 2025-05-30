OBJS =-L ../obj -lsng
CFLAGS = -I../include -g

ifndef SIZE
SIZE = 100 
endif

all: nxdr copy

nxdr :  master worker matrix

master : master.c
	cc $(CFLAGS) -DN=$(SIZE) $(INCS) -o master master.c $(OBJS)

worker : worker.c
	cc $(CFLAGS) -DN=$(SIZE) $(INCS) -o worker worker.c $(OBJS)

matrix : matrix.c
	cc $(CFLAGS) -DN=$(SIZE) $(INCS) -o matrix matrix.c $(OBJS)

copy : master worker
	cp master ../bin
	cp worker ../bin

