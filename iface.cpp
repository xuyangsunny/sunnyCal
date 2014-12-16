///********************************************************************
//	created:	2014/12/15
//	created:	15:12:2014   19:42
//	filename: 	\\psf\Home\Downloads\Com????-cd\SETUP\CODE\sunnyCal\sunnyCal\sunnyCal\iface.cpp
//	file path:	\\psf\Home\Downloads\Com????-cd\SETUP\CODE\sunnyCal\sunnyCal\sunnyCal
//	file base:	iface
//	file ext:	cpp
//	author:		sunny Xuyang
//
//	purpose:	主要是来学习com组件
//*********************************************************************/
#include "sunny.h"
#ifdef SUNNY3
#include <iostream>
#include <objbase.h>
#include <math.h>
////************************************
//// Method:    trace
//// FullName:  trace
//// Access:    public
//// Returns:   void
//// Qualifier: 打印各种字符串
//// Parameter: char * msg 传入需要打印的字符串
////************************************
using namespace std;
void trace(char* msg)
{
    if (msg != NULL)
        {
            std::cout << msg << std::endl;
        }
}
///*简单计算接口，包括加法，乘法*/
interface ICalBase
{
    //************************************
    // Method:    Add
    // FullName:  ICalBase::Add
    // Access:    virtual public
    // Returns:   int
    // Qualifier: 声明一个简单的加法
    // Parameter: int a 第一个加数
    // Parameter: int b 第二个加数
    //************************************
    virtual int Add(int a, int b) = 0;
    //************************************
    // Method:    Mul
    // FullName:  ICalBase::Mul
    // Access:    virtual public
    // Returns:   int
    // Qualifier: 声明一个简单的乘法
    // Parameter: int a 第一个乘数
    // Parameter: int b 第二个乘数
    //************************************
    virtual int Mul(int a, int b) = 0;

};
/************************************************************************/
/*     ICalStd 主要是一些标准的计算接口包括开方运算，求和运算             */
/************************************************************************/
interface ICalStd
{
    //************************************
    // Method:    Sqrt
    // FullName:  ICalStd::Sqrt
    // Access:    virtual public
    // Returns:   int
    // Qualifier: 开方运算
    // Parameter: int a 输入的开方数
    //************************************
    virtual int Sqrt(int a) = 0;
    //************************************
    // Method:    Sum
    // FullName:  ICalStd::Sum
    // Access:    virtual public
    // Returns:   int
    // Qualifier: 求和运算
    // Parameter: int n	输入的是0-n的和 输入小于0为输入错误
    //************************************
    virtual int Sum(int n) = 0;

};

interface ICalSup
{
    //************************************
    // Method:    Sort
    // FullName:  ICalSup::Sort
    // Access:    virtual public
    // Returns:   void
    // Qualifier: 对于一个int数组排序
    // Parameter: int * pArray
    // Parameter: int n int数组的个数
    //************************************
    virtual void Sort(int* pArray, int n) = 0;
    //************************************
    // Method:    Fib
    // FullName:  ICalSup::Fib
    // Access:    virtual public
    // Returns:   int
    // Qualifier: 求取费波拉契数
    // Parameter: int n 第几个 费波拉契数 大于0
    //************************************
    virtual int Fib(int n) = 0;
};

class MyCal: public ICalBase, public ICalStd, public ICalSup
{
public:
    MyCal();
    ~MyCal();

    virtual int Add(int a, int b)      //throw std::exception("The method or operation is not implemented.");
    {
        cout <<"ADD :"<< a + b << endl;
        return a + b;
    }

    virtual int Mul(int a, int b)      //throw std::exception("The method or operation is not implemented.");
    {
        cout << "a*b :" << a* b << endl;
        return a * b;
    }

    virtual int Sqrt(int a)       //throw std::exception("The method or operation is not implemented.");
    {
        cout << "sqrt :" << (int) sqrt(a) << endl;
        return (int) sqrt(a);
    }

    virtual int Sum(int n)       //throw std::exception("The method or operation is not implemented.");
    {
        int sum = 0;

        for (int i = 0; i < n; ++i)
            {
                sum += i;
            }

        cout << "sum : " << sum << endl;
        return sum;
    }

    virtual void Sort(int* pArray, int n)      //throw std::exception("The method or operation is not implemented.");
    {
        if (pArray == NULL)
            {
                return;
            }

        for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n - i - 1; ++j)
                    {
                        if (pArray[j + 1] < pArray[j])
                            {
                                int temp = pArray[j];
                                pArray[j] = pArray[j + 1];
                                pArray[j + 1] = temp;
                            }
                    }
            }
        for (int i = 0; i < n; i++)
            {
                cout << pArray[i] << " ";
            }
        cout << endl;
    }

    virtual int Fib(int n)       //throw std::exception("The method or operation is not implemented.");
    {
        int first = 1;
        int second = 1;
        int res = 1;

        for (int i = 2; i < n; ++i)
            {
                res = first + second;
                first = second;
                second = res;
            }
        cout << "fib: " << res << endl;
        return res;
    }

private:

};

MyCal::MyCal() {}

MyCal::~MyCal() {}

int main()
{
    MyCal* pMyCal = new MyCal;
    int res = 0;
    char buf[100];
    int array[10] = {3, 34, 45, 22, 44, 432, 22, 75, 43, 21 };
    ICalBase* pICalBase = pMyCal;

    if (pICalBase != NULL)
        {
            res = pICalBase->Add(1, 2);
            res = pICalBase->Mul(33, 44);
        }

    ICalStd* PICalStd = pMyCal;

    if (PICalStd != NULL)
        {
            res = PICalStd->Sqrt(10);
            res = PICalStd->Sum(10);
        }

    ICalSup* PICalSup = pMyCal;

    if (PICalSup != NULL)
        {
            res = PICalSup->Fib(10);
            PICalSup->Sort(array, 10);
        }
    system("pause");
    return 0;
}
#endif