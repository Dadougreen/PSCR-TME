#include <iostream>
#include <unistd.h>
#include <vector>
#include <sys/wait.h>
#include "rsleep.h"

int vie = 3;

static void recevoirDegat(int)
{
	vie -= 1;
	if(vie==0)
	{
		std::cout<<"processus ce termine" << getpid() << std::endl;
		exit(1);
	}
	else
	{
		std::cout<<"vie restante : " << vie << std::endl;
		exit(0);
	}
}

void attaque(pid_t adversaire){
	struct sigaction sa = {0};
	sa.sa_handler = &recevoirDegat;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);

	if(kill(adversaire,SIGINT)==-1)// pv = 0 mort
	{
		exit(0);
	}
	randsleep();
}

void defense()
{
	signal(SIGINT, SIG_IGN);
	randsleep();
}

void combat(pid_t adversaire)
{
	while(1)
	{
		defense();
		attaque(adversaire);
	}
}

int main () {

	int pidL = fork();

	if(pidL==0) // fils L
	{
		int pidV = fork();

		combat(pidV);
	}

	return 0;
}


/*
int main () { //EXO 1-2


	const int N = 3;
	int nbfils = 0; //EXO 1 : 10 processus (1 pere + 9fils)
	std::cout << "main pid=" << getpid() << std::endl;

	for (int i=1, j=N; i<=N && j==N && fork()==0 ; i++ ) {
		std::cout << " i:j " << i << ":" << j << std::endl;
		for (int k=1; k<=i && j==N ; k++) {
			nbfils+=1;
			pid_t pidj = fork();
			if (pidj == 0) { //fils
				j=0;
				std::cout << " k:j " << k << ":" << j << std::endl;
			}
			else //pere
			{
				for(int m=0; m<nbfils ; m++)
					{
						if(wait(NULL)==-1)
						{
							std::cout<<"Trop de wait de" <<getpid()<<std::endl;
							break;
						}
					}
					if(wait(NULL)!=-1)
					{
						std::cout<<"Il en reste"<<std::endl;
					}

			}

		}
	}

	return 0;
}
*/

