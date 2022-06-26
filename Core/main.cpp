#include <iostream>
#include <string>
#include <memory>
#include "DLLoader.h"
#include "ishared.h"

using namespace std;

#ifdef WIN32
static const std::string dllLibPathToV1 = "LibVersion001.dll";
static const std::string dllLibPathToV2 = "LibVersion002lib.dll";
#endif
#ifdef __linux__
static const std::string dllLibPathToV1 = "./libLibVersion001.so";
static const std::string dllLibPathToV2 = "./libLibVersion002lib.so";
#endif
#ifdef __APPLE__
static const std::string dllLibPathToV1 = "./libLibVersion001.dylib";
static const std::string dllLibPathToV2 = "./libLibVersion002lib.dylib";
#endif

/*
** Using the smart pointer directly in an inner function because
** the reference to its destructor contained in the dll is lost before
** going out of the caller function's scope.
*/
void ShowStats(dlloader::DLLoader<ishared>& dlloader)
{
	std::shared_ptr<ishared> version = dlloader.DLGetInstance();

	if(version)
		version->ShowStats();
}

void RunLibary(const std::string& path)
{
	dlloader::DLLoader<ishared> dlloader(path);

	std::cout << "Loading " << path << std::endl;
	dlloader.DLOpenLib();

	ShowStats(dlloader);

	std::cout << "Unloading " << path << std::endl;
	dlloader.DLCloseLib();
}

int main()
{
	RunLibary(dllLibPathToV1);
	RunLibary(dllLibPathToV2);

	dlloader::DLLoader<ishared> dlloader(dllLibPathToV2);
	auto version = dlloader.DLGetInstance();
	version->ShowStats();
	return 0;
}