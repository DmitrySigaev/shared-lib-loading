cmake_minimum_required(VERSION 3.9)  	# �������� ������ CMake.
					# ���� ������ ������������ ���������
					# ������ ��������, ��������� ��������� �����.
project(SharedLib-Core)                 # �������� �������

set(CMAKE_CXX_STANDARD 17)

### Output directory ###
set(CMAKE_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/Core/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIR})

## Sources ##
if (WIN32)
        # ��������� ���������� �� ������� ���������� ��� ������������ ����� windows
	set(DLLOADER_SRC
		Core/DLLoader/Windows/DLLoader.h
	)
	
	include_directories(
		Core/DLLoader/Windows/
	)
add_compile_definitions(_HAS_STD_BYTE=0)
endif(WIN32)

if(UNIX)
        # ��������� ���������� �� ������� ���������� ��� ������������ ����� linux
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
# ������� ����������� ���� � ������ Use-Shared-Core
add_executable(Use-Shared-Core
	${DLLOADER_SRC}
	Core/main.cpp
	Core/cpp/EnvVariablesImporter.cpp
    Core/cpp/Logger.cpp
)

target_link_libraries(Use-Shared-Core ${CMAKE_DL_LIBS})    	# �������� ��������� � ������������  CMAKE_DL_LIBS ${CMAKE_DL_LIBS} So, for any target that links with a library that uses dlopen

set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT SharedLib-Core)

add_subdirectory(Libraries/LibVersion001)  # path � shared ���������� 1
add_subdirectory(Libraries/LibVersion002)  # path � shared ���������� 2 � ����� �����������������