#pragma once

#include "Queue.h"
#include "Job.h"
#include <vector>
#include <thread>

namespace pr {

class Pool{
	Queue<Job> queue;
	std::vector<std::thread> threads;
public:
	Pool(int qsize) : queue(qsize) {};

	void start(int nbthread){
		threads.reserve(nbthread);
		for (int i = 0; i<nbthread; i++)
		{

			threads.emplace_back(&poolworker, std::ref(queue));

		}
	}
	static void poolworker(Queue<Job> queue){
		while(true){
			Job *j = queue.pop();
			if(j == nullptr) break;
			j -> run();
			delete j;
		}
	}
	void submit(Job *job){
		queue.push(job);
	}

	void stop(){
		queue.setBlocking(false);
		for(size_t i =0; i<threads.size(); i=i+1)
		{
			threads[i].join();
		}
		threads.clear();
	}
	~Pool(){
		stop();
	}
};

}


