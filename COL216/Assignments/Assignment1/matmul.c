#include <stdio.h>

#define N 128
int a[N][N];
int b[N][N];
int c[N][N];

void initMat1(){
	int i,j;
	for (i=0; i<N; i++){
		for(j=0; j< N; j++){
			a[i][j] = (i + j)%17 ;
		}
	}
}

void initMat2(){
	int i,j;
	for (i=0; i<N; i++){
		for(j=0; j< N; j++){
			b[i][j] = (i - j + 64)%6 + (i * j)% 8;
		}
	}
}

void matMul(){
	int i,j,k,sum;
	for (i=0; i<N; i++){
		for(j=0; j< N; j++){
			sum = 0;
			for(k=0; k< N; k++){
				sum += a[i][k] * b[k][j];
			}
			c[i][j] = sum;
		}
	}
}

int matSum(){
	int i,j,sum;
	sum = 0;
	for (i=0; i<N; i++)
		for(j=0; j< N; j++)
			sum += c[i][j];
	return sum;
}

void main(){
	initMat1();
	initMat2();
	matMul();
	int val = matSum();
	printf("Sum is %d\n",val);
}



















