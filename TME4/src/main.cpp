#include "Banque.h"
#include "Compte.h"
#include <chrono>
#include <iostream>

using namespace std;

const int NB_THREAD = 10;
using namespace pr ;

int main () {
	vector<thread> threads;
	threads.reserve(NB_THREAD);
	Banque banque(NB_THREAD,110);
	// TODO : creer des threads qui font ce qui est demandé

	for(int k=0; k< NB_THREAD ; k=k+1)
	{
		size_t i,j = rand()%banque.size();
		size_t m = rand()%100+1;
		threads.emplace_back(&Banque::transfert,&banque,i,j,m);

	}


	for (auto & t : threads) {
				t.join();
			}



	for (size_t i=0; i<threads.size(); ++i) {
		int sleep = rand()%20;
		std::this_thread::sleep_for (std::chrono::milliseconds(sleep));

	}

	//Question 2 :
	//On verifie si aucune somme n'a été perdu apres les transferts
	//banque.comptabiliser(NB_THREAD*110);

	//Question 4 :
	//On utilise Lock() avant d'effectuer le debit et avant de crediter un compte
	//et ensuite UnLock() apres avoir realiser le debit ou le credit (donc dans debiter(),crediter())

	return 0;
}
