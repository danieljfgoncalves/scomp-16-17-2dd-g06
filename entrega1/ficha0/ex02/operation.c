/*
 * Daniel Goncalves > 1151452@isep.ipp.pt
 * SCOMP - Turma 2DD
 * 
 * operation.c
 * 
 */
#include <stdio.h>
#include <stdlib.h>

/*
 * Usando aritmética de apontadores, implemente uma função que recebendo 
 * como parâmetros o endereço de um vector de inteiros, o seu número de 
 * elementos e um determinado valor, subtraia esse valor a todos os 
 * elementos do vector.
 */
void operation( int* vec, unsigned int size, int x)
{
	unsigned int i;
	for (i = 0; i < size; i++)
	{
		*(vec + i) = *(vec + i) - x;
	}
}
