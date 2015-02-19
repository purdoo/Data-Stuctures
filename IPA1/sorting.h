#ifndef SORTING_H
#define SORTING_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

long *Load_File(char *Filename, int *Size);
int Save_File(char *Filename, long *Array, int Size);
void Shell_Insertion_Sort(long *Array, int Size, double *N_Comp, double *N_Move);
void Shell_Selection_Sort(long *Array, int Size, double *N_Comp, double *N_Move);
int Print_Seq(char *Filename, int Size);
int *Gen_Seq(int Size);

#endif
