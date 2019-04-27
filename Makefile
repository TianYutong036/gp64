accounting.o:accounting_sys.cpp account.h budget.h date.h record.h
	g++ -c accounting_sys.cpp
accounting_sys:
	g++ accounting.o -o accounting_sys
	
