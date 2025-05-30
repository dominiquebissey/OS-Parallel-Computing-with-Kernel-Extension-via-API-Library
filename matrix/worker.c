#include <stdio.h>
#include "matrix.h"

double ita[N/2][N];
double ott[N/2][N];
double wall_clock();

int main()
{
	int G, tsd, res, i, j, k, status;
	int ix, ia, ib, tplength;
	double t0, t1;
	//sleep(20);

	strcpy(tpname, "B");
	puts(tpname);
	printf("To OpRead");
	status = OpRead(tpname, (char **) &ituple_B); 
    //printf(" mtwrk. received B (%s) \n", tpname);
	tplength = (1+N*N)*sizeof(double);
	if ((ituple_A = (double *)malloc(tplength)) == NULL) 
		exit(-1);
	while (1)  		/* loop forever */
	{
		printf("Worker waiting for a tuple \n");
		strcpy(tpname, "A");
		tplength = OpGet(tpname, (char **) &ituple_A);
		printf("Worker recieved (%s)\n", tpname);
		t0 = wall_clock();


		ix = atoi(&tpname[1]);
		printf("Worker got (%s) ix(%d) \n",tpname, ix);
		if (tplength > 0) {		/* normal receive */
			G = (int) ituple_A[0];

			printf(" mtwrk got ix (%d) G(%d) \n",ix, G);
			printf("Tuple first item [%f]", *ituple_A);

		/* check for the application termination signal */
			if (G == -1) {
				status = OpPut(tpname, (char*)ituple_A, tplength);
				exit(1);
				return 0;
			}
			for (i = 0; i < G; i++)
				for (j = 0; j < N; j++)
				{
					ita[i][j] = ituple_A[i*N+j+1];
					ott[i][j] = 0;
				}
			if ((otuple = (double *)malloc(tplength)) == NULL)
				exit(-1);
			otuple[0] = ituple_A[0];

			for (i =0; i < G; i++)
			    for (k =0; k < N; k++)
			    	for (j =0; j < N; j++)
			    		ott[i][j] = ott[i][j] + ita[i][k] * ituple_B[k][j];


			for (i = 0; i < G; i++)
				for (j = 0; j < N; j++)
					otuple[i*N+j+1] = ott[i][j];



			 sprintf(tpname,"C%d",ix);
			 //printf(" mtwrk. put in (%s) \n",tpname);
			 status = OpPut(tpname, (char*)otuple, tplength);
			 t1 = wall_clock() - t0;
			 //printf(" Worker MFLOPS = (%f) \n", N*N*G/t1);
			 free(otuple);
		} else {
			printf("Worker Terminated \n"); 
			exit(0);
		}
	}

}

