#include "sunny.h"
#ifdef SUNNY5
#include <iostream>
#include <objbase.h>
#include "iface.h"
using namespace std;
int main()
{
    HRESULT hr;
    hr = CoInitialize ( NULL );
    
    if ( FAILED ( hr ) )
    {
        return -1;
    }
    
    int res = 0;
    int array[10] = {3, 34, 45, 22, 44, 432, 22, 75, 43, 21 };
    ICalBase* pICalBase = NULL;
    hr =::CoCreateInstance ( CLSID_COMT12, NULL, CLSCTX_INPROC_SERVER, IID_CALBASE, ( LPVOID* ) &pICalBase );
    
    
    if ( SUCCEEDED ( hr ) )
    {
        res = pICalBase->Add ( 1, 2 );
        res = pICalBase->Mul ( 33, 44 );
       
    }
    
    ICalStd* PICalStd = NULL;
    hr = pICalBase->QueryInterface ( IID_CALSTD, ( void** ) &PICalStd );
    
    if ( SUCCEEDED ( hr ) )
    {
        res = PICalStd->Sqrt ( 10 );
        res = PICalStd->Sum ( 10 );
        PICalStd->Release();
    }
    
    ICalSup* PICalSup = NULL;
    hr = pICalBase->QueryInterface ( IID_CALSUP, ( void** ) &PICalSup );
    
    if ( SUCCEEDED ( hr ) )
    {
        res = PICalSup->Fib ( 10 );
        PICalSup->Sort ( array, 10 );
        PICalSup->Release();
    }
    
    pICalBase->Release();
    CoUninitialize();
    system ( "pause" );
    return 0;
}
#endif