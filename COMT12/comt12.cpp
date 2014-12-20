
/********************************************************************
	created:	2014/12/19
	created:	19:12:2014   20:55
	filename: 	\\psf\Home\Documents\Visual Studio 2010\Projects\sunnyCal\COMT12\comt12.cpp
	file path:	\\psf\Home\Documents\Visual Studio 2010\Projects\sunnyCal\COMT12
	file base:	comt12
	file ext:	cpp
	author:		xuyang

	purpose:这个文件主要是组件12，其中只有接口 ICalBase和ICalStd
*********************************************************************/
#include <iostream>
#include <objbase.h>
#include "iface.h"
#include "registry.h"
using namespace std;
static HMODULE  g_hModule = NULL;
// Friendly name of component
const char g_szFriendlyName[] = "gszCOMT12CalBaseAndCalStdOnly,COMT12";
// Version-independent ProgID
const char g_szVerIndProgID[] = "gszCOMT12VerIndProgID.COMT12" ;

// ProgID
const char g_szProgID[] = "gszCOMT12ProgID.COMT12.1" ;

static long  g_cComponents = 0;
static long  g_cServeLock = 0;
struct INonDelegatingUnknown
{
    virtual HRESULT __stdcall NonDelegatingQueryInterface ( REFIID riid, void** ppvObject ) = 0; 
    virtual ULONG   __stdcall NonDelegatingAddRef() = 0;
	virtual ULONG __stdcall NonDelegatingRelease ( void ) = 0;
};

void trace ( char* msg )
{
    if ( msg != NULL )
    {
        std::cout << msg << std::endl;
    }
}
class MyCal: public ICalBase, public ICalStd, public INonDelegatingUnknown
{
    public:
        MyCal ( IUnknown* pUnknownOuter );
        ~MyCal();
        
        virtual int Add ( int a, int b )   //throw std::exception("The method or operation is not implemented.");
        {
            cout << "ADD :" << a + b << endl;
            return a + b;
        }
        
        virtual int Mul ( int a, int b )   
        {
            cout << "a*b :" << a* b << endl;
            return a * b;
        }
        virtual int Sqrt ( int a )   
        {
            return m_pICalStd->Sqrt ( a );
        }
        
        virtual int Sum ( int n )   
        {
            return m_pICalStd->Sum ( n );
        }
        
        
        HRESULT STDMETHODCALLTYPE Init();
        
        virtual HRESULT STDMETHODCALLTYPE QueryInterface ( REFIID riid, void** ppvObject )
        {
			return m_pUnknownOuter->QueryInterface(riid,ppvObject);
        }
        
        virtual ULONG STDMETHODCALLTYPE AddRef ( void )
        {
            return m_pUnknownOuter->AddRef();
        }
        
        virtual ULONG STDMETHODCALLTYPE Release ( void )
        {
            //throw std::exception("The method or operation is not implemented.");
            return m_pUnknownOuter->Release();
        }
        
        virtual HRESULT __stdcall NonDelegatingQueryInterface ( REFIID riid, void** ppvObject ) ;
		virtual ULONG   __stdcall NonDelegatingAddRef() ;
        virtual ULONG __stdcall NonDelegatingRelease ( void ) ;
        
        
    private:
        long m_ref;
        ICalStd* m_pICalStd;//包含时使用的内部指针
        IUnknown* m_pUnknownOuter;//聚合时使用的指针，如果为非聚合状态，则是Iunknown包装的 InonDelegate指针
        
};

HRESULT __stdcall MyCal:: NonDelegatingQueryInterface ( REFIID riid, void** ppvObject )//直接选文函数  返回的是 INonDelegatingUnknown ref自己这边加，如果是其他，ref加在外面
{
    //throw std::exception("The method or operation is not implemented.");
    if ( riid == IID_IUnknown )
    {
        *ppvObject = static_cast< INonDelegatingUnknown* > ( this );
    }
    
    else if ( riid == IID_CALBASE )
    {
        *ppvObject = static_cast<ICalBase* > ( this );
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
ULONG __stdcall MyCal::  NonDelegatingRelease ( void )
{
    cout << "MyCal Release :" << m_ref - 1 << endl;
    
    if ( InterlockedDecrement ( &m_ref ) == 0 )
    {
        delete this;
    }
    
    return m_ref;
    //  return 0;
}
ULONG   __stdcall MyCal:: NonDelegatingAddRef()
{
    cout << "MyCal AddRef: " << m_ref + 1 << endl;
    return InterlockedIncrement ( &m_ref );
}


MyCal::MyCal ( IUnknown* pUnknownOuter ) : m_ref ( 1 ), m_pICalStd ( NULL )
{
    InterlockedIncrement ( &g_cComponents );
	//初始化 pUnknownOuter
	if(pUnknownOuter==NULL)
	{
		trace("non delegate");
		m_pUnknownOuter=reinterpret_cast<IUnknown*>(static_cast<INonDelegatingUnknown *>(this));//这句很重要需要琢磨
	}
	else
	{
		trace("delegate ");
		m_pUnknownOuter=pUnknownOuter;
	}
}

MyCal::~MyCal()
{
    InterlockedDecrement ( &g_cComponents );
    
    if ( m_pICalStd != NULL )//包含指针 需要调用release
    {
        
        m_pICalStd->Release();
    }
    
    trace ( "destroy mycal12" );
}

HRESULT STDMETHODCALLTYPE MyCal:: Init()
{
    HRESULT hr;
    hr =::CoCreateInstance ( CLSID_COMT2, NULL, CLSCTX_INPROC_SERVER, IID_CALSTD, ( LPVOID* ) &m_pICalStd );
    
    if ( FAILED ( hr ) )
    {
        trace ( "con not create contained comp" );
        return E_FAIL;
    }
    
    else
    {
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
    
    if ( pUnknownOuter != NULL && iid != IID_IUnknown )//聚合申请的是 IID_IUnknown
    {
        return CLASS_E_NOAGGREGATION;
    }
    
    MyCal* pMyCal = new MyCal ( pUnknownOuter );
    
    if ( pMyCal == NULL )
    {
        return E_OUTOFMEMORY;
    }
    
    hr = pMyCal->Init();
    
    if ( FAILED ( hr ) )
    {
        pMyCal->NonDelegatingRelease();
        return hr;
    }
    
    hr = pMyCal->NonDelegatingQueryInterface ( iid, ppv );
    pMyCal->NonDelegatingRelease();
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
    if ( clsid != CLSID_COMT12 )
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
    return RegisterServer ( g_hModule, CLSID_COMT12, g_szFriendlyName, g_szVerIndProgID, g_szProgID );
}

STDAPI DllUnregisterServer()
{
    return UnregisterServer ( CLSID_COMT12, g_szVerIndProgID, g_szProgID );
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