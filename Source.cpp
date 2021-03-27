/* In cazul mediu statistic, cele 2 metode arata aproximativ aceeasi performanta
In cazul cel mai defavorabil, insa, metoda bottom-up este mai buna pt ca la topDown la fiecare 
inserare va trebui sa parcurg arborele pana la radcina ca maximul sa ajunga in varf
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#include "Profiler.h"

Profiler profiler("temaHeap");

void swap(int* a, int* b)
{
	int aux;
	aux = *a;
	*a = *b;
	*b = aux;

}

void reconstr_heap(int a[], int i , int n, const char* typeComp, const char* typeAsig)
{
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int maxim;

	maxim = i;
	
	if (left <= n && a[left] > a[i])
	{
		profiler.countOperation(typeComp, n);
		maxim = left;
	}
	if (right <= n && a[right] > a[maxim])
	{
		profiler.countOperation(typeComp, n);
		maxim = right;
	}
	if (maxim != i)
	{
		profiler.countOperation(typeAsig, n, 3);
		swap(&a[i], &a[maxim]);
		reconstr_heap(a, maxim, n, "compMedBU", "assMedBU");
	}

}

void constr_heap_bottomUp(int a[], int n, const char* typeComp, const char* typeAsig)
{
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		reconstr_heap(a, i, n, typeComp, typeAsig);
	}
}




void heapify(int a[], int i,int cheie,int n, const char* typeComp, const char* typeAsig)
{
	int parinte;
	if (i == 1) {
		parinte = 0;
	}
	else {
		parinte = round((i / 2.0) - 1);
	}

	while (i > 0 && a[parinte] < cheie)
	{
		profiler.countOperation(typeComp, n);
		profiler.countOperation(typeAsig, n);
		a[i] = a[parinte];
		i = parinte;

		if (i == 1) {
			parinte = 0;
		}
		else {
			parinte = round((i / 2.0) - 1);
		}

	}
	profiler.countOperation(typeAsig, n);
	a[i] = cheie;

}

void topDown(int a[], int n, const char* typeComp, const char* typeAsig)
{
	for (int i = 1; i < n; i++)
	{
		heapify(a, i, a[i], n,typeComp, typeAsig);
	}
}

void heapSort(int a[], int n)
{
	//constr_heap_bottomUp(a, n);

	for (int i = n - 1; i >= 0; i--)
	{
		swap(&a[0], &a[i]);
		reconstr_heap(a, 0, i-1,"compMedBU", "assMedBU");
	}
}


int main()
{
	/*
	int a[] = {1,2,3,4,5};
	int n = 5;
	
	constr_heap_bottomUp(a, n);
	topDown(a, n);
	heapSort(a, n);

	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	*/
	int a[10000];
	int b[10000];
	for (int n = 100; n < 10000; n += 100)
	{
		FillRandomArray(a, n, 0, 50000, true, 0);
		for (int k = 0; k < n; k++)
		{
			b[k] = a[k];
		}
		constr_heap_bottomUp(a, n, "compMedBU", "assMedBU");
		topDown(b, n, "compMedTD", "assMedTD");
	}

	for (int n = 100; n < 1000; n += 100)
	{
		FillRandomArray(a, n, 0, 50000, true, 1);
		for (int k = 0; k < n; k++)
		{
			b[k] = a[k];
		}
		constr_heap_bottomUp(a, n, "compWorseBU", "assWorseBU");
		topDown(b, n, "compWorseTD", "assWorseTD");
	}


	profiler.addSeries("totalEffBU", "compMedBU", "assMedBU");
	profiler.addSeries("totalEffTD", "compMedTD", "assMedTD");

	profiler.createGroup("AsignariMed", "assMedBU", "assMedTD");
	profiler.createGroup("ComparariMed", "compMedBU", "compMedTD");
	profiler.createGroup("totalEffortMed", "totalEffBU", "totalEffTD");

	profiler.addSeries("worseEffBU", "compWorseBU", "assWorseBU");
	profiler.addSeries("worseEffTD", "compWorseTD", "assWorseTD");
	
	profiler.createGroup("AsignariWorse", "assWorseBU", "assWorseTD");
	profiler.createGroup("CompWorse", "compWorseBU", "compWorseTD");
	profiler.createGroup("totalEffortWorse", "worseEffBU", "worseEffTD");
	
	profiler.showReport();

	
	return 0;
}