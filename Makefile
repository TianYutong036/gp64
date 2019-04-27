date.o:date.cpp date.h
	g++ -c date.cpp
	
accounting:accounting_sys.cpp date.o record.h budget.h account.h
	g++ accounting_sys.cpp date.o -o accounting
