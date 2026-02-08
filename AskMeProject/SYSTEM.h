#ifndef SYSTEM_H_
#define SYSTEM_H_
#include"Backend.h"
#include "Frontend.h"


class SYSTEM
{
public:

	SYSTEM();
	void Run();

private:
	Backend Boptimizer;
	Frontend Foptimizer;

};

#endif