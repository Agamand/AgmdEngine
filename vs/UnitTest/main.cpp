#include <Allocator/MemPoolAllocator.h>
#include <Utilities/SmartPtr.h>
#include <vector>
#include <Windows.h>
#include <cstdio>
#include <vector>

using namespace AgmdUtilities;


void bidule()
{
	int *c = new int(0);
	SmartPtr<int> a = c;
	*a = 1;
	SmartPtr<int> b = c;
	
	
	printf("%i %i",*a,*b);
	
	/**/
	return;
}




int main(int _a, char** _b)
{
    //MemPoolAllocator<int> allocator;
    
    //int*& i = allocator.Allocate();
    //SharedPtr<int> a;
    //int v = 10;
    //int v2 = 15;
    //SharedPtr<int> a,b,c = a = b = &v;
	bidule();
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