#include <Allocator/MemPoolAllocator.h>
#include <vector>
#include <Windows.h>
#include <cstdio>

using namespace AgmdUtilities;

int main(int _a, char** _b)
{
    //MemPoolAllocator<int> allocator;
    
    //int*& i = allocator.Allocate();
    //SharedPtr<int> a;
    int v = 10;
    int v2 = 15;
    SharedPtr<int> a,b,c = a = b = &v;


    
    /*int d = 10;
    SharedPtr<int>c(&d);
    SharedPtr<int>t(c);
    int e = *c;
    int o = 50;
    t = &o;
    printf("%i",*c);
    printf("%i",e);
    int *& test = c;*/ 

    system("pause");

}