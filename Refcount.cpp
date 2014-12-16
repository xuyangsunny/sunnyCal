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
#include <iostream>
#include <objbase.h>
#include <math.h>
//************************************
// Method:    trace
// FullName:  trace
// Access:    public
// Returns:   void
// Qualifier: ��ӡ�����ַ���
// Parameter: char * msg ������Ҫ��ӡ���ַ���
//************************************
using namespace std;
extern const IID IID_CALBASE;
extern const IID IID_CALSTD;
extern const IID IID_CALSUP;
void trace(char* msg)
{
    if (msg != NULL)
        {
            std::cout << msg << std::endl;
        }
}
/*�򵥼���ӿڣ������ӷ����˷�*/
interface ICalBase :
public IUnknown
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
interface ICalStd :
public IUnknown
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

interface ICalSup :
public IUnknown
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

class MyCal: public ICalBase, public ICalStd, public ICalSup
{
public:
    MyCal();
    ~MyCal();

    virtual int Add(int a, int b)      //throw std::exception("The method or operation is not implemented.");
    {
        cout << "ADD :" << a + b << endl;
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

    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject)
    {
        //throw std::exception("The method or operation is not implemented.");
        if (riid == IID_IUnknown)
            {
                *ppvObject = static_cast<ICalBase* >(this);
            }
        else if (riid == IID_CALBASE)
            {
                *ppvObject = static_cast<ICalBase* >(this);
            }
        else if (riid == IID_CALSTD)
            {
                *ppvObject = static_cast<ICalStd* >(this);
            }
        else if (riid == IID_CALSUP)
            {
                *ppvObject = static_cast<ICalSup* >(this);
            }
        else
            {
                *ppvObject = NULL;
                return E_NOINTERFACE;
            }
        reinterpret_cast<IUnknown*>(*ppvObject)->AddRef();
        return S_OK;

    }

    virtual ULONG STDMETHODCALLTYPE AddRef(void)
    {
        //throw std::exception("The method or operation is not implemented.");
		cout<<"AddRef: "<<m_ref+1<<endl;
		return InterlockedIncrement(&m_ref);
       // return 0;
    }

    virtual ULONG STDMETHODCALLTYPE Release(void)
    {
        //throw std::exception("The method or operation is not implemented.");
		cout<<"Release :"<<m_ref-1<<endl;
		if (InterlockedDecrement(&m_ref)==0)
		{
			delete this;
		}
		return m_ref;
      //  return 0;
    }

private:
	long m_ref;

};

MyCal::MyCal():m_ref(0) {}

MyCal::~MyCal() {}

static const IID IID_CALBASE = {0x32bb8320, 0xb41b, 0x11cf,
    {0xa6, 0xbb, 0x0, 0x80, 0xc7, 0xb2, 0xd6, 0x82}
} ;
static const IID IID_CALSTD = {0x32bb8322, 0xb41b, 0x11cf,
    {0xa6, 0xbb, 0x0, 0x80, 0xc7, 0xb2, 0xd6, 0x82}
} ;
static const IID IID_CALSUP = {0x32bb8324, 0xb41b, 0x11cf,
    {0xa6, 0xbb, 0x0, 0x80, 0xc7, 0xb2, 0xd6, 0x82}
} ;


IUnknown* CreateInstance()
{

    IUnknown* pI = static_cast<ICalBase*>(new MyCal);
    pI->AddRef();
    return pI;
}
int main()
{
    //MyCal* pMyCal = new MyCal;
	HRESULT hr;
    IUnknown* pI = CreateInstance();
    int res = 0;
    
    int array[10] = {3, 34, 45, 22, 44, 432, 22, 75, 43, 21 };
    ICalBase* pICalBase = NULL;
    hr=pI->QueryInterface(IID_CALBASE, (void**)&pICalBase);

    if (SUCCEEDED(hr))
        {
            res = pICalBase->Add(1, 2);
            res = pICalBase->Mul(33, 44);
			pICalBase->Release();
        }

    ICalStd* PICalStd = NULL;
	 hr=pI->QueryInterface(IID_CALSTD, (void**)&PICalStd);

     if (SUCCEEDED(hr))
        {
            res = PICalStd->Sqrt(10);
            res = PICalStd->Sum(10);
			PICalStd->Release();
        }

    ICalSup* PICalSup = NULL;
	 hr=pI->QueryInterface(IID_CALSUP, (void**)&PICalSup);

    if (SUCCEEDED(hr))
        {
            res = PICalSup->Fib(10);
            PICalSup->Sort(array, 10);
			PICalSup->Release();
        }
	pI->Release();
    system("pause");
    return 0;
}