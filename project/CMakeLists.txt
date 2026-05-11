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
src/assemble/hextool.cpp
src/assemble/dectool.cpp
src/assemble/vect_writer.cpp

)

set (COMPILER_SOURCES

src/compiler/compiler.cpp
src/compiler/lexer/lexer.cpp
src/compiler/token.cpp

)


add_executable(tsmc src/main.cpp)

target_sources(tsmc
	PRIVATE
		${MENU_SOURCES}
		${ASSEMBLE_SOURCES}
		${COMPILER_SOURCES}
)

