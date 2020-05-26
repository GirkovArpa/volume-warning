//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "level.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall MyThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall MyThread::MyThread(bool CreateSuspended) : TThread(CreateSuspended) {
}
//---------------------------------------------------------------------------
void __fastcall MyThread::Execute() {
    NameThreadForDebugging(System::String(L"VolumeWarningThread"));
	//---- Place thread code here ----
    while (true) {
        int micLevel = level();
		Synchronize([&]() {
			Form2->Label1->Caption = IntToStr(micLevel);
			//micLevel = 137;
			int otherConst = 137;
			micLevel *= 1.37;
			Form2->Image1->Stretch = true;
			int imgHeight = 276;
			Form2->Image1->Height = (imgHeight / 100) * micLevel;
			Form2->Image1->Top = 54 + (imgHeight - ((imgHeight / 100) * micLevel));
		});
        //Sleep(100);
    }
}
//---------------------------------------------------------------------------






