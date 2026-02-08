#ifndef SYSTEM_
#define SYSTEM_
#include"Backend.h"
#include "Frontend.h"
class System
{

public:

	void Run();
	System() :Foptimizer(Boptimizer) {}




private:

	Backend Boptimizer;
	Frontend Foptimizer;

};

#endif