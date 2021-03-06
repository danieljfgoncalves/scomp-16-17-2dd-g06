/*
 * Renato Oliveira > 1140822@isep.ipp.pt
 * SCOMP - Turma 2DD
 * 
 * main.c
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include "redirect_file_descriptor.h"
#include "create_childs.h"



const int READ =0;
const int WRITE =1;
const int NUMBEROFCHILDS=3;


/*
 * PL 2 - Exercise 17
 */
int main(void)
{
	
	int index_processo;
	int fd[2][2]; 			// dois pipes: fd[2][2]
	
	
	if((pipe(fd[0]) == -1 )| (pipe(fd[1]) == -1))	// ERRO AO CRIAR PIPE
	{
		perror("pipe failed.\n");
		return -1; 
	}
	index_processo = create_childs(NUMBEROFCHILDS);
	
	
	if (index_processo == 0) 	// PROCESSO PAI
	{		
		close(fd[0][READ]);
		close(fd[1][READ]);
		close(fd[0][WRITE]);
		close(fd[1][WRITE]);
		// Esperar que o filho acabe (BOA PRÁTICA)
		wait(NULL);
		wait(NULL);
	} 
	else 				// PROCESSO FILHO
	{
		switch (index_processo)
		{
			case 1:
				
				close(fd[0][READ]);
				close(fd[1][READ]);
				close(fd[1][WRITE]);
				redirect_file_descriptor(fd[0][WRITE],STDOUT_FILENO);
				execl("/bin/ls","ls","-la",(char*)NULL);
				break;
			case 2:
				close(fd[1][READ]);
				close(fd[0][WRITE]);
				redirect_file_descriptor(fd[0][READ],STDIN_FILENO);
				redirect_file_descriptor(fd[1][WRITE],STDOUT_FILENO);    
				execl("/bin/sort","sort",(char*)NULL);
				break;
			case 3:
			   close(fd[0][READ]);
			   close(fd[0][WRITE]);
			   close(fd[1][WRITE]);
			   redirect_file_descriptor(fd[1][READ],STDIN_FILENO);
			   execl("/bin/wc","wc","-l",(char*)NULL);
			   break;
		}
	}
	return 0;
}
