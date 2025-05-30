#include <stdio.h>
#include "matrix.h"
double C[N][N];		/* result Matrix. */
double A[N][N];
double wall_clock();

int main()
{ char host[128];
	int i, j, k, received;
	int ix, iy, tplength, status;
	int G, R, P, res, tsd, x;
	double t0, t1;
	float F;
	FILE *fd;

	t0 = wall_clock();
	ix = 0;


	G = 4; // Get chunk size
	P = 2; // Get number of processors
    printf(" master.  Chunk size (%d) \n",G);
	R = N;

        tplength = (1+N*N)*sizeof(double);
	// Building Matrix A and B
        for (i = 0; i < N; i++)
                for (j = 0; j < N; j++)
		{
                        ituple_B[i][j] = (double) i * j;
			A[i][j] = (double) i * j;
		}

		strcpy(tpname,"B0");
        printf("To first Put:\n");
        status = OpPut(tpname, (char *) (double *)ituple_B, tplength);
        printf("master sent (%d)bytes\n", status);
        tplength = (1+ G*N) * sizeof(double);


	//printf("tplength = (%d) \n", tplength);
	if ((ituple_A = (double *) malloc(tplength)) == NULL) 
    {
        perror("master malloc A error");
        exit(1);
    }
	while (R > 0) {
		if (R < G) G = R;
		R = R - G ;
		//printf(" mtclnt. G(%d) R(%d) \n", G,R);
		ituple_A[0] = G;
		for (x = 0; x < G; x++)
			for (j = 0; j < N; j++) 
				ituple_A[x*N+j+1] = A[ix+x][j];
		sprintf(tpname,"A%d",ix);
		status = OpPut(tpname, (char *)ituple_A, tplength);
        printf("master sent A group (%s) bytes (%d)\n", tpname, status);
		ix += G;
	}
	free(ituple_A);

	/* now receive the result  */
	received = i = 0;
	tplength = (1+N*N)*sizeof(double);
	if ((otuple = (double *)malloc(tplength)) == NULL)
    {
        perror("master result malloc error");
        exit(1);
    }
	while (received < N) {
		strcpy(tpname,"C");
		printf(" master.  waiting for result\n");
		tplength = OpGet(tpname, (char **)&otuple);

		G = (int) otuple[0];
		ix = atoi(&tpname[1]);
		iy = 1;
		printf(" master.  tuple %d received %d) \n", ix, received);
					/* reassemble the result matrix */
		for (i= 0; i < G; i++) {
				received ++;
				for (j=0; j < N; j++) {
						C[ix][j] = otuple[iy];
						iy++;
				}
				ix ++;
		}
	}
	free(otuple);

	printf(" master.  received everything\n");
	/* insert zero size tuple as termination signal */
	tplength = sizeof(double);
	if ((ituple_A = (double *)malloc(tplength)) == NULL) {
		exit(1);
	}
	ituple_A[0]  = -1;
	sprintf(tpname, "A%d",N*N);
	status = OpPut(tpname, (char *) ituple_A, tplength);
	free(ituple_A);
	t1 = wall_clock() - t0;

	fd = fopen("matrix.par.time", "a");
	printf("nXDR chunked: (%s) (%f)sec. P(%d) f(%d) n(%d) ",
			host, t1/1000000, P, G,  N*1);
	if (t1>0) fprintf(fd, " (%f) MFLOPS.\n", (float) N*N*N/t1);
	else fprintf(fd, " MFLOPS: Not measured.\n");
	fclose(fd);
	exit(0);
	return(0);

}
