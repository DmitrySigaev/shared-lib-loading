#include "StatVersion001.h"

#if defined(__linux__) || defined(__APPLE__)
extern "C"
{
	StatVersion001 *allocator()
	{
		return new StatVersion001();
	}

	void deleter(StatVersion001 *ptr)
	{
		delete ptr;
	}
}
#endif

#ifdef WIN32
extern "C"
{
	__declspec (dllexport) StatVersion001 *allocator()
	{
		return new StatVersion001();
	}

	__declspec (dllexport) void deleter(StatVersion001 *ptr)
	{
		delete ptr;
	}
}
#endif

void StatVersion001::ShowStats()
{
	std::cout << "I'm the first version class !" << std::endl;
}