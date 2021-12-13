#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

void Task1()
{
    cout << "Task 1: " << endl;

    cout << "Float:" << endl;

    float Sd_f [3];
    float Sa_f [3];

    int n[3] = {static_cast<int>(pow(10,3)), static_cast<int>(pow(10,6)), static_cast<int>(pow(10,9))};

    for(int k = 0; k < 3; k++)
    {
        for(int i = 1; i <= n[k]; i++)
        {
            Sd_f[k] += static_cast<float>(1)/i;
        }

        for(int i = n[k]; i > 0; i--)
        {
            Sa_f[k] += static_cast<float>(1)/i;
        }

        cout << "n = " << n[k] << " : Sd = " << Sd_f[k] << ", Sa = " << Sa_f[k] << endl;
    }

    cout << "Double:" << endl;

    double Sd_d [3];
    double Sa_d [3];

    for(int k = 0; k < 3; k++)
    {
        for(int i = 1; i <= n[k]; i++)
        {
             Sd_d[k] += static_cast<double>(1)/i;
        }

        for(int i = n[k]; i > 0; i--)
        {
            Sa_d[k] += static_cast<double>(1)/i;
        }

        cout << "n = " << n[k] << " : Sd = " << Sd_d[k] << ", Sa = " << Sa_d[k] << endl;
    }

    cout << endl;
}

double stepForTask2(unsigned long long int i)
{
    return pow(-1,i)*(3.0)/(i+3);
}

double DeviationAndSum(double& t, double a, double b)
{
    double s = a+b;

    double bs = s-a;
    double as = s-bs;
    t = (b-bs)+(a-as);

    return s;
}

void Task2()
{
    double eps = pow(10,-6);

    double sum1 = 0;
    double t = 0;
    double t_i;
    double sum2 = 0;

    // Rump–Ogita–Oishi algorithm
    for(int i = 0; abs(stepForTask2(i+1)) > eps; i++)
    {
        sum1 = DeviationAndSum(t_i,sum1,stepForTask2(i));
        t += t_i;
    }

    for(int i = 0; abs(stepForTask2(i+1)-stepForTask2(i)) > eps; i++)
    {
         sum2 += stepForTask2(i);
    }

    cout << "Task 2:" << endl;
    cout << "Rump-Ogita-Oishi algorithm: sum = " << sum1+t << ", eps = " << eps << endl;
    cout << "Naive algorithm: sum = " << sum2 << ", eps = " << eps << endl;
    cout << "Difference: " << sum1+t-sum2 << endl;
    cout << endl;
}

double stepForTask3(unsigned long long int i, double alpha)
{
    return 1.0/pow(i,alpha);
}

void Task3()
{
    double eps = pow(10,-6);
    double alpha = 2;

    double sum1 = 0;
    double a_i = stepForTask3(1,alpha);
    double t = 0;
    double t_i;
    double sum2 = 0;

    // Rump–Ogita–Oishi algorithm
    for(int i = 1; a_i + stepForTask3(i+1,alpha-1)/(alpha-1) > eps; i++)
    {
        sum1 = DeviationAndSum(t_i,sum1,stepForTask3(i,alpha));
        t += t_i;
        a_i = stepForTask3(i+1,alpha);
    }

    a_i = stepForTask3(1,alpha);

    for(int i = 1; a_i + stepForTask3(i+1,alpha-1)/(alpha-1) > eps; i++)
    {
        sum2 += stepForTask3(i,alpha);
        a_i = stepForTask3(i+1,alpha);
    }

    cout << "Task 3:" << endl;
    cout << "Rump-Ogita-Oishi algorithm: sum = " << sum1+t << ", eps = " << eps << endl;
    cout << "Naive algorithm: sum = " << sum2 << ", eps = " << eps << endl;
    cout << "Difference: " << sum1+t-sum2 << endl;
    cout << endl;
}

extern "C" double Task4_asm_fpu(double x);

void Task4()
{
    double x = 4.25;
    double y = Task4_asm_fpu(x);

    cout << "Task 4:" << endl;
    cout << "Assembler: x = " << x << ", y = " << y << endl;
    cout << "CPP: x = " << x << ", y = " << (pow(2,x)-1)*(2+2*x) << endl;
    cout << endl;
}

void Task5()
{
    double x[4] = {1.1, 2.2, 3.3, 4.4};
    double y[4] = {10.5, 11.6, 12.7, 13.8};

    cout << "Task 5: " << endl;
    cout << "x: ";
    for(int i = 0; i < 4; i++)
    {
         cout << setw(5) << x[i];
    }

    cout << endl;
    cout << "y: ";
    for(int i = 0; i < 4; i++)
    {
        cout << setw(5) << y[i];
    }

    cout << endl;

    double z[4]{0};

    asm(
    "vmovapd (%0), %%ymm0\n"
    "vmovapd (%1), %%ymm1\n"
    "vmovapd (%2), %%ymm2\n"
    "vaddpd %%ymm0, %%ymm1, %%ymm3\n"
    "vsubpd %%ymm1, %%ymm0, %%ymm4\n"
    "vmulpd %%ymm3, %%ymm4, %%ymm2\n"
    "vmovapd %%ymm2, (%2)\n"
    :: "r"(x), "r"(y),"r"(z)
    : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4"
    );

    cout << "z: ";
    for(int i = 0; i < 4; i++)
    {
        cout << setw(5) << z[i] << " ";
    }

    cout << endl << endl;
}


extern "C" double Task6_cpp(double x, double y);
double Task6_cpp(double x, double y)
{
    return 4.6*pow(x,y)-1.3;
}

int main()
{
    Task1();
    Task2();
    Task3();
    Task4_asm_fpu(4.25);
    Task4();
    Task5();
    cout << Task6_cpp(10, 12)<< endl;

    return 0;
}
