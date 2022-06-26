#pragma once

#include <iostream>
#include "IDLLoader.h"
#include "Windows.h"

namespace dlloader
{
	template <class T>
	class DLLoader : public IDLLoader<T>
	{

	private:
		HMODULE			_handle;
		std::string		_pathToLib;
		std::string		_allocClassSymbol;
		std::string		_deleteClassSymbol;

	public:
		DLLoader(std::string const &pathToLib,
			std::string const &allocClassSymbol = "allocator",
			std::string const &deleteClassSymbol = "deleter") :
			_handle(nullptr), _pathToLib(pathToLib),
			_allocClassSymbol(allocClassSymbol), _deleteClassSymbol(deleteClassSymbol)
		{
			if (!_handle)
				DLOpenLib();
		}

		~DLLoader() {
			if (_handle)
				DLCloseLib();
		}
		void DLOpenLib() override
		{
			if (!_handle && !(_handle = LoadLibrary(_pathToLib.c_str()))) {
				std::cerr << "Can't open and load " << _pathToLib << std::endl;
			}
		}

		std::shared_ptr<T> DLGetInstance() override
		{
			using allocClass = T * (*)();    // typedef T* (* allocClass)(void) тип указатель на функцию с параметром (void)                                         
			using deleteClass = void(*)(T *);
			
			if(!_handle)
				return std::shared_ptr<T>(nullptr);

			auto allocFunc = reinterpret_cast<allocClass>(
				GetProcAddress(_handle, _allocClassSymbol.c_str()));
			auto deleteFunc = reinterpret_cast<deleteClass>(
				GetProcAddress(_handle, _deleteClassSymbol.c_str()));

			if (!allocFunc || !deleteFunc) {
				DLCloseLib();
				std::cerr << "Can't find allocator or deleter symbol in " << _pathToLib << std::endl;
			}

			return std::shared_ptr<T>(
				allocFunc(),
				[deleteFunc](T *p) { deleteFunc(p); });
		}

		void DLCloseLib() override
		{
			if (_handle && FreeLibrary(_handle) == 0) {
				std::cerr << "Can't close " << _pathToLib << std::endl;
			}
			_handle = nullptr;
		}

	};

}