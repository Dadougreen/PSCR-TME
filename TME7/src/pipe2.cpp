#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include<stdio.h>
#include <string.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define N 10
#define M 5

using namespace std;

int main(int argc, char ** argv) {

	vector<sem_t> sems;
	for (int i =0; i<N; i++){
		sem_t * s = sem_open("/"+ to_string(i);
		O_CREAT|O_EXCL|O_RDWR, 0600, i==0);
	}
	return 0;
}


