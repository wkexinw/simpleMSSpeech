
#include "pch.h"
#include <Windows.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <sapi.h>
using namespace std;

int main()
{
	//read speech text
	ifstream input("./speech.txt", ios::in);
	stringstream buffer;
	buffer << input.rdbuf();
	string contents(buffer.str());
	/*
	language id
	411		jpanese
	809		chinese
	409		english

	speech speed
	-10 ~ 10
	*/
	string speech= "<VOICE REQUIRED='LANGUAGE=411' /><rate absspeed='-2' />" + contents;

	/*
		#define CP_ACP                    0           // default to ANSI code page
		#define CP_OEMCP                  1           // default to OEM  code page
		#define CP_MACCP                  2           // default to MAC  code page
		#define CP_THREAD_ACP             3           // current thread's ANSI code page
		#define CP_SYMBOL                 42          // SYMBOL translations

		#define CP_UTF7                   65000       // UTF-7 translation
		#define CP_UTF8                   65001       // UTF-8 translation
	*/
	int nLen = MultiByteToWideChar(CP_UTF8, MB_PRECOMPOSED, speech.c_str(), -1, NULL, 0);
	wchar_t * wc = new wchar_t[nLen];
	MultiByteToWideChar(CP_UTF8, MB_PRECOMPOSED, speech.c_str(), -1, wc, nLen);

	ISpVoice * pVoice = NULL;

	
	//COM initial   
	
	if (FAILED(::CoInitialize(NULL)))
		
		return FALSE;

	
	//get ISpVoice interface   
	
	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
	
	if (SUCCEEDED(hr))
	{
		
		hr = pVoice->Speak(wc, SPF_DEFAULT | SPF_IS_XML, NULL);
		

	}

	pVoice->Release();
		
	pVoice = NULL;
	

	return 0;
}

