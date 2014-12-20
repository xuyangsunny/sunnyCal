// COMT13.cpp : 定义 DLL 应用程序的导出函数。
//




/********************************************************************
	created:	2014/12/19
	created:	19:12:2014   20:55
	filename: 	\\psf\Home\Documents\Visual Studio 2010\Projects\sunnyCal\COMT13\comt13.cpp
	file path:	\\psf\Home\Documents\Visual Studio 2010\Projects\sunnyCal\COMT13
	file base:	comt13
	file ext:	cpp
	author:		xuyang

	purpose:这个文件主要是组件13，其中只有接口 ICalBase和ICalSup
*********************************************************************/
#include <iostream>
#include <objbase.h>
#include "iface.h"
#include "registry.h"
using namespace std;
static HMODULE  g_hModule = NULL;
// Friendly name of component
const char g_szFriendlyName[] = "gszCOMT134CalBaseAndCalSupOnly,COMT13";
// Version-independent ProgID
const char g_szVerIndProgID[] = "gszCOMT134VerIndProgID.COMT13" ;

// ProgID
const char g_szProgID[] = "gszCOMT134ProgID.COMT13.1" ;

static long  g_cComponents = 0;
static long  g_cServeLock = 0;
void trace ( char* msg )
{
    if ( msg != NULL )
    {
        std::cout << msg << std::endl;
    }
}
class MyCal: public ICalSup
{
    public:
        MyCal();
        ~MyCal();
        
      
		virtual void Sort ( int* pArray, int n )   //throw std::exception("The method or operation is not implemented.");
		{
			if ( pArray == NULL )
			{
				return;
			}

			for ( int i = 0; i < n; ++i )
			{
				for ( int j = 0; j < n - i - 1; ++j )
				{
					if ( pArray[j + 1] < pArray[j] )
					{
						int temp = pArray[j];
						pArray[j] = pArray[j + 1];
						pArray[j + 1] = temp;
					}
				}
			}

			for ( int i = 0; i < n; i++ )
			{
				cout << pArray[i] << " ";
			}

			cout << endl;
		}

		virtual int Fib ( int n )    //throw std::exception("The method or operation is not implemented.");
		{
			int first = 1;
			int second = 1;
			int res = 1;

			for ( int i = 2; i < n; ++i )
			{
				res = first + second;
				first = second;
				second = res;
			}

			cout << "fib: " << res << endl;
			return res;
		}

        
        HRESULT STDMETHODCALLTYPE Init();
        
        virtual HRESULT STDMETHODCALLTYPE QueryInterface ( REFIID riid, void** ppvObject )
        {
            //throw std::exception("The method or operation is not implemented.");
            if ( riid == IID_IUnknown )
            {
                *ppvObject = static_cast<ICalSup* > ( this );
            }
            
            else if ( riid == IID_CALBASE )
            {
                return m_pUnknownInner->QueryInterface(riid,ppvObject);
            }
            
            else if ( riid == IID_CALSUP )
            {
                *ppvObject = static_cast<ICalSup * > ( this );
            }
            
            else
            {
                *ppvObject = NULL;
                return E_NOINTERFACE;
            }
            
            reinterpret_cast<IUnknown*> ( *ppvObject )->AddRef();
            
            return S_OK;
        }
        
        virtual ULONG STDMETHODCALLTYPE AddRef ( void )
        {
            //throw std::exception("The method or operation is not implemented.");
            cout << "MyCal AddRef: " << m_ref + 1 << endl;
            return InterlockedIncrement ( &m_ref );
            // return 0;
        }
        
        virtual ULONG STDMETHODCALLTYPE Release ( void )
        {
            //throw std::exception("The method or operation is not implemented.");
            cout << "MyCal Release :" << m_ref - 1 << endl;
            
            if ( InterlockedDecrement ( &m_ref ) == 0 )
            {
                delete this;
            }
            
            return m_ref;
            //  return 0;
        }
        
    private:
        long m_ref;
        ICalBase* m_pICalBase;
		IUnknown * m_pUnknownInner;
        
};




MyCal::MyCal() : m_ref ( 1 ), m_pICalBase ( NULL ),m_pUnknownInner(NULL)
{
    InterlockedIncrement ( &g_cComponents );
}

MyCal::~MyCal()
{
    InterlockedDecrement ( &g_cComponents );
	//m_ref=1;
	// Counter the pUnknownOuter->Release in the Init method.
	//IUnknown* pUnknownOuter = this ;
	//pUnknownOuter->AddRef() ;
	/*
    if ( m_pICalBase != NULL )
    {
        //delete m_pICalStd;
		m_pICalBase->Release();
    }
	*/
	if (m_pUnknownInner!=NULL)
	{
		m_pUnknownInner->Release();
	}
    
    trace ( "destroy mycal~13" );
}

HRESULT STDMETHODCALLTYPE MyCal:: Init()
{
    HRESULT hr;
	IUnknown * m_pUnknownOuter=reinterpret_cast<IUnknown *>(this);
    hr =::CoCreateInstance ( CLSID_COMT12, m_pUnknownOuter, CLSCTX_INPROC_SERVER, IID_IUnknown, ( LPVOID* ) &m_pUnknownInner );
    
    if ( FAILED ( hr ) )
    {
        trace ( "con not create acc comp" );
        return E_FAIL;
    }
    
    else
    {
		
		hr=m_pUnknownInner->QueryInterface(IID_CALBASE,(void **)&m_pICalBase);//只是作为检验
		if ( FAILED ( hr ) )
		{
			trace ( "con not create acc2 comp" );
			m_pUnknownInner->Release();//关闭内部容器
			return E_FAIL;
		}
		
		m_pICalBase->Release();
        return S_OK;
    }
}

class CFactory: public IClassFactory
{
    public:
        // IUnknown
        virtual HRESULT __stdcall QueryInterface ( const IID& iid, void** ppv ) ;
        
        virtual ULONG   __stdcall AddRef()
        {
            return InterlockedIncrement ( &m_cRef );
        }
        virtual ULONG   __stdcall Release()
        {
            return InterlockedDecrement ( &m_cRef );
        }
        
        // Interface IClassFactory
        virtual HRESULT __stdcall CreateInstance ( IUnknown* pUnknownOuter,
                const IID& iid,
                void** ppv ) ;
        virtual HRESULT __stdcall LockServer ( BOOL bLock ) ;
        
        // Constructor
        CFactory() : m_cRef ( 1 ) {}
        
        // Destructor
        ~CFactory()
        {
            trace ( "Class factory:\t\tDestroy self." ) ;
        }
        
    private:
        long m_cRef ;
};

HRESULT __stdcall CFactory::  CreateInstance ( IUnknown* pUnknownOuter,
        const IID& iid,
        void** ppv )
{
    HRESULT hr;
    
    if ( pUnknownOuter != NULL )
    {
        return CLASS_E_NOAGGREGATION;
    }
    
    MyCal* pMyCal = new MyCal;
    
    if ( pMyCal == NULL )
    {
        return E_OUTOFMEMORY;
    }
    
    hr = pMyCal->Init();
    
    if ( FAILED ( hr ) )
    {
        pMyCal->Release();
        return hr;
    }
    
    hr = pMyCal->QueryInterface ( iid, ppv );
    pMyCal->Release();
    return hr;
}
HRESULT __stdcall CFactory:: QueryInterface ( const IID& riid, void** ppvObject )
{
    if ( riid == IID_IUnknown )
    {
        *ppvObject = static_cast<IClassFactory* > ( this );
    }
    
    else if ( riid == IID_IClassFactory )
    {
        *ppvObject = static_cast<IClassFactory* > ( this );
    }
    
    else
    {
        *ppvObject = NULL;
        return E_NOINTERFACE;
    }
    
    reinterpret_cast<IClassFactory*> ( *ppvObject )->AddRef();
    
    return S_OK;
}


HRESULT __stdcall CFactory:: LockServer ( BOOL bLock )
{
    if ( bLock )
    {
        return  InterlockedIncrement ( &g_cServeLock );
    }
    
    else
    {
        return InterlockedDecrement ( &g_cServeLock );
    }
}



STDAPI DllGetClassObject ( const CLSID& clsid,
                           const IID& iid,
                           void** ppv )
{
    if ( clsid != CLSID_COMT13 )
    {
        return CLASS_E_CLASSNOTAVAILABLE;
    }
    
    HRESULT hr;
    CFactory* pCFactory = new CFactory();
    
    if ( pCFactory == NULL )
    {
        return E_OUTOFMEMORY ;
    }
    
    hr = pCFactory->QueryInterface ( iid, ppv );
    pCFactory->Release();
    return hr;
}
STDAPI DllRegisterServer()
{
    return RegisterServer ( g_hModule, CLSID_COMT13, g_szFriendlyName, g_szVerIndProgID, g_szProgID );
}

STDAPI DllUnregisterServer()
{
    return UnregisterServer ( CLSID_COMT13, g_szVerIndProgID, g_szProgID );
}

STDAPI DllCanUnloadNow()
{
    if ( g_cComponents == 0 && ( g_cServeLock == 0 ) )
    {
        return S_OK;
    }
    
    return S_FALSE;
}
///////////////////////////////////////////////////////////
//
// DLL module information
//
BOOL APIENTRY DllMain ( HANDLE hModule,
                        DWORD dwReason,
                        void* lpReserved )
{
    if ( dwReason == DLL_PROCESS_ATTACH )
    {
        g_hModule = ( HMODULE ) hModule ;
    }
    
    return TRUE ;
}