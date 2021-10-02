#include <iostream>
#include <iomanip>
using namespace std;

void print16(void* p)
{
	cout << "unsigned hex16 = " << hex << *(reinterpret_cast<unsigned short*>(p)) << endl;
	cout << "unsigned dec16 = " << dec << *(reinterpret_cast<unsigned short*>(p)) << endl;
	cout << "signed hex16 = " << hex << *(reinterpret_cast<short*>(p)) << endl;
	cout << "signed dec16 = " << dec << *(reinterpret_cast<short*>(p)) << endl;
}

void print32(void* p)
{
	cout << "unsigned hex32 = " << hex << *(reinterpret_cast<unsigned int*>(p)) << endl;
	cout << "unsigned dec32 = " << dec << *(reinterpret_cast<unsigned int*>(p)) << endl;
	cout << "signed hex32 = " << hex << *(reinterpret_cast<int*>(p)) << endl;
	cout << "signed dec32 = " << dec << *(reinterpret_cast<int*>(p)) << endl;
}

void print64(void* p)
{
	cout << "unsigned hex64 = " << hex << *(reinterpret_cast<unsigned long long*>(p)) << endl;
	cout << "unsigned dec64 = " << dec << *(reinterpret_cast<unsigned long long*>(p)) << endl;
	cout << "signed hex64 = " << hex << *(reinterpret_cast<long long*>(p)) << endl;
	cout << "signed dec64 = " << dec << *(reinterpret_cast<long long*>(p)) << endl;
}

void CastSignedFrom16To32(short p)
{
	int res32 = static_cast<int> (p);

	cout << endl << "--------------" << endl;

	cout << p << endl;

	print16(&p);

	print32(&res32);
}

void CastUnsignedFrom16To32(unsigned short p)
{
	unsigned int res32 = static_cast<unsigned int> (p);

	cout << endl << "--------------" << endl;

	cout << p << endl;

	print16(&p);

	print32(&res32);
}

void PrintDumb(void* p, size_t N)
{
	unsigned char* dump1 = (unsigned char*)p;
	unsigned short* dump = (unsigned short*)dump1;

	for (size_t i = 0; i < N; i++)
	{
		cout << hex << (unsigned short)(*(dump1++)) << "_";
	}
}

int main()
{
	cout << endl << "char = " << (sizeof(char)) << endl;
	cout << "signed char = " << (sizeof(signed char)) << endl;
	cout << "unsigned char = " << (sizeof(unsigned char)) << endl;
	cout << "char* = " << (sizeof(char*)) << endl;
	cout << "wchar_t = " << (sizeof(wchar_t)) << endl;
	cout << "wchar_t* = " << (sizeof(wchar_t*)) << endl;
	cout << "short = " << (sizeof(short)) << endl;
	cout << "short* = " << (sizeof(short*)) << endl;
	cout << "int = " << (sizeof(int)) << endl;
	cout << "int* = " << (sizeof(int*)) << endl;
	cout << "long = " << (sizeof(long)) << endl;
	cout << "long* = " << (sizeof(long*)) << endl;
	cout << "long long = " << (sizeof(long long)) << endl;
	cout << "long long* = " << (sizeof(long long*)) << endl;
	cout << "float = " << (sizeof(float)) << endl;
	cout << "float* = " << (sizeof(float*)) << endl;
	cout << "double = " << (sizeof(double)) << endl;
	cout << "double* = " << (sizeof(double*)) << endl;
	cout << "long double = " << (sizeof(long double)) << endl;
	cout << "long double* = " << (sizeof(long double*)) << endl;

	cout << endl << "--------------" << endl;

	unsigned int value = 0x0000;
	unsigned int value1 = 0xFFFF;
	int value2 = 0x8000;
	int value3 = +0xFFFF;
	int y = 3, z = -8;

	print16(&value);
	print16(&value1);
	print16(&value2);
	print16(&value3);
	print16(&y);
	print16(&z);

	cout << endl << "--------------" << endl;

	value = 0x0000;
	value1 = 0xFFFFFFFF;
	value2 = 0x80000000;
	value3 = +0xFFFFFFFF;
	float x = 0xA1B2C3D4, y1 = 3, z1 = -8;

	print32(&value);
	print32(&value1);
	print32(&value2);
	print32(&value3);
	print32(&x);
	print32(&y1);
	print32(&z1);

	cout << endl << "--------------" << endl;

	print64(&value);
	print64(&value1);
	print64(&value2);
	print64(&value3);
	print64(&x);
	print64(&y1);
	print64(&z1);

	value = 0x0000;
	value1 = 0xFFFF;
	value2 = 0x8000;
	value3 = +0xFFFF;

	CastSignedFrom16To32(value);
	CastSignedFrom16To32(value1);
	CastUnsignedFrom16To32(value2);
	CastUnsignedFrom16To32(value3);

	int x1 = 0xA1B2C3D4;
	int aray[3] = { 1,2,3 };
	double y2 = 0.96;
	char charArray[] = "bcdxy";
	char charArray1[] = "ёжзий";
	wchar_t charArray2[] = "bcdxy";
	wchar_t charArray3[] = "ёжзий";

	cout << endl << "--------------" << "int" << endl;
	PrintDumb(&x1, sizeof(x));

	cout << endl << "--------------" << "int aray" << endl;
	PrintDumb(&aray, 3 * sizeof(int));

	cout << endl << "--------------" << "double" << endl;
	PrintDumb(&y2, sizeof(y2));

	cout << endl << "--------------" << "char" << endl;
	PrintDumb(&charArray, 6 * sizeof(char));

	cout << endl << "--------------" << "char" << endl;
	PrintDumb(&charArray1, 6 * sizeof(char));

	cout << endl << "--------------" << "wchar_t" << endl;
	PrintDumb(&charArray2, 3 * sizeof(wchar_t));

	cout << endl << "--------------" << "wchar_t" << endl;
	PrintDumb(&charArray3, 3 * sizeof(wchar_t));

	return 0;
}
