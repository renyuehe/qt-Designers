/** 注册回调演示 **/

/** 单纯的函数指针 使用 是 回调 recall **/
/** 回调利用了数组 实现动态调用 是 钩子 hook **/
#include <stdio.h>

void test1()
{
    printf("====%s=====\n", __func__);
}

void test2()
{
    printf("====%s=====\n", __func__);
}

void test3()
{
    printf("====%s=====\n", __func__);
}
//定义一个函数指针类
typedef void(*FUNC)(void);
//定义一个数组，数组的成员是指针
//是函数指针
FUNC arr[] = {
    //把函数注册到数组
    test1,
    //test3
    test2,
};

//
void kill(int id)
{
    if(id >=(int)(sizeof(arr)/sizeof(arr[0])) ){
        printf("no function.\n");
        return;
    }

    arr[id]();
}
int main()
{
#if 0
    for(int i = 0; i < (int)(sizeof(arr)/sizeof(arr[0])); i++){
        if(arr[i]){
            arr[i]();  //回调函数
        }
    }
#else
    kill(1);
    kill(5);
#endif

    return 0;
}

