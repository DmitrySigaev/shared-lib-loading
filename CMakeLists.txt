cmake_minimum_required(VERSION 3.9)  	# Проверка версии CMake.
					# Если версия установленой программы
					# старее указаной, произайдёт аварийный выход.
project(SharedLib-Core)                 # Название проекта

set(CMAKE_CXX_STANDARD 17)

### Output directory ###
set(CMAKE_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/Core/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIR})

## Sources ##
if (WIN32)
        # Установка переменной со списком исходников для исполняемого файла windows
	set(DLLOADER_SRC
		Core/DLLoader/Windows/DLLoader.h
	)
	
	include_directories(
		Core/DLLoader/Windows/
	)
add_compile_definitions(_HAS_STD_BYTE=0)
endif(WIN32)

if(UNIX)
        # Установка переменной со списком исходников для исполняемого файла linux
	set(DLLOADER_SRC
		Core/DLLoader/Unix/DLLoader.h
	)

	include_directories(
		Core/DLLoader/Unix/
	)

    set (CMAKE_CXX_FLAGS "-W -Wall -Wextra")
endif(UNIX)

include_directories(
    Core/header/
	Core/DLLoader/
	API/
)
# Создает исполняемый файл с именем Use-Shared-Core
add_executable(Use-Shared-Core
	${DLLOADER_SRC}
	Core/main.cpp
	Core/cpp/EnvVariablesImporter.cpp
    Core/cpp/Logger.cpp
)

target_link_libraries(Use-Shared-Core ${CMAKE_DL_LIBS})    	# Линковка программы с библиотеками  CMAKE_DL_LIBS ${CMAKE_DL_LIBS} So, for any target that links with a library that uses dlopen

set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT SharedLib-Core)

add_subdirectory(Libraries/LibVersion001)  # path к shared библиотеке 1
add_subdirectory(Libraries/LibVersion002)  # path к shared библиотеке 2 с новой функциональностью