// ConsoleApplication2.cpp: �D�n�M���ɡC


#include "stdafx.h"
#include "MyForm.h"
using namespace std;
using namespace System;
using namespace ConsoleApplication2;
int main(array<System::String ^> ^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);	

	Application::Run(gcnew MyForm());
	Application::Exit();
}
