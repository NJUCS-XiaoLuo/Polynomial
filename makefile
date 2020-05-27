main:main.o UI.h UI.o Poly_Manage.h Poly_Manage.o Polynomial.h Polynomial.o
	g++ -g UI.h UI.o Poly_Manage.h Poly_Manage.o Polynomial.h Polynomial.o main.o -o main

main.o: main.cpp
	g++ -c  -g main.cpp
UI.o:UI.cpp
	g++ -c -g UI.cpp
Poly_Manage.o:Poly_Manage.cpp
	g++ -c -g Poly_Manage.cpp
Polynomial.o:Polynomial.cpp
	g++ -c -g Polynomial.cpp
clean:
	rm *.o
	rm main