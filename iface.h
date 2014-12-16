/********************************************************************
	created:	2014/12/15
	created:	15:12:2014   19:42
	filename: 	\\psf\Home\Downloads\Com????-cd\SETUP\CODE\sunnyCal\sunnyCal\sunnyCal\iface.cpp
	file path:	\\psf\Home\Downloads\Com????-cd\SETUP\CODE\sunnyCal\sunnyCal\sunnyCal
	file base:	iface
	file ext:	cpp
	author:		sunny Xuyang

	purpose:	��Ҫ����ѧϰcom���
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
// Qualifier: ��ӡ�����ַ���
// Parameter: char * msg ������Ҫ��ӡ���ַ���
//************************************
//using namespace std;
extern "C"
{
extern const IID IID_CALBASE;
extern const IID IID_CALSTD;
extern const IID IID_CALSUP;
}

/*�򵥼���ӿڣ������ӷ����˷�*/
interface ICalBase : public IUnknown
{
    //************************************
    // Method:    Add
    // FullName:  ICalBase::Add
    // Access:    virtual public
    // Returns:   int
    // Qualifier: ����һ���򵥵ļӷ�
    // Parameter: int a ��һ������
    // Parameter: int b �ڶ�������
    //************************************
    virtual int Add(int a, int b) = 0;
    //************************************
    // Method:    Mul
    // FullName:  ICalBase::Mul
    // Access:    virtual public
    // Returns:   int
    // Qualifier: ����һ���򵥵ĳ˷�
    // Parameter: int a ��һ������
    // Parameter: int b �ڶ�������
    //************************************
    virtual int Mul(int a, int b) = 0;

};
/************************************************************************/
/*     ICalStd ��Ҫ��һЩ��׼�ļ���ӿڰ����������㣬�������             */
/************************************************************************/
interface ICalStd : public IUnknown
{
    //************************************
    // Method:    Sqrt
    // FullName:  ICalStd::Sqrt
    // Access:    virtual public
    // Returns:   int
    // Qualifier: ��������
    // Parameter: int a ����Ŀ�����
    //************************************
    virtual int Sqrt(int a) = 0;
    //************************************
    // Method:    Sum
    // FullName:  ICalStd::Sum
    // Access:    virtual public
    // Returns:   int
    // Qualifier: �������
    // Parameter: int n	�������0-n�ĺ� ����С��0Ϊ�������
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
    // Qualifier: ����һ��int��������
    // Parameter: int * pArray
    // Parameter: int n int����ĸ���
    //************************************
    virtual void Sort(int* pArray, int n) = 0;
    //************************************
    // Method:    Fib
    // FullName:  ICalSup::Fib
    // Access:    virtual public
    // Returns:   int
    // Qualifier: ��ȡ�Ѳ�������
    // Parameter: int n �ڼ��� �Ѳ������� ����0
    //************************************
    virtual int Fib(int n) = 0;
};
