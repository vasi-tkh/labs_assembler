#include <iostream>

void AssemblerFunc(int x, int y)
{
	int z, w;
	__asm
	{
		mov    eax, dword ptr[x] // записали в регист eax значение переменной x
		add    eax, 8			 // добавили к этому значению 8
		cdq						 //  расширяем размерность числа с учетом знака
		div    dword ptr[y]		 // делим на переменную y, записывая остаток в edx
		mov    dword ptr[z], eax // поместили в z значение (x + 8) / y
	}

	__asm
	{
		mov    eax, dword ptr[x] // записали в регист eax значение переменной x
		add    eax, 8			 // добавили к этому значению 8
		cdq						 //  расширяем размерность числа с учетом знака
		div    dword ptr[y]		 // делим на переменную y, записывая остаток в edx
		mov    dword ptr[w], edx // поместили в w значение остаток от (x + 8) / y
	}

	std::cout << "z = " << z << std::endl << "w = " << w << std::endl;
}

void AssemblerAddressFunc(int* x, int* y)
{
	int z, w;
	__asm
	{
		mov    eax, dword ptr[x]		// записали в регистр eax значение адреса переменной x
		mov    eax, dword ptr[eax]		// записываем в регистр eax значение переменной x по адресу
		add    eax, 8					// добавили к этому значению 8
		mov    ecx, dword ptr[y]		// записали в регистр ecx адрес переменной y
		cdq								//  расширяем размерность числа с учетом знака
		div    dword ptr[ecx]			// делим на переменную y, записывая остаток в edx
		mov    dword ptr[z], eax		// поместили в z значение (x + 8) / y
	}

	__asm
	{
		mov    eax, dword ptr[x]		// записали в регистр eax значение адреса переменной x
		mov    eax, dword ptr[eax]		// записываем в регистр eax значение переменной x по адресу
		add    eax, 8					// добавили к этому значению 8
		mov    ecx, dword ptr[y]		// записали в регистр ecx адрес переменной y
		cdq								//  расширяем размерность числа с учетом знака
		div    dword ptr[ecx]			// делим на переменную y, записывая остаток в edx
		mov    dword ptr[w], edx		// поместили в w значение остатка от (x + 8) / y
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
///		Инициализация массива нулями
/// </summary>
/// <param name="n">	Размер массива</param>
void InitializeArray(int pArray[], size_t n)
{
	__asm
	{
		mov ecx, n // записываю в регистр ecx сколько рах ходить по циклу
		mov esi, 0
		mov edx, 0 // ход конем, так как просто 0 он сразу писать не хотел
		mov eax, pArray
		GO :
		mov[eax + 4 * esi], edx // Заполняю нулями в цикле
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
		mov edx, dword ptr[index]   // записываем в ebx индекс
		mov ebx, dword ptr[number]  // записываем в ebx number
		mov eax, pArray

		mov[eax + 4 * edx], ebx
	}

	std::cout << std::endl << "New element on index " << index << " are equal " << pArray[index];
}

void SetFF(int pArray[], unsigned int index)
{
	__asm
	{
		mov edx, dword ptr[index]   // записываем в ebx индекс
		mov ecx, pArray
		mov ebx, [ecx + 4 * edx]	// записываем в ebx число по этому адресу
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