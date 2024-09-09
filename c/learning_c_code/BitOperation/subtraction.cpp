#include <iostream>
using namespace std;
int main(void)
{
    int a=15,b=12;              //定义要计算的值
    b=(~b)+1;                   //计算补码
    cout<<"b:*************"<<b<<endl;
    int carry,result;           //定义与运算后的进位值和异或结果
    do{                         //需先进行一次运算，所以使用do while
        result=a^b;             //异或运算
        carry=(a&b)<<1;;        //与运算后左移一位 
        a=result;               //使用异或后的结果和与运算左移一位的结果重复计算
        b=carry;
    }
    while (carry!=0);
    cout<< "结果："<<result<<endl;
}