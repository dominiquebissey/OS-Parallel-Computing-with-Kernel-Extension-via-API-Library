/*.........................................................................*/
/*                  TSPINGPONG.C ------> TSH API test program                     */
/*                                                                         */
/*                  By N. Isaac Rajkumar [April '93]                       */
/*                  February '13, updated by Dominique Bissey                 */
/*.........................................................................*/

#include "tsPingPong.h"

int main(int argc, char **argv)
{
    char tpName[64]; strcpy(tpName,"Tuple1");
    char tpName2[64]; strcpy(tpName2, "Tu");
    char *tuple = "This is the very first pingpong tuple....";
    char *returnTuple;
    u_long tpLength = strlen(tuple);
    u_long status; //Returning value
    //Now put tuple
    status = OpPut(tpName, tuple, tpLength);
    printf("OpPut status (%ld) sent to Tuple Space\n", status);
    //Now read tuple
    strcpy(tpName2, "Tu");
    status = OpRead(tpName2, &returnTuple);
    printf("OpRead1 bytes(%ld) name (%s) returnTuple(%s)\n", status, tpName2, returnTuple);
    //Now get tuple
    strcpy(tpName2, "Tu");
    status = OpGet(tpName2, &returnTuple);
    printf("OpGet bytes(%ld) name (%s) returnTuple(%s)\n", status, tpName2, returnTuple);
    int ix = atoi(&tpName2[5]);
    printf("OpGet atoi conversion (%d)\n", ix);
    //Hanging
    strcpy(tpName2, "Tu");
    status = OpRead(tpName2, &returnTuple);
    printf("OpRead2 bytes(%ld) name (%s) returnTuple(%s)\n", status, tpName2, returnTuple);

    exit(0);

}