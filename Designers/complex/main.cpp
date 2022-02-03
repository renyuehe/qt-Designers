#if 0
#include "complex.h"

int main() {
    Complex c1 (4.5, 1.2);
    Complex c2 (3.6, 1.5);

    Complex c3 = c1 + c2;
    Complex c4 = c3 + 1.4; /* Right operand is promoted. */
    Complex c5 = 8.0 - c4; /* Left operand is promoted. */
    Complex c6 = 1.2 + c4; /* Error: left operand
        is not promoted for member operators. */
}


#elif 1
#include "complex.h"
#include <iostream>

int main() {
    using namespace std;
    Complex c1(3.4, 5.6);
    Complex c2(7.8, 1.2);

    cout << c1 << " + " << c2 << " = " << c1 + c2 << endl;
    cout << c1 << " - " << c2 << " = " << c1 - c2 << endl;
    Complex c3 = c1 * c2;
    cout << c1 << " * " << c2 << " = " << c3 << endl;
    cout << c3 << " / " << c2 << " = " << c3 / c2 << endl;
    cout << c3 << " / " << c1 << " = " << c3 / c1 << endl;

    return 0;
}
#endif
