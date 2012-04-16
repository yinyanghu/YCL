all:			BigInt.o BigInt_Extend.o

BigInt.o:		BigInt.cpp BigInt.h
	g++ BigInt.cpp -c

BigInt_Extend.o:	BigInt_Extend.cpp BigInt_Extend.h	
	g++ BigInt_Extend.cpp -c

clean:
	rm *.o
