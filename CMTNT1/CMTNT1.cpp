#include <iostream>
#include <objbase.h>
#include "../iface.h"
using namespace std;
void trace(char* msg)
{
    if (msg != NULL)
        {
            std::cout << msg << std::endl;
        }
}
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
				  *ppvObject = NULL;
                return E_NOINTERFACE;
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


extern "C" IUnknown* CreateInstance()
{

    IUnknown* pI = static_cast<ICalBase*>(new MyCal);
    pI->AddRef();
    return pI;
}

MyCal::MyCal():m_ref(0) {}

MyCal::~MyCal() {}