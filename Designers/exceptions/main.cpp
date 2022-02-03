#if 1  //抛出异常

#include <iostream>
using namespace std;

int division(int x, int y){
    if(y == 0){
        throw 0;
        throw "Division by zero condition!";
    }
}

int main(){

    int m, n;
    cin >> m >> n;
    try {
        cout << division(m, n) << endl;
    }
    //exception 是标准异常，不是普通的异常
    catch(exception e){
        cout << "eception err" << endl;
    }
    catch(int &error){
        cerr << "divasion by " << error << endl;
    }
    catch(const char * msg){
        cerr << msg <<endl;
    }
//	catch(...){
//		cerr <<"other type error"<<endl;
//	}

    return 0;
}


#elif 1  //异常处理

#include <iostream>
using namespace std;


int main(){
    try{
        //try 块中放置可能抛出异常的代码 -》 保护代码
        //new 空间太大，申请内存失败，就会抛出异常
        char * p = new char[0xfffffffff];
    }
    catch(exception e){
        cout<<"new space fail"<<endl;//捕获异常，其中 exception 是系统异常
//		cout<<"new space fail"<<e.what()<<endl;
    }

    return 0;
}

#elif 0 /** 自定义异常 **/
#include <iostream>
#include <exception>
#include <string>
using namespace std;

class MyException : public exception
{
public:
    MyException() : message("Error."){}
    MyException(string str) : message("Error : " + str) {}
    ~MyException() throw () {
    }

    virtual const char* what() const throw () {
        return message.c_str();
    }

private:
    string message;
};

int main()
{
    try
    {
        throw MyException();
    }
    catch(MyException& e)
    {
        std::cout << e.what() << std::flush;
    }
    catch(std::exception& e)
    {
        //其他的错误
    }
}
#endif
