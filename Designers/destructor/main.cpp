#include <iostream>
#include <string>
using namespace std;

class Thing {
 public:
    Thing(int n) : m_Num(n) {

    }
    ~Thing() {
        cout << "destructor called: "
             << m_Num << endl;
    }

 private:
    string m_String;
    int m_Num;
};

void function(Thing t) {
    Thing lt(106);
    Thing* tp1 = new Thing(107);
    Thing* tp2 = new Thing(108);
    delete tp1;
}

int main() {
    Thing t1(101), t2(102);
    Thing* tp1 = new Thing(103);
    function(t1);
    {  /* Nested block/scope. */
        Thing t3(104);
        Thing* tp = new Thing(105);
    }
    delete tp1;
    return 0;
}

