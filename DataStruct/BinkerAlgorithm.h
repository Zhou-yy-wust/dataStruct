#pragma once
#ifndef BANKERALGORITHEM_H
#define BANKERALGORITHEM_H
#include<iostream>
#define PROCESS 10
#define SOURCE 5
void Banker_Algorithm(int** , int** , int* , int , int );
void AddMatrix(int** , int** , int** , int , int );
void SubMatrix(int** , int** , int** , int , int );
void AddVector(int*, int*, int*, int);
void SubVector(int*, int*, int*, int);
void Initialize(int**&, int**&, int*&, int, int);
int GetRequestion(int*, int);
bool  IsGreater(int *,int*,int);
bool Security(int **,int**,int*,int,int);
void Delete(int**, int**, int**, int*, int*, int,int);
void print(int**, int n, int m);
void Main();




#endif
