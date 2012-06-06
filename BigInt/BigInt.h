#ifndef	__CSTDIO__
#define __CSTDIO__
#include <cstdio>
#endif

#ifndef	__CSTRING__
#define __CSTRING__
#include <cstring>
#endif

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X,Y) ((X) < (Y) ? (Y) : (X))
#define ABS(X) ((X) < 0 ? (-X) : (X))
#define SGN(X) ((X) == 0 ? 0 : (((X) > 0) ? 1 : -1))


#define capacity		100
#define base			1000000000
#define base_bit		30

struct unsigned_BigInt
{
	int len;
	int __data[capacity];
	unsigned_BigInt() : len(0) {}
	unsigned_BigInt(const unsigned_BigInt &source) : len(source.len)
	{
		memcpy(__data, source.__data, len * sizeof *__data);
	}

	unsigned_BigInt(int key) : len(0)
	{
		for (; key > 0; key >>= base_bit)
			__data[len ++] = key % base;
	}

	unsigned_BigInt & operator = (const unsigned_BigInt &key)
	{
		len = key.len;
		memcpy(__data, key.__data, len * sizeof *__data);
		return *this;
	}
	int & operator [] (int Index) { return __data[Index]; }
	int operator [] (int Index) const { return __data[Index]; }

	
	void print()
	{
		if (len == 0)
		{
			printf("0");
			return;
		}
		printf("%d", __data[len - 1]);
		for (int i = len - 2; i >= 0; -- i)
			for (int j = base / 10; j > 0; j /= 10)
				printf("%d", __data[i] / j % 10);
	}
};

inline int compare(const unsigned_BigInt &A, const unsigned_BigInt &B);


unsigned_BigInt operator + (const unsigned_BigInt &A, const unsigned_BigInt &B);

unsigned_BigInt operator - (const unsigned_BigInt &A, const unsigned_BigInt &B);

unsigned_BigInt operator * (const unsigned_BigInt &A, const int B);

unsigned_BigInt operator * (const unsigned_BigInt &A, const unsigned_BigInt &B);


unsigned_BigInt operator / (const unsigned_BigInt &A, const int B);

unsigned_BigInt operator % (const unsigned_BigInt &A, const int B);

void divide(const unsigned_BigInt &A, const unsigned_BigInt &B, unsigned_BigInt &Q, unsigned_BigInt &R);

unsigned_BigInt operator / (const unsigned_BigInt &A, const unsigned_BigInt &B);

unsigned_BigInt operator % (const unsigned_BigInt &A, const unsigned_BigInt &B);

unsigned_BigInt unsigned_read(char *s);

struct signed_BigInt
{
	unsigned_BigInt data;
	int sign;
	signed_BigInt() : data(0), sign(0) {}
	signed_BigInt(const signed_BigInt &source) : sign(source.sign)
	{
		data = source.data;
	}
	signed_BigInt(int key) : sign(SGN(key)), data(ABS(key)) {}
	signed_BigInt & operator = (const signed_BigInt &key)
	{
		sign = key.sign;
		data = key.data;
		return *this;
	}
	int & operator [] (int Index) { return data[Index]; }
	int operator [] (int Index) const { return data[Index]; }

	void print()
	{
		if (sign == -1) printf("-");
		data.print();
	}
};

inline int compare(const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt operator + (const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt operator - (const signed_BigInt &A);

signed_BigInt operator - (const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt operator * (const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt operator / (const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt operator % (const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt signed_read(char *s);


const unsigned_BigInt unsigned_Zero = 0;
const unsigned_BigInt unsigned_One = 1;

const signed_BigInt Zero = 0;
const signed_BigInt One = 1;
const signed_BigInt Minus_One = -1;

