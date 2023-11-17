#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include<stdio.h>
#include <string.h>

int main(int argc, char ** argv)
{
	pid_t p,f1;
	p = getpid();

	int pfd[2];
	size_t sz = argc;

	char** arr1 = new  char *[sz];
	char* arr2[sz];

	bool nextArg = false;

	for (size_t i =0; i<sz ; i++){
		if (strcmp(argv[i],"'\'" )) break;
		if (strcmp(argv[i],"|"))
		{
			nextArg = true;
			break;
		}
		if(!nextArg) {
			 arr1[i]  = argv[i];
		}
		else {
			arr2[i]=argv[i];
		}
	}


	if (pipe (pfd) == -1) {
		perror ("pipe");
		exit (1);
	}
	if ( (f1 = fork ( )) == -1 ){
		perror ("fork");
		exit (2);
	}

	if (f1 == 0) { /* fils */
		dup2(pfd[1],STDOUT_FILENO);
		close (pfd[1]); close (pfd[0]);
		if (execv (argv[1], arr1) == -1) {
			perror ("execv"); exit (3);
		}
	}
	else { /* père */
		dup2(pfd[0],STDIN_FILENO);
		close (pfd[0]);
		close (pfd[1]);
		if (execv (arr2[0], arr2) == -1) {
			perror ("execv"); exit (3);
		}
	}
	return 0;

}
