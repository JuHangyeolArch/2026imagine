cmake_minimum_required(VERSION 4.3.1)

project(abcasm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

set(MENU_SOURCES src/menu/menu.cpp)
set(ASSEMBLE_SOURCES
src/assemble/assemble.cpp
src/assemble/source_reader.cpp
src/assemble/trimmer.cpp

)


add_executable(abcasm src/main.cpp)

target_sources(abcasm
	PRIVATE
		${MENU_SOURCES}
		${ASSEMBLE_SOURCES}
)

