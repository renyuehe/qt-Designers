#include <iostream>
using namespace std;



//************************* array VS ptr 数组和指针
int main()  {
   int a[] = {12, 34, 56, 78};
   cout << a << "\t" << &a[1] - a << endl;
   int x = 99;
//   a = &x;
   int* pa;
   cout << pa << endl;
   pa = &x;
   cout << pa << "\t" << pa - &a[3] << endl;
   cout << a[4] << "\t" << a[5] << endl;
   cout << *(a + 2) << "\t" << sizeof(int) <<endl;
   void* pv = a;
   cout << pv << endl;
   int* pi = static_cast<int*>(pv);
   cout << *(pi + 2) << endl;
   return 0;
}

////************************* pointer Arith 指针运算
//int main()  {
//    using namespace std;
//    int y[] = {3, 6, 9};
//    int x = 12;
//    int* px;
//    px = y;  /* y, or any array name, is an "alias" for a
//        pointer to the first element in the array */
//    cout << "What's next: " << *++px << endl;
//    cout << "What's next: " << *++px << endl;
//    cout << "What's next: " << *++px << endl;
//    cout << "What's next: " << *++px << endl;
//    return 0;
//}


////************************* pointerIndex 指针索引
//int main()  {
//    int x = 23;
//    int y = 45;
//    int* px = &x;
//    cout << "px[0] = " << px[0] << endl;
//    cout << "px[1] = " << px[1] << endl;
//    cout << "px[2] = " << px[2] << endl;
//    cout << "px[-1] = " << px[-1] << endl;
//    return 0;
//}


////************************* returning pointers
//#include <assert.h>

//int paramSize;

//void bar(int* integers) {
//    integers[2]=3;                      /* Change the third element in the incoming array. */
//}

//int* foo(int arrayparameter[]) {
//    using namespace std;
//    paramSize = sizeof(arrayparameter);
//    bar(arrayparameter);                /* Pass an array by pointer to a function. */
//    return arrayparameter;              /* Return an array as a pointer from a function. */
//}

//int main(int argc, char** argv) {
//    int intarray2[40] = {9,9,9,9,9,9,9,2,1};
//    char chararray[20] = "Hello World"; /* Special syntax for initializing char array. */
//    int intarray1[20];                  /* Uninitialized memory. */
//    int* retval;                        /* Uninitialized pointer. */

////  intarray1 = foo(intarray2);         /* Error, intarray1 is like a char* const, it cannot be assigned to. */

//    retval = foo(intarray2);
//    assert (retval[2] == 3);
//    assert (retval[2] = intarray2[2]);
//    assert (retval == intarray2);
////    int refSize = getSize(intarray2);
////    assert(refSize == paramSize);
//    return 0;
//}

