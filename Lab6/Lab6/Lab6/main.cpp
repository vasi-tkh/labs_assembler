#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

extern "C" bool Task1_asm(int x);
void Task1()
{
    cout << "Task 1:" << endl;
    cout << "x = " << 10 << ", (x >= 8) : " << Task1_asm(10) << endl;
    cout << "x = " << 8 << ", (x >= 8) : " << Task1_asm(8) << endl;
    cout << "x = " << 2 << ", (x >= 8) : " << Task1_asm(2) << endl;
    cout << endl;
}

void Task2()
{
    int x = 8;
    int y;
    __asm__ __volatile__
    (
     "movl %[x], %%ecx\n"
     "movl %[y], %%eax\n"
     "cmpl $7,   %%ecx\n"
     "movl $23, %%eax\n"

     "leal 76(%%ecx,%%ecx,4), %%edx \n"
     "cmovlel %%edx, %%eax\n"

     "movl %%eax, %[y]\n"
     :[y]"=m"(y)
     :[x]"g"(x),[Zero]"rm"(0)
     :"eax", "ecx","edx",  "cc"
    );

    cout << "Task 2:" << endl;
    cout << "x = " << x << ", y = " << y << endl;
    x = 2;
    __asm__ __volatile__
    (
     "movl %[x], %%ecx\n"
     "movl %[y], %%eax\n"
     "cmpl $7,   %%ecx\n"
     "movl $23, %%eax\n"

     "leal 76(%%ecx,%%ecx,4), %%edx \n"
     "cmovlel %%edx, %%eax\n"

     "movl %%eax, %[y]\n"
     :[y]"=m"(y)
     :[x]"g"(x),[Zero]"rm"(0)
     :"eax", "ecx","edx",  "cc"
    );

    cout << "x = " << x << ", y = " << y << endl;
    cout << endl;
}

extern "C" double Task3_asm(double x);
void Task3()
{
    cout << "Task 3:" << endl;
    cout << "x = " << 10.1 << ", y(x) = " << Task3_asm(10.1) << endl;

    cout << endl;
}

extern "C" int Task4_asm(int N, int x);
void Task4()
{
    int N;
    int x;

    cout << "Task 4:" << endl;

    cout << "Input N: ";
    cin >> N;
    cout << "Input x0: ";
    cin >> x;

    cout << Task4_asm(N,x);

    cout << endl << endl;
}

extern "C" void Task5_asm(int* M, size_t L);
void Task5()
{
    size_t L = 5;
    int M[L];

    Task5_asm(M,L);

    cout << "Task 5: " << endl;
    for(int i = 0; i < L;i++)
        cout << setw(5) << M[i];
    cout << endl << endl;
}

extern "C" double Task6_asm(double eps);
void Task6()
{
    double eps = pow(10,-6);

    cout << "Task 6:" << endl;
    cout << "Sum = " << Task6_asm(eps) << endl;
}

int main()
{
    Task1();
    Task2();
    // Task3();
    // Task4();
    Task5();
    Task6();

    return 0;
}

