#include <cstdio>
#include <cstring>
#include <cstdlib>

#define capacity		100
#define base			1000000000
#define base_bit		30

inline int sgn(int key)
{
	if (key > 0) return 1;
	if (key < 0) return -1;
	if (key == 0) return 0;
}

inline int abs(int key)
{
	return (key < 0) ? -key : key;
}

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

	unsigned_BigInt(long long key) : len(0)
	{
		for (; key > 0; key /= base)
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

struct signed_BigInt
{
	unsigned_BigInt data;
	int sign;
	signed_BigInt() : data(0), sign(0) {}
	signed_BigInt(const signed_BigInt &source) : sign(source.sign)
	{
		data = source.data;
	}
	signed_BigInt(int key) : sign(sgn(key)), data(abs(key)) {}
	signed_BigInt & operator = (const signed_BigInt &key)
	{
		sign = key.sign;
		data = key.data;
		return *this;
	}
	int & operator [] (int Index) { return data[Index]; }
	int operator [] (int Index) const { return data[Index]; }
};

inline int compare(const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt operator + (const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt operator - (const signed_BigInt &A);

signed_BigInt operator - (const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt operator * (const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt operator / (const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt operator % (const signed_BigInt &A, const signed_BigInt &B);


const unsigned_BigInt unsigned_Zero = 0;
const unsigned_BigInt unsigned_One = 1;

const signed_BigInt Zero = 0;
const signed_BigInt One = 1;
const signed_BigInt Minus_One = -1;

