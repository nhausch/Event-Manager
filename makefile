MAEXE : MA.o Date.o Event.o Activity.o
	g++ -Wall MA.o Date.o Event.o Activity.o -o MAEXE

MA.o : Date.h MA.cpp Event.h Activity.h
	g++ -Wall -c MA.cpp

Date.o : Date.h Date.cpp
	g++ -Wall -c Date.cpp

Event.o : Event.h Event.cpp Date.h
	g++ -Wall -c Event.cpp

Activity.o : Activity.h Activity.cpp Date.h Event.h
	g++ -Wall -c Activity.cpp