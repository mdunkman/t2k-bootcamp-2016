#include "hello.h"

namespace bootcamp {

std::string Hello() 
{
#ifdef __I_HAVE_THE_POWER__
    std::string message = "Welcome to my world; all this power overwhelms me!";
#else
    std::string message = "Hello world!";
#endif /*__I_HAVE_THE_POWER__*/
    return message;
}

};

