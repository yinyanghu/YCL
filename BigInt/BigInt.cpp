#include "BigInt.h"

/****************************************************************
 * Unsigned Big Integer						*
 ****************************************************************/

inline int compare(const unsigned_BigInt &A, const unsigned_BigInt &B)
{
	if (A.len != B.len) return A.len > B.len ? 1 : -1;
	int i;
	for (i = A.len - 1; i >= 0 && A[i] == B[i]; -- i);
	if (i < 0) return 0;
	return A[i] > B[i] ? 1 : -1;
}



unsigned_BigInt operator + (const unsigned_BigInt &A, const unsigned_BigInt &B)
{
	unsigned_BigInt R;
	int i;
	int Carry = 0;
	for (i = 0; i < A.len || i < B.len || Carry > 0; ++ i)
	{
		if (i < A.len) Carry += A[i];
		if (i < B.len) Carry += B[i];
		R[i] = Carry % base;
		Carry /= base;
	}
	R.len = i;
	return R;
	
}

unsigned_BigInt operator - (const unsigned_BigInt &A, const unsigned_BigInt &B)
{
	unsigned_BigInt R;
	int Carry = 0;
	R.len = A.len;
	for (int i = 0; i < R.len; ++ i)
	{
		R[i] = A[i] - Carry;
		if (i < B.len) R[i] -= B[i];
		if (R[i] < 0) Carry = 1, R[i] += base;
		else Carry = 0;
	}
	while (R.len > 0 && R[R.len - 1] == 0) -- R.len;
	return R;
}

unsigned_BigInt operator * (const unsigned_BigInt &A, const int B)
{
	int i;
	if (B == 0) return 0;
	unsigned_BigInt R;
	long long Carry = 0;
	for (i = 0; i < A.len || Carry > 0; ++ i)
	{
		if (i < A.len) Carry += (long long)(A[i]) * B;
		R[i] = Carry % base;
		Carry /= base;
	}
	R.len = i;
	return R;
}

unsigned_BigInt operator * (const unsigned_BigInt &A, const unsigned_BigInt &B)
{
	if (B.len == 0) return 0;
	unsigned_BigInt R;
	for (int i = 0; i < A.len; ++ i)
	{
		long long Carry = 0;
		for (int j = 0; j < B.len || Carry > 0; ++ j)
		{
			if (j < B.len) Carry += (long long)(A[i]) * B[j];
			if (i + j < R.len) Carry += R[i + j];
			if (i + j >= R.len) R[R.len ++] = Carry % base;
			else R[i + j] = Carry % base;
			Carry /= base;
		}
	}
	return R;
}



unsigned_BigInt operator / (const unsigned_BigInt &A, const int B)
{

	unsigned_BigInt R;
	long long C = 0;
	for (int i = A.len - 1; i >= 0; -- i)
	{
		C = C * base + A[i];
		R[i] = C / B;
		C %= B;
	}
	R.len = A.len;
	while (R.len > 0 && R[R.len - 1] == 0) -- R.len;
	return R;

}

unsigned_BigInt operator % (const unsigned_BigInt &A, const int B)
{
	long long C = 0;
	for (int i = A.len - 1; i >= 0; -- i)
	{
		C = C * base + A[i];
		C %= B;
	}
	return C;
}

unsigned_BigInt operator / (const unsigned_BigInt &A, const unsigned_BigInt &B)
{
	if (compare(A, B) < 0) return 0;

	unsigned_BigInt R, Carry = 0;
	int left, right, mid;
	for (int i = A.len - 1; i >= 0; -- i)
	{
		Carry = Carry * base + A[i];

		left = 0;
		right = base;
		while (left + 1 < right)
		{
			mid = (left + right) >> 1;
			if (compare(B * mid , Carry) <= 0)
				left = mid;
			else
				right = mid;
		}
		R[i] = left;
		Carry = Carry - B * left;
	}
	R.len = A.len;
	while (R.len > 0 && R[R.len - 1] == 0) -- R.len;
	return R;

}

unsigned_BigInt operator % (const unsigned_BigInt &A, const unsigned_BigInt &B)
{
	if (compare(A, B) < 0) return A;

	unsigned_BigInt Carry = 0;
	int left, right, mid;
	for (int i = A.len - 1; i >= 0; -- i)
	{
		Carry = Carry * base + A[i];
		
		left = 0;
		right = base;
		while (left + 1 < right)
		{
			mid = (left + right) >> 1;
			if (compare(B * mid, Carry) <= 0)
				left = mid;
			else
				right = mid;
		}
		Carry = Carry - B * left;
	}
	return Carry;

}

unsigned_BigInt unsigned_read()
{
	unsigned_BigInt ret = 0;
	char ch;
	while ((ch = getc(stdin)) > ' ')
		ret = ret * 10 + (int(ch) - int('0'));
	return ret;
}
	








/****************************************************************
 * Signed Big Integer						*
 ****************************************************************/

inline int compare(const signed_BigInt &A, const signed_BigInt &B)
{
	if (A.sign > B.sign) return 1;
	if (A.sign < B.sign) return -1;
	return compare(A.data, B.data);
}

signed_BigInt operator + (const signed_BigInt &A, const signed_BigInt &B)
{
	if (A.sign == 0) return B;
	if (B.sign == 0) return A;
	signed_BigInt R;
	if (A.sign * B.sign == 1)
	{
		R.data = A.data + B.data;
		R.sign = A.sign;
	}
	else if (A.sign == 1)
	{
		int k = compare(A.data, B.data);
		if (k == 1)
		{
			R.sign = 1;
			R.data = A.data - B.data;
		}
		else if (k == 0)
		{
			R.sign = 0;
			R.data = 0;
		}
		else if (k == -1)
		{
			R.sign = -1;
			R.data = B.data - A.data;
		}
	}
	else
	{
		int k = compare(B.data, A.data);
		if (k == 1)
		{
			R.sign = 1;
			R.data = B.data - A.data;
		}
		else if (k == 0)
		{
			R.sign = 0;
			R.data = 0;
		}
		else if (k == -1)
		{
			R.sign = -1;
			R.data = A.data - B.data;
		}
	}
	return R;
}

signed_BigInt operator - (const signed_BigInt &A)
{
	signed_BigInt R;
	R.sign = -A.sign;
	R.data = A.data;
	return R;
}

signed_BigInt operator - (const signed_BigInt &A, const signed_BigInt &B)
{
	if (B.sign == 0) return A;
	if (A.sign == 0) return -B;
	signed_BigInt R;
	if (A.sign * B.sign == -1)
	{
		R.sign = A.sign;
		R.data = A.data + B.data;
	}
	else
	{
		int k = compare(A.data, B.data);
		if (k == 0)
		{
			R.sign = 0;
			R.data = 0;
			return R;
		}
		if (A.sign == 1 && B.sign == 1)
		{
			if (k == -1)
			{
				R.data = B.data - A.data;
				R.sign = -1;
			}
			else
			{
				R.data = A.data - B.data;
				R.sign = 1;
			}
		}
		else
		{
			if (k == -1)
			{
				R.data = B.data - A.data;
				R.sign = 1;
			}
			else
			{
				R.data = A.data - B.data;
				R.sign = -1;
			}
		}
	}
	return R;
}

signed_BigInt operator * (const signed_BigInt &A, const signed_BigInt &B)
{
	signed_BigInt R;
	if (A.sign * B.sign == 0)
	{
		R.data = 0;
		R.sign = 0;
		return R;
	}
	R.data = A.data * B.data;
	R.sign = A.sign * B.sign;
	return R;
}

signed_BigInt operator / (const signed_BigInt &A, const signed_BigInt &B)
{
	signed_BigInt R;
	if (A.sign == 0)
	{
		R.data = 0;
		R.sign = 0;
		return R;
	}
	R.data = A.data / B.data;
	if (R.data.len == 0)
		R.sign = 0;
	else
		R.sign = A.sign * B.sign;
	return R;
}

signed_BigInt operator % (const signed_BigInt &A, const signed_BigInt &B)
{
	signed_BigInt R;
	if (A.sign == 0)
	{
		R.data = 0;
		R.sign = 0;
		return R;
	}
	R.data = A.data % B.data;
	if (R.data.len == 0)
	{
		R.sign = 0;
		return R;
	}
	R.sign = 1;
	if (A.sign * B.sign == -1)
		R.data = B.data - A.data % B.data;
	return R;
}


signed_BigInt signed_read()
{
	signed_BigInt ret;
	char ch;
	ch = getc(stdin);
	if (ch == '-')
		ret.sign = -1;
	else
	{
		ungetc(ch, stdin);
		ret.sign = 1;
	}
	ret.data = unsigned_read();
	if (compare(ret.data, unsigned_Zero) == 0)
		ret.sign = 0;
	return ret;
}


