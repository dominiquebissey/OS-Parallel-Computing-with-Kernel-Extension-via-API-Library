/*.........................................................................*/
/*                  TSHTEST.H ------> TSH test program                     */
/*                  February '13, Oct '18 updated by Dominique Bissey         */
/*.........................................................................*/

#include "synergy.h"

u_short PORT = 12944;
int tshsock ;

int connectTsh(u_short) ;

u_long OpPut(char *, char *, long) ;
u_long OpGet(char *, char **) ;
u_long OpRead(char *, char **) ;



