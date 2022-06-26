#include "StatVersion002.h"

#if defined(__linux__) || defined(__APPLE__)
extern "C"
{
	StatVersion002 *allocator()
	{
		return new StatVersion002();
	}

	void deleter(StatVersion002 *ptr)
	{
		delete ptr;
	}
}
#endif

#ifdef WIN32
extern "C"
{
	__declspec (dllexport) StatVersion002 *allocator()
	{
		return new StatVersion002();
	}

	__declspec (dllexport) void deleter(StatVersion002 *ptr)
	{
		delete ptr;
	}
}
#endif

void StatVersion002::ShowStats()
{
	std::cout << "I'm the second version class with new functionality !" << std::endl;
}

void StatVersion002::NewFunctionality()
{
	std::cout << "This is what I can do after upgrade !" << std::endl;
}