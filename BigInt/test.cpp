#include "BigInt_Extend.h"

using namespace std;


int main()
{

	unsigned_BigInt A, B;
	A = unsigned_read();
	B = unsigned_read();

	unsigned_BigInt C;

	C = A + B;
	C.print();
	printf("\n");

	C = A - B;
	C.print();
	printf("\n");

	C = A * B;
	C.print();
	printf("\n");

	C = A / B;
	C.print();
	printf("\n");

	
	C = A % B;
	C.print();
	printf("\n");

	signed_BigInt a, b;
	a = signed_read();
	b = signed_read();

	//a.print();
	//printf("\n");
	//b.print();
	//printf("\n");
	signed_BigInt c;

	c = a + b;
	c.print();
	printf("\n");

	c = a - b;
	c.print();
	printf("\n");

	c = a * b;
	c.print();
	printf("\n");

	c = a / b;
	c.print();
	printf("\n");

	c = a % b;
	c.print();
	printf("\n");
	return 0;
}
