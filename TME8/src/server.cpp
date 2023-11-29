
//g++ -Wall -g -O0 server.cpp -o server
//g++ -Wall -g -O0 client.cpp -o client
// ./client localhost
// ./server


#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

#define PORTSERV 6993
#define LIST 0
#define UP 1
#define DOWN 2
#define EXIT 3

using namespace std;
int main(int argc, char *argv[]) {
	struct sockaddr_in sin; /* Nom de la socket de connexion */
	struct sockaddr_in exp;
	int sc ; /* Socket de connexion */
	int scom; /* Socket de communication */
	struct hostent *hp;
	unsigned int fromlen = sizeof(exp);
	char buff;
	int fd[2]; //#0 lire, 1 ecrire;

	/* creation de la socket */

	if ((sc = socket(AF_INET,SOCK_STREAM,0)) < 0) {
		perror("socket"); exit(1);
	}

	memset((char *)&sin,0, sizeof(sin));
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(PORTSERV);
	sin.sin_family = AF_INET;

	/* nommage */

	if (bind(sc,(struct sockaddr *)&sin,sizeof(sin)) < 0) {
		perror("bind");
		exit(1);
	}

	listen(sc, 5);

/* Boucle principale */
	for (;;) {
		if ((scom = accept(sc, (struct sockaddr *)&exp, &fromlen))== -1) {
			perror("accept"); exit(3);
			}
		// recu connection de exp

		/* Création d'un processus fils qui traite la requete */
//		if (fork() == 0) {
			/* Processus fils */

			if (read(scom,&buff, sizeof(buff)) < 0) {
				perror("read"); exit(4);
				}

			/*** Traitement du message ***/
			switch(buff) {
			  case LIST:
			    // code block
				  cout<<"LIST"<<endl;
			    break;
			  case UP:
			    // code block
				  cout<<"UP"<<endl;
			    break;
			  case DOWN:
			  	//dup2(scom.(socket::GetFd()),fd[1]);
				  cout<<"DOWN"<<endl;
			  	break;
			  case EXIT:
			  	// code block
				  cout<<"EXIT"<<endl;
			  	break;

			  default:
				  perror("decode mauvais signal"); exit(69);
			}
			/*
			if (write(scom, &cpt, sizeof(cpt)) == -1) {
				perror("write"); exit(2);
			}*/

			/* Fermer la communication */
			shutdown(scom,2);
			close(scom);
			exit(0);
		//}
	} /* Fin de la boucle for */
	close(sc);
	return 0;
}
