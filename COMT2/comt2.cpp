
/********************************************************************
	created:	2014/12/19
	created:	19:12:2014   20:55
	filename: 	\\psf\Home\Documents\Visual Studio 2010\Projects\sunnyCal\COMT2\comt2.cpp
	file path:	\\psf\Home\Documents\Visual Studio 2010\Projects\sunnyCal\COMT2
	file base:	comt2
	file ext:	cpp
	author:		xuyang

	purpose:这个文件主要是组件1，其中只有接口 ICalStd
*********************************************************************/
#include <iostream>
#include <objbase.h>
#include "iface.h"
#include "registry.h"
using namespace std;
static HMODULE  g_hModule = NULL;
// Friendly name of component
const char g_szFriendlyName[] = "gszCOMT2CalBaseOnly,COMT2";
// Version-independent ProgID
const char g_szVerIndProgID[] = "gszCOMT2VerIndProgID.COMT2" ;

// ProgID
const char g_szProgID[] = "gszCOMT2ProgID.COMT2.1" ;

static long  g_cComponents = 0;
static long  g_cServeLock = 0;
void trace ( char* msg )
{
    if ( msg != NULL )
    {
        std::cout << msg << std::endl;
    }
}
class MyCal: public ICalStd
{
    public:
        MyCal();
        ~MyCal();
        
		virtual int Sqrt ( int a )    //throw std::exception("The method or operation is not implemented.");
		{
			cout << "sqrt :" << ( int ) sqrt ( double ( a ) ) << endl;
			return ( int ) sqrt ( double ( a ) );
		}

		virtual int Sum ( int n )    //throw std::exception("The method or operation is not implemented.");
		{
			int sum = 0;

			for ( int i = 0; i < n; ++i )
			{
				sum += i;
			}

			cout << "sum : " << sum << endl;
			return sum;
		}
        
        
        
        
        
        virtual HRESULT STDMETHODCALLTYPE QueryInterface ( REFIID riid, void** ppvObject )
        {
            //throw std::exception("The method or operation is not implemented.");
            if ( riid == IID_IUnknown )
            {
                *ppvObject = static_cast<ICalStd* > ( this );
            }
            
            else if ( riid == IID_CALSTD )
            {
                *ppvObject = static_cast<ICalStd* > ( this );
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
        
};




MyCal::MyCal() : m_ref ( 1 )
{
    InterlockedIncrement ( &g_cComponents );
}

MyCal::~MyCal()
{
    InterlockedDecrement ( &g_cComponents );
    trace ( "destroy mycal" );
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
    if ( clsid != CLSID_COMT2 )
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
    return RegisterServer ( g_hModule, CLSID_COMT2, g_szFriendlyName, g_szVerIndProgID, g_szProgID );
}

STDAPI DllUnregisterServer()
{
    return UnregisterServer ( CLSID_COMT2, g_szVerIndProgID, g_szProgID );
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