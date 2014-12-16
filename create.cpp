#include <iostream>
#include <objbase.h>
#include "create.h"
using namespace std;
typedef  IUnknown* (*CREATEFUNCPTR)();
IUnknown* CallCreateInstance(char* name) 
{
	// Load dynamic link library into process.
	HMODULE hmodule=::LoadLibrary(name);
	if(hmodule==NULL)
	{
		cout<<"error CALL "<<endl;
		return NULL;
	}
	CREATEFUNCPTR createInstance =(CREATEFUNCPTR)GetProcAddress(hmodule,"CreateInstance");
		if(createInstance==NULL)
		{
			cout<<"error CALL 2"<<endl;
		  return NULL;
		}
		return createInstance();
}