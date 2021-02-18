qslab: main.cpp QS.h QS.cpp 
	g++ -std=c++11 -o qslab main.cpp QS.cpp
win: main.cpp QS.h QS.cpp
	cl /EHsc main.cpp QS.cpp
