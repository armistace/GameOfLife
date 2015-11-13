#
#
#game of life makefile
#
#

life: core/cell.cpp core/cellArray.cpp core/functions.cpp cli/main.cpp Makefile
	g++  -Wall -std=c++14 -v -ggdb3 core/cellArray.cpp core/cell.cpp core/functions.cpp cli/main.cpp -o life-cli -lncurses
