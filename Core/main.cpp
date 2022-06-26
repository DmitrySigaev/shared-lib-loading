#include <iostream>
#include <string>
#include <memory>
#include <Logger.h>
#include "DLLoader.h"
#include "ishared.h"
#include "EnvVariablesImporter.h"

using namespace std;
#define MAIN_CLASS_NAME "Main"



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

int main(int argc, char* argv[])
{

	RunLibary(dllLibPathToV1);
	RunLibary(dllLibPathToV2);

	dlloader::DLLoader<ishared> dlloader(dllLibPathToV2);
	auto version = dlloader.DLGetInstance();
	version->ShowStats();

	Logger::init();

	Logger::info("Sleeping for 15 sec"); // waiting for old pods to disconnect

	Logger::info("Start application", MAIN_CLASS_NAME);

	// env variables
	if (argc == 2) {
		EnvVariablesImporter::load(argv[1]);
	}
	else if (argc == 3) {
		EnvVariablesImporter::load(argv[1], argv[2]);
	}
	else {
		Logger::info("Expected at least 1 argument: path to a dir with app*.property files and (optional) environment name.",
			MAIN_CLASS_NAME);
		return 1;
	}

	Logger::info("Properties: \n" + EnvVariablesImporter::get_all_values_as_string(), MAIN_CLASS_NAME);

	Logger::info("Init video transcoder", MAIN_CLASS_NAME);

	return 0;
}