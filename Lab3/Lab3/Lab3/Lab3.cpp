#include <iostream>

void AssemblerFunc(int x, int y)
{
	int z, w;
	__asm
	{
		mov    eax, dword ptr[x] // �������� � ������ eax �������� ���������� x
		add    eax, 8			 // �������� � ����� �������� 8
		cdq						 //  ��������� ����������� ����� � ������ �����
		div    dword ptr[y]		 // ����� �� ���������� y, ��������� ������� � edx
		mov    dword ptr[z], eax // ��������� � z �������� (x + 8) / y
	}

	__asm
	{
		mov    eax, dword ptr[x] // �������� � ������ eax �������� ���������� x
		add    eax, 8			 // �������� � ����� �������� 8
		cdq						 //  ��������� ����������� ����� � ������ �����
		div    dword ptr[y]		 // ����� �� ���������� y, ��������� ������� � edx
		mov    dword ptr[w], edx // ��������� � w �������� ������� �� (x + 8) / y
	}

	std::cout << "z = " << z << std::endl << "w = " << w << std::endl;
}

void AssemblerAddressFunc(int* x, int* y)
{
	int z, w;
	__asm
	{
		mov    eax, dword ptr[x]		// �������� � ������� eax �������� ������ ���������� x
		mov    eax, dword ptr[eax]		// ���������� � ������� eax �������� ���������� x �� ������
		add    eax, 8					// �������� � ����� �������� 8
		mov    ecx, dword ptr[y]		// �������� � ������� ecx ����� ���������� y
		cdq								//  ��������� ����������� ����� � ������ �����
		div    dword ptr[ecx]			// ����� �� ���������� y, ��������� ������� � edx
		mov    dword ptr[z], eax		// ��������� � z �������� (x + 8) / y
	}

	__asm
	{
		mov    eax, dword ptr[x]		// �������� � ������� eax �������� ������ ���������� x
		mov    eax, dword ptr[eax]		// ���������� � ������� eax �������� ���������� x �� ������
		add    eax, 8					// �������� � ����� �������� 8
		mov    ecx, dword ptr[y]		// �������� � ������� ecx ����� ���������� y
		cdq								//  ��������� ����������� ����� � ������ �����
		div    dword ptr[ecx]			// ����� �� ���������� y, ��������� ������� � edx
		mov    dword ptr[w], edx		// ��������� � w �������� ������� �� (x + 8) / y
	}

	std::cout << "z = " << z << std::endl << "w = " << w << std::endl;
}

void CheckFunc(int x, int y)
{
	int z = (x + 8) / y;
	int w = (x + 8) % y;

	std::cout << "z = " << z << std::endl << "w = " << w << std::endl;
}

/// <summary>
///		������������� ������� ������
/// </summary>
/// <param name="n">	������ �������</param>
void InitializeArray(int pArray[], size_t n)
{
	__asm
	{
		mov ecx, n // ��������� � ������� ecx ������� ��� ������ �� �����
		mov esi, 0
		mov edx, 0 // ��� �����, ��� ��� ������ 0 �� ����� ������ �� �����
		mov eax, pArray
		GO :
		mov[eax + 4 * esi], edx // �������� ������ � �����
			inc esi
			loop GO
	}

	for (size_t i = 0; i < n; i++)
	{
		std::cout << pArray[i] << " ";
	}
}

void SetNumber(int pArray[], unsigned int index, int number)
{
	__asm
	{
		mov edx, dword ptr[index]   // ���������� � ebx ������
		mov ebx, dword ptr[number]  // ���������� � ebx number
		mov eax, pArray

		mov[eax + 4 * edx], ebx
	}

	std::cout << std::endl << "New element on index " << index << " are equal " << pArray[index];
}

void SetFF(int pArray[], unsigned int index)
{
	__asm
	{
		mov edx, dword ptr[index]   // ���������� � ebx ������
		mov ecx, pArray
		mov ebx, [ecx + 4 * edx]	// ���������� � ebx ����� �� ����� ������
		bts [eax], ebx
	}

	std::cout << std::endl << "New element on index " << index << " are equal " << pArray[index];
}

int main()
{
	int a = 2, b = 3;
	// AssemblerFunc(a, b);
	// AssemblerAddressFunc(&a, &b);

	/*std::cout << "Check: " << std::endl;
	CheckFunc(a, b);*/

	std::cout << "Create array: " << std::endl;

	int n = 5;
	int* pArray = new int[n];

	InitializeArray(pArray, n);
	SetNumber(pArray, 1, 789);
	//SetFF(pArray, 1);

	delete[] pArray;
}