date.o:date.cpp date.h
	g++ -c date.cpp

user.o:user.cpp user.h
	g++ -c user.cpp

accounting:accounting_sys.cpp user.o date.o record.h budget.h account.h
	g++ accounting_sys.cpp user.o date.o -o accounting
