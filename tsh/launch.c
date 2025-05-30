/*.........................................................................*/
/*                  LAUNCH.C ------> TSH test program                     */
/*                                                                         */
/*                  By N. Isaac Rajkumar [April '93]                       */
/*                  February '13, updated by Dominique Bissey                 */
/*.........................................................................*/

#include "tshtest.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_COMMAND_LENGTH 1024

int status;

int connectTsh(u_short port)
{
   struct hostent *host ;
   short tsh_port ;
   u_long tsh_host ;
   int sock ;

   // use local host 
   tsh_host = inet_addr("127.0.0.1");
   /*
   if ((host = gethostbyname("localhost")) == NULL)
	{
	   perror("connectTsh::gethostbyname\n") ;
	   exit(1) ;
	}
   tsh_host = *((long *)host->h_addr_list[0]) ;
   */
   tsh_port = htons(port);
				/* get socket and connect to TSH */
   if ((sock = get_socket()) == -1)
    {
       perror("connectTsh::get_socket\n") ;
       exit(1) ;
    }
   if (!do_connect(sock, tsh_host, tsh_port))
    {
       perror("connectTsh::do_connect\n") ;
       exit(1) ;
    }      
   return sock ;
}


int main(int argc, char **argv)
{
	u_short this_op ;
   
	if (argc < 2)
    {
       printf("Usage : %s port commandPath\n", argv[0]) ;
       exit(1) ;
    }
    this_op = htons(TSH_OP_SHELL) ;
    tshsock = connectTsh(atoi(argv[1])) ;
        // Send this_op to TSH
    if (!writen(tshsock, (char *)&this_op, sizeof(this_op)))
    {
        perror("main::writen\n") ;
        exit(1) ;
    }
    printf("sent tsh OP_SHELL op \n");
    tsh_shell_it out;
    tsh_shell_ot in;
    char *buff = NULL;
    char *st;
    size_t command_length;

    printf("\nEnter command to execute: ");
    buff = (char *)malloc(MAX_COMMAND_LENGTH);
    st = fgets(buff, MAX_COMMAND_LENGTH, stdin);
    if (!st) {
        perror("fgets failed");
        free(buff);
        return 1;
    }

    buff[strcspn(buff, "\n")] = 0;

    command_length = strlen(buff);
    out.length = htonl(command_length);

    if (!writen(tshsock, (char *)&out, sizeof(out))) {
        perror("OpShell: writen failed");
        free(buff);
        return 2;
    }

    if (!writen(tshsock, buff, command_length)) {
        perror("OpShell: writen failed to send command");
        free(buff);
        return 3;
    }

    if (!readn(tshsock, (char *)&in, sizeof(in))) {
        perror("OpShell: readn failed");
        free(buff);
        return 4;
    }

    printf("\n\nFrom TSH :\n");
    printf("\nstatus : %d", ntohs(in.status));
    printf("\nerror : %d\n", ntohs(in.error));
    printf("stdout : %s\n", in.stdout);

    free(buff);
    close(tshsock);
}
