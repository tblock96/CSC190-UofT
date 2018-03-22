#include "assignment2.h"

void denseMatrixMult(int ** A, int ** B, int *** resultMatrix, int n) {
	int **m0, **m1, **m2, **m3, **m4, **m5, **m6;
	int **c00, **c01, **c10, **c11;
	int **tmp1, **tmp2;
	// initialize at the top level only.
	if(n==MATSIZE) initMatrix(resultMatrix, n);
	// Check the base case
	/*TODO Add edge cases (n%2!=0 etc.)
 *
 * 	*/
 	if(n==1) *resultMatrix[0][0]=A[0][0]*B[0][0];
	else {
		// Initialize m0 - m6
		initMatrix(&m0,n/2);
		initMatrix(&m1,n/2);
		initMatrix(&m2,n/2);
		initMatrix(&m3,n/2);
		initMatrix(&m4,n/2);
		initMatrix(&m5,n/2);
		initMatrix(&m6,n/2);
		tmp1=sum(A,A,0,0,n/2,n/2,n/2);
		tmp2=sum(B,B,0,0,n/2,n/2,n/2);
		denseMatrixMult(tmp1,tmp2,&m0,n/2);
		freeMatrices(n/2, tmp1, tmp2);
		tmp1=sum(A,A,n/2,0,n/2,n/2,n/2);
		tmp2=sum(m1,B,0,0,0,0,n/2);
		denseMatrixMult(tmp1,tmp2,&m1,n/2);
		freeMatrices(n/2, tmp1, tmp2);
		tmp1=sum(m2,A,0,0,0,0,n/2);
		tmp2=sub(B,B,0,n/2,n/2,n/2,n/2);
		denseMatrixMult(tmp1,tmp2,&m2,n/2);
		freeMatrices(n/2, tmp1, tmp2);
		tmp1=sum(m3,A,0,0,n/2,n/2,n/2);
		tmp2=sub(B,B,n/2,0,0,0,n/2);
		denseMatrixMult(tmp1,tmp2,&m3,n/2);
		freeMatrices(n/2, tmp1, tmp2);
		tmp1=sum(A,A,0,0,0,n/2,n/2);
		tmp2=sum(m4,B,0,0,n/2,n/2,n/2);
		denseMatrixMult(tmp1,tmp2,&m4,n/2);
		freeMatrices(n/2, tmp1, tmp2);
		tmp1=sub(A,A,n/2,0,0,0,n/2);
		tmp2=sum(B,B,0,0,0,n/2,n/2);
		denseMatrixMult(tmp1,tmp2,&m5,n/2);
		freeMatrices(n/2,tmp1,tmp2);
		tmp1=sub(A,A,0,n/2,n/2,n/2,n/2);
		tmp2=sum(B,B,n/2,0,n/2,n/2,n/2);
		denseMatrixMult(tmp1,tmp2,&m6,n/2);
		freeMatrices(n/2,tmp1,tmp2);
		// Add the above matrices to get partitions of C
		tmp1= sum(m3, m6, 0, 0,0,0,n/2);
		tmp2= sum(m0, tmp1,0,0,0,0,n/2);
		c00 = sub(tmp2,m4,0,0,0,0,n/2);
		freeMatrices(n/2,tmp1,tmp2);
		c01 = sum(m2, m4, 0,0,0,0,n/2);
		c10 = sum(m1, m3, 0,0,0,0,n/2);
		tmp1= sum(m2,m5,0,0,0,0,n/2);
		tmp2= sum(m0,tmp1,0,0,0,0,n/2);
		c11 = sub(tmp2,m1,0,0,0,0,n/2);
		freeMatrices(n/2,tmp1,tmp2);
		composeMatrix(c00,c01,c10,c11,resultMatrix,n);		
		// Free m0 - m6, c matrices
		freeMatrix(n/2, m0);
		freeMatrix(n/2, m1);
		freeMatrix(n/2, m2);
		freeMatrix(n/2, m3);
		freeMatrix(n/2, m4);
		freeMatrix(n/2, m5);
		freeMatrix(n/2, m6);
		freeMatrix(n/2, c00);
		freeMatrix(n/2, c01);
		freeMatrix(n/2, c10);
		freeMatrix(n/2, c11);
	}
}

void freeMatrices(int n, int **mat1, int **mat2) {
	freeMatrix(n, mat1); freeMatrix(n,mat2);
}

void composeMatrix(int **c00, int **c01, int **c10, int **c11, int ***rM, int n) {
	int i, j;
	for(i=0;i<n/2;i++) {
		for(j=0;j<n/2;j++) { 
			(*rM)[i][j] = c00[i][j];
			(*rM)[i+n/2][j] = c10[i][j];
			(*rM)[i][j+n/2] = c01[i][j];
			(*rM)[i+n/2][j+n/2] = c11[i][j];
		}
	}
}

int **sum(int ** A, int ** B, int x1, int y1, int x2, int y2, int n) {
	int i, j, count, x, y, **mat, **C;
	//Dynamically allocate a new n*n matrix
	initMatrix(&C, n);
	//Switch statement for which matrix to add
	for(count=0;count<2;count++) {
		if(count == 0){ mat=A;x=x1;y=y1;}
		else if(count == 1) {mat=B;x=x2;y=y2;}
		else printf("ERROR: counter failed\n");
	//Add values from the switch matrix to the C matrix
		for(i=0;i<n;i++) {
			for(j=0;j<n;j++) 
				C[i][j] += mat[i+x][j+y];
		}
	} return C;
}

int **sub(int **A, int **B, int x1, int y1, int x2, int y2, int n) {
	int i, j, **C, **tmp;
	//Dynamically allocate a new n*n matrix
	initMatrix(&tmp, n);
	//Add A to C
	C = sum(tmp, A, 0, 0, x1, y1, n);
	//free tmp
	freeMatrix(n, tmp);
	//Subtract B from C
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			C[i][j] -= B[i+x2][j+y2];
	} return C;
}
	
void initMatrix(int ***mat, int n) {
	int i, j;
	*mat =(int**)malloc(n*sizeof(int*));
	if(*mat==NULL) printf("ALLOCATION ERROR");
	for(i=0;i<n;i++) {
		(*mat)[i] = (int*)malloc(n*sizeof(int));
		if((*mat)[i]==NULL) printf("ALLOCATION ERROR\n");
		for(j=0;j<n;j++) (*mat)[i][j]=0;
	}
}

int **readMatrix(char * filename) {
	int i, j, **tmp;
	FILE *fp = fopen(filename, "r");
	if(fp==NULL) printf("ERROR: %s could not be opened.\n", filename);
	tmp = (int**)malloc(MATSIZE*sizeof(int*));
	for(i=0;i<MATSIZE;i++) {
		tmp[i] = (int*)malloc(MATSIZE*sizeof(int));
		for(j=0;j<MATSIZE;j++)
			fscanf(fp,"%d",&tmp[i][j]);
	}
	return tmp;
}

void freeMatrix(int n, int ** matrix) {
	int i;
	for(i=0;i<n;i++) {
		free(matrix[i]);
	} free(matrix);
}

void printMatrix(int n, int ** A) {
	int i,j;
	for(i=0;i<n;i++) {
		for(j=0;j<n;j++) {
			printf("%d ", A[i][j]);
		} printf("\n");
	}
}
