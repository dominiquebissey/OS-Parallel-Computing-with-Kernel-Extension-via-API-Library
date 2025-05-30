/*.........................................................................*/
/*                  TSHTEST.H ------> TSH test program                     */
/*                  February '13, Oct '18 updated by Dominique Bissey         */
/*.........................................................................*/

#include "synergy.h"

char login[TUPLENAME_LEN];

void OpPut(/*void*/) ;
void OpGet(/*void*/) ;
void OpExit(/*void*/) ;
void OpShell(/*void*/) ;


int tshsock ;

int connectTsh(u_short) ;
u_short drawMenu(/*void*/) ;

