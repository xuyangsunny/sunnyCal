#include "sunny.h"
#ifdef SUNNY4
#include <iostream>
#include <objbase.h>
#include "iface.h"
#include "create.h"
using namespace std;
int main()
{
    //MyCal* pMyCal = new MyCal;
    HRESULT hr;
    IUnknown* pI = CallCreateInstance ( "CMTNT1.dll" );
    
    if ( pI == NULL )
    {
        return -1;
    }
    
    int res = 0;
    int array[10] = {3, 34, 45, 22, 44, 432, 22, 75, 43, 21 };
    ICalBase* pICalBase = NULL;
    hr = pI->QueryInterface ( IID_CALBASE, ( void** ) &pICalBase );
    
    if ( SUCCEEDED ( hr ) )
    {
        res = pICalBase->Add ( 1, 2 );
        res = pICalBase->Mul ( 33, 44 );
        pICalBase->Release();
    }
    
    ICalStd* PICalStd = NULL;
    hr = pI->QueryInterface ( IID_CALSTD, ( void** ) &PICalStd );
    
    if ( SUCCEEDED ( hr ) )
    {
        res = PICalStd->Sqrt ( 10 );
        res = PICalStd->Sum ( 10 );
        PICalStd->Release();
    }
    
    ICalSup* PICalSup = NULL;
    hr = pI->QueryInterface ( IID_CALSUP, ( void** ) &PICalSup );
    
    if ( SUCCEEDED ( hr ) )
    {
        res = PICalSup->Fib ( 10 );
        PICalSup->Sort ( array, 10 );
        PICalSup->Release();
    }
    
    pI->Release();
    system ( "pause" );
    return 0;
}
#endif