all:			BigInt.o BigInt_Extend.o

BigInt.o:		BigInt.cpp BigInt.h
	g++ BigInt.cpp -c -O3

BigInt_Extend.o:	BigInt_Extend.cpp BigInt_Extend.h
	g++ BigInt_Extend.cpp -c -O3

debug:	
	g++ BigInt.cpp -g -c
	g++ BigInt_Extend.cpp -g -c

clean:
	rm *.o
	rm a.out
