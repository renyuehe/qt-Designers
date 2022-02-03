#include <iostream>
#include "chStack1.h"

int countChar(char c, ChStack &s) {
    int  count = 0;
    while (!s.isEmpty())
        count += (c == s.pop());
    return count;
}


int main()
{
    char a = '1';


    ChStack s(5, "12115");
    int ret = countChar(a, s);
    std::cout << ret << std::endl;


    return 0;
}
