/* const cast、 const menber、 const global*/

#include <iostream>
#include <chunk.h>
using namespace std;

extern const int NN = 22;     // a different constant
extern const int MM;          // error
// declare global constant - storage allocated elsewhere
extern const int QQ;    // external declaration
void newFunction() {
   int x = QQ + NN;
   cout << x << endl;
}

class Snafu {
public:
    Snafu(int x) : mData(x) {}
    //const 参数,只能向小(权限)转换,不能向大(权限)转换
    //第二个 const 表示 {} 内都不能有写操作
    void showSum(const Snafu & other) const
    {
        cout << mData + other.mData << endl;
    }

    void print(){
        cout << "no const method" << endl;
    }
private:
    int mData;
};

void foo(const Snafu & obj1,const Snafu & obj2)
{
    //只有 const Snafu 类型参数 能接受 obj2
    obj1.showSum(obj2);
}

int main() {
    newFunction();

    Snafu obj1(12345);
    obj1.print();
    const Snafu obj2(54321);
//    obj2.print();     /* Error! const object cannot call non-const methods. */

    foo(obj1, obj2);

       return 0;
}



