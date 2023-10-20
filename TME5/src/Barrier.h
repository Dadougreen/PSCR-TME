#pragma once

#include "Pool.h"

#include <vector>
#include <thread>

namespace pr {

class Barrier {
	Pool p;

	public:
	Barrier() : p() {};
	int todo (nbJob)
	{
		for(int i =0 ; i<nbJob; i=i+1)
		{
			p.submit(new Job())
		}
	}
	~Barrier();
};

}
