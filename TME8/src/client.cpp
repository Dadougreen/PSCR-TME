#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define PORTSERV 6993
#define h_addr h_addr_list[0] /* definition du champs h_addr */

int main(int argc, char *argv[]) {
	struct sockaddr_in dest; /* Nom du serveur */

	int sock;
	int fromlen = sizeof(dest);
	int msg;
	int reponse;
	if (argc != 2) {
		fprintf(stderr, "Usage : %s machine\n", argv[0]);
		exit(1);
	}
	if ((sock = socket(AF_INET,SOCK_STREAM,0)) == -1) {
		perror("socket");
		exit(1);
	}
	/* remplir la structure dest */
	dest.sin_port = htons(PORTSERV);
	dest.sin_addr.s_addr = INADDR_ANY;
	dest.sin_family = AF_INET;

	/* Etablir la connexion */
	if (connect(sock, (struct sockaddr *) &dest, sizeof(dest)) == -1) {
		perror("connect"); exit(1);
	}
	msg = 2;
	/* Envoyer le message (un entier ici )*/
	if (write(sock,&msg,sizeof(msg)) == -1) {
		perror("write"); exit(1);
	}
	/* Recevoir la reponse */
	if (read(sock,&reponse,sizeof(reponse)) == -1) {
		perror("recvfrom"); exit(1);
	}
	printf("Reponse : %d\n", reponse);
	/* Fermer la connexion */
	shutdown(sock,2);
	close(sock);
	return(0);
}

