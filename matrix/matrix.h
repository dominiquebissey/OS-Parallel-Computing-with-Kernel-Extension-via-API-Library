#include "synergy.h"

char tpname[64];

double ituple_B[N][N];
double *ituple_A;
double *otuple;

u_long OpPut(char *, char *, long) ;
u_long OpGet(char *, char **) ;
u_long OpRead(char *, char **) ;