#include<stdlib.h>
#include<stdio.h>
#define MATSIZE 8

void freeMatrix(int n, int ** matrix);
int readMatrixSize(char * filename);
int **readMatrix(char * filename);
void denseMatrixMult(int **matrix1, int **matrix2, int ***resultMatrix, int n);
void initMatrix(int ***matrix, int n);
int **sum(int ** A, int ** B, int x1, int y1, int x2, int y2, int n);
int **sub(int ** A, int ** B, int x1, int y1, int x2, int y2, int n);
void printMatrix(int n, int ** A);
void composeMatrix(int **c00, int **c01, int **c10, int **c11, int ***rM, int n);
void freeMatrices(int n, int **mat1, int **mat2);
void printAllMs(int n, int **m[]);
