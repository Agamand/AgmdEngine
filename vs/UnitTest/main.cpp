#include <vector>
#include <Windows.h>
#include <cstdio>
#include <vector>


#include <Thread\ThreadPool.h>
#define _USE_MATH_DEFINES
#include <math.h>


void testSphere2Cart2Sphere()
{
    for (int i = 0; i <= 0; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            float a = (M_PI * 2 * i) / 50.0f, b = M_PI_2 - M_PI * j / 50.0f;
            float x = cosf(a) * cosf(b),
                y = sinf(a) * cosf(b),
                z = sinf(b);
            float a2, b2;
            /*a2 = atan2f(y,x);
            if(y < 0)
                a2 = 2*M_PI+a2;
            b2 = */
            b2 = atan2f(z, sqrt(x * x + y * y));
            a2 = atan2f(y, x);
            if (x < 0)
                a2 += 2 * M_PI;


            printf("x : %.3f,y : %.3f,z : %.3f, alpha : %.3f , beta : %.3f\n", x, y, z, a, b);
            if (a - a2 >= 0.001f)
                printf("i: %.2f j: %.2f   -- a!=a2 %.3f %.3f\n", i / 50.f, j / 50.f, a, a2);
            if (b - b2 >= 0.001f)
                printf("i: %.2f j: %.2f   -- b!=b2 %.3f %.3f\n", i / 50.f, j / 50.f, b, b2);
        }
    }
}


#include <cassert>
int v;

struct C
{
    int a;

    C()
    {
        a = 1;
    }
};

struct B
{
};

struct A
{
    B b;
};

int main(int _a, char** _b)
{
    //MemPoolAllocator<int> allocator;

    //int*& i = allocator.Allocate();
    //SharedPtr<int> a;
    //int v = 10;
    //int v2 = 15;
    //SharedPtr<int> a,b,c = a = b = &v;
    //testSphere2Cart2Sphere();
    /*int d = 10;
    SharedPtr<int>c(&d);
    SharedPtr<int>t(c);
    int e = *c;
    int o = 50;
    t = &o;
    printf("%i",*c);
    printf("%i",e);
    int *& test = c;*/

    // system("pause");
    CThreadPool pool;
    pool.start();
    int a = 1;
    pool.AddJobToPool([&a]() { a = a + 1; });
    pool.AddJobToPool([&a]() { a = a + 1; });

    pool.WaitQueue();
    assert(v==0);
    return v;
}
