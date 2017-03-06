/*
 * Daniel Goncalves > 1151452@isep.ipp.pt
 * SCOMP - Turma 2DD
 * 
 * main.c
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/*
 * PL 1 - Exercise 4h
 */
int main(void)
{
	pid_t pid;
	int f, status;
	
	for (f = 0; f < 3; f++)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("Erro ao criar filho.\n");
			exit(-1);
		}
		
		if (pid > 0)
		{
			printf("Eu sou o PAI\n");
			if (f == 1)
			{
				// Waits for child
				waitpid(pid, &status, WNOHANG);
			}
		}
		else
		{
			// Numero de ordem (f + 1).
			exit(f+1);
		}
	}

	return 0;
}
