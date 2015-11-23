#
#
#game of life makefile
#
#

life-cli: core/cell.cpp core/cellArray.cpp core/functions.cpp cli/cli_functions.cpp cli/main.cpp Makefile
	g++  -Wall -std=c++14 -v -ggdb3 core/cellArray.cpp core/cell.cpp core/functions.cpp cli/cli_functions.cpp cli/main.cpp -o life-cli -lncurses

life-gtk: core/cell.cpp core/cellArray.cpp core/functions.cpp gtkmm/gtk_functions.cpp gtkmm/main.cpp Makefile
	g++  -Wall -std=c++14 -v -ggdb3 core/cellArray.cpp core/cell.cpp core/functions.cpp gtkmm/gtk_functions.cpp gtkmm/main.cpp -o life-gtk -lncurses

