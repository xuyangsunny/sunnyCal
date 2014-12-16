/********************************************************************
	created:	2014/12/15
	created:	15:12:2014   19:42
	filename: 	\\psf\Home\Downloads\Com????-cd\SETUP\CODE\sunnyCal\sunnyCal\sunnyCal\iface.cpp
	file path:	\\psf\Home\Downloads\Com????-cd\SETUP\CODE\sunnyCal\sunnyCal\sunnyCal
	file base:	iface
	file ext:	cpp
	author:		sunny Xuyang

	purpose:	主要是来学习com组件
*********************************************************************/
//#include <iostream>
//#include <objbase.h>
//#include <math.h>
#pragma once
//************************************
// Method:    trace
// FullName:  trace
// Access:    public
// Returns:   void
// Qualifier: 打印各种字符串
// Parameter: char * msg 传入需要打印的字符串
//************************************
//using namespace std;
extern "C"
{
extern const IID IID_CALBASE;
extern const IID IID_CALSTD;
extern const IID IID_CALSUP;
}

/*简单计算接口，包括加法，乘法*/
interface ICalBase : public IUnknown
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
interface ICalStd : public IUnknown
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

interface ICalSup :public IUnknown
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
