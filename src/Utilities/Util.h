#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <Debug/New.h>


namespace Agmd
{

    struct Delete
    {
        template <class T> void operator ()(T*& p) const
        {
            delete p;
            p = NULL;
        }
    };

    inline unsigned int NearestPowerOfTwo(unsigned int value)
    {
        unsigned int temp = value;
        unsigned int powerOfTwo = 0;

        while (temp > 1)
        {
            temp >>= 1;
            ++powerOfTwo;
        }

        unsigned int retval = 1 << powerOfTwo;

        return retval == value ? retval : retval << 1;
    }

    #include <Debug/NewOff.h>

}


#endif //UTIL_H
